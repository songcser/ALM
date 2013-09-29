<%@ page contentType="text/html; charset=gb2312"%>
<%@ page language="java" import="java.util.*,com.prolambda.model.*,com.prolambda.controller.*,java.io.*" pageEncoding="ISO-8859-1"%>
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
	<script type="text/javascript" src="js/fileBrowser.js"></script>
	<script type="text/javascript">
	<%LibraryList libList = (LibraryList)request.getAttribute("librarylist");
	DepInfoList depList = (DepInfoList)request.getAttribute("dependencelist");%>
	fb = new FileBrowser('fb',"librarys");
	fb.checkbox = true;
	
	function downloadLibrary(){
		var selectFile = fb.getSelectedFile();
		//alert(selectFile.length);
		var libIds = "";
		for(var i=0;i<selectFile.length;i++){
			libIds += selectFile[i].id+",";
		}
		if(libIds!=""){
			var url = "LibraryServlet?flag=downloadLibrary&libIds="+libIds;
		
			location.href = url;
		}
		
	}
	
	function goBack(){
		fb.goBack();
		//fb.goHome();
	}
	
	function goHome(){
		fb.goHome();
	}
	
	function createFolder(){
		var name = document.getElementById("newFolder");
		//alert(name.value);
		if(name.value!=''){
			fb.createFolder(name.value);
		}
		name.value = "";
	}
	
	function inithere(){
		
		init(0);
		//alert("bf");
		<%
			for(Library lib:libList){
		%>
			var path = '<%=lib.getName() %>';
			var id = '<%=lib.getId() %>';
			//alert(path);
			fb.add(id,path);
		<%}%>
		//fb.add("/sss");
		//alert("sss");
		fb.show();
	}
	</script>
	
  </head>
  
  <body BGCOLOR="#FAF0E6" onload="inithere()">
  <script language="javascript"> 
  	nav = new Navigation("navigation",true);
  	nav.add('build management','PDMServlet?pdm=BuildManagement');
  	nav.add('repository','repositoryPage.jsp','contentFrame');
  	nav.add('artifact','ArtifactServlet?flag=navigation','contentFrame');
  	nav.add('build history','BuildServlet?flag=navigation','contentFrame');
  	nav.show();
  	//var s = window.parent.document.getElementById('contentFrame').src;
  	
  </script>
    <table border="1" bgcolor="#CDCDC1" width="100%" align="center" CELLPADDING="0" CELLSPACING="0">
	<tbody>
	
	<tr>
		<td height="700px" colspan=3 width="100%" valign="top" bgcolor="c0c0c0">
		<center>
				<%
			
				//String number = (String)request.getAttribute("buildNumber");
				String artName = (String)request.getAttribute("artName");
				//Repository rep = new Repository();
				//RepositoryService repSer = new RepositoryService();
				//rep = repSer.getByName(repName);
				//String tabName = (String)request.getAttribute("tabName");
				Build build = (Build)request.getAttribute("build");
				
		 		%>
				<div STYLE="position:relative; left:0; top:0; width:100%; border:none thin gray">
					<table STYLE="width:100%"  CELLPADDING="0" CELLSPACING="0" bgcolor="c0c0c0" border="0">
						<tr>
						
							<%//if(tabName == "t1"){
							 %>
							
							<td ID="t1" CLASS="selTab" HEIGHT="25" width="180" onclick="changeTabs(event)">Properties</td>
							<td ID="t2" CLASS="tab" width="180" onclick="changeTabs(event)">Library File</td>
							<td ID="t3" CLASS="tab" width="150" onclick="changeTabs(event)">Build Log</td>
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
							<td valign="top" HEIGHT="*" COLSPAN="4" ID="tabContents" > 
							<div CLASS="cont" ID="t1Contents" STYLE="position:relative; left:10" >
					<p>&nbsp;</p>
					<p>&nbsp;</p>
					<h3><%=artName %> build_<%=build.getNumber() %> Properties</h3>
					
    				<p>&nbsp;</p>
    				<p>&nbsp;</p>
    				<table border="1" width="700px" align="center">
    					<tr>
    						<td width="100px">Number:</td>
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
				<div CLASS="cont" ID="t2Contents" >
					<p>&nbsp;</p>
					<div style="float:left;width:80%;height:250px;overflow:auto;border-style:outset" >
						
						<a href="javascript: goBack()" style="position:relative;left:50;top:5"><img src="images/filebrowser/base/back.png" /></a>
						<a href="javascript: goHome()" style="position:relative;left:50;top:5"><img src="images/filebrowser/base/home.png" /></a>
						
						<input type="text" id = "fullPath" value="/" style="width:250px;position:relative;left:50;">
						<!-- 
						<a href="javascript: createFolder()" style="position:relative;left:50;top:5"><img src="images/filebrowser/folder_add.png" /></a>
						<input type="text" id = "newFolder" style="width:100px;position:relative;left:50;">
						 -->
						<div id="librarys" style="border-style:inset;background-color:#fff;overflow:auto;height:200px;width:80%;position:relative;left:50"></div>
						
					</div>
					<div style="position:relative; left:10;float:left;width:15%;height:250px;overflow:auto;border-style:outset">
			 			
						<input type="submit" name="download" value="Download" style="height:30px;width:70px;position:relative;left:20;top:70" onclick="downloadLibrary()" /><p>
					</div>
					 <!-- 
					 <table border=1 width="350px" align="center">
    					<tr bgcolor=Orange>
    						<td width="350px">Name</td>
    						<!-- 
    						<td width="200px">Description</td><td width="100px">Type</td>
    						
    						<th width="50px">Dependencies</th>
    						
    					</tr>
    					<%
      						for(int i=0;i<libList.size();i++)
      						{
      							Library lib = new Library();
      							lib = libList.get(i);
      					%>
    					<tr>
    						<td width="350px"><a href="LibraryServlet?flag=download&libId=<%=lib.getId() %>&libName=<%=lib.getName() %>"><%=lib.getName() %></a></td>   	
	    					<!-- 
	    					<td width="200px"><%=lib.getDescription() %></td>
	    					<td width="100px"><%=lib.getType() %> </td>
	    					
	    					<td width="50px"><a href="LibraryServlet?flag=dependence&libId=<%=lib.getId()%>&libName=<%=lib.getName() %>" target="_blank">click</a></td>
       						
       					</tr>
       					<% } %>
      				</table>
      				 -->
      				<p>&nbsp;</p>
					<p>&nbsp;</p>
					<%if(depList.size()>0){ %>
					<h4 align="center">Dependence</h4>
			
					<table border=0 width="650px" align="center">
						<tr>
							<td align="right">
							<input type="button" name="package" value="Package to zip" height="30px" onclick="location.href='BuildServlet?flag=package&buildId=<%=build.getId() %>'"/>
							</td>
						</tr>
					</table>
					
      				 <!-- 
      				<a href="BuildServlet?flag=package&buildId=<%=build.getId() %>"> Package to zip</a>
      				-->
      				<table id="idData" border=1 width="650px" align="center" style="table-layout:fixed;">
      				
      					<tr bgcolor=Orange>
    						<th width="50px">Flag</th>
    						<th width="100px">Repository</th>
    						<th width="100px">Name</th>
    						<th width="20px">Version</th>
    						<th width="250px">Path</th>
    						<th width="200px">Location</th>
    					</tr>
      					<%
      						for(int i=0;i<depList.size();i++)
      						{
      							DepInfo dep = depList.get(i);
      							//if("Build".equ)
      					%>
      					<tr>
    						<td width="50px"><%=dep.getFlag() %></td>
    						<td width="100px"><%=dep.getRepository() %></td>
    						<td width="100px"><%=dep.getName() %></td>
    						<td width="20px"><%=dep.getVersion() %></td>
    						<td width="250px"><%=dep.getPath() %></td>
    						<th width="100px"><%=dep.getLocation() %></th>
    					</tr>
    					<%} %>
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
     				<%} %>
				</div>
				
				<div CLASS="cont" ID="t3Contents" STYLE="position:relative; width:750px">
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
							
						}
					 %>
					<textarea  class="comments" id="show" name="show" cols=90 rows=40 style="height:expression((this.scrollHeight>660)?'660px':(this.scrollHeight+5)+'px');overflow:auto;"> <%=text %>
   					</textarea> 
   					
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
