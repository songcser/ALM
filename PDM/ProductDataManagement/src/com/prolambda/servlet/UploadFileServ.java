package com.prolambda.servlet;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.RandomAccessFile;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

import com.prolambda.controller.*;
import com.prolambda.model.*;


public class UploadFileServ extends HttpServlet {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 2150320198982896631L;
	private String strFileFolder;
	private String fullPath;
	private String flag = "";
	private String strRet ;
	public void init(){
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		//ServletConfig config = getServletConfig();
		///strFileFolder = config.getInitParameter("strFileFolder");
		File file = new File(strFileFolder);
		if (!file.exists()) {
			file.mkdirs();
		}
	}
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)  {
		doPost(req, resp);
	}


	protected void doPost(HttpServletRequest req, HttpServletResponse resp) {
		try {
			//strFileFolder = "E:\\TempFolder";
			resp.setContentType("text/html");  
			PrintWriter out = resp.getWriter(); 
			strRet = "";
			System.out.println("Upload");
			final long MAX_SIZE = 10 * 1024 * 1024;// 设置上传文件最大为 10M  
			
			DiskFileItemFactory dfif = new DiskFileItemFactory();  
			dfif.setSizeThreshold(4096);// 设置上传文件时用于临时存放文件的内存大小,这里是4K.多于的部分将临时存在硬盘  
			
		    dfif.setRepository(new File(strFileFolder));
			///设置可上传文件的最大尺寸
		    ServletFileUpload sfu = new ServletFileUpload(dfif);  
	        // 设置最大上传尺寸  
	        sfu.setSizeMax(MAX_SIZE);  
	        
	        List<?> listFiles = null;  
	        try {  
	        	listFiles = sfu.parseRequest(req);  
	        } catch (FileUploadException e) {// 处理文件尺寸过大异常  
	           
	            e.printStackTrace();  
	        }  
			
			//String field = req.getParameter("field");
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
			
			String arg1 = null;
			String arg2 = null;
			String arg3 = null;
			
	        if (listFiles == null || listFiles.size() == 0) {  
	        	out.print("<script language='javascript'>alert('please select file upload');</script>");
	            
	            //out.println("<a href=\"upload.html\" target=\"_top\">返回</a>");    
	        }
	        System.out.println("list size:"+listFiles.size());
			if (null != listFiles && listFiles.size()>0) {
				for (int i = 0; i <listFiles.size(); i++) {
					FileItem fileItem = (FileItem)listFiles.get(i);
					if(fileItem.isFormField()||fileItem==null)
					{
						
						if(!fileItem.getFieldName().equals("")&&fileItem.getFieldName()!=null){
							fullPath = fileItem.getString();
							if(i==0)
							{
								String fl = fileItem.getFieldName();
								if("flag".equals(fl)){
									flag = fileItem.getString();
									FileItem argItem1 = (FileItem)listFiles.get(++i);
									if("arg1".equals(argItem1.getFieldName())){
										arg1 = argItem1.getString();
									}
									FileItem argItem2 = (FileItem)listFiles.get(++i);
									if("arg2".equals(argItem2.getFieldName())){
										arg2 = argItem2.getString();
									}
									FileItem argItem3 = (FileItem)listFiles.get(++i);
									if("arg3".equals(argItem3.getFieldName())){
										arg3 = argItem3.getString();
									}
									//System.out.println("["+i+"] "+"Field Name---->"+fileItem.getFieldName());
									//System.out.println("["+i+"] "+"Item Name---->"+fileItem.getString());
								}else{
									flag = fileItem.getFieldName();
								}
								//flag = fileItem.getFieldName();
							}
							
							System.out.println("Category: "+arg1);
							System.out.println("Component: "+arg2);
							System.out.println("Version: "+arg3);
						}
						
						continue; 
						//repName = fileItem.getFieldName();
						//artName = fileItem.getString();
					} 
					if (null!= fileItem.getName()) {
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
						
						File saveFile = new File(strFileFolder,fileName);
						fileNames.add(fileName);
						filePaths.add(filePath);
						fileItem.write(saveFile);
					}
				}
			}
			
			String retStr = getInfo(fileNames,strFileFolder);
			
			HashMap<String, String> nameMap = changeName(fileNames,strFileFolder);
			//System.out.println("Map:"+nameMap);
			if(!"".equals(retStr)&&flag==null){
				int repInt = retStr.indexOf('_');
				String repName = retStr.substring(0, repInt);
				int artInt = retStr.indexOf('_', repInt+1);
				String artName = retStr.substring(repInt+1, artInt);
				String num = retStr.substring(artInt+1);
				System.out.println(repName+"----"+artName+"----"+num);
				retStr += InsertLibrary(filePaths,repName,artName,num,nameMap);
				out.write("UpLoad File You are success!"+ retStr);
			}else if(!"".equals(flag)&&"build".equals(flag)){
				retStr += InsertLibrary(filePaths,arg1,arg2,arg3,nameMap);
			}else if(!"".equals(flag)&&"component".equals(flag)&&arg1!=null&&arg2!=null&&arg3!=null){
				InsertComponentLibrary(filePaths,arg1,arg2,arg3,nameMap);
			}else if(!"".equals(flag)&&"component".equals(flag)||"product".equals(flag)){
				InsertLibrary(req,resp,filePaths,nameMap);
				out.print("<script>parent.callback('"+strRet+"')</script>");
			}else if(!"".equals(flag)&&"buildManagement".equals(flag)){
				addConfigFile(filePaths,nameMap);
				out.print("<script>parent.callback('"+strRet+"')</script>");
			}
			
			
			out.flush();
			out.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void addConfigFile(ArrayList<String > filepaths,HashMap<String,String> nameMap){
		//System.out.println("add Config File");
		BuildManagementService buildSer = new BuildManagementService();
		ConfigFileList fileList = buildSer.getAllConfig();
		Boolean isExist = false;
		for(String path:filepaths){
			for(ConfigFile file:fileList){
				if(path.equals(file.getName())){
					isExist = true;
				}
			}
			if(isExist){
				continue;
			}
			ConfigFile file = new ConfigFile();
			String filename = nameMap.get(path).toString();
			file.setName(path);
			file.setIsRunning(false);
			file.setFileName(filename);
			
			buildSer.addConfig(file);
			
			int id = buildSer.getIdByFileName(filename);
			
			strRet += id+","+path+"|";
		}
	}
	
	public String getInfo(ArrayList<String> fileNames,String strFileFolder) throws IOException{
		String retStr="";
		
		for(String name:fileNames)
		{
			if(name.equals("log"))
			{
				RandomAccessFile raf = new RandomAccessFile(strFileFolder+"/"+name, "r");  
				long len = raf.length();  
				if (len != 0L) {  
					long pos = len - 1;  
					while (pos > 0) {   
						pos--;  
						raf.seek(pos);  
						if (raf.readByte() == '\n') {  
							retStr = raf.readLine();
							break;
						}  
					}  
				}  
				raf.close(); 
			}
		}
		System.out.println("Log info--->"+retStr);
		return retStr;
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
			System.out.println("File Name:"+name);
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
	
	public void InsertLibrary(HttpServletRequest request,HttpServletResponse response,ArrayList<String> fileNames,HashMap<String,String> nameMap) throws ServletException, IOException{
		HttpSession session = request.getSession(true);
		String versionId = "";
		if("component".equals(flag)){
			versionId = (String)session.getAttribute("versionId");
		}else if("product".equals(flag)){
			versionId = (String)session.getAttribute("productVersionId");
		}
		LibraryService libSer = new LibraryService();
		System.out.println("fileName:"+fileNames.size());
		for(String path:fileNames)
		{
			String name = path;
			int index1 = path.lastIndexOf('/');
			if(index1!=-1){
				name = path.substring(index1+1);
			}
			String fileName = nameMap.get(name).toString();
			
			Library lib = new Library();
			int index = name.lastIndexOf('.');
			String type = name.substring(index);
			path = fullPath + path;
			lib.setName(path);
			lib.setType(type);
			if("component".equals(flag)){
				lib.setComponentId(Integer.parseInt(versionId));
			}else if("product".equals(flag)){
				lib.setProductId(Integer.parseInt(versionId));
			}
			
			lib.setFileName(fileName);
			
			LibraryList libList = new LibraryList();
			if("component".equals(flag)){
				libList = libSer.getAllByComponentId(Integer.parseInt(versionId));
			}else if("product".equals(flag)){
				libList = libSer.getAllByProductId(Integer.parseInt(versionId));
			}
					
			Boolean flag = true;
			for(Library libt:libList){
				if(libt.getName().equals(path)){
					strRet += libt.getId()+","+name+"|";
					File file = new File(strFileFolder+"/"+fileName);
					if(file.exists())
						file.delete();
					lib.setId(libt.getId());
					libSer.update(lib);
					
					flag = false;
					break;
				}
			}
			if(flag){

				libSer.create(lib);
				
				int libId = libSer.getIdByFileName(fileName);
				
				strRet += libId +","+name+"|";
			}
			
		}
		
		
		LibraryList libList = libSer.getAllByComponentId(Integer.parseInt(versionId));
		session.setAttribute("componentLibraryList", libList);
		
		//request.getRequestDispatcher("componentLibraryPage.jsp").forward(request, response);
	}
	
	public String InsertComponentLibrary(ArrayList<String > fileNames,String category, String component,String version,HashMap<String,String> nameMap){
		
		System.out.println("Import Component:");
		ComponentVersionService cVerSer = new ComponentVersionService();
		ComponentService cSer = new ComponentService();
		ComponentCategoryService cCateSer = new ComponentCategoryService();
		if(!cCateSer.contains(category)){
			ComponentCategory cate = new ComponentCategory();
			System.out.println("Create Category:");
			
			SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			Date date = new Date();
			String time = df.format(date);
			Timestamp created = Timestamp.valueOf(time);
			Timestamp modified = Timestamp.valueOf(time);
			
			cate.setName(category);
			cate.setDescription("Create "+category+"  "+time);
			cate.setComponentCount(0);
			cate.setCreated(created);
			cate.setModified(modified);
			
			cCateSer.create(cate);
			
		}
		if(!cSer.contains(category, component)){
			Component com = new Component();
			System.out.println("Create Component");
			int categoryId = cCateSer.getByName(category).getId();
			
			SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			Date date = new Date();
			String time = df.format(date);
			Timestamp created = Timestamp.valueOf(time);
			Timestamp modified = Timestamp.valueOf(time);
			com.setName(component);
			com.setDescription("Create "+component+"  "+time);
			com.setCreated(created);
			com.setModified(modified);
			com.setLastVersion("0.0");
			com.setCategoryId(categoryId);
			
			cSer.create(com);
		}
		if(!cVerSer.contains(category, component, version)&&!"head".equals(version)){
			ComponentVersion cVersion = new ComponentVersion();
			System.out.println("Create Version");
			int componentId = cSer.getIdByName(category, component);
			//String version = request.getParameter("version");
			//String description = request.getParameter("description");
			SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			Date date = new Date();
			String time = df.format(date);
			Timestamp created = Timestamp.valueOf(time);
			//Timestamp modified = Timestamp.valueOf(time);
			
			cVersion.setVersion(version);
			cVersion.setDescription("Create Version:"+version+"   "+time);
			cVersion.setCreated(created);
			cVersion.setComponentId(componentId);
			
			cVerSer.create(cVersion);
		}
		
		int versionId = 0;
		if("head".equals(version)){
			versionId = cVerSer.getIdByVersion(category, component);
		}else{
			versionId = cVerSer.getIdByVersion(category, component, version);
		}
		
		String log = "";
		for(String path:fileNames)
		{
			String name = path;
			int index1 = path.lastIndexOf('/');
			if(index1!=-1){
				name = path.substring(index1+1);
			}

			Library lib = new Library();
			int index = name.lastIndexOf('.');
			String type="";
			if(index>0)
				type = name.substring(index);
			System.out.println("Name:"+name);
			String fileName = nameMap.get(name).toString();
			lib.setName(path);
			lib.setType(type);
			//lib.setBuildId(buildId);
			lib.setComponentId(versionId);
			lib.setFileName(fileName);
			LibraryService libSer = new LibraryService();
			libSer.create(lib);
		}
		return log;
	}
	
	public String InsertLibrary(ArrayList<String > fileNames,String repName,String artName,String num,HashMap<String,String> nameMap)
	{
		
		
		//Library lib = new Library();
		BuildService buildSer = new BuildService();
		int buildId = buildSer.getIdByRepArt(repName, artName, Integer.parseInt(num));
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
	
}
