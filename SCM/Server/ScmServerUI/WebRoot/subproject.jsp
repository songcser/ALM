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
    
    <title>sub-project page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="subproject page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	<base target="cframe"/>
	-->
	
	<script type="text/javascript">
		function subProjects()
		{
			if(fSubproject.logmessage.value == null || fSubproject.logmessage.value == ""){
				alert("log message is null");
				return ;
			}
			
			if(fSubproject.subprojects.value == null || fSubproject.subprojects.value == ""){
				alert("sub-projects is null");
				return ;
			}
			
			fSubproject.submit();
			//window.close();
		}
		
		function CancelSubprojects()
		{
			window.close();
		}
	</script>
  </head>
  
  <body>
  	<br>
 	<iframe name="sframe" style="display:none"></iframe>
  	<form method="post" action="SingleReposManServlet" target="sframe" name="fSubproject">
  		<input type="hidden" name="action" value="subproject"/>
  	  <div style="left:25px;top:10;width:350;position:absolute;">
  	  	<font color="red">&nbsp;*please input sub-project names, split by ";"</font>
  	  </div>
  	  <div style="left:25px;top:40;width:350;border-width:1px;border-color:#000;position:absolute;">
  	  	<textarea name="subprojects" cols="41" rows="2"></textarea>
  	  </div>
  	  <div style="left:25px;top:90;width:350;position:absolute;">
  	  	<font color="red">&nbsp;*please input log message</font>
  	  </div>
  	  <div style="left:25;top:120;width:350;height:150;position:absolute;">
  	  	<textarea name="logmessage" cols="41" rows="7"></textarea>
  	  </div>
  	  <div style="left:25;top:240;width:350;position:absolute;">
  	  	<table align="center" width="350">
		  <tr height="40">
		  	<td align="right" valign="bottom">
		  		<input name="subproject" value="subproject" type="button" onClick="subProjects()"/>
		  		<input name="cancel" value="cancel" type="button" onClick="CancelSubprojects()"/>
		  	</td>
		  </tr>
		 </table>
  	  </div>
	</form>
  </body>
</html>
