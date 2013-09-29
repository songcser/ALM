package com.prolambda.model;

import java.io.Serializable;

public class ProductDependence implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 5349253390560833689L;
	private int id;
	private int productId;
	
	private int dependenceId;
	private String dependenceName;
	private String dependenceVersion;
	private int fileId;
	private String fileName;
	private String relativePath;
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public int getProductId() {
		return productId;
	}
	public void setProductId(int productId) {
		this.productId = productId;
	}
	
	public int getDependenceId() {
		return dependenceId;
	}
	public void setDependenceId(int dependenceId) {
		this.dependenceId = dependenceId;
	}
	
	public String getDependenceName() {
		return dependenceName;
	}
	public void setDependenceName(String dependenceName) {
		this.dependenceName = dependenceName;
	}
	public String getDependenceVersion() {
		return dependenceVersion;
	}
	public void setDependenceVersion(String dependenceVersion) {
		this.dependenceVersion = dependenceVersion;
	}
	public int getFileId() {
		return fileId;
	}
	public void setFileId(int fileId) {
		this.fileId = fileId;
	}
	public String getFileName() {
		return fileName;
	}
	public void setFileName(String fileName) {
		this.fileName = fileName;
	}
	public String getRelativePath() {
		return relativePath;
	}
	public void setRelativePath(String relativePath) {
		this.relativePath = relativePath;
	}
}
