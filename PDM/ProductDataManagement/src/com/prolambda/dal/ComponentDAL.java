package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;

import com.prolambda.model.Component;
import com.prolambda.model.ComponentList;
import com.prolambda.model.Database;

public class ComponentDAL {
	public Boolean create(Component com){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String name = com.getName();
			Timestamp created = com.getCreated();
			Timestamp modified = com.getModified();
			String description = com.getDescription();
			String version = com.getLastVersion();
			int categoryId = com.getCategoryId();
			String sql = "insert into t_component(name,description,created,modified,lastversion,categoryId)" +
					" values('"+name+"','"+description+"','"+created+"','"+modified+"','"+version+"','"+categoryId+"')";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
			sql = "update t_ccategory set componentCount = componentCount + 1 where id = '"+categoryId+"'";
			
			i=st.executeUpdate(sql);
			if(i!=1)
				return false;
			
		} catch (SQLException e) {
		
			e.printStackTrace();
		}finally{
			   try{
				  // rs.close();
				   st.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
		return true;
	}
	
	public Boolean delete(int id){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_component where id = '"+id+"'";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
		} catch (SQLException e) {
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
		return true;
	}
	
	public Boolean update(Component com){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			int id = com.getId();
			String name = com.getName();
			Timestamp created = com.getCreated();
			Timestamp modified = com.getModified();
			String description = com.getDescription();
			//String type = com.getType();
			//String version = com.getVersion();
			//int categoryId = com.getCategoryId();
			String sql = "update t_component set name = '"+name+"' , description = '"+description+"', created = '"+created+"', modified = '"+modified+"' where id = '"+id+"'";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
		} catch (SQLException e) {
		
			e.printStackTrace();
		}finally{
			   try{
				  // rs.close();
				   st.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
		return true;
	}
	
	public ComponentList getAll(int categoryId){
		ComponentList comList = new ComponentList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_component where categoryId='"+categoryId+"'");
			
			while(rs.next())
			{
				Component com= new Component();
				int id = rs.getInt(1);
				com.setId(id);
				String name = rs.getString(2);
				com.setName(name);
				String description = rs.getString(3);
				com.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				com.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				com.setModified(modified);
				String version = rs.getString(6);
				com.setLastVersion(version);
				//int categoryId = rs.getInt(6);
				com.setCategoryId(categoryId);
				
				comList.add(com);
				
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
		return comList;
	}
	
	public Component getById(int id){
		Component com = new Component();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_component where id = '"+id+"'");
			
			while(rs.next())
			{
				//Component com= new Component();
				//int id = rs.getInt(1);
				com.setId(id);
				String name = rs.getString(2);
				com.setName(name);
				String description = rs.getString(3);
				com.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				com.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				com.setModified(modified);
				String version = rs.getString(6);
				com.setLastVersion(version);
				int categoryId = rs.getInt(7);
				com.setCategoryId(categoryId);
				
				//comList.add(com);
				
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
		return com;
	}
	
	public int getIdByName(String categoryName,String componentName){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_ccategory where name = '"+categoryName+"'");
			if(rs.next()){
				int categoryId = rs.getInt(1);
				rs = st.executeQuery("select id from t_component where name = '"+componentName+"' and categoryid = '"+categoryId+"'");
				if(rs.next()){
					return rs.getInt(1);
				}
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
		return -1;
	}
	
	public Boolean contains(String categoryName,String componentName){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_ccategory where name = '"+categoryName+"'");
			if(rs.next()){
				int categoryId = rs.getInt(1);
				rs = st.executeQuery("select id from t_component where name = '"+componentName+"' and categoryid = '"+categoryId+"'");
				if(rs.next()){
					return true;
				}
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
		return false;
	}
}
