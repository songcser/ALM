package com.prolambda.model;

import java.io.Serializable;
import java.sql.Timestamp;

public class ComponentVersion implements Serializable{

	/**
	 * 
	 */
	private static final long serialVersionUID = -1612988812462382635L;
	private int id;
	private String version;
	private String description;
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
	public int getComponentId() {
		return componentId;
	}
	public void setComponentId(int componentId) {
		this.componentId = componentId;
	}
	private Timestamp created;
	private int componentId;
}
