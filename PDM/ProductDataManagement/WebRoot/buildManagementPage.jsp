<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="UTF-8"%>
<%@ page contentType="text/html;charset=gbk" %>
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
	
	<link rel="stylesheet" type="text/css" href="css/styles.css">
	<script type="text/javascript" src="js/pager.js"></script>
	<script type="text/javascript" src="js/navigation.js"></script>
	<script type="text/javascript" src="js/jquery.js"></script>
	<script type="text/javascript">
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
	
	function firm()
	{
		var name=window.showModalDialog("deleteRepository.jsp",window,"dialogHeight:100px,dialogWidth:150px,status:0, edge:sunken");
    	//var name=prompt("Which repository do you want to delete?","");
    	//alert(name);
    	if(name)
    	{
    		name = name.replaceAll("%"," ");
    		//alert(name);
        	location.href="RepositoryServlet?flag=delete&repName="+name;
    	}	
	}
	
	function createDialog(){
		
		var retValue=window.showModalDialog("createRepositoryPage.jsp",window,"dialogHeight:200px,dialogWidth:400px, status:0, edge:sunken");
		
		if(retValue)
		{
			var name=retValue[0];
			var des=retValue[1];
			location.href="RepositoryServlet?flag=create&name="+name+"&description="+des;
		}
	}
	
	function clean(){
		//location.href="RepositoryServlet?flag=clean";
	}
	
	var fileId = 0;
	function addLibrary(){
		//var retValue=window.showModalDialog("addLibraryPage.jsp",window,"dialogHeight:200px,dialogWidth:400px, status:0, edge:sunken");
		
		var table = document.getElementById("fileTable");
        var newTr = table.insertRow(-1);
        //newTr.id = "tr"+id;
        var newTd0 = newTr.insertCell();
       // var newTd1 = newTr.insertCell();
        //var newTd2 = newTr.insertCell();
        newTd0.innerHTML = "<input type=\"file\" name=\"inputFile\" id='file"+fileId+"'> <input type=\"button\" value=\"-\" onclick=\"removefile(this)\">"; 
       // newTd1.innerHTML= "<input type=\"file\" name=\"test1\">";
       // newTd2.innerHTML= "<input type=\"file\" name=\"test1\">";
       
      	var obj = document.getElementById("file"+fileId);
       	fileId++;
		var ie=navigator.appName=="Microsoft Internet Explorer"?true:false;
		if(ie){
			obj.click();
			//document.getElementById("filename").value=document.getElementById("file").value;
		}else{
			var a=document.createEvent("MouseEvents");//FF的处理
			a.initEvent("click",true,true);
			obj.dispatchEvent(a);
		}
       
	}
	
	function uploadFile(){
		//var obj = document.getElementById("filePath");
		//obj.value = fb.getFullPath().substring(1);
		document.getElementById("fileUpload").submit();
		
		var table = document.getElementById("fileTable");
		var length = table.rows.length;
		//alert(length);
		for(var i=0;i<length;i++){
			table.deleteRow(i);
			length=length-1;
         	i=i-1;
		}
		fileId = 0;
	}
	
	function callback(msg){
		//alert(msg);
		var table = document.getElementById("configTable");
		var lib = msg.split('|');
		for(var i=0;i<lib.length-1;i++){
			var li = lib[i].split(',');
			var id = li[0];
			var name = li[1];
			
			var newRow = table.insertRow(-1);
			var cell0 = document.createElement("td");
			cell0.innerHTML = '<input type="checkbox" name="checkbox" id="'+id+'">';
			cell0.setAttribute("width","20");
			var cell1 = document.createElement("td");
			cell1.innerHTML = "<a href=\"BuildManagementServlet?flag=download&id="+id+"\">"+name+"</a>";
			cell1.setAttribute("width","150");
			var cell2 = document.createElement("td");
			cell2.innerHTML = "false";
			cell2.setAttribute("width","150");
			var cell3 = document.createElement("td");
			cell3.innerHTML = "0001-01-01 00:00:00.0";
			cell3.setAttribute("width","200");
			newRow.appendChild(cell0);
			newRow.appendChild(cell1);
			newRow.appendChild(cell2);
			newRow.appendChild(cell3);
			//fb.addFile(id,path);
		}
	}
	function getIds(isRunning){
		var checkbox = document.getElementsByName("checkbox");
		var table = document.getElementById("configTable");
		var ids = "";
		for(var i=0;i<checkbox.length;i++){
			if(checkbox[i].checked){
				var id = checkbox[i].id;
				if(isRunning!=""){
					table.rows[i+1].cells[2].innerHTML = isRunning;
				}
				
				ids += checkbox[i].id+",";
			}
		}
		return ids;
	}
	
	function run(){
		if(confirm("do you want to run?")==false)
			return;
		var ids = getIds("true");
		var url = "BuildManagementServlet?flag=run&ids="+ids;
		//alert(url);
		ajaxSend(url,false);
	}
	
	function stop(){
		if(confirm("do you want to stop?")==false)
			return;
		var ids = getIds("false");
		var url = "BuildManagementServlet?flag=stop&ids="+ids;
		ajaxSend(url,false);
	}
	
	function build(){
		if(confirm("do you want to build?")==false)
			return;
		var ids = getIds("");
		var url = "BuildManagementServlet?flag=build&ids="+ids;
		ajaxSend(url,false);
	}
	
	function deleteFile(){
		if(confirm("do you want to delete?")==false)
			return;
		var checkbox = document.getElementsByName("checkbox");
		var table = document.getElementById("configTable");
		var ids = "";
		var length = checkbox.length;
		for(var i=0;i<length;i++){
			if(checkbox[i].checked){
				
				var id = checkbox[i].id;
				//table.rows[i+1].cells[2].innerHTML = isRunning;
				ids += checkbox[i].id+",";
				table.deleteRow(i+1);
				length--;
				i--;
			}
		}
		//alert(ids);
		var url = "BuildManagementServlet?flag=delete&ids="+ids;
		ajaxSend(url,false);
	}
	</script>
	
	
  </head>
  
  <body BGCOLOR="#FAF0E6" onLoad="goPage(1,5);">
  
   <table border="2" bgcolor="#CDCDC1" width="1000px" align="center">
<tr>
	<td  height="60px" colspan=3 width="750px">
	<ul id = "header">
		<li style="width:70px"><a href="PDMServlet?pdm=Home">Home</a></li>
		<li><a href="PDMServlet?pdm=BuildManagement">Build Management</a></li>
		<li><a>Outcome Management</a>
			<ul>
				<li><a href="PDMServlet?pdm=ComponentCategory">Component Category</a></li>
				<li><a href="PDMServlet?pdm=ProductCategory">Product Category</a></li>
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
		<script language="javascript"> 
  		nav = new Navigation("navigation",false);
  		//alert("ss");
  		nav.add('build management','PDMServlet?pdm=BuildManagement');
  		//nav.add('repository','repositoryPage.jsp','contentFrame');
  		nav.show();
  		</script>
		</div>
		</td>
	</tr>
<tr>
	<td colspan=4  height="700px" valign="top">
		<div style="position:relative;left:100; top:30;width:80%;height:260px;overflow:auto;border-style:outset;">
    	<table border=0 width="100%" align="center">
    	<tr>
    		<td>
    			<input type="submit" name="create" value="Create" height="30px"
    			onclick="createDialog()" />
    			<input type="submit" name="delete" value="Delete" onclick="firm()" />
    			<!-- 
    			<input type="submit" name="clean" value="Clean" onclick="clean()" />
    			 -->
    		</td>
    	</tr>
    	</table>
    		<% 
    		RepositoryList repList=(RepositoryList)session.getAttribute("repositorylist");
    		%>
    		<table id="idData" border=1 width="100%" height="100px" align="center">
    			<tr bgcolor=Orange>
    				<th width="180px">name</th><th width="200px">description</th><th width="170px">created</th><th width="170px">modified</th>
    			</tr>
    			<%
      				for(int i=0;i<repList.size();i++)
      				{
      					Repository rep = new Repository();
      					rep = repList.get(i);
      			%>
    			<tr>
    				<td width="180px"><a href="RepositoryServlet?flag=select&repId=<%= rep.getId() %>&repName=<%=rep.getName() %>"><%=rep.getName()%></a></td>   	
	    			<td width="200px"><%=rep.getDescription() %></td>
	    			<td width="170px"><%=rep.getCreated() %></td>
	    			<td width="170px"><%=rep.getModified() %></td>
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
     		</center>
		</div>
		<p>&nbsp;&nbsp;</p>
		
		<div style="position:relative;left:100; top:30;width:80%;height:350px;overflow:auto;border-style:outset;">
			<p align="center">Build Management</p>
			<% ConfigFileList fileList = (ConfigFileList)request.getAttribute("configfilelist"); %>
			<div style="position:relative; top:10;width:98%;height:150px;overflow:auto;border-style:outset;">
				<table id="configTable" border=1 width="100%">
					<tr bgcolor=Orange>
						<th width="20">&nbsp;</th><th width="150">name</th><th width="150">isRunning</th><th width="200">buildTime</th>
					</tr>
					<% for(ConfigFile file:fileList){
					 %>
					 <tr >
					 	<td width="20"><input type="checkbox" id="<%=file.getId() %>" name="checkbox"></td>
					 	<td width="150"><a href="BuildManagementServlet?flag=download&id=<%=file.getId() %>"><%=file.getName() %></a></td>
					 	<td width="150"><%=file.getIsRunning() %></td>
					 	<td width="200"><%=file.getBuildtime() %></td>
					 </tr>
					<%} %>
				</table>
			</div>
			<p>&nbsp;&nbsp;</p>
			<input type="submit" name="add" value="Add" height="30px" style="position:relative;left:20;top:10"onclick="addLibrary()" />
			<input type="submit" value="upload" style="position:relative;left:20;top:10" onclick="uploadFile()" />
			<input type="button" value="run" style="position:relative;left:20;top:10" onclick="run()" />
			<input type="button" value="stop" style="position:relative;left:20;top:10" onclick="stop()" />
			<input type="button" value="delete" style="position:relative;left:20;top:10" onclick="deleteFile()" />
			<input type="button" value="build" style="position:relative;left:20;top:10" onclick="build()" />
			<div id="load" style="width:98%;height:100px;overflow:auto;border-style:outset;background-color:#fff;position:relative;top:10">
	
			<form id="fileUpload" method="post" action="UploadFileServ"  enctype="multipart/form-data" target="hidden_frame">
			<iframe name='hidden_frame' id="hidden_frame" style='display:none'></iframe>
			<input type="hidden" id = "filePath" name="buildManagement" value="new">
			<table id="fileTable" width="100%" border=1>
				
		
			</table>
			</form> 
			</div>
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

</table>
  </body>
</html>
