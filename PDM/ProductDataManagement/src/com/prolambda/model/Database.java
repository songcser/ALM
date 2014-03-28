package com.prolambda.model;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

public class Database {

	public Connection getConn()
	{
		Connection conn = null;
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			// 
			e.printStackTrace();
		}
		// 数据库连接url
		String url = "jdbc:mysql://localhost:3306/db_pdm?useUnicode=true&characterEncoding=utf-8&zeroDateTimeBehavior=round&transformedBitIsBoolean=true";
		// 获取数据库连接
		try {
			conn = DriverManager.getConnection(url, "root", "root");
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}
		
		return conn;
	}
	
	public ArrayList<String> showTables() throws SQLException
	{
		ArrayList<String> tables = new ArrayList<String>();
		Connection conn = null;
		conn = getConn();
		Statement state = conn.createStatement();
		ResultSet rs = state.executeQuery("show tables;");
		while(rs.next()){
			
			tables.add(rs.getString(1));
		}
		rs.close();
		return tables;
	}
	
	public void createRepositoryTable(){
		String repTableSql = "create table t_repository(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"modified timestamp," +
				"primary key(id))";
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(repTableSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createArtifactTable(){
		String artTableSql = "create table t_artifact(id int not null auto_increment," +
				"name varchar(100) not null," +
				"count int," +
				"started timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"lasttime timestamp," +
				"repositoryid int not null," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(artTableSql);

		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createBuildTable(){
		String buildTableSql = "create table t_build(id int not null auto_increment," +
				"number int not null," +
				"started timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"duration bigint," +
				"result varchar(10)," +
				"sourcepath varchar(100)," +
				"sourceversion varchar(10)," +
				"environment varchar(1024)," +
				"log varchar(50)," +
				"artifactid int not null," +
				"primary key(id))";
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(buildTableSql);
			
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
		
	}
	
	public void createLibraryTable(){
		String libTableSql = "create table t_library(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"type varchar(10)," +
				"filename varchar(64)," +
				"buildid int not null," +
				"componentid int not null," +
				"productid int not null," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(libTableSql);

		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createDependenceTable(){
		String depTableSql = "create table t_dependence(id int not null auto_increment," +
				"flag varchar(20),"+
				"referenceid int not null," +
				"path varchar(50)," +
				"location varchar(50),"+
				"buildid int not null,"+
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(depTableSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createConfigFileTable(){
		String configFileTableSql = "create table t_configfile(id int not null auto_increment," +
				"name varchar(100) not null," +
				"isrunning TINYINT(1) not null," +
				"buildTime timestamp not null DEFAULT '0000-00-00 00:00:00'," +
				"filename varchar(100) not null," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(configFileTableSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createProductCategoryTable(){
		String productCategoryTableSql = "create table t_pcategory(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"modified timestamp," +
				"productCount int not null," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(productCategoryTableSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createProductTable(){
		String productTableSql = "create table t_product(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"modified timestamp," +
				"lastversion varchar(20),"+
				"categoryid int not null," +
				"state int not null default 0,"+
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(productTableSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createProductVersionTable(){
		String productVersionTableSql = "create table t_pversion(id int not null auto_increment," +
				"version varchar(20) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"productid int not null," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(productVersionTableSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createComponentCategoryTable(){
		String componentCategoryTableSql = "create table t_ccategory(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"modified timestamp," +
				"componentCount int not null," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(componentCategoryTableSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createComponentTable(){
		String componentTableSql = "create table t_component(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"modified timestamp," +
				"lastversion varchar(20),"+
				"categoryid int not null," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(componentTableSql);
		} catch (SQLException e) {
			e.printStackTrace();
		}finally{
			try{
				state.close();
				conn.close();
			}catch(Exception ex){
				ex.printStackTrace();
			}
		}
	}
	
	public void createComponentVersionTable(){
		String productVersionTableSql = "create table t_cversion(id int not null auto_increment," +
				"version varchar(20) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"componentid int not null," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(productVersionTableSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createComponentDependenceTable(){
		String componentDependenceSql = "create table t_cdependence(id int not null auto_increment," +
				"componentid int not null," +
				"dependenceid int not null," +
				"location varchar(100)," +
				"primary key(id))";
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(componentDependenceSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createProductDependenceTable(){
		String componentDependenceSql = "create table t_pdependence(id int not null auto_increment," +
				"productid int not null," +
				"dependenceid int not null," +
				"dependenceName varchar(100),"+
				"dependenceVersion varchar(50),"+
				"fileid int not null,"+
				"fileName varchar(100),"+
				"location varchar(100) ," +
				"primary key(id))";
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(componentDependenceSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createIssFileTable(){
		String issFileSql = "create table t_issfile(id int not null auto_increment," +
				"productid int not null,"+
				"issid int not null default -1," +
				"fileid int not null default -1," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(issFileSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createProductTreeTable(){
		String productTreeSql = "create table t_ptree(id int not null auto_increment," +
				"productid int not null," +
				"libraryid int not null," +
				"path varchar(100) not null," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(productTreeSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createUserTable(){
		String userTableSql = "create table t_user(id int not null auto_increment," +
				"userid varchar(64) not null," +
				"name varchar(50) not null," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(userTableSql);
		} catch (SQLException e) {
			// 
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createProductComponentTable(){
		String proComSql = "create table t_procom(id int not null auto_increment," +
				"productid int not null, " +
				"componentid int not null," +
				"location varchar(100) ," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(proComSql);
		} catch (SQLException e) {
			
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createBuilderTable(){
		String proComSql = "create table t_builder(id int not null auto_increment," +
				"name varchar(100) not null, " +
				"password varchar(100) not null," +
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(proComSql);
		} catch (SQLException e) {
			
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createBackupLogTable(){
		String backupLogSql = "create table t_backuplog(id int not null auto_increment," +
				"startTime timestamp not null DEFAULT CURRENT_TIMESTAMP, " +
				"endTime timestamp not null ," +
				"status varchar(10) not null,"+
				"log varchar(512) not null,"+
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(backupLogSql);
		} catch (SQLException e) {
			
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
	
	public void createTables(){
		//HashMap<String, String> table = new HashMap<String, String>();
		try {
			ArrayList<String> tables = showTables();
			if(tables.size()<1){
				createAll();
				return ;
			}
			
			String table = "";
			for(int i=0;i<tables.size();i++){
				table += tables.get(i);
			}
			if(table.indexOf("t_repository")==-1){
				createRepositoryTable();
			}
			if(table.indexOf("t_artifact")==-1){
				createArtifactTable();
			}
			if(table.indexOf("t_build")==-1){
				createBuildTable();
			}
			if(table.indexOf("t_library")==-1){
				createLibraryTable();
			}
			if(table.indexOf("t_dependence")==-1){
				createDependenceTable();
			}
			if(table.indexOf("t_user")==-1){
				createUserTable();
			}
			if(table.indexOf("t_pcategory")==-1){
				createProductCategoryTable();
			}
			if(table.indexOf("t_product")==-1){
				createProductTable();
			}
			if(table.indexOf("t_pversion")==-1){
				createProductVersionTable();
			}
			if(table.indexOf("t_ccategory")==-1){
				createComponentCategoryTable();
			}
			if(table.indexOf("t_component")==-1){
				createComponentTable();
			}
			if(table.indexOf("t_cversion")==-1){
				createComponentVersionTable();
			}
			if(table.indexOf("t_procom")==-1){
				createProductComponentTable();
			}
			if(table.indexOf("t_cdependence")==-1){
				createComponentDependenceTable();
			}
			if(table.indexOf("t_pdependence")==-1){
				createProductDependenceTable();
			}
			if(table.indexOf("t_ptree")==-1){
				createProductTreeTable();
			}
			if(table.indexOf("t_issfile")==-1){
				createIssFileTable();
			}
			if(table.indexOf("t_configfile")==-1){
				createConfigFileTable();
			}
			if(table.indexOf("t_builder")==-1){
				createBuilderTable();
			}
			if(table.indexOf("t_backuplog")==-1){
				createBackupLogTable();
			}
			
			
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
		/*
		
		*/
	}
	
	public void createAll(){
		
		String repTableSql = "create table t_repository(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"modified timestamp," +
				"primary key(id))";
		
		String artTableSql = "create table t_artifact(id int not null auto_increment," +
				"name varchar(100) not null," +
				"count int," +
				"started timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"lasttime timestamp," +
				"repositoryid int," +
				"primary key(id))";
		
		String buildTableSql = "create table t_build(id int not null auto_increment," +
				"number int not null," +
				"started timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"duration bigint," +
				"result varchar(10)," +
				"sourcepath varchar(100)," +
				"sourceversion varchar(10)," +
				"environment varchar(1024)," +
				"log varchar(50)," +
				"artifactid int," +
				"primary key(id))";
		
		String libTableSql = "create table t_library(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"type varchar(10)," +
				"filename varchar(64)," +
				"buildid int ," +
				"componentid int not null," +
				"productid int not null," +
				"primary key(id))";
		
		String depTableSql = "create table t_dependence(id int not null auto_increment," +
				"flag varchar(20),"+
				"referenceid int not null," +
				"path varchar(50)," +
				"location varchar(50),"+
				"buildid int not null,"+
				"primary key(id))";
		
		String configFileTableSql = "create table t_configfile(id int not null auto_increment," +
				"name varchar(100) not null," +
				"isrunning TINYINT(1) not null," +
				"buildTime timestamp not null DEFAULT '0000-00-00 00:00:00'," +
				"filename varchar(100) not null," +
				"primary key(id))";
		
		String productCategoryTableSql = "create table t_pcategory(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"modified timestamp," +
				"productCount int not null," +
				"primary key(id))";
		
		String productTableSql = "create table t_product(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"modified timestamp," +
				"lastversion varchar(20),"+
				"categoryid int not null," +
				"state int not null default 0,"+
				"primary key(id))";
		
		String productVersionTableSql = "create table t_pversion(id int not null auto_increment," +
				"version varchar(20) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"productid int not null," +
				"primary key(id))";
		
		String componentCategoryTableSql = "create table t_ccategory(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"modified timestamp," +
				"componentCount int not null," +
				"primary key(id))";
		
		String componentTableSql = "create table t_component(id int not null auto_increment," +
				"name varchar(100) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"modified timestamp," +
				"lastversion varchar(20),"+
				"categoryid int not null," +
				"primary key(id))";
		
		String componentVersionTableSql = "create table t_cversion(id int not null auto_increment," +
				"version varchar(20) not null," +
				"description varchar(200)," +
				"created timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"componentid int not null," +
				"primary key(id))";
		
		String userTableSql = "create table t_user(id int not null auto_increment," +
				"userid varchar(50) not null," +
				"name varchar(50) not null," +
				"primary key(id))";
		
		String proComSql = "create table t_procom(id int not null auto_increment," +
				"productid int not null, " +
				"componentid int not null," +
				"location varchar(100) ," +
				"primary key(id))";
		
		String componentDependenceSql = "create table t_cDependence(id int not null auto_increment," +
				"componentid int not null," +
				"dependenceid int not null," +
				"location varchar(100) default \".\" ," +
				"primary key(id))";
		
		String productDependenceSql = "create table t_pDependence(id int not null auto_increment," +
				"productid int not null," +
				"dependenceid int not null," +
				"dependenceName varchar(100),"+
				"dependenceVersion varchar(50),"+
				"fileid int not null,"+
				"fileName varchar(100),"+
				"location varchar(100) default \".\" ," +
				"primary key(id))";
		
		String productTreeSql = "create table t_ptree(id int not null auto_increment," +
				"productid int not null," +
				"libraryid int not null," +
				"path varchar(100) not null," +
				"primary key(id))";
		
		String issFileSql = "create table t_issfile(id int not null auto_increment," +
				"productid int not null,"+
				"issid int not null," +
				"fileid int not null," +
				"primary key(id))";
		
		String builderSql = "create table t_builder(id int not null auto_increment," +
				"name varchar(100) not null, " +
				"password varchar(100) not null," +
				"primary key(id))";
		
		String backupLogSql = "create table t_backuplog(id int not null auto_increment," +
				"startTime timestamp not null DEFAULT CURRENT_TIMESTAMP, " +
				"endTime timestamp not null DEFAULT CURRENT_TIMESTAMP," +
				"status varchar(10) not null"+
				"log varchar(512) not null"+
				"primary key(id))";
		
		Statement state = null;
		Connection conn = null;
		try {
			conn = getConn();
			state = conn.createStatement();
			
			state.executeUpdate(repTableSql);
			state.executeUpdate(artTableSql);
			state.executeUpdate(buildTableSql);
			state.executeUpdate(libTableSql);
			state.executeUpdate(depTableSql);
			state.executeUpdate(productCategoryTableSql);
			state.executeUpdate(productTableSql);
			state.executeUpdate(productVersionTableSql);
			state.executeUpdate(componentCategoryTableSql);
			state.executeUpdate(componentTableSql);
			state.executeUpdate(componentVersionTableSql);
			state.executeUpdate(userTableSql);
			state.executeUpdate(proComSql);
			state.executeUpdate(componentDependenceSql);
			state.executeUpdate(productDependenceSql);
			state.executeUpdate(productTreeSql);
			state.executeUpdate(issFileSql);
			state.executeUpdate(configFileTableSql);
			state.executeUpdate(builderSql);
			state.executeUpdate(backupLogSql);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
			   try{
				   state.close();
				   conn.close();
			   }catch(Exception ex){
				   ex.printStackTrace();
			   }
		
		}
	}
}
