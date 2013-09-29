package com.prolambda.alm.scmcentral.bll;

import java.util.*;

import com.prolambda.alm.scmcentral.dal.IniFileOpe;
import com.prolambda.alm.scmcentral.entity.*;
import com.prolambda.webmatrix.directory.ActiveDirectory;

public class Login 
{
	ScmUser user;
	
	public Login(ScmUser user)
	{
		this.user = user;
	}
	
	public Login()
	{
		user = new ScmUser();
	}

	public ScmUser getUser()
	{
		return user;
	}

	public void setUser(ScmUser user)
	{
		this.user = user;
	}
	
	public int userFirstLogin(List<ScmUser> companyUsers, String configRealPath, int Flag)
	{
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "sysConfig", "host");
		String host = iniFileOpe.readKeyValue();
		iniFileOpe.setKey("domain");
		String domain = iniFileOpe.readKeyValue();
		
		String name = user.getName();
		String password = user.getPassword();
		
		ActiveDirectory aDirectory = new ActiveDirectory(host, domain);
		aDirectory.setUsername("pl\\" + name);
		aDirectory.setPassword(password);
		
		if(aDirectory.validate()){
			if(1 == Flag){
				iniFileOpe.setSection("lastLogin");
				iniFileOpe.setKey("name");
				iniFileOpe.setValue(name);
				iniFileOpe.writeKeyValue();
				iniFileOpe.setKey("password");
				iniFileOpe.setValue(password);
				iniFileOpe.writeKeyValue();
			}
			
			iniFileOpe.setSection("sysConfig");
			iniFileOpe.setKey("svnRoot");
			String svnRoot = iniFileOpe.readKeyValue();
			
			iniFileOpe.setSection("sysUser");
			for(int i = 0; i < companyUsers.size(); i++){
				String[] tBuffer = companyUsers.get(i).getName().split("@");
				String tName = new String("");
				if(tBuffer.length >= 1){
					tName = tBuffer[0];
				}
				if(tName.equals(user.getName())){
					iniFileOpe.setKey(companyUsers.get(i).getId());
					iniFileOpe.setValue(user.getName());
					iniFileOpe.writeKeyValue();
					break;
				}
			}
			
			iniFileOpe.setFileName(svnRoot+"\\authz");
			iniFileOpe.setSection("groups");
			iniFileOpe.setKey("admin");
			String members = iniFileOpe.readKeyValue();
			
			if(members != null && !members.equals("")){
				String[] tMembers = members.split(",");
				int j = 0;
				for(j = 0; j < tMembers.length; j++){
					if(user.getName().equals(tMembers[j])){
						break;
					}
				}
				
				if(j == tMembers.length){
					iniFileOpe.setValue(members+","+user.getName());
					iniFileOpe.writeKeyValue();
				}
				else{
					iniFileOpe.setValue(members);
					iniFileOpe.writeKeyValue();
				}
			}
			else{
				iniFileOpe.setValue(user.getName());
				iniFileOpe.writeKeyValue();
			}
			
			return 0;
		}
		else{
			return -2;
		}
		
	}
	
	public int userLogin(List<ScmUser> sysUsers, String configRealPath, int Flag)
	{
		if(sysUsers.size() <= 0){
			return -3;
		}
		
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "sysConfig", "host");
		String host = iniFileOpe.readKeyValue();
		iniFileOpe.setKey("domain");
		String domain = iniFileOpe.readKeyValue();
		
		String name = user.getName();
		String password = user.getPassword();
		for(int i = 0; i < sysUsers.size(); i++){
			if(name.equals(sysUsers.get(i).getName())){
				ActiveDirectory aDirectory = new ActiveDirectory(host, domain);
				aDirectory.setUsername("pl\\" + name);
				aDirectory.setPassword(password);
				
				if(aDirectory.validate()){
					if(1 == Flag){
						iniFileOpe.setSection("lastLogin");
						iniFileOpe.setKey("name");
						iniFileOpe.setValue(name);
						iniFileOpe.writeKeyValue();
						iniFileOpe.setKey("password");
						iniFileOpe.setValue(password);
						iniFileOpe.writeKeyValue();
					}
					
					return 0;
				}
				else{
					return -2;
				}
			}
		}
		
		return -1;
	}
	
	public ScmUser getLastLogin(String configRealPath)
	{
		ScmUser user = new ScmUser();
		
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "lastLogin", "name");
		String name = iniFileOpe.readKeyValue();
		iniFileOpe.setKey("password");
		String password = iniFileOpe.readKeyValue();
		
		user.setName(name);
		user.setPassword(password);
		
		return user;
	}
}
