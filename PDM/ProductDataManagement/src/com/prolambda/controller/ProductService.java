package com.prolambda.controller;

import com.prolambda.dal.ProductDAL;
import com.prolambda.model.Product;
import com.prolambda.model.ProductList;

public class ProductService {
	public Boolean create(Product pro){
		ProductDAL proDAL = new ProductDAL();
		return proDAL.create(pro);
	}
	
	public Boolean delete(int id){
		ProductDAL proDAL = new ProductDAL();
		return proDAL.delete(id);
	}
	
	public Boolean update(Product pro){
		ProductDAL proDAL = new ProductDAL();
		return proDAL.update(pro);
	}
	
	public ProductList getAll(int categoryId){
		ProductDAL proDAL = new ProductDAL();
		return proDAL.getAll(categoryId);
	}
	
	public Product getById(int id){
		ProductDAL proDAL = new ProductDAL();
		return proDAL.getById(id);
	}
	
	public Boolean contains(String categoryName,String productName){
		ProductDAL proDAL = new ProductDAL();
		return proDAL.contains(categoryName,productName);
	}
	public int getIdByName(String categoryName,String productName){
		ProductDAL proDAL = new ProductDAL();
		return proDAL.getIdByName(categoryName,productName);
	}
	
}
