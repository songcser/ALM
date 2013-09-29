package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import com.prolambda.model.Database;
import com.prolambda.model.Library;
import com.prolambda.model.LibraryList;

public class LibraryDAL {
	
//	int pageSize = 5;
//	int rowCount = 0;
//	int pageCount = 0;

	public Boolean create(Library lib)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			/*rs = st.executeQuery("select * from t_repository");
			String countSql = "select count(id) from t_library";
			rs = st.executeQuery(countSql);
			String cou = rs.getString(1);
			String id = Integer.parseInt(cou)+"";
			*/
			String name = lib.getName();
			String description = lib.getDescription();
			String type = lib.getType();
			int buildId = lib.getBuildId();
			int componentId = lib.getComponentId();
			int productId = lib.getProductId();
			String fileName = lib.getFileName();
			String sql = "insert into t_library(name,description,type,fileName,buildid,componentId,productId)" +
					" values('"+name+"','"+description+"','"+type+"','"+fileName+"','"+buildId+"','"+componentId+"','"+productId+"')";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
		} catch (SQLException e) {
			// 
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
	
	public Boolean delete(int id)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_library where id = '"+id+"'";
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
	
	public Boolean deleteByComponentId(int componentId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_library where componentid = '"+componentId+"'";
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
	
	public Boolean deleteByBuildId(int buildId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_library where buildid = '"+buildId+"'";
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
	
	public Boolean deleteByProductId(int productId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_library where productId = '"+productId+"'";
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
	
	public Boolean update(Library lib)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			//rs = st.executeQuery("select * from t_repository");
			int id = lib.getId();
			String name = lib.getName();
			String description = lib.getDescription();
			String type = lib.getType();
			String fileName = lib.getFileName();
			int buildId = lib.getBuildId();
			int componentId = lib.getComponentId();
			int productId = lib.getProductId();
			String sql = "update t_library set name = '"+name+"', description = '"+description+"', type = '"+type+"', filename = '"+fileName+"', " +
					"buildId = '"+buildId+"', componentId = '"+componentId+"', productId = '"+productId+"' where id = '"+id+"'";
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
	
	public LibraryList getAllByBuildId(int buildId)
	{
		LibraryList libList = new LibraryList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_library where buildId = '"+buildId+"'");
			
			while(rs.next())
			{
				Library lib = new Library();
				int id = rs.getInt(1);
				lib.setId(id);
				String name = rs.getString(2);
				lib.setName(name);
				String description = rs.getString(3);
				lib.setDescription(description);
				String type = rs.getString(4);
				lib.setType(type);
				String fileName = rs.getString(5);
				lib.setFileName(fileName);
				lib.setBuildId(buildId);
				
				libList.add(lib);
				
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
		return libList;
	}
	
	public LibraryList getAllByComponentId(int componentId)
	{
		LibraryList libList = new LibraryList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_library where componentId = '"+componentId+"'");
			
			while(rs.next())
			{
				Library lib = new Library();
				int id = rs.getInt(1);
				lib.setId(id);
				String name = rs.getString(2);
				lib.setName(name);
				String description = rs.getString(3);
				lib.setDescription(description);
				String type = rs.getString(4);
				lib.setType(type);
				String fileName = rs.getString(5);
				lib.setFileName(fileName);
				lib.setComponentId(componentId);
				
				libList.add(lib);
				
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
		return libList;
	}
	
	public LibraryList getAllByProductId(int productId)
	{
		LibraryList libList = new LibraryList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_library where productId = '"+productId+"'");
			
			while(rs.next())
			{
				Library lib = new Library();
				int id = rs.getInt(1);
				lib.setId(id);
				String name = rs.getString(2);
				lib.setName(name);
				String description = rs.getString(3);
				lib.setDescription(description);
				String type = rs.getString(4);
				lib.setType(type);
				String fileName = rs.getString(5);
				lib.setFileName(fileName);
				lib.setProductId(productId);
				
				libList.add(lib);
				
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
		return libList;
	}
	
	public Library getById(int id)
	{
		Library lib = new Library();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select name,description,type,buildId,componentId,productId,filename from t_library where id = '"+id+"'");
			
			if(rs.next())
			{
				lib.setId(id);
				String name = rs.getString(1);
				lib.setName(name);
				String description = rs.getString(2);
				lib.setDescription(description);
				String type = rs.getString(3);
				lib.setType(type);
				int buildId = rs.getInt(4);
				lib.setBuildId(buildId);
				int componentId = rs.getInt(5);
				lib.setComponentId(componentId);
				int productId = rs.getInt(6);
				lib.setProductId(productId);
				String fileName = rs.getString(7);
				lib.setFileName(fileName);
				
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
		return lib;
	}

	public int getIdByFileName(String fileName){
		
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_library where filename = '"+fileName+"'");
			
			if(rs.next())
			{
				return rs.getInt(1);
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
