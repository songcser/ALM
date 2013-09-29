<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'importLibraryPage.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<script type="text/javascript" src="js/pager.js"></script>
	<script type="text/javascript">
	function inithere(){
		//window.parent.test();
		//var test = window.opener.test();
		//alert(test);
		var obj = document.getElementById("repositoryList");
		
		var url = "ComponentVersionServlet?flag=getRepository";
		var retStr = ajaxSend(url,false);
		
		if(retStr){
			var name=retStr.split('|');
			
			for(var i=0;i<name.length;i++){
				obj.options.add(new Option(name[i],name[i]));
			}
			obj.options[0].selected = "selected";
			
			var table = document.getElementById("artifact");
			
			url = "ComponentVersionServlet?flag=getArtifact&repName="+name[0];
			
			retStr = ajaxSend(url,false);
			
			if(retStr){
				var id = 0;
				var artifact = retStr.split('|');
				//alert(artifact[0]);
				for(var i=0;i<artifact.length-1;i++){
					var build = artifact[i].split(',');
					//alert(build.length);
					if(build.length>2){
						var newTr = table.insertRow(-1);
						//alert(build);
						var newTd0 = newTr.insertCell(0);
       					var newTd1 = newTr.insertCell(1);
        				var newTd2 = newTr.insertCell(2);
						
						newTd0.innerHTML = "<input type=\"checkbox\"  name=\"check\">";
						//alert(newTd0.innerHTML);
						newTd0.setAttribute("width","20");
       					newTd1.innerHTML= build[0];
       					newTd1.setAttribute("width","200");
       					var form = "<select id=\"buildList"+id+"\" style=\"width:100px\" >";
						for(var j=1;j<build.length-1;j++){
							var str = build[j].split('&');
							if(str.length==2){
								//alert(str[1]);
								form += "<option id="+str[0]+" value="+str[1]+">"+str[1]+"</option>";
							}
						}
						form += "</select>"
						newTd2.innerHTML= form;
						newTd2.setAttribute("width","100");
						id++;
					}
					
				}
				
			}
		}
	}
	
	function selectRepository(){
	
		var obj = document.getElementById("repositoryList");
		var name = obj.options[obj.selectedIndex].value;
		var table = document.getElementById("artifact");
		
		var length = table.rows.length;
		for(var i=0;i<length;i++){
			table.deleteRow(i);
			length=length-1;
         	i=i-1;
		}
		url = "ComponentVersionServlet?flag=getArtifact&repName="+name;
		//alert(url);
		retStr = ajaxSend(url,false);
		//alert(retStr);
		if(retStr&&retStr!=""){
			var id = 0;
			var artifact = retStr.split('|');
			//alert(artifact);
			for(var i=0;i<artifact.length-1;i++){
				var build = artifact[i].split(',');
					//alert(build.length);
				if(build.length>2){
					var newTr = table.insertRow(-1);
						//alert(build);
					var newTd0 = newTr.insertCell(0);
       				var newTd1 = newTr.insertCell(1);
        			var newTd2 = newTr.insertCell(2);
						
					newTd0.innerHTML = "<input type=\"checkbox\"  name=\"check\">";
					//alert(newTd0);
					newTd0.setAttribute("width","20");
       				newTd1.innerHTML= build[0];
       				newTd1.setAttribute("width","200");
       				var form = "<select id=\"buildList"+id+"\" style=\"width:100px\" >";
					for(var j=1;j<build.length-1;j++){
						var str = build[j].split('&');
						if(str.length==2){
							//alert(str[1]);
							form += "<option id="+str[0]+" value="+str[1]+">"+str[1]+"</option>";
						}
						
					}
					form += "</select>"
					newTd2.innerHTML= form;
					newTd2.setAttribute("width","100");
					id++;
				}
					
			}
				
		}
	}
	
	function importFile(){
		var checkObj = document.getElementsByName("check");  
		
		var value = new Array();
		var j=0;
		for(var i=0;i<checkObj.length;i++){
			if(checkObj[i].checked){
				var build = document.getElementById("buildList"+i);
				var number = build.options[build.selectedIndex].value;
				value[j] = build.options[build.selectedIndex].id;
				j++;
			}
		}
		
		window.returnValue = value;
		window.close();
	}
	</script>
  </head>
  
  <body onload="inithere()" BGCOLOR="#CDCDC1" >
  <p>&nbsp;</p>

  	<center>
    <div style="width:90%">
    	Repository : <select id="repositoryList" style="width:250px" onchange="selectRepository()">
    	</select>
    </div>
    <p>&nbsp;</p>
    <p>Artifacts</p>
    <table>
    <tr><td>
     <input type="submit" value="upload" style="width:60px;align:right" onclick="importFile()" >
     </td>
     </tr>
    <tr>
    <td>
   
    <div style="height:300px;overflow:auto;" >
    	<table id="artifact" border=1 width="400px"> 
    		<tr bgcolor=Orange>
    			<td width="10"> </td>
    			<td width="100">Name</td>
    			<td width="200">Build Times</td>
    		</tr>
    	</table>
    </div>
    </td>
    </tr>
    </table>
    </center>
  </body>
</html>
