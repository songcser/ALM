package com.prolambda.model;

public class ProductTree {
	private int id;
	private int productId;
	private int libraryId;
	private String path;
	
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
	public int getLibraryId() {
		return libraryId;
	}
	public void setLibraryId(int libraryId) {
		this.libraryId = libraryId;
	}
	public String getPath() {
		return path;
	}
	public void setPath(String path) {
		this.path = path;
	}
}
