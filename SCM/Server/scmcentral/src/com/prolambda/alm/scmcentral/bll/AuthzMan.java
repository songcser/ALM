package com.prolambda.alm.scmcentral.bll;

import java.util.*;
import com.prolambda.alm.scmcentral.dal.*;
import com.prolambda.alm.scmcentral.entity.*;

public class AuthzMan 
{
	public static List<String> findUserPerm(String name, String svnRoot)
	{
		List<String> retList;
		
		String configPath = svnRoot + "\\authz";
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, name);
		retList = iniFileOpe.findByKey();
		
		return retList;
	}
	
	public static List<String> findGroupPerm(String name, String svnRoot)
	{
		List<String> retList;
		
		String configPath = svnRoot + "\\authz";
		String key = "@" + name;
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, key);
		retList = iniFileOpe.findByKey();
		
		return retList;
	}
	
	public static List<ScmUser> findPathUserPerm(String section, String svnRoot)
	{
		List<ScmUser> retList = new ArrayList<ScmUser>();
		List<String> permList;
		
		String configPath = svnRoot + "\\authz";
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, section, "");
		permList = iniFileOpe.findBySection();
		
		if(permList == null){
			return retList;
		}
		
		for(int i = 0; i < permList.size(); i++){
			String[] perm = permList.get(i).split("::=");
			if(perm.length >= 2){
				if(0 != perm[0].indexOf("@")){
					ScmUser user = new ScmUser();
					user.setName(perm[0]);
					if(perm[1].equals("r")){
						user.setPermission(0);
					}
					if(perm[1].equals("rw")){
						user.setPermission(1);
					}
					retList.add(user);
				}
			}
		}
		
		return retList;
	}
	
	public static List<UserGroup> findPathGroupPerm(String section, String svnRoot)
	{
		List<UserGroup> retList = new ArrayList<UserGroup>();
		List<String> permList;
		
		String configPath = svnRoot + "\\authz";
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, section, "");
		permList = iniFileOpe.findBySection();
		
		if(permList == null){
			return retList;
		}
		
		for(int i = 0; i < permList.size(); i++){
			String[] perm = permList.get(i).split("::=");
			if(perm.length >= 2){
				if(0 == perm[0].indexOf("@")){
					UserGroup group = new UserGroup();
					group.setName(perm[0]);
					if(perm[1].equals("r")){
						group.setPermission(0);
					}
					if(perm[1].equals("rw")){
						group.setPermission(1);
					}
					retList.add(group);
				}
			}
		}
		
		return retList;
	}
	
	public static boolean setUserPerm(String section, ScmUser user, String svnRoot)
	{
		String configPath = svnRoot + "\\authz";
		String key = user.getName();
		String value = "";
		
		if(0 == user.getPermission()){
			value = "r";
		}
		if(1 == user.getPermission()){
			value = "rw";
		}
		
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, section, key, value);
		
		if(!iniFileOpe.writeKeyValue()){
			return false;
		}
		
		return true;
	}
	
	public static boolean deleleUserPerm(String section, ScmUser user, String svnRoot)
	{
		String configPath = svnRoot + "\\authz";
		String key = user.getName();
		
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, section, key);
		
		if(!iniFileOpe.deleteKeyValue()){
			return false;
		}
		
		return true;
	}
	
	public static boolean setGroupPerm(String section, UserGroup group, String svnRoot)
	{
		String configPath = svnRoot + "\\authz";
		String key = "@" + group.getName();
		String value = "";
		
		if(0 == group.getPermission()){
			value = "r";
		}
		if(1 == group.getPermission()){
			value = "rw";
		}
		
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, section, key, value);
		
		if(!iniFileOpe.writeKeyValue()){
			return false;
		}
		
		return true;
	}
	
	public static boolean deleteGroupPerm(String section, UserGroup group, String svnRoot)
	{
		String configPath = svnRoot + "\\authz";
		String key = "@" + group.getName();
		
		IniFileOpe iniFileOpe = new IniFileOpe(configPath, section, key);
		
		if(!iniFileOpe.deleteKeyValue()){
			return false;
		}
		
		return true;
	}
}
