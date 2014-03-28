<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>Delete Component Category</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<script type="text/javascript">
	 <%ComponentCategoryList comCateList = (ComponentCategoryList)session.getAttribute("componentCategoryList");
	 	if(comCateList.size()<1)
	 		return;
	  %>
	var name = '<%=comCateList.get(0).getName().replace(' ', '%') %>';
	//alert(name);
	function selectChange(){
		var obj = document.getElementById("categoryList");
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
   
    	<select id="categoryList" style="width:200px" onchange="selectChange()">
    		<%
    			for(ComponentCategory comCate:comCateList){ 
    				String cName = comCate.getName();
    				cName = cName.replace(" ", "%");
    				//System.out.println(cName);
    		 %>
    		 <option value=<%=cName %>><%=comCate.getName() %></option>
    		 <%} %>
    	</select>
    <input type="submit" onclick="sendTo()"/>
  </body>
</html>
