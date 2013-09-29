package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;

import com.prolambda.model.Build;
import com.prolambda.model.BuildList;
import com.prolambda.model.BuildResult;
import com.prolambda.model.Database;

public class BuildDAL {
	
//	int pageSize = 5;
//	int rowCount = 0;
//	int pageCount = 0;

	public Boolean create(Build build)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			/*rs = st.executeQuery("select * from t_repository");
			String countSql = "select count(id) from t_artifact";
			rs = st.executeQuery(countSql);
			String cou = rs.getString(1);
			String id = Integer.parseInt(cou)+"";
			*/
			int number = build.getNumber();
			Timestamp started = build.getStarted();
			long duration = build.getDuration();
			String result = build.getResult().name();
			String sourcePath = build.getSourcePath();
			String sourceVersion = build.getSourceVersion();
			String environment = build.getEnvironment();
			int artifactId = build.getArtifactId();
			String log = build.getLog();
			
			String sql = "insert into t_build(number,started,duration,result,sourcepath,sourceversion,environment,log,artifactid) " +
					"values('"+number+"','"+started+"','"+duration+"','"+result+"','"
					+sourcePath+"','"+sourceVersion+"','"+environment+"','"+log+"','"+artifactId+"')";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
			sql = "update t_artifact set count = '"+number+"',lasttime = '"+started+"' where id = '"+artifactId+"'";
			i = st.executeUpdate(sql);
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
			String sql = "delete from t_build where id = '"+id+"'";
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
	
	public Boolean deleteByArtId(int artId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_build where artifactid = '"+artId+"'";
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
	
	public Boolean update(Build build)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			//rs = st.executeQuery("select * from t_repository");
			int id = build.getId();
			String sourcePath = build.getSourcePath();
			String sourceVersion = build.getSourceVersion();
			String environment = build.getEnvironment();
			String sql = "update t_build set sourcePath = '"+sourcePath+"', sourceVersion = '"+sourceVersion+"', environment = '"+environment+"' where id = '"+id+"'";
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
	
	public Boolean updateLog(int id,String log){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			//rs = st.executeQuery("select * from t_repository");
			
			String sql = "update t_build set log = '"+log+"' where id = '"+id+"'";
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
	
	public BuildList getAll(int artifactId)
	{
		BuildList buildList = new BuildList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_build where artifactid = '"+artifactId+"'");
			
			while(rs.next())
			{
				Build build = new Build();
				int id = rs.getInt(1);
				build.setId(id);
				int number = rs.getInt(2);
				build.setNumber(number);
				Timestamp started = rs.getTimestamp(3);
				build.setStarted(started);
				long duration = rs.getLong(4);
				build.setDuration(duration);
				String result = rs.getString(5);
				build.setResult(BuildResult.valueOf(result));
				String sourcePath = rs.getString(6);
				build.setSourcePath(sourcePath);
				String sourceVersion = rs.getString(7);
				build.setSourceVersion(sourceVersion);
				String environment = rs.getString(8);
				build.setEnvironment(environment);
				String log = rs.getString(9);
				build.setLog(log);
				build.setArtifactId(artifactId);
				
				buildList.add(build);
				
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
		return buildList;
	}
	
	public Build getById(int id)
	{
		Build build = new Build();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_build where id = '"+id+"'");
			
			while(rs.next())
			{
				//String id = rs.getString(1);
				build.setId(id);
				int number = rs.getInt(2);
				build.setNumber(number);
				Timestamp started = rs.getTimestamp(3);
				build.setStarted(started);
				long duration = rs.getLong(4);
				build.setDuration(duration);
				String result = rs.getString(5);
				build.setResult(BuildResult.valueOf(result));
				String sourcePath = rs.getString(6);
				build.setSourcePath(sourcePath);
				String sourceVersion = rs.getString(7);
				build.setSourceVersion(sourceVersion);
				String environment = rs.getString(8);
				build.setEnvironment(environment);
				String log = rs.getString(9);
				build.setLog(log);
				int artifactId = rs.getInt(10);
				build.setArtifactId(artifactId);
				
				
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
		return build;
	}
	/*
	public BuildList getByPage(int pageNow,int artId)
	{
		BuildList buildList = new BuildList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_build where artifactid = '"+artId+"'limit "+(pageNow-1)*pageSize+","+pageSize+" ");
			//rs = st.executeQuery("select * from t_artifact where repositoryid='"+repId+"'");
			//int cou = 0;
			//int num = 0;
			while(rs.next())
			{
				Build build = new Build();
				int id = rs.getInt(1);
				build.setId(id);
				int number = rs.getInt(2);
				build.setNumber(number);
				Timestamp started = rs.getTimestamp(3);
				build.setStarted(started);
				long duration = rs.getLong(4);
				build.setDuration(duration);
				String result = rs.getString(5);
				build.setResult(BuildResult.valueOf(result));
				String sourcePath = rs.getString(6);
				build.setSourcePath(sourcePath);
				String sourceVersion = rs.getString(7);
				build.setSourceVersion(sourceVersion);
				String environment = rs.getString(8);
				build.setEnvironment(environment);
				String log = rs.getString(9);
				build.setLog(log);
				build.setArtifactId(artId);
				
				buildList.add(build);
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
		return buildList;
	}
	
	public int getPageCount(int artId)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "select count(*) from t_build where artifactid="+artId;
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
	*/
	
	public int getIdByRepArt(String repName,String artName,int num)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_repository where name = '"+repName+"'");
			if(rs.next())
			{
				int repId = rs.getInt(1);
				
				rs = st.executeQuery("select id from t_artifact where repositoryid = '"+repId+"'and name = '"+artName+"'");
				
				while(rs.next())
				{
					int artId = rs.getInt(1);
					
					rs = st.executeQuery("select id,number from t_build where artifactid = '"+artId+"'");
					
					while(rs.next())
					{
						if(num == rs.getInt(2))
						{
							return rs.getInt(1);
						}
					}
					
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
	
	public int getIdByRepArt(String repName,String artName)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_repository where name = '"+repName+"'");
			if(rs.next())
			{
				int repId = rs.getInt(1);
				
				rs = st.executeQuery("select id from t_artifact where repositoryid = '"+repId+"'and name = '"+artName+"'");
				
				while(rs.next())
				{
					int artId = rs.getInt(1);
					
					rs = st.executeQuery("select id,number from t_build where artifactid = '"+artId+"'");
					
					if(rs.last()){
						return rs.getInt(1);
					}
					
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
	
	public Boolean contains(int artId,int num){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_build where number = '"+num+"' and artifactid = '"+artId+"'");
			
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
