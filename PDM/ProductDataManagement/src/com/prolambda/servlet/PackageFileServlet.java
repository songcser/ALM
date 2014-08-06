package com.prolambda.servlet;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
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

import com.prolambda.controller.LibraryService;
import com.prolambda.controller.ProductVersionService;
import com.prolambda.model.ComponentVersion;
import com.prolambda.model.ComponentVersionList;
import com.prolambda.model.GuidCreator;
import com.prolambda.model.Library;
import com.prolambda.model.LibraryList;

public class PackageFileServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 4466474242497329975L;
	private String strFileFolder;
	private String innoSetup;
	private String tempPath;
	String strRet = "";
	public void init()throws ServletException{
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		//ServletConfig config = getServletConfig();
		//strFileFolder = config.getInitParameter("strFileFolder");
		innoSetup = getServletContext().getInitParameter("innoSetup");
		File file = new File(strFileFolder);
		if (!file.exists()) {
			file.mkdirs();
		}
		
		
		super.init();
	}
	
	public void destroy() {  
		
        super.destroy(); // Just puts "destroy" string in log  
        // Put your code here  
    }  
  
    public void doGet(HttpServletRequest request, HttpServletResponse response)  
            throws ServletException, IOException {  
        doPost(request, response);  
    }  
  
    @SuppressWarnings({ "unchecked" })
	public void doPost(HttpServletRequest request, HttpServletResponse response)  
            throws ServletException, IOException {
    	
    	request.setCharacterEncoding("utf-8");  //设置编码  
        System.out.println("upload");
    	
    	
    	//ArrayList<String> issList = new ArrayList<String>();
        //获得磁盘文件条目工厂  
        DiskFileItemFactory factory = new DiskFileItemFactory();  
        //获取文件需要上传到的路径  
        //String path = request.getRealPath("/upload");  
          
        //如果没以下两行设置的话，上传大的 文件 会占用 很多内存，  
        //设置暂时存放的 存储室 , 这个存储室，可以和 最终存储文件 的目录不同  
        /** 
         * 原理 它是先存到 暂时存储室，然后在真正写到 对应目录的硬盘上，  
         * 按理来说 当上传一个文件时，其实是上传了两份，第一个是以 .tem 格式的  
         * 然后再将其真正写到 对应目录的硬盘上 
         */
        GuidCreator gc = new GuidCreator();
    	String guidPath = gc.toString();
		tempPath = strFileFolder + "/" + guidPath;
		
        File tempDir = new File(tempPath);
        if(!tempDir.exists()){
        	tempDir.mkdirs();
        }
        factory.setRepository(tempDir);  
        //设置 缓存的大小，当上传文件的容量超过该缓存时，直接放到 暂时存储室  
        factory.setSizeThreshold(1024*1024) ;  
          
        //高水平的API文件上传处理  
        ServletFileUpload upload = new ServletFileUpload(factory);  
          
        strRet = "";
        
        try {  
            //可以上传多个文件  
            List<FileItem> list = (List<FileItem>)upload.parseRequest(request);
            if(list.size()<1){
            	return;
            }
            createFolder(request,response);
            System.out.println(list.size());
            for(int i=0;i<list.size();i++)  
            {  
            	FileItem item = list.get(i);
                //获取表单的属性名字  
            	//System.out.println("i:"+i);
                String name = item.getFieldName();  
                System.out.println("name:"+name);
                //如果获取的 表单信息是普通的 文本 信息  
                if(item.isFormField())  
                {                     
                    //获取用户具体输入的字符串 ，名字起得挺好，因为表单提交过来的是 字符串类型的  
                    String value = item.getString();
                    //System.out.println("name:"+name+" value:"+value);
                    if(name.equals("checkbox")&&value.equals("no")){
                    	i+=1;
                    	continue;
                    }
                    FileItem textItem = list.get(++i);
                   // FileItem pathItem = list.get(++i);
                    if(textItem.isFormField()){
                    	String libId = textItem.getString();
                        System.out.println("libId:"+libId);
                        LibraryService libSer = new LibraryService();
                        Library lib = libSer.getById(Integer.parseInt(libId));
                        String fileName = lib.getName();
                    //    String path = pathItem.getString();
                    //    int index = fileName.lastIndexOf("/");
                    //    if(path.equals(fileName.substring(0,index))){
                   //     	continue;
                    //    }
                       // fileName = path + fileName.substring(index+1);
                    //    lib.setName(fileName);
                        File sourceFile = new File(strFileFolder+"/"+lib.getFileName());
                        File targetFile = new File(tempPath+"/"+fileName);
                       
                        if(sourceFile.exists()){
                        	
                        	copyFile(sourceFile,targetFile);
                        	packageIss(fileName);
                        	addLibrary(request,response,fileName);
                        }
                    }else{
                    	
                         /** 
                          * 以下三步，主要获取 上传文件的名字 
                          */  
                         //获取路径名  
                     	
                     	
                     	//String path = pathItem.getString();
                     	//path = path.replace('\\', '/');
                     //	System.out.println(path);
                     	
                        String itemValue = textItem.getName();
                         //System.out.println(path+"/"+value);
                         //索引到最后一个反斜杠  
                        int start = itemValue.lastIndexOf("\\");  
                         //截取 上传文件的 字符串名字，加1是 去掉反斜杠，  
                         String filename = itemValue.substring(start+1);  
                         //System.out.println("filename:"+filename);
                         //issList.add(filename);
                         //request.setAttribute(name, filename);  
                         
                         //真正写到磁盘上  
                         //它抛出的异常 用exception 捕捉  
                           
                         //item.write( new File(path,filename) );//第三方提供的  
                           
                         //手动写的  
                         File issPath = new File(tempPath);
                         if(!issPath.exists()){
                         	issPath.mkdirs();
                         }
                         File issFile = new File(tempPath,filename);
                         
                         OutputStream out = new FileOutputStream(issFile);  
                           
                         InputStream in = textItem.getInputStream() ;  
                           
                         int length = 0 ;  
                         byte [] buf = new byte[1024] ;  
                           
                        /// System.out.println("file:"+tempPath+"/"+filename);
       
                         // in.read(buf) 每次读到的数据存放在   buf 数组中  
                         while( (length = in.read(buf) ) != -1)  
                         {  
                             //在   buf 数组中 取出数据 写到 （输出流）磁盘上  
                             out.write(buf, 0, length);  
                               
                         }  
                         
                         in.close();  
                         out.flush();
                         out.close();  
                         
                         packageIss(filename);
                         addLibrary(request,response,filename);
                         
                    }
                    
                  
                }  
                //对传入的非 简单的字符串进行处理 ，比如说二进制的 图片，电影这些  
        
            }
            
    		
        } catch (FileUploadException e) {  
            //   
            e.printStackTrace();  
        }  
        catch (Exception e) {  
            //   
              
            //e.printStackTrace();  
        }  
        
        delFolder(tempPath);
       
        HttpSession session = request.getSession(true);
        PrintWriter out = response.getWriter();
        
        String versionId = (String)session.getAttribute("productVersionId");
        ProductVersionService pVerSer = new ProductVersionService();
    	LibraryService libSer = new LibraryService();
		LibraryList setupFileList = libSer.getAllByProductId(Integer.parseInt(versionId));	
		
		LibraryList libList = new LibraryList();
		for(Library tlib:setupFileList){
			int tfileId = pVerSer.getIssBySetupFile(tlib.getId());
			Library issFile = libSer.getById(tfileId);
			libList.add(issFile);
		}
		
		session.setAttribute("issFileList", libList);
		session.setAttribute("setupFileList", setupFileList);
		
		//System.out.println("strRet:"+strRet);
		out.print("<script>parent.callback('"+strRet+"')</script>");
		
    }  
    
    public void addLibrary(HttpServletRequest request,HttpServletResponse response,String filename) throws ServletException, IOException{
    	
    	System.out.println("filename:"+filename);
    	File issFile = new File(tempPath+"/"+filename);
    	HttpSession session = request.getSession(true);
    	String versionId = (String)session.getAttribute("productVersionId");
    	
    	ProductVersionService pVerSer = new ProductVersionService();
    	LibraryService libSer = new LibraryService();
    	BufferedReader reader = null;
    	
    	GuidCreator gc = new GuidCreator();
    	
    	String defaultPath = ".";
    	String sourceDir = ".";
    	String path = ".";
        String setupFile = "setup.exe";
        Boolean flag = true;
        
        File issSourceFile = new File(tempPath+"/"+filename);
        String guidName = gc.toString();
        File issTargetFile = new File(strFileFolder+"/"+guidName);
        
        
        
    	try {
            //System.out.println("以行为单位读取文件内容，一次读一整行：");
            reader = new BufferedReader(new FileReader(issFile));
            String tempString = null;
           
            // 一次读入一行，直到读入null为文件结束
            while ((tempString = reader.readLine()) != null) {
                // 显示行号
               int index = tempString.indexOf("OutputDir");
               if(index!=-1){
            	  index = tempString.indexOf("=");
            	  if(index!=-1){
            		  path = tempString.substring(index+1).trim();
            	  }
               }else{
            	   index = tempString.indexOf("OutputBaseFilename");
                   if(index!=-1){
                	   index = tempString.indexOf("=");
                	   if(index!=-1){
                		   setupFile = tempString.substring(index+1).trim()+".exe";
                	   }
                   }else{
                	   index = tempString.indexOf("SourceDir");
                	   if(index!=-1){
                		   index = tempString.indexOf("=");
                		   if(index!=-1){
                			   sourceDir = tempString.substring(index+1).trim();
                		   }
                	   }
                	   /*
                	   else {
                		   index = tempString.indexOf("DefaultGroupName");
                		   if(index!=-1){
                			   index = tempString.indexOf("=");
                			   if(index!=-1){
                				   defaultPath = tempString.substring(index+1).trim();
                			   }
                		   }
                	   }
                	   */
                   }
               }
               
            }
            //System.out.println("path:"+path);
            
            if(path!=null){
            	String sourcePath = "";
            	int index = path.indexOf(":");
            	if(index!=-1){
            		sourcePath = path;
            	}else {
            		sourcePath = tempPath + "/" /*+defaultPath + "/"*/ + sourceDir + "/" +path + "/" + setupFile;
            	}
            	System.out.println("DefaultPath:"+defaultPath);
            	System.out.println("SourceDir:"+sourceDir);
            	System.out.println("Path:"+path);
            	System.out.println("SetupFile:"+setupFile);
            	System.out.println("Path:"+sourcePath);
            	//System.out.println(path+"/"+setupFile);
            	File sourceFile = new File(sourcePath);
            	gc = new GuidCreator();
            	String setupGuidName = gc.toString();
            	//System.out.println(guidName);
            	File targetFile = new File(strFileFolder+"/"+setupGuidName);
            	if(sourceFile.exists())
            		copyFile(sourceFile,targetFile);
            	else {
            		System.out.println("Create setup file error");
            		return;
            	}
            	
            	Library ilib = new Library();
            	
                int libId = 0;
                
            	index = filename.lastIndexOf('.');
        		String type = filename.substring(index);
        		//path = fullPath + path;
        		//System.out.println("issName:"+filename);
        		ilib.setName(filename);
        		ilib.setType(type);
        		//ilib.setProductId(Integer.parseInt(versionId));
        		ilib.setFileName(guidName);
               // System.out.println("guidName:"+guidName);
                copyFile(issSourceFile,issTargetFile);
               // System.out.println("issSourceFile:"+issSourceFile.getName());
                LibraryList libList = (LibraryList)session.getAttribute("issFileList");
              //  System.out.println("libList:"+libList);
        		for(Library tlib:libList){
        			if(tlib.getName().equals(filename)){
        				//tlib.setId(lib.getId());
        				libId = tlib.getId();
        				ilib.setId(libId);
        				libSer.update(ilib);
        				//System.out.println("oldFile: "+tlib.getFileName());
        				File oldFile = new File(strFileFolder+"/"+tlib.getFileName());
        				if(oldFile.exists()){
        					oldFile.delete();
        				}
        				flag = false;
        			}
        		}
        		if(flag){
        			System.out.println("create issFile");
        			libSer.create(ilib);
        			libId = libSer.getIdByFileName(guidName);
        		}
            	
            	Library lib = new Library();
            	
            	
            	//index = setupFile.lastIndexOf('.');
				//type = setupFile.substring(index);
				//path = fullPath + path;
            	String setupName = filename.substring(0, index+1)+"exe";
				lib.setName(setupName);
				lib.setType(".exe");
				lib.setProductId(Integer.parseInt(versionId));
				lib.setFileName(setupGuidName);
				//libSer.create(lib);
				//System.out.println("issFileId:"+libId);
				if(pVerSer.containsIss(libId)){
					int fileId = pVerSer.getFileByIss(libId);
					//System.out.println("libId:"+libId+" fileId:"+fileId);
					if(fileId!=-1){
						Library oldLib = libSer.getById(fileId);
						File oldFile = new File(strFileFolder+"/"+oldLib.getFileName());
						if(oldFile.exists()){
							oldFile.delete();
						}
						lib.setId(fileId);
						libSer.update(lib);
						strRet += "<a href=\"LibraryServlet?flag=download&libId="+libId+"\">"+filename+"</a>" +
								"<a href=\"LibraryServlet?flag=download&libId="+fileId+"\">"+setupName+"</a>";
					}else {
						//System.out.println("create setupFile:");
						libSer.create(lib);
						fileId = libSer.getIdByFileName(setupGuidName);
						//System.out.println("libId:"+libId+" fileId:"+fileId);
						pVerSer.addIssFile(Integer.parseInt(versionId),libId, fileId);
						strRet += "<a href=\"LibraryServlet?flag=download&libId="+libId+"\">"+filename+"</a>" +
								"<a href=\"LibraryServlet?flag=download&libId="+fileId+"\">"+setupName+"</a>";
					}
				}else{
					System.out.println("create setupFile:");
					libSer.create(lib);
					int fileId = libSer.getIdByFileName(setupGuidName);
					//System.out.println("libId:"+libId+" fileId:"+fileId);
					pVerSer.addIssFile(Integer.parseInt(versionId),libId, fileId);
					strRet += "<a href=\"LibraryServlet?flag=download&libId="+libId+"\">"+filename+"</a>" +
							"<a href=\"LibraryServlet?flag=download&libId="+fileId+"\">"+setupName+"</a>";
				}
            }
            
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e1) {
                }
            }
        }
        
        
        
		
    }
    
    public void packageIss(String filename) throws IOException{
    	
    	Runtime runtime = Runtime.getRuntime();
    	
    	Process process = runtime.exec(innoSetup+" /cc \""+tempPath+"/"+filename+"\"");
 		
 		try {
 			
 			process.waitFor();
 			if(process.exitValue()!=0){
 				System.out.print("failed");
 			}
 			
 		} catch (InterruptedException e) {
 			// 
 			e.printStackTrace();
 		}
 		
    }

    public void delFolder(String folderPath) {
        try {
        	File myFilePath = new File(folderPath);
        	if(myFilePath.exists()){
        		delAllFile(folderPath); //删除完里面所有内容
              
                myFilePath.delete(); //删除空文件夹
        	}
           
        } catch (Exception e) {
        	e.printStackTrace(); 
        }
    }
    
    public boolean delAllFile(String path) {
        boolean flag = false;
        File file = new File(path);
        if (!file.exists()) {
          return flag;
        }
        if (!file.isDirectory()) {
          return flag;
        }
        String[] tempList = file.list();
        File temp = null;
        for (int i = 0; i < tempList.length; i++) {
           if (path.endsWith(File.separator)) {
              temp = new File(path + tempList[i]);
           } else {
               temp = new File(path + File.separator + tempList[i]);
           }
           if (temp.isFile()) {
              temp.delete();
           }
           if (temp.isDirectory()) {
              delAllFile(path + "/" + tempList[i]);//先删除文件夹里面的文件
              delFolder(path + "/" + tempList[i]);//再删除空文件夹
              flag = true;
           }
        }
        return flag;
      }
    public void createFolder(HttpServletRequest request, HttpServletResponse response) throws IOException {
    	HttpSession session = request.getSession(true);
		
    	
		
		String versionId = (String)session.getAttribute("productVersionId");
		
		
		ProductVersionService versionSer = new ProductVersionService();
		ComponentVersionList versionList = versionSer.getComponents(Integer.parseInt(versionId));
		
		for(ComponentVersion comVersion:versionList){
			String location = versionSer.getComponentLocation(Integer.parseInt(versionId), comVersion.getId());
			//Component com = comSer.getById(comVersion.getComponentId());
			//ComponentCategory cCategory = cCatSer.getById(com.getCategoryId());
			//strRet += cCategory.getName()+","+com.getName()+","+comVersion.getVersion()+",";
			findFile(comVersion.getId(),location);
			//strRet += "|";
		}
    }
    
    private void findFile(int id,String location) throws IOException{
    	LibraryService libSer = new LibraryService();
    	LibraryList libList = libSer.getAllByComponentId(id);
		for(Library lib:libList){
			String name = lib.getName();
			int index = name.lastIndexOf('/');
			String path = name;
			String fileName = name;
			//System.out.println("name:"+name);
			File file = null;
			if(index!=-1){
				path = location + "/" +name.substring(0,index);
				
				fileName = name.substring(index+1);
				file = new File(tempPath+"/"+path);
				if (!file.exists()) {
					file.mkdirs();
				}
			}else{
				
				file = new File(tempPath+"/"+location);
				
				if (!file.exists()) {
					file.mkdirs();
				}
			}
			
			
			File sourceFile = new File(strFileFolder+"/"+lib.getFileName());
			File targetFile = new File(file.getAbsolutePath()+"/"+fileName);
			if(sourceFile.exists()){
				copyFile(sourceFile,targetFile);
			}
			
			//strRet += lib.getName()+",";
		}
    }
    public void copyFile(File sourceFile, File targetFile) throws IOException {
        BufferedInputStream inBuff = null;
        BufferedOutputStream outBuff = null;
        try {
            // 新建文件输入流并对它进行缓冲
            inBuff = new BufferedInputStream(new FileInputStream(sourceFile));

            // 新建文件输出流并对它进行缓冲
            outBuff = new BufferedOutputStream(new FileOutputStream(targetFile));

            // 缓冲数组
            byte[] b = new byte[1024 * 10];
            int len;
            while ((len = inBuff.read(b)) != -1) {
                outBuff.write(b, 0, len);
            }
            // 刷新此缓冲的输出流
            outBuff.flush();
        } finally {
            // 关闭流
            if (inBuff != null)
                inBuff.close();
            if (outBuff != null)
                outBuff.close();
        }
    }
}
