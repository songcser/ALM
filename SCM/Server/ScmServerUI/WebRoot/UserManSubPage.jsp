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
    
    <title>user manage sub page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="user manage sub page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	<script type="text/javascript">
		<%
		 String basicMessage = (String)request.getAttribute("basic");
		 List<String> paths = (List<String>)request.getAttribute("Paths");
		 List<String> userAuthzs = (List<String>)request.getAttribute("userAuthzs");
		 if(paths == null || userAuthzs == null){
		 	paths = new ArrayList<String>();
		 	userAuthzs = new ArrayList<String>();
		 }
		 int i = 0;
		%>
	</script>
	
	<link rel="stylesheet" media="all" type="text/css" href="css/tab.css" />
	<script src="js/tab.js" type="text/javascript"></script>
  </head>
  
  <body>
  	<div id="gallery">
		<div class="on" title="Constable"><span>Basic message</span></div>
		<div class="off" title="Monet"><span>Permission message</span></div>
	</div>
	
	<div id="Constable" class="show" style="width:90%;height=90%;">
		<table>
			<tr>
				<td>
				 	<%
			    	 if(basicMessage != null){
			    	 	out.println(basicMessage);
			    	 }
			    	 else{
			    	 	out.println("welcome to scm");
			    	 }
			     	%>
				</td>
			</tr>
		</table>
	</div>

	<div id="Monet" class="hide" style="width:90%;height=90%;">
		<table border="1">
			<tr>
				<td>
					<span>path</span>
				</td>
				<td>
					<span>permission</span>
				</td>
			</tr>
			<%
			 for(i = 0; i < paths.size(); i++){
			 	 out.println("<tr>");
				 out.println("<td>");
				 out.println(paths.get(i));
				 out.println("</td>");
				 out.println("<td>");
				 out.println(userAuthzs.get(i));
				 out.println("</td>");
				 out.println("</tr>");
			 }
			%>
		</table>
	</div>	
  </body>
</html>
