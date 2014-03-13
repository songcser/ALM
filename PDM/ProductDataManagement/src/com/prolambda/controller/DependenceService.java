package com.prolambda.controller;

import com.prolambda.dal.DependenceDAL;
import com.prolambda.model.Dependence;
import com.prolambda.model.DependenceList;

public class DependenceService {
	
	public Boolean create(Dependence item)
	{
		DependenceDAL depDAL = new DependenceDAL();
		return depDAL.create(item);
	}
	
	public Boolean delete(int id)
	{
		DependenceDAL depDAL = new DependenceDAL();
		return depDAL.delete(id);
	}
	
	public Boolean deleteByBuildId(int libId){
		DependenceDAL depDAL = new DependenceDAL();
		return depDAL.deleteByBuildId(libId);
	}
	
	public Boolean update(Dependence item)
	{
		DependenceDAL depDAL = new DependenceDAL();
		return depDAL.update(item);
	}
	
	public DependenceList getAll(int buildId)
	{
		DependenceDAL depDAL = new DependenceDAL();
		
		return depDAL.getAll(buildId);
	}
	
	public Dependence getById(int id)
	{
		DependenceDAL depDAL = new DependenceDAL();
		
		return depDAL.getById(id);
	}
	public Boolean contains(Dependence dep){
		DependenceDAL depDAL = new DependenceDAL();
		return depDAL.contains(dep);
	}
	
	public DependenceList getAllByRefId(int refId){
		DependenceDAL depDAL = new DependenceDAL();
		return depDAL.getAllByRefId(refId);
	}
}
