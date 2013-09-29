package com.prolambda.controller;

import com.prolambda.dal.ProductVersionDAL;
import com.prolambda.model.ComponentVersionList;
import com.prolambda.model.ProductDependence;
import com.prolambda.model.ProductDependenceList;
import com.prolambda.model.ProductTree;
import com.prolambda.model.ProductTreeList;
import com.prolambda.model.ProductVersion;
import com.prolambda.model.ProductVersionList;

public class ProductVersionService {
	public Boolean create(ProductVersion version){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.create(version);
	}
	
	public Boolean delete(int id){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.delete(id);
	}
	
	public Boolean update(ProductVersion version){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.update(version);
	}
	
	public ProductVersionList getVersions(int productId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getVersions(productId);
	}
	
	public ProductVersion getVersionById(int id){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getVersionById(id);
	}
	
	public Boolean contains(String categoryName,String productName,String version){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.contains(categoryName,productName,version);
	}
	
	public int getIdByVersion(String categoryName,String productName,String version){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getIdByVersion(categoryName,productName,version);
	}
	
	public int getIdByVersion(String categoryName,String productName){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getIdByVersion(categoryName,productName);
	}
	
	public ComponentVersionList getComponents(int id){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getComponents(id);
	}
	
	public Boolean addComponent(int productId,int componentId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.addComponent(productId,componentId);
	}
	public Boolean addComponent(int productId,int componentId,String location){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.addComponent(productId,componentId,location);
	}
	
	public Boolean containsComponent(int productId,int componentId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.containsComponent(productId,componentId);
	}
	
	public Boolean deleteComponent(int productId,int componentId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.deleteComponent(productId,componentId);
	}
	
	public Boolean setComponentLocation(int productId,int componentId,String location){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.setComponentLocation(productId, componentId,location);
	}
	
	public String getComponentLocation(int productId,int componentId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getComponentLocation(productId, componentId);
	}
	
	public ProductDependenceList getDependences(int productId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getDependences(productId);
	}
	
	public Boolean addDependence(int productId,int dependenceId,int fileid){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.addDependence(productId, dependenceId,fileid);
	}
	
	public Boolean addDependence(ProductDependence pDep){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.addDependence(pDep);
	}
	public Boolean containDependence(int productId,int dependenceId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.containsDependence(productId,dependenceId);
	}
	
	public Boolean removeDependence(int productId,int dependenceId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.removeDependence(productId,dependenceId);
	}
	
	public Boolean addTree(ProductTree tree){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.addTree(tree);
	}
	
	public Boolean containTree(int productId,int libraryId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.containTree(productId,libraryId);
	}
	
	public Boolean updateTree(ProductTree tree){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.updateTree(tree);
	}
	
	public int getTreeId(int productId, int libraryId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getTreeId(productId,libraryId);
	}

	public ProductTreeList getTrees(int productId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getTrees(productId);
	}

	public Boolean deleteTree(int productId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.deleteTree(productId);
	}
	
	public Boolean deleteTree(int productId, int libraryId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.deleteTree(productId,libraryId);
	}
	public Boolean deleteTreeByLibrary(int libraryId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.deleteTreeByLibrary(libraryId);
	}
	
	public Boolean addIssFile(int productid,int issId,int fileId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.addIssFile(productid,issId, fileId);
	}
	
	public int getFileByIss(int issId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getFileByIss(issId);
	}
	
	public int getIssBySetupFile(int setupId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getIssBySetupFile(setupId);
	}
	
	public Boolean containsIss(int issId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.containsIss(issId);
	}
	
	public Boolean deleteByIssId(int issId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.deleteByIssId(issId);
	}
	
	public String getDependenceLocation(int productId,int dependenceId){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getDependenceLocation(productId,dependenceId);
	}
	
	public String getDependenceLocation(int id){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.getDependenceLocation(id);
	}
	
	public Boolean setDependenceLocation(int productId,int dependenceId,String location){
		ProductVersionDAL versionDAL = new ProductVersionDAL();
		return versionDAL.setDependenceLocation(productId, dependenceId, location);
	}
}
