package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;

import com.prolambda.model.ComponentCategory;
import com.prolambda.model.ComponentCategoryList;
import com.prolambda.model.Database;

public class ComponentCategoryDAL {
	public Boolean create(ComponentCategory comCategory){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String name = comCategory.getName();
			Timestamp created = comCategory.getCreated();
			String description = comCategory.getDescription();
			Timestamp modified = comCategory.getModified();
			int componentCount = comCategory.getComponentCount();
			String sql = "insert into t_ccategory(name,description,created,modified,componentCount)" +
					" values('"+name+"','"+description+"','"+created+"','"+modified+"','"+componentCount+"')";
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
	public Boolean delete(int id){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_ccategory where id = '"+id+"'";
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
	
	public Boolean delete(String name){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_ccategory where name = '"+name+"'";
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
	
	public Boolean update(ComponentCategory comCategory){
		
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			//rs = st.executeQuery("select * from t_repository");
			int id = comCategory.getId();
			String name = comCategory.getName();
			String description = comCategory.getDescription();
			Timestamp created = comCategory.getCreated();
			Timestamp modified = comCategory.getModified();
			//int productCount = proCategory.getProductCount();
			String sql = "update t_ccategory set name = '"+name+"', description = '"+description+"', created = '"+created+"', modified = '"+modified+"' where id = '"+id+"'";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
			   try{
			//	   rs.close();
				   st.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
		return true;
	}
	
	public ComponentCategoryList getAll(){
		ComponentCategoryList comCategoryList = new ComponentCategoryList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_ccategory");
			
			while(rs.next())
			{
				ComponentCategory comCategory = new ComponentCategory();
				int id = rs.getInt(1);
				comCategory.setId(id);
				String name = rs.getString(2);
				comCategory.setName(name);
				String description = rs.getString(3);
				comCategory.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				comCategory.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				comCategory.setModified(modified);
				int componentCount = rs.getInt(6);
				comCategory.setComponentCount(componentCount);
				
				comCategoryList.add(comCategory);
				
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
		return comCategoryList;
	}
	
	public ComponentCategory getById(int id){
		ComponentCategory comCategory = new ComponentCategory();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_ccategory where id = '"+id+"'");
			
			while(rs.next())
			{
				//ComponentCategory comCategory = new ComponentCategory();
				//int id = rs.getInt(1);
				comCategory.setId(id);
				String name = rs.getString(2);
				comCategory.setName(name);
				String description = rs.getString(3);
				comCategory.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				comCategory.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				comCategory.setModified(modified);
				int componentCount = rs.getInt(6);
				comCategory.setComponentCount(componentCount);
				
				//comCategoryList.add(comCategory);
				
			}
		} catch (SQLException e) {
			
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
		return comCategory;
	}
	
	public ComponentCategory getByName(String name){
		ComponentCategory comCategory = new ComponentCategory();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_ccategory where name = '"+name+"'");
			
			while(rs.next())
			{
				//ComponentCategory comCategory = new ComponentCategory();
				int id = rs.getInt(1);
				comCategory.setId(id);
				//String name = rs.getString(2);
				comCategory.setName(name);
				String description = rs.getString(3);
				comCategory.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				comCategory.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				comCategory.setModified(modified);
				int componentCount = rs.getInt(6);
				comCategory.setComponentCount(componentCount);
				
				//comCategoryList.add(comCategory);
				
			}
		} catch (SQLException e) {
			
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
		return comCategory;
	}
	
	public Boolean contains(String name){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_ccategory where name = '"+name+"'");
			
			if(!rs.next())
			{
				return false;
			}
		} catch (SQLException e) {
			
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
		return true;
	}
}
