package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;

import com.prolambda.model.BackupLog;
import com.prolambda.model.BackupLogList;
import com.prolambda.model.Database;

public class BackupDAL {

	public Boolean create(BackupLog bck)
	{
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String startTime = bck.getStartTime();
			String endTime = bck.getEndTime();
			String status = bck.getStatus();
			String log = bck.getLog();
			String sql = "insert into t_backupLog(startTime,endTime,status,log)" +
					" values('"+startTime+"','"+endTime+"','"+status+"','"+log+"')";
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
	
	public BackupLogList getAllLog(){
		BackupLogList logList = new BackupLogList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_backupLog");
			
			while(rs.next())
			{
				BackupLog log = new BackupLog();
				int id = rs.getInt(1);
				log.setId(id);
				Timestamp start = rs.getTimestamp(2);
				log.setStartTime(start.toString());
				Timestamp end = rs.getTimestamp(3);
				log.setEndTime(end.toString());
				String status = rs.getString(4);
				log.setStatus(status);
				String tlog = rs.getString(5);
				
				log.setLog(tlog);
				logList.add(log);
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
		
		return logList;
	}
}
