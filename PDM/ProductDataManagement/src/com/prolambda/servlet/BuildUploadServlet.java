package com.prolambda.servlet;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

import com.prolambda.controller.ArtifactService;
import com.prolambda.controller.BuildService;
import com.prolambda.controller.ComponentVersionService;
import com.prolambda.controller.DependenceService;
import com.prolambda.controller.LibraryService;
import com.prolambda.controller.ProductVersionService;
import com.prolambda.controller.RepositoryService;
import com.prolambda.model.Artifact;
import com.prolambda.model.ArtifactList;
import com.prolambda.model.Build;
import com.prolambda.model.BuildResult;
import com.prolambda.model.Dependence;
import com.prolambda.model.GuidCreator;
import com.prolambda.model.Library;
import com.prolambda.model.Repository;

public class BuildUploadServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -145471950113298367L;

	private String strFileFolder;
	int buildId = 0;
	int depCount = 0;
	Boolean flag = false;
	
	public void init(){
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		//ServletConfig config = getServletConfig();
		//strFileFolder = config.getInitParameter("strFileFolder");
		File file = new File(strFileFolder);
		if (!file.exists()) {
			file.mkdirs();
		}
	}
	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request, response);
	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		PrintWriter out = response.getWriter(); 
		System.out.println("Upload");
		final long MAX_SIZE = 100 * 1024 * 1024;// 设置上传文件最大为 10M  
		
		DiskFileItemFactory dfif = new DiskFileItemFactory();  
		dfif.setSizeThreshold(4096);// 设置上传文件时用于临时存放文件的内存大小,这里是4K.多于的部分将临时存在硬盘  
		
	    dfif.setRepository(new File(strFileFolder));
		///设置可上传文件的最大尺寸
	    ServletFileUpload sfu = new ServletFileUpload(dfif);  
        // 设置最大上传尺寸  
        sfu.setSizeMax(MAX_SIZE);  
        
        List<?> listFiles = null;  
        try {  
        	listFiles = sfu.parseRequest(request);  
        } catch (FileUploadException e) {// 处理文件尺寸过大异常  
           
            e.printStackTrace();  
        }  
		
        buildId = 0;
    	depCount = 0;
    	flag = false;
        
		//String field = request.getParameter("field");
		//System.out.println("field--->"+field);
		/*
		DiskFileUpload diskFileUpload = new DiskFileUpload();
		diskFileUpload.setSizeMax(1234556677);
		//设置缓冲区大小，这里是2kb
		diskFileUpload.setSizeThreshold(2048);
		//设置临时目录
		diskFileUpload.setRepositoryPath(strFileFolder);
		List<?> listFiles = diskFileUpload.parseRequest(res);
		*/
		
		ArrayList<String > fileNames = new ArrayList<String>();
		ArrayList<String > filePaths = new ArrayList<String>();
		
		
        if (listFiles == null || listFiles.size() == 0) {  
        	out.print("<script language='javascript'>alert('please select file upload');</script>");
            
            //out.println("<a href=\"upload.html\" target=\"_top\">返回</a>");    
        }
       System.out.println("File Size:"+listFiles.size());
        //int buildId = 0;
        if (null != listFiles && listFiles.size()>0) {
        	
        	for(int i=0;i<listFiles.size();i++){
        		FileItem fileItem = (FileItem)listFiles.get(i);
        		if(fileItem.isFormField()){
        			
        			//int count = 0;
        			//Boolean flag = false;
        			//Integer integer = new Integer(i);
        			//Integer count = new Integer(0);
        			i= getBuildMsg(listFiles,i);
        			//System.out.println("Integer:"+i);
        			//System.out.println("DepCount:"+depCount);
        			if(i==-1){
        				return;
        			}
        			i = getDependenceMsg(listFiles,i);
        			i--;
        			
        		}else if(null!=fileItem.getName()){
        			String fileName = fileItem.getName();
        			
					System.out.println("["+i+"] "+"File Name---->"+fileName);
					//long size = fileItem.getSize();
					if("".equals(fileName)){
						continue;
					}
					fileName = fileName.replace("\\", "/");
					String filePath = fileName;
					int index = fileName.lastIndexOf('/');
					if(index!=-1){
						fileName = fileName.substring(index+1);
					}
					//System.out.println("File Name:"+fileName);
					GuidCreator gc = new GuidCreator();
					String guidName = gc.toString();
					File saveFile = new File(strFileFolder,guidName);
					fileNames.add(guidName);
					filePaths.add(filePath);
					try {
						fileItem.write(saveFile);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
        		}
        	}
        	addLibrary(fileNames,filePaths);
        	
			//buildId = buildSer.getIdByRepArt(repName, artName, Integer.parseInt(number));
        	//HashMap<String, String> nameMap = changeName(fileNames,strFileFolder);
        	
        	//InsertLibrary(buildId,depList,filePaths,fileNames,nameMap);
        	//InsertLibrary(filePaths,buildId,nameMap);
        }
	}
	
	public int getDependenceMsg(List<?> listFiles,int i){
	
		//System.out.println("DepCount:"+count);
		//System.out.println();
		DependenceService depSer = new DependenceService();
		
		//DependenceList depList = new DependenceList();
		for(int j=0;j<depCount;j++){
			Dependence dep = new Dependence();
			String depRepName = null;
			String depArtName = null;
			String depNumber = null;
			
			FileItem fieldItem = (FileItem)listFiles.get(i++);
			if(fieldItem.isFormField()&&fieldItem.getFieldName().equals("DepFlag_"+j)){
				dep.setFlag(fieldItem.getString());
				System.out.println("["+(i-1)+"] "+"DepFlag_"+j+"--->"+fieldItem.getString());
				
			}
			fieldItem = (FileItem)listFiles.get(i++);
			if(fieldItem.isFormField()&&fieldItem.getFieldName().equals("DepRepository_"+j)){
				depRepName = fieldItem.getString();
				System.out.println("["+(i-1)+"] "+"DepRepository_"+j+"--->"+fieldItem.getString());
				
			}
			fieldItem = (FileItem)listFiles.get(i++);
			if(fieldItem.isFormField()&&fieldItem.getFieldName().equals("DepName_"+j)){
				depArtName = fieldItem.getString();
				System.out.println("["+(i-1)+"] "+"DepName_"+j+"--->"+fieldItem.getString());
				
			}
			fieldItem = (FileItem)listFiles.get(i++);
			if(fieldItem.isFormField()&&fieldItem.getFieldName().equals("DepVersion_"+j)){
				depNumber = fieldItem.getString();
				System.out.println("["+(i-1)+"] "+"DepVersion_"+j+"--->"+fieldItem.getString());
				
			}
			fieldItem = (FileItem)listFiles.get(i++);
			if(fieldItem.isFormField()&&fieldItem.getFieldName().equals("DepPath_"+j)){
				dep.setPath(fieldItem.getString());
				System.out.println("["+(i-1)+"] "+"DepPath_"+j+"--->"+fieldItem.getString());
				
			}
			fieldItem = (FileItem)listFiles.get(i++);
			if(fieldItem.isFormField()&&fieldItem.getFieldName().equals("DepLocation_"+j)){
				dep.setLocation(fieldItem.getString());
				System.out.println("["+(i)+"] "+"DepLocation_"+j+"--->"+fieldItem.getString());
			}
			//buildId = buildSer.getIdByRepArt(repName, artName, Integer.parseInt(number));
			dep.setBuildId(buildId);
			
			if("Build".equals(dep.getFlag())){
				BuildService buildSer = new BuildService();
				int depBuildId = 0;
				if("head".equals(depNumber)){
					depBuildId = buildSer.getIdByRepArt(depRepName, depArtName);
				}else{
					depBuildId = buildSer.getIdByRepArt(depRepName, depArtName, Integer.parseInt(depNumber));
				}
				
				if(depBuildId>0){
					dep.setReferenceId(depBuildId);
				//	depList.add(dep);
				}
			}else if("Component".equals(dep.getFlag())){
				ComponentVersionService cVerSer = new ComponentVersionService();
				int depComponentId = 0;
			//	System.out.println("Component Dependence");
				if("head".equals(depNumber)){
					depComponentId = cVerSer.getIdByVersion(depRepName, depArtName);
				}else{
					depComponentId = cVerSer.getIdByVersion(depRepName, depArtName, depNumber);
				}
		//		System.out.println("DepComponentId"+depComponentId);
				if(depComponentId>0){
					dep.setReferenceId(depComponentId);
				}
				
			}else if("Product".equals(dep.getFlag())){
				ProductVersionService pVerSer = new ProductVersionService();
				int depProductId = 0;
				if("head".equals(depNumber)){
					depProductId = pVerSer.getIdByVersion(depRepName, depArtName);
				}else{
					depProductId = pVerSer.getIdByVersion(depRepName, depArtName,depNumber);
				}
				
				if(depProductId>0){
					dep.setReferenceId(depProductId);
				}
			}
			
			
			if(flag||!depSer.contains(dep)){
				depSer.create(dep);
			}
			else {
				depSer.update(dep);
			}
		}
		return i;
	}
	
	public int  getBuildMsg(List<?> listFiles,int i){
		BuildService buildSer = new BuildService();
		RepositoryService repSer = new RepositoryService();
        Build build = new Build();
        String repName = null ;
		String artName  = null;
		String number = null;
		String buildTime = null;
		String duration = null;
		String result = null;
		String sourcePath = null;
		String sourceVersion = null;
		String environment = null;
		String count = "0";
		
		//int count = ;
		//int buildId = 0;
		for(;i<10;i++){
			FileItem fieldItem = (FileItem)listFiles.get(i);
			if(fieldItem.isFormField()&&"RepositoryName".equals(fieldItem.getFieldName())){
				repName = fieldItem.getString();
				System.out.println("["+i+"] "+"RepositoryName-->"+repName);
			}else if(fieldItem.isFormField()&&"ArtifactName".equals(fieldItem.getFieldName())){
				artName = fieldItem.getString();
				System.out.println("["+i+"] "+"ArtifactName-->"+artName);
			}else if(fieldItem.isFormField()&&"Number".equals(fieldItem.getFieldName())){
				number = fieldItem.getString();
				System.out.println("["+i+"] "+"Number-->"+number);
			}else if(fieldItem.isFormField()&&"BuildTime".equals(fieldItem.getFieldName())){
				buildTime = fieldItem.getString();
				System.out.println("["+i+"] "+"BuildTime-->"+buildTime);
			}else if(fieldItem.isFormField()&&"Duration".equals(fieldItem.getFieldName())){
				duration = fieldItem.getString();
				System.out.println("["+i+"] "+"Duration-->"+duration);
			}else if(fieldItem.isFormField()&&"Result".equals(fieldItem.getFieldName())){
				result = fieldItem.getString();
				System.out.println("["+i+"] "+"Result-->"+result);
			}else if(fieldItem.isFormField()&&"SourcePath".equals(fieldItem.getFieldName())){
				sourcePath = fieldItem.getString();
				System.out.println("["+i+"] "+"SourcePath-->"+sourcePath);
			}else if(fieldItem.isFormField()&&"SourceVersion".equals(fieldItem.getFieldName())){
				sourceVersion = fieldItem.getString();
				System.out.println("["+i+"] "+"SourceVersion-->"+sourceVersion);
			}else if(fieldItem.isFormField()&&"Environment".equals(fieldItem.getFieldName())){
				environment = fieldItem.getString();
				System.out.println("["+i+"] "+"Environment-->"+environment);
			}else if(fieldItem.isFormField()&&"DepCount".equals(fieldItem.getFieldName())){
				count = fieldItem.getString();
				depCount = Integer.parseInt(count);
				System.out.println("["+i+"] "+"DepCount-->"+depCount);
				//System.out.println("Count:"+count);
			}
		}
		//System.out.println("["+i+"] "+"Field Name----->"+fieldItem.getString());
		
		//return null;
		
		if("1".equals(number)){
			Artifact art = new Artifact();
			art.setName(artName);
			art.setCount(Integer.parseInt(number));
			art.setStarted(Timestamp.valueOf(buildTime));
			art.setLasttime(Timestamp.valueOf(buildTime));
			Repository rep = new Repository();
			
			rep = repSer.getByName(repName);
			art.setRepId(rep.getId());
			
			ArtifactService artSer = new ArtifactService();
			if(artSer.contains(rep.getId(), artName)){
				System.out.println("");
				return -1;
			}
			artSer.create(art);
			flag = true;
		}
		//System.out.println("");
		String path = sourcePath.replace('\\', '/');
		//String logt = log.replace('\\', '/');
		//Build build = new Build();
		build.setNumber(Integer.parseInt(number));
		build.setStarted(Timestamp.valueOf(buildTime));
		build.setDuration(Long.parseLong(duration));
		build.setResult(BuildResult.valueOf(result));
		build.setSourcePath(path);
		build.setSourceVersion(sourceVersion);
		build.setEnvironment(environment);
		//build.setLog(logt);
		//RepositoryService repSer = new RepositoryService();
		Repository rep = repSer.getByName(repName);
		ArtifactService artSer = new ArtifactService();
		ArtifactList artList = artSer.getAll(rep.getId());
		System.out.println("RepositoryId:"+rep.getId());
		int artId = 0 ;
		for(Artifact art:artList)
		{
			if(art.getName().equals(artName))
			{
				artId = art.getId();
				break;
			}
		}
		System.out.println("ArtifactId:"+artId);
		build.setArtifactId(artId);
		//BuildService buildSer = new BuildService();
		
		if(buildSer.contains(artId, Integer.parseInt(number))){
			System.out.println("the build number is exist");
			return -1;
		}
		buildSer.create(build);
		
		buildId = buildSer.getIdByRepArt(repName, artName, Integer.parseInt(number));
		System.out.println("BuildId:"+buildId);
		
		return i;
	}
	
	public void addLibrary(ArrayList<String> fileNames,ArrayList<String> filePaths){
		BuildService buildSer = new BuildService();
		
		for(int i=0;i<fileNames.size();i++){
			String name = filePaths.get(i);
			
			Library lib = new Library();
			
			if(name.equals("log"))
			{
				//log = nameMap.get(name).toString();
				buildSer.updateLog(buildId, fileNames.get(i));
				System.out.println("buildId:"+buildId);
				System.out.println("log file:"+fileNames.get(i));
				continue;
			}
			
			int index = name.lastIndexOf('.');
			String type="";
			if(index>0)
				type = name.substring(index);
			System.out.println("Name:"+name);
			//String fileName = nameMap.get(name).toString();
			String fileName = fileNames.get(i);
			lib.setName(name);
			lib.setType(type);
			lib.setBuildId(buildId);
			lib.setFileName(fileName);
			LibraryService libSer = new LibraryService();
			libSer.create(lib);
		}
	}
	
	public String InsertLibrary(ArrayList<String > fileNames,int buildId,HashMap<String,String> nameMap)
	{
		
		
		//Library lib = new Library();
		BuildService buildSer = new BuildService();
		//int buildId = buildSer.getIdByRepArt(repName, artName, Integer.parseInt(num));
		String log = "";
		for(String path:fileNames)
		{
			String name = path;
			int index1 = path.lastIndexOf('/');
			if(index1!=-1){
				name = path.substring(index1+1);
			}
			if(name.equals("log"))
			{
				log = nameMap.get(name).toString();
				buildSer.updateLog(buildId, log);
				continue;
			}
			Library lib = new Library();
			int index = name.lastIndexOf('.');
			String type="";
			if(index>0)
				type = name.substring(index);
			//System.out.println("Name:"+name);
			String fileName = nameMap.get(name).toString();
			lib.setName(path);
			lib.setType(type);
			lib.setBuildId(buildId);
			lib.setFileName(fileName);
			LibraryService libSer = new LibraryService();
			libSer.create(lib);
		}
		return log;
	}
	
	public HashMap<String, String> changeName(ArrayList<String> fileNames,String strFileFolder) throws IOException
	{
		HashMap<String, String> map = new HashMap<String, String>();
		for(String name:fileNames)
		{
			String oldName = strFileFolder+"/"+name;
			///String newName = tmpName+"_"+name;
			
			GuidCreator gc = new GuidCreator();
			String guidName = gc.toString();
			String newName = strFileFolder+"/"+guidName;
			System.out.println("File--->"+guidName);
			
			File oldfile=new File(oldName);   
	        File newfile=new File(newName);
	        if(newfile.exists())//若在该目录下已经有一个文件和新文件名相同，则不允许重命名   
	        	System.out.println(newName+"is exit！");   
	        else{   
	        	oldfile.renameTo(newfile);
	        	map.put(name, guidName);
	        }
		}
		return map;
	}
}
