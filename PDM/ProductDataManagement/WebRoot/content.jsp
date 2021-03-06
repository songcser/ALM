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
    <table border="1" bgcolor="#CDCDC1" width="100%" align="center" CELLPADDING="0" CELLSPACING="0">
	<tbody>
	<% 
		ArtifactList artList = (ArtifactList)session.getAttribute("artifactlist");
		Repository rep = (Repository)session.getAttribute("repository");
	%>
	<tr>
		<td height="700px" colspan=3 width="100%" valign="top" bgcolor="c0c0c0">
		<center>
				<%
				String repName = (String)session.getAttribute("repName");
				//Repository rep = new Repository();
				//RepositoryService repSer = new RepositoryService();
				//rep = repSer.getByName(repName);
				//String tabName = (String)request.getAttribute("tabName");
				
		 		%>
				<div STYLE="position:relative; left:0; top:0; width:100%; border:none thin gray">
					<table STYLE="width:100%"  CELLPADDING="0" CELLSPACING="0" bgcolor="c0c0c0" border="0">
						<tr>
						
							<%//if(tabName == "t1"){
							 %>
							
							<td ID="t1" CLASS="selTab" HEIGHT="25" width="180">Properties</td>
							<td ID="t2" CLASS="tab" width="180">View Artifacts</td>
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
							<td valign="top" HEIGHT="*" COLSPAN="4" ID="tabContents" STYLE="border-left:solid thin white;border-bottom:solid thin white;border-right:solid thin white"> </td>
						</tr>
					</table>
				</div>
				<div CLASS="conts" ID="t1Contents" STYLE="position:relative; left:50" >
					<p>&nbsp;</p>
					<p>&nbsp;</p>
					<h3><%=repName %> Properties</h3>
					<!--  
					<input type="submit" name="modify" value="Modify" height="30px"
    					onclick="javascript:window.open('modifyRepositoryPage.jsp','ModifyRepository','width=400,height=200 alwaysRaised=yes')" />
    				-->
    				<input type="submit" name="modify" value="Modify" height="30px" onclick="modifyDialog()" />
    				<p>&nbsp;</p>
    				<p>&nbsp;</p>
    				<table border="1">
    					<tr>
    						<td>Name:</td>
    						<td><%=rep.getName() %></td>
    					</tr>
    					<tr>
    						<td>Description:</td>
    						<td><%=rep.getDescription() %></td>
    					</tr>
    					<tr>
    						<td>Created:</td>
    						<td><%=rep.getCreated() %></td>
    					</tr>
    					<tr>
    						<td>Modified:</td>
    						<td><%=rep.getModified() %></td>
    					</tr>
    				</table>
				</div>
				<div CLASS="conts" ID="t2Contents" >
					
					 <p>&nbsp;</p>
					 <p>&nbsp;</p>
					 <table id="idData" border=1 width="550px" align="center">
    					<tr bgcolor=Orange>
    						<th width="100px">Name</th><th width="50px">Count</th><th width="200px">Started</th><th width="200px">Last Build</th>
    					</tr>
    					<%
      						for(int i=0;i<artList.size();i++)
      						{
      							Artifact art = new Artifact();
      							art = artList.get(i);
      					%>
    					<tr>
    						<td width="100px"><a href="ArtifactServlet?flag=select&artId=<%= art.getId() %>&artName=<%=art.getName() %>"><%=art.getName()%></a></td>   	
	    					<td width="50px"><%=art.getCount() %></td>
	    					<td width="200px"><%=art.getStarted() %></td>
	    					<td width="200px"><%=art.getLasttime() %></td>
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
      				<%
    				/*获取pageNow
     				int pageNow=Integer.parseInt((String)request.getAttribute("pageNow"));
      
      	 			if(pageNow!=1){
          				out.println("<a href=ArtifactServlet?flag=fenye&tabName=t2&pageNow="+(pageNow-1)+">Last</a>"); 
          			}
          			//获取pageCount
          			String s_pageCount=(String)request.getAttribute("pageCount");
          			int pageCount=Integer.parseInt(s_pageCount);
          			//显示超练接
          			for(int i=1;i<=pageCount;i++){
          				out.println("<a href=ArtifactServlet?flag=fenye&tabName=t2&pageNow="+i+">"+i+"</a>");
          			}
          			if(pageNow<pageCount){
          				out.println("<a href=ArtifactServlet?flag=fenye&tabName=t2&pageNow="+(pageNow+1)+">Next</a>"); 
          			}*/
     				%>
     				</center>
				</div>
		
		</center>
  		</td>
	</tr>
</tbody>
</table>

  </body>
</html>
