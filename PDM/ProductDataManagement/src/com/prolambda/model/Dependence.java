package com.prolambda.model;

public class Dependence {
	private int id;
	private int referenceId;
	private String flag;
	private String path;
	//private String platform;
	//private String configuration;
	private String location;
	private int buildId;
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public int getReferenceId() {
		return referenceId;
	}
	public String getFlag() {
		return flag;
	}
	public void setFlag(String flag) {
		this.flag = flag;
	}
	public String getPath() {
		return path;
	}
	public void setPath(String path) {
		this.path = path;
	}
	public void setReferenceId(int referenceId) {
		this.referenceId = referenceId;
	}
	/*
	public String getPlatform() {
		return platform;
	}
	public void setPlatform(String platform) {
		this.platform = platform;
	}
	public String getConfiguration() {
		return configuration;
	}
	public void setConfiguration(String configuration) {
		this.configuration = configuration;
	}*/
	public String getLocation() {
		return location;
	}
	public void setLocation(String location) {
		this.location = location;
	}
	public int getBuildId() {
		return buildId;
	}
	public void setBuildId(int buildId) {
		this.buildId = buildId;
	}
}
