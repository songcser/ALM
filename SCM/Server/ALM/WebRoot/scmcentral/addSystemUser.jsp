<%@include file="common.inc"%>
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
		if(companyUsers == null){
			companyUsers = new ArrayList<ScmUser>();
		}
		
		List<String> companyUserNames = new ArrayList<String>();
		for(int i= 0; i < companyUsers.size(); i++){
			String[] tpBuffer = companyUsers.get(i).getName().split("@");
			if(tpBuffer.length >= 2){
				companyUserNames.add(tpBuffer[0]);
			}
		}
		
		List<String> Names = companyUserNames;
	    int len = Names.size();
	   %>
	   
	   function initial()
	   {
	      fAddSysUser.s1.length = <%=len%>;
	      var k = 0;
	      <%for(int i = 0; i < len; i++){%>
	         fAddSysUser.s1.options[k].value = k+1;
	         fAddSysUser.s1.options[k].text = "<%=Names.get(i)%>";
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
	      for(var i = 0; i < s1.length; i++){
	         s2.options[s2.length-s1.length+i].value = s1.options[i].value;
	         s2.options[s2.length-s1.length+i].text = s1.options[i].text;
	      }
	
	      s1.length = 0;
	   }
	</script>
	

  <head>
    <base href="<%=basePath%>">
    
    <title>add system user page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="add system user page">
	
	<script type="text/javascript" language="javascript">
		function addSystemUsers()
		{
  			var members = "";
  			for(var i = 0; i < fAddSysUser.s2.length; i++){
  				members += fAddSysUser.s2.options[i].text;
  				if(i < fAddSysUser.s2.length-1){
  					members += "::=";
  				}
  			}
  			if(members == ""){
  				alert("nothing had beed selected");
  				return;
  			}
  			fAddSysUser.selected.value = members;
			fAddSysUser.submit();
			window.close();
		}
		
		function CancelAdd(){
			window.close();
		}
	</script>
  </head>
  
  <body onload="initial()">
  	<br/>
    <iframe name="aframe" style="display:none"></iframe>
  	<form method="post" action="SysManServlet" target="aframe" name="fAddSysUser">
  		<input type="hidden" name="action" value="addSystemUsers"/>
  		<input type="hidden" name="selected" value=""/>
  		<div style="margin-left:25px;top:10px;postion:absolute;">
	  		<div>
	  			<span style="font=16;"><font color="red">*please select users from left to right</font></span>
	  		</div>
	  		<br>
	  		<div>
	  		 <table>
		         <tr>
		            <td>
		               <select id="s1" name="s1" size=13 style="width:150">
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
		               <select id="s2" name="s2" size=13 style="width:150">
		               </select>
		            </td>
		         </tr>
		      </table>
	  		</div>
			<div>
				<table align="center" width="350">
		  			<tr style="height:40">
		  				<td align="right" valign="bottom">
		  					<input name="add" value="add" type="button" style="width:70;" onClick="addSystemUsers()"/>
		  					<input name="Cancel" value="Cancel" type="button" style="width:70;" onClick="CancelAdd()"/>
		  				</td>
		  			</tr>
		  		</table>
		  	</div>
	  </div>
	</form>
  </body>
</html>
