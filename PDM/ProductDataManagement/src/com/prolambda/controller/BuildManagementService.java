package com.prolambda.controller;

import java.sql.Timestamp;

import com.prolambda.dal.BuildManagementDAL;
import com.prolambda.model.BuildProject;
import com.prolambda.model.ConfigFile;
import com.prolambda.model.ConfigFileList;

public class BuildManagementService {

	public void addConfig(ConfigFile file){
		BuildManagementDAL buildDAL = new BuildManagementDAL();
		
		buildDAL.addConfigFile(file);
	}
	
	public Boolean deleteConfigFile(int id){
		BuildManagementDAL buildDAL = new BuildManagementDAL();
		return buildDAL.deleteConfigFile(id);
	}
	
	public Boolean updateBuildTime(int id,Timestamp buildTime){
		BuildManagementDAL buildDAL = new BuildManagementDAL();
		return buildDAL.updateBuildTime(id, buildTime);
	}
	public Boolean updateRunning(int id,Boolean isRunning){
		BuildManagementDAL buildDAL = new BuildManagementDAL();
		if(isRunning){
			return buildDAL.updateRunning(id,1);
		}else 
			return buildDAL.updateRunning(id,0);
		
	}
	
	public ConfigFileList getAllConfig(){
		BuildManagementDAL buildDAL = new BuildManagementDAL();
		return buildDAL.getAll();
	}
	
	public ConfigFile getConfigByName(String name){
		BuildManagementDAL buildDAL = new BuildManagementDAL();
		return buildDAL.getConfigByName(name);
	}
	
	public ConfigFile getById(int id){
		BuildManagementDAL buildDAL = new BuildManagementDAL();
		return buildDAL.getById(id);
	}
	
	public int getIdByFileName(String filename){
		BuildManagementDAL buildDAL = new BuildManagementDAL();
		return buildDAL.getIdByFileName(filename);
	}
	
	private void createBuildProject(BuildProject pro){
		BuildManagementDAL buildDAL = new BuildManagementDAL();
		buildDAL.createBuildProject(pro);
	}
}
