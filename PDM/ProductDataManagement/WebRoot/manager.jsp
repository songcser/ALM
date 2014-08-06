<%@ page language="java" import="java.util.*,com.prolambda.controller.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
//System.out.println("BasePath:"+basePath);
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>Product Data Management</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">

	<link rel="stylesheet" type="text/css" href="css/styles.css">

	<script type="text/javascript" src="js/dTree.js"></script>
	<script type="text/javascript">
		
	function inithere(){
	d = new dTree('d',"leftContent","noChildren");
		var cateid =0;
		var comid =0;
		var verid =0;
		var id = 0;
		
	<% 
		String flag = request.getParameter("flag");
		if(flag.equals("component")){
		ComponentCategoryService  comCateSer = new ComponentCategoryService();
  		ComponentService comSer = new ComponentService();
  		ComponentVersionService verSer = new ComponentVersionService();
  		LibraryService libSer = new LibraryService();
  		ComponentCategoryList comCateList = comCateSer.getAll();
  		
  	%>
		<%for(int i=0;i<comCateList.size();i++){
  			ComponentCategory comCate = comCateList.get(i);
  			String cateName = comCate.getName();
  			%>
  			
  				cateid = id;
  				d.add(cateid, -1, '<%=cateName %>');
  				id++;
  			
  			<%
  			
  			ComponentList comList = comSer.getAll(comCate.getId());
  			for(int j=0;j<comList.size();j++){
  				Component com = comList.get(j);
  				String comName = com.getName();
  				%>
  				
  				comid = id;
  				d.add(comid, cateid, '<%=comName %>');
  				id++;
  			
  				<%
  				ComponentVersionList verList = verSer.getVersions(com.getId());
  				for(int t=0;t<verList.size();t++){
  					ComponentVersion ver = verList.get(t);
  					%>
  					
  					verid = id;
  					var url = "ComponentVersionServlet?flag=showLibrary&versionId="+<%=ver.getId() %>;
  					d.add(verid, comid, '<%=ver.getVersion() %>',url,'','contentFrame');
  					
  					id++;
  					<% 
  					
  				}
  			}
  		} 
  		}else if(flag.equals("product")){
  		ProductCategoryService  proCateSer = new ProductCategoryService();
  		ProductService proSer = new ProductService();
  		ProductVersionService verSer = new ProductVersionService();
  		LibraryService libSer = new LibraryService();
  		ProductCategoryList proCateList = proCateSer.getAll();
  		
  	%>
		<%for(int i=0;i<proCateList.size();i++){
  			ProductCategory proCate = proCateList.get(i);
  			String cateName = proCate.getName();
  			%>
  			
  				cateid = id;
  				d.add(cateid, -1, '<%=cateName %>');
  				id++;
  			
  			<%
  			
  			ProductList proList = proSer.getAll(proCate.getId());
  			for(int j=0;j<proList.size();j++){
  				Product pro = proList.get(j);
  				String proName = pro.getName();
  				%>
  				
  				comid = id;
  				d.add(comid, cateid, '<%=proName %>');
  				id++;
  			
  				<%
  				ProductVersionList verList = verSer.getVersions(pro.getId());
  				for(int t=0;t<verList.size();t++){
  					ProductVersion ver = verList.get(t);
  					%>
  					
  					verid = id;
  					var url = "ProductVersionServlet?flag=showLibrary&versionId="+<%=ver.getId() %>;
  					d.add(verid, comid, '<%=ver.getVersion() %>',url,'','contentFrame');
  					
  					id++;
  					<% 
  					
  				}
  			}
  		} 
  		}
  		%>
  		d.show();
	}
	</script>
  </head>
  
  <body onload="inithere()">
  	<div  class="dtree" id="leftContent" style="float:left;width:20%;height:95%;overflow:auto;border-style:outset">
  	 	
  	</div>
  	
    <div style="position:relative; left:10;float:left;width:78%;height:95%;overflow:auto;border-style:outset">
    	<iframe id="contentFrame" name="contentFrame" frameborder="0" marginheight="0" marginwidth="0" scrolling="no" style="width:100%; height:100%; overflow:no"></iframe>
    </div>
  </body>
</html>
