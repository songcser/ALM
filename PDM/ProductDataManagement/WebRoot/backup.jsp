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
	<link rel="stylesheet" type="text/css" href="css/styles.css">
	<script type="text/javascript">
	function backupTest(){
		//alert("ss");
		//document.getElementById("backupform").submit();
		var obj = document.getElementById("BackupForm");
		//alert(obj);
		obj.submit();
		
		//window.returnValue = "";
		//window.close();
	}
	function cancle(){
		window.close();
	}
	
	function selectFrequency(){
		var obj = document.getElementById("frequency");
		var fre = obj.options[obj.selectedIndex].value;
		if("day"==fre){
			document.getElementById("dayDiv").style.display="block";
			document.getElementById("weekDiv").style.display="none";
			document.getElementById("monthDiv").style.display="none";
		}else if("week"==fre){
			document.getElementById("dayDiv").style.display="none";
			document.getElementById("weekDiv").style.display="block";
			document.getElementById("monthDiv").style.display="none";
		}else if("month"==fre){
			document.getElementById("dayDiv").style.display="none";
			document.getElementById("weekDiv").style.display="none";
			document.getElementById("monthDiv").style.display="block";
		}
	}
	function isBackup(is){
		if(is){
			document.getElementById("setBackup").style.display="block";
		}else {
			document.getElementById("setBackup").style.display="none";
		}
	}
	</script>

  </head>
  
  <body BGCOLOR="#CDCDC1">
	<center><H3>Backup Setting</H3></center>
    <div style="width:400px;height:300px;padding-top:20px;margin:auto;">
    	
    	<form id="BackupForm" action="SystemServlet?flag=backup" method="post" style="border:1px solid blue;" target="hidden_frame" >
		<!-- 
		<iframe name='hidden_frame' id="hidden_frame" style='display:none'></iframe>
		 -->
		<input type="radio" name="isbackup" value="true" onclick="isBackup(true)" checked="checked">Start Backup
		<input type="radio" name="isbackup" value="false" onclick="isBackup(false)">Stop Backup<br>
    	<p></p>
    	<div id="setBackup" style="border-style:inset;">
    	
    	<table >
    		<tr>
    			<td>Backup Path:</td>
    			<td><input type="text" name="backupPath">
    		</tr>
    		
    		<tr>
    			<td>Frequency:</td>
    			<td>
    				<select id="frequency" name="frequency" onchange="selectFrequency()">
    					<option value="day">Every Day</option>
    					<option value="week">Every Week</option>
    					<option value="month">Every Month</option>
    				</select>
    			</td>
    		</tr>
    		<tr>
    			<td>Which Day :</td>
    			<td>
    				<div id="dayDiv">
    				<select id="day" name="day" >
    					<%for(int i=1;i<=100;i++){ %>
    					<option value="<%=i %>"><%=i %></option>
    					<%} %>
    				</select>
    				</div>
    				<div id="weekDiv" style="display:none">
    				<select id="week" name="week" >
    					<option value="Monday">Monday</option>
    					<option value="Tuesday">Tuesday</option>
    					<option value="Wednesday">Wednesday</option>
    					<option value="Thursday">Thursday</option>
    					<option value="Friday">Friday</option>
    					<option value="Saturday">Saturday</option>
    					<option value="Sunday">Sunday</option>
    				</select>
    				</div>
    				<div id="monthDiv" style="display:none">
    				<select id="month" name="month" >
    				<%for(int i=1;i<31;i++){ %>
    					<option value="<%=i %>"><%=i %></option>
    				<%} %>
    				</select>
    				</div>
    			</td>
    		</tr>
    		<tr>
    			<td>Which Time:</td>
    			<td>
    				<select id="hour" name="hour">
    				<% for(int i=0;i<24;i++){
    					//for(int j=0;j<60;j++){
    				%>
    					<option value="<%=i %>"><%=i %></option>
    				<%}// }%>
    				</select>
    				:
    				<select id="minute" name="minute">
    				<% for(int i=0;i<60;i++){
    					//for(int j=0;j<60;j++){
    				%>
    					<option value="<%=i %>"><%=i %></option>
    				<%} //}%>
    				</select>
    			</td>
    		</tr>
    		<tr>
    			<td>backup copy</td>
    			<td><input type="text" name="copy"></td>
    		</tr>
    	</table>
    	
    	</div>
    	
    	<p></p>
    	<div style="border-style:inset;">
    	<table border="1" width="100%">
    		<tr>
    			<td>status:</td>
    			<td>running/stopped</td>
    		</tr>
    		<tr>
    			<td>start time:</td>
    			<td>2013-7-30 00:12:00</td>
    		</tr>
    		<tr>
    			<td>last time:</td>
    			<td>2013-8-03 00:12:00</td>
    		</tr>
    		<tr>
    			<td>backup path:</td>
    			<td>C:\ALM\PDM\Backup</td>
    		</tr>
    		<tr>
    			<td>backup rule:</td>
    			<td>every 3 day,On 00:12:00</td>
    		</tr>
    		<tr>
    			<td><input type="button" value="show log"></td>
    	</table>
    	</div>
    	<p></p>
    	<input type="submit" value="Ok">
    	<input type="submit" value="Cancle" onclick="cancle()">
    	</form>
    	
    </div>
    
  </body>
</html>
