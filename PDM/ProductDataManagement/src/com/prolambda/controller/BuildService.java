package com.prolambda.controller;

import com.prolambda.dal.BuildDAL;
import com.prolambda.model.Build;
import com.prolambda.model.BuildList;

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
}
