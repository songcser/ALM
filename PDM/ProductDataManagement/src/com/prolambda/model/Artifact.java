package com.prolambda.model;

import java.io.Serializable;
import java.sql.Timestamp;

public class Artifact implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = -1181319508194191884L;
	private int id;
	private String name;
	private int count;
	private Timestamp started;
	private Timestamp lasttime;
	private int repId;
	
	
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
	public int getCount() {
		return count;
	}
	public void setCount(int count) {
		this.count = count;
	}
	public Timestamp getStarted() {
		return started;
	}
	public void setStarted(Timestamp started) {
		this.started = started;
	}
	public Timestamp getLasttime() {
		return lasttime;
	}
	public void setLasttime(Timestamp lasttime) {
		this.lasttime = lasttime;
	}
	public int getRepId() {
		return repId;
	}
	public void setRepId(int repId) {
		this.repId = repId;
	}
	
	
}
