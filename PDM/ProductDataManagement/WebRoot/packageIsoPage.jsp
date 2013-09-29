<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'packageIsoPage.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">

	<link rel="stylesheet" type="text/css" href="css/styles.css">
	<script type="text/javascript" src="js/pager.js"></script>
	<script type="text/javascript" src="js/fileBrowser.js"></script>
	<script type="text/javascript">
	fb = new FileBrowser('fb',"setupFile");
	function initHere(){
		
		var selectObj = document.getElementById("setupList");
		var url = "ProductVersionServlet?flag=getDependenceLibrary";
		var retStr = ajaxSend(url,false);
		//alert(retStr);
		if(retStr){
			//alert(retStr);
			var libs = retStr.split('|');
			for(var i=0;i<libs.length-1;i++){
				var lib = libs[i].split(',');
				selectObj.options.add(new Option(lib[1],lib[0]));
			}
		}
		
		url = "ProductVersionServlet?flag=getTree";
		retStr = ajaxSend(url,false);
		//alert(retStr);
		if(retStr){
			var trees = retStr.split('|');
			for(var i=0;i<trees.length-1;i++){
				var tree = trees[i].split(',');
				if(tree.length==2){
					var id = tree[0];
					var path = tree[1];
					//alert("ss");
					//alert(path);
					fb.add(id, path);
					fb.show();
				}
			}
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
	}
	
	function inputSelect(){
		var selectObj = document.getElementById('setupList');
		//alert("ss");
		var id = selectObj.options[selectObj.selectedIndex].value;
		var name = selectObj.options[selectObj.selectedIndex].text;
		//alert(name);
		
		fb.addFile(id,name);
		selectObj.options.remove(selectObj.selectedIndex);
	}
	
	function outputSelect(){
		var selectObj = document.getElementById('setupList');
		var file = fb.remove();
		selectObj.options.add(new Option(file.name,file.ext));
	}
	
	function sendTo(){
		var files = fb.getFiles();
		//alert(files.length);
		var value = new Array(files.length);
		var str = '';
		for(var i=0;i<files.length;i++){
			str += files[i].id+","+files[i].path+files[i].name+"|";
			//alert(str);
			value[i] = str;
		}
		//alert(str);
		window.returnValue = str;
		window.close();
	}
	function cancel(){
		window.close();
	}
	</script>
	
  </head>
  
  <body bgcolor="#CDCDC1" onload="initHere()" >
  <div id="main" >
    <div style="float:left; height:350px; width:45%;">
    	<p>Dependence setup file</p>
    	<div style="height:295px;width:100%;border-style:inset;background-color:#fff;overflow:auto;position:relative;top:7;right:5">
    		<select id="setupList" multiple size="17" style="width:100%" >
    			
    		</select>
    	</div>
    </div>
    <div style="float:left;height:350px;width:10%;">
    <input type="button" value=">>" style="position:relative;top:130px;left:8" onclick="inputSelect()">
    <input type="button" value="<<" style="position:relative;top:170px;left:8" onclick="outputSelect()">
    </div>
    <div style="float:right;height:350px;width:45%;">
    	<a href="javascript: goBack()" style="position:relative;top:5"><img src="images/filebrowser/base/back.png" /></a>
		<a href="javascript: goHome()" style="position:relative;top:5"><img src="images/filebrowser/base/home.png" /></a>
		<input type="text" id = "fullPath" value="/" style="width:140px;">
		<a href="javascript: createFolder()" style="position:relative;top:5"><img src="images/filebrowser/folder_add.png" /></a>
		<input type="text" id = "newFolder" style="width:60px;">
    	<div id="setupFile" style="height:295px;width:100%;border-style:inset;background-color:#fff;overflow:auto;position:relative; right:5">
    	</div>
    </div>
    <input type="button" value="Submit" onclick="sendTo()">
    <input type="button" value="Cancel" onclick="cancel()">
    </div>
  </body>
</html>
