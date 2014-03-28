<%@ page contentType="text/html; charset=gb2312"%>
<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>System Management</title>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<meta http-equiv="content-type" content="text/html;charset=gb2312" />
	
	<link rel="stylesheet" type="text/css" href="css/styles.css">
	<script type="text/javascript" src="js/jquery.js"></script>
	<script type="text/javascript" src="js/pager.js"></script>
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

	function AddUserDialog(){
		
		//alert("ss");
		var retValue=window.showModalDialog("addUser.jsp",window,"dialogHeight:600px,dialogWidth:400px, status:0, edge:sunken");
		//alert(retValue);
		
		if(retValue)
		{
			var strId="";
			var length = retValue[0];
			
			for(var i=1;i<length+1;i++)
			{	
				if(retValue[i]&&retValue[i]!=""){
					var value = "&id"+i+"="+retValue[i];
					strId = strId.concat(value);
				}
			}
			//alert(strId);
			var servlet = "SystemServlet?flag=addUser"+strId;
			//alert(servlet);
			//location.href=servlet;
			ajaxSend(servlet,false);
			location.reload();
			
		}
	}
	
	function RemoveUserDialog(){
		var retValue = window.showModalDialog("removeUserPage.jsp",window,"dialogHeight:100px,dialogWidth:250px,status:0, edge:sunken")
	
		if(retValue){
			var servlet = "SystemServlet?flag=removeUser&name="+retValue;
			ajaxSend(servlet,false);
			location.reload();
		}
	}
	
	function setBuilder(){
		var retValue=window.showModalDialog("SetBuilder.jsp",window,"dialogHeight:150px,dialogWidth:50px, status:0, edge:sunken");
		
		if(retValue){
			var strName = retValue[0];
			var strPassword = retValue[1];
			
			var servlet = "SystemServlet?flag=setBuilder&name="+strName+"&password="+strPassword;
			ajaxSend(servlet,false);
			location.reload();
		}
	}
	
	function backup(){
		var retValue=window.showModalDialog("backup.jsp",window,"dialogHeight:500px,dialogWidth:400px, status:0, edge:sunken");
		//window.open('backup.jsp', 'Backup', 'height=600,width=500,top=0,left=0,toolbar=no,menubar=no,scrollbars=no,resizable=no,location=no,status=no');
		if(retValue){
			location.reload();
		}
	}
	
	function tobackup(){
		var servlet = "SystemServlet?flag=toBackup";
		ajaxSend(servlet,false);
	}
	
	function backupLog(){
		var retValue=window.showModalDialog("viewBackupLog.jsp",window,"dialogHeight:600px,dialogWidth:800px, status:0, edge:sunken");
	}
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
				<li><a href="PDMServlet?pdm=ComponentCategory">Component Category</a></li>
				<li><a href="PDMServlet?pdm=ProductCategory">Product Category</a></li>
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
	<%
		String filePath = (String)request.getAttribute("strFileFolder"); 
		PDMUserList userList = (PDMUserList)session.getAttribute("userList");
		String buildName = (String)request.getAttribute("builderName");
	%>
	<td height="700px" colspan=4 width="1000px" valign="top">
	<div id = "content">
	<p>&nbsp;</p>
	<p>&nbsp;</p>
	<table width="700px" border="2" height="25px">
		<tr>
			<td width="100px">File Path:</td>
			<td><%=filePath %></td>
		</tr>
		<tr>
			<td width="100">Builder:</td>
			<td><%=buildName %></td>
		</tr>
	</table>
	<p>&nbsp;</p>
	<input type="button" name="setBuilder" id="setBuilder" value="SetBuilder" onclick="setBuilder()">
	<input type="button" name="backup" id="backup" value="Backup Strategy" onclick="backup()">
	<input type="button" name="tobackup" value="Backup Now" onclick="tobackup()">
	<input type="button" name="backuplog" value="Backup Log" onclick="backupLog()">
	<p>&nbsp;</p>
	<input type="submit" name="user" value="Add User" height="30px" onclick="AddUserDialog()" />
	<input type="submit" name="user" value="Remove User" height="30px" onclick="RemoveUserDialog()" />
	<!-- 
		 onclick="window.showModalDialog('addUser.jsp',window,'dialogHeight:500px,dialogWidth:400px, status:0, edge:sunken')" />
	 -->
	 	<div style="height:500px;width:550px;overflow:auto">
		<table width="200px" border="2">
			<tr bgcolor=Orange>
				<th width="200px">Name</th>
			</tr>
			<%
			for(int i=0;i<userList.size();i++){
				PDMUser user = userList.get(i);
			 %>
			<tr>
				
				<td width="100px"><%=user.getName() %>
			</tr>
			<%} %>
		</table>
		</div>
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
