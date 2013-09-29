package com.prolambda.model;

import java.io.Serializable;
import java.sql.Timestamp;

public class ProductVersion implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 5140609670552587397L;
	private int id;
	private String version;
	private String description;
	private Timestamp created;
	private int productId;
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getVersion() {
		return version;
	}
	public void setVersion(String version) {
		this.version = version;
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
	public int getProductId() {
		return productId;
	}
	public void setProductId(int productId) {
		this.productId = productId;
	}
	
}
