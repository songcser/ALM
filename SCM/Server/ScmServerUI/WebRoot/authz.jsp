<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ page import="com.prolambda.scmserv.entity.*" %>
<%@ page import="com.prolambda.scmserv.bll.*" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>authz page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="authz page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	<base target="cframe"/>
	-->
	
	<script type="text/javascript">
		function authzs()
		{
			var path = document.getElementsByName("path");
			if(path == null || path.length <= 0){
				alert("have no dest path");
				return;
			}
			
			var members = "";
  			for(i = 0; i < fAuthz.s2.length; i++){
  				members += fAuthz.s2.options[i].text;
  				if(i < fAuthz.s2.length-1){
  					members += "::=";
  				}
  			}
  			if(members == ""){
  				alert("have no user or group beed selected");
  				return ;
  			}
  			fAuthz.selected.value = members;
  			
			fAuthz.submit();
			//window.close();
		}
		
		function CancelAuthzs()
		{
			window.close();
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
		
		function initial()
		{
			<%
			/*
			 List<String> authzFullPaths = new ArrayList<String>();
			 String sel = (String)request.getSession().getAttribute("sel");
			 
			 String realPath = request.getSession().getServletContext().getRealPath("\\config");
			 ReposMan reposMan = new ReposMan();
			 reposMan.readStructTree(realPath);
			 List<String> noteList = reposMan.getNoteList();
			 List<String> noteIdList = reposMan.getNoteIdList();
			 
			 String SingleReposName = (String)request.getSession().getAttribute("SingleReposName");
			 String[] noteIds = sel.split(";");
			 String fullPath = "";
			 
		 	 int level = 0;
		 	 if((level = noteIds[0].length()) > 1 && level <=2){
		 		 String fathId = noteIds[0].substring(0, level-1);
		 		 int index = noteIdList.indexOf(fathId);
		 		 if(noteList.get(index).equals("trunk")){
		 			 fullPath = SingleReposName + "/trunk/" + noteList.get(noteIdList.indexOf(noteIds[0]));
		 			 authzFullPaths.add(fullPath);
		 		 }
		 	 }
		 	 else if(level > 2 && level <=3){
		 	 	 String fathId = noteIds[0].substring(0, level-1);
		 		 String grandFathId = noteIds[0].substring(0, level-2);
		 		 int fathIndex = noteIdList.indexOf(fathId);
		 		 int index = noteIdList.indexOf(grandFathId);
		 		 if(noteList.get(index).equals("branches")){
		 			 fullPath = SingleReposName + "/branches/" + noteList.get(fathIndex) + "/" + noteList.get(noteIdList.indexOf

(noteIds[0]));
		 			 authzFullPaths.add(fullPath);
		 		 }
		 	 }
			 
			 request.setAttribute("authzFullPaths", authzFullPaths);*/
			%>
			
			
			<%
			 String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
			 SysMan sysMan = new SysMan();
			 String svnRoot = sysMan.readSvnRoot(configRealPath);
			
			 UserMan userMan = new UserMan();
			 List<ScmUser> companyUsers = userMan.getUsersFromCompany(configRealPath);
			 UserGroupMan userGroupMan = new UserGroupMan();
			 List<UserGroup> userGroups = userGroupMan.getGroupsFromRepos(svnRoot);
			 if(userGroups == null){
			 	userGroups = new ArrayList<UserGroup>();
			 }
			 if(companyUsers == null){
			 	companyUsers = new ArrayList<ScmUser>();
			 }
			
			 List<String> userNames = new ArrayList<String>();
			 List<String> groupNames = new ArrayList<String>();
			 for(int i = 0; i < companyUsers.size(); i++){
				String[] tpBuffer = companyUsers.get(i).getName().split("@");
				if(tpBuffer.length >= 2){
					userNames.add(tpBuffer[0]);
				}
			 }
			
			 for(int i = 0; i < userGroups.size(); i++){
				groupNames.add("@" + userGroups.get(i).getName());
			 }
			%>
			fAuthz.s1.length = <%=(userNames.size()+groupNames.size())%>;
			var k = 0;
			<%for(int i = 0; i < groupNames.size(); i++){%>
			   fAuthz.s1.options[k].value = k+1;
			   fAuthz.s1.options[k].text = "<%=groupNames.get(i)%>";
			   k++;
			<%}%>
			<%for(int i = 0; i < userNames.size(); i++){%>
			   fAuthz.s1.options[k].value = k+1;
			   fAuthz.s1.options[k].text = "<%=userNames.get(i)%>";
			   k++;
			<%}%>
			
			//var pobj = window.parent.dialogArguments;
			//alert(pobj);
			var table = document.getElementById("authzTable");
			var nodeId = window.parent.dialogArguments.getCheckedNodeId();
			//alert(nodeId);
			var ids = nodeId.split(";");
			for(var i=0;i<ids.length;i++){
				var id = ids[i];
				if(id=="")
					continue;
				var path = window.parent.dialogArguments.getNodePathById(id);
				//alert(path);
				var index = path.indexOf("/");
				//alert(index);
				if(index<0){
					alert("can't select this path");
					window.close();
					return;
				}
				var vindex = path.indexOf("/",index+1);
				//alert(vindex);
				var flag;
				if(vindex>0){
					
					flag = path.substring(index+1,vindex);
					//alert(flag);
					if(flag=="trunk"){
						index = path.lastIndexOf("/");
						//alert(index+"---"+vindex);
						if(index!=vindex){
							alert("can't select this path");
							window.close();
							return;
						}
					}else if(flag=="branches"){
						var start = path.indexOf("/",vindex);
						start = path.indexOf("/",start+1);
						
						var end = path.lastIndexOf("/");
						//alert(start+"---"+end);
						if(end>start&&start!=-1){
							alert("can't select this path");
							window.close();
							return;
						}
					}else if(flag=="tags"){
						alert("can't select this path");
						window.close();
						return;
					}
				}else{
					alert("can't select this path");
					window.close();
					return;
				}
				
				var newRow = table.insertRow(-1);
				newRow.style.fontSize="14";
				//var cell0 = document.createElement("td");
				var cell0 = newRow.insertCell(0);
				cell0.setAttribute("bgcolor", "#FFFFFF");
				cell0.innerHTML = '<input name="path" value="'+path+'" type="checkbox" checked readonly/>';
				//var cell1 = document.createElement("td");
				var cell1 = newRow.insertCell(1);
				cell1.innerHTML = "<span>"+path+"</span>";
				//newRow.appendChild(cell0);
				//newRow.appendChild(cell1);
			}
		}
	</script>
  </head>
  
  <body onload="initial()">
  	<br>
 	<iframe name="aframe" style="display:none"></iframe>
  	<form method="post" action="SingleReposManServlet" target="aframe" name="fAuthz">
  		<input type="hidden" name="action" value="authz"/>
  		<input type="hidden" name="selected" value=""/>
  	  <div style="left:25px;top:10;width:350;position:absolute;">
  	  	<font>&nbsp;*authz for follow path</font>
  	  </div>
  	  <div style="left:25px;top:30;height:30;width:350;border-left:#000 solid 1px;border-right:#000 solid 1px;border-top:#000 solid 1px;border-bottom:#000 solid 1px;position:absolute;">
  	  	<table id="authzTable">
  	  		<!-- 
  	  		<c:forEach var="authzPath" items="${requestScope.authzFullPaths}">	
			    <tr style="font-size:14;">
			      <td bgcolor="#FFFFFF">
			      <input name="path" value=<c:out value="${authzPath}"/> type="checkbox" checked readonly/>
			      <span><c:out value="${authzPath}"/></span>
			      </td>
			    </tr>
			</c:forEach>
			 -->
  	  	</table>
  	  </div>
  	  <div style="left:25px;top:70;width:350;position:absolute;">
  	  	<font color="red">&nbsp;*please select user or group from left to right</font>
  	  </div>
  	  <div style="left:25;top:90;width:350;height:220;position:absolute;">
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
  	  <div style="left:25;top:330;width:350;position:absolute;">
  	  	<table align="center" width="350">
  	  	  <tr>
  	  	  	<td>
  	  	  		<select name="authztype" size="1" style="width:150">
  	  	  			<option value="write" selected>write</option>
  	  	  			<option value="read">read</option>
  	  	  		</select>
  	  	  	</td>
  	  	  </tr>
		  <tr height="30">
		  	<td align="right" valign="bottom">
		  		<input name="authz" value="authz" type="button" onClick="authzs()"/>
		  		<input name="cancel" value="cancel" type="button" onClick="CancelAuthzs()"/>
		  	</td>
		  </tr>
		 </table>
  	  </div>
	</form>
  </body>
</html>
