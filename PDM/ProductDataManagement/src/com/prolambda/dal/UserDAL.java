package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import com.prolambda.model.Database;
import com.prolambda.model.PDMUser;
import com.prolambda.model.PDMUserList;

public class UserDAL {
	
	public void addUser(PDMUser user){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		if(isExist(user.getUserId())){
			return;
		}
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			st.executeUpdate("insert into t_user(userid,name) values('"+user.getUserId()+"','"+user.getName()+"')");
			
		}catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
			   try{
				   //rs.close();
				   st.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public Boolean isExist(String userId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_user where userId = '"+userId+"'");
			
			if(rs.next()){
				return true;
			}
		}catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
			   try{
				   rs.close();
				   st.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
		return false;
	}
	
	public PDMUserList getUser(){
		PDMUserList userList = new PDMUserList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_user");
			
			while(rs.next())
			{
				PDMUser user = new PDMUser();
				user.setId(rs.getInt(1));
				user.setUserId(rs.getString(2));
				user.setName(rs.getString(3));
				userList.add(user);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
			   try{
				   rs.close();
				   st.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
		return userList;
	}

}
