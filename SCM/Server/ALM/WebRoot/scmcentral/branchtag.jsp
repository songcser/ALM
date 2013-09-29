<%@include file="common.inc"%>

<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>branch or tag page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="branch or tag page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	<base target="cframe"/>
	-->
	
	<script type="text/javascript">
		function branchtag()
		{
			if(fBranchtag.destpath.value == null || fBranchtag.sourcepath.value == null){
				alert("source path or dest path is null");
				return;
			}
			if(fBranchtag.destpath.value == "" || fBranchtag.sourcepath.value == ""){
				alert("source path or dest path is null");
				return;
			}
			if(fBranchtag.logmessage.value == null || fBranchtag.logmessage.value == ""){
				alert("log message is null");
				return ;
			}
			
			fBranchtag.submit();
			window.close();
		}
		
		function CancelBranchtag()
		{
			window.close();
		}
		
		function initial()
		{
			<%
			 List<String> btFullPaths = new ArrayList<String>();
			 String sel = (String)request.getSession().getAttribute("sel");
			 
			 String realPath = request.getSession().getServletContext().getRealPath("\\config");
			 ReposMan reposMan = new ReposMan();
			 reposMan.readStructTree(realPath);
			 List<String> noteList = reposMan.getNoteList();
			 List<String> noteIdList = reposMan.getNoteIdList();
			 
			 String SingleReposName = (String)request.getSession().getAttribute("SingleReposName");
			 String[] noteIds = sel.split(";");
			 String fullPath = "";
			 
			 if(!noteIds[0].equals("0")){
			 	int level = noteIds[0].length();
			 	if(level >= 2){
			 		int currentIndex = noteIdList.indexOf(noteIds[0]);
			 		int fathIndex = noteIdList.indexOf(noteIds[0].substring(0, level-1));
			 		if(noteList.get(fathIndex).equals("branches")){
			 			btFullPaths.add(SingleReposName + "/branches/" + noteList.get(currentIndex));
			 			btFullPaths.add(SingleReposName + "/tags/" + noteList.get(currentIndex));
			 		}
			 		if(noteList.get(fathIndex).equals("trunk")){
			 			btFullPaths.add(SingleReposName + "/trunk/" + noteList.get(currentIndex));
			 			btFullPaths.add(SingleReposName + "/branches/1.0/" + noteList.get(currentIndex));
			 		}
			 	}
			 	else if(level >= 1){
			 		int currentIndex = noteIdList.indexOf(noteIds[0]);
			 		if(noteList.get(currentIndex).equals("trunk")){
			 			btFullPaths.add(SingleReposName + "/trunk");
			 			btFullPaths.add(SingleReposName + "/branches/1.0");
			 		}
			 	}
			 	
			 }
		
			 request.setAttribute("btFullPaths", btFullPaths);
			%>
			
			<%if(btFullPaths.size() >= 2){%>
				document.getElementById("sourcepath").value = "<%=btFullPaths.get(0)%>";
				document.getElementById("destpath").value = "<%=btFullPaths.get(1)%>";
			<%}%>
		}
	</script>
  </head>
  
  <body onload="initial()">
  	<br>
 	<iframe name="bframe" style="display:none"></iframe>
  	<form method="post" action="SingleReposManServlet" target="bframe" name="fBranchtag">
  		<input type="hidden" name="action" value="branchtag"/>
  	  <div style="left:25px;height:60;width:350;border-width:1px;border-color:#000;position:absolute;">
  	  	<table>
  	  		<tr style="height:30;">
  	  			<td>
  	  				<span>*source path:&nbsp;</span><input name="sourcepath" id="sourcepath" value="" type="text" style="width:200"/>
  	  			</td>
  	  		</tr>
  	  		<tr style="height:30;">
  	  			<td>
  	  				<span>*dest path:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><input name="destpath" id="destpath" value="" type="text" style="width:200"/>
  	  			</td>
  	  		</tr>
  	  	</table>
  	  </div>
  	  <div style="left:25px;top:90;height:60;width:350;position:absolute;">
  	  	<font color="red">&nbsp;*please input log message</font>
  	  </div>
  	  <div style="left:25;top:120;width:350;height:150;position:absolute;">
  	  	<textarea name="logmessage" cols="41" rows="7"></textarea>
  	  </div>
  	  <div style="left:25;top:240;width:350;position:absolute;">
  	  	<table align="center" width="350">
		  <tr height="40">
		  	<td align="right" valign="bottom">
		  		<input name="ok" value="ok" type="button" style="width:65;"onClick="branchtag()"/>
		  		<input name="cancel" value="cancel" type="button" onClick="CancelBranchtag()"/>
		  	</td>
		  </tr>
		 </table>
  	  </div>
	</form>
  </body>
</html>
