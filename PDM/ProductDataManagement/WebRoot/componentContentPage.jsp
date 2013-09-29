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
	
	<% 
		ComponentCategory comCate = (ComponentCategory)session.getAttribute("componentCategory");
		ComponentList comList = (ComponentList)session.getAttribute("componentList");
		
	%>
	function modifyDialog(){
		
		
		var retValue=window.showModalDialog("modifyComponentCategoryPage.jsp",window,"dialogHeight:200px,dialogWidth:400px, status:0, edge:sunken");
		
		var oldName = "<%=comCate.getName() %>";
		
		if(retValue)
		{
			var name=retValue[0];
			var des=retValue[1];
			//if(name){
				var url = "ComponentCategoryServlet?flag=isModify&name="+name;
				var retStr = ajaxSend(url,false);
				if(retStr=="yes"){
					if(name){
						var obj = window.parent.leftFrame.document.getElementById("categoryList");
						for(var i=0;i<obj.options.length;i++){
							if(obj.options[i].value == oldName){
								obj.options[i].text = name;
								obj.options[i].value = name;
								break;
							}
						}
					}
					
					location.href="ComponentCategoryServlet?flag=modify&name="+name+"&description="+des;
				}
			//}
		}
	}
	
	function createDialog(){
		var retValue=window.showModalDialog("createComponentPage.jsp",window,"dialogHeight:200px,dialogWidth:400px, status:0, edge:sunken");
		
		
		if(retValue)
		{
			
			var name=retValue[0];
			var des=retValue[1];

			var categoryName = "<%=comCate.getName() %>";
			//var categoryId = "<%=comCate.getId() %>";
			var url="ComponentServlet?flag=create&name="+name+"&description="+des+"&categoryName="+categoryName;
			//alert(url);
			var retStr = ajaxSend(url,false);
			//alert(retStr);
			var text=retStr.split('|');
			//alert(text);
			if(text.length==5){
				var array = new Array();
				var width = new Array();
				var id = text[0];
				var name = text[1];
				var description = text[2];
				var created = text[3];
				var lastVersion = text[4];
					//alert(id);
				
				var url = "<a href=\"ComponentServlet?flag=select&componentId="+id+"&componentName="+name+"\">"+name+"</a>";
				array[0] = url;
				width[0] = "150px";
				array[1] = description;
				width[1] = "250px";
				array[2] = created;
				width[2] = "250px";
				
				addRow(array,width);
			}
			
			var td = document.getElementById("count");
			var count = parseInt(td.innerHTML)+1;
			td.innerHTML = count;
		}
	}
	function deleteDialog(){
		//alert("sss");
		var retValue=window.showModalDialog("deleteComponentPage.jsp",window,"dialogHeight:100px,dialogWidth:150px,status:0, edge:sunken");
		//alert(retValue);
		if(retValue){
			var name = retValue;
			var categoryName = "<%=comCate.getName() %>";
			var url = "ComponentServlet?flag=delete&categoryName="+categoryName+"&componentName="+name;
			ajaxSend(url,true);
			//alert(retStr);
			removeRow(name);
		}
	}
	</script>
  </head>
  
  <body BGCOLOR="#FAF0E6"  onload="init(0)">
  <script language="javascript"> 

  	nav = new Navigation("navigation",true);
  	nav.add('component category','PDMServlet?pdm=ComponentCategory');
  	nav.show();
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
							<td ID="t2" CLASS="tab" width="180" onclick="changeTabs(event)">View Components</td>
							<%//}else{ %>
							<!-- 
							<td ID="t1" CLASS="tab" HEIGHT="25" width="150">Properties</td>
							<td ID="t2" CLASS="selTab" width="150">View Artifacts</td>
							<%//} %>  -->
							<td width="150px">&nbsp;</td>
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
							<td valign="top" HEIGHT="*" COLSPAN="4" ID="tabContents" STYLE="border-left:solid thin white;border-bottom:solid thin white;border-right:solid thin white"> 
							<div CLASS="cont" ID="t1Contents" STYLE="position:relative; left:10" >
							<p>&nbsp;</p>
							<p>&nbsp;</p>
					<h3><%=comCate.getName() %> Properties</h3>
					<!--  
					<input type="submit" name="modify" value="Modify" height="30px"
    					onclick="javascript:window.open('modifyRepositoryPage.jsp','ModifyRepository','width=400,height=200 alwaysRaised=yes')" />
    				-->
    				<input type="submit" name="modify" value="Modify" height="30px" onclick="modifyDialog()" />
    				<p>&nbsp;</p>
    				<p>&nbsp;</p>
    				<table border="1" align="center" width="700px" >
    					<tr>
    						<td width="200px">Name:</td>
    						<td><%=comCate.getName() %></td>
    					</tr>
    					<tr>
    						<td>Description:</td>
    						<td><%=comCate.getDescription() %></td>
    					</tr>
    					<tr>
    						<td>Created:</td>
    						<td><%=comCate.getCreated() %></td>
    					</tr>
    					<tr>
    						<td>Modified:</td>
    						<td><%=comCate.getModified() %></td>
    					</tr>
    					<tr>
    						<td>Number of Product</td>
    						<td id="count"><%=comCate.getComponentCount() %></td>
    					</tr>
    				</table>
				</div>
				<div CLASS="cont" ID="t2Contents" STYLE="position:relative; left:10">
					
					 <p>&nbsp;</p>
					 <p>&nbsp;</p>
					 <input type="submit" name="create" value="Create" height="30px" onclick="createDialog()" />
					 <input type="submit" name="delete" value="Delete" height="30px" onclick="deleteDialog()" />
					 <table id="idData" border=1 width="700px" align="left">
    					<tr bgcolor=Orange>
    						<th width="150px">Name</th><th width="250px">Description</th><th width="250px">Started</th>
    					</tr>
    					<%
      						for(int i=0;i<comList.size();i++)
      						{
      							Component com = comList.get(i);
      					%>
    					<tr>
    						<td width="150px"><a href="ComponentServlet?flag=select&componentId=<%= com.getId() %>&componentName=<%=com.getName() %>"><%=com.getName()%></a></td>   	
	    					<td width="250px"><%=com.getDescription() %></td>
	    					<td width="250px"><%=com.getCreated() %></td>
	    					
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
