<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'deleteProductCategoryPage.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<script type="text/javascript">
	<%ComponentVersionList versionList = (ComponentVersionList)session.getAttribute("componentVersionList"); 
		if(versionList.size()<1){
			return;
		}
		
	%>
	var name = '<%=versionList.get(0).getVersion() %>';
	var id = '<%=versionList.get(0).getId() %>';
	
	function selectChange(){
		var obj = document.getElementById("componentList");
		name = obj.options[obj.selectedIndex].value;
		id = obj.options[obj.selectedIndex].id;
	}
	function sendTo(){
		var value = new Array([2]);
		
		value[0]=id;
		value[1]=name;
		
		window.returnValue = value;
		window.close();
	}
	</script>
  </head>
  
  <body>

    
    	<select id="componentList" style="width:200px" onchange="selectChange()">
    		<%
    			for(ComponentVersion version:versionList){ 
    		 %>
    		 <option id=<%=version.getId() %> value=<%=version.getVersion() %>><%=version.getVersion() %></option>
    		 <%} %>
    	</select>

    <input type="submit" value="Submit" onclick="sendTo()"/>
  </body>
</html>
