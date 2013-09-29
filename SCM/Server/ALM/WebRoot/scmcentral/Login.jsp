<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>scm server login page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="scm server login page">
	
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	
	<script language="javascript">
		function initial()
		{
			<%
			 String FirstUse = (String)request.getSession().getAttribute("FirstUse");
			 String lastUserName = new String("");
			 String lastUserPassword = new String("");
			 if(FirstUse.equals("no")){
			 	lastUserName = (String)request.getAttribute("lastUserName");
				lastUserPassword = (String)request.getAttribute("lastUserPassword");
			 }
			%>
			
			fLogin.username.value = "<%=lastUserName%>";
			fLogin.password.value = "<%=lastUserPassword%>";
		}
	
		function change()
		{
			document.getElementById("code").src="RandCodeServlet?sc="+new Date().getTime();        
		};
	
		function CheckEmpty()
		{
			if (fLogin.username.value==""){
				alert("please input username!");fLogin.UserName.focus();
				return;
			}
			if(fLogin.password.value==""){
				alert("please input password!");fLogin.PWD.focus();
				return;
			}
			if(fLogin.randcode.value==""){
				alert("please input idetifying code!");
				fLogin.IdentifyCode.focus();
				return;
			}
			fLogin.submit();
		};
	</script>
  </head>
  
  <body onload="initial()">
    <form method="post" action="LoginServlet" name="fLogin">
      <table width=100% height=100% border="0" bgColor="#6175d3">
        <tr height=20%>
        </tr>
        <tr>
          <td width=50%>
          </td>
          <td>
            <table height="300" style="border-bottom:1px solid #000;border-left:1px solid #000;border-right:1px solid #000;border-top:1px solid #000" bgColor="#c0c0c0" align="left" width="350">
              <tr>
                <td width="95"></td>
                <td valign="bottom" height="60">
                  <%
					String Error = (String)request.getAttribute("Error");
					if(Error != null && !Error.isEmpty()){
						out.println("<font color = 'red'>" + Error + "</font>");
					}
					else{
						out.println("please input username and password");
					}
			      %>
			    </td>
              </tr>
              
              <tr>
                <td align="right">
                  <span class="STYLE15" style="font-size:18px">username:</span>
                </td>
                <td>
                  <input name="username" type="text" style="width=220;height=30;font-size:20px"/>
                </td>
              </tr>
              
              <tr>
                <td align="right">
                  <span class="STYLE15" style="font-size:18px">password:</span>
                </td>
                <td>
                  <input name="password" type="password" style="width=220;height=30;font-size:20px"/>
                </td>
              </tr>
              
              <tr>
                <td align="right">
                  <span class="STYLE15" style="font-size:18px">identifing:&nbsp;</span>
                </td>
                <td>
                  <input name="randcode" type="text" class="input2" size="7" style="height=30;font-size:20px"/>
                  &nbsp;<img src="RandCodeServlet" id="code"/>
				  &nbsp;<a href="" onclick="change();" style="font-size:18px">next</a>
                </td>
              </tr>
              
              <tr>
                <td>
                </td>
                <td align="right" height="60" valign="top">
                  <input name="bLogin" type="button" style="width:80px;height:30px" value="Login" onClick="CheckEmpty()"/>
                  &nbsp;&nbsp;<input name="bReset" type="reset" style="width:80px;height:30px" value="Reset"/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                </td>
              </tr>
            </table>
          </td>
        </tr>
	  </table>
    </form>
  </body>
</html>
