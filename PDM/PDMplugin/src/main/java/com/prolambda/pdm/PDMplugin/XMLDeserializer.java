package com.prolambda.pdm.PDMplugin;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

public class XMLDeserializer {
	 private String endStr = ".xml";
	 private String configFile;
	 private static XStream xStream;
	
	public String getConfigFile() {
		return configFile;
	}

	public void setConfigFile(String configFile) {
		this.configFile = configFile;
	}

	static{
		xStream = new XStream(new DomDriver());
		//xStream.processAnnotations(Project.class);
		xStream.alias("project", PDMProject.class);
		xStream.alias("sourceCode", SourceCode.class);
		xStream.alias("dependence", Dependence.class);
	}
	
	@SuppressWarnings("unused")
	public PDMProject read(){
    	//Company company = new Company();
    	try {
			InputStream in=new FileInputStream(new File("E:\\workspace\\PDMplugin\\work\\jobs\\Test1\\workspace\\P-EF.xml"));
			if(in==null){
				System.out.print("error");
				return null;
			}
			PDMProject company=(PDMProject)xStream.fromXML(in);
			if(company==null){
				System.out.print("company error");
				return null;
			}
			return company;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
    	
    	return null;
    }
	public PDMProject fromXMLs(String path){
		PDMProject project = new PDMProject();
		File file = new File(path);
		File[] fileList = file.listFiles();
		String configfile = null;
		
		//xStream.alias("dependences", DependenceList.class);
		//xStream.addImplicitCollection(Project.class, "dependences");
		for(File confFile:fileList){
			if(confFile.getName().endsWith(endStr)){
				configfile = confFile.getAbsolutePath();
				setConfigFile(confFile.getName());
				break;
			}
		}
		 
		try {
			InputStream fis = new FileInputStream(new File(configfile));
			project = (PDMProject)xStream.fromXML(fis);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return project;
	}

}
