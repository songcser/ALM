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
	<script type="text/javascript">
//	d = new dTree('d',"leftContent",false,"product");
	<% 
		ProductCategory proCate = (ProductCategory)session.getAttribute("productCategory");
		Product pro = (Product)session.getAttribute("product");
		ProductVersionList versionList = (ProductVersionList)session.getAttribute("productVersionList");
	%>
	
	function modifyProductDialog(){
		var retValue=window.showModalDialog("modifyProductPage.jsp",window,"dialogHeight:200px,dialogWidth:400px, status:0, edge:sunken");
	
		if(retValue){
			var name = retValue[0];
			var des = retValue[1];
			//alert(name);
			//if(name){
				var url = "ProductServlet?flag=isModify&name="+name;
				var retStr = ajaxSend(url,false);
				//alert(retStr);
				if(retStr=="true"){
					var oldName = '<%=pro.getName() %>';
				
					if(name!=oldName){
						if(name){
							parent.leftFrame.changeName(oldName,name);
						}
						location.href="ProductServlet?flag=modify&name="+name+"&description="+des;
						
					}else{
						alert("the product is exist");
					}
				}
		//	}
		}
	}
	
	function createVersionDialog(){
		var retValue=window.showModalDialog("createProductVersionPage.jsp",window,"dialogHeight:200px,dialogWidth:400px, status:0, edge:sunken");
		
		
		if(retValue)
		{
			
			var version=retValue[0];
			var des=retValue[1];
			
			var productName = "<%=pro.getName() %>";
			var productId = "<%=pro.getId() %>";
			var url="ProductVersionServlet?flag=create&version="+version+"&description="+des+"&productId="+productId+"&productName="+productName;
			
			var retStr = ajaxSend(url,false);
			//alert(retStr);
			
			var text=retStr.split('|');
				//alert(text);
			if(text.length==5){
				var array = new Array(3);
				var width = new Array(3);
				
				var id = text[0];
				var version = text[1];
				var description = text[2];
				var created = text[3];
				var pid = text[4];
					//alert(id);
				var url = "<a href=\"ProductVersionServlet?flag=select&versionId="+id+"&version="+version+"\">"+version+"</a>";
				array[0] = url;
				width[0] = "150px";
				array[1] = description;
				width[1] = "250px";
				array[2] = created;
				width[2] = "250px";
				addRow(array,width);
					//alert(pid);
				if(pid>0){
					//alert(pid);
					parent.leftFrame.treeAdd(id,pid,version,"ProductVersionServlet?flag=select&versionId="+id+"&version="+version,'','contentFrame');
				}
				
				//var td = document.getElementById("lastVersion");
			
				//url = "ProductVersionServlet?flag=getLastVersion";
				//alert(url);
				//var ret = ajaxSend(url,false);
				//td.innerHTML = ret;
			}
			
			
		}
	}
	function deleteVersionDialog(){
		//alert("sss");
		var retValue=window.showModalDialog("deleteProductVersionPage.jsp",window,"dialogHeight:100px,dialogWidth:150px,status:0, edge:sunken");
		//alert(retValue[0]);
		if(retValue){
			var versionId = retValue[0];
			var name = retValue[1];
			var productId = "<%=pro.getId() %>";
			var url = "ProductVersionServlet?flag=delete&versionId="+versionId;

			var retStr = ajaxSend(url,false);
			//alert(retStr);
			removeRow(name);
			
			parent.leftFrame.treeDel(versionId,retStr);
			
			
		}
	}
	</script>
  </head>
  
  <body BGCOLOR="#FAF0E6"  onload="init(0)">
  <script language="javascript"> 
  	//var pNav = parent.navigator.innerText;
  	//parent.navigator.innerText=pNav;
  	//parent.navigation.innerHTML='<a href="PDMServlet?pdm=BuildManagement">build management</a>>><a href="repositoryPage.jsp" target="contentFrame"">repository</a>';
  	nav = new Navigation("navigation",true);
  	nav.add('product category','PDMServlet?pdm=ProductCategory');
  	nav.add('product','ProductServlet?flag=navigation','contentFrame');
  	nav.show();
  
  	//alert("sss");
  	<%String isTree = (String)session.getAttribute("isTree");
  		if(isTree.equals("1")){
  		
  	 %>
  	//alert(<%=isTree %>);
  	parent.leftFrame.showTree();
  	<%}%>
  </script>
    <table border="1" bgcolor="#CDCDC1" width="100%" align="center" CELLPADDING="0" CELLSPACING="0">
	<tbody>
	
	<tr>
		<td height="700px" colspan=3 width="100%" valign="top" bgcolor="c0c0c0">
		<center>
				<div STYLE="position:relative; left:0; top:0; width:100%; border:none thin gray">
					<table STYLE="width:100%"  CELLPADDING="0" CELLSPACING="0" bgcolor="c0c0c0" border="0">
						<tr>
						
							<%//if(tabName == "t1"){
							 %>
							
							<td ID="t1" CLASS="selTab" HEIGHT="25" width="180" onclick="changeTabs(event)">Properties</td>
							<td ID="t2" CLASS="tab" width="180" onclick="changeTabs(event)">Version Management</td>
							<%//}else{ %>
							<!-- 
							<td ID="t1" CLASS="tab" HEIGHT="25" width="150">Properties</td>
							<td ID="t2" CLASS="selTab" width="150">View Artifacts</td>
							<%//} %>  -->
							<td width="180">&nbsp;</td>
							<td width="180">&nbsp;</td>
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
							<td valign="top" HEIGHT="*" COLSPAN="4" ID="tabContents" STYLE="border-left:solid thin white;border-bottom:solid thin white;border-right:solid thin white"> 
								<div CLASS="cont" ID="t1Contents" STYLE="position:relative; left:10" >
					<p>&nbsp;</p>
					<p>&nbsp;</p>
					<h3><%=pro.getName() %> Properties</h3>
					<!--  
					<input type="submit" name="modify" value="Modify" height="30px"
    					onclick="javascript:window.open('modifyRepositoryPage.jsp','ModifyRepository','width=400,height=200 alwaysRaised=yes')" />
    				-->
    				<input type="submit" name="modify" value="Modify" height="30px" onclick="modifyProductDialog()" />
    				<p>&nbsp;</p>
    				<p>&nbsp;</p>
    				<table border="1" align="left" width="700px" >
    					<tr>
    						<td width="200px">Name:</td>
    						<td><%=pro.getName() %></td>
    					</tr>
    					<tr>
    						<td>Description:</td>
    						<td><%=pro.getDescription() %></td>
    					</tr>
    					<tr>
    						<td>Created:</td>
    						<td><%=pro.getCreated() %></td>
    					</tr>
    					<tr>
    						<td>Modified:</td>
    						<td><%=pro.getModified() %></td>
    					</tr>
    					<tr>
    						<td >State:</td>
    						<% if(0==pro.getState()){ %>
    						<td id="lastVersion">internal</td>
    						<%}else if(1==pro.getState()){ %>
    						<td id="lastVersion">external</td>
    						<%} %>
    					</tr>
    				</table>
				</div>
				<div CLASS="cont" ID="t2Contents" >
					
					 <p>&nbsp;</p>
					 <p>&nbsp;</p>
					 <input type="submit" name="create" value="Create Version" height="30px" onclick="createVersionDialog()" />
					 <input type="submit" name="delete" value="Delete Version" height="30px" onclick="deleteVersionDialog()" />
					 <table id="idData" border=1 width="700px" align="center">
    					<tr bgcolor=Orange>
    						<th width="150px">Name</th><th width="250px">Description</th><th width="250px">Created</th>
    					</tr>
    					<%
      						for(int i=0;i<versionList.size();i++)
      						{
      							ProductVersion version = versionList.get(i);
      					%>
    					<tr>
    						<td width="150px"><a href="ProductVersionServlet?flag=select&versionId=<%= version.getId() %>&version=<%=version.getVersion() %>"><%=version.getVersion() %></a></td>   	
	    					<td width="250px"><%=version.getDescription() %></td>
	    					<td width="250px"><%=version.getCreated() %></td>
	    					
       					</tr>
       					<% } %>
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
