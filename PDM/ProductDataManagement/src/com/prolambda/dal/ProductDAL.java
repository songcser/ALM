package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;

import com.prolambda.model.Database;
import com.prolambda.model.Product;
import com.prolambda.model.ProductList;

public class ProductDAL {
	public Boolean create(Product pro){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			/*rs = st.executeQuery("select * from t_repository");
			String countSql = "select count(id) from t_repository";
			rs = st.executeQuery(countSql);
			String count = rs.getString(1);
			String id = Integer.parseInt(count)+"";
			*/
			String name = pro.getName();
			Timestamp created = pro.getCreated();
			String description = pro.getDescription();
			Timestamp modified = pro.getModified();
			String lastVersion = pro.getLastVersion();
			int categoryId = pro.getCategoryId();
			int state = pro.getState();
			String sql = "insert into t_product(name,description,created,modified,lastVersion,categoryid,state)" +
					" values('"+name+"','"+description+"','"+created+"','"+modified+"','"+lastVersion+"','"+categoryId+"','"+state+"')";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
			sql = "update t_pcategory set productCount = productCount + 1 where id = '"+categoryId+"'";
			
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
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			int categoryid = 0;
			String sql = "select categoryid from t_product where id = '"+id+"'";
			rs = st.executeQuery(sql);
			if(rs.next()){
				categoryid = rs.getInt(1);
			}
			
			sql = "delete from t_product where id = '"+id+"'";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
			sql = "update t_pcategory set productCount = productCount - 1 where id = '"+categoryid+"'";
			
			i=st.executeUpdate(sql);
			if(i!=1)
				return false;
			
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
	
	public Boolean update(Product pro){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			//rs = st.executeQuery("select * from t_repository");
			int id = pro.getId();
			String name = pro.getName();
			String description = pro.getDescription();
			Timestamp created = pro.getCreated();
			Timestamp modified = pro.getModified();
			//int productCount = proCategory.getProductCount();
			String sql = "update t_product set name = '"+name+"', " +
					"description = '"+description+"', created = '"+created+"', modified = '"+modified+"' where id = '"+id+"'";
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
	
	public ProductList getAll(int categoryId){
		ProductList proList = new ProductList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_product where categoryId = '"+categoryId+"'");
			
			while(rs.next())
			{
				Product pro= new Product();
				int id = rs.getInt(1);
				pro.setId(id);
				String name = rs.getString(2);
				pro.setName(name);
				String description = rs.getString(3);
				pro.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				pro.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				pro.setModified(modified);
				String lastVersion = rs.getString(6);
				pro.setLastVersion(lastVersion);
				//int categoryId = rs.getInt(6);
				pro.setCategoryId(categoryId);
				int state = rs.getInt(8);
				pro.setState(state);
				
				proList.add(pro);
				
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
		return proList;
	}
	
	public Product getById(int id){
		Product pro = new Product();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_product where id = '"+id+"'");
			
			if(rs.next())
			{
				pro.setId(id);
				String name = rs.getString(2);
				pro.setName(name);
				String description = rs.getString(3);
				pro.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				pro.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				pro.setModified(modified);
				String lastVersion = rs.getString(6);
				pro.setLastVersion(lastVersion);
				int categoryId = rs.getInt(7);
				pro.setCategoryId(categoryId);
				int state = rs.getInt(8);
				pro.setState(state);

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
		return pro;
	}
	
	public Boolean contains(String categoryName,String productName){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_pcategory where name = '"+categoryName+"'");
			if(rs.next()){
				int categoryId = rs.getInt(1);
				rs = st.executeQuery("select id from t_product where name = '"+productName+"' and categoryid = '"+categoryId+"'");
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
	
	public int getIdByName(String categoryName,String productName){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_pcategory where name = '"+categoryName+"'");
			if(rs.next()){
				int categoryId = rs.getInt(1);
				rs = st.executeQuery("select id from t_product where name = '"+productName+"' and categoryid = '"+categoryId+"'");
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
	
	
}
