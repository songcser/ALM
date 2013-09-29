<%@ page contentType="text/html; charset=gb2312"%>
<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>Build Management</title>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<meta http-equiv="content-type" content="text/html;charset=gb2312" />
	
	<link rel="stylesheet" type="text/css" href="css/styles.css">
	
	<script type="text/javascript" src="js/pager.js"></script>
	<script type="text/javascript" src="js/dTree.js"></script>
	<script type="text/javascript">
	function modifyDialog(){
		
		var retValue=window.showModalDialog("modifyRepositoryPage.jsp",window,"dialogHeight:200px,dialogWidth:400px, status:0, edge:sunken");
		
		if(retValue)
		{
			var name=retValue[0];
			var des=retValue[1];
			location.href="RepositoryServlet?tabName=t1&flag=modify&name="+name+"&description="+des;
		}
	}
	</script>
  </head>
  
  <body BGCOLOR="#FAF0E6" onclick="changeTabs()" onload="init()">
    <table border="2" bgcolor="#CDCDC1" width="1000" align="center">
	<tbody>
	<% 
		ArtifactList artList = (ArtifactList)session.getAttribute("artifactlist");
		Repository rep = (Repository)session.getAttribute("repository");
	%>
	<tr>
	<td  height="60px" colspan=3 width="750px">
		<div id = "header">
		<form method="post" action="PDMServlet" name="header">
   	 		<input type="submit" value="Home" id="home" name="pdm" >
   	 		<input type="submit" value="BuildManagement" id="buildManagement" name="pdm" >
   	 		<input type="submit" value="OutcomeManagement" id="outcomeManagement" name="pdm">
   	 		<input type="submit" value="SystemManagement" id="systemManagement" name="pdm">
   	 	</form>
   	 	</div>
	</td>
		
	<td width="250px">&nbsp;</td>
	</tr>
	<tr>
		<td width="250px" valign="top">
		<p>&nbsp;</p>

		<div class="dtree" id="dtree1">

    		<script type="text/javascript">

        		d = new dTree('d',"dtree1",'goods');
				
				
        		d.add(0,-1,'<%=rep.getName() %>');
        		
				<%for(Artifact art:artList){%>
				
				var node = new Node(<%=art.getId() %>,0,'<%=art.getName() %>','ArtifactServlet?flag=select&artId=<%= art.getId() %>&artName=<%=art.getName() %>','','contentFrame');
				node._hc = true;
				d.aNodesData[d.aNodesData.length] = node;
				//d.getChildren(<%=art.getId() %>);
        		//d.add(<%=art.getId() %>,0,'<%=art.getName() %>');
        		<%}%>
        		
        		
        		d.show();

    		</script>

		</div>
		
		</td>
		<td height="700px" colspan=3 width="750px" valign="top">
		<iframe src="repositoryPage.jsp" id="contentFrame" name="contentFrame" frameborder="0" marginheight="0" marginwidth="0" scrolling="no" style="width:100%; height:100%; overflow:no"></iframe>
  		</td>
	
	</tr>
	<tr>
	<td width="250px">
		<div id = "footer">
			<p >footer</p>
		</div>
	</td>
	<td width="250px">&nbsp;</td>
	<td width="250px">&nbsp;</td>
	<td width="250px">&nbsp;</td></tr>
</tbody>
</table>

  </body>
</html>
