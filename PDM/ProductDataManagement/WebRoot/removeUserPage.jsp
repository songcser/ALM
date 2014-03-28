<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'removeUserPage.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	<script type="text/javascript">
	 <%PDMUserList userList = (PDMUserList)session.getAttribute("userList");
	 	if(userList.size()<1)
	 		return;
	  %>
	var name = '<%=userList.get(0).getName().replace(' ', '%') %>';
	//alert(name);
	function selectChange(){
		var obj = document.getElementById("userList");
		name = obj.options[obj.selectedIndex].value;
		//alert(name);
	}
	function sendTo(){
		//alert(name);
		window.returnValue = name;
		window.close();
	}
	</script>
  </head>
  
  <body>
    <select id="userList" style="width:200px" onchange="selectChange()">
    		<%
    			for(PDMUser user:userList){ 
    				String cName = user.getName();
    				cName = cName.replace(" ", "%");
    				//System.out.println(cName);
    		 %>
    		 <option value=<%=cName %>><%=user.getName() %></option>
    		 <%} %>
    	</select>
    <input type="submit" onclick="sendTo()"/>
  </body>
</html>
