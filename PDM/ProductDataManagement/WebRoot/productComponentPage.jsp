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
	<% ComponentCategoryList categoryList = (ComponentCategoryList)session.getAttribute("categoryList");
    	ComponentList comList = (ComponentList)session.getAttribute("componentList");
		ComponentVersionList versionList = (ComponentVersionList)session.getAttribute("componentVersionList");

		ProductDependenceList pDepList = (ProductDependenceList)session.getAttribute("pDependenceList");

		String version = (String)session.getAttribute("productVersion");
		String versionId = (String)session.getAttribute("productVersionId");
	%>

	d = new dTree('d',"componentfile","noChildren");
	dd = new dTree('dd',"dependencefile","noChildren");
	function addComponentDialog(){
		var retValue=window.showModalDialog("addComponentPage.jsp",window,"dialogHeight:600px,dialogWidth:400px, status:0, edge:sunken");
	
		if(retValue&&retValue.length>0){
			//alert(retValue.length);
			var id = '';
			for(var i=0;i<retValue.length;i++){
				if(retValue[i]){
					//alert(retValue[i]);
					id += retValue[i] + ",";
				}
				
			}
			
			//alert(id);
			location.href="ProductVersionServlet?flag=addComponent&componentIds="+id;
		}
	}
	
	function removeComponentDialog(){
		var retValue=window.showModalDialog("removeComponentPage.jsp",window,"dialogHeight:100px,dialogWidth:100px, status:0, edge:sunken");
	
		if(retValue){
			
			var url = "ProductVersionServlet?flag=removeComponent&componetName="+retValue;
			ajaxSend(url,true);
			//alert(retStr);
			removeRow(retValue);
		}
	}
	
	function removeComponent(id){
		//alert(id);
		location.href = "ProductVersionServlet?flag=deleteComponent&componentId="+id;
	}
	
	
	function selectComponent(id){
	
		var url = "ProductVersionServlet?flag=selectComponent&componentId="+id;
		var retStr = ajaxSend(url,false);
		
		//parent.leftFrame.showTree();
		
		parent.leftFrame.location.href = "componentLeftPage.jsp";
		
		location.href = "componentLibraryPage.jsp";
		
		
	}
	function removefile(){
		var table = document.getElementById("setupTable");
		var fileTable = document.getElementById("fileTable");
		/*
		if(table.rows.length<3){
			return;
		}
		var row=obj.parentNode.parentNode;
		//alert(row.length);
        var tab=row.parentNode;
        tab.deleteRow(row.rowIndex);
		*/
		var id = "<%=versionId %>";
		var checkbox = document.getElementsByName("checkbox");
		var length = table.rows.length;
		for(var i=0;i<length;i++){
			if(checkbox[i].checked){
				var row=checkbox[i].parentNode.parentNode;
				var text = row.cells[1].innerHTML;
				var sIndex = text.indexOf("libId=")+6;
				if(sIndex>6){
				    var eIndex = text.indexOf("\"",sIndex);
					var libId = text.substring(sIndex,eIndex);
					var url = "ProductVersionServlet?flag=removeFile&issId="+libId;
					ajaxSend(url,false);
				}
				table.deleteRow(row.rowIndex);
				length=length-1;
         		i=i-1;
         		
         		text = row.cells[2].innerHTML;
         		sIndex = text.indexOf(">")+1;
         		if(sIndex>1){
         			var eIndex = text.indexOf("<",sIndex);
         			var fileName = text.substring(sIndex,eIndex);
         			var len = fileTable.rows.length;
         			var flag = true;
         			for(var j=0;j<len;j++){
         				var oRow = fileTable.rows[j];
         				if(oRow.id == id){
         					if(flag){
         						flag = false;
         					}else{
         						var str = oRow.cells[0].innerHTML;
         						sIndex = str.indexOf("value=\"")+7;
         						if(sIndex>7){
         							eIndex = str.indexOf("\"",sIndex);
         							var name = str.substring(sIndex,eIndex);
         							if(name == fileName){
         								fileTable.deleteRow(oRow.rowIndex);
         								len--;
         								j--;
         							}
         						}
         					}
         				}
         			}
         		}
			}
			
		}
		
	}
	
	function removeSetupFile(id){
		
		var table = document.getElementById("setupTable");
		
		var tr = document.getElementById("setupId"+id);
		//alert(tr);
		table.deleteRow(tr.rowIndex);
		
		var url = "ProductVersionServlet?flag=removeSetupFile&setupFileId="+id;
		ajaxSend(url,false);
		
		
	}
	
	function changeDependenceLocation(obj){
		var location = obj.value;
		var fileId = obj.name;
		//alert(location);
		if(location=="")
			location=".";
		
		var url = "ProductVersionServlet?flag=changeDependenceLocation&fileId="+fileId+"&location="+location;
		ajaxSend(url,false);
		
		dd.clear();
  		dd.add(0,-1,"");
  		url = "ProductVersionServlet?flag=getDependenceFile";
  		createDependenceTree(url,dd);
  		dd.show();
	}
	
	function changeLocation(obj){
		var location = obj.value;
		var libId = obj.name;
		//alert(location);
		if(location=="")
			location=".";
		var url = "ProductVersionServlet?flag=changeLocation&libId="+libId+"&location="+location;
		ajaxSend(url,false);
		
		dd.clear();
  		dd.add(0,-1,"");
  		url = "ProductVersionServlet?flag=getDependenceFile";
  		createDependenceTree(url,dd);
  		dd.show();
	}
	
	function changeComponentLocation(obj){
		var location = obj.value;
		var libId = obj.name;
		
		if(location=="")
			location=".";
		var url = "ProductVersionServlet?flag=changeComponentLocation&componentId="+libId+"&location="+location;
		ajaxSend(url,true);
		
		d.clear();
		d.add(0,-1,"");
		var url = "ProductVersionServlet?flag=getLibrary";
  		createTree(url,d);
  		d.show();
	}
	
	function removeDependence(id){
		//alert(id);
		var table = document.getElementById("fileTable");
		
		var length = table.rows.length;
		for(var i=0;i<length;i++){
			var row = table.rows[i];
			if(row.id==id){
				table.deleteRow(row.rowIndex);
				length=length-1;
         		i=i-1;
			}
		}
		
		var depTable = document.getElementById("dependenceTable");
		length = depTable.rows.length;
		for(var i=0;i<length;i++){
			var row = depTable.rows[i];
			if(row.id==id){
				depTable.deleteRow(row.rowIndex);
				length--;
				i--;
			}
		}
		//alert(length);
		//var tr = document.getElementById(id);
		//alert(tr);
		//table.deleteRow(tr.rowIndex);
		
		var url = "ProductVersionServlet?flag=removeDependence&dependenceId="+id;
		ajaxSend(url,false);
		
		dd.clear();
  		dd.add(0,-1,"");
  		url = "ProductVersionServlet?flag=getDependenceFile";
  		createDependenceTree(url,dd);
  		dd.show();
	}
	
	function selectDependence(id){
		var url = "ComponentVersionServlet?flag=selectProduct&productId="+id;
		//alert(url);
		var ret = ajaxSend(url,false);
		//alert(ret);
		//parent.leftFrame.showTree();
		parent.leftFrame.location.href = "productLeftPage.jsp";
		if(ret=='internal'){
			location.href = "productComponentPage.jsp";
		}else if(ret=='external'){
			location.href = "externalProductPage.jsp";
		}
		
	}
	
	function packageIss(){
		
		var checkbox = document.getElementsByName("checkbox");
		var table = document.getElementById("setupTable");
		//var save = table.innerHTML;
		//alert(save);
		//var rows = [];
		var length = table.rows.length;
		for(var i=0;i<length;i++){
			if(!checkbox[i]){
				continue;
			}
			if(!checkbox[i].checked){
				checkbox[i].checked = true;
				//var value = checkbox[i].value;
				//var row=checkbox[i].parentNode.parentNode;
				//table.deleteRow(row.rowIndex);
				//length=length-1;
         		//i=i-1;
         		checkbox[i].value = 'no';
			}else{
				checkbox[i].value = 'yes';
			}
			//alert(table.innerHTML);
		}
		//alert("ss");
		//alert(table.innerHTML);
		
		//document.getElementById("fileUpload").submit();
		//table.innerHTML = save;
		
		document.getElementById("fileUpload").submit();
		
		for(var i=0;i<length;i++){
			checkbox[i].checked = false;
		}
		
	}	
	
	function callback(msg)   
	{   
		//alert(msg);
       	var start = 0;
       	var index = msg.indexOf("</a>",start);
       	//var sss = "s</as>ws</a>swcww";
       	//alert(sss.indexOf("</a>",0));
       	//alert(msg);
       	var table = document.getElementById("setupTable");
       	while(index!=-1){
       		
       		var str = msg.substring(start,index+4);
       		//alert(index);
       		//alert(str);
       		//var newRow = table.insertRow(-1);
       		//newRow.id = "setupId"+libId;
       		var sIndex = str.indexOf("libId=")+6;
	       	var eIndex = str.indexOf("\"",sIndex);
	       	var libId = str.substring(sIndex,eIndex);
	       	
	       	sIndex = str.indexOf(">")+1;
	       	eIndex = str.indexOf("<",sIndex);
	       	var libName = str.substring(sIndex,eIndex);
	       	var lIndex = libName.lastIndexOf("/")+1;
	       	var fileName = libName;
	       	var filePath = ".";
	       	if(lIndex>1){
	       		fileName = libName.substring(lIndex);
	       		filePath = libName.substring(0,lIndex);
	       		str = str.substring(0,sIndex)+fileName+str.substring(eIndex);
	       	}
	       	
	       	//alert(fileName+"-----"+filePath);
	       	var row;
	       	//alert(table.rows.length);
	       	var flag = true;
	       	for(var i=1;i<table.rows.length;i++){
       			row = table.rows[i];
       			var text = row.cells[1].innerHTML;
       			sIndex = text.indexOf(">")+1;
       			if(sIndex>1){
       				eIndex = text.indexOf("<",sIndex);
       				text = text.substring(sIndex,eIndex);
       			}
       			//alert(text+'---'+fileName+'---'+str);
       			if(text==fileName||text==str){
       				if(flag){
       					row.cells[1].innerHTML = str;
			       		//var newTd0 = newRow.insertCell(0);
			       		//newTd0.innerHTML = '<input type="checkbox" name="checkbox" /><input type="text" value="'+libId+'" name="text" style="display:none"/>'
				       	//newTd0.setAttribute("width","10px");
				       	
				       //	var newTd1 = newRow.insertCell(1);
				       	//newTd1.innerHTML = str;
				       //	newTd1.setAttribute("width","150px");
				       //	var newTd2 = newRow.insertCell(2);
				       	//alert(newTd2);
				       //	newTd2.innerHTML = ".exe";
				       //	newTd2.setAttribute("width","50px");
				       	
				       	start = index + 4;
				       	index = msg.indexOf("</a>",start);
				      	
				      	str = msg.substring(start,index+4);
				      	sIndex = str.indexOf("libId=")+6;
				       	eIndex = str.indexOf("\"",sIndex);
				       	libId = str.substring(sIndex,eIndex);
				       	
				       	row.cells[2].innerHTML = str;
				       	//alert(str);
				       //	var newTd3 = newRow.insertCell(3);
				       //	newTd3.innerHTML = str;
				       //	newTd3.setAttribute("width","150px");
				       	
				       	start = index + 4;
				       	index = msg.indexOf("</a>",start);
				       	flag = false;
       				}else{
       					table.deleteRow(row.rowIndex);
       				}
       				
       			}
       		}	
    	}
    	
    	var url = "ProductVersionServlet?flag=getSetupFile";
    	var retStr = ajaxSend(url,false);
    	if(retStr){
    		alert(retStr);
    		var table = document.getElementById("fileTable");
    		var id = "<%=versionId %>";
    		//alert(id);
		//alert(id);
			var flag = true;
			var length = table.rows.length;
			for(var i=1;i<length;i++){
				var row = table.rows[i];
				if(row.id==id){
					//alert(row.id);
					if(flag){
						flag = false
					}
					else{
						table.deleteRow(row.rowIndex);
						length--;
						i--;
					}
				}
			}
			var libs = retStr.split('|');
			for(var i=0;i<libs.length-1;i++){
				var lib = libs[i].split(',');
				var libId = lib[0];
				var libName = lib[1];
				
				var newRow = table.insertRow(i+2);
				newRow.style.display = "none";
				newRow.id = id;
				var cell0 = newRow.insertCell(0);
				cell0.innerHTML = '<div style="width:250px;"><input type="text" value="'+libName+'" readonly size=35 style="background-color:#c0c0c0;color:#000;"></div>';
				cell0.setAttribute("width","250px");
				
				var cell1 = newRow.insertCell(1);
				cell1.innerHTML = '<div style="width:350px;"><input type="text" name="'+libId+'" value="'+libName+'"  size=52 onchange="changeLocation(this)"/></div>';
				cell1.setAttribute("width","350px");
				cell1.setAttribute("colspan","3");
			}
    	}
	}  
	
	function addDependence(){
		var retValue = window.showModalDialog("addProductDependencePage.jsp",window,"dialogHeight:600px,dialogWidth:400px, status:0, edge:sunken");
		
		if(retValue&&retValue.length>0){
			var id = '';
			
			for(var i=0;i<retValue.length;i++){
				if(retValue[i]){
					id += retValue[i] + ",";
				}
			}
			//alert(id);
			var url="ProductVersionServlet?flag=addDependence&productIds="+id;
			var retStr = ajaxSend(url,false);
			
			if(retStr){
				
				var table = document.getElementById("fileTable");
				var depTable = document.getElementById("dependenceTable");
				var str=retStr.split('|');
				for(var i=0;i<str.length;i++){
					var text = str[i].split(',');
					if(text.length==6){
						var id = text[0];
						var version = text[1];
						var dependence = text[2];
						var fileId = text[3];
						var fileName = text[4];
						var location = text[5];
						//alert(location);
						if(i==0){
							//var url = "<a href=\"javascript: selectDependence("+id+")\">"+dependence+' '+version+"</a>";
							var url = "<div style=\"width:530px;\"><a href=\"javascript: selectDependence("+id+")\">"+dependence+' '+version+"</a></div>";
							var newRow = table.insertRow(-1);
							newRow.id = id;
							newRow.setAttribute("bgcolor","orange");
							var cell0 = document.createElement("td");
							cell0.innerHTML = url;
							cell0.setAttribute("width","530px");
							cell0.setAttribute("colspan","3");
							
							
							
							
							var cell1 = document.createElement("td");
							cell1.innerHTML = "<a href=\"javascript: collapse("+id+")\">collapse</a>";
							cell1.setAttribute("width","70");
							/*
							var cell2 = document.createElement("td");
							cell2.innerHTML = "<a href=\"javascript: removeDependence("+id+")\">remove</a>";
							cell2.setAttribute("width","70");
							*/
							newRow.appendChild(cell0);
							newRow.appendChild(cell1);
							//newRow.appendChild(cell2);
							
							var depRow = depTable.insertRow(-1);
							var depCell0 = depRow.insertCell(0);
							depCell0.setAttribute("width","400px");
							depCell0.innerHTML = dependence;
							
							var depCell1 = depRow.insertCell(1);
							depCell1.setAttribute("width","130px");
							depCell1.innerHTML = version;
							
							var depCell2 = depRow.insertCell(2);
							depCell2.setAttribute("width","70px");
							depCell2.innerHTML = '<a href="javascript: removeDependence('+id+')">remove</a>';
							
						}
						
						var newRow = table.insertRow(-1);
						newRow.id = id;
						var cell0 = document.createElement("td");
						cell0.innerHTML = '<div style="width:250px;"><input type="text" value="'+fileName+'" disabled size=35 style="background-color:#c0c0c0;color:#000;"></div>';
						cell0.setAttribute("width","250");
						var cell1 = document.createElement("td");
						cell1.innerHTML = '<div style="width:350px;"><input type="text" name="'+fileId+'" value="'+location+'" size=52 onchange="changeDependenceLocation(this)" /></div>';
						cell1.setAttribute("width","350");
						cell1.setAttribute("colspan","3");
						
						/*
						var cell3 = document.createElement("td");
						cell3.innerHTML = "<input type='text' value='"+location+"' onchange='changeLocation(this)' size=35 />";
						cell3.setAttribute("width","250");
						var cell4 = document.createElement("td");
						cell4.innerHTML = ;
						cell4.setAttribute("width","20");
						*/
						newRow.appendChild(cell0);
						newRow.appendChild(cell1);
						
						
					}
				
				}
			}
		}
		dd.clear();
  		dd.add(0,-1,"");
  		url = "ProductVersionServlet?flag=getDependenceFile";
  		createDependenceTree(url,dd);
  		dd.show();
	}
	
	function collapse(id){
		var table = document.getElementById("fileTable");
		//alert(id);
		var flag = true;
		var length = table.rows.length;
		for(var i=0;i<length;i++){
			var row = table.rows[i];
			if(row.id==id){
				if(flag){
					flag = false
				}
				else{
					
					var display = row.style.display;
					
					if(display=="none"){
						
						row.style.display = "block";
					}else{
						row.style.display = "none";
					}
				}
			}
		}		
	}
	
	
	
	function downloadISO(){
		//var retValue=window.showModalDialog("packageIsoPage.jsp",window,"dialogHeight:600px,dialogWidth:800px, status:0, edge:sunken");
	
		//if(retValue&&retValue!=''){
		var root = document.getElementById("rootDirectory");
		var index = root.value.indexOf("/");
		if(index>-1){
			alert("input name error");
			return;
		}
		//alert(root.value);
		var url = "ProductVersionServlet?flag=packageIso&root="+root.value;
			
		location.href = url;
		//}
	}
	/*
	function addfile(){
		//var retValue=window.showModalDialog("addLibraryPage.jsp",window,"dialogHeight:200px,dialogWidth:400px, status:0, edge:sunken");
		
		var testTb1 = document.getElementById("fileTable");
        var newTr = testTb1.insertRow(-1);
        //newTr.id = "tr"+id;
        var newTd0 = newTr.insertCell();
       // var newTd1 = newTr.insertCell();
        //var newTd2 = newTr.insertCell();
        newTd0.innerHTML = "<input type=\"file\" name=\"inputFile\"> <input type=\"button\" value=\"-\" onclick=\"removefile(this)\"> <input type=\"button\" value=\"+\" onclick=\"addfile()\">"; 
       // newTd1.innerHTML= "<input type=\"file\" name=\"test1\">";
       // newTd2.innerHTML= "<input type=\"file\" name=\"test1\">";
       
	}*/
	var inputId = 0;
	function openBrowser(){
		var table = document.getElementById("setupTable");
		
		var newRow = table.insertRow(-1);
		//newRow.id = id;
		var cell0 = document.createElement("td");
		cell0.innerHTML = '<input type="checkbox" name="checkbox" value="'+inputId+'" /><input type="file" class="hiddenfile" id="file'+inputId+'" name="file'+inputId+'" />';
		//alert(cell0.innerHTML);
		cell0.setAttribute("width","7");
		var cell1 = document.createElement("td");
		cell1.innerHTML = '';
		cell1.setAttribute("width","100");
		var cell2 = document.createElement("td");
		cell2.innerHTML = "";
		cell2.setAttribute("width","250");
		/*
		var cell3 = document.createElement("td");
		cell3.innerHTML = '<input type="text" value="." name="text" size=35/>';
		cell3.setAttribute("width","250");
		*/
		
		newRow.appendChild(cell0);
		newRow.appendChild(cell1);
		newRow.appendChild(cell2);
		//newRow.appendChild(cell3);
		
		var obj = document.getElementById("file"+inputId);
		var ie=navigator.appName=="Microsoft Internet Explorer"?true:false;
		if(ie){
			obj.click();
			//document.getElementById("filename").value=document.getElementById("file").value;
		}else{
			var a=document.createEvent("MouseEvents");//FF的处理
			a.initEvent("click",true,true);
			obj.dispatchEvent(a);
			
		}
		
		obj.onchange = addfile;
	}
	
	function addfile(){
		var obj = document.getElementById("file"+inputId);
		var value = obj.value;
		
		var table = document.getElementById("setupTable");
		
		var index = value.lastIndexOf("\\");
		value = value.substring(index+1);
		//alert(value);
		
		
		for(var i=0;i<table.rows.length-1;i++){
			var row = table.rows[i];
			var text = row.cells[1].innerHTML;
			if(text==value){
				table.deleteRow(table.rows.length-1);
				return;
			}
			else{
				var sIndex = text.indexOf(">")+1;
				if(sIndex>0){
					var eIndex = text.indexOf("<",sIndex);
					var name = text.substring(sIndex,eIndex);
					//alert(name);
					if(name==value){
						
						var lastRow = table.rows[table.rows.length-1];
						lastRow.cells[1].innerHTML = row.cells[1].innerHTML;
						lastRow.cells[2].innerHTML = row.cells[2].innerHTML;
						
						table.deleteRow(row.rowIndex);
						inputId++;
						return;
					}
				}
			}
		}
		
		var lastRow = table.rows[table.rows.length-1];
		lastRow.cells[1].innerHTML = value;
		inputId++;
		//alert(table);
		
		
		//alert(newRow);
		
	}
	
	function importProductFile(){
		var retValue = window.showModalDialog("importProductFile.jsp",window,"dialogHeight:600px,dialogWidth:400px, status:0, edge:sunken");
	}
	
	function createTree(url,obj){
		var retStr = ajaxSend(url,false);
  		//alert(retStr);
  		
  		if(retStr){
  			var cc = retStr.split('|');
  			
  			var id = 1;
  			for(var i=0;i<cc.length-1;i++){
  				var com = cc[i].split(',');
  				//alert(com.length);
  				if(com.length<4){
  					continue;
  				}
  				var name = com[0]+'_'+com[1];
  				//alert(name);
  				obj.add(id,0,name);
  				var tId = id;
  				id++;
  				var paths = new Array();
  				var pathId = new Array();
  				for(var j=2;j<com.length-1;j+=2){
  					var path = com[j].split('/');
  					var temp="";
  					
  					for(var k=0;k<path.length;k++){
  						//var tid = id;
  						
  						var flag = true;
  						//if(k==path.length-1){
  						//	temp += path[k];
  						//}else
  							temp += path[k]+'/';
  						for(var t=0;t<paths.length;t++){
  							//alert("temp: "+temp+"   path:"+paths[t]);
  							if(temp == paths[t]){
  								flag = false;
  							}
  						}
  						if(flag){
  							//alert(temp);
  							var pid = id-1;
  							var index = temp.lastIndexOf('/');
  							var subStr = temp.substring(0, index);
  							index = subStr.lastIndexOf('/');
  							subStr = subStr.substring(0, index+1);
  							//alert(subStr);
  							if(subStr==''){
  								pid = tId;
  							}
  							for(var t=0;t<paths.length;t++){
  								//alert("temp: "+temp.substring(0,index)+" path:"+paths[t]);
  								if(paths[t]==subStr){
  									
  									pid = pathId[t];
  									//alert(pid);
  								}
  							}
  							paths.push(temp);
  							pathId.push(id);
  							//alert("id: "+id+"  path: "+path[k]);
  							obj.add(id,pid,path[k]);
  							id++;
  						}
  					}
  				}
  			}
  		}
	
	}
	
	function createDependenceTree(url,obj){
		var retStr = ajaxSend(url,false);
		//alert(retStr);
		if(retStr){
			var id = 0;
			var com = retStr.split(',');
			obj.add(id,-1,"");
  			var tId = id;
  			id++;
  			var paths = new Array();
  			var pathId = new Array();
  			for(var j=0;j<com.length-1;j++){
  				var path = com[j].split('/');
  				var temp="";
  					
  				for(var k=0;k<path.length;k++){
  						//var tid = id;
  						
  					var flag = true;
  						//if(k==path.length-1){
  						//	temp += path[k];
  						//}else
  					temp += path[k]+'/';
  					for(var t=0;t<paths.length;t++){
  							//alert("temp: "+temp+"   path:"+paths[t]);
  						if(temp == paths[t]){
  							flag = false;
  						}
  					}
  					if(flag){
  							//alert(temp);
  						var pid = id-1;
  						var index = temp.lastIndexOf('/');
  						var subStr = temp.substring(0, index);
  						index = subStr.lastIndexOf('/');
  						subStr = subStr.substring(0, index+1);
  						//alert(subStr);
  						if(subStr==''){
  							pid = tId;
  						}
  						for(var t=0;t<paths.length;t++){
  							//alert("temp: "+temp.substring(0,index)+" path:"+paths[t]);
  							if(paths[t]==subStr){
  									
  								pid = pathId[t];
  								//alert(pid);
  							}
  						}
  						paths.push(temp);
  							pathId.push(id);
  						//alert("id: "+id+"  path: "+path[k]);
  						obj.add(id,pid,path[k]);
  						id++;
  					}
  				}
  			}
		}
	}
	
	function inithere(){
		//alert("sss");
		init(0);
  		d.add(0,-1,"");
  		dd.add(0,-1,"");
  		var url = "ProductVersionServlet?flag=getLibrary";
  		
  		createTree(url,d);
  		
  		url = "ProductVersionServlet?flag=getDependenceFile";
  		
  		createDependenceTree(url,dd);
  		d.show();
  		dd.show();
	}
	
	</script>
  </head>
  
  <body BGCOLOR="#FAF0E6"  onload="inithere()">
  <script language="javascript"> 
  	//alert("ss");
  	//var pNav = parent.navigator.innerText;
  	//parent.navigator.innerText=pNav;
  	//parent.navigation.innerHTML='<a href="PDMServlet?pdm=BuildManagement">build management</a>>><a href="repositoryPage.jsp" target="contentFrame"">repository</a>';
  	var nav = new Navigation("navigation",true);
  	//alert("sss");
  	nav.add('product category','PDMServlet?pdm=ProductCategory');
  	nav.add('product','ProductServlet?flag=navigation','contentFrame');
  	nav.add('version','ProductVersionServlet?flag=navigation&state=internal','contentFrame');
  	nav.show();
  	
  	<%String isFlag = (String)session.getAttribute("isProduct");
  		if(isFlag.equals("yes")){
  	 %>
	parent.leftFrame.showTree();
	<%}%>
	parent.leftFrame.selectId(<%=Integer.parseInt(versionId) %>);
  </script>
    <table border="1" bgcolor="#CDCDC1" width="100%" align="center" CELLPADDING="0" CELLSPACING="0">
	<tbody>
	
	<tr>
		<td height="700px" colspan=3 width="100%" valign="top" bgcolor="#c0c0c0">
		<center>
				<div STYLE="position:relative; left:0; top:0; width:100%; border:none thin gray">
					<table STYLE="width:100%"  CELLPADDING="0" CELLSPACING="0" bgcolor="c0c0c0" border="0">
						<tr>
						
							
							
							<td ID="t1" CLASS="selTab" HEIGHT="25" width="180" onclick="changeTabs(event)">Components</td>
															
							<td ID="t2" CLASS="tab" width="180" onclick="changeTabs(event)">Dependences</td>
							
							<td ID="t3" CLASS="tab" width="180" onclick="changeTabs(event)">Package Management</td>
							
							<td ID="t4" CLASS="tab" width="150" onclick="changeTabs(event)">Release Management</td>
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
					
					 		
							<div style="width:48%;height:280px;overflow:auto;float:left;border-style:outset;" >
							<input type="submit" name="add" value="Add" height="30px" onclick="addComponentDialog()" />
					 		<table id="idData" border=1 align="center">
    							<tr bgcolor=Orange>
    								<th width="150px" >Component</th>
    								
    								<th width="50px" height="30px">Version</th>
    								
    								<th width="30" >remove</th>
    							</tr>
    					<%
    						
      						for(int i=0;i<versionList.size();i++)
      						{
      							ComponentCategory category = categoryList.get(i);
      							Component com = comList.get(i);
      							ComponentVersion cVersion = versionList.get(i);
      							
      					%>
    							<tr>
    								<td width="150px"><a href="javascript: selectComponent(<%=cVersion.getId() %>)"><%=com.getName() %></a></td>   	
	    							
	    							<td width="50px"><%=cVersion.getVersion() %></td>
	    							
	    							<td width="50">
	    							<a href="javascript: removeComponent(<%=cVersion.getId() %>)">remove</a>
	    							</td>
       					<% } %>
       							</tr>
      						</table>
      						
      						<p>&nbsp;&nbsp;</p>
      						<center>
      						<div id="barcon" ></div>
      						</center>
							</div>
							<div style="width:48%;height:280px;float:left;border-style:outset;">
							<p style="font-size:25px;font-family: Georgia, serif;">component file:</p>
								<div id="componentfile" class="dtree" style="overflow:auto;border-style:inset;background-color:#fff;height:85%;widht:100%"></div>
							
							</div>
							<div style="clear:both;height:250px;width:98%;border-style:inset;overflow:auto;position:relative; top:30">
								
									<input type="button" value="add" onclick="openBrowser()">
									<input type="button" value="remove" onclick="removefile()">
									<input type="button" value="package" onclick="packageIss()">
									
									<p>&nbsp;&nbsp;</p>
									<div style="height:190px;width:98%;overflow:auto;">
									<form id="fileUpload" method="post" action="PackageFileServlet"  enctype="multipart/form-data" target="hidden_frame">
									<iframe name='hidden_frame' id="hidden_frame" style='display:none'></iframe>
									<table id="setupTable" width="100%" border=1>
										<tr bgcolor=Orange>
											<th width="7px">&nbsp;</th><th width="250px">ISS file</th><th width="250px">Installer</th>
										</tr>
										<%	LibraryList libList = (LibraryList)session.getAttribute("issFileList");
											LibraryList setupList = (LibraryList)session.getAttribute("setupFileList");
											for(int i=0;i<libList.size();i++){
												Library lib = libList.get(i);
												
												Library setup = setupList.get(i);
												//String location = setup.getName();
												String setupName = setup.getName();
												int index = setupName.lastIndexOf("/");
												if(index>-1){
													setupName = setupName.substring(index+1);
												//	location = location.substring(0,index);
												}
												//}else {
												//	location = ".";
												//}
										 %>
										 <tr id="setupId<%=lib.getId() %>">
										 	<td width="7px"><input type="checkbox" name="checkbox" /><input type="text" value="<%=lib.getId() %>" name="text" style='display:none'/></td>
										 	<td width="250px"><a href="LibraryServlet?flag=download&libId=<%=lib.getId() %>"><%=lib.getName() %></a></td>
										 	
										 	<td width="250px"><a href="LibraryServlet?flag=download&libId=<%=setup.getId() %>"><%=setupName %></a></td>
										 	
										 </tr>
										 <%} %>
									</table>
									</form>
									</div>
							</div>
							</div>
							<div CLASS="cont" ID="t2Contents" STYLE="position:relative; left:10" >
								<p>&nbsp;</p>
								<input type="button" value="Add" onclick="addDependence()">
								<table id="dependenceTable" border=1  align="center" width="600" style="table-layout:fixed">
									<tr bgcolor=orange><th width="400">Product</th><th width="130">Version</th><th width="70px">remove</th></tr>
									<%
										int depId = 0;
										for(int i=0;i<pDepList.size();i++){
											ProductDependence pDep = pDepList.get(i);		
											if(pDep.getDependenceId()!=depId){
											depId = pDep.getDependenceId();
									 %>
									 <tr id="<%=depId %>">
									 	<td width="400"><%=pDep.getDependenceName() %></td>
									 	<td width="130"><%=pDep.getDependenceVersion() %></td>
									 	<td width="70px"><a href="javascript: removeDependence(<%=depId %>)">remove</a></td>
									 </tr>
									 <%}} %>
								</table>
							
							</div>
							
							<div CLASS="cont" ID="t3Contents" STYLE="position:relative; left:10" >
							
							<!--  
								<div  style="float:left;height:350px;width:46%;border-style:outset;">
									
								</div>
								
								<div  style="position:relative; left:10;float:left;height:350px;width:48%;border-style:outset">
									<p style="font-size:25px;font-family: Georgia, serif;">dependence file:</p>
									<div id="dependencefile" class="dtree" style="border-style:inset;background-color:#fff;height:89%;widht:100%;overflow:auto;"></div>
								</div >
								
							-->	
							<p>&nbsp;</p>
							<div id="tableDiv" style="border-style:inset;overflow:auto;height:320px;width:700">
							
							<div style="position:relative; left:40;height:320px;width:600px">
							 <table id="fileTable" border=1  align="center" width="600" style="table-layout:fixed">
							 	<tr style="display:none"><td width="250px">s</td><td width="210px">s</td><td width="70px">s</td><td width="70px">s</td></tr>
							 	 <%int proId = Integer.parseInt(versionId);
							 	  Product pro = (Product)session.getAttribute("product"); %>
							 	 <tr id="<%=versionId %>" bgcolor=orange>
							 	 	<td width="530px" colspan="3"><div style="width:530px;"><a href="javascript: selectDependence(<%=versionId %>)"><%=pro.getName() %> <%=version %></a></div></td>
									<td width="70px"><a href="javascript: collapse(<%=versionId %>)">collapse</a></td>
									
							 	 </tr>
							 	 <%							 	  
							 	  	for(int i=0;i<setupList.size();i++){												
										Library setup = setupList.get(i);
							 	  %>
							 	  <tr id="<%=proId %>" style="display:none">
									<td width="250px"><div style="width:250px;"><input type="text" value="<%=setup.getName() %>" readonly size=35 style="background-color:#c0c0c0;color:#000;"></div></td>
									<td width="350px" colspan="3"><div style="width:350px;"><input type="text" name="<%=setup.getId() %>" value="<%=setup.getName() %>"  size=52 onchange="changeLocation(this)"/></div></td>
								</tr>
							 	 <% }
								 	depId = 0;
									for(int i=0;i<pDepList.size();i++){
										ProductDependence pDep = pDepList.get(i);		
										if(pDep.getDependenceId()!=depId){
										depId = pDep.getDependenceId();
											
							 	%>
								<tr id="<%=depId %>" bgcolor=orange>
									<td width="530px" colspan="3"><div style="width:530px;"><a href="javascript: selectDependence(<%=depId %>)"><%=pDep.getDependenceName() %> <%=pDep.getDependenceVersion() %></a></div></td>
									<td width="70px"><a href="javascript: collapse(<%=depId %>)">collapse</a></td>
									
								</tr>
								
								<%}%>
								<tr id="<%=depId %>" style="display:none">
									<td width="250px"><div style="width:250px;"><input type="text" value="<%=pDep.getFileName() %>" readonly size=35 style="background-color:#c0c0c0;color:#000;"></div></td>
									<td width="350px" colspan="3"><div style="width:350px;"><input type="text" name="<%=pDep.getFileId() %>" value="<%=pDep.getRelativePath() %>"  size=52 onchange="changeDependenceLocation(this)"/></div></td>
								</tr>
								<%} %>
							</table>
							</div>
						</div>
								
								<p>&nbsp;&nbsp;</p>
								ISO Name: <input type=text id="rootDirectory" value=".">
								<a href="javascript: downloadISO()" style="position:relative; left:150;">Download ISO</a>
								<div style="height:250px;width:95%;border-style:outset;align:center">
									<div id="dependencefile" class="dtree" style="border-style:inset;background-color:#fff;height:100%;widht:100%;overflow:auto;"></div>
								</div>
								</div>
							
							<div CLASS="cont" ID="t4Contents" STYLE="position:relative; left:15;" >

							
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
