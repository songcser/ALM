package com.prolambda.model;

import java.sql.Timestamp;

public class ConfigFile {
	private int id;
	private String name;
	private String fileName;
	private Boolean isRunning;
	private Timestamp buildtime;
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
	public String getFileName() {
		return fileName;
	}
	public void setFileName(String fileName) {
		this.fileName = fileName;
	}
	public Boolean getIsRunning() {
		return isRunning;
	}
	public void setIsRunning(Boolean isRunning) {
		this.isRunning = isRunning;
	}
	public Timestamp getBuildtime() {
		return buildtime;
	}
	public void setBuildtime(Timestamp buildtime) {
		this.buildtime = buildtime;
	}
}
