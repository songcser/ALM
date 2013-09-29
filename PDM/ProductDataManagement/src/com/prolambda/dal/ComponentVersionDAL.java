package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;

import com.prolambda.model.ComponentVersion;
import com.prolambda.model.ComponentVersionList;
import com.prolambda.model.Database;
import com.prolambda.model.ProductVersion;
import com.prolambda.model.ProductVersionList;

public class ComponentVersionDAL {
	public Boolean create(ComponentVersion cVersion){
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
			String version = cVersion.getVersion();
			Timestamp created = cVersion.getCreated();
			String description = cVersion.getDescription();
		//	Timestamp modified = pro.getModified();
		//	String lastVersion = pro.getLastVersion();
			int componentId = cVersion.getComponentId();
			String sql = "insert into t_cversion(version,description,created,componentId)" +
					" values('"+version+"','"+description+"','"+created+"','"+componentId+"')";
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
			String sql = "delete from t_cversion where id = '"+id+"'";
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
	public Boolean update(ComponentVersion version){
		return true;
	}
	
	public ComponentVersionList getVersions(int componentId){
		ComponentVersionList versionList = new ComponentVersionList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_cversion where componentid = '"+componentId+"'");
			
			while(rs.next())
			{
				ComponentVersion cVersion= new ComponentVersion();
				int id = rs.getInt(1);
				cVersion.setId(id);
				String version = rs.getString(2);
				cVersion.setVersion(version);
				String description = rs.getString(3);
				cVersion.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				cVersion.setCreated(created);
				//int categoryId = rs.getInt(6);
				cVersion.setComponentId(componentId);
				
				versionList.add(cVersion);
				
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
		return versionList;
	}
	
	public ComponentVersion getVersionById(int id){
		ComponentVersion cVersion= new ComponentVersion();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_cversion where id = '"+id+"'");
			
			while(rs.next())
			{
				
				//int id = rs.getInt(1);
				cVersion.setId(id);
				String version = rs.getString(2);
				cVersion.setVersion(version);
				String description = rs.getString(3);
				cVersion.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				cVersion.setCreated(created);
				//int categoryId = rs.getInt(6);
				int componentId = rs.getInt(5);
				cVersion.setComponentId(componentId);
				
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
		return cVersion;
	}
	
	public Boolean contains(String categoryName,String componentName,String version){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_ccategory where name = '"+categoryName+"'");
			if(rs.next()){
				int categoryId = rs.getInt(1);
				rs = st.executeQuery("select id from t_component where name = '"+componentName+"' and categoryid = '"+categoryId+"'");
				if(rs.next()){
					int componentId = rs.getInt(1);
					rs = st.executeQuery("select id from t_cversion where version ='"+version+"' and componentid = '"+componentId+"'");
					if(rs.next())
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
	
	public int getIdByVersion(String categoryName,String componentName,String version){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_ccategory where name = '"+categoryName+"'");
			if(rs.next()){
				int categoryId = rs.getInt(1);
				rs = st.executeQuery("select id from t_component where name = '"+componentName+"' and categoryid = '"+categoryId+"'");
				if(rs.next()){
					int componentId = rs.getInt(1);
					rs = st.executeQuery("select id from t_cversion where version ='"+version+"' and componentid = '"+componentId+"'");
					if(rs.next())
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
	
	public int getIdByVersion(String categoryName,String componentName){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select id from t_ccategory where name = '"+categoryName+"'");
			if(rs.next()){
				int categoryId = rs.getInt(1);
				rs = st.executeQuery("select id from t_component where name = '"+componentName+"' and categoryid = '"+categoryId+"'");
				if(rs.next()){
					int componentId = rs.getInt(1);
					rs = st.executeQuery("select id from t_cversion where  componentid = '"+componentId+"'");
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
	
	public ProductVersionList getProducts(int id){
		ProductVersionList versionList = new ProductVersionList();
		
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		//ResultSet rss = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,ResultSet.CONCUR_UPDATABLE);
			//rs = st.executeQuery("select * from t_pversion where id='"+id+"'");
			rs = st.executeQuery("select productid from t_procom where componentid = '"+id+"'");
			
			rs.last();
			int length = rs.getRow();
			int[] idList = new int[length];
			rs.beforeFirst();
			int i=0;
			while(rs.next())
			{
				idList[i] = rs.getInt(1);
				i++;
			}
			for(int productid:idList){
				
				ProductVersion pVersion = new ProductVersion();
				rs = st.executeQuery("select * from t_pversion where id = '"+productid+"'");
				
				if(rs.next())
				{
					int proid = rs.getInt(1);
					pVersion.setId(proid);
					String version = rs.getString(2);
					pVersion.setVersion(version);
					String description = rs.getString(3);
					pVersion.setDescription(description);
					Timestamp created = rs.getTimestamp(4);
					pVersion.setCreated(created);
					int productId = rs.getInt(5);
					pVersion.setProductId(productId);	
				
				}
				versionList.add(pVersion);
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
		
		return versionList;
	}
	
	public ComponentVersionList getDependences(int versionId){
		ComponentVersionList versionList = new ComponentVersionList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select dependenceid from t_cdependence where componentid = '"+versionId+"'");
			
			rs.last();
			int length = rs.getRow();
			int[] idList = new int[length];
			rs.beforeFirst();
			int i=0;
			while(rs.next())
			{
				idList[i] = rs.getInt(1);
				i++;
			}
			for(int id:idList){
				rs = st.executeQuery("select * from t_cversion where id = '"+id+"'");
				
				while(rs.next())
				{
					ComponentVersion cVersion= new ComponentVersion();
					//int id = rs.getInt(1);
					cVersion.setId(id);
					String version = rs.getString(2);
					cVersion.setVersion(version);
					String description = rs.getString(3);
					cVersion.setDescription(description);
					Timestamp created = rs.getTimestamp(4);
					cVersion.setCreated(created);
					int componentId = rs.getInt(5);
					cVersion.setComponentId(componentId);
					
					versionList.add(cVersion);
					
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
		return versionList;
	}

	public Boolean addDependence(int componentId,int dependenceId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "insert into t_cdependence(componentId,dependenceId,location)" +
					" values('"+componentId+"','"+dependenceId+"','.')";
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
	
	public Boolean containDependence(int componentId,int dependenceId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "select id from t_cdependence where componentId = '"+componentId+"' and dependenceId = '"+dependenceId+"'";
			rs = st.executeQuery(sql);
			if(rs.next())
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
	
	public String getLocation(int componentId,int dependenceId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "select location from t_cdependence where componentId = '"+componentId+"' and dependenceId = '"+dependenceId+"'";
			rs = st.executeQuery(sql);
			if(rs.next())
				return rs.getString(1);
			
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
		return ".";
	}
	
	public Boolean removeDependence(int componentId,int dependenceId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "delete from t_cdependence where componentId = '"+componentId+"' and dependenceId = '"+dependenceId+"'";
			int i = st.executeUpdate(sql);
			if(i<1)
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
}
