package com.prolambda.applet;

public class TreeNode {

	private String name;
	private String path;
	
	public TreeNode(String name,String path){
	
		this.name = name;
		this.path = path;
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getPath() {
		return path;
	}
	public void setPath(String path) {
		this.path = path;
	}
	
	public String toString(){
	    return  this.name;
	}
}
