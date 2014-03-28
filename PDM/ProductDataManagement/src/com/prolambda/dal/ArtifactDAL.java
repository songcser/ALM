package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;

import com.prolambda.model.Artifact;
import com.prolambda.model.ArtifactList;
import com.prolambda.model.Database;

public class ArtifactDAL {

//	int pageSize = 5;
//	int rowCount = 0;
//	int pageCount = 0;
	
	public Boolean create(Artifact art)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String name = art.getName();
			int count = art.getCount();
			Timestamp started = art.getStarted();
			Timestamp lasttime = art.getLasttime();
			int repositoryId = art.getRepId();
			String sql = "insert into t_artifact(name,count,started,lasttime,repositoryid)" +
					" values('"+name+"','"+count+"','"+started+"','"+lasttime+"','"+repositoryId+"')";
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
	
	public Boolean delete(int id)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_artifact where id = '"+id+"'";
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
	
	public Boolean deleteByRepId(int repId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_artifact where repositoryid = '"+repId+"'";
			int i = st.executeUpdate(sql);
			if(i<1)
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
	
	public Boolean update(Artifact art)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			//rs = st.executeQuery("select * from t_repository");
			int id = art.getId();
			Timestamp lasttime = art.getLasttime();
			String sql = "update t_artifact set lasttime = '"+lasttime+"' where id = '"+id+"'";
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
	
	public ArtifactList getAll()
	{
		ArtifactList artList = new ArtifactList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_artifact");
			
			while(rs.next())
			{
				Artifact art = new Artifact();
				int id = rs.getInt(1);
				art.setId(id);
				String name = rs.getString(2);
				art.setName(name);
				int count = rs.getInt(3);
				art.setCount(count);
				Timestamp started = rs.getTimestamp(4);
				art.setStarted(started);
				Timestamp lasttime = rs.getTimestamp(5);
				art.setLasttime(lasttime);
				int repId = rs.getInt(6);
				art.setRepId(repId);
				artList.add(art);
				
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
		return artList;
	}
	
	public ArtifactList getAll(int repositoryId)
	{
		ArtifactList artList = new ArtifactList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_artifact where repositoryid = '"+repositoryId+"'");
			
			while(rs.next())
			{
				Artifact art = new Artifact();
				int id = rs.getInt(1);
				art.setId(id);
				String name = rs.getString(2);
				art.setName(name);
				int count = rs.getInt(3);
				art.setCount(count);
				Timestamp started = rs.getTimestamp(4);
				art.setStarted(started);
				Timestamp lasttime = rs.getTimestamp(5);
				art.setLasttime(lasttime);
				art.setRepId(repositoryId);
				
				artList.add(art);
				
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
		return artList;

	}
	
	public Artifact getById(int id)
	{
		Artifact art = new Artifact();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select name,count,started,lasttime,repositoryid from t_artifact where id = '"+id+"'");
			
			while(rs.next())
			{
				art.setId(id);
				String name = rs.getString(1);
				art.setName(name);
				int count = rs.getInt(2);
				art.setCount(count);
				Timestamp started = rs.getTimestamp(3);
				art.setStarted(started);
				Timestamp lasttime = rs.getTimestamp(4);
				art.setLasttime(lasttime);
				int repId = rs.getInt(5);
				art.setRepId(repId);
				
				break;
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
		return art;
	}
	/*
	public ArtifactList getByPage(int pageNow,int repId)
	{
		ArtifactList artList = new ArtifactList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_artifact where repositoryid = '"+repId+"'limit "+(pageNow-1)*pageSize+","+pageSize+" ");
			//rs = st.executeQuery("select * from t_artifact where repositoryid='"+repId+"'");
			//int cou = 0;
			//int num = 0;
			while(rs.next())
			{
				Artifact art = new Artifact();
				int id = rs.getInt(1);
				art.setId(id);
				String name = rs.getString(2);
				art.setName(name);
				int count = rs.getInt(3);
				art.setCount(count);
				Timestamp started = rs.getTimestamp(4);
				art.setStarted(started);
				Timestamp lasttime = rs.getTimestamp(5);
				art.setLasttime(lasttime);
				art.setRepId(repId);
				artList.add(art);
				/*
				if(cou>(pageNow-1)*pageSize){
					artList.add(art);
					if(num>pageSize)
						break;
					num++;
				}
				cou++;
				
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
		return artList;
	}*/
/*	
	public int getPageCount(int repId)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "select count(*) from t_artifact where repositoryid="+repId;
			//rs = st.executeQuery("select count(*) from t_artifact where repositoryid='"+repId+"'");
			rs = st.executeQuery(sql);
			while(rs.next())
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
	}
	
	public int getCount(int repId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "select count(*) from t_artifact where repositoryid="+repId;
			//rs = st.executeQuery("select count(*) from t_artifact where repositoryid='"+repId+"'");
			rs = st.executeQuery(sql);
			while(rs.next())
			{
				rowCount = rs.getInt(1);
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
		return rowCount;
	}
	*/
	public Boolean contains(int repositoryId, String artifactName)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_artifact where name = '"+artifactName+"' and repositoryid = '"+repositoryId+"'");
			
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
}
