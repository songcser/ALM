<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'productLeftPage.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	
	<link rel="stylesheet" type="text/css" href="css/styles.css">
	
	<script type="text/javascript" src="js/pager.js"></script>
	<script type="text/javascript" src="js/dTree.js"></script>
	<script type="text/javascript">
	var d = new dTree('d',"leftContent2","product");
	
	<% 
  		ProductCategoryList proCateList = (ProductCategoryList)session.getAttribute("productCategoryList");
  		ProductCategory category = (ProductCategory)session.getAttribute("productCategory");
	%>
	function deleteDialog(){
	
		var retValue=window.showModalDialog("deleteProductCategoryPage.jsp",window,"dialogHeight:100px,dialogWidth:250px,status:0, edge:sunken");
		
		if(retValue){
			var name = retValue;
			//alert(name);
			var obj = document.getElementById("categoryList");
			for(var i=0;i<obj.options.length;i++){
				if(obj.options[i].value == name){
					name = name.replace("*"," ");
					var url = "ProductCategoryServlet?flag=delete&name="+name;
					ajaxSend(url,true);
					
					if(i==obj.selectedIndex){
						//alert(i);
						if(i==obj.options.length-1&&i>0){
							var categoryName = obj.options[i-1].value;
							obj.options[i-1].selected = "selected";
							window.parent.contentFrame.location.href="ProductCategoryServlet?flag=select&categoryName="+categoryName;
						}else {
							var categoryName = obj.options[i+1].value;
							obj.options[i+1].selected="selected";
							window.parent.contentFrame.location.href="ProductCategoryServlet?flag=select&categoryName="+categoryName;
						}
					}
					obj.options.remove(i);
					break;
				}
			}
		}
	}
	
	
	
	function createDialog(){
		
		var retValue=window.showModalDialog("createProductCategoryPage.jsp",window,"dialogHeight:200px,dialogWidth:400px, status:0, edge:sunken");
		
		
		if(retValue)
		{
			
			var name=retValue[0];
			var des=retValue[1];
			
			var urlt = "ProductCategoryServlet?flag=isCreate&name="+name;
			var retStr = ajaxSend(urlt,false);
			//alert(retStr);
			if(retStr == "yes"){
				var url="ProductCategoryServlet?flag=create&name="+name+"&description="+des;
				//alert(url);
				parent.contentFrame.location.href=url;
				var obj = document.getElementById("categoryList");
				var index = obj.selectedIndex;
				//alert(index);
				obj.options.add(new Option(name,name));
				///alert(index);
				if(index>=0){
					obj.options[index].selected=false;
					obj.options[obj.options.length-1].selected="selected";
				}else
					obj.options[0].selected="selected";
				
			}
		}
	}
	
	function selectCategory(){
		var obj = document.getElementById("categoryList");
		var categoryName = obj.options[obj.selectedIndex].value;
		//alert(categoryName);
		window.parent.contentFrame.location.href="ProductCategoryServlet?flag=select&categoryName="+categoryName;
		
	}
	
	function showTree(){
		
  		//d.add(0,-1,'<%=category.getName() %>');
  		
  		var url = "ProductServlet?flag=getTree";
  		//alert(url);
  		var pid = -1;
  		var retStr = ajaxSend(url,false);
		//alert(retStr);
		var text=retStr.split('|');
		//alert(text);
		d.add(0,-1,text[0]);
		for(var i=1;i<text.length;i++){
			var text2 = text[i].split(',');
			//alert(text[i]);
			if(text2.length==3){
				if(i==text.length-1){
					if(text2[0]>0)
						pid = text2[0];
				}else{
					var array = new Array();
					var id = text2[0];
					var productId = text2[1];
					var name = text2[2];
					//alert(id);
					var str = "ProductServlet?flag=select&productId="+productId+"&productName="+name;
					var node = new Node(id,0,name,str,'','contentFrame');	
					node._hc = true;
					d.aNodesData[d.aNodesData.length] = node;	
				}
			}
		}
  		d.show();
  		//alert(pid);
  		if(!d.aNodesData[pid]._io){
  			
  			d.o(pid);
  			d.s(pid);
  		}
  		
  		var content1 = document.getElementById("leftContent1");
		var content2 = document.getElementById("leftContent2");
	
		content1.style.display="none";
		content2.style.display="block";
	}
  	
  	function treeAdd(id,pid,name,url,title,target){
  	
		var tId = parseInt(id)+500;
		var tPid = parseInt(pid);
		
		d.add(tId, tPid, name, url, title, target);
		d.show();
	
		if(!d.aNodesData[tPid]._io){
			d.o(tPid);
			d.s(tPid);
		}
	}

	
	function treeDel(id,pid){
		
		var tPid = parseInt(pid);
		var tId = parseInt(id)+500;
		d.del(tId);
		
		d.show();
	
		if(!d.aNodesData[tPid]._io){
			//alert(pid);
			d.o(tPid);
			d.s(tPid);
		}
	}
	
	function selectId(id){
		var tId = parseInt(id)+500;
		///alert(tId);
		d.s(tId);
	}
	
	function changeName(oldName,name){
		d.changeName(oldName,name);
	}
  	
	</script>
  </head>
  
  <body BGCOLOR="#CDCDC1">
  <div class="dtree" id="leftContent1">
  	<p>&nbsp;</p>
    <h4>Product Category</h4>
    <input type="submit" name="create" value="Create" height="30px" onclick="createDialog()" />
    <input type="submit" name="delete" value="Delete" height="30px" onclick="deleteDialog()" />
    <p>&nbsp;</p>
    <table width="220px" height="500px" border="2" bgcolor="#fff" align="center">
    	<tr>
    		<td valign="top">
    		
    		<select id="categoryList" multiple size="30" style="width:220px" onchange="selectCategory()">
    		<%for(int i=0;i<proCateList.size();i++){
    		ProductCategory proCate = proCateList.get(i);
    		String name = proCate.getName().replace(' ', '*');
    		if(i==0){
    		%>
    		<option value=<%=name %> selected="selected"><%=proCate.getName() %></option>	
    		<%}else{ %>
    		<option value=<%=name %>><%=proCate.getName() %></option>
    		
    		 <%}} %>
    		 </select>
    		</td>
    	</tr>
    </table>
  </div>
  <div class="dtree" id="leftContent2" style="display:none">
 
  </div>
  </body>
</html>
