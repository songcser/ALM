package com.prolambda.servlet;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimerTask;

import javax.servlet.ServletContext;

import com.prolambda.controller.BuildManagementService;
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
		// TODO Auto-generated method stub
		//System.out.println("buildPath: "+buildPath);
		//System.out.println("workspace: "+workspace);
		//System.out.println("");
		//System.out.println("not run");
		if(!isRunning){
			
			isRunning = true;
			System.out.println("Running");
			
			BuildManagementService buildSer = new BuildManagementService();
			ConfigFileList fileList = buildSer.getAllConfig();
			//System.out.println("file size:"+fileList.size());
			for(ConfigFile file:fileList){
				if(file.getIsRunning()){
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
						String cmd = buildPath+" \""+ws+"\" \""+ filepath +"\"";
						
						//System.out.println("cmd: "+cmd);
						int exitValue = exeCmd(cmd);
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
				}
			}
			delAllFile(tempPath);
			
			isRunning = false;
			System.out.println("stop");
		}else{
			System.out.println("not stop");
		}
	}
	public int  exeCmd(String cmd){
		//System.out.println("building");
		Runtime run = Runtime.getRuntime();
        Process process = null;
        try {
            process = run.exec(cmd); // 执行cmd命令
            final BufferedInputStream in = new BufferedInputStream(process.getInputStream());  
            //final InputStream is1 = process.getInputStream();
            new Thread(new Runnable() {
                public void run() {
                    BufferedReader br = new BufferedReader(new InputStreamReader(in)); 
                    try {
                    	String str;
                    	while ((str = br.readLine()) != null){

                            //获得命令执行后在控制台的输出信息  
                            System.out.println("Output---> "+str);// 打印输出信息  
                             
                    	}
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
                }

				public Runnable start() {
					// TODO Auto-generated method stub
					return null;
				}
            }.start());
            //BufferedReader inBr = new BufferedReader(new InputStreamReader(in));
            String lineStr;  
           // while ((lineStr = inBr.readLine()) != null){

                //获得命令执行后在控制台的输出信息  
           //     System.out.println("Output---> "+lineStr);// 打印输出信息  
                 
          //  }
            BufferedInputStream errin = new BufferedInputStream(process.getErrorStream());
            BufferedReader errbr = new BufferedReader(new InputStreamReader(errin));
            while((lineStr = errbr.readLine())!=null){
            	System.out.println("Error--->"+lineStr);
            }
            //检查命令是否执行失败。
            /*
            while(process.exitValue()!=0&&process.exitValue()!=1){
            	System.out.println("exit value"+process.exitValue());
            }*/
            if(process.waitFor()!=0){
            	//System.out.println("exit value: "+process.exitValue());
            }
            //inBr.close();
            in.close();
            errbr.close();
            errin.close();
        } catch (Exception e) {
            System.out.println("Error executing");
        }
        //System.out.println("Notepad returned " + process.exitValue());
        
        return process.exitValue();
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
