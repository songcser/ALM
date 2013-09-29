<%@ page contentType="text/html; charset=gb2312"%>
<%@ page language="java" import="java.util.*,com.prolambda.model.*,java.io.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>Build History</title>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<meta http-equiv="content-type" content="text/html;charset=gb2312" />
	
	<link rel="stylesheet" type="text/css" href="css/styles.css">
	
	<script type="text/javascript" src="js/pager.js"></script>
	<script type="text/javascript" src="js/dTree.js"></script>
	
  </head>
  
  <body BGCOLOR="#FAF0E6" onclick="changeTabs()" onload="init()">
  	
    <table border="2" bgcolor="#CDCDC1" width="1000px" align="center">
	<tbody>
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
	<%
		ArtifactList artList = (ArtifactList)request.getAttribute("artifactlist");
		String repName = (String)session.getAttribute("repName");
		String artId = (String)session.getAttribute("artId");
	 %>
	<tr>
		<td width="250px" valign="top">
		<p>&nbsp;</p>

		<div class="dtree" id="dtree1" style="height:700px;overflow:auto">

    		<script type="text/javascript">

        		d = new dTree('d',"dtree1",'goods');
				
				
        		d.add(0,-1,'<%=repName %>');
        		
				<%for(Artifact arts:artList){%>
				
				var node = new Node(<%=arts.getId() %>,0,'<%=arts.getName() %>','ArtifactServlet?flag=select&artId=<%= arts.getId() %>&artName=<%=arts.getName() %>');
				node._hc = true;
				d.aNodesData[d.aNodesData.length] = node;
				
        		
        		<%}%>
        		//alert(<%=artId %>);
        		d.getChildren(<%=artId %>);
        		d.show();

    		</script>

		</div>
		
		</td>
		<td height="700px" colspan=3 width="700px" valign="top">
		<div id = "content"  style="height:700px;overflow:hidden">
		<center>
		<table align="left" width="700px" border="0" height="700px" CELLPADDING="0" CELLSPACING="0">
			<tr>
				<td valign="top" bgcolor="c0c0c0">
				<%
				String number = (String)session.getAttribute("buildNumber");
				String artName = (String)session.getAttribute("artName");
				//Repository rep = new Repository();
				//RepositoryService repSer = new RepositoryService();
				//rep = repSer.getByName(repName);
				//String tabName = (String)request.getAttribute("tabName");
				Build build = (Build)request.getAttribute("build");
		 		%>
				<div STYLE="position:relative; left:0; top:0; width:760px; border:none thin gray">
					<table STYLE="width:760px"  CELLPADDING="0" CELLSPACING="0" bgcolor="c0c0c0" border="0">
						<tr>
						
							<%//if(tabName == "t1"){
							 %>
							
							<td ID="t1" CLASS="selTab" HEIGHT="25" width="150">Properties</td>
							<td ID="t2" CLASS="tab" width="150">View Libraries</td>
							<td ID="t3" CLASS="tab" width="150">Build Log</td>
							<%//}else{ %>
							<!-- 
							<td ID="t1" CLASS="tab" HEIGHT="25" width="150">Properties</td>
							<td ID="t2" CLASS="selTab" width="150">View Artifacts</td>
							<%//} %>  -->
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
				<div CLASS="conts" ID="t1Contents" STYLE="position:relative; left:50;" >
					<p>&nbsp;</p>
					<p>&nbsp;</p>
					<h3><%=artName%> build_<%=number %> Properties</h3>
					
    				<p>&nbsp;</p>
    				<p>&nbsp;</p>
    				<table border="1" width="600px">
    					<tr>
    						<td>Number:</td>
    						<td><%=build.getNumber() %></td>
    					</tr>
    					<tr>
    						<td>Started:</td>
    						<td><%=build.getStarted() %></td>
    					</tr>
    					<tr>
    						<td>Duration:</td>
    						<td><%=build.getDuration() %>ms</td>
    					</tr>
    					<tr>
    						<td>Result:</td>
    						<td><%=build.getResult().toString() %></td>
    					</tr>
    					<tr>
    						<td>Source Path:</td>
    						<td><%=build.getSourcePath() %></td>
    					</tr>
    					<tr>
    						<td>Source Version:</td>
    						<td><%=build.getSourceVersion() %></td>
    					</tr>
    					<tr>
    						<td>Environment:</td>
    						<td><%=build.getEnvironment() %></td>
    					</tr>
    				</table>
				</div>
				<div CLASS="conts" ID="t2Contents" STYLE="position:relative; left:50; width:750px">
					<% 
						LibraryList libList = (LibraryList)request.getAttribute("librarylist");
					 %>
					 <p>&nbsp;</p>
					 <p>&nbsp;</p>
					 <table id="idData" border=1 width="550px" align="center">
    					<tr bgcolor=Orange>
    						<th width="100px">Name</th><th width="200px">Description</th><th width="50px">Type</th>
    						<th width="50px">Dependencies</th>
    					</tr>
    					<%
      						for(int i=0;i<libList.size();i++)
      						{
      							Library lib = new Library();
      							lib = libList.get(i);
      					%>
    					<tr>
    						<td width="150px"><a href="LibraryServlet?flag=download&libId=<%=lib.getId() %>&libName=<%=lib.getName() %>"><%=lib.getName() %></a></td>   	
	    					<td width="200px"><%=lib.getDescription() %></td>
	    					<td width="50px"><%=lib.getType() %> </td>
	    					<td width="50px"><a href="LibraryServlet?flag=dependence&libId=<%=lib.getId()%>&libName=<%=lib.getName() %>" target="_blank">click</a></td>
       					</tr>
       					<% } %>
      				</table>
      				
      				<p>&nbsp;&nbsp;</p>
      				<center>
      				<table width="60%" align="right">
						<tr>
							<td>
							<div id="barcon"></div>
							</td>
						</tr>
					</table>
      				<%
    				/*获取pageNow
     				int pageNow=Integer.parseInt((String)request.getAttribute("pageNow"));
      
      	 			if(pageNow!=1){
          				out.println("<a href=LibraryServlet?flag=fenye&tabName=t2&pageNow="+(pageNow-1)+">Last</a>"); 
          			}
          			//获取pageCount
          			String s_pageCount=(String)request.getAttribute("pageCount");
          			int pageCount=Integer.parseInt(s_pageCount);
          			//显示超练接
          			for(int i=1;i<=pageCount;i++){
          				out.println("<a href=LibraryServlet?flag=fenye&tabName=t2&pageNow="+i+">"+i+"</a>");
          			}
          			if(pageNow<pageCount){
          				out.println("<a href=LibraryServlet?flag=fenye&tabName=t2&pageNow="+(pageNow+1)+">Next</a>"); 
          			}*/
     				%>
     				</center>
				</div>
				<div CLASS="conts" ID="t3Contents" STYLE="position:relative; left:50; width:750px">
					<%
						String logPath = (String)request.getAttribute("log");
						File file = new File(logPath);
						String text="";
						try{
							FileReader fr = new FileReader(file);
							BufferedReader br = new BufferedReader(fr);
							
							String s = null;
							while((s=br.readLine())!=null){
								text += s +"\n";
							}
							
							fr.close();
							br.close();
						}catch(IOException e){
							out.print(e);
							out.flush();
							out.close();
						}
					 %>
					<textarea id="show" name="show" cols=90 rows=40> <%=text %>
   					</textarea> 
   					
				</div>
				</td>
			</tr>
		</table>
		</center>
		</div>
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
