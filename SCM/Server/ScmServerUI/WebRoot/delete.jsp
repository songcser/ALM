<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ page import="com.prolambda.scmserv.entity.*" %>
<%@ page import="com.prolambda.scmserv.bll.*" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>delete page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="delete page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	<base target="cframe"/>
	-->
	
	<script type="text/javascript">
		function CancelDeletes()
		{
			window.close();
		}
		
		function initial()
		{
			var table = document.getElementById("selectedNodeId");
			var nodeId = window.parent.dialogArguments.getCheckedNodeId();
			//alert(nodeId);
			var ids = nodeId.split(";");
			for(var i=0;i<ids.length-1;i++){
				var id = ids[i];
				var path = window.parent.dialogArguments.getNodePathById(id);
				//alert(path);
				var newRow = table.insertRow(-1);
				newRow.style.fontSize="14";
				//var cell0 = document.createElement("td");
				var cell0 = newRow.insertCell(0);
				cell0.setAttribute("bgcolor", "#FFFFFF");
				cell0.innerHTML = '<input name="path" value="'+path+'" type="checkbox" checked readonly/>';
				//var cell1 = document.createElement("td");
				var cell1 = newRow.insertCell(1);
				cell1.innerHTML = "<span>"+path+"</span>";
				//newRow.appendChild(cell0);
				//newRow.appendChild(cell1);
			}
		}
		
		function deletes()
		{
			
			var obj = document.getElementsByName("path");
			for(var i=0;i<obj.length;i++){
				var str = obj[i].value.split("/");
				if(str.length<=2){
					alert("can't delete basic structure");
					window.close();
					return;
				}
			}
			var log = document.getElementById("logmessage");
			if(log.value == null || log.value == ""){
				alert("log message is null");
				return ;
			}
			fDelete.submit();
			//window.close();
		}
	</script>
  </head>
  
  <body onload="initial()">
  	<br>
 	<iframe name="dframe" style="display:none"></iframe>
  	<form method="post" action="SingleReposManServlet" target="dframe" name="fDelete">
  		<input type="hidden" name="action" value="delete"/>
  	  <div style="left:25px;width:350;top:10;position:absolute;">
  	  	<font color="red">&nbsp;*you will delete follow paths</font>
  	  </div>
  	  <div style="left:25px;overflow:scroll;top:30;height:90;width:350;border-left:#000 solid 1px;border-right:#000 solid 1px;border-top:#000 solid 1px;border-bottom:#000 solid 1px;position:absolute;">
  	  	<table id="selectedNodeId">
  	  		<!-- 
  	  		<c:forEach var="delPath" items="${requestScope.delFullPaths}">	
			    <tr style="font-size:14;">
			      <td bgcolor="#FFFFFF">
			      <input name="path" value=<c:out value="${delPath}"/> type="checkbox" checked readonly/>
			      </td>
			      <td>
			      <span><c:out value="${delPath}"/></span>
			      </td>
			    </tr>
			</c:forEach>
			 -->
  	  	</table>
  	  </div>
  	  <div style="left:25px;top:130;width:350;position:absolute;">
  	  	<font color="red">&nbsp;*please input log message</font>
  	  </div>
  	  <div style="left:25;top:155;width:350;height:150;border-left:#000 solid 1px;border-right:#000 solid 1px;border-top:#000 solid 1px;border-bottom:#000 solid 1px;position:absolute;">
  	  	<textarea id="logmessage" name="logmessage" cols="41" rows="10"></textarea>
  	  </div>
  	  <div style="left:25;top:330;width:350;position:absolute;">
  	  	<table align="center" width="350">
		  <tr height="40">
		  	<td align="right" valign="bottom">
		  		<input name="delete" value="delete" type="button" onClick="deletes()"/>
		  		<input name="cancel" value="cancel" type="button" onClick="CancelDeletes()"/>
		  	</td>
		  </tr>
		 </table>
  	  </div>
	</form>
  </body>
</html>
