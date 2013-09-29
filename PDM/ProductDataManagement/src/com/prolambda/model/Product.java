package com.prolambda.model;

import java.io.Serializable;
import java.sql.Timestamp;

public class Product implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = -5526083563820589669L;
	private int id;
	private String name;
	private String description;
	private Timestamp created;
	private Timestamp modified;
	private int state;
	private String lastVersion;
	private int categoryId;
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
	public int getState() {
		return state;
	}
	public void setState(int state) {
		this.state = state;
	}
	public String getLastVersion() {
		return lastVersion;
	}
	public void setLastVersion(String lastVersion) {
		this.lastVersion = lastVersion;
	}
	public int getCategoryId() {
		return categoryId;
	}
	public void setCategoryId(int categoryId) {
		this.categoryId = categoryId;
	}
}
