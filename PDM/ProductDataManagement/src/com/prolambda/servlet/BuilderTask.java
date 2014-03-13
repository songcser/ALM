package com.prolambda.servlet;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimerTask;

import javax.servlet.ServletContext;

import com.prolambda.controller.BuildManagementService;
import com.prolambda.controller.BuildService;
import com.prolambda.controller.FileService;
import com.prolambda.model.ConfigFile;
import com.prolambda.model.ConfigFileList;

public class BuilderTask  extends TimerTask{

	private static boolean isRunning = false;
	private ServletContext context = null; 
	//private String path;
	private String strFileFolder;
	private String buildPath;
	private String workspace;
	private String tempPath;
	//String str = context.getInitParameter("strFileFolder");
	public BuilderTask(ServletContext context){
		this.context = context;
		this.strFileFolder = this.context.getInitParameter("strFileFolder");
		this.buildPath = "\""+context.getRealPath("/")+"builder"+"\\Builder.exe\"";
		this.workspace = context.getInitParameter("workspace");
		this.workspace = this.workspace.replace("/", "\\");
		this.tempPath = this.workspace+"\\temp";
		File file = new File(this.tempPath);
		if(!file.exists()){
			file.mkdirs();
		}
		//this.buildPath = this.buildPath.replace("\\", "/");
		System.out.println("start");
	}
	
	public BuilderTask(ServletContext context,String path){
		
	}
	@Override
	public void run() {
		
		if(!isRunning){
			
			isRunning = true;
			System.out.println("Running");
			//FileService fileSer = new FileService();
			BuildService buildService = new BuildService();
			BuildManagementService buildSer = new BuildManagementService();
			ConfigFileList fileList = buildSer.getAllConfig();
			//System.out.println("file size:"+fileList.size());
			for(ConfigFile file:fileList){
				if(file.getIsRunning()){
					buildService.exeCmd(buildPath, strFileFolder, tempPath, workspace, "false", file);
					/*
					String filepath =strFileFolder +"/"+ file.getFileName();
					File oldFile = new File(filepath);
					File newFile = new File(this.tempPath+"\\"+file.getName());
					//System.out.println("old File: "+oldFile.getAbsolutePath());
					//System.out.println("new File: "+newFile.getAbsolutePath());
					if(oldFile.exists()){
						try {
							copyFile(oldFile,newFile);
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
						String cmd = buildPath+" \""+ws+"\" \""+ filepath +"\" false";
						
						//System.out.println("cmd: "+cmd);
						int exitValue = buildService.exeCmd(cmd);
						if(exitValue==0){
							SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
							Date date = new Date();
							String time = df.format(date);
							Timestamp buildtime = Timestamp.valueOf(time);
							buildSer.updateBuildTime(file.getId(), buildtime);
						}
						//System.out.println("finish");
						//newFile.renameTo(oldFile);
					}
					*/
				}
			}
			delAllFile(tempPath);
			
			isRunning = false;
			System.out.println("stop");
		}else{
			System.out.println("not stop");
		}
	}

	public  void copyFile(File sourceFile, File targetFile) throws IOException {
		//System.out.println("copy file");
        BufferedInputStream inBuff = null;
        BufferedOutputStream outBuff = null;
        try {
            // 新建文件输入流并对它进行缓冲
            inBuff = new BufferedInputStream(new FileInputStream(sourceFile));

            // 新建文件输出流并对它进行缓冲
            outBuff = new BufferedOutputStream(new FileOutputStream(targetFile));

            // 缓冲数组
            byte[] b = new byte[1024 * 5];
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
	
	public boolean delAllFile(String path) {
		//System.out.println("delete path:"+path);
        boolean flag = false;
        File file = new File(path);
        if (!file.exists()) {
          return flag;
        }
        if (!file.isDirectory()) {
          return flag;
        }
        String[] tempList = file.list();
        //File temp = null;
        //System.out.println("delete size:"+tempList.length);
        for (int i = 0; i < tempList.length; i++) {
        	File files = new File(path +"\\"+tempList[i]);
        	//System.out.println("file path:	"+tempList[i]);
        	files.delete();
        }
        
        //file.delete();
        return true;
      }
}
