package com.prolambda.scmserv.entity;

import java.io.UnsupportedEncodingException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;

import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;

import com.prolambda.scmserv.bll.EncrypAES;

public class ScmUser 
{
	String name;
	String password;
	String id;
	int permission;
	String role;
	
	public String getRole()
	{
		return role;
	}

	public void setRole(String role)
	{
		this.role = role;
	}

	public ScmUser(String name, String password, String id, int permission)
	{
		this.name = name;
		this.password = password;
		this.id = id;
		this.permission = permission;
	}
	
	public ScmUser(String name, String id, int permission)
	{
		this.name = name;
		this.password = new String("");
		this.id = id;
		this.permission = permission;
	}
	
	public ScmUser(String name, int permission)
	{
		this.name = name;
		this.password = new String("");
		this.permission = permission;
		this.id = new String("");
	}
	
	public ScmUser(String name)
	{
		this.name = name;
		this.password = new String("");
		this.id = new String("");
		this.permission = -1;
	}
	
	public ScmUser()
	{
		name = new String("");
		password = new String("");
		id = new String("");
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
	
	public String getAESPassword() {
		
		return EncrypAES.AESencrypt(password,name);
	}
	
	public String getPassword() 
	{
		return password;
	}
	
	public void setAESPassword(String password) {
		
		this.password = EncrypAES.AESdecrypt(password,name); 
		//System.out.println("Password: "+password);
	}
	
	public void setPassword(String password) 
	{
		this.password = password;
	}
	
	public String getId() 
	{
		return id;
	}
	
	public void setId(String id) 
	{
		this.id = id;
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
