<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>scm server system setting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="scm server system setting page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	<script type="text/javascript" src="js/jquery.js"></script>
	<link rel="stylesheet" media="all" type="text/css" href="css/menu.css" />
	<script src="js/menu.js" type="text/javascript"></script>
	
	<script language="javascript" type="text/javascript">
		function saveSvnRoot(){
			if(fSysMan.svnroot.value == null || fSysMan.svnroot.value == "" || fSysMan.svnroot.value.length <= 1){
				alert("svn root path is null");
				return;
			}
			document.getElementById("action").value="savesvnroot";
			fSysMan.submit();
		}
		
		function saveServerURL(){
			if(fSysMan.serverurl.value == null || fSysMan.serverurl.value == "" || fSysMan.serverurl.value.length <= 1){
				alert("server url is null");
				return;
			}
			document.getElementById("action").value="saveserverurl";
			fSysMan.submit();
		}
		
		function saveRecycleBin(){
			if(fSysMan.recycle.value==null||fSysMan.recycle.value==""||fSysMan.recycle.value.length<=1){
				alert("recycle is null");
				return;
			}
			document.getElementById("action").value="saverecycle";
			fSysMan.submit();
		}
		
		function deleteSystemUsers()
		{
			var name = fSysMan.name;
			var message = "please make sure delete folow items:\r\n";
			var flag = 0;
			
			if(name == null){
				alert("have no items");
				return;
			}
			
			if(name != null && name.length == null){
				if(name.checked){
					message += name.value + "\r\n";
					flag = 1;
				}
			}
			else{
				for(var i = 0; i < name.length; i++){
					if(name[i].checked){
						message += name[i].value + "\r\n";
						flag = 1;
					}
	  			}
  			}
  			
  			if(0 == flag){
				alert("nothing had been selected");
				return;
			}
  			
  			flag = window.confirm(message);
			if(flag){
				document.getElementById("action").value = "deleteSystemUsers";
				fSysMan.submit();
				return;
			}
			else{
				return;
			}
		}
		
		function SetAdmin()
		{
			var name = fSysMan.name;
			var message = "set follow users as administrator:\r\n";
			var flag = 0;
			
			if(name == null){
				alert("have no items");
				return;
			}
			
			if(name != null && name.length == null){
				if(name.checked){
					message += name.value + "\r\n";
					flag = 1;
				}
			}
			else{
				for(var i = 0; i < name.length; i++){
					if(name[i].checked){
						message += name[i].value + "\r\n";
						flag = 1;
					}
	  			}
  			}
  			
  			if(0 == flag){
				alert("nothing had been selected");
				return;
			}
  			
  			flag = window.confirm(message);
			if(flag){
				document.getElementById("action").value = "setadmin";
				fSysMan.submit();
				return;
			}
			else{
				return;
			}
		}
		
		function CancelAdmin()
		{
			var name = fSysMan.name;
			var message = "set follow users as non-administrator:\r\n";
			var flag = 0;
			
			if(name == null){
				alert("have no items");
				return;
			}
			
			if(name != null && name.length == null){
				if(name.checked){
					message += name.value + "\r\n";
					flag = 1;
				}
			}
			else{
				for(var i = 0; i < name.length; i++){
					if(name[i].checked){
						message += name[i].value + "\r\n";
						flag = 1;
					}
	  			}
  			}
  			
  			if(0 == flag){
				alert("nothing had been selected");
				return;
			}
  			
  			flag = window.confirm(message);
			if(flag){
				document.getElementById("action").value = "canceladmin";
				fSysMan.submit();
				return;
			}
			else{
				return;
			}
		}
		
		function addSystemUsers()
		{
			window.showModalDialog("addSystemUser.jsp", window, "dialogWidth=400px;dialogHeight=350px;status=no");
		}
	</script>
	
	<link rel="stylesheet" media="all" type="text/css" href="css/tab.css" />
	<script src="js/tab.js" type="text/javascript"></script>
  </head>
  
  <body>
	<div style="width:100%;background:#D3DFD3">
	  <div style="float:left">
		<ul id="nav">
			<li><a style="height:30px" href="ReposManServlet">Repostory manage</a></li>
			<li><a style="height:30px;cursor:pointer;">System manage \/ </a>
				<ul>
					<li><a href="UserManServlet">User manage</a></li>
					<li><a href="UserGroupManServlet">User group manage</a></li>
					<li><a href="SysManServlet">System setting</a></li>
				</ul>
				<div class="clear"></div>
			</li>
		</ul>
	  </div>
	  <div style="float:right;height:30px;line-height:30px;margin-right:40">
		<span>
			<%
			 String currentUserName = (String)request.getSession().getAttribute("currentUserName");
			 if(currentUserName != null){
			 	out.println("<font size=2 color=black>current user: " + currentUserName + "&nbsp;&nbsp;|&nbsp;&nbsp;</font>");
			 }
			 else{
			 	out.println("<font size=2 color=black>current user: null &nbsp;&nbsp;|&nbsp;&nbsp; </font>");
			 }
			%>
		</span>
		<span>
		<a href="LogoutServlet"><font size=2 color=black>Logout</font></a>
	    </span>
	  </div>
	</div>
	
  <div style="margin-right:40">
  	<table align="center" width=100%>
		<tr height="30">
		  	<td align="right" valign="bottom">
		  		<span><font size=2 color=black>Current:&nbsp;System Setting</font></span>
		  	</td>
		</tr>
	</table>
  </div>
	
	<iframe name="dframe" style="display:none"></iframe>
	<form name="fSysMan" action="SysManServlet" method="post" target="dframe">
		<input type="hidden" name="action" id="action" value="empty"/>
		<div style="width:90%;height=90%;position:absolute;">
			<div id="gallery">
				<div class="on" title="Constable"><span>Basic setting</span></div>
				<div class="off" title="Monet"><span>System user setting</span></div>
			</div>
			
			<div id="Constable" class="show" style="width:90%;height=90%;">
				<table height="400" width="430" align="center">
					<tr>
						<td>
							<%
							 String svnRoot = (String)request.getAttribute("svnRoot");
							 out.println("current svn root: " + svnRoot);
							%>
						</td>
					</tr>
					<tr>
						<td>
							<span>change svn root:</span>
							<input type="text" name="svnroot" style="width:250;" value=""/><br>
						</td>
					</tr>
					<tr align="right">
						<td>
							<input type="button" style="width:60;" name="savesvnroot" value="save" onClick="saveSvnRoot()"/>
						</td>
					</tr>
					<tr>
						<td>
							<%
							 String serverURL = (String)request.getAttribute("serverURL");
							 out.println("current server url: " + serverURL);
							%>
						</td>
					</tr>
					<tr>
						<td>
							<span>change server url:</span>
							<input type="text" name="serverurl" style="width:250;" value=""/><br>
						</td>
					</tr>
					<tr align="right">
						<td>
							<input type="button" style="width:60;" name="saveserverurl" value="save" onClick="saveServerURL()"/>
						</td>
					</tr>
					<tr>
						<td>
							<%
							 String recycle = (String)request.getAttribute("recycleBin");
							 out.println("current Recycle Bin: " + recycle);
							%>
						</td>
					</tr>
					<tr>
						<td>
							<span>change Recycle Bin:</span>
							<input type="text" name="recycle" style="width:250;" value=""/><br>
						</td>
					</tr>
					<tr align="right">
						<td>
							<input type="button" style="width:60;" name="saverecycle" value="save" onClick="saveRecycleBin()"/>
						</td>
					</tr>
				</table>
			</div>
		
			<div id="Monet" class="hide" style="width:90%;height=90%;">
				<input type="button" name="delete" value="delete" style="width:60;" onClick="deleteSystemUsers()"/>
				<input type="button" name="add" value="add" style="width:60;" onClick="addSystemUsers()"/>
				<input type="button" name="setadmin" value="SetAdmin" style="width:100;" onClick="SetAdmin()"/>
				<input type="button" name="canceladmin" value="CancelAdmin" style="width:100;" onClick="CancelAdmin()"/>
				<table border="1">
					<tr align="center">
						<td style="width:150">
							<span>user name</span>
						</td>
						<td>
							<span>user id</span>
						</td>
						<td>
							<span>user role</span>
						</td>
					</tr>
					<c:forEach var="user" items="${requestScope.systemUsers}">	
					    <tr style="font-size:16;">
					      <td bgcolor="#FFFFFF">
						      <input name="name" id="name" value=<c:out value="${user.name}"/> type="checkbox"/>
						      <span><c:out value="${user.name}"/></span>
					      </td>
					      <td bgcolor="#FFFFFF">
						      <span><c:out value="${user.id}"/></span>
					      </td>
					      <td>
					          <span><c:out value="${user.role}"/></span>
					      </td>
					    </tr>
					</c:forEach>
				</table>
			</div>
		</div>
	</form>
  </body>
</html>






















