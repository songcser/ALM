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
}
