package com.prolambda.scmserv.bll;

import com.prolambda.scmserv.dal.*;
import com.prolambda.scmserv.entity.*;

import java.util.*;

public class UserGroupMan 
{
	List<UserGroup> groups;
	
	public UserGroupMan()
	{
		groups = new ArrayList<UserGroup>();
	}
	
	public UserGroupMan(List<UserGroup> groups)
	{
		this.groups = groups;
	}
	
	public List<UserGroup> getGroups()
	{
		return groups;
	}
	
	public void setGroups(List<UserGroup> groups)
	{
		this.groups = groups;
	}
	
	public List<UserGroup> getGroupsFromRepos(String svnRoot)
	{
		String configPath = svnRoot + "\\authz";
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, "groups", "");
		List<String> groupList = iniFileOpe.findBySection();
		
		for(int j = 0; j < groupList.size(); j++){
		   String[] tpBuffer = groupList.get(j).split("::=");
		   if(tpBuffer.length >= 2){
			   String[] values = tpBuffer[1].split(",");
			   List<String> members = new ArrayList<String>();
			   
			   for(int i = 0; i < values.length; i++){
				   members.add(values[i]);
			   }
			   
			   UserGroup group = new UserGroup(tpBuffer[0], members);
			   groups.add(group);
		   }
		}
		
		return groups;
	}
	
	public boolean saveGroups(String svnRoot)
	{
		String configPath = svnRoot + "\\authz";
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, "groups", "");
		
		for(int i = 0; i < groups.size(); i++){
			iniFileOpe.setKey(groups.get(i).getName());
			List<String> memberList = groups.get(i).getMembers();
			String value = "";
			for(int j = 0; j < memberList.size(); j++){
				value += memberList.get(j);
				if(j < memberList.size() -1){
					value += ",";
				}
			}
			iniFileOpe.setValue(value);
			iniFileOpe.writeKeyValue();
		}
		
		return true;
	}
	
	public boolean addGroup(UserGroup group)
	{
		groups.add(group);
		return true;
	}
	
	public boolean removeGroup(UserGroup group)
	{
		groups.remove(group);
		return true;
	}
	
	public boolean createGroup(UserGroup group, String svnRoot)
	{
		String configPath = svnRoot + "\\authz";
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, "groups", "");
		
		iniFileOpe.setKey(group.getName());
		List<String> memberList = group.getMembers();
		String value = "";
		for(int j = 0; j < memberList.size(); j++){
			value += memberList.get(j);
			if(j < memberList.size() -1){
				value += ",";
			}
		}
		iniFileOpe.setValue(value);
		if(!iniFileOpe.writeKeyValue()){
			return false;
		}

		return true;
	}
	
	public boolean deleteGroup(UserGroup group, String svnRoot)
	{
		String configPath = svnRoot + "\\authz";
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, "groups", "");
		
		iniFileOpe.setKey(group.getName());
		if(!iniFileOpe.deleteKeyValue()){
			return false;
		}
		
		return true;
	}
}
