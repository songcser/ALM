package com.prolambda.controller;

import com.prolambda.dal.ProductCategoryDAL;
import com.prolambda.model.ProductCategory;
import com.prolambda.model.ProductCategoryList;

public class ProductCategoryService {
	public Boolean create(ProductCategory proCate){
		ProductCategoryDAL proCateDAL = new ProductCategoryDAL();
		return proCateDAL.create(proCate);
	}
	
	public Boolean delete(int id){
		ProductCategoryDAL proCateDAL = new ProductCategoryDAL();
		return proCateDAL.delete(id);
	}
	
	public Boolean delete(String name){
		ProductCategoryDAL proCateDAL = new ProductCategoryDAL();
		return proCateDAL.delete(name);
	}
	
	public Boolean update(ProductCategory proCate){
		ProductCategoryDAL proCateDAL = new ProductCategoryDAL();
		return proCateDAL.update(proCate);
	}
	
	public ProductCategoryList getAll(){
		ProductCategoryDAL proCateDAL = new ProductCategoryDAL();
		return proCateDAL.getAll();
	}
	
	public ProductCategory getById(int id){
		ProductCategoryDAL proCateDAL = new ProductCategoryDAL();
		return proCateDAL.getById(id);
	}
	
	public ProductCategory getByName(String name){
		ProductCategoryDAL proCateDAL = new ProductCategoryDAL();
		return proCateDAL.getByName(name);
	}
	
	public Boolean contains(String name){
		ProductCategoryDAL proCateDAL = new ProductCategoryDAL();
		return proCateDAL.contains(name);
	}
}
