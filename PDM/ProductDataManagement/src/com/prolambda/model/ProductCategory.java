package com.prolambda.model;

import java.io.Serializable;
import java.sql.Timestamp;

public class ProductCategory implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1307487462075299724L;
	private int id;
	private String name;
	private String description;
	private Timestamp created;
	private Timestamp modified;
	private int productCount;
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
	public Timestamp getCreated() {
		return created;
	}
	public void setCreated(Timestamp created) {
		this.created = created;
	}
	public Timestamp getModified() {
		return modified;
	}
	public void setModified(Timestamp modified) {
		this.modified = modified;
	}
	public int getProductCount() {
		return productCount;
	}
	public void setProductCount(int productCount) {
		this.productCount = productCount;
	}

}
