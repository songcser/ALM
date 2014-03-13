package com.prolambda.scmserv.dal;

import java.util.*;
import java.io.*;

public class SvnCmd 
{
	String sourcePath;
	String destPath;
	String message;
	String arguments;
	
	public SvnCmd(String sourcePath, String destPath, String message, String arguments)
	{
		this.sourcePath = sourcePath;
		this.destPath = destPath;
		this.message = message;
		this.arguments = arguments;
	}
	
	public SvnCmd(String destPath, String message, String arguments)
	{
		this.destPath = destPath;
		this.message = message;
		this.arguments = arguments;
		this.sourcePath = new String("");
	}
	
	public SvnCmd(String destPath, String arguments)
	{
		this.destPath = destPath;
		this.arguments = arguments;
		this.sourcePath = new String("");
		this.message = new String("");
	}
	
	public SvnCmd()
	{
		sourcePath = new String("");
		destPath = new String("");
		message = new String("");
		arguments = new String("");
	}
	
	public String getSourcePath() 
	{
		return sourcePath;
	}
	
	public void setSourcePath(String sourcePath) 
	{
		this.sourcePath = sourcePath;
	}
	
	public String getDestPath() 
	{
		return destPath;
	}
	
	public void setDestPath(String destPath) 
	{
		this.destPath = destPath;
	}
	
	public String getMessage() 
	{
		return message;
	}
	
	public void setMessage(String message) 
	{
		this.message = message;
	}
	
	public String getArguments() {
		return arguments;
	}

	public void setArguments(String arguments) {
		this.arguments = arguments;
	}

	private List<String> exeCmd(String cmd)
	{
		List<String> retList = new ArrayList<String>();
		
		try
		{
			Process pro = Runtime.getRuntime().exec(cmd);
			BufferedReader br = new BufferedReader(new InputStreamReader(pro.getInputStream()));
			
			String str;
			while(( str = br.readLine()) != null)
			{
				retList.add(str);
			}
		}
		catch (IOException e) 
		{
			e.printStackTrace();
		}
		
		return retList;
	}

	//is not fine, because we don't know the arguments what this function needs 
	public List<String> svnAdminCreate()
	{
		List<String> retList;
		
		if(destPath.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("destPath is null");
			return retList;
		}
		
		String cmd = "svnadmin create " + arguments + " \"" + destPath + "\"";
		retList = exeCmd(cmd);
		
		return retList;
	}
	
	public List<String> svnCopy()
	{
		List<String> retList;
		
		if(sourcePath.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("sourcePath is null");
			return retList;
		}
		
		if(destPath.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("destPath is null");
			return retList;
		}		
		
		if(message.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("message is null");
			return retList;
		}
		
		String cmd = "svn copy --non-interactive " + arguments + " -m \"" + message + "\" \"" + sourcePath + "\" \"" + destPath + "\"";
		retList = exeCmd(cmd);
		
		return retList;
	}
	
	public List<String> svnUnlock()
	{
		List<String> retList;
		
		if(destPath.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("destPath is null");
			return retList;
		}
		
		String cmd = "svn unlock --non-interactive " + arguments + " \"" + destPath + "\"";
		retList = exeCmd(cmd);
		
		return retList;
	}
	
	public List<String> svnUnlocks(List<String> urls)
	{
		List<String> retList;
		
		if(urls.size() <= 0){
			retList = new ArrayList<String>();
			retList.add("nothing need to unlock");
			return retList;
		}
		
		String destPath = "";
		for(int i = 0; i < urls.size(); i++){
			destPath += " \"";
			destPath += urls.get(i);
			destPath += "\"";
		}
		
		String cmd = "svn unlock --non-interactive " + arguments + destPath;
		retList = exeCmd(cmd);
		
		return retList;
	}
	
	public List<String> svnDelete()
	{
		List<String> retList;
		
		if(destPath.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("destPath is null");
			return retList;
		}
		
		if(message.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("message is null");
			return retList;
		}
		
		String cmd = "svn delete --non-interactive " + arguments + " -m \"" + message + "\" \"" + destPath + "\"";
		retList = exeCmd(cmd);
		
		return retList;
	}
	
	public List<String> svnDeletes(List<String> urls)
	{
		List<String> retList;
		
		if(urls.size() <= 0){
			retList = new ArrayList<String>();
			retList.add("nothing need to delete");
			return retList;
		}
		
		if(message.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("message is null");
			return retList;
		}
		
		String destPath = "";
		for(int i = 0; i < urls.size(); i++){
			destPath += " \"";
			destPath += urls.get(i);
			destPath += "\"";
		}
		
		String cmd = "svn delete --non-interactive " + arguments + " -m \"" + message + "\"" + destPath;
		retList = exeCmd(cmd);
		
		return retList;
	}
	
	public List<String> svnInfo()
	{
		List<String> retList;
		
		if(destPath.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("destPath is null");
			return retList;
		}
		
		String cmd = "svn info --non-interactive " + arguments + " \"" + destPath + "\"";
		retList = exeCmd(cmd);
		
		return retList;
	}
	
	public List<String> svnImport()
	{
		List<String> retList;
		
		if(sourcePath.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("sourcePath is null");
			return retList;
		}
		
		if(destPath.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("destPath is null");
			return retList;
		}
		
		if(message.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("message is null");
			return retList;
		}
		
		String cmd = "svn import --non-interactive " + arguments + " -m \"" + message + "\" \"" + sourcePath + "\" \"" + destPath + "\"";
		retList = exeCmd(cmd);
		
		return retList;
	}
	
	public List<String> svnList()
	{
		List<String> retList;
		
		if(destPath.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("destPath is null");
			return retList;
		}
		
		String cmd = "svn list --non-interactive " + arguments + " \"" + destPath + "\"";
		retList = exeCmd(cmd);
		
		return retList;
	}
	
	public List<String> svnLog()
	{
		List<String> retList;
		
		if(destPath.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("destPath is null");
			return retList;
		}
		
		String cmd = "svn log --non-interactive " + arguments + " \"" + destPath + "\"";
		retList = exeCmd(cmd);
		
		return retList;
	}
	
	public List<String> svnMkdir()
	{
		List<String> retList;
		
		if(destPath.length() <= 0){
			retList = new ArrayList<String>();
			retList.add("destPath is null");
			return retList;
		}
		
		String cmd = "svn mkdir --non-interactive -m \"" + message + "\" " + arguments + " \"" + destPath + "\"";
		retList = exeCmd(cmd);
		
		return retList;
	}
}
