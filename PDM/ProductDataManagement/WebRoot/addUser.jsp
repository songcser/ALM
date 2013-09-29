<%@ page language="java" import="java.util.*,com.prolambda.webmatrix.directory.ActiveDirectory,
com.prolambda.webmatrix.directory.User,com.prolambda.webmatrix.directory.UserList;" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'addUser.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<script language="javascript">
	function sendTo(){
		var boxes = document.getElementsByName("username");
		  
    	var userId = new Array();
    	userId[0]=boxes.length;
    	//alert(boxes.length);
    	for (var i = 0; i < boxes.length; i++)  
    	{  
   	 		if(boxes[i].checked)  
    		{  
       			 userId[i+1] = boxes[i].value;  
    		}
    		
    	}
    	
    	window.returnValue = userId;
		window.close();
    }
    </script>
  </head>
  
  <body>
    <%
    	String host = "ldap://192.168.99.10:389";
		String domain = "pl.local";
		
		try {
			ActiveDirectory aDirectory = new ActiveDirectory(host, domain);
			aDirectory.setUsername("pl\\test");
			aDirectory.setPassword("pro!ambDa");
			
			if(!aDirectory.validate()){
				out.print("error");
			}
			UserList userList = aDirectory.getUserList("OU=pro-lambda");
     %>
     <form method="post" action="SystemServlet?flag=addUser" name="header">
     <div style="height:400px;width:400px;overflow:auto">
     <table width="300px" height="30px" border="2">
     		<%
     			for(int i=0;i<userList.size();i++){
     				User user = userList.get(i);
     				String name = user.getUsername();
     				int index = name.indexOf('@');
     				name = name.substring(0, index);
     		%>
     	<tr>
     		
     		<td>
     			
     				<input type="checkbox" value=<%=user.getId() %> name="username" ><%=name %>
   	 			
   	 		</td>
   	 		
   	 	</tr>
   	 	<%}
   	 	} catch (Exception e) {
			e.printStackTrace();
		} %>
   	 </table>
   	 </div>
   	 	<input type="submit" value="Submit" name="add" onclick="sendTo()">
   	 	<input type="reset" value="Reset" >
   	 </form>
  </body>
</html>
