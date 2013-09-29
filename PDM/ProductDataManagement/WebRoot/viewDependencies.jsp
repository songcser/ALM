<%@ page language="java" import="java.util.*,com.prolambda.model.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>Dependence</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

  </head>
  
  <body BGCOLOR="#FAF0E6">
  	<%
  		String libName = (String)session.getAttribute("libName");
  		String number = (String)session.getAttribute("buildNumber");
  		DependenceList depList = (DependenceList)request.getAttribute("dependencelist");
  		String repName = (String)request.getAttribute("repName");
  		String type = (String)request.getAttribute("type");
  		String depName = (String)request.getAttribute("depName");
  	 %>
  	<center>
    <h3>Dependencies of <%=libName %></h3>
   
	<p>&nbsp;</p>
	<p>&nbsp;</p>
	<table id="idData" border=1 width="550px" align="center">
    	<tr bgcolor=Orange>
    		<th width="100px">Name</th><th width="200px">Repository Name</th><th width="50px">Type</th>
    	</tr>
    	<%
      		for(int i=0;i<depList.size();i++)
      		{
      			Dependence dep = new Dependence();
      			dep = depList.get(i);
      	%>
    	<tr>
    		<td width="150px"><a href="DependenceServlet?tabName=t1&flag=download&depId=<%=dep.getId() %>&refId=<%=dep.getReferenceId() %>"><%=depName %></a></td>   	
	    	<td width="200px"><%=repName %></td>
	    	<td width="50px"><%=type %> </td>
       	</tr>
       	<% } %>
    </table>
      				
    <p>&nbsp;&nbsp;</p>

    <%
    //获取pageNow
     	int pageNow=Integer.parseInt((String)request.getAttribute("pageNow"));
      
      	if(pageNow!=1){
          	out.println("<a href=DependenceServlet?flag=fenye&tabName=t2&pageNow="+(pageNow-1)+">Last</a>"); 
        }
          			//获取pageCount
        String s_pageCount=(String)request.getAttribute("pageCount");
        int pageCount=Integer.parseInt(s_pageCount);
          			//显示超练接
        for(int i=1;i<=pageCount;i++){
          	out.println("<a href=DependenceServlet?flag=fenye&tabName=t2&pageNow="+i+">"+i+"</a>");
        }
        if(pageNow<pageCount){
          	out.println("<a href=DependenceServlet?flag=fenye&tabName=t2&pageNow="+(pageNow+1)+">Next</a>"); 
        }
     %>
    </center>
  </body>
</html>
