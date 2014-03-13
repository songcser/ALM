package com.prolambda.scmserv.entity;

import java.util.*;

public class Repository 
{
	String name;
	String svnRoot;
	String serverURL;
	String owner;
	List<String> subProjects;
	List<String> branches;
	List<String> tags;
	
	public Repository()
	{
		name = new String("");
		svnRoot = new String("");
		serverURL = new String("");
		subProjects = new ArrayList<String>();
		branches = new ArrayList<String>();
		tags = new ArrayList<String>();
	}
	
	public Repository(String name, String svnRoot, String serverURL, List<String> subProjects, List<String> branches, List<String> tags)
	{
		this.name = name;
		this.svnRoot = svnRoot;
		this.serverURL = serverURL;
		this.subProjects = subProjects;
		this.branches = branches;
		this.tags = tags;
	}
	
	public Repository(String name, String svnRoot, List<String> subProjects, List<String> branches, List<String> tags)
	{
		this.name = name;
		this.svnRoot = svnRoot;
		this.serverURL = new String("");
		this.subProjects = subProjects;
		this.branches = branches;
		this.tags = tags;
	}
	
	public Repository(String name, String svnRoot)
	{
		this.name = name;
		this.svnRoot = svnRoot;
		this.serverURL = new String("");
		this.subProjects = new ArrayList<String>();
		this.branches = new ArrayList<String>();
		this.tags = new ArrayList<String>();
	}
	
	public String getOwner()
	{
		return owner;
	}

	public void setOwner(String owner)
	{
		this.owner = owner;
	}
	
	public String getName()
	{
		return name;
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
	
	public String getSvnRoot() 
	{
		return svnRoot;
	}
	
	public void setSvnRoot(String svnRoot)
	{
		this.svnRoot = svnRoot;
	}
	
	public String getServerURL() 
	{
		return serverURL;
	}
	
	public void setServerURL(String serverURL)
	{
		this.serverURL = serverURL;
	}
	
	public List<String> getSubProjects()
	{
		return subProjects;
	}
	
	public void setSubProjects(List<String> subProjects) 
	{
		this.subProjects = subProjects;
	}
	
	public List<String> getBranches()
	{
		return branches;
	}
	
	public void setBranches(List<String> branches)
	{
		this.branches = branches;
	}
	
	public List<String> getTags() 
	{
		return tags;
	}
	
	public void setTags(List<String> tags) 
	{
		this.tags = tags;
	}
}
