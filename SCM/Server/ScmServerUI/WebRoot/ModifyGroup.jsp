<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%@ page import="com.prolambda.scmserv.entity.*" %>
<%@ page import="com.prolambda.scmserv.bll.*" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>

	<script  language = "javascript">
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
	      var name = window.dialogArguments.document.getElementsByName("userGroup");
		  for(var i = 0; i < name.length; i++)
		  {
			if(name[i].checked){
				fModifyGroup.groupname.value = name[i].value;
				break;
			}
		  }
	      
	      fModifyGroup.s1.length = <%=len%>;
	      var k = 0;
	      <%for(int i = 0; i < len; i++){%>
	         fModifyGroup.s1.options[k].value = k+1;
	         fModifyGroup.s1.options[k].text = "<%=Names.get(i)%>";
	         k++;
	      <%}%>
	   }

	   function move(s1, s2){
	      index = s1.selectedIndex;
	      if(index == -1){
	         alert("no select");
	         return;
	      }
	      s2.length++;
	      s2.options[s2.length - 1].value = s1.options[index].value;
	      s2.options[s2.length - 1].text = s1.options[index].text;
	      s1.remove(index);
	   }

	   function moveAll(s1, s2){
	      if(s1.length == 0){
	         alert("no need to move");
	         return;
	      }
	
	      s2.length = s2.length + s1.length;
	      for(i = 0; i < s1.length; i++){
	         s2.options[s2.length-s1.length+i].value = s1.options[i].value;
	         s2.options[s2.length-s1.length+i].text = s1.options[i].text;
	      }
	
	      s1.length = 0;
	   }
	</script>
	

  <head>
    <base href="<%=basePath%>">
    
    <title>modify group page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="modify group page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	<script type="text/javascript" language="javascript">
		function ModifyGroup()
		{
			if(fModifyGroup.groupname.value == ""){
				alert("group name is null");
				window.close();
			}
			
  			var members = "";
  			for(i = 0; i < fModifyGroup.s2.length; i++){
  				members += fModifyGroup.s2.options[i].text;
  				if(i < fModifyGroup.s2.length-1){
  					members += "::=";
  				}
  			}
  			
  			fModifyGroup.selected.value = members;
  			
			fModifyGroup.submit();
			window.close();
		}
		
		function CancelModify(){
			window.close();
		}
	</script>
  </head>
  
  <body onload="initial()">
  	<br/>
    <iframe name="nframe" style="display:none"></iframe>
  	<form method="post" action="UserGroupManServlet" target="nframe" name="fModifyGroup">
  		<input type="hidden" name="action" value="modify"/>
  		<input type="hidden" name="selected" value=""/>
  		<div style="margin-left:10px;margin-top:10px">
	  		<div>
	  			<span style="font=18;">*name:&nbsp;&nbsp;&nbsp;&nbsp;</span>
		  		<input name="groupname" value="" type="text" style="width=240;height=25;font-size=18" readonly/>
	  		</div>
	  		<div>
	  			<br/>
	  		</div>
	  		<div>
	  		
	  		 <table>
		         <tr>
		            <td>
		               <select id="s1" name="s1" size=10 style="width:150">
		               </select>
		            </td>
		
		            <td>
		               <input type="button" name="moveToRight" value="---->" onClick="move(s1, s2)">
		               <br>
		               <input type="button" name="moveAllToRight" value="-->>" onClick="moveAll(s1, s2)">
		
		               <br>
		               <input type="button" name="moveToLift" value="<----" onClick="move(s2, s1)">
		               <br>
		               <input type="button" name="moveAllToLift" value="<<--" onClick="moveAll(s2, s1)">
		            </td>
		
		            <td>
		               <select id="s2" name="s2" size=10 style="width:150">
		               </select>
		            </td>
		         </tr>
		      </table>
	  		</div>
	  		
	  		<div>
	  			<br/>
	  		</div>
			<div>
				<table align="center" width="350">
		  			<tr height="30">
		  				<td align="right" valign="bottom">
		  					<input name="Modify" value="Modify" type="button" onClick="ModifyGroup()"/>
		  					<input name="Cancel" value="Cancel" type="button" onClick="CancelModify()"/>
		  				</td>
		  			</tr>
		  		</table>
		  	</div>
	  </div>
	</form>
  </body>
</html>
