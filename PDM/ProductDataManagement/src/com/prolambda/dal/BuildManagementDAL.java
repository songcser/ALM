package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;

import com.prolambda.model.ConfigFile;
import com.prolambda.model.ConfigFileList;
import com.prolambda.model.Database;

public class BuildManagementDAL {
	
	public Boolean addConfigFile(ConfigFile file){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String name = file.getName();
			String filename = file.getFileName();
			Boolean isRunning = file.getIsRunning();
			int isrun = 0;
			if(isRunning){
				isrun = 1;
			}
			//Timestamp buildTime= file.getBuildtime();
			//Timestamp buildTime = Timestamp.valueOf("0000-00-00 00:00:00");
			String sql = "insert into t_configfile(name,isrunning,buildtime,filename)" +
					" values('"+name+"','"+isrun+"','0000-00-00 00:00:00.0','"+filename+"')";
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

	public Boolean deleteConfigFile(int id){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_configfile where id = '"+id+"'";
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

	public Boolean updateBuildTime(int id,Timestamp buildTime){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "update t_configfile set buildtime = '"+buildTime+"' where id = '"+id+"'";
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

	public Boolean updateRunning(int id,int isRunning){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "update t_configfile set isRunning = '"+isRunning+"' where id = '"+id+"'";
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
	
	public ConfigFileList getAll(){
		ConfigFileList fileList = new ConfigFileList();
		
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_configfile");
			
			while(rs.next())
			{
				ConfigFile file = new ConfigFile();
				int id = rs.getInt(1);
				file.setId(id);
				String name = rs.getString(2);
				file.setName(name);
				Boolean isRunning = rs.getBoolean(3);
				file.setIsRunning(isRunning);
				//String buildTime = rs.getString(4);
				Timestamp buildTime = rs.getTimestamp(4);
				//System.out.println("time:"+buildTime);
				file.setBuildtime(buildTime);
				//file.setBuildtime(Timestamp.valueOf(buildTime));
				String filename = rs.getString(5);
				file.setFileName(filename);
				fileList.add(file);
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
		return fileList;
	}

	public ConfigFile getById(int id){

		ConfigFile file = new ConfigFile();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_configfile where id='"+id+"'");
			
			while(rs.next())
			{
				
				//int id = rs.getInt(1);
				file.setId(id);
				String name = rs.getString(2);
				file.setName(name);
				Boolean isRunning = rs.getBoolean(3);
				file.setIsRunning(isRunning);
				Timestamp buildTime = rs.getTimestamp(4);
				file.setBuildtime(buildTime);
				//String buildTime = rs.getString(4);
				//file.setBuildtime(Timestamp.valueOf(buildTime));
				String filename = rs.getString(5);
				file.setFileName(filename);
				
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
		return file;
	}
	
	public int getIdByFileName(String filename){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_configfile where filename = '"+filename+"'");
			
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
