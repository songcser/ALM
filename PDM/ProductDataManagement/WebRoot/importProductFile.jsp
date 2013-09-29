<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'importProductFile.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<script type="text/javascript" src="js/pager.js"></script>
	<script type="text/javascript">
	function init(){
		var table = document.getElementById("fileTable");
		
		var url = "ProductVersionServlet?flag=getLibrary";
		var retStr = ajaxSend(url,false);
		if(retStr){
			//alert(retStr);
			var cc = retStr.split('|');
			for(var i=0;i<cc.length-1;i++){
  				var com = cc[i].split(',');
  				//alert(com.length);
  				if(com.length<4){
  					continue;
  				}
  				var component = com[0];
  				var version = com[1];
  				for(var j=2;j<com.length-1;j++){
  					var file = com[j];
  					var libId = com[++j];
  					var index = file.lastIndexOf("/");
  					var name = file.substring(index+1);
  					var path = file.substring(0,index+1);
  					
  					var newRow = table.insertRow(-1);
  					newRow.id = libId;
  					var cell0 = newRow.insertCell(0);
  					cell0.innerHTML = '<input type="checkbox" name="checkbox" />';
  					cell0.setAttribute("width","10px");
  					var cell1 = newRow.insertCell(1);
  					cell1.innerHTML = name;
  					cell1.setAttribute("width","150px");
  					var cell2 = newRow.insertCell(2);
  					cell2.innerHTML = component;
  					cell2.setAttribute("width","150");
  					var cell3 = newRow.insertCell(3);
  					cell3.innerHTML = version;
  					cell3.setAttribute("width","100");
  					var cell4 = newRow.insertCell(4);
  					cell4.innerHTML = "<input type='text' value='"+path+"' size='20' />";
  					cell4.setAttribute("width","150");
  				}
  			}
		}
	}
	</script>
  </head>
  
  <body BGCOLOR="#CDCDC1" onload="init()">
  <div style="width:100%;heigth:80%">
  	<p>&nbsp;&nbsp;</p>
    <table id="fileTable"  border="1"  width="90%" align="center" CELLPADDING="0" CELLSPACING="0">
    	<tr bgcolor=Orange>
    		<th></th><th>File</th><th>Component</th><th>Version</th><th>Location</th>
    	</tr>
    </table>
  </div>
  </body>
</html>
