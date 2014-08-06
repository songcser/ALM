<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'createBuildProjectPage.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
<script language="javascript">
	function sendTo(){
		var value = new Array([2]);
		var name = document.getElementById("name").value;
		var url = document.getElementById("url").value;
		var path = document.getElementById("path").value;
		
		value[0] = name;
		value[1] = url;
		value[2] = path;
		
		window.returnValue = value;
		window.close();
	}
	
	</script>
  </head>
  
  <body bgcolor="#CDCDC1" >
  	
  	
 		<table border=0 width=420px>
 			<caption align="top">Create Component Category</caption>
 			<tr>
 				<td>Name:</td>
 				<td width=300px><input type="text" name="name" id="name" ></td>
 			</tr>
 			<tr>
 				<td >Config File URL:    </td>
 				<td ><input type="text" name="name" id="url" style="width:300px"></td>
 			</tr>
 			<tr>
 				<td>Relative Path:</td>
 				<td><input type="text" name="name" id="path" style="width:300px"></td>
 			</tr>
 			<tr>
 				<td></td>
 				<td align="right">
 					<input type="submit" name="Submit" value="Submit" onclick="sendTo()"> 
				 	<input type="reset" name="Reset" value="Reset"> 
				</td>
 			</tr>
 		</table>
 
  
  </body>
</html>
