package com.prolambda.alm.scmcentral.servlet;

import com.prolambda.alm.scmcentral.entity.*;
import com.prolambda.alm.scmcentral.bll.*;
import java.io.IOException;
import java.util.*;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class LoginServlet extends HttpServlet
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public LoginServlet()
	{
		super();
	}

	public void destroy()
	{
		super.destroy();
	}

	public void init() throws ServletException
	{
		super.init();
	}

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
   		
   		Login login = new Login();
   		ScmUser user = login.getLastLogin(configRealPath);
   		if(user.getName() != null && !user.getName().equals("") && user.getPassword() != null && !user.getPassword().equals("")){
   			request.setAttribute("lastUserName", user.getName());
   			request.setAttribute("lastUserPassword", "");
   			request.getSession().setAttribute("FirstUse", "no");
   		}
   		else{
   			request.getSession().setAttribute("FirstUse", "yes");
   		}
   		
		request.getRequestDispatcher("scmcentral/Login.jsp").forward(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String FirstUse = (String)request.getSession().getAttribute("FirstUse");
		String name = request.getParameter("username");
	   	String password = request.getParameter("password");
	   	String rIdentifyCode = request.getParameter("randcode");
	   	String tIdentifyCode = (String)request.getSession().getAttribute("rand");
	   	
	   	request.setAttribute("lastUserName", name);
		request.setAttribute("lastUserPassword", password);
	   	
	   	String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
   		ScmUser user = new ScmUser(name, password, "", -1);
   		Login login = new Login(user);
   		UserMan userMan = new UserMan();
   		
	   	if(FirstUse.equals("yes")){
	   		List<ScmUser> companyUsers = userMan.getUsersFromCompany(configRealPath);
	   		int retFlag = login.userFirstLogin(companyUsers, configRealPath, 1);
	   		
	   		if(!rIdentifyCode.equals(tIdentifyCode)){
		   		String iError = "*identifycode&nbsp;error";
				request.setAttribute("Error", iError);
				request.getRequestDispatcher("scmcentral/Login.jsp").forward(request, response);
		   	}
	   		else if(0 == retFlag){
	   			request.getSession().setAttribute("currentUserName", user.getName());
	   			request.getSession().setAttribute("currentUserPassword", user.getPassword());
	   			
	   			if(request.getSession().getAttribute("currentUserRole")!=null){
   					request.getSession().removeAttribute("currentUserRole");
   				}
   				request.getSession().setAttribute("currentUserRole", "administrator");
	   			response.sendRedirect("SysManServlet");
	   		}
	   		else{
	   			String Error = "*username&nbspor&nbsp;password&nbsp;error";
				request.setAttribute("Error", Error);
		   		request.getRequestDispatcher("scmcentral/Login.jsp").forward(request, response);
	   		}
	   	}
	   	else{
	   		List<ScmUser> sysUsers = userMan.getUsersFromSystem(configRealPath);
	   		
	   		
	   		int retFlag = login.userLogin(sysUsers, configRealPath, 1);
	   		
	   		if(-1 == retFlag || -3 == retFlag){
	   			String uError = "*username&nbsp;error";
				request.setAttribute("Error", uError);
		   		request.getRequestDispatcher("scmcentral/Login.jsp").forward(request, response);
	   		}
	   		else if(-2 == retFlag){
	   			String pError = "*password&nbsp;error";
				request.setAttribute("Error", pError);
		   		request.getRequestDispatcher("scmcentral/Login.jsp").forward(request, response);
	   		}
	   		else if(!rIdentifyCode.equals(tIdentifyCode)){
		   		String iError = "*identifycode&nbsp;error";
				request.setAttribute("Error", iError);
				request.getRequestDispatcher("scmcentral/Login.jsp").forward(request, response);
		   	}
	   		else if(0 == retFlag){
	   			request.getSession().setAttribute("currentUserName", user.getName());
	   			request.getSession().setAttribute("currentUserPassword", user.getPassword());
	   			
	   			if(IsAdmin(user.getName(), configRealPath)){
	   				if(request.getSession().getAttribute("currentUserRole")!=null){
	   					request.getSession().removeAttribute("currentUserRole");
	   				}
	   				request.getSession().setAttribute("currentUserRole", "administrator");
	   				response.sendRedirect("SysManServlet");
	   			}
	   			else{
	   				if(request.getSession().getAttribute("currentUserRole")!=null){
	   					request.getSession().removeAttribute("currentUserRole");
	   				}
	   				request.getSession().setAttribute("currentUserRole", "non-administrator");
	   				response.sendRedirect("ReposManServlet");
	   			}
	   		}
	   	}
	}
	
	private boolean IsAdmin(String userName, String configRealPath)
	{
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		List<String> adminUsers = sysMan.getAdmins("admin", svnRoot);
		
		for(int i = 0; i < adminUsers.size(); i++){
			if(adminUsers.get(i).equals(userName)){
				return true;
			}
		}
		
		return false;
	}
}
