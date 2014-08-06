package com.prolambda.servlet;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


import com.prolambda.controller.LibraryService;
import com.prolambda.model.GuidCreator;
import com.prolambda.model.Library;


public class LibraryServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -893166095475641845L;
	private String strFileFolder;

	public void init(){
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		//ServletConfig config = getServletConfig();
		//strFileFolder = config.getInitParameter("strFileFolder");
	}
	
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		String flag = request.getParameter("flag");
		if(flag.equals("download")){
			download(request, response);
		}else if(flag.equals("downloadLibrary")){
			downloadLibrary(request,response);
		}
	}

	
	private void downloadLibrary(HttpServletRequest request,HttpServletResponse response) throws IOException  {
		String libIds = request.getParameter("libIds");
		
		GuidCreator gc = new GuidCreator();
		String zipName = gc.toString();
		FileInputStream fis = null;  
	    BufferedInputStream bis = null;  
	    //FileOutputStream fos = null;
	    BufferedOutputStream bos = null;
	    ZipOutputStream zos = null;  
		
	    ServletOutputStream out = response.getOutputStream();
	    try{
			response.setHeader("Content-disposition", "attachment;filename="+zipName+".zip");
			bos = new BufferedOutputStream(out);
					//	fos = new FileOutputStream(zipFile);
			zos = new ZipOutputStream(bos);  
		    byte[] bufs = new byte[1024];  
		    int fileSize = 0;
			LibraryService libSer = new LibraryService();
			String[] libIdList = libIds.split(",");
			for(String libId:libIdList){
				//System.out.println("libId:"+libId);
				if("".equals(libId)||"null".equals(libId)){
					continue;
				}
				
				Library lib = libSer.getById(Integer.parseInt(libId));
				
				File sourceFile = new File(strFileFolder+"/"+lib.getFileName());
				//System.out.println("file name"+lib.getName());
				//System.out.println("file path"+sourceFile.getAbsolutePath());
				if(sourceFile.exists()==false){
					System.out.println("file no exist");
					continue;

				}else{
					ZipEntry zipEntry=new ZipEntry(lib.getName());
					//System.out.println("Name:"+lib.getName());
					zos.putNextEntry(zipEntry);  
	                // 读取待压缩的文件并写进压缩包里  
	                fis = new FileInputStream(sourceFile);  
	                bis = new BufferedInputStream(fis);  
	                int read = 0;  
	                while((read=bis.read(bufs)) != -1) {  
	                	fileSize += read;
	                    zos.write(bufs, 0, read);
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
	
	

	public void download(HttpServletRequest request, HttpServletResponse response) throws IOException
	{
		String libId = request.getParameter("libId");
		
		LibraryService libSer = new LibraryService();
		Library lib = libSer.getById(Integer.parseInt(libId));
		String fileName = lib.getFileName();
		String libName = lib.getName();
		String Name = libName;
		int index = libName.indexOf('/');
		if(index!=-1){
			Name = libName.substring(index+1);
		}
		String filePath = strFileFolder+"/"+fileName;
		
		File obj = new File(filePath);
	    if (!obj.exists()) {
	      response.setContentType("text/html;charset=GBK");
	      response.getWriter().print("the file is not exist"+filePath);
	      return;
	    }

	    // 读取文件名：用于设置客户端保存时指定默认文件名
	    //int index = path.lastIndexOf("/"); // 前提：传入的path字符串以“\”表示目录分隔符
	    //String fileName = path.substring(index + 1);

	    // 写流文件到前端浏览器
	    ServletOutputStream out = response.getOutputStream();
	    response.setHeader("Content-disposition", "attachment;filename=" + Name);
	    BufferedInputStream bis = null;
	    BufferedOutputStream bos = null;
	    try {
	      bis = new BufferedInputStream(new FileInputStream(filePath));
	      bos = new BufferedOutputStream(out);
	      byte[] buff = new byte[2048];
	      int bytesRead;
	      while (-1 != (bytesRead = bis.read(buff, 0, buff.length))) {
	        bos.write(buff, 0, bytesRead);
	      }
	    } catch (IOException e) {
	      throw e;
	    } finally {
	      if (bis != null)
	        bis.close();
	      if (bos != null)
	        bos.close();
	    }
	}

}
