<%@include file="common.inc"%>

<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>delete page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="delete page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	<base target="cframe"/>
	-->
	
	<script type="text/javascript">
		function CancelDeletes()
		{
			window.close();
		}
		
		function initial()
		{
			<%
			 List<String> delFullPaths = new ArrayList<String>();
			 String sel = (String)request.getSession().getAttribute("sel");
			 
			 String realPath = request.getSession().getServletContext().getRealPath("\\config");
			 ReposMan reposMan = new ReposMan();
			 reposMan.readStructTree(realPath);
			 List<String> noteList = reposMan.getNoteList();
			 List<String> noteIdList = reposMan.getNoteIdList();
			 
			 String SingleReposName = (String)request.getSession().getAttribute("SingleReposName");
			 String[] noteIds = sel.split(";");
			 String fullPath = "";
			 
			 int tInit = 0;
			 
			 for(int i = 0; i < noteIds.length; i++){
			 	if(noteIds[i].equals("0")){
			 		continue;
			 	}
			 	
			 	int level = noteIds[i].length();
			 	int sCount = 0;
			 	int rCount = 0;
			 	int tIndex = 0;
			 	int k = 0;
			 	for(k = i+1; k < noteIds.length; k++){
			 		int tLevel = noteIds[k].length();
			 		if(tLevel <= level){
			 			break;
			 		}
			 		if(tLevel > level){
			 			if(!noteIds[i].equals(noteIds[k].substring(0, level))){
			 				break;
			 			}
			 		}
			 		sCount++;
			 	}
			 	tIndex = k-1;
			 	
			 	int j = 0;
			 	fullPath = SingleReposName;
			 	for(k = tInit; k < noteIdList.size(); k++){
			 		if(noteIdList.get(k).length() <= level){
			 			if(noteIdList.get(k).equals(noteIds[i].substring(0, noteIdList.get(k).length()))){
			 				fullPath += "/" + noteList.get(k);
			 				if(noteIds[i].equals(noteIdList.get(k))){
					 			for(j = k+1; j < noteIdList.size(); j++){
					 				int tLevel = noteIdList.get(j).length();
					 				if(tLevel <= level){
					 					break;
					 				}
					 				rCount++;
					 			}
					 			break;
					 		}
			 			}
			 		}
			 	}
			 	
			 	if(sCount == rCount){
			 		delFullPaths.add(fullPath);
			 		i = tIndex;
			 	}
			 }
			 
			 request.setAttribute("delFullPaths", delFullPaths);
			%>
		}
		
		function deletes()
		{
			<%
			 int ttFlag = 0;
			 List<String> ttsel = (List<String>)request.getAttribute("delFullPaths");
			 if(ttsel != null){
				 for(int i = 0; i < ttsel.size(); i++){
				 	String[] ttpBuffer = ttsel.get(i).split("/");
				 	if(ttpBuffer.length <= 2){
				 		ttFlag = 1;
				 	}
				 }
			 }
			%>
			
			<%if(ttFlag == 1){%>
				alert("can't delete basic structure");
				window.close();
				return;
			<%}%>
			
			if(fDelete.logmessage.value == null || fDelete.logmessage.value == ""){
				alert("log message is null");
				return ;
			}
			
			fDelete.submit();
			window.close();
		}
	</script>
  </head>
  
  <body onload="initial()">
  	<br>
 	<iframe name="dframe" style="display:none"></iframe>
  	<form method="post" action="SingleReposManServlet" target="dframe" name="fDelete">
  		<input type="hidden" name="action" value="delete"/>
  	  <div style="left:25px;width:350;top:10;position:absolute;">
  	  	<font color="red">&nbsp;*you will delete follow paths</font>
  	  </div>
  	  <div style="left:25px;overflow:scroll;top:30;height:90;width:350;border-left:#000 solid 1px;border-right:#000 solid 1px;border-top:#000 solid 1px;border-bottom:#000 solid 1px;position:absolute;">
  	  	<table>
  	  		<c:forEach var="delPath" items="${requestScope.delFullPaths}">	
			    <tr style="font-size:14;">
			      <td bgcolor="#FFFFFF">
			      <input name="path" value=<c:out value="${delPath}"/> type="checkbox" checked readonly/>
			      </td>
			      <td>
			      <span><c:out value="${delPath}"/></span>
			      </td>
			    </tr>
			</c:forEach>
  	  	</table>
  	  </div>
  	  <div style="left:25px;top:130;width:350;position:absolute;">
  	  	<font color="red">&nbsp;*please input log message</font>
  	  </div>
  	  <div style="left:25;top:155;width:350;height:150;border-left:#000 solid 1px;border-right:#000 solid 1px;border-top:#000 solid 1px;border-bottom:#000 solid 1px;position:absolute;">
  	  	<textarea name="logmessage" cols="41" rows="10"></textarea>
  	  </div>
  	  <div style="left:25;top:330;width:350;position:absolute;">
  	  	<table align="center" width="350">
		  <tr height="40">
		  	<td align="right" valign="bottom">
		  		<input name="delete" value="delete" type="button" onClick="deletes()"/>
		  		<input name="cancel" value="cancel" type="button" onClick="CancelDeletes()"/>
		  	</td>
		  </tr>
		 </table>
  	  </div>
	</form>
  </body>
</html>
