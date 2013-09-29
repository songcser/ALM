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
import com.prolambda.model.ConfigFile;

public class BuildManagementServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1499919562207546879L;

	private String strFileFolder;
	private String workspace;
	public void init(){
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		workspace = getServletContext().getInitParameter("workspace");
		//ServletConfig config = getServletConfig();
		///strFileFolder = config.getInitParameter("strFileFolder");
		
	}
	
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
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

	    // ��ȡ�ļ������������ÿͻ��˱���ʱָ��Ĭ���ļ���
	    //int index = path.lastIndexOf("/"); // ǰ�᣺�����path�ַ����ԡ�\����ʾĿ¼�ָ���
	    //String fileName = path.substring(index + 1);

	    // д���ļ���ǰ�������
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
			String name = file.getName();
			int index = name.lastIndexOf(".");
			if(index>0)
				name = name.substring(0,index);
			String ws = workspace + "\\" + name;
			DeleteFolder(ws);
			buildSer.deleteConfigFile(Integer.parseInt(id));
		}
	}
	
	public Boolean DeleteFolder(String sPath) {
		Boolean flag = false;  
		File file = new File(sPath);  
	    // �ж�Ŀ¼���ļ��Ƿ����  
	    if (!file.exists()) {  // �����ڷ��� false  
	        return flag;  
	    } else {  
	        // �ж��Ƿ�Ϊ�ļ�  
	        if (file.isFile()) {  // Ϊ�ļ�ʱ����ɾ���ļ�����  
	            return deleteFile(sPath) ;
	        } else {  // ΪĿ¼ʱ����ɾ��Ŀ¼����  
	            return deleteDirectory(sPath);  
	        }  
	    }  
	}
	
	public boolean deleteDirectory(String sPath) {  
	    //���sPath�����ļ��ָ�����β���Զ������ļ��ָ���  
	    if (!sPath.endsWith(File.separator)) {  
	        sPath = sPath + File.separator;  
	    }  
	    File dirFile = new File(sPath);  
	    //���dir��Ӧ���ļ������ڣ����߲���һ��Ŀ¼�����˳�  
	    if (!dirFile.exists() || !dirFile.isDirectory()) {  
	        return false;  
	    }  
	    boolean flag = true;  
	    //ɾ���ļ����µ������ļ�(������Ŀ¼)  
	    File[] files = dirFile.listFiles();  
	    for (int i = 0; i < files.length; i++) {  
	        //ɾ�����ļ�  
	        if (files[i].isFile()) {  
	            flag = deleteFile(files[i].getAbsolutePath());  
	            if (!flag) break;  
	        } //ɾ����Ŀ¼  
	        else {  
	            flag = deleteDirectory(files[i].getAbsolutePath());  
	            if (!flag) break;  
	        }  
	    }  
	    if (!flag) return false;  
	    //ɾ����ǰĿ¼  
	    if (dirFile.delete()) {  
	        return true;  
	    } else {  
	        return false;  
	    }  
	    
	    
	}
	
	public boolean deleteFile(String sPath) {  
	    boolean flag = false;  
	    File file = new File(sPath);  
	    // ·��Ϊ�ļ��Ҳ�Ϊ�������ɾ��  
	    if (file.isFile() && file.exists()) {  
	        file.delete();  
	        flag = true;  
	    }
	    return flag;  
	}

}