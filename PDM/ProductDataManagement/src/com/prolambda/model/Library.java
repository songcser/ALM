package com.prolambda.model;

import java.io.Serializable;

public class Library implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 3925612696783999926L;
	private int id;
	private String name;
	private String description;
	private String type;
	private int buildId = -1;
	private int componentId = -1;
	private int productId = -1;
	private String fileName;
	//private String targetPath;
	
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
	public String getType() {
		return type;
	}
	public void setType(String type) {
		this.type = type;
	}
	public int getBuildId() {
		return buildId;
	}
	public void setBuildId(int buildId) {
		this.buildId = buildId;
	}
	public int getComponentId() {
		return componentId;
	}
	public void setComponentId(int componentId) {
		this.componentId = componentId;
	}
	public int getProductId() {
		return productId;
	}
	public void setProductId(int productId) {
		this.productId = productId;
	}
	public String getFileName() {
		return fileName;
	}
	public void setFileName(String fileName) {
		this.fileName = fileName;
	}
	/*
	public String getTargetPath() {
		return targetPath;
	}
	public void setTargetPath(String targetPath) {
		this.targetPath = targetPath;
	}
	
	*/
}
