package com.prolambda.pdm.PDMplugin;

import com.thoughtworks.xstream.annotations.XStreamAlias;

@XStreamAlias("dependence")
public class SourceCode {
	
	@XStreamAlias("url")
	private String url;
	
	@XStreamAlias("version")
	private String version;
	public String getUrl() {
		return url;
	}
	public void setUrl(String url) {
		this.url = url;
	}
	public String getVersion() {
		return version;
	}
	public void setVersion(String version) {
		this.version = version;
	}
}
