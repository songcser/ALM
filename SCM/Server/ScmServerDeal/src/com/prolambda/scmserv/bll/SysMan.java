package com.prolambda.scmserv.bll;

import com.prolambda.scmserv.entity.*;
import com.prolambda.scmserv.dal.*;

import java.io.*;
import java.util.*;

public class SysMan 
{
	String svnRoot;
	String serverURL;
	String recycleBin;
	String svnConfig;
	
	public SysMan()
	{
		svnRoot = new String("");
		serverURL = new String("");
		svnConfig = new String("");
	}
	
	public SysMan(String svnRoot, String serverURL)
	{
		this.svnRoot = svnRoot;
		this.serverURL = serverURL;
	}
	
	public String getSvnRoot()
	{
		return svnRoot;
	}
	
	public void setSvnRoot(String svnRoot)
	{
		this.svnRoot = svnRoot;
	}
	
	public String getServerURL(){
		return serverURL;
	}
	
	public void setServerURL(String serverURL)
	{
		this.serverURL = serverURL;
	}
	
	public String getRecycleBin(){
		return recycleBin;
	}
	public void setRecycleBin(String recycle){
		this.recycleBin = recycle;
	}
	public String getSvnConfig()
	{
		return svnConfig;
	}
	
	public void setSvnConfig(String svnConfig)
	{
		this.svnConfig = svnConfig;
	}
	
	public boolean isFirstRun()
	{
		Properties prop = System.getProperties();
		String os = prop.getProperty("os.name");
		String osUser = prop.getProperty("user.name");
		
		if(os.equals("Windows XP")){
			svnConfig = "C:\\Documents and Settings\\" + osUser + "\\Application Data\\Subversion\\auth\\svn.simple";
		}
		else if(os.equals("Windows 7")){
			svnConfig = "C:\\Users\\" + osUser + "\\AppData\\Roaming\\Subversion\\auth\\svn.simple";
		}
		else{
			return true;
		}
		
		File file = new File(svnConfig);
		if(file.exists()){
			return false;
		}
	
		return true;
	}
	
	public boolean configSvn(ScmUser user, String depos)
	{
		String destPath = serverURL + "/" + depos;
		String arguments = "--username " + user.getName() + " --password " + user.getPassword();
		SvnCmd infoCmd = new SvnCmd(destPath, arguments);
		List<String> tpList = infoCmd.svnInfo();
		
		if((tpList.size() <= 0) || (0 == tpList.get(0).indexOf("svn: "))){
			return false;
		}
		
		return true;
	}
	
	public boolean saveSvnRoot(String configRealPath, ScmUser lastLogin)
	{
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "sysConfig", "svnRoot", svnRoot);
		if(!iniFileOpe.writeKeyValue()){
			return false;
		}
		
		iniFileOpe.setFileName(svnRoot+"\\authz");
		iniFileOpe.setSection("groups");
		iniFileOpe.setKey("admin");
		String members = iniFileOpe.readKeyValue();
		
		if(members != null && !members.equals("")){
			String[] tMembers = members.split(",");
			int j = 0;
			for(j = 0; j < tMembers.length; j++){
				if(lastLogin.getName().equals(tMembers[j])){
					break;
				}
			}
			
			if(j == tMembers.length){
				iniFileOpe.setValue(members+","+lastLogin.getName());
				iniFileOpe.writeKeyValue();
			}
			else{
				iniFileOpe.setValue(members);
				iniFileOpe.writeKeyValue();
			}
		}
		else{
			iniFileOpe.setValue(lastLogin.getName());
			iniFileOpe.writeKeyValue();
		}
		
		return true;
	}
	
	public String readSvnRoot(String configRealPath)
	{
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "sysConfig", "svnRoot");
		svnRoot = iniFileOpe.readKeyValue();
		
		return svnRoot;
	}
	
	public boolean saveServerURL(String configRealPath)
	{
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "sysConfig", "serverURL", serverURL);
		if(!iniFileOpe.writeKeyValue()){
			return false;
		}
		
		return true;
	}
	
	public boolean saveRecycleBin(String configRealPath){
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath,"sysConfig","recycleBin",recycleBin);
		if(!iniFileOpe.writeKeyValue()){
			return false;
		}
		return true;
	}
	
	public String readServerURL(String configRealPath)
	{
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "sysConfig", "serverURL");
		serverURL = iniFileOpe.readKeyValue();
		
		return serverURL;
	}
	
	public String readRecycleBin(String configRealPath){
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath,"sysConfig","recycleBin");
		recycleBin = iniFileOpe.readKeyValue();
		return recycleBin;
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
	
	public boolean setAdmin(String adminUser, String svnRoot)
	{
		String fileName = svnRoot + "\\authz";
		
		IniFileOpe iniFileOpe = new IniFileOpe();
		iniFileOpe.setFileName(fileName);
		iniFileOpe.setSection("groups");
		iniFileOpe.setKey("admin");
		
		String value = iniFileOpe.readKeyValue();
		if(null != value){
			value = value.trim();
		}
		if(null != value && !value.equals("")){
			String[] tpBuffer = value.split(",");
			int i = 0;
			for(i = 0; i < tpBuffer.length; i++){
				if(tpBuffer[i].equals(adminUser)){
					break;
				}
			}
			
			if(i >= tpBuffer.length){
				value = value + "," + adminUser;
			}
			
			iniFileOpe.setValue(value);
			iniFileOpe.writeKeyValue();
		}
		else{
			iniFileOpe.setValue(adminUser);
			iniFileOpe.writeKeyValue();
		}
		
		return true;
	}
	
	public boolean setAdmins(List<String> adminUsers, String svnRoot)
	{
		String fileName = svnRoot + "\\authz";
		
		IniFileOpe iniFileOpe = new IniFileOpe();
		iniFileOpe.setFileName(fileName);
		iniFileOpe.setSection("groups");
		iniFileOpe.setKey("admin");
		
		String value = iniFileOpe.readKeyValue();
		if(null != value){
			value = value.trim();
		}
		if(null != value && !value.equals("")){
			String[] tpBuffer = value.split(",");
			for(int k = 0; k < adminUsers.size(); k++){
				int i = 0;
				for(i = 0; i < tpBuffer.length; i++){
					if(tpBuffer[i].equals(adminUsers.get(k))){
						break;
					}
				}
				
				if(i >= tpBuffer.length){
					value = value + "," + adminUsers.get(k);
				}
			}
			
			iniFileOpe.setValue(value);
			iniFileOpe.writeKeyValue();
		}
		else{
			value = "";
			for(int k = 0; k < adminUsers.size(); k++){
				value += adminUsers.get(k);
				if(k < adminUsers.size()-1){
					value += ",";
				}
			}
			iniFileOpe.setValue(value);
			iniFileOpe.writeKeyValue();
		}
		
		return true;
	}
	
	public boolean cancelAdmin(String adminUser, String svnRoot)
	{
		String fileName = svnRoot + "\\authz";
		
		IniFileOpe iniFileOpe = new IniFileOpe();
		iniFileOpe.setFileName(fileName);
		iniFileOpe.setSection("groups");
		iniFileOpe.setKey("admin");
		
		String value = iniFileOpe.readKeyValue();
		if(null != value){
			value = value.trim();
		}
		if(value != null && !value.equals("")){
			String[] tpBuffer = value.split(",");
			String tvalue = "";
			for(int i = 0; i < tpBuffer.length; i++){
				if(!tpBuffer[i].equals(adminUser)){
					tvalue += tpBuffer[i] + ",";
				}
			}
			
			if(tvalue == ""){
				value = " ";
			}
			else{
				value = tvalue.substring(0, tvalue.length()-1);
			}
			
			iniFileOpe.setValue(value);
			iniFileOpe.writeKeyValue();
		}
		
		return true;
	}
	
	public boolean cancelAdmins(List<String> adminUsers, String svnRoot)
	{
		String fileName = svnRoot + "\\authz";
		
		IniFileOpe iniFileOpe = new IniFileOpe();
		iniFileOpe.setFileName(fileName);
		iniFileOpe.setSection("groups");
		iniFileOpe.setKey("admin");
		
		String value = iniFileOpe.readKeyValue();
		if(null != value){
			value = value.trim();
		}
		if(value != null && !value.equals("")){
			String[] tpBuffer = value.split(",");
			String tvalue = "";
			for(int i = 0; i < tpBuffer.length; i++){
				int k = 0;
				for(k = 0; k < adminUsers.size(); k++){
					if(tpBuffer[i].equals(adminUsers.get(k))){
						break;
					}
				}
				
				if(k >= adminUsers.size()){
					tvalue += tpBuffer[i] + ",";
				}
			}
			
			if(tvalue == ""){
				value = " ";
			}
			else{
				value = tvalue.substring(0, tvalue.length()-1);
			}
			
			iniFileOpe.setValue(value);
			iniFileOpe.writeKeyValue();
		}
		
		return true;
	}
}











