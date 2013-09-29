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
    
    <title>Repository</title>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<meta http-equiv="content-type" content="text/html;charset=gb2312" />
	
	<link rel="stylesheet" type="text/css" href="css/styles.css">
	
	<script type="text/javascript" src="js/pager.js"></script>
	<script type="text/javascript" src="js/dTree.js"></script>
	<script type="text/javascript" src="js/navigation.js"></script>
  </head>
  
  <body BGCOLOR="#FAF0E6" onload="init(0)">
  
  <script language="javascript"> 
  	nav = new Navigation("navigation",true);
  	nav.add('build management','PDMServlet?pdm=BuildManagement');
  	nav.add('repository','repositoryPage.jsp','contentFrame');
  	nav.add('artifact','ArtifactServlet?flag=navigation','contentFrame');
  	nav.show();
  	//var s = window.parent.document.getElementById('contentFrame').src;
  	
  </script>
  
    <table border="1" bgcolor="#CDCDC1" width="100%" align="center" CELLPADDING="0" CELLSPACING="0">
	<tbody>
	<% 
		Artifact art = (Artifact)request.getAttribute("artifact");
		BuildList buildList = (BuildList)request.getAttribute("buildlist");
		//String artId = (String)request.getAttribute("artId");
	%>
	<tr>
		<td height="700px" colspan=3 width="100%" valign="top" bgcolor="c0c0c0">
		<center>
				<%
				String repName = (String)session.getAttribute("repName");
		 		%>
				<div STYLE="position:relative; left:0; top:0; width:100%; border:none thin gray">
					<table STYLE="width:100%"  CELLPADDING="0" CELLSPACING="0" bgcolor="c0c0c0" border="0">
						<tr>
						
							<%//if(tabName == "t1"){
							 %>
							
							<td ID="t1" CLASS="selTab" HEIGHT="25" width="180" onclick="changeTabs(event)">Properties</td>
							<td ID="t2" CLASS="tab" width="180" onclick="changeTabs(event)">Build History</td>
							<%//}else{ %>
							<!-- 
							<td ID="t1" CLASS="tab" HEIGHT="25" width="150">Properties</td>
							<td ID="t2" CLASS="selTab" width="150">View Artifacts</td>
							<%//} %>  -->
							<td width="150px">&nbsp;</td>
							<td width="150px">&nbsp;</td>
						</tr>
						<tr>
							<%//if(tabName=="t1"){ %>
							<td ID="t1base" STYLE="height:2; border-left:solid thin white"></td>
							<td ID="t2base" STYLE="height:2; background-color:white; border-right:solid thin white"></td>
							<%//}else{ %>
							<!-- 
							<td ID="t1base" STYLE="height:2; background-color:white; border-right:solid thin white"></td>
							<td ID="t2base" STYLE="height:2; border-left:solid thin white"></td>
							 -->
							<%//} %>
							<td ID="t3base" STYLE="height:2; background-color:white; border-left:solid thin white"></td>
							<td ID="t4base" STYLE="height:2; background-color:white; border-left:solid thin white"></td>
						</tr>
						<tr>
							<td valign="top" HEIGHT="*" COLSPAN="4" ID="tabContents" STYLE="border-left:solid thin white;border-bottom:solid thin white;border-right:solid thin white"> 
							<div CLASS="cont" ID="t1Contents" STYLE="position:relative; left:10" >
					<p>&nbsp;</p>
					<p>&nbsp;</p>
					<h3><%=art.getName() %> Properties</h3>
					<!--  
					<input type="submit" name="modify" value="Modify" height="30px"
    					onclick="javascript:window.open('modifyRepositoryPage.jsp','ModifyRepository','width=400,height=200 alwaysRaised=yes')" />
    				-->
    				<p>&nbsp;</p>
    				<p>&nbsp;</p>
    				<table border="1" align="center" width="700px">
    					<tr>
    						<td width="100px">Name:</td>
    						<td><%=art.getName() %></td>
    					</tr>
    					<tr>
    						<td>Started:</td>
    						<td><%=art.getStarted() %></td>
    					</tr>
    					<tr>
    						<td>Last Build:</td>
    						<td><%=art.getLasttime() %></td>
    					</tr>
    					<tr>
    						<td>Count of Build:</td>
    						<td><%=art.getCount() %></td>
    					</tr>
    				</table>
				</div>
				<div CLASS="cont" ID="t2Contents" >
					
					 <p>&nbsp;</p>
					 <p>&nbsp;</p>
					 <table id="idData" border=1 width="500px" align="center">
    					<tr bgcolor=Orange>
    						<th width="100px">Number</th><th width="200px">Started</th><th width="200px">Duration</th>
    					</tr>
    					<%
      						for(int i=0;i<buildList.size();i++)
      						{
      							Build build = new Build();
      							build = buildList.get(i);
      					%>
    					<tr>
    						<td width="100px"><a href="BuildServlet?flag=select&buildId=<%= build.getId() %>&buildNumber=<%=build.getNumber() %>">#<%=build.getNumber()%></a></td>   	
	    					<td width="200px"><%=build.getStarted() %></td>
	    					<td width="200px"><%=build.getDuration() %>  ms</td>
	    			
       					</tr>
       					<% } %>
      				</table>
      				
      				<p>&nbsp;&nbsp;</p>
      				<center>
      				
      				<table width="60%" align="right">
						<tr>
							<td>
							<div id="barcon" ></div>
							</td>
						</tr>
					</table>
     				</center>
				</div>
		
							</td>
						</tr>
					</table>
				</div>
				
		</center>
  		</td>
	</tr>
</tbody>
</table>

  </body>
</html>
