package com.prolambda.scmserv.servlet;

import com.prolambda.scmserv.dal.IniFileOpe;
import com.prolambda.scmserv.entity.*;
import com.prolambda.scmserv.bll.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.*;

import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class LoginServlet extends HttpServlet
{
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
		String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
   		
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
   		
   		
		request.getRequestDispatcher("Login.jsp").forward(request, response);
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
	   	
	   	String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
   		ScmUser user = new ScmUser(name, password, "", -1);
   		Login login = new Login(user);
   		UserMan userMan = new UserMan();
   		
	   	if(FirstUse.equals("yes")){
	   		List<ScmUser> companyUsers = userMan.getUsersFromCompany(configRealPath);
	   		int retFlag = 0;
			retFlag = login.userFirstLogin(companyUsers, configRealPath, 1);
	   		
	   		if(!rIdentifyCode.equals(tIdentifyCode)){
		   		String iError = "*identifycode&nbsp;error";
				request.setAttribute("Error", iError);
				request.getRequestDispatcher("Login.jsp").forward(request, response);
		   	}
	   		else if(0 == retFlag){
	   			request.getSession().setAttribute("currentUserName", user.getName());
	   			request.getSession().setAttribute("currentUserPassword", user.getAESPassword());
	   			
	   			if(request.getSession().getAttribute("currentUserRole")!=null){
   					request.getSession().removeAttribute("currentUserRole");
   				}
   				request.getSession().setAttribute("currentUserRole", "administrator");
	   			response.sendRedirect("SysManServlet");
	   		}
	   		else{
	   			String Error = "*username&nbspor&nbsp;password&nbsp;error";
				request.setAttribute("Error", Error);
		   		request.getRequestDispatcher("Login.jsp").forward(request, response);
	   		}
	   	}
	   	else{
	   		List<ScmUser> sysUsers = userMan.getUsersFromSystem(configRealPath);
	   		
	   		int retFlag =0;
			retFlag = login.userLogin(sysUsers, configRealPath, 1);
	   		
	   		if(-1 == retFlag || -3 == retFlag){
	   			String uError = "*username&nbsp;error";
				request.setAttribute("Error", uError);
		   		request.getRequestDispatcher("Login.jsp").forward(request, response);
	   		}
	   		else if(-2 == retFlag){
	   			String pError = "*password&nbsp;error";
				request.setAttribute("Error", pError);
		   		request.getRequestDispatcher("Login.jsp").forward(request, response);
	   		}
	   		else if(!rIdentifyCode.equals(tIdentifyCode)){
		   		String iError = "*identifycode&nbsp;error";
				request.setAttribute("Error", iError);
				request.getRequestDispatcher("Login.jsp").forward(request, response);
		   	}
	   		else if(0 == retFlag){
	   			
	   			request.getSession().setAttribute("currentUserName", user.getName());
	   			String pwd = user.getAESPassword();
				request.getSession().setAttribute("currentUserPassword", pwd);
				//System.out.println(pwd);
	   			
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
