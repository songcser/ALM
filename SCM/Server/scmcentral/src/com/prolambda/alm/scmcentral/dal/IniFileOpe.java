package com.prolambda.alm.scmcentral.dal;

import java.util.*;
import java.io.*;

import ch.ubique.inieditor.IniEditor;

public class IniFileOpe
{
	String fileName;
	String section;
	String key;
	String value;
	
	public IniFileOpe(String fileName, String section, String key)
	{
		this.fileName = fileName;
		this.section = section;
		this.key = key;
		this.value = new String("");
	}
	
	public IniFileOpe(String fileName, String section, String key, String value)
	{
		this.fileName = fileName;
		this.section = section;
		this.key = key;
		this.value = value;
	}
	
	public IniFileOpe(String fileName, String key)
	{
		this.fileName = fileName;
		this.key = key;
		this.section = new String("");
		this.value = new String("");
	}
	
	public IniFileOpe()
	{
		fileName = new String("");
		section = new String("");
		key = new String("");
		value = new String("");
	}
	
	public String getFileName()
	{
		return fileName;
	}
	
	public void setFileName(String fileName)
	{
		this.fileName = fileName;
	}
	
	public String getSection() 
	{
		return section;
	}
	
	public void setSection(String section) 
	{
		this.section = section;
	}
	
	public String getKey() 
	{
		return key;
	}
	
	public void setKey(String key) 
	{
		this.key = key;
	}
	
	public String getValue()
	{
		return value;
	}
	
	public void setValue(String value)
	{
		this.value = value;
	}

	//is not fine, because we don't know the arguments what this function needs
	@SuppressWarnings("unchecked")
	public List<String> findBySection()
	{
		List<String> retList = new ArrayList<String>();;
		
		if(fileName.length() <= 0){
			retList.add("000001::=fileName is null");
			return retList;
		}
		
		if(section.length() <= 0){
			retList.add("000002::=section is null");
			return retList;
		}
		
		try{
			IniEditor iniEditor = new IniEditor();
			iniEditor.load(new File(fileName));
			
			if(!iniEditor.hasSection(section)){
				return retList;
			}
			
			List<String> optionList = iniEditor.optionNames(section);
			for(int i = 0; i < optionList.size(); i++){
				String key = optionList.get(i);
				String value = iniEditor.get(section, key);
				if(null == value){
					value = new String("");
				}
				retList.add(key + "::=" + value);
			}
		}
		catch(IOException ex){
			retList.add("000004::=load file failed");
		}
		
		return retList;
	}
	
	@SuppressWarnings("unchecked")
	public List<String> findByKey()
	{
		List<String> retList = new ArrayList<String>();
		
		if(fileName.length() <= 0){
			retList.add("000001::=fileName is null");
			return retList;
		}
		
		if(key.length() <= 0){
			retList.add("000003::=key is null");
			return retList;
		}
		
		try{
			IniEditor iniEditor = new IniEditor();
			iniEditor.load(new File(fileName));
			
			List<String> sectionList = iniEditor.sectionNames();
			for(int i = 0; i < sectionList.size(); i++){
				String section = sectionList.get(i);
				String value = iniEditor.get(section, key);
				if(null != value){
					retList.add(section + "::=" + value);
				}
			}
		}
		catch(IOException ex){
			retList.add("000004::=load file failed");
		}
		
		return retList;
	}
	
	public boolean writeKeyValue()
	{
		if(fileName.length() <= 0 || section.length() <= 0){
			return false;
		}
		
		if(key.length() <= 0 || value.length() <= 0){
			return false;
		}
		
		try{
			IniEditor iniEditor = new IniEditor();
			iniEditor.load(fileName);
			if(!iniEditor.hasSection(section)){
				iniEditor.addSection(section);
			}
			iniEditor.set(section, key, value);
			iniEditor.save(fileName);
		}
		catch(IOException ex){
			return false;
		}
		
		return true;
	}
	
	public boolean deleteKeyValue()
	{
		if(fileName.length() <= 0 || section.length() <= 0){
			return false;
		}
		
		if(key.length() <= 0){
			return false;
		}
		
		try{
			IniEditor iniEditor = new IniEditor();
			iniEditor.load(fileName);
			
			if(!iniEditor.hasOption(section, key)){
				return false;
			}
			
			iniEditor.remove(section, key);
			iniEditor.save(fileName);
		}
		catch(IOException ex){
			return false;
		}
		
		return true;
	}

	public String readKeyValue()
	{
		if(fileName.length() <= 0 || section.length() <= 0){
			value = "";
			return value;
		}
		
		if(key.length() <= 0){
			value = "";
			return value;
		}
		
		try{
			IniEditor iniEditor = new IniEditor();
			iniEditor.load(fileName);
			value = iniEditor.get(section, key);
		}
		catch(IOException ex){
			value = "";
			return value;
		}
		
		return value;
	}
	
	public boolean hasSection()
	{
		if(fileName == null || section == null){
			return false;
		}
		
		if(fileName.length() <= 0 || section.length() <= 0){
			return false;
		}
		
		try{
			IniEditor iniEditor = new IniEditor();
			iniEditor.load(fileName);
			if(iniEditor.hasSection(section)){
				return true;
			}
			else{
				return false;
			}
		}
		catch(IOException ex){
			return false;
		}
	}
	
	public boolean hasOption()
	{
		if(fileName == null || section == null || key == null){
			return false;
		}
		
		if(fileName.length() <= 0 || section.length() <= 0 || key.length() <= 0){
			return false;
		}
		
		try{
			IniEditor iniEditor = new IniEditor();
			iniEditor.load(fileName);
			if(iniEditor.hasOption(section, key)){
				return true;
			}
			else{
				return false;
			}
		}
		catch(IOException ex){
			return false;
		}
	}
	
	@SuppressWarnings("unchecked")
	public List<String> getAllSections()
	{
		List<String> retList = null;
		if(fileName == null || fileName.length() <= 0){
			retList = new ArrayList<String>();
			return retList;
		}
		
		try{
			IniEditor iniEditor = new IniEditor();
			iniEditor.load(fileName);
			retList = iniEditor.sectionNames();
			if(retList == null){
				retList = new ArrayList<String>();
			}
		}
		catch(IOException ex){
			retList = new ArrayList<String>();
			return retList;
		}
		
		return retList;
	}
	
	@SuppressWarnings("unchecked")
	public List<String> getAllOptions()
	{
		List<String> retList = null;
		if(fileName == null || fileName.length() <= 0){
			retList = new ArrayList<String>();
			return retList;
		}
		
		if(section == null || section.length() <= 0){
			retList = new ArrayList<String>();
			return retList;
		}
		
		try{
			IniEditor iniEditor = new IniEditor();
			iniEditor.load(fileName);
			retList = iniEditor.optionNames(section);
			if(retList == null){
				retList = new ArrayList<String>();
			}
		}
		catch(IOException ex){
			retList = new ArrayList<String>();
			return retList;
		}
		
		return retList;
	}
}













