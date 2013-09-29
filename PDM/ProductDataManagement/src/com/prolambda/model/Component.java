package com.prolambda.model;

import java.io.Serializable;
import java.sql.Timestamp;

public class Component implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = -581521978923740544L;
	private int id;
	private String name;
	private String description;
	private String lastVersion;
	private Timestamp created;
	private Timestamp modified;
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
	public String getLastVersion() {
		return lastVersion;
	}
	public void setLastVersion(String lastVersion) {
		this.lastVersion = lastVersion;
	}
	public Timestamp getCreated() {
		return created;
	}
	public void setCreated(Timestamp created) {
		this.created = created;
	}
	public int getCategoryId() {
		return categoryId;
	}
	public void setCategoryId(int categoryId) {
		this.categoryId = categoryId;
	}
	public Timestamp getModified() {
		return modified;
	}
	public void setModified(Timestamp modified) {
		this.modified = modified;
	}
}
