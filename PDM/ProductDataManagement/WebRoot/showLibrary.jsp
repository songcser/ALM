<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'showLibrary.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<script type="text/javascript" src="js/fileBrowser.js"></script>
	<script type="text/javascript">
	//d = new dTree('d',"leftContent",false,"component");
	<% 
		LibraryList libList = (LibraryList)request.getAttribute("libraryList");
		
	%>
	fb = new FileBrowser('fb',"librarys");
	fb.checkbox = true;
	
	function downloadLibrary(){
		var selectFile = fb.getSelectedFile();
		//alert(selectFile.length);
		var libIds = "";
		for(var i=0;i<selectFile.length;i++){
			libIds += selectFile[i].id+",";
		}
		if(libIds!=""){
			var url = "LibraryServlet?flag=downloadLibrary&libIds="+libIds;
		
			location.href = url;
		}
		
	}
	
	function goBack(){
		fb.goBack();
		//fb.goHome();
	}
	
	function goHome(){
		fb.goHome();
	}
	
	function inithere(){
		
		
		//alert("bf");
		<%
			for(Library lib:libList){
		%>
			var path = '<%=lib.getName() %>';
			var id = '<%=lib.getId() %>';
			//alert(path);
			fb.add(id,path);
		<%}%>
		//fb.add("/sss");
		//alert("sss");
		fb.show();
	}
	</script>
  </head>
  
  <body BGCOLOR="#FAF0E6" onload="inithere()">
  <div style="float:left;width:80%;height:250px;overflow:auto;border-style:outset" >
  <a href="javascript: goBack()" style="position:relative;left:50;top:5"><img src="images/filebrowser/base/back.png" /></a>
	<a href="javascript: goHome()" style="position:relative;left:50;top:5"><img src="images/filebrowser/base/home.png" /></a>
    <div id="librarys" style="border-style:inset;background-color:#fff;overflow:auto;height:200px;width:70%;position:relative;left:50"></div>
 	</div>
 	<div style="position:relative; left:10;float:left;width:15%;height:250px;overflow:auto;border-style:outset">
		
	<input type="submit" name="download" value="Download" style="height:30px;width:70px;position:relative;left:20;top:70" onclick="downloadLibrary()" /><p>
	</div>
  </body>
</html>
