<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%@ page import="com.prolambda.scmserv.bll.*" %>
<%@ page import="com.prolambda.scmserv.entity.*" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>Change owner page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="Change owner page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	<base target="cframe"/>
	-->
	
	<script type="text/javascript">
		<% 
	   	 String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
	   	 UserMan userMan = new UserMan();
		 List<ScmUser> companyUsers = userMan.getUsersFromCompany(configRealPath);
		 List<String> companyUserNames = new ArrayList<String>(); 

		 for(int i = 0; i < companyUsers.size(); i++){
			String name = companyUsers.get(i).getName();
			companyUserNames.add(name.split("@")[0]);
		 }
	     List<String> Names = companyUserNames;
	     if(Names == null){
	     	Names = new ArrayList<String>();
	     }
	     int len = Names.size();
	    %>
	   
	    function initial()
	    {
	      fChangeOwner.s1.length = <%=len%>;
	      var k = 0;
	      <%for(int i = 0; i < len; i++){%>
	         fChangeOwner.s1.options[k].value = "<%=Names.get(i)%>";
	         fChangeOwner.s1.options[k].text = "<%=Names.get(i)%>";
	         k++;
	      <%}%>
	      
	      var name = window.dialogArguments.document.getElementsByName("reposname");
		  if(name == null){
			return;
		  }
			
		  if(name != null && name.length == null){
			if(name.checked){
				document.getElementById("reposname").value = name.value;
			}
			return;
		  }
		  
		  for(var i = 0; i < name.length; i++)
		  {
			if(name[i].checked){
				document.getElementById("reposname").value = name[i].value;
				break;
			}
  		  }
	    }
	    
		function ChangeOwner()
		{
			if(fChangeOwner.reposname.value == ""){
				alert("repository name is null");
				return;
			}
			
			fChangeOwner.submit();
			//window.close();
		}
		
		function CancelChange()
		{
			window.close();
		}
	</script>
  </head>
  
  <body onload="initial()">
 	<iframe name="cframe" style="display:none"></iframe>
  	<form method="post" action="ReposManServlet" target="cframe" name="fChangeOwner">
  		<input type="hidden" name="action" value="changeowner"/>
	  <table align="center">
	  	<tr height="70">
	  		<td valign="bottom">
	  			<span style="font=18;"><font color="black">name:</font>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
	  			<input name="reposname" id="reposname" value="" type="text" style="width=240;height=25;font-size=18" readonly/>
	  		</td>
	  	</tr>
	  	<tr height="70">
	  		<td valign="bottom">
	  			<span style="font=18;"><font color="red">*owner:</font>&nbsp;&nbsp;&nbsp;</span>
	  			<select id="s1" name="s1" size=1 style="width:144;"></select>
	  		</td>
	  	</tr>
	  	<tr height="70">
	  		<td align="right" valign="bottom">
	  			<input name="changeowner" value="ChangeOwner" type="button" onClick="ChangeOwner()"/>
	  			<input name="cancel" value="Cancel" type="button" onClick="CancelChange()"/>
	  		</td>
	  	</tr>
	  </table>
	</form>
  </body>
</html>
