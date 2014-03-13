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
		LibraryList libList = (LibraryList)session.getAttribute("componentLibraryList");
		String version = (String)session.getAttribute("componentVersion");
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
	
	function importLibraryDialog(){
		var retValue=window.showModalDialog("importLibraryPage.jsp",window,"dialogHeight:600px,dialogWidth:400px, status:0, edge:sunken");
	
		if(retValue&&retValue.length>0){
			//alert(retValue.length);
			var id = '';
			for(var i=0;i<retValue.length;i++){
				if(retValue[i]){
					id += retValue[i] + ",";
				}
				
			}
			location.href="ComponentVersionServlet?flag=importLibrary&buildId="+id;
		}
	}
	
	function addDependence(){
		var retValue = window.showModalDialog("addDependencePage.jsp",window,"dialogHeight:600px,dialogWidth:400px, status:0, edge:sunken");
		
		if(retValue){
			/*var id = '';
			/
			for(var i=0;i<retValue.length;i++){
				if(retValue[i]){
					id += retValue[i] + ",";
				}
			}
			*/
			var url="ComponentVersionServlet?flag=addDependence&componentIds="+retValue;
			var retStr = ajaxSend(url,false);
			//alert(retStr);
			if(retStr){
				var table = document.getElementById("dependenceTable");
				var length = table.rows.length;
				for(var i=1;i<length;i++){
					table.deleteRow(i);
					length=length-1;
         			i=i-1;
				}
				var str=retStr.split('|');
				for(var i=0;i<str.length;i++){
					var text = str[i].split(',');
					if(text.length==4){
				
					//var array = new Array(3);
					//var width = new Array(3);
					
						var id = text[0];
						var version = text[1];
						var component = text[2];
						var category = text[3];
						//alert(id);
						var newRow = table.insertRow(-1);
						newRow.id = "dependenceId"+id;
						var url = "<a href=\"javascript: selectDependence("+id+")\">"+component+"</a>";
						
						var cell0 = document.createElement("td");
						cell0.innerHTML = url;
						cell0.setAttribute("width","150");
						var cell1 = document.createElement("td");
						cell1.innerHTML = category;
						cell1.setAttribute("width","250");
						var cell2 = document.createElement("td");
						cell2.innerHTML = version;
						cell2.setAttribute("width","100");
						var cell3 = document.createElement("td");
						cell3.innerHTML = "<a href=\"javascript: removeDependence("+id+")\">remove</a>";
						newRow.appendChild(cell0);
						newRow.appendChild(cell1);
						newRow.appendChild(cell2);
						newRow.appendChild(cell3);
					}
				
				}
				
			}
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
	
	function removeDependence(id){
		//alert(id);
		var table = document.getElementById("dependenceTable");
		
		var tr = document.getElementById("dependenceId"+id);
		//alert(tr);
		table.deleteRow(tr.rowIndex);
		
		var url = "ComponentVersionServlet?flag=removeDependence&dependenceId="+id;
		ajaxSend(url,false);
	}
	
	function selectProduct(productid){
	
		var url = "ComponentVersionServlet?flag=selectProduct&productId="+productid;
		//alert(url);
		var retStr = ajaxSend(url,false);
		
		//parent.leftFrame.showTree();
		
		parent.leftFrame.location.href = "productLeftPage.jsp";
		
		location.href = "productComponentPage.jsp";
	}
	
	function selectDependence(id){
		
		var url = "ProductVersionServlet?flag=selectComponent&componentId="+id;
		
		var retStr = ajaxSend(url,false);
		
		location.href = "componentLibraryPage.jsp";
	}
	
	function removefile(obj){
		//alert(id);
		//var table = document.getElementById("fileTable");
		//for(var i=0;i<table.rows.length;i++){
		//	if(table.rows[i].id=="tr"+id)
		//		table.deleteRow(i);
		//}
		//alert(obj);
		var row=obj.parentNode.parentNode;
		//alert(row.length);
        var tab=row.parentNode;
        tab.deleteRow(row.rowIndex);
		
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
  	nav.add('component category','PDMServlet?pdm=ComponentCategory');
  	nav.add('component','ComponentServlet?flag=navigation','contentFrame');
  	nav.add('version','ComponentVersionServlet?flag=navigation','contentFrame');
  	nav.show();
  	
  	<%
  		String flag = (String)session.getAttribute("isFlag");
  		if(flag.equals("no")){
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
							
							<td ID="t2" CLASS="tab" width="180" onclick="changeTabs(event)">Where Used</td>
							
							<td ID="t3" CLASS="tab" width="180" onclick="changeTabs(event)">Dependences</td>
							 
							<td ID="t4" CLASS="tab" width="150">&nbsp;</td>
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
					 			<!--  
					 			<input type="submit" name="test" value="Test" style="height:30px;width:70px;position:relative;left:20;top:60;" onclick="importLibraryDialog()" /><p>
								-->
								<input type="submit" name="download" value="Download" style="height:30px;width:70px;position:relative;left:20;top:70" onclick="downloadLibrary()" /><p>
							</div>
							
							<p>&nbsp;&nbsp;</p>
							<p>&nbsp;&nbsp;</p>
							<input type="submit" name="add" value="Add" height="30px" style="position:relative;left:20;top:30"onclick="addLibrary()" />
							<input type="submit" value="upload" style="position:relative;left:20;top:30" onclick="uploadFile()" >
							<div id="load" style="clear:both;width:97%;height:220px;overflow:auto;border-style:outset;background-color:#fff;position:relative;top:30">
					
							<form id="fileUpload" method="post" action="UploadFileServ"  enctype="multipart/form-data" target="hidden_frame">
							<iframe name='hidden_frame' id="hidden_frame" style='display:none'></iframe>
							<input type="hidden" id = "filePath" name="component" value="new">
							<table id="fileTable" width="100%" border=1>
								
						
							</table>
							</form> 
							</div>
						</div>
				
						<div CLASS="cont" ID="t2Contents" STYLE="position:relative; left:15">
					
					 		<p>&nbsp;</p>
					 		<h3>Version: <%=version %></h3>
							<div style="border-style:inset;overflow:auto;height:400px;width:700">
							 <table  border=1 width="550px" align="center">
    							<tr bgcolor=Orange>
    								<th width="150px">Product </th><th width="250px">Product Category</th><th width="100px">Version</th>
    							</tr>
    					<%
    						ProductVersionList pVersionList = (ProductVersionList)session.getAttribute("productVersionList");
    						ProductCategoryList pCategoryList = (ProductCategoryList)session.getAttribute("productCategoryList");
    						ProductList proList = (ProductList)session.getAttribute("productList");
      						for(int i=0;i<pVersionList.size();i++)
      						{
      							ProductVersion pVersion = pVersionList.get(i);
      							Product pro = proList.get(i);
      							ProductCategory category = pCategoryList.get(i);
      							
      					%>
    							<tr>
    								<td width="150px"><a href="javascript: selectProduct(<%=pVersion.getId() %>)"><%=pro.getName() %></a></td>   	
	    							<td width="250px"><%=category.getName() %></td>
	    							<td width="100px"><%=pVersion.getVersion() %></td>
	    					
       							</tr>
       					<%} %>
      						</table>
      						</div>
						</div>
				
						<div CLASS="cont" ID="t3Contents" STYLE="position:relative; left:15">
						<p>&nbsp;</p>
						<input type="button" value="Add" onclick="addDependence()">
						<div style="border-style:inset;overflow:auto;height:400px;width:700">
						 <table id="dependenceTable" border=1 width="520px" align="center">
    							<tr bgcolor=Orange>
    								<th width="150px">Component </th><th width="250px">Component Category</th><th width="100px">Version</th><th width="20">remove</th>
    							</tr>
								<% ComponentVersionList versionList = (ComponentVersionList)session.getAttribute("versionDependenceList");
								ComponentList componentList = (ComponentList)session.getAttribute("componentDependenceList");
								ComponentCategoryList categoryList = (ComponentCategoryList)session.getAttribute("categoryDependenceList");
								for(int i=0;i<versionList.size();i++){
									ComponentVersion cVersion = versionList.get(i);
									Component com = componentList.get(i);
									ComponentCategory cCategory = categoryList.get(i);
							 	%>
								<tr id="dependenceId<%=cVersion.getId() %>">
									<td width="150px"><a href="javascript: selectDependence(<%=cVersion.getId() %>)"><%=com.getName() %></a></td>
									<td width="250px"><%=cCategory.getName() %></td>
									<td width="100px"><%=cVersion.getVersion() %></td>
									<td width="20px"><a href="javascript: removeDependence(<%=cVersion.getId() %>)">remove</a></td>
								</tr>
								<%	} %>
						</table>
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
