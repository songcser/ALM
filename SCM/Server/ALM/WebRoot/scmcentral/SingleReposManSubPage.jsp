<%@include file="common.inc"%>

<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>single repository manage sub page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="single repository manage sub page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	<link rel="stylesheet" media="all" type="text/css" href="css/tab.css" />
	<script src="js/tab.js" type="text/javascript"></script>
	
	<script type="text/javascript">
		function deleteAuthz(){
			var name = fSubPage.name;
			var message = "please make sure delete folow items:\r\n";
			var flag = 0;
			
			if(name == null){
				alert("have no items");
				return;
			}
			
			if(name != null && name.length == null){
				if(name.checked){
					message += name.value + "\r\n";
					flag = 1;
				}
			}
			
			for(var i = 0; i < name.length; i++){
				if(name[i].checked){
					message += name[i].value + "\r\n";
					flag = 1;
				}
  			}
  			
  			if(0 == flag){
				alert("nothing had been selected");
				return;
			}
  			
  			flag = window.confirm(message);
			if(flag){
				document.getElementById("action").value = "deleteAuthz";
				fSubPage.submit();
				return;
			}
			else{
				return;
			}
		}
		
		function modifyAuthz()
		{
			<%
			 List<String> userAuthzs = (List<String>)request.getAttribute("userAuthzs");
			 List<String> groupAuthzs = (List<String>)request.getAttribute("groupAuthzs");
			 String tsection = (String)request.getAttribute("section");
			 if(userAuthzs == null){
			 	userAuthzs = new ArrayList<String>();
			 }
			 if(groupAuthzs == null){
			 	groupAuthzs = new ArrayList<String>();
			 }
			%>
			
			<%if(userAuthzs.size()+groupAuthzs.size() <= 0){%>
				alert("nothing need to modify");
				return;
			<%}%>
			
			window.showModalDialog("modifyAuthz.jsp?section=<%=tsection%>", window, "dialogWidth=400px;dialogHeight=400px;status=no");
		}
	</script>
  </head>
  
  <body>
    <div id="gallery">
		<div class="on" title="Constable"><span>Log message</span></div>
		<div class="off" title="Vincent"><span>Status message</span></div>
		<div class="off" title="Monet"><span>Permission message</span></div>
	</div>
	
	<div id="Constable" class="show" style="width:90%;height=90%;overflow:scroll;">
		<table>
			<c:forEach var="log" items="${requestScope.logMessage}">	
			    <tr style="font-size:14;">
			      <td bgcolor="#FFFFFF">
			      <span><c:out value="${log}"/></span>
			      </td>
			    </tr>
			</c:forEach>
		</table>
	</div>
	
	<div id="Vincent" class="hide" style="width:90%;height:90%;overflow:scroll;">
		<table>
			<c:forEach var="status" items="${requestScope.statusMessage}">	
			    <tr style="font-size:14;">
			      <td bgcolor="#FFFFFF">
			      <span><c:out value="${status}"/></span>
			      </td>
			    </tr>
			</c:forEach>
		</table>
	</div>
	
	<div id="Monet" class="hide" style="width:90%;height=90%;">
		<iframe name="dframe" style="display:none"></iframe>
		<p>permission of current path: <c:out value="${requestScope.currentPath}"/></p>
		<form name="fSubPage" action="SingleReposManServlet" target="dframe" method="post">
		<input type="hidden" name="section" id="section" value="<c:out value="${requestScope.section}"/>"/>
		<input type="hidden" name="action" id="action" value="empty"/>
		<input type="button" name="delete" value="delete" onClick="deleteAuthz()"/>
		<input type="button" name="modify" value="modify" onClick="modifyAuthz()"/>
		<table border="1">
			<tr>
				<td width="150" align="center">
					<span>Name</span>
				</td>
				<td width="150" align="center">
					<span>role</span>
				</td>
				<td width="150" align="center">
					<span>permission</span>
				</td>
			</tr>
			<c:forEach var="user" items="${requestScope.userAuthzs}">	
			    <tr style="font-size:14;">
			      <td bgcolor="#FFFFFF">
			      	<input type="checkbox" name="name" value="<c:out value="${user.name}"/>"/><c:out value="${user.name}"/>
			      </td>
			      <td>
			      	<span>user</span>
			      </td>
			      <td>
			      	<c:choose>
			      		<c:when test="${user.permission == 1}"><c:out value="write"/></c:when>
			      		<c:when test="${user.permission == 0}"><c:out value="read"/></c:when>
					</c:choose>
			      </td>
			    </tr>
			</c:forEach>
			<c:forEach var="group" items="${requestScope.groupAuthzs}">	
			    <tr style="font-size:14;">
			      <td bgcolor="#FFFFFF">
			      	<input type="checkbox" name="name" value="<c:out value="${group.name}"/>"/><c:out value="${group.name}"/>
			      </td>
			      <td>
			      	<span>group</span>
			      </td>
			      <td>
			      	<c:choose>
			      		<c:when test="${group.permission == 1}"><c:out value="write"/></c:when>
			      		<c:when test="${group.permission == 0}"><c:out value="read"/></c:when>
					</c:choose>
			      </td>
			    </tr>
			</c:forEach>
		</table>
		</form>
	</div>
  </body>
</html>
