package com.prolambda.controller;

import com.prolambda.dal.ComponentVersionDAL;
import com.prolambda.model.ComponentVersion;
import com.prolambda.model.ComponentVersionList;
import com.prolambda.model.ProductVersionList;

public class ComponentVersionService {

	public Boolean create(ComponentVersion version){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.create(version);
	}
	
	public Boolean delete(int id){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.delete(id);
	}
	
	public Boolean update(ComponentVersion version){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.update(version);
	}
	
	public ComponentVersionList getVersions(int componentId){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.getVersions(componentId);
	}
	
	public ComponentVersion getVersionById(int id){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.getVersionById(id);
	}
	
	public Boolean contains(String categoryName,String componentName,String version){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.contains(categoryName,componentName,version);
	}
	
	public int getIdByVersion(String categoryName,String componentName,String version){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.getIdByVersion(categoryName,componentName,version);
	}
	
	public int getIdByVersion(String categoryName,String componentName){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.getIdByVersion(categoryName,componentName);
	}
	
	public ProductVersionList getProducts(int id){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.getProducts(id);
	}
	
	public ComponentVersionList getDependences(int id){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.getDependences(id);
	}
	
	public Boolean addDependence(int componentId,int dependenceId){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.addDependence(componentId,dependenceId);
	}
	
	public Boolean containDependence(int componentId,int dependenceId){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.containDependence(componentId,dependenceId);
	}
	
	public Boolean removeDependence(int componentId,int dependenceId){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.removeDependence(componentId,dependenceId);
	}
	
	public String getLocation(int componentId,int dependenceId){
		ComponentVersionDAL versionDAL = new ComponentVersionDAL();
		return versionDAL.getLocation(componentId, dependenceId);
	}
}
