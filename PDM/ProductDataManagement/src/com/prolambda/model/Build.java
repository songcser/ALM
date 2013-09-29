package com.prolambda.model;

import java.sql.Timestamp;

public class Build {
	private int id;
	private int number;
	private Timestamp started;
	private long duration;
	private BuildResult result;
	private String sourcePath;
	private String sourceVersion;
	private String environment;
	private String log;
	private int artifactId;
	
	
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public int getNumber() {
		return number;
	}
	public void setNumber(int number) {
		this.number = number;
	}
	public Timestamp getStarted() {
		return started;
	}
	public void setStarted(Timestamp started) {
		this.started = started;
	}
	public long getDuration() {
		return duration;
	}
	public void setDuration(long duration) {
		this.duration = duration;
	}
	public String getSourcePath() {
		return sourcePath;
	}
	public void setSourcePath(String sourcePath) {
		this.sourcePath = sourcePath;
	}
	public String getSourceVersion() {
		return sourceVersion;
	}
	public void setSourceVersion(String sourceVersion) {
		this.sourceVersion = sourceVersion;
	}
	public String getEnvironment() {
		return environment;
	}
	public void setEnvironment(String environment) {
		this.environment = environment;
	}
	public String getLog() {
		return log;
	}
	public void setLog(String log) {
		this.log = log;
	}
	public int getArtifactId() {
		return artifactId;
	}
	public void setArtifactId(int artifactId) {
		this.artifactId = artifactId;
	}
	public BuildResult getResult() {
		return result;
	}
	public void setResult(BuildResult result) {
		this.result = result;
	}
}
