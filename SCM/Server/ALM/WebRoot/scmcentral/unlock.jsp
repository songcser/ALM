<%@include file="common.inc"%>

<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>unlock page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="unlock page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	<base target="cframe"/>
	-->
	
	<script type="text/javascript">
		function unlocks()
		{
			var path = document.getElementsByName("path");
			if(path == null || path.length <= 0){
				alert("have no dest path");
				return;
			}
			
			fUnlock.submit();
			window.close();
		}
		
		function CancelUnlocks()
		{
			window.close();
		}
		
		function initial()
		{
			<%
			 List<String> unlockFullPaths = new ArrayList<String>();
			 String sel = (String)request.getSession().getAttribute("sel");
			 
			 String realPath = request.getSession().getServletContext().getRealPath("\\config");
			 ReposMan reposMan = new ReposMan();
			 reposMan.readStructTree(realPath);
			 List<String> noteList = reposMan.getNoteList();
			 List<String> noteIdList = reposMan.getNoteIdList();
			 List<String> noteFlag = reposMan.getDirFlagList();
			 
			 String SingleReposName = (String)request.getSession().getAttribute("SingleReposName");
			 String[] noteIds = sel.split(";");
			 String fullPath = "";
			 
			 for(int i = 0; i < noteIds.length; i++){
			 	if(noteIds[i].equals("0")){
			 		continue;
			 	}
			 	int index = noteIdList.indexOf(noteIds[i]);
			 	if(noteFlag.get(index).equals("0")){
			 		fullPath = SingleReposName;
			 		for(int k = 0; k < noteIdList.size(); k++){
			 			if(noteIdList.get(k).length() <= noteIds[i].length()){
			 				if(noteIdList.get(k).equals(noteIds[i].substring(0, noteIdList.get(k).length()))){
			 					fullPath += "/" + noteList.get(k);
			 				}
			 			}
			 		}
			 		unlockFullPaths.add(fullPath);
			 	}
			 }
			 
			 request.setAttribute("unlockFullPaths", unlockFullPaths);
			%>
		}
	</script>
  </head>
  
  <body onload="initial()">
  	<br>
 	<iframe name="uframe" style="display:none"></iframe>
  	<form method="post" action="SingleReposManServlet" target="uframe" name="fUnlock">
  		<input type="hidden" name="action" value="unlock"/>
  	  <div style="left:25px;top:10;width:350;position:absolute;">
  	  	<font color="red">&nbsp;*you will unlock follow files</font>
  	  </div>
  	  <div style="left:25px;overflow:scroll;top:35;height:165;width:350;border-left:#000 solid 1px;border-right:#000 solid 1px;border-top:#000 solid 1px;border-bottom:#000 solid 1px;position:absolute;">
  	  	<table>
  	  		<c:forEach var="unlockPath" items="${requestScope.unlockFullPaths}">	
			    <tr style="font-size:14;">
			      <td bgcolor="#FFFFFF">
			      <input name="path" value=<c:out value="${unlockPath}"/> type="checkbox" checked readonly/>
			      </td>
			      <td>
			      <span><c:out value="${unlockPath}"/></span>
			      </td>
			    </tr>
			</c:forEach>
  	  	</table>
  	  </div>
  	  <div style="left:25;top:200;width:350;position:absolute;">
  	  	<table align="center" width="350">
		  <tr height="30">
		  	<td align="right" valign="bottom">
		  		<input name="unlock" value="unlock" type="button" onClick="unlocks()"/>
		  		<input name="cancel" value="cancel" type="button" onClick="CancelUnlocks()"/>
		  	</td>
		  </tr>
		 </table>
  	  </div>
	</form>
  </body>
</html>
