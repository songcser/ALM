<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>user group manage sub page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="user group manage sub page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	<link rel="stylesheet" media="all" type="text/css" href="css/tab.css" />
	<script src="js/tab.js" type="text/javascript"></script>
	
	<script type="text/javascript">
		<%
		 String basicMessage = (String)request.getAttribute("basic");
		 List<String> paths = (List<String>)request.getAttribute("Paths");
		 List<String> userAuthzs = (List<String>)request.getAttribute("userAuthzs");
		 List<String> groupMembers = (List<String>)request.getAttribute("groupMembers");
		 if(paths == null || userAuthzs == null){
		 	paths = new ArrayList<String>();
		 	userAuthzs = new ArrayList<String>();
		 }
		 
		 if(groupMembers == null){
		 	groupMembers = new ArrayList<String>();
		 }
		 int i = 0;
		%>
	</script>
  </head>
  
  <body>
  	<div id="gallery">
		<div class="on" title="Constable"><span>Basic message</span></div>
		<div class="off" title="Vincent"><span>Member message</span></div>
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
	
	<div id="Vincent" class="hide" style="width:90%;height=90%;">
			<%
    	 	 for(i = 0; i < groupMembers.size(); i++){
    	 	 	out.println(groupMembers.get(i) + "<br>");
    	 	 }
	     	%>
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
