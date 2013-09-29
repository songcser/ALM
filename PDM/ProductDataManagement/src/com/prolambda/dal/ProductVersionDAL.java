package com.prolambda.dal;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;

import com.prolambda.model.ComponentVersion;
import com.prolambda.model.ComponentVersionList;
import com.prolambda.model.Database;
import com.prolambda.model.ProductDependence;
import com.prolambda.model.ProductDependenceList;
import com.prolambda.model.ProductTree;
import com.prolambda.model.ProductTreeList;
import com.prolambda.model.ProductVersion;
import com.prolambda.model.ProductVersionList;

public class ProductVersionDAL {
	public Boolean create(ProductVersion pVersion){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String version = pVersion.getVersion();
			Timestamp created = pVersion.getCreated();
			String description = pVersion.getDescription();
		//	Timestamp modified = pro.getModified();
		//	String lastVersion = pro.getLastVersion();
			int productId = pVersion.getProductId();
			String sql = "insert into t_pversion(version,description,created,productId)" +
					" values('"+version+"','"+description+"','"+created+"','"+productId+"')";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
		//	sql = "update t_product set lastVersion = " + version;
		//	i=st.executeUpdate(sql);
		//	if(i!=1){
		//		return false;
		//	}
			
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
			String sql = "delete from t_pversion where id = '"+id+"'";
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
	public Boolean update(ProductVersion version){
		return true;
	}
	
	public ProductVersionList getVersions(int productId){
		ProductVersionList versionList = new ProductVersionList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_pversion where productId = '"+productId+"'");
			
			while(rs.next())
			{
				ProductVersion pVersion= new ProductVersion();
				int id = rs.getInt(1);
				pVersion.setId(id);
				String version = rs.getString(2);
				pVersion.setVersion(version);
				String description = rs.getString(3);
				pVersion.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				pVersion.setCreated(created);
				//int categoryId = rs.getInt(6);
				pVersion.setProductId(productId);
				
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
	
	public ProductVersion getVersionById(int id){
		ProductVersion pVersion= new ProductVersion();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement();
			//rs = st.executeQuery("select * from t_pversion where id='"+id+"'");
			rs = st.executeQuery("select * from t_pversion where id = '"+id+"'");
			if(rs.next())
			{
				pVersion.setId(id);
				String version = rs.getString(2);
				pVersion.setVersion(version);
				String description = rs.getString(3);
				pVersion.setDescription(description);
				Timestamp created = rs.getTimestamp(4);
				pVersion.setCreated(created);
				int productId = rs.getInt(5);
				pVersion.setProductId(productId);	
			
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
		return pVersion;
	}
	
	public Boolean contains(String categoryName,String productName,String version){
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
					int productId = rs.getInt(1);
					rs = st.executeQuery("select id from t_pversion where version ='"+version+"' and productid = '"+productId+"'");
					if(rs.next())
						return true;
				}
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
	
	public int getIdByVersion(String categoryName,String productName,String version){
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
					int productId = rs.getInt(1);
					rs = st.executeQuery("select id from t_pversion where version ='"+version+"' and productid = '"+productId+"'");
					if(rs.next())
						return rs.getInt(1);
				}
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
		return -1;
	}
	
	public int getIdByVersion(String categoryName,String productName){
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
					int productId = rs.getInt(1);
					rs = st.executeQuery("select id from t_pversion where  productid = '"+productId+"'");
					if(rs.last())
						return rs.getInt(1);
				}
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
		return -1;
	}
	
	public ComponentVersionList getComponents(int productId){
		ComponentVersionList versionList = new ComponentVersionList();
		
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		//ResultSet rss = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,ResultSet.CONCUR_UPDATABLE);
			//rs = st.executeQuery("select * from t_pversion where id='"+id+"'");
			rs = st.executeQuery("select componentid from t_procom where productid = '"+productId+"'");
			
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
			for(int componentid:idList){
				
				ComponentVersion cVersion = new ComponentVersion();
				rs = st.executeQuery("select * from t_cversion where id = '"+componentid+"'");
				
				if(rs.next())
				{
					
					int id = rs.getInt(1);
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
				versionList.add(cVersion);
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

	public Boolean addComponent(int productId,int componentId,String location){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "insert into t_procom(productId,componentId,location)" +
					" values('"+productId+"','"+componentId+"','"+location+"')";
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
	
	public Boolean addComponent(int productId,int componentId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "insert into t_procom(productId,componentId,location)" +
					" values('"+productId+"','"+componentId+"','.')";
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
	
	public Boolean setComponentLocation(int productId,int componentId,String location){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "update t_procom set location = '"+location+"' where productid = '"+productId+"' and componentId='"+componentId+"'";
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
	
	public String getComponentLocation(int productId,int componentId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "select location from t_procom where productId = '"+productId+"' and componentId = '"+componentId+"'";
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
	
	public Boolean containsComponent(int productId,int componentId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "select componentId from t_procom where productId = '"+productId+"'";
			rs = st.executeQuery(sql);
			while(rs.next()){
				if(componentId==rs.getInt(1))
					return false;
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
		return true;
	}
	
	public Boolean deleteComponent(int productId,int componentId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_procom where productId = '"+productId+"' and componentId='"+componentId+"'";
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
	
	public ProductDependenceList getDependences(int productId){
		ProductDependenceList depList = new ProductDependenceList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_pdependence where productId = '"+productId+"'");
			
			while(rs.next()){
				ProductDependence pDep = new ProductDependence();
				int id = rs.getInt(1);
				pDep.setId(id);
				pDep.setProductId(productId);
				int depId = rs.getInt(3);
				pDep.setDependenceId(depId);
				String depName = rs.getString(4);
				pDep.setDependenceName(depName);
				String depVersion = rs.getString(5);
				pDep.setDependenceVersion(depVersion);
				int fileId = rs.getInt(6);
				pDep.setFileId(fileId);
				String fileName = rs.getString(7);
				pDep.setFileName(fileName);
				String path = rs.getString(8);
				pDep.setRelativePath(path);
				
				depList.add(pDep);
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

	public Boolean addDependence(ProductDependence pDep){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			int productId = pDep.getProductId();
			int depId = pDep.getDependenceId();
			String depName = pDep.getDependenceName();
			String depVersion = pDep.getDependenceVersion();
			int fileId = pDep.getFileId();
			String fileName = pDep.getFileName();
			String path = pDep.getRelativePath();
			
			String sql = "insert into t_pdependence(productId,dependenceId,dependenceName,dependenceVersion,fileid,filename,location)" +
					" values('"+productId+"','"+depId+"','"+depName+"','"+depVersion+"','"+fileId+"','"+fileName+"','"+path+"')";
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
	public Boolean addDependence(int productId,int dependenceId,int fileid){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "insert into t_pdependence(productId,dependenceId,fileid,location)" +
					" values('"+productId+"','"+dependenceId+"','"+fileid+"','.')";
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
	
	public Boolean containsDependence(int productId,int fileId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "select id from t_pdependence where productId = '"+productId+"' and fileId = '"+fileId+"'";
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
	
	public Boolean setDependenceLocation(int productId,int fileId,String location){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "update t_pdependence set location = '"+location+"' where productid = '"+productId+"' and fileid='"+fileId+"'";
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
	
	public String getDependenceLocation(int productId,int fileId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "select location from t_pdependence where productId = '"+productId+"' and fileId = '"+fileId+"'";
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
	
	public String getDependenceLocation(int id){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "select location from t_pdependence where id = '"+id+"'";
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
	
	public Boolean removeDependence(int productId,int dependenceId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_pdependence where productid = '"+productId+"' and dependenceid = '"+dependenceId+"'";
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

	public Boolean addTree(ProductTree tree){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			int productId = tree.getProductId();
			int libraryId = tree.getLibraryId();
			String path = tree.getPath();
			String sql = "insert into t_ptree(productId,libraryId,path)" +
					" values('"+productId+"','"+libraryId+"','"+path+"')";
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
	
	public Boolean containTree(int productId, int libraryId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
		
			String sql = "select id from t_ptree where productId = '"+productId+"' and libraryId = '"+libraryId+"'";
			rs = st.executeQuery(sql);
			if(rs.next()){
				return false;
			}
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
	
	public Boolean updateTree(ProductTree tree){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			int productId = tree.getProductId();
			int libraryId = tree.getLibraryId();
			String path = tree.getPath();
			String sql = "update t_ptree set productid = '"+productId+"', libraryId = '"+libraryId+"', path = '"+path+"' " +
					"where id = '"+tree.getId()+"'";
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
	
	public int getTreeId(int productId, int libraryId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
		
			String sql = "select id from t_ptree where productId = '"+productId+"' and libraryId = '"+libraryId+"'";
			rs = st.executeQuery(sql);
			if(rs.next()){
				return rs.getInt(1);
			}
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
		return -1;
	}
	
	public ProductTreeList getTrees(int productId){
		ProductTreeList treeList = new ProductTreeList();
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			rs = st.executeQuery("select * from t_ptree where productId = '"+productId+"'");
			
			while(rs.next())
			{
				ProductTree tree= new ProductTree();
				int id = rs.getInt(1);
				tree.setId(id);
				tree.setProductId(productId);
				int libraryId = rs.getInt(3);
				tree.setLibraryId(libraryId);
				String path = rs.getString(4);
				tree.setPath(path);
				
				treeList.add(tree);
				
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
		return treeList;
	}
	
	public Boolean deleteTree(int productId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_ptree where productid = '"+productId+"'";
			int i = st.executeUpdate(sql);
			if(i>1)
				return false;
			
			
		} catch (SQLException e) {
			// 
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
	
	public Boolean deleteTree(int productId,int libraryId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_ptree where productid = '"+productId+"' and libraryId = '"+libraryId+"'";
			int i = st.executeUpdate(sql);
			if(i!=1)
				return false;
			
			
		} catch (SQLException e) {
			// 
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
	
	public Boolean deleteTreeByLibrary(int libraryId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_ptree where libraryid = '"+libraryId+"'";
			int i = st.executeUpdate(sql);
			if(i>1)
				return false;
			
			
		} catch (SQLException e) {
			// 
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
	
	public Boolean addIssFile(int productId,int issId,int fileId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			
			String sql = "insert into t_issfile(productid,issid,fileid)" +
					" values('"+productId+"','"+issId+"','"+fileId+"')";
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
	
	public int getFileByIss(int issId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
		
			String sql = "select fileid from t_issfile where issid = '"+issId+"'";
			rs = st.executeQuery(sql);
			if(rs.next()){
				return rs.getInt(1);
			}
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
		return -1;
	}
	
	public int getIssBySetupFile(int setupId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
		
			String sql = "select issid from t_issfile where fileid = '"+setupId+"'";
			rs = st.executeQuery(sql);
			if(rs.next()){
				return rs.getInt(1);
			}
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
		return -1;
	}
	
	public ArrayList<Integer> getIssByProduct(int productId){
		ArrayList<Integer> issId = new ArrayList<Integer>(); ;
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
		
			String sql = "select issid from t_issfile where productid = '"+productId+"'";
			rs = st.executeQuery(sql);
			//int i=0;
			if(rs.next()){
				int id=rs.getInt(1);
				issId.add(new Integer(id));
		
			}
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
		return issId;
	}
	
	public Boolean containsIss(int issId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
		
			String sql = "select id from t_issfile where issid = '"+issId+"'";
			rs = st.executeQuery(sql);
			if(rs.next()){
				return true;
			}
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
		return false;
	}
	
	public Boolean deleteByIssId(int issId){
		Database db = new Database();
		Connection conn = null;
		Statement st = null;
		//ResultSet rs = null;
		try {
			conn = db.getConn();
			st = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
			String sql = "delete from t_issfile where issid = '"+issId+"'";
			int i = st.executeUpdate(sql);
			if(i<1)
				return false;
			
			
		} catch (SQLException e) {
			// 
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
}
