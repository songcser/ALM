package com.prolambda.alm.scmcentral.entity;

import java.util.*;

public class UserGroup
{
	String name;
	List<String> members;
	int permission;
	
	public UserGroup(String name, List<String> members, int permission)
	{
		this.name = name;
		this.members = members;
		this.permission = permission;
	}
	
	public UserGroup(String name, List<String> members)
	{
		this.name = name;
		this.members = members;
		this.permission = -1;
	}
	
	public UserGroup(String name)
	{
		this.name = name;
		this.members = new ArrayList<String>();
		this.permission = -1;
	}
	
	public UserGroup()
	{
		name = new String("");
		members = new ArrayList<String>();
		permission = -1;
	}
	
	public String getName()
	{
		return name;
	}
	
	public void setName(String name) 
	{
		this.name = name;
	}
	
	public List<String> getMembers()
	{
		return members;
	}
	
	public void setMembers(List<String> members) 
	{
		this.members = members;
	}
	
	public int getPermission() 
	{
		return permission;
	}
	
	public void setPermission(int permission) 
	{
		this.permission = permission;
	}
}
