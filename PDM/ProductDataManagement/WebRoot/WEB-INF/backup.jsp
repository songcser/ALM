<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'backup.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

  </head>
  
  <body>
    <div>
    	<form action="" method="post" >
    	<table>
    		<tr>
    			<td><input type="text" value="Backup Path:"></td>
    			<td><input type="text" name="backupPath">
    		</tr>
    		<tr>
    			<td><input type="checkbox" name="checkbox" value="Database"></td>
    			<td><input type="checkbox" name="checkbox" value="File"></td>
    		</tr>
    		<tr>
    			<td><input type="text" name="startTime" value="Start Backup Time"></td>
    			<td><input type="text" name="duration" value="Duration"></td>
    		</tr>
    		<tr>
    			<td><input type="text" value="How long to backup"></td>
    			<td>
    				<select id="time" name="frequency">
    					<option value="hour">Every Hour</option>
    					<option value="day">Every Day</option>
    					<option value="week">Every Week</option>
    					<option value="month">Every Month</option>
    					<option value="year">Every Year</option>
    				</select>
    			</td>
    		</tr>
    		<tr>
    			<td><input type="text" name="week" value="Which day to backup"></td>
    			<td>
    				<select id="week" name="week">
    					<option value="Monday">Monday</option>
    					<option value="Tuesday">Tuesday</option>
    					<option value="Wednesday">Wednesday</option>
    					<option value="Thursday">Thursday</option>
    					<option value="Friday">Friday</option>
    					<option value="Saturday">Saturday</option>
    					<option value="Sunday">Sunday</option>
    				</select>
    			</td>
    		</tr>
    		<tr>
    			<td><input type="submit" value="Ok"></td>
    			<td><input type="button" value="Cancle"></td>
    		</tr>
    	</table>
    	</form>
    </div>
  </body>
</html>
