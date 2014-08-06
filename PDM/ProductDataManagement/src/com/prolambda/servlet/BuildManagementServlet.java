package com.prolambda.servlet;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.prolambda.controller.BuildManagementService;
import com.prolambda.controller.BuildService;
import com.prolambda.model.ConfigFile;

public class BuildManagementServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1499919562207546879L;

	private String strFileFolder;
	private String workspace;
	private String tempPath;
	private String buildPath;
	private String idsList;
	public void init(){
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		workspace = getServletContext().getInitParameter("workspace");
		this.buildPath = "\""+getServletContext().getRealPath("/")+"builder"+"\\Builder.exe\"";
		this.workspace = this.workspace.replace("/", "\\");
		this.tempPath = this.workspace+"\\temp";
		File file = new File(this.tempPath);
		if(!file.exists()){
			file.mkdirs();
		}
	}
	
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
	}

	public void doPost(final HttpServletRequest request, final HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		String flag = request.getParameter("flag");
		//System.out.println("flag:"+flag);
		BuildManagementService buildSer = new BuildManagementService();
		if("run".equals(flag)){
			String idList = request.getParameter("ids");
			
			String[] ids = idList.split(",");
			for(String id:ids){
				if("".equals(id))
					continue;
				System.out.println("id:"+id);
				buildSer.updateRunning(Integer.parseInt(id), true);
			}
		}else if("stop".equals(flag)){
			String idList = request.getParameter("ids");
			
			String[] ids = idList.split(",");
			for(String id:ids){
				if("".equals(id))
					continue;
				buildSer.updateRunning(Integer.parseInt(id), false);
			}
		}else if("delete".equals(flag)){
			delete(request,response);
		}else if("download".equals(flag)){
			download(request,response);
		}else if("build".equals(flag)){
			idsList = request.getParameter("ids");
			Thread t = new Thread(new Runnable(){
				public void run(){
					
					build();
	               }
			}); 
			t.start();
		}else if("createproject".equals(flag)){
			createBuildProject(request,response);
		}
	}
	
	private void createBuildProject(HttpServletRequest request,HttpServletResponse response){
		
	}
	
	private void build(){
		//String idList = request.getParameter("ids");
		String[] ids = idsList.split(",");
		BuildManagementService buildManSer = new BuildManagementService();
		BuildService buildSer = new BuildService();
		for(String id:ids){
			if("".equals(id))
				continue;
			ConfigFile file = buildManSer.getById(Integer.parseInt(id));
			buildSer.exeCmd(buildPath, strFileFolder, tempPath, workspace, "true", file);
			/*
			String filepath =strFileFolder +"/"+ file.getFileName();
			File oldFile = new File(filepath);
			File newFile = new File(this.tempPath+"\\"+file.getName());
			//System.out.println("old File: "+oldFile.getAbsolutePath());
			//System.out.println("new File: "+newFile.getAbsolutePath());
			if(oldFile.exists()){
				try {
					fileSer.copyFile(oldFile,newFile);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				String name = file.getName();
				int index = name.lastIndexOf(".");
				if(index>0){
					name = name.substring(0,index);
				}
				String ws = workspace + "\\" + name;
				File wfile = new File(ws);
				if (!wfile.exists()) {
					wfile.mkdirs();
				}
				//oldFile.renameTo(newFile);
				filepath = newFile.getAbsolutePath();
				filepath = filepath.replace("/", "\\");
				String cmd = buildPath+" \""+ws+"\" \""+ filepath +"\" true";
				
				//System.out.println("cmd: "+cmd);
				int exitValue = buildSer.exeCmd(cmd);
				if(exitValue==0){
					SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
					Date date = new Date();
					String time = df.format(date);
					Timestamp buildtime = Timestamp.valueOf(time);
					buildManSer.updateBuildTime(file.getId(), buildtime);
					//buildSer.BuildReference(name);
				}
			}
			*/
		}
	}
	
	private void download(HttpServletRequest request,HttpServletResponse response) throws IOException {
		String id = request.getParameter("id");
		
		BuildManagementService buildSer = new BuildManagementService();
		ConfigFile file = buildSer.getById(Integer.parseInt(id));
		String fileName = file.getFileName();
		String libName = file.getName();
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

	public void delete(HttpServletRequest request,HttpServletResponse response){
		String idList = request.getParameter("ids");
		BuildManagementService buildSer = new BuildManagementService();
		String[] ids = idList.split(",");
		for(String id:ids){
			if("".equals(id))
				continue;
			ConfigFile file = buildSer.getById(Integer.parseInt(id));
			File cFile = new File(strFileFolder+"/"+file.getFileName());
			if(cFile.exists()){
				cFile.delete();
			}
			//String name = file.getName();
			//int index = name.lastIndexOf(".");
			//if(index>0)
				//name = name.substring(0,index);
			//String ws = workspace + "\\" + name;
			//DeleteFolder(ws);
			buildSer.deleteConfigFile(Integer.parseInt(id));
		}
	}
	
	public Boolean DeleteFolder(String sPath) {
		Boolean flag = false;  
		File file = new File(sPath);  
	    // 判断目录或文件是否存在  
	    if (!file.exists()) {  // 不存在返回 false  
	        return flag;  
	    } else {  
	        // 判断是否为文件  
	        if (file.isFile()) {  // 为文件时调用删除文件方法  
	            return deleteFile(sPath) ;
	        } else {  // 为目录时调用删除目录方法  
	            return deleteDirectory(sPath);  
	        }  
	    }  
	}
	
	public boolean deleteDirectory(String sPath) {  
	    //如果sPath不以文件分隔符结尾，自动添加文件分隔符  
	    if (!sPath.endsWith(File.separator)) {  
	        sPath = sPath + File.separator;  
	    }  
	    File dirFile = new File(sPath);  
	    //如果dir对应的文件不存在，或者不是一个目录，则退出  
	    if (!dirFile.exists() || !dirFile.isDirectory()) {  
	        return false;  
	    }  
	    boolean flag = true;  
	    //删除文件夹下的所有文件(包括子目录)  
	    File[] files = dirFile.listFiles();  
	    for (int i = 0; i < files.length; i++) {  
	        //删除子文件  
	        if (files[i].isFile()) {  
	            flag = deleteFile(files[i].getAbsolutePath());  
	            if (!flag) break;  
	        } //删除子目录  
	        else {  
	            flag = deleteDirectory(files[i].getAbsolutePath());  
	            if (!flag) break;  
	        }  
	    }  
	    if (!flag) return false;  
	    //删除当前目录  
	    if (dirFile.delete()) {  
	        return true;  
	    } else {  
	        return false;  
	    }  
	    
	    
	}
	
	public boolean deleteFile(String sPath) {  
	    boolean flag = false;  
	    File file = new File(sPath);  
	    // 路径为文件且不为空则进行删除  
	    if (file.isFile() && file.exists()) {  
	        file.delete();  
	        flag = true;  
	    }
	    return flag;  
	}

}
