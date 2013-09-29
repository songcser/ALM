<%@include file="common.inc"%>

<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>scm server repository manage page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="scm server repository manage page">
	
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	
	<script type="text/javascript" src="js/jquery.js"></script>
	<link rel="stylesheet" media="all" type="text/css" href="css/menu.css" />
	<script src="js/menu.js" type="text/javascript"></script>
	
	<script type="text/javascript">
		function CreateRepos()
		{
			window.showModalDialog("CreateRepos.jsp", window, "dialogWidth=380px;dialogHeight=250px;status=no");
		}
		
		function ChangeOwner()
		{
			window.showModalDialog("ChangeOwner.jsp", window, "dialogWidth=380px;dialogHeight=250px;status=no");
		}
		
		function DeleteRepos()
		{
			var name = fReposMan.reposname;
			
			if(name == null){
				alert("have no items");
				return;
			}
			
			var message = "please make sure delete the repository: ";
			
			if(name != null && name.length == null){
				if(name.checked){
					message += name.value;
					var flag = window.confirm(message);
					if(flag){
						fReposMan.submit();
						return;
					}
					else{
						return;
					}
				}
			}
			
			for(var i = 0; i < name.length; i++)
			{
				if(name[i].checked){
					message += name[i].value;
					var flag = window.confirm(message);
					if(flag){
						fReposMan.submit();
						return;
					}
					else{
						return;
					}
				}
  			}
  			
			alert("nothing had been selected");
		}
		
		function initial()
		{
			<%
			 String currentUserRole = (String)request.getSession().getAttribute("currentUserRole");
			%>
			<%if(currentUserRole == null || !currentUserRole.equals("administrator")){%>
				document.getElementById("Create").style.display = "none";
				document.getElementById("Delete").style.display = "none";
				document.getElementById("changeowner").style.display = "none";
				document.getElementById("SysManMenu").style.display = "none";
			<%}%>
		}
	</script>
	
  </head>
  
  <body onload="initial()" bgcolor="#9F9FF0">
  
  <div style="width:100%;background:#D3DFD3">
  	<div style="float:left">
	  <ul id="nav">
		<li><a style="height:30px" href="ReposManServlet">Repostory manage</a></li>
		<li><a style="height:30px;cursor:pointer;">System manage \/ </a>
			<ul>
				<li><a href="UserManServlet">User manage</a></li>
				<li><a href="UserGroupManServlet">User group manage</a></li>
				<li id="SysManMenu"><a href="SysManServlet">System setting</a></li>
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
		  		<span><font size=2 color=black>Current:&nbsp;Repository Manage</font></span>
		  	</td>
		</tr>
	</table>
  </div>

<iframe name="rframe" style="display:none"></iframe>
<form method="post" action="ReposManServlet" name="fReposMan" target="rframe">
	<input type="hidden" name="action" value="delete"/>
  <div>
	<table width=100% border="0" align="center">
   		<tr>
   		  <td>
   		    <input name="Create" id="Create" type="button" style="width:100px;height:25px" value="Create" onClick="CreateRepos()"/>
   		    <input name="Delete" id="Delete" type="button" style="width:100px;height:25px" value="Delete" onClick="DeleteRepos()"/>
   		    <input name="changeowner" id="changeowner" type="button" style="width:100px;height:25px" value="ChangeOwner" onClick="ChangeOwner()"/>
   		  </td>
   		</tr>
   		<tr>
   		<td>
   		  <table width=100% border="1">
	   		  <tr>
	   		  	<td width=10% height="27" bgcolor="#cce3f8" align="center">name
	   		  	</td>
	   		  	<td width=10% height="27" bgcolor="#0F9FFF" align="center">owner
	   		  	</td>
	   		  	<td width=30% height="27" bgcolor="#0F9FFF" align="center">sub-projects
	   		  	</td>
	   		  	<td width=25% height="27" bgcolor="#cce3f8" align="center">branches
	   		  	</td>
	   		  	<td width=25% height="27" bgcolor="#0F9FFF" align="center">tags
	   		  	</td>
	   		  </tr>
		      <c:forEach var="repos" items="${requestScope.reposes}">	
			    <tr style="font-size:12">
			      <td height="27" bgcolor="#FFFFFF">
			      <input name="reposname" value=<c:out value="${repos.name}"/> type="radio"/>
			      <a href="SingleReposManServlet?SingleReposName=<c:out value="${repos.name}"/>"><c:out value="${repos.name}"/></a>
			      </td>
			      
			      <td bgcolor="#FFFFFF">
			      <span><c:out value="${repos.owner}"/></span>
			      </td>
			      
			      <td bgcolor="#FFFFFF">
			      <c:forEach var="subprojects" items="${repos.subProjects}">
			      <c:out value="${subprojects}"/>;
			      </c:forEach>
			      </td>
			      
			      <td height="27" bgcolor="#FFFFFF">
			      <c:forEach var="branches" items="${repos.branches}">
			      <c:out value="${branches}"/>;
			      </c:forEach>
			      </td>
			      
			      <td bgcolor="#FFFFFF">
			      <c:forEach var="tags" items="${repos.tags}">
			      <c:out value="${tags}"/>;
			      </c:forEach>
			      </td>
			    </tr>
			  </c:forEach>	
    	 </table>
   		</td>
   		</tr>
    </table>
    </div>
</form>
  </body>
</html>
