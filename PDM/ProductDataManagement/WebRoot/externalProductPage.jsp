<%@ page contentType="text/html; charset=gb2312"%>
<%@ page language="java" import="java.util.*,com.prolambda.model.*,com.prolambda.controller.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>Component</title>
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
	//d = new dTree('d',"leftContent",false,"component");
	<% 
		LibraryList libList = (LibraryList)session.getAttribute("productLibraryList");
		String version = (String)session.getAttribute("productVersion");
	%>
	fb = new FileBrowser('fb',"librarys");
	fb.checkbox = true;
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
	
	
	function removeLibrary(){
		//var retValue=window.showModalDialog("removeLibraryPage.jsp",window,"dialogHeight:100px,dialogWidth:100px, status:0, edge:sunken");
	
		//if(retValue){
		var selectFile = fb.getSelectedFile();
		//alert(selectFile.length);
		var libIds = "";
		for(var i=0;i<selectFile.length;i++){
			libIds += selectFile[i].id+",";
		}
		var url = "ComponentVersionServlet?flag=removeLibrary&libIds="+libIds;
		ajaxSend(url,true);	
			//alert(retStr);
			//removeRow(retValue);
		//	fb.remove(retValue);
		//}
		
		fb.remove();
	}
	
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
	function uploadFile(){
		var obj = document.getElementById("filePath");
		obj.value = fb.getFullPath().substring(1);
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
		var lib = msg.split('|');
		for(var i=0;i<lib.length-1;i++){
			var li = lib[i].split(',');
			var id = li[0];
			var path = li[1];
			
			fb.addFile(id,path);
		}
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
  
  <body BGCOLOR="#FAF0E6"  onload="inithere()" >
  <script language="javascript"> 
  	//var pNav = parent.navigator.innerText;
  	//parent.navigator.innerText=pNav;
  	//parent.navigation.innerHTML='<a href="PDMServlet?pdm=BuildManagement">build management</a>>><a href="repositoryPage.jsp" target="contentFrame"">repository</a>';
  	nav = new Navigation("navigation",true);
  	nav.add('product category','PDMServlet?pdm=ProductCategory');
  	nav.add('product','ProductServlet?flag=navigation','contentFrame');
  	nav.add('version','ProductVersionServlet?flag=navigation&state=external','contentFrame');
  	nav.show();
  	
  	<%
  		String flag = (String)session.getAttribute("isProduct");
  		if(flag.equals("yes")){
  	%>
	parent.leftFrame.showTree();
	<%}%>
  </script>
    <table border="1" bgcolor="#CDCDC1" width="100%" align="center" CELLPADDING="0" CELLSPACING="0">
	<tbody>
	
	<tr>
		<td height="700px" colspan=3 width="100%" valign="top" bgcolor="c0c0c0">
		
				<div STYLE="position:relative; left:0; top:0; width:100%; border:none thin gray">
					<table STYLE="width:100%"  CELLPADDING="0" CELLSPACING="0" bgcolor="c0c0c0" border="0">
						<tr>
						
							<%//if(tabName == "t1"){
							 %>
							
							<td ID="t1" CLASS="selTab" HEIGHT="25" width="180" onclick="changeTabs(event)">Libraries</td>
							
							
							
							<!--
							<td ID="t5" CLASS="tab" width="120">View Specifications</td>
							 -->
						</tr>
						<tr>
							<td ID="t1base" STYLE="height:2; border-left:solid thin white"></td>
							 
							<td ID="t2base" STYLE="height:2; background-color:white; border-right:solid thin white"></td>
							
							<td ID="t3base" STYLE="height:2; background-color:white; border-left:solid thin white"></td>
							
							<td ID="t4base" STYLE="height:2; background-color:white; border-left:solid thin white"></td>
							<!-- 
							<td ID="t5base" STYLE="height:2; background-color:white; border-left:solid thin white"></td>
							-->
						</tr>
						<tr>
							<td valign="top" HEIGHT="*" COLSPAN="4" ID="tabContents" STYLE="border-left:solid thin white;border-right:solid thin white"> 
							<div CLASS="cont" ID="t1Contents" STYLE="position:relative; left:10" >
							<p>&nbsp;</p>
							<h3>Version: <%=version %></h3>
						
					 		
							<div style="float:left;width:80%;height:250px;overflow:auto;border-style:outset" >
							
							<a href="javascript: goBack()" style="position:relative;left:50;top:5"><img src="images/filebrowser/base/back.png" /></a>
							<a href="javascript: goHome()" style="position:relative;left:50;top:5"><img src="images/filebrowser/base/home.png" /></a>
							<input type="text" id = "fullPath" value="/" style="width:250px;position:relative;left:50;">
							<a href="javascript: createFolder()" style="position:relative;left:50;top:5"><img src="images/filebrowser/folder_add.png" /></a>
							<input type="text" id = "newFolder" style="width:100px;position:relative;left:50;">
							<div id="librarys" style="border-style:inset;background-color:#fff;overflow:auto;height:200px;width:80%;position:relative;left:50"></div>
							
							</div>
							
							<div style="position:relative; left:10;float:left;width:15%;height:250px;overflow:auto;border-style:outset">
					 			
					 			<input type="submit" name="remove" value="Remove" style="height:30px;width:70px;position:relative;left:20;top:50;" onclick="removeLibrary()" /><p>
								<input type="submit" name="download" value="Download" style="height:30px;width:70px;position:relative;left:20;top:70" onclick="downloadLibrary()" /><p>
							</div>
							
							<p>&nbsp;&nbsp;</p>
							<p>&nbsp;&nbsp;</p>
							<input type="submit" name="add" value="Add" height="30px" style="position:relative;left:20;top:30"onclick="addLibrary()" />
							<input type="submit" value="upload" style="position:relative;left:20;top:30" onclick="uploadFile()" >
							<div id="load" style="clear:both;width:97%;height:180px;overflow:auto;border-style:outset;background-color:#fff;position:relative;top:30">
					
							<form id="fileUpload" method="post" action="UploadFileServ"  enctype="multipart/form-data" target="hidden_frame">
							<iframe name='hidden_frame' id="hidden_frame" style='display:none'></iframe>
							<input type="hidden" id = "filePath" name="product" value="new">
							<table id="fileTable" width="100%" border=1>
								
						
							</table>
							</form> 
							</div>
						</div>
							</td>
						</tr>
					</table>
				</div>
				
  		</td>
	</tr>
</tbody>
</table>
  </body>
</html>
