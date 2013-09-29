package com.prolambda.pdm.PDMplugin;


import hudson.Launcher;
import hudson.Extension;
import hudson.util.FormValidation;
import hudson.model.AbstractBuild;
import hudson.model.Action;
import hudson.model.BuildListener;
import hudson.model.AbstractProject;
import hudson.tasks.BuildStepMonitor;

import hudson.tasks.BuildStepDescriptor;
import hudson.tasks.Notifier;
import hudson.tasks.Publisher;
import net.sf.json.JSONObject;
import org.kohsuke.stapler.DataBoundConstructor;
import org.kohsuke.stapler.StaplerRequest;
import org.kohsuke.stapler.QueryParameter;

import javax.servlet.ServletException;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

/**
 * @author jysong
 */
public class PDMPublish extends Notifier  {

	private final String path;


    // Fields in config.jelly must match the parameter names in the "DataBoundConstructor"
    @DataBoundConstructor
    public PDMPublish(String path) {
        this.path = path;

    }

    /**
     * We'll use this from the <tt>config.jelly</tt>.
     */
    public String getPath() {
        return path;
    }
    
    
    @SuppressWarnings({ "rawtypes", "deprecation"})
	@Override
    public boolean perform( AbstractBuild build, Launcher launcher, BuildListener listener) {
        // This is where you 'build' the project.
        // Since this is a dummy, we just say 'hello world' and call that a build.

        // This also shows how you can consult the global configuration of the builder
    	/*
        if (getDescriptor().getUseFrench())
            listener.getLogger().println("Bonjour, "+path+"!");
        else
            listener.getLogger().println("Hello, "+path+"!");
        */
    	//AbstractProject ap = build.getProject();
    	//String scm = ap.getScm().getType();
    	//String retInfo ="";
        String serverUrl = getDescriptor().getServer();
    	PDMService pdmService = new PDMService();
    	BuildMessage message = new BuildMessage();
    	//ArrayList<PDMProject> projects = new ArrayList<PDMProject>();
    	DOMParser parser = new DOMParser();
    	/*
    	String temp = "";
    	String item[] = path.split("\\n");
		for(int i=0;i<item.length;i++){
			String str[] = item[i].split(" ");
			
			temp = str.length+str[1];
		}
	*/
    	message.getPath(path);
    	message.getMessage(build);
    	//message.setRepName(repository);
    	//String strPath = build.getWorkspace().toString()+"\\"+path;
    	String workPath = build.getWorkspace().toString();
    	parser.parse(workPath);
    	//ArrayList<Project> projects = new ArrayList<Project>();
    	ArrayList<PDMProject> projects = parser.readConfig();
    	//temp = parser.readConfigs();
    	//XMLDeserializer xml = new XMLDeserializer();
    	//PDMProject project = xml.fromXMLs(workPath);
    	//String pro = "";
    	
    	//for(PDMProject project:projects){
    	//	pro += project.toString();
    	//}
    	File log = build.getLogFile();
    	try
		{
			pdmService.postMessage(message,projects, serverUrl);
    		pdmService.changeLog(message,projects, log);
			pdmService.uploadFiles(message,workPath,serverUrl,log);
		} catch (Exception e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//listener.getLogger().println("retInfo: "+retInfo+"  path:" + path +"\nproject: "+pro+"@");
		//message.sendMessage();
        return true;
    }

    // Overridden for better type safety.
    // If your plugin doesn't really define any property on Descriptor,
    // you don't have to do this.
 
	@Override
    public DescriptorImpl getDescriptor() {
        //return (DescriptorImpl)super.getDescriptor();
		return DESCRIPTOR;
    }

	public Action getProjectAction(AbstractProject< ?, ?> project) {
        return null;
    }
	
	public BuildStepMonitor getRequiredMonitorService() {
        return BuildStepMonitor.BUILD;
    }
	
	
	@Override
    public boolean needsToRunAfterFinalized() {
        return true;
    }
    
    @Extension
    public static final DescriptorImpl DESCRIPTOR = new DescriptorImpl();
    /**
     * Descriptor for {@link HelloWorldBuilder}. Used as a singleton.
     * The class is marked as public so that it can be accessed from views.
     *
     * <p>
     * See <tt>src/main/resources/hudson/plugins/hello_world/HelloWorldBuilder/*.jelly</tt>
     * for the actual HTML fragment for the configuration screen.
     */
     // This indicates to Jenkins that this is an implementation of an extension point.
    public static final class DescriptorImpl  extends BuildStepDescriptor<Publisher> {
        /**
         * To persist global configuration information,
         * simply store it in a field and call save().
         *
         * <p>
         * If you don't want fields to be persisted, use <tt>transient</tt>.
         */
       // private boolean useFrench;
        private String server;
        
        
        protected DescriptorImpl() {
            super(PDMPublish.class);
            load();
        }
		
        /**
         * Performs on-the-fly validation of the form field 'name'.
         *
         * @param value
         *      This parameter receives the value that the user has typed.
         * @return
         *      Indicates the outcome of the validation. This is sent to the browser.
         */
        public FormValidation doCheckPath(@QueryParameter String value)
                throws IOException, ServletException {
            if (value.length() == 0){
                return FormValidation.error("Please set a path");
            }
            
            return FormValidation.ok();
        }
        
        public FormValidation doCheckServer(@QueryParameter String value)
        		throws IOException, ServletException {
        	if (value.length() == 0)
        		return FormValidation.error("Please set a server");
        	
        	return FormValidation.ok();
        }

        public FormValidation doCheckRepository(@QueryParameter String value)
				throws IOException, ServletException {
        	if (value.length() == 0)
        		return FormValidation.error("Please set a repository");
	
        	return FormValidation.ok();
        }
        
        @SuppressWarnings("rawtypes")
		public boolean isApplicable(Class<? extends AbstractProject> aClass) {
            // Indicates that this builder can be used with all kinds of project types 
            return true;
        }

        /**
         * This human readable name is used in the configuration screen.
         */
        public String getDisplayName() {
            return "Publish to PDM";
        }

        @Override
        public boolean configure(StaplerRequest req, JSONObject formData) throws FormException {
            // To persist global configuration information,
            // set that to properties and call save().
            //useFrench = formData.getBoolean("useFrench");
            server = formData.getString("server");
            //repository = formData.getString("repository");
            // ^Can also use req.bindJSON(this, formData);
            //  (easier when there are many fields; need set* methods for this, like setUseFrench)
            save();
            return super.configure(req,formData);
        }

       // public PDMBuilder newInstance(StaplerRequest req) throws FormException {
            //LOGGER.fine("New instance of ConnectionsPlugin for a job");
            //return new PDMBuilder();
        //}
        /**
         * This method returns true if the global configuration says we should speak French.
         *
         * The method name is bit awkward because global.jelly calls this method to determine
         * the initial state of the checkbox by the naming convention.
         */
       // public boolean getUseFrench() {
       //     return useFrench;
       // }
        public String getServer()
        {
        	return server;
        }
       
    }

}

