<%@include file="common.inc"%>

<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>scm server user manage page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="scm server user manage page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	<script type="text/javascript" src="js/jquery.js"></script>
	<link rel="stylesheet" media="all" type="text/css" href="css/menu.css" />
	<script src="js/menu.js" type="text/javascript"></script>
	
	<script type="text/javascript">
		function initial()
		{
			<%
			 List<ScmUser> userList = (List<ScmUser>)request.getAttribute("companyUsers");
			 if(userList == null){
			 	userList = new ArrayList<ScmUser>();
			 }
			 int i = 0;
			%>
			
			<%
			 String currentUserRole = (String)request.getSession().getAttribute("currentUserRole");
			%>
			<%if(currentUserRole == null || !currentUserRole.equals("administrator")){%>
				document.getElementById("SysManMenu").style.display = "none";
			<%}%>
		}
	</script>
  </head>
  
  <body onload="initial()">
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
		  		<span><font size=2 color=black>Current:&nbsp;User Manage</font></span>
		  	</td>
		</tr>
	</table>
  </div>
	
	<form name="fUserMan" action="UserManServlet" method="post">
		<div style="left:0px;overflow:scroll;height:90%;width:170;position:absolute;">
			<table width="150" align="left">
				<tr style="height:25px;">
					<td valign="middle" align="center" bgColor="#318bce">
						<span>All users</span>
					</td>
				</tr>
				<c:forEach var="companyUser" items="${requestScope.companyUsers}">	
				    <tr style="font-size:12;">
				      <td bgcolor="#FFFFFF">
				      <input name="companyUser" value=<c:out value="${companyUser.name}"/> type="checkbox"/>
				      <a href="UserManServlet?selected=<%=userList.get(i++).getName()%>&flag=1" target="a"><c:out value="${companyUser.name}"/></a>
				      </td>
				    </tr>
				</c:forEach>
			</table>
		</div>
		
		<div style="left:175px;width:90%;height=90%;position:absolute;">
			<iframe style="width:100%;height=100%;" marginheight=0 marginwidth=0 frameborder="no" border="0" name="a" src="UserManSubPage.jsp"></iframe>
		</div>
	</form>
  </body>
</html>






















