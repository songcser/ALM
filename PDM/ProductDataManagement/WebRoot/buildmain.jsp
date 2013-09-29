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
	<script type="text/javascript" src="js/jquery.js"></script>
	<script type="text/javascript">
	<% 
		ArtifactList artList = (ArtifactList)session.getAttribute("artifactlist");
		Repository rep = (Repository)session.getAttribute("repository");
	%>
	$(document).ready(function () {	
	
		$('#header li').hover(
			function () {
			//show its submenu
				$('ul', this).slideDown(170);

			}, 
			function () {
			//hide its submenu
				$('ul', this).slideUp(170);			
			}
		);
	
	});
	function inithere(){
		////alert("ssss");
		//init(0);
		//alert("ddd");
   		
	}
	</script>
  </head>
  
  <body BGCOLOR="#FAF0E6" onload="init(0) ">

    <table border="1" bgcolor="#CDCDC1" width="1000" align="center">
	<tbody>
	
	<tr>
	<td  height="60px" colspan=3 width="750px">
	<ul id = "header">
		<li style="width:70px"><a href="PDMServlet?pdm=Home">Home</a></li>
		<li><a href="PDMServlet?pdm=BuildManagement">Build Management</a></li>
		<li><a>Outcome Management</a>
			<ul>
				<li><a href="PDMServlet?pdm=ComponentCategory">Component Management</a></li>
				<li><a href="PDMServlet?pdm=ProductCategory">Product Management</a></li>
			</ul>
		</li>
		<li><a href="PDMServlet?pdm=SystemManagement">System Management</a></li>
	</ul>

	</td>
		
	<td width="250px">&nbsp;</td>
	</tr>
	<tr>
		<td colspan=4 height="2px">
		<div id="navigation">
		
		</div>
		</td>
	</tr>
	<tr>
		<td width="250px" valign="top">
		<p>&nbsp;</p>
		<div style="width:250px;height:700px;overflow:auto;">
		<div class="dtree" id="dtree1" >
		<script type="text/javascript">
		d = new dTree('d',"dtree1","build");
		

   		d.add(0,-1,'<%=rep.getName() %>');
   		
		<%for(Artifact art:artList){%>
		//alert("<%=art.getId() %>");
		var node = new Node(<%=art.getId() %>,0,'<%=art.getName() %>','ArtifactServlet?flag=select&artId=<%= art.getId() %>&artName=<%=art.getName() %>','','contentFrame');
		node._hc = true;
		d.aNodesData[d.aNodesData.length] = node;
		//d.getChildren(<%=art.getId() %>);
   		//d.add(<%=art.getId() %>,0,'<%=art.getName() %>');
   		<%}%>
   		
   		
   		d.show();
   		</script>
		</div>
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
