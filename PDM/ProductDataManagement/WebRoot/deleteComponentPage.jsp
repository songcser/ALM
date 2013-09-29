<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>Delete Product</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<script type="text/javascript">
	<%ComponentList comList = (ComponentList)session.getAttribute("componentList"); %>
	var name = '<%=comList.get(0).getName() %>';
	
	function selectChange(){
		var obj = document.getElementById("componentList");
		name = obj.options[obj.selectedIndex].value;
	}
	function sendTo(){
		window.returnValue = name;
		window.close();
	}
	</script>
  </head>
  
  <body>

    
    	<select id="componentList" style="width:200px" onchange="selectChange()">
    		<%
    			for(Component com:comList){ 
    		 %>
    		 <option value=<%=com.getName() %>><%=com.getName() %></option>
    		 <%} %>
    	</select>

    <input type="submit" value="Submit" onclick="sendTo()"/>
  </body>
</html>
