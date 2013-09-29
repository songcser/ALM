package com.prolambda.controller;

import com.prolambda.dal.RepositoryDAL;
import com.prolambda.model.*;

public class RepositoryService {
	
	public Boolean create(Repository rep)
	{
		RepositoryDAL repDAL = new RepositoryDAL();
		return repDAL.create(rep);
	}
	
	public Boolean delete(String name)
	{
		RepositoryDAL repDAL = new RepositoryDAL();
		return repDAL.delete(name);
	}
	
	public void clean(){
		RepositoryDAL repDAL = new RepositoryDAL();
		repDAL.clean();
	}
	
	public void update(Repository rep)
	{
		RepositoryDAL repDAL = new RepositoryDAL();
		repDAL.update(rep);
	}
	
	public RepositoryList getAll()
	{
		RepositoryList repList = new RepositoryList();
		RepositoryDAL repDAL = new RepositoryDAL();
		repList = repDAL.getAll();
		return repList;
	}
	
	public Repository getById(int id)
	{
		RepositoryDAL repDAL = new RepositoryDAL();
		
		return repDAL.getById(id);
	}
	
	public Repository getByName(String name)
	{
		RepositoryDAL repDAL = new RepositoryDAL();
		
		return repDAL.getByName(name);
	}
	
	public boolean contains(String name)
	{
		RepositoryDAL repDAL = new RepositoryDAL();
		
		return repDAL.contains(name);
	}
/*
	public RepositoryList getByPage(int pageNow) {
		// TODO Auto-generated method stub
		RepositoryDAL repDAL = new RepositoryDAL();
		RepositoryList repList = repDAL.getByPage(pageNow);
		return repList;
	}

	public int getPageCount() {
		// TODO Auto-generated method stub
		RepositoryDAL repDAL = new RepositoryDAL();
		return repDAL.getPageCount();
	}*/
}

