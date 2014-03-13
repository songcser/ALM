package com.prolambda.controller;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

import com.prolambda.dal.BuildDAL;
import com.prolambda.model.Artifact;
import com.prolambda.model.ArtifactList;
import com.prolambda.model.Build;
import com.prolambda.model.BuildList;
import com.prolambda.model.ConfigFile;
import com.prolambda.model.Dependence;
import com.prolambda.model.DependenceList;
import com.prolambda.model.Repository;

public class BuildService {

	public Boolean create(Build build)
	{
		BuildDAL buildDAL = new BuildDAL();
		return buildDAL.create(build);
	}
	
	public Boolean delete(int id)
	{
		BuildDAL buildDAL = new BuildDAL();
		return buildDAL.delete(id);
	}
	
	public Boolean deleteByArtId(int artId){
		BuildDAL buildDAL = new BuildDAL();
		return buildDAL.deleteByArtId(artId);
	}
	
	public Boolean update(Build build)
	{
		BuildDAL buildDAL = new BuildDAL();
		return buildDAL.update(build);
	}
	
	public Boolean updateLog(int id,String log)
	{
		BuildDAL buildDAL = new BuildDAL();
		return buildDAL.updateLog(id,log);
	}
	
	public BuildList getAll(int ArtifactId)
	{
		BuildDAL buildDAL = new BuildDAL();
		
		return buildDAL.getAll(ArtifactId);
	}
	
	public Build getById(int id)
	{
		BuildDAL buildDAL = new BuildDAL();
		return buildDAL.getById(id);
	}
	/*
	public BuildList getByPage(int pageNow, int artId)
	{
		BuildDAL buildDAL = new BuildDAL();
		
		return buildDAL.getByPage(pageNow,artId);
		
	}
	
	public int getPageCount(int artId)
	{
		BuildDAL buildDAL = new BuildDAL();
		
		return buildDAL.getPageCount(artId);
	}
	*/
	
	public int getIdByRepArt(String repName,String artName,int num)
	{
		BuildDAL buildDAL = new BuildDAL();
		
		return buildDAL.getIdByRepArt(repName, artName, num);
	}
	
	public int getIdByRepArt(String repName,String artName){
		BuildDAL buildDAL = new BuildDAL();
		
		return buildDAL.getIdByRepArt(repName, artName);
	}
	
	
	public Boolean contains(int artId,int num){
		BuildDAL buildDAL = new BuildDAL();
		return buildDAL.contains(artId,num);
	}
	
	public void BuildReference(String buildPath,String strFileFolder,String tempPath,String workspace,String forceFlag,String name){
		ArrayList<String> nameList = new ArrayList<String>();
		RepositoryService repSer = new RepositoryService();
		ArtifactService artSer = new ArtifactService();
		Repository rep = repSer.getByName(name);
		//System.out.println("RepName: "+name);
		ArtifactList artList = artSer.getAll(rep.getId());
		
		BuildService buildSer = new BuildService();
		DependenceService depSer = new DependenceService();
		for(Artifact art:artList){
			//System.out.println("ArtName: "+art.getName());
			BuildList buildList = buildSer.getAll(art.getId());
			for(Build build:buildList){
				//System.out.println("BuildNum:"+build.getNumber());
				//System.out.println("BuildId:"+build.getId());
				DependenceList depList = depSer.getAll(build.getId());
				//System.out.println("depListLength:"+depList.size());
				for(Dependence dep:depList){
					//System.out.println("DepId:"+dep.getBuildId());
					//System.out.println("Flag:"+dep.getFlag());
					if(dep.getFlag().equals("Build")){
						//System.out.println("DepRefId:"+dep.getReferenceId());
						Build refBuild = buildSer.getById(dep.getReferenceId());
						Artifact refArt = artSer.getById(refBuild.getArtifactId());
						//System.out.println("RefArtName:"+refArt.getName());
						Repository refRep = repSer.getById(refArt.getRepId());
						//System.out.println("RefRepName:"+refRep.getName());
						String refName = refRep.getName();
						boolean flag = true;
						for(int i=0;i<nameList.size();i++){
							if(refName.equals(nameList.get(i))){
								flag = false;
							}
						}
						if(flag){
							nameList.add(refName);
						}
					}
					
				}
			}
		}
		//System.out.println("NameLength:"+nameList.size());
		BuildManagementService bmSer = new BuildManagementService();
		for(String cn:nameList){
			//System.out.println("Name:"+cn);
			ConfigFile config = bmSer.getConfigByName(cn+".xml");
			exeCmd(buildPath,strFileFolder,tempPath,workspace,forceFlag,config);
		}
	}
	
	public int exeCmd(String buildPath,String strFileFolder,String tempPath,String workspace,String forceFlag,ConfigFile file){
		FileService fileSer = new FileService();
		String filepath =strFileFolder +"/"+ file.getFileName();
		File oldFile = new File(filepath);
		File newFile = new File(tempPath+"\\"+file.getName());
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
			String cmd = buildPath+" \""+ws+"\" \""+ filepath +"\" "+forceFlag;
			
			//System.out.println("cmd: "+cmd);
			int exitValue = exeCmd(cmd);
			if(exitValue==0){
				BuildManagementService buildManSer = new BuildManagementService();
				SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
				Date date = new Date();
				String time = df.format(date);
				Timestamp buildtime = Timestamp.valueOf(time);
				buildManSer.updateBuildTime(file.getId(), buildtime);
				BuildReference(buildPath,strFileFolder,tempPath,workspace,forceFlag,name);
			}
			return exitValue;
		}
		return -1;
	}
	
	public int  exeCmd(String cmd){
		//System.out.println("cmd:"+cmd);
		Runtime run = Runtime.getRuntime();
        Process process = null;
        try {
            process = run.exec(cmd); // 执行cmd命令
            final BufferedInputStream in = new BufferedInputStream(process.getInputStream());  
           
            new Thread(new Runnable() {
                public void run() {
                    BufferedReader br = new BufferedReader(new InputStreamReader(in)); 
                    try {
                    	String str;
                    	while ((str = br.readLine()) != null){

                            
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
          
            BufferedInputStream errin = new BufferedInputStream(process.getErrorStream());
            BufferedReader errbr = new BufferedReader(new InputStreamReader(errin));
            while((lineStr = errbr.readLine())!=null){
            	System.out.println("Error--->"+lineStr);
            }
            //检查命令是否执行失败。
           
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
}
