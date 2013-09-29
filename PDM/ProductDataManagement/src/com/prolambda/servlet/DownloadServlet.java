package com.prolambda.servlet;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.regex.Pattern;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.prolambda.controller.BuildService;
import com.prolambda.controller.ComponentVersionService;
import com.prolambda.controller.LibraryService;
import com.prolambda.controller.ProductVersionService;
import com.prolambda.model.GuidCreator;
import com.prolambda.model.Library;
import com.prolambda.model.LibraryList;

public class DownloadServlet extends HttpServlet {

	
	/**
	 * 
	 */
	private static final long serialVersionUID = 764821175766939822L;
	private String strFileFolder;

	public void init(){
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		//ServletConfig config = getServletConfig();
		//strFileFolder = config.getInitParameter("strFileFolder");
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

		doPost(request,response);
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
		String flag = request.getParameter("Flag");
		String repository = request.getParameter("Repository");
		String name = request.getParameter("Name");
		String version = request.getParameter("Version");
		String path = request.getParameter("Path");
		System.out.println("flag-->"+flag);
		System.out.println("repository-->"+repository);
		System.out.println("name-->"+name);
		System.out.println("version-->"+version);
		System.out.println("path-->"+path);
		int id = 0;
		LibraryService libSer = new LibraryService();
		if("Build".equals(flag)){
			BuildService buildSer = new BuildService();
			
			if("head".equals(version)){
				
				id = buildSer.getIdByRepArt(repository, name);
				
			}else{
				id = buildSer.getIdByRepArt(repository, name, Integer.parseInt(version));
				
			}
			if(id>0){
				
				LibraryList libList = libSer.getAllByBuildId(id);
				libList = filterLibList(libList,path);
				if(libList.size()<=0){
					return;
				}
				download(libList,response);
			}
			
		}else if("Component".equals(flag)){
			ComponentVersionService cVerSer = new ComponentVersionService();
			
			if("head".equals(version)){
				id = cVerSer.getIdByVersion(repository, name);
			}else{
				id = cVerSer.getIdByVersion(repository, name, version);
			}
			if(id>0){
				LibraryList libList = libSer.getAllByComponentId(id);
				libList = filterLibList(libList,path);
				if(libList.size()<=0){
					return;
				}
				download(libList,response);
			}
		}else if("Product".equals(flag)){
			ProductVersionService pVerSer = new ProductVersionService();
			
			if("head".equals(version)){
				id = pVerSer.getIdByVersion(repository, name);
			}else {
				id = pVerSer.getIdByVersion(repository, name, version);
			}
			if(id>0){
				LibraryList libList = libSer.getAllByProductId(id);
				
				libList = filterLibList(libList,path);
				if(libList.size()<=0){
					return;
				}
				download(libList,response);
			}
		}else{
			System.out.println("your flag is wrong");
			response.setHeader("Content-disposition", "attachment; you input error");
			PrintWriter out = response.getWriter();
			//ServletOutputStream out = response.getOutputStream();
			out.println("you input error");
			out.flush();
			out.close();
			//BufferedOutputStream bos = new BufferedOutputStream(out);
			//
		}
	}
	
	public LibraryList filterLibList(LibraryList libList,String paths){
		
		LibraryList list = new LibraryList();
		
		String[] dir = paths.split(";");
		
		for(int i=0;i<libList.size();i++){
			Library lib = libList.get(i);
			for(String path:dir){
				if(!"".equals(path)&&wildMatch(path,lib.getName())){
					list.add(lib);
				}
			}
		}
    	
    	return list;
	}
	
	private boolean wildMatch(String pattern, String str) {
		int index = pattern.indexOf("*");
		if(index!=-1){
			pattern = toJavaPattern(pattern);
			return Pattern.matches(pattern, str);
		}else{
			index = str.indexOf(pattern);
			if(index==0)
				return true;
			else 
				return false;
		}
        
        
    }
	private static String toJavaPattern(String pattern) {
      
		String path = pattern;
		path = path.replace('.', '#');   
		path = path.replaceAll("#", "\\\\.");   
		path = path.replace('*', '#');   
		path = path.replaceAll("#", ".*");   
		path = path.replace('?', '#');   
		path = path.replaceAll("#", ".?");   
		path = "^" + path + "$";
	
        return path;
    }
	
	public void download(LibraryList libList,HttpServletResponse response) throws IOException{
		GuidCreator gc = new GuidCreator();
		String zipName = gc.toString();
		FileInputStream fis = null;  
	    BufferedInputStream bis = null;  
	    //FileOutputStream fos = null;
	    BufferedOutputStream bos = null;
	    ZipOutputStream zos = null;  
	    
	    ServletOutputStream out = response.getOutputStream();
	    try{
	    	
	    	//System.out.println("pre:"+preStr);
	    	//System.out.println("end:"+endStr);
			response.setHeader("Content-disposition", "attachment;filename="+zipName+".zip");
			bos = new BufferedOutputStream(out);
					//	fos = new FileOutputStream(zipFile);
			zos = new ZipOutputStream(bos);  
		    byte[] bufs = new byte[1024];  
		    int fileSize = 0;
			
			for(Library lib:libList){
				String name = lib.getName();
				//index = name.indexOf(path);
				//if(index!=0){
				//	continue;
				//}
				//System.out.println("action");
				
				
				//Library lib = libSer.getById(Integer.parseInt(libId));
				
				File sourceFile = new File(strFileFolder+"/"+lib.getFileName());
				
				if(sourceFile.exists()==false){
					 System.out.println("file isn't exist");
					 continue;
					/*try {  
		                    if(null != bos) bos.close();  
		                    if(null != zos) zos.close();  
		                } catch (IOException e) {  
		                    e.printStackTrace();  
		                    throw new RuntimeException(e);  
		                }*/
					 //return;
					 //out.println(">>>>>> 待压缩的文件目录：" + lib.getFileName() + " 不存在. <<<<<<");
				}else{
					System.out.println("file name: "+name);
					System.out.println("file Path: "+sourceFile.getAbsolutePath());
					ZipEntry zipEntry=new ZipEntry(lib.getName());
					zos.putNextEntry(zipEntry); 
					//System.out.println("Zip File:"+zipEntry.getSize());
	                // 读取待压缩的文件并写进压缩包里  
	                fis = new FileInputStream(sourceFile);  
	                bis = new BufferedInputStream(fis);  
	                int read = 0;  
	                while((read=bis.read(bufs)) != -1) {  
	                	
	                    zos.write(bufs, 0, read);
	                    fileSize += read;
	                    zos.flush();
	                }  
				}
			}
		
			System.out.println("fileSize:"+fileSize);
			response.setContentLength(fileSize);
			bos.flush();
			out.flush();
			
	    }catch (FileNotFoundException e) {
	    	e.printStackTrace();
	    } catch (IOException e) {  
	    	e.printStackTrace();  
	    	throw new RuntimeException(e);  
	    } finally {  
        // 关闭流  
	    	try {  
	    		if(null != fis){
	    			fis.close();
	    		}
	    		if(null != bis){
	    			bis.close();
	    		}
	    		if(null != zos){
	    			
	    			zos.close();  
	    		}
	    		if(null != bos) {
	    			
	    			bos.close();  
	    		}
	    		if(null != out){
	    			out.close();
	    		}
	    	} catch (IOException e) {  
	    		e.printStackTrace();  
	    		throw new RuntimeException(e);  
	    	}
	    }
	}

}
