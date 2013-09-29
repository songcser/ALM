package com.prolambda.pdm.PDMplugin;

import com.thoughtworks.xstream.annotations.XStreamAlias;

@XStreamAlias("dependence")
public class Dependence {
	
	@XStreamAlias("name")
	private String name;
	
	@XStreamAlias("version")
	private String version;
	
	@XStreamAlias("repository")
	private String repository;
	
	@XStreamAlias("platform")
	private String platform;
	
	@XStreamAlias("configuration")
	private String configuration;
	
	@XStreamAlias("location")
	private String location;
	
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getVersion() {
		return version;
	}
	public void setVersion(String version) {
		this.version = version;
	}
	public String getRepository() {
		return repository;
	}
	public void setRepository(String repository) {
		this.repository = repository;
	}
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
	}
	public String getLocation() {
		return location;
	}
	public void setLocation(String location) {
		this.location = location;
	}
}
