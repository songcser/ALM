package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;

import com.prolambda.model.Database;
import com.prolambda.model.Repository;
import com.prolambda.model.RepositoryList;

public class RepositoryDAL {
	
//	int pageSize = 5;
//	int rowCount = 0;
//	int pageCount = 0;

	public Boolean create(Repository rep)
	{
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
			String name = rep.getName();
			Timestamp created = rep.getCreated();
			String description = rep.getDescription();
			Timestamp modified = rep.getModified();
			String sql = "insert into t_repository(name,description,created,modified)" +
					" values('"+name+"','"+description+"','"+created+"','"+modified+"')";
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
	
	public Boolean delete(String name)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_repository where name = '"+name+"'";
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
	
	public void clean(){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "truncate table t_repository";
			st.executeUpdate(sql);
			sql = "truncate table t_artifact";
			st.executeUpdate(sql);
			sql = "truncate table t_build";
			st.executeUpdate(sql);
			sql = "truncate table t_library";
			st.executeUpdate(sql);
			sql = "truncate table t_dependence";
			st.executeUpdate(sql);
			
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
	}
	
	public Boolean update(Repository rep)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			//rs = st.executeQuery("select * from t_repository");
			int id = rep.getId();
			String name = rep.getName();
			String description = rep.getDescription();
			Timestamp created = rep.getCreated();
			Timestamp modified = rep.getModified();
			String sql = "update t_repository set name = '"+name+"', description = '"+description+"', created = '"+created+"', modified = '"+modified+"' where id = '"+id+"'";
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
	
	public RepositoryList getAll()
	{
		RepositoryList repList = new RepositoryList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_repository");
			
			while(rs.next())
			{
				Repository rep = new Repository();
				int id = rs.getInt(1);
				rep.setId(id);
				String name = rs.getString(2);
				rep.setName(name);
				String description = rs.getString(3);
				rep.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				rep.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				rep.setModified(modified);
				
				repList.add(rep);
				
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
		return repList;
	}
	
	public Repository getById(int id)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		Repository rep = new Repository();
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select name,description,created,modified from t_repository where id = '"+id+"'");
			
			while(rs.next())
			{
				String name = rs.getString(1);
				rep.setName(name);
				String description = rs.getString(2);
				rep.setDescription(description);
				Timestamp created = rs.getTimestamp(3);
				rep.setCreated(created);
				Timestamp modified = rs.getTimestamp(4);
				rep.setModified(modified);
			}
			
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
		return rep;
	}
	
	public Repository getByName(String name)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		Repository rep = new Repository();
		rep.setName(name);
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id,description,created,modified from t_repository where name = '"+name+"'");
			
			if(rs.next())
			{
				int id = rs.getInt(1);
				rep.setId(id);
				String description = rs.getString(2);
				rep.setDescription(description);
				Timestamp created = rs.getTimestamp(3);
				rep.setCreated(created);
				Timestamp modified = rs.getTimestamp(4);
				rep.setModified(modified);
			}
			
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
		return rep;
	}
	
	public boolean contains(String name)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_repository where name = '"+name+"'");
			
			if(rs.next())
				return true;
			
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
		return false;
	}
/*
	public RepositoryList getByPage(int pageNow) {
		// TODO Auto-generated method stub
		RepositoryList repList = new RepositoryList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			
			
			st = conn.createStatement();
			rs = st.executeQuery("select * from t_repository limit "+(pageNow-1)*pageSize+","+pageSize);
			
			while(rs.next())
			{
				Repository rep = new Repository();
				int id = rs.getInt(1);
				rep.setId(id);
				String name = rs.getString(2);
				rep.setName(name);
				String description = rs.getString(3);
				rep.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				rep.setCreated(created);
				Timestamp modified = rs.getTimestamp(5);
				rep.setModified(modified);
				
				repList.add(rep);
				
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
		return repList;
	}

	public int getPageCount() {
		// TODO Auto-generated method stub
		
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select count(*) from t_repository");
			
			if(rs.next())
			{
				rowCount = rs.getInt(1);
			}
			
			if(rowCount%pageSize==0)
	        {
	            pageCount=rowCount/pageSize;
	        }else
	        {
	            pageCount=rowCount/pageSize+1;
	        } 
			
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
		return pageCount;
	}*/
}
