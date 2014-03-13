package com.prolambda.scmserv.bll;

import java.util.*;

import com.prolambda.scmserv.entity.*;
import com.prolambda.scmserv.dal.*;
import com.prolambda.webmatrix.directory.*;

public class UserMan 
{
	List<ScmUser> companyUsers;
	List<ScmUser> systemUsers;
	
	public UserMan()
	{
		companyUsers = new ArrayList<ScmUser>();
		systemUsers = new ArrayList<ScmUser>();
	}
	
	public UserMan(List<ScmUser> companyUsers, List<ScmUser> systemUsers)
	{
		this.companyUsers = companyUsers;
		this.systemUsers = systemUsers;
	}
	
	public List<ScmUser> getCompanyUsers()
	{
		return companyUsers;
	}
	
	public void setCompanyUsers(List<ScmUser> companyUsers) 
	{
		this.companyUsers = companyUsers;
	}
	
	public List<ScmUser> getSystemUsers() 
	{
		return systemUsers;
	}
	
	public void setSystemUsers(List<ScmUser> systemUsers) 
	{
		this.systemUsers = systemUsers;
	}

	public List<ScmUser> getUsersFromCompany(String configRealPath)
	{
		try {
			IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "sysConfig", "host");
			String host = iniFileOpe.readKeyValue();
			iniFileOpe.setKey("domain");
			String domain = iniFileOpe.readKeyValue();
			
			ActiveDirectory aDirectory = new ActiveDirectory(host, domain);
			aDirectory.setUsername("pl\\test");
			aDirectory.setPassword("pro!ambDa");
			
			if(!aDirectory.validate()){
				return companyUsers;
			}
			
			UserList userList = aDirectory.getUserList("OU=pro-lambda");
			for(User user : userList){
				ScmUser scmUser = new ScmUser(user.getUsername(), user.getId(), -1);
				companyUsers.add(scmUser);
			}

		} 
		catch (Exception e){
			return companyUsers;
		}

		return companyUsers;
	}
	
	public List<ScmUser> getUsersFromSystem(String configRealPath)
	{
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "sysUser", "");
		List<String> userList = iniFileOpe.findBySection();
		
		iniFileOpe.setSection("sysConfig");
		iniFileOpe.setKey("svnRoot");
		String svnRoot = iniFileOpe.readKeyValue();
		
		List<String> adminUserNames = getAdmins("admin", svnRoot);
		
		for(int i = 0; i < userList.size(); i++){
			String[] tpBuffer = userList.get(i).split("::=");
			if(tpBuffer.length >= 2){
				ScmUser scmUser = new ScmUser();
				scmUser.setName(tpBuffer[1]);
				scmUser.setId(tpBuffer[0]);
				
				int k = 0;
				for(k = 0; k < adminUserNames.size(); k++){
					if(tpBuffer[1].equals(adminUserNames.get(k))){
						scmUser.setRole("administrator");
						break;
					}
				}
				
				if(k >= adminUserNames.size()){
					scmUser.setRole("non-adminstrator");
				}
				
				systemUsers.add(scmUser);
			}
		}
		
		return systemUsers;
	}
	
	public List<String> getAdmins(String adminGroup, String svnRoot)
	{
		List<String> retList = new ArrayList<String>();
		String fileName = svnRoot + "\\authz";
		
		IniFileOpe iniFileOpe = new IniFileOpe();
		iniFileOpe.setFileName(fileName);
		iniFileOpe.setSection("groups");
		iniFileOpe.setKey(adminGroup);
		
		String value = iniFileOpe.readKeyValue();
		if(null != value && "" != value){
			String[] tpBuffer = value.split(",");
			for(int i = 0; i < tpBuffer.length; i++){
				retList.add(tpBuffer[i]);
			}
		}
		
		return retList;
	}	
	
	public boolean saveSystemUsers(String configRealPath)
	{
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "sysUser", "");
		
		for(int i = 0; i < systemUsers.size(); i++){
			iniFileOpe.setKey(systemUsers.get(i).getId());
			iniFileOpe.setValue(systemUsers.get(i).getName());
			iniFileOpe.writeKeyValue();
		}
		
		return true;
	}
	
	public boolean addSystemUsers(ScmUser user)
	{
		systemUsers.add(user);
		return true;
	}
	
	public boolean removeSystemUsers(ScmUser user)
	{
		systemUsers.remove(user);
		return true;
	}
	
	public boolean createSystemUsers(ScmUser user, String configRealPath)
	{
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "sysUser", "");
		
		iniFileOpe.setKey(user.getId());
		iniFileOpe.setValue(user.getName());
		if(!iniFileOpe.writeKeyValue()){
			return false;
		}
		
		return true;
	}
	
	public boolean deleteSystemUsers(ScmUser user, String configRealPath)
	{
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "sysUser", "");
		
		iniFileOpe.setKey(user.getId());
		if(!iniFileOpe.deleteKeyValue()){
			return false;
		}
		
		return true;
	}
}
