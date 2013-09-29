package com.prolambda.controller;

import com.prolambda.dal.ArtifactDAL;
import com.prolambda.model.*;

public class ArtifactService {

	public Boolean create(Artifact art)
	{
		ArtifactDAL artDAL = new ArtifactDAL();
		return artDAL.create(art);
	}
	
	public Boolean delete(int id)
	{
		ArtifactDAL artDAL = new ArtifactDAL();
		return artDAL.delete(id);
	}
	
	public Boolean deleteByRepId(int repId){
		ArtifactDAL artDAL = new ArtifactDAL();
		return artDAL.deleteByRepId(repId);
	}
	
	public Boolean update(Artifact art)
	{
		ArtifactDAL artDAL = new ArtifactDAL();
		return artDAL.update(art);
	}
	
	public ArtifactList getAll()
	{
		ArtifactDAL artDAL = new ArtifactDAL();
		return artDAL.getAll();
	}
	
	public ArtifactList getAll(int repId)
	{
		ArtifactDAL artDAL = new ArtifactDAL();
		
		return artDAL.getAll(repId);
	}
	
	public Artifact getById(int id)
	{
		ArtifactDAL artDAL = new ArtifactDAL();
		
		return artDAL.getById(id);
	}
	/*
	public ArtifactList getByPage(int pageNow, int repId)
	{
		ArtifactDAL artDAL = new ArtifactDAL();
		
		return artDAL.getByPage(pageNow,repId);
		
	}
	
	public int getPageCount(int repId)
	{
		ArtifactDAL artDAL = new ArtifactDAL();
		
		return artDAL.getPageCount(repId);
	}
	
	
	
	public int getCount(int repId){
		ArtifactDAL artDAL = new ArtifactDAL();
		
		return artDAL.getCount(repId);
	}*/
	public Boolean contains(int repId, String artName)
	{
		ArtifactDAL artDAL = new ArtifactDAL();
		
		return artDAL.contains(repId, artName);
	}
	
	
}
