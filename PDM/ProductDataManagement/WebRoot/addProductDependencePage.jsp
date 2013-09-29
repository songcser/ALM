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
	<%
		String versionId = (String)session.getAttribute("productVersionId");
	%>
	
	function init(){
		var obj = document.getElementById("categoryList");
		
		var url = "ProductVersionServlet?flag=getProductCategory";
		var retStr = ajaxSend(url,false);
		//alert(retStr);
		if(retStr){
			var name=retStr.split('|');
			
			for(var i=0;i<name.length;i++){
				obj.options.add(new Option(name[i],name[i]));
			}
			
			var table = document.getElementById("products");
			
			url = "ProductVersionServlet?flag=getProducts&categoryName="+name[0];
			
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
       					var form = "<select id=\"versionList"+id+"\" style=\"width:100px\" >";
						for(var j=1;j<build.length-1;j++){
							var str = build[j].split('&');
							if(str.length==2){
								var vId = "<%=Integer.parseInt(versionId) %>";
								if(str[0]==vId)
									continue;
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
	
	function selectCategory(){
	
		var obj = document.getElementById("categoryList");
		var name = obj.options[obj.selectedIndex].value;
		var table = document.getElementById("products");
		
		var length = table.rows.length;
		for(var i=0;i<length;i++){
			table.deleteRow(i);
			length=length-1;
         	i=i-1;
		}
		
		//alert(table.rows.length);
		var url = "ProductVersionServlet?flag=getProducts&categoryName="+name;
		//alert(url);
		var retStr = ajaxSend(url,false);
		//alert(retStr);
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
					//alert(newTd0);
					newTd0.setAttribute("width","20");
       				newTd1.innerHTML= build[0];
       				newTd1.setAttribute("width","200");
       				var form = "<select id=\"versionList"+id+"\" style=\"width:100px\" >";
					for(var j=1;j<build.length-1;j++){
						var str = build[j].split('&');
						if(str.length==2){
							var vId = "<%=Integer.parseInt(versionId) %>";
								if(str[0]==vId)
									continue;
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
	
	function addDependence(){
		var checkObj = document.getElementsByName("check");  
		
		var value = new Array(checkObj.length);
		for(var i=0;i<checkObj.length;i++){
			if(checkObj[i].checked){
				var build = document.getElementById("versionList"+i);
				var number = build.options[build.selectedIndex].value;
				value[i] = build.options[build.selectedIndex].id;
			}
		}
		
		window.returnValue = value;
		window.close();
	}
	</script>
  </head>
  
  <body onload="init(0)" BGCOLOR="#CDCDC1" >
  <p>&nbsp;</p>

  	<center>
    <div style="width:90%">
    	Product Category : <select id="categoryList" style="width:250px" onchange="selectCategory()">
    	</select>
    </div>
    <p>&nbsp;</p>
    <p>Products</p>
    <table>
    <tr><td>
     <input type="submit" value="Add" style="width:60px;align:right" onclick="addDependence()" >
     </td>
     </tr>
    <tr>
    <td>
   
    <div style="height:300px;overflow:auto;" >
    	<table id="products" border=1 width="400px"> 
    		<tr bgcolor=Orange>
    			<td width="10"> </td>
    			<td width="100">Name</td>
    			<td width="200">Version</td>
    		</tr>
    	</table>
    </div>
    </td>
    </tr>
    </table>
    </center>
  </body>
</html>
