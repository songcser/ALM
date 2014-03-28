package com.prolambda.controller;

import com.prolambda.dal.UserDAL;
import com.prolambda.model.PDMUser;
import com.prolambda.model.PDMUserList;

public class UserService {
	
	public Boolean isExist(String userId){
		UserDAL userDAL = new UserDAL();
		return userDAL.isExist(userId);
	}
	
	public PDMUserList getUser(){
		UserDAL userDAL = new UserDAL();
		return userDAL.getUser();
	}
	
	public void addUser(PDMUser user){
		UserDAL userDAL = new UserDAL();
		userDAL.addUser(user);
	}
	
	public void removeUser(String name){
		UserDAL userDAL = new UserDAL();
		userDAL.removeUser(name);
	}
	
	public void setBuilder(String name,String password){
		UserDAL userDAL = new UserDAL();
		userDAL.setBuilder(name,password);
	}
	
	public String getBuilderName(){
		UserDAL userDAL = new UserDAL();
		return userDAL.getBuilderName();
	}
	
	public String getBuilderPassword(){
		UserDAL userDAL = new UserDAL();
		return userDAL.getBuilderPassword();
	}
	
	public Boolean addFirstUser(String name,String userId){
		UserDAL userDAL = new UserDAL();
		return userDAL.addFirstUser(name,userId);
	}
}
