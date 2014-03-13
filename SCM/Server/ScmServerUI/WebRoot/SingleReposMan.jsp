<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>scm server single repository manage page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="scm server single repository manage page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	<script type="text/javascript" src="js/wtree.js"></script>   
	<script type="text/javascript" src="js/jquery.js"></script>   
	<link rel="stylesheet" href="css/dtree.css" type="text/css"></link>  
	<link rel="stylesheet" media="all" type="text/css" href="css/menu.css" />
	<script src="js/menu.js" type="text/javascript"></script>
	
	<script language="javascript" type="text/javascript">
		function deletes()
		{
			//var flag = sel();
			//if(flag == 0){
			//	alert("nothing had been selected");
			//	return;
		//	}
			
			window.showModalDialog("delete.jsp", window, "dialogWidth=400px;dialogHeight=400px;status=no");
		}
		
		function unlocks()
		{
		//	var flag = sel();
		//	if(flag == 0){
		//		alert("nothing had been selected");
		//		return;
		//	}
			window.showModalDialog("unlock.jsp", window, "dialogWidth=400px;dialogHeight=250px;status=no");
		}
		
		function branchtags()
		{
			//var flag = sel();
			//if(flag == 0){
			//	alert("nothing had been selected");
			//	return;
			//}
			window.showModalDialog("branchtag.jsp", window, "dialogWidth=400px;dialogHeight=300px;status=no");
		}
		
		function subprojects()
		{
			window.showModalDialog("subproject.jsp", window, "dialogWidth=400px;dialogHeight=300px;status=no");
		}
		
		function authzs()
		{
			//var flag = sel();
			//if(flag == 0){
			//	alert("nothing had been selected");
			//	return;
			//}
			window.showModalDialog("authz.jsp", window, "dialogWidth=400px;dialogHeight=400px;status=no");
		}
	
		function sel(){
			var selids=d.getCheckedNodes();
			
			var str="";
			for(var n=0; n<selids.length; n++){
				str+=selids[n]+";";
			}
			
			if(str == ""){
				return 0;
			}
			
			document.getElementById("action").value = "temp";
			document.getElementById("selected").value = str;
			fSingleReposMan.submit();
		}
		
		function getCheckedFileId(){
			var selids=d.getCheckedNodes();
			var str = "";
			for(var i=0;i<selids.length;i++){
				if(!d.aNodes[selids[i]]._hc){
					str+=selids[i]+";";
				}
			}
			return str;
		}
		
		function getCheckedNodeId(){
			var selids=d.getCheckedNodes();
			var tempId=[];
			var str="";
			var flag = true;
			for(var n=0; n<selids.length; n++){
				for(var i=0;i<tempId.length;i++){
					if(tempId[i]==d.aNodes[selids[n]].pid){
						flag =false;
					}
				}
				if(flag){
					
					str+=selids[n]+";";
				}
				tempId[tempId.length] = selids[n];
			}
			
			if(str == ""){
				return 0;
			}
			
			return str;
		}
	
		function getNodePathById(id){
			if(id==0||id=="0")
				return "";
			var path = d.aNodes[id].name;
			var pid=d.aNodes[id].pid;
			while(pid!='0'||pid!=0){
				path = d.aNodes[pid].name+"/"+path;
				pid = d.aNodes[pid].pid;
				/*
				for(var i=0;i<d.aNodes.length;i++){
					if(d.aNodes[i].id==pid){
						path = d.aNodes[i].name+"/"+path;	
						pid = d.aNodes[i].pid;
					}
				}*/
			}
			
			return d.aNodes[0].name+"/"+path;
		}
		
		function initial()
		{
			<%
			 String currentUserRole = (String)request.getSession().getAttribute("currentUserRole");
			%>
			<%if(currentUserRole == null || !currentUserRole.equals("administrator")){%>
				document.getElementById("SysManMenu").style.display = "none";
			<%}%>
		}
	</script>
	
	<!-- 
	<link rel="stylesheet" media="all" type="text/css" href="css/tab.css" />
	<script src="js/tab.js" type="text/javascript"></script>
	-->
	
  </head>
  
  <body onload="initial()">
	<div style="width:100%;background:#D3DFD3">
	  <div style="float:left;">
		<ul id="nav">
			<li><a style="height:30px" href="ReposManServlet">Repostory manage</a></li>
			<li><a style="height:30px;cursor:pointer;">System manage \/ </a>
				<ul>
					<li><a href="UserManServlet">User manage</a></li>
					<li><a href="UserGroupManServlet">User group manage</a></li>
					<li id="SysManMenu"><a href="SysManServlet">System setting</a></li>
				</ul>
				<div class="clear"></div>
			</li>
		</ul>
	  </div>
	  <div style="float:right;height:30px;line-height:30px;margin-right:40">
		<span>
			<%
			 String currentUserName = (String)request.getSession().getAttribute("currentUserName");
			 if(currentUserName != null){
			 	out.println("<font size=2 color=black>current user: " + currentUserName + "&nbsp;&nbsp;|&nbsp;&nbsp;</font>");
			 }
			 else{
			 	out.println("<font size=2 color=black>current user: null &nbsp;&nbsp;|&nbsp;&nbsp; </font>");
			 }
			%>
		</span>
		<span>
		<a href="LogoutServlet"><font size=2 color=black>Logout</font></a>
	    </span>
	  </div>
	</div>

  <div style="margin-right:40">
  	<table align="center" width=100%>
		<tr height="30">
		  	<td align="right" valign="bottom">
		  		<span><font size=2 color=black>Current:&nbsp;</font></span>
		  		<span><a href="ReposManServlet"><font size=2 color=black>Repository Manage</font></a></span>
		  		<span>
		  		<%
		  		 String ttreposName = (String)request.getSession().getAttribute("SingleReposName");
		  		 if(ttreposName == null){
		  		 	ttreposName = "null";
		  		 }
		  		 out.println("<font size=2 color=black>&nbsp;>&nbsp;" + ttreposName + "</font>");
		  		%>
		  		</span>
		  	</td>
		</tr>
	</table>
  </div>
	
	<iframe name="sframe" style="display:none"></iframe>
	<form name="fSingleReposMan" action="SingleReposManServlet" target="sframe" method="post">
		<input type="hidden" name="action" id="action" value="temp"/>
		<input type="hidden" name="selected" id="selected" value="empty"/>
		<div style="left:0px;overflow:scroll;height:90%;width:270;position:absolute;">
			<table width="250" align="left">
				<tr style="height:25px;">
					<td valign="middle" align="center" bgColor="#318bce">
						<sapn>Repository Structure</sapn>
					</td>
				</tr>
				<tr>
					<td>
						<input name="delete" value="D" type="button" style="width:40px" onClick="deletes()"/>
						<input name="unlock" value="U" type="button" style="width:40px" onClick="unlocks()"/>
						<input name="branchtag" value="B" type="button" style="width:40px" onClick="branchtags()"/>
						<input name="subproject" value="S" type="button" style="width:40px" onClick="subprojects()"/>
						<input name="authz" value="A" type="button" style="width:40px" onClick="authzs()"/>
						<input name="selected" value="" type="hidden" />
					</td>
				</tr>
				<tr>
					<td>
						<script type="text/javascript">
							d = new dTree('d','img/');
							d.config.folderLinks=true;
							d.config.useCookies=false;
							d.config.check=true;
							
							<%
							 String reposName = (String)request.getSession().getAttribute("SingleReposName");
							 List<String> noteList = (List<String>)request.getAttribute("noteList");
							 List<String> noteIdList = (List<String>)request.getAttribute("noteIdList");
							 List<String> fathIdList = (List<String>)request.getAttribute("fathIdList");
							 List<String> dirFlagList = (List<String>)request.getAttribute("dirFlagList");
							 List<String> pathList = (List<String>)request.getAttribute("pathList");
							%>
							d.add(0,-1,'<%=reposName%>','SingleReposManServlet?tselected=0&taction=getMessage','','c');
							
							<%if(noteList != null && noteList.size() > 0){%>
								
								<%for(int i = 0; i < noteList.size(); i++){%>
									
									<%if(dirFlagList.get(i).equals("1")){%>
										
										d.add(<%=noteIdList.get(i)%>,<%=fathIdList.get(i)%>,'<%=noteList.get(i)%>','SingleReposManServlet?tselected=<%=pathList.get(i)%>&taction=getMessage','','c','img/folder.gif');
									<%}else{%>
										d.add(<%=noteIdList.get(i)%>,<%=fathIdList.get(i)%>,'<%=noteList.get(i)%>','SingleReposManServlet?tselected=<%=pathList.get(i)%>&taction=getMessage','','c');
									<%}%>
								<%}%>
							<%}%>
							document.write(d.toString());
						</script>
					</td>
				</tr>
			</table>
		</div>
		
		<div style="left:275px;width:80%;height:500;position:absolute;">
			<iframe style="width:100%;height:100%;" marginheight=0 marginwidth=0 frameborder="no" border="0" name="c"  src="SingleReposManSubPage.jsp"></iframe>
		</div>
	</form>
  </body>
</html>
