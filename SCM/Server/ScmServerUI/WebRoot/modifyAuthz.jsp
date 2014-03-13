<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ page import="com.prolambda.scmserv.entity.*" %>
<%@ page import="com.prolambda.scmserv.bll.*" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>modify permission page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="modify permission page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	<script type="text/javascript">
		function initial()
		{
			<%
			 String section = (String)request.getParameter("section");
			 String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
			 SysMan sysMan = new SysMan();
			 String svnRoot = sysMan.readSvnRoot(configRealPath);
			 List<UserGroup> groupAuthzs = null;
			 List<ScmUser> userAuthzs = null;
			 if(section != null){
			 	groupAuthzs = AuthzMan.findPathGroupPerm(section, svnRoot);
			 	userAuthzs = AuthzMan.findPathUserPerm(section, svnRoot);
			 }
			 if(groupAuthzs == null){
			 	groupAuthzs = new ArrayList<UserGroup>();
			 }
			 if(userAuthzs == null){
			 	userAuthzs = new ArrayList<ScmUser>();
			 }
			 
			 request.setAttribute("userAuthzs", userAuthzs);
			 request.setAttribute("groupAuthzs", groupAuthzs);
			%>
			document.getElementById("section").value = window.dialogArguments.document.getElementById("section").value;
		}
	
		function doModify()
		{
			fModify.submit();
			window.close();
		}
		
		function cancelModify()
		{
			window.close();
		}
		
		<%int i = 0; int j = 0;%>
	</script>
  </head>
  
  <body onload="initial()">
		<iframe name="mframe" style="display:none"></iframe>
		<div style="left:25px;top:20;width:350;position:absolute;">
			<p>current path: <%out.println("&nbsp;<font color=red>" + section + "</font>");%></p>
		</div>
		
		<div style="left:25px;top:50;overflow:scroll;height:290;width:350;border-left:#000 solid 1px;border-right:#000 solid 1px;border-top:#000 solid 1px;border-bottom:#000 solid 1px;position:absolute;">
		<form name="fModify" action="SingleReposManServlet" target="mframe" method="post">
			<input type="hidden" name="section" id="section" value=""/>
			<input type="hidden" name="action" id="action" value="modifyAuthz"/>
			<table border="1">
				<tr>
					<td width="150" align="center">
						<span>Name</span>
					</td>
					<td width="100" align="center">
						<span>role</span>
					</td>
					<td width="100" align="center">
						<span>permission</span>
					</td>
				</tr>
				<c:forEach var="user" items="${requestScope.userAuthzs}">	
				    <tr style="font-size:14;">
				      <td bgcolor="#FFFFFF">
				      	<input type="checkbox" name="name" value="<c:out value="${user.name}"/>"/><c:out value="${user.name}"/>
				      </td>
				      <td>
				      	<span>user</span>
				      </td>
				      <td>
				        <select name="<%=j++%>" id="<%=i++%>" size="1" style="width:100">
					      	<c:choose>
					      		<c:when test="${user.permission == 1}">
					      			<option value="write" selected><c:out value="write"/></option>
					      			<option value="read"><c:out value="read"/></option>
					      		</c:when>
					      		<c:when test="${user.permission == 0}">
					      			<option value="write"><c:out value="write"/></option>
					      			<option value="read" selected><c:out value="read"/></option>
					      		</c:when>
							</c:choose>
						</select>
				      </td>
				    </tr>
				</c:forEach>
				<c:forEach var="group" items="${requestScope.groupAuthzs}">	
				    <tr style="font-size:14;">
				      <td bgcolor="#FFFFFF">
				      	<input type="checkbox" name="name" value="<c:out value="${group.name}"/>"/><c:out value="${group.name}"/>
				      </td>
				      <td>
				      	<span>group</span>
				      </td>
				      <td>
				        <select name="<%=j++%>" id="<%=i++%>" size="1" style="width:100">
				        	<c:choose>
					      		<c:when test="${group.permission == 1}">
					      			<option value="write" selected><c:out value="write"/></option>
					      			<option value="read"><c:out value="read"/></option>
					      		</c:when>
					      		<c:when test="${group.permission == 0}">
									<option value="write"><c:out value="write"/></option>
					      			<option value="read" selected><c:out value="read"/></option>
					      		</c:when>
							</c:choose>
		                </select>
				      </td>
				    </tr>
				</c:forEach>
			</table>
		</form>
	</div>
	<div style="left:25;top:335;width:350;position:absolute;">
  	  	<table align="center" width="350">
		  <tr height="40">
		  	<td align="right" valign="bottom">
		  		<input type="button" name="modify" value="modify" onClick="doModify()"/>
				<input type="button" name="cancel" value="cancel" onClick="cancelModify()"/>
		  	</td>
		  </tr>
		 </table>
  	  </div>
  </body>
</html>
