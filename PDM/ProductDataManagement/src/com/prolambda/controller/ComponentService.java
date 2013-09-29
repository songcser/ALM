package com.prolambda.controller;

import com.prolambda.dal.ComponentDAL;
import com.prolambda.model.Component;
import com.prolambda.model.ComponentList;

public class ComponentService {
	public Boolean create(Component com){
		ComponentDAL comDAL = new ComponentDAL();
		return comDAL.create(com);
	}
	
	public Boolean delete(int id){
		ComponentDAL comDAL = new ComponentDAL();
		return comDAL.delete(id);
	}
	
	public Boolean update(Component com){
		ComponentDAL comDAL = new ComponentDAL();
		return comDAL.update(com);
	}
	
	public ComponentList getAll(int categoryId){
		ComponentDAL comDAL = new ComponentDAL();
		return comDAL.getAll(categoryId);
	}
	
	public Component getById(int id){
		ComponentDAL comDAL = new ComponentDAL();
		return comDAL.getById(id);
	}
	
	public int getIdByName(String categoryName,String name){
		ComponentDAL comDAL = new ComponentDAL();
		return comDAL.getIdByName(categoryName,name);
	}
	
	public Boolean contains(String categoryName,String componentName){
		ComponentDAL comDAL = new ComponentDAL();
		return comDAL.contains(categoryName,componentName);
	}
}
