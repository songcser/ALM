<%@ page language="java" import="java.util.*,com.prolambda.dal.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'viewBackupLog.jsp' starting page</title>
    
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
  <center>
  	<div>Backup Log<br>
  	<%BackupDAL backupDAL = new BackupDAL();
  		BackupLogList logList = backupDAL.getAllLog();
  		
  	 %>
  		<table border=1 width="90%" align="center">
  			<tr><th>StartTime</th><th>EndTime</th><th>Status</th><th>Log</th></tr>
  			<%for(int i=0;i<logList.size();i++){
  				BackupLog log = logList.get(i);
  				%>
  			<tr>
  				<td><%=log.getStartTime() %></td>
  				<td><%=log.getEndTime() %></td>
  				<td><%=log.getStatus() %></td>
  				<td><%=log.getLog() %></td>
  			</tr>
  			<%} %>
  		</table>
  	</div>
   </center>
  </body>
</html>
