<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>Delete Product Category</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<script type="text/javascript">
	 <%ProductCategoryList proCateList = (ProductCategoryList)session.getAttribute("productCategoryList");
	 	if(proCateList.size()<1){
	 		return;
	 	}
	  %>
	var name = '<%=proCateList.get(0).getName().replace(" ", "%") %>';
	//alert(name);
	function selectChange(){
		var obj = document.getElementById("categoryList");
		name = obj.options[obj.selectedIndex].value;
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
    			for(ProductCategory proCate:proCateList){ 
    				String pName = proCate.getName().replace(" ", "%");
    		 %>
    		 <option value=<%=pName %>><%=proCate.getName() %></option>
    		 <%} %>
    	</select>
    	
    <input type="submit" onclick="sendTo()"/>
  </body>
</html>
