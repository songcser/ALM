package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import com.prolambda.model.Database;
import com.prolambda.model.Dependence;
import com.prolambda.model.DependenceList;

public class DependenceDAL {
	
//	int pageSize = 5;
//	int rowCount = 0;
//	int pageCount = 0;

	public Boolean create(Dependence item)
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
			int buildId = item.getBuildId();
			int refId = item.getReferenceId();
			String flag = item.getFlag();
			String path = item.getPath();
			//String platform = item.getPlatform();
			//String configuration = item.getConfiguration();
			String location = item.getLocation();
			String sql = "insert into t_dependence(flag,referenceid,path,location,buildid) " +
					"values('"+flag+"','"+refId+"','"+path+"','"+location+"','"+buildId+"')";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
		} catch (SQLException e) {
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
			String sql = "delete from t_dependence where id = '"+id+"'";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
		} catch (SQLException e) {
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
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_dependence where buildid = '"+buildId+"'";
			int i = st.executeUpdate(sql);
			if(i<1)
				return false;
			
		} catch (SQLException e) {
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
	
	public Boolean update(Dependence item)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			int buildId = item.getBuildId();
			int refId = item.getReferenceId();
			String flag = item.getFlag();
			String path = item.getPath();
			//String platform = item.getPlatform();
			//String configuration = item.getConfiguration();
			String location = item.getLocation();
			
			//String selectSql = "select buildId from t_dependence where"
			
			String sql = "update t_dependence set flag = '"+flag+"',path = '"+path+"',location = '"+location+"'" +
					"where referenceId = '"+refId+"'and buildId = '"+buildId+"'";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
		} catch (SQLException e) {
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
	
	public DependenceList getAllByRefId(int refId){
		DependenceList depList = new DependenceList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_dependence where referenceid = '"+refId+"'");
			
			while(rs.next())
			{
				Dependence dep = new Dependence();
				
				int id = rs.getInt(1);
				dep.setId(id);
				String flag = rs.getString(2);
				dep.setFlag(flag);
				//int refId = rs.getInt(3);
				dep.setReferenceId(refId);
				String path = rs.getString(4);
				dep.setPath(path);
				//dep.setPlatform(platform);
				//String configuration = rs.getString(4);
				//dep.setConfiguration(configuration);
				String location = rs.getString(5);
				dep.setLocation(location);
				dep.setBuildId(rs.getInt(6));
				depList.add(dep);
				
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
		
		return depList;
	}
	
	public DependenceList getAll(int buildId)
	{
		DependenceList depList = new DependenceList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_dependence where buildId = '"+buildId+"'");
			
			while(rs.next())
			{
				Dependence dep = new Dependence();
				
				int id = rs.getInt(1);
				dep.setId(id);
				String flag = rs.getString(2);
				dep.setFlag(flag);
				int refId = rs.getInt(3);
				dep.setReferenceId(refId);
				String path = rs.getString(4);
				dep.setPath(path);
				//dep.setPlatform(platform);
				//String configuration = rs.getString(4);
				//dep.setConfiguration(configuration);
				String location = rs.getString(5);
				dep.setLocation(location);
				dep.setBuildId(buildId);
				depList.add(dep);
				
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
		
		return depList;
	}
	
	public Dependence getById(int id)
	{
		Dependence dep = new Dependence();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_dependence where id = '"+id+"'");
			
			if(rs.next())
			{
				dep.setId(id);
				String flag = rs.getString(2);
				dep.setFlag(flag);
				int refId = rs.getInt(3);
				dep.setReferenceId(refId);
				String path = rs.getString(4);
				dep.setPath(path);
				//String configuration = rs.getString(4);
				//dep.setConfiguration(configuration);
				String location = rs.getString(5);
				dep.setLocation(location);
				int buildId = rs.getInt(6);
				dep.setBuildId(buildId);
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
		return dep;
	}
	
	public Boolean contains(Dependence dep){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_dependence where buildId = '"+dep.getBuildId()+"'and referenceId = '"+dep.getReferenceId()+"'and " +
					"flag = '"+dep.getFlag()+"'and path = '"+dep.getPath()+"'and location = '"+dep.getLocation()+"'");
			
			if(rs.next())
			{
				return true;
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
		return false;
	}
}
