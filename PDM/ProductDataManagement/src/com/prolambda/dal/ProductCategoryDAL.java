package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;

import com.prolambda.model.Database;
import com.prolambda.model.ProductCategory;
import com.prolambda.model.ProductCategoryList;

public class ProductCategoryDAL {
	public Boolean create(ProductCategory proCategory){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String name = proCategory.getName();
			Timestamp created = proCategory.getCreated();
			String description = proCategory.getDescription();
			Timestamp modified = proCategory.getModified();
			int productCount = proCategory.getProductCount();
			String sql = "insert into t_pcategory(name,description,created,modified,productCount)" +
					" values('"+name+"','"+description+"','"+created+"','"+modified+"','"+productCount+"')";
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
			String sql = "delete from t_pcategory where id = '"+id+"'";
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
			String sql = "delete from t_pcategory where name = '"+name+"'";
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
	
	public Boolean update(ProductCategory proCategory){
		
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			//rs = st.executeQuery("select * from t_repository");
			int id = proCategory.getId();
			String name = proCategory.getName();
			String description = proCategory.getDescription();
			Timestamp created = proCategory.getCreated();
			Timestamp modified = proCategory.getModified();
			//int productCount = proCategory.getProductCount();
			String sql = "update t_pcategory set name = '"+name+"', description = '"+description+"', created = '"+created+"', modified = '"+modified+"' where id = '"+id+"'";
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
	
	public ProductCategoryList getAll(){
		ProductCategoryList proCategoryList = new ProductCategoryList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_pcategory");
			
			while(rs.next())
			{
				ProductCategory proCategory = new ProductCategory();
				int id = rs.getInt(1);
				proCategory.setId(id);
				String name = rs.getString(2);
				proCategory.setName(name);
				String description = rs.getString(3);
				proCategory.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				proCategory.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				proCategory.setModified(modified);
				int productCount = rs.getInt(6);
				proCategory.setProductCount(productCount);
				
				proCategoryList.add(proCategory);
				
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
		return proCategoryList;
	}
	
	public ProductCategory getById(int id){
		ProductCategory proCategory = new ProductCategory();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_pcategory where id='"+id+"'");
			
			if(rs.next())
			{
				//ProductCategory proCategory = new ProductCategory();
				//int id = rs.getInt(1);
				proCategory.setId(id);
				String name = rs.getString(2);
				proCategory.setName(name);
				String description = rs.getString(3);
				proCategory.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				proCategory.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				proCategory.setModified(modified);
				int productCount = rs.getInt(6);
				proCategory.setProductCount(productCount);
				
				//proCategoryList.add(proCategory);
				
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
		return proCategory;
	}
	
	public ProductCategory getByName(String name){
		ProductCategory proCategory = new ProductCategory();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		
		//String temp = name.replace('*', ' ');
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_pcategory where name='"+name+"'");
			
			if(rs.next())
			{
				//ProductCategory proCategory = new ProductCategory();
				int id = rs.getInt(1);
				proCategory.setId(id);
				//String name = rs.getString(2);
				proCategory.setName(name);
				String description = rs.getString(3);
				proCategory.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				proCategory.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				proCategory.setModified(modified);
				int productCount = rs.getInt(6);
				proCategory.setProductCount(productCount);
				
				//proCategoryList.add(proCategory);
				
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
		return proCategory;
	}
	
	public Boolean contains(String name){
		
		//ProductCategory proCategory = new ProductCategory();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_pcategory where name='"+name+"'");
			
			if(!rs.next())
			{
				return false;
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
		return true;
	}
}
