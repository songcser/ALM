package com.prolambda.model;

public class BuildProject {
	private int id;
	private String Name;
	private String ConfigUrl;
	private String RelativePath;
	
	
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getName() {
		return Name;
	}
	public void setName(String name) {
		Name = name;
	}
	public String getConfigUrl() {
		return ConfigUrl;
	}
	public void setConfigUrl(String configUrl) {
		ConfigUrl = configUrl;
	}
	public String getRelativePath() {
		return RelativePath;
	}
	public void setRelativePath(String relativePath) {
		RelativePath = relativePath;
	}
	
	
}
