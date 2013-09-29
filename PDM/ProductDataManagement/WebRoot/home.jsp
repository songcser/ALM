<%@ page contentType="text/html; charset=gb2312"%>
<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>Product Data Management</title>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<meta http-equiv="content-type" content="text/html;charset=gb2312" />
	
	<link rel="stylesheet" type="text/css" href="css/styles.css">
	<script type="text/javascript" src="js/jquery.js"></script>
	<script type="text/javascript">
	$(document).ready(function () {	
	
		$('#header li').hover(
			function () {
			//show its submenu
				$('ul', this).slideDown(170);

			}, 
			function () {
			//hide its submenu
				$('ul', this).slideUp(170);			
			}
		);
	
	});
	</script>
  </head>
  
  <body BGCOLOR="#FAF0E6">
    <table border="2" bgcolor="#CDCDC1" width="1000" align="center">
<tbody>
<tr>
	<td  height="60px" colspan=3 width="750px">
	<ul id = "header">
		<li style="width:70px"><a href="PDMServlet?pdm=Home">Home</a></li>
		<li><a href="PDMServlet?pdm=BuildManagement">Build Management</a></li>
		<li><a>Outcome Management</a>
			<ul>
				<li><a href="PDMServlet?pdm=ComponentCategory">Component Management</a></li>
				<li><a href="PDMServlet?pdm=ProductCategory">Product Management</a></li>
			</ul>
		</li>
		<li><a href="PDMServlet?pdm=SystemManagement">System Management</a></li>
	</ul>
	<!-- 
		<div id = "header">
		<form method="post" action="PDMServlet" name="header">
   	 		<input type="submit" value="Home" id="home" name="pdm" >
   	 		<input type="submit" value="BuildManagement" id="buildManagement" name="pdm" >
   	 		<input type="submit" value="OutcomeManagement" id="outcomeManagement" name="pdm">
   	 		<input type="submit" value="SystemManagement" id="systemManagement" name="pdm">
   	 	</form>
   	 	</div>
   	 	 -->
	</td>
		
	<td width="250px">&nbsp;</td>
</tr>
<tr>
	<td height="700px" colspan=4 width="1000px">
	<div id = "content">
	<center>
		<table align="center" width="700px" border="2" height="250px">
			<tr>
				<td>
				Product data management system is the unified management of product research and development company. With the increase in the company's development of products, the various components of the product is also a corresponding increase in the need for these large number of files are managed. Product data management system to solve the problem of a large number of data storage. Just compile the generated files, the system began to be managed, until the entire product is released to the future maintenance, product backup, unified management.
The overall structure of the system is divided into three main parts: Build Management, Outcome Management, System Management. Build Management and Outcome Management for the two most important aspects. Build Management main products produced on the compiler to compile management, Outcome Management to manage product components.
  				</td>
			</tr>
		</table>
	</center>
	</div>
  	</td>
	
</tr>
<tr>
	<td width="250px">
		<div id = "footer">
			<p >footer</p>
		</div>
	</td>
	<td width="250px">&nbsp;</td>
	<td width="250px">&nbsp;</td>
	<td width="250px">&nbsp;</td></tr>
</tbody>
</table>
  </body>
</html>
