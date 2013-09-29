package com.prolambda.controller;

import com.prolambda.dal.ComponentCategoryDAL;
import com.prolambda.model.ComponentCategory;
import com.prolambda.model.ComponentCategoryList;

public class ComponentCategoryService {
	public Boolean create(ComponentCategory comCategory){
		ComponentCategoryDAL comCateDAL = new ComponentCategoryDAL();
		return comCateDAL.create(comCategory);
	}
	
	public Boolean delete(int id){
		ComponentCategoryDAL comCateDAL = new ComponentCategoryDAL();
		return comCateDAL.delete(id);
	}
	
	public Boolean delete(String name){
		ComponentCategoryDAL comCateDAL = new ComponentCategoryDAL();
		return comCateDAL.delete(name);
	}
	
	public Boolean update(ComponentCategory comCategory){
		ComponentCategoryDAL comCateDAL = new ComponentCategoryDAL();
		return comCateDAL.update(comCategory);
	}
	
	public ComponentCategoryList getAll(){
		ComponentCategoryDAL comCateDAL = new ComponentCategoryDAL();
		return comCateDAL.getAll();
	}
	
	public ComponentCategory getById(int id){
		ComponentCategoryDAL comCateDAL = new ComponentCategoryDAL();
		return comCateDAL.getById(id);
	}
	
	public ComponentCategory getByName(String name){
		ComponentCategoryDAL comCateDAL = new ComponentCategoryDAL();
		return comCateDAL.getByName(name);
	}
	
	public Boolean contains(String name){
		ComponentCategoryDAL comCateDAL = new ComponentCategoryDAL();
		return comCateDAL.contains(name);
	}
}
