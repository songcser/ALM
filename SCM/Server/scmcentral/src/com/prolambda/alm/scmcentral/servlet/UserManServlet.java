package com.prolambda.alm.scmcentral.servlet;

import java.io.IOException;
import com.prolambda.alm.scmcentral.bll.*;
import com.prolambda.alm.scmcentral.entity.*;
import java.util.*;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class UserManServlet extends HttpServlet
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public UserManServlet()
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
		String currentUserName = (String)request.getSession().getAttribute("currentUserName");
		if(currentUserName == null){
			response.sendRedirect("LoginServlet");
			return;
		}
		
		String flag = request.getParameter("flag");
		if(flag != null && flag.equals("1")){
			doPost(request, response);
			return;
		}
		
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		UserMan userMan = new UserMan();
		List<ScmUser> companyUsers = userMan.getUsersFromCompany(configRealPath);
		if(companyUsers == null){
			companyUsers = new ArrayList<ScmUser>();
		}
		
		for(int i = 0; i < companyUsers.size(); i++){
			String name = companyUsers.get(i).getName();
			companyUsers.get(i).setName(name.split("@")[0]);
		}
		
		request.setAttribute("companyUsers", companyUsers);
		request.getRequestDispatcher("scmcentral/UserMan.jsp").forward(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String selected = request.getParameter("selected");
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		
		List<String> Authz = AuthzMan.findUserPerm(selected, svnRoot);
		List<String> Paths = new ArrayList<String>();
		List<String> userAuthzs = new ArrayList<String>();
		
		for(int i = 0; i < Authz.size(); i++){
			String[] tpBuffer = Authz.get(i).split("::=");
			if(tpBuffer.length >= 2){
				Paths.add(tpBuffer[0]);
				userAuthzs.add(tpBuffer[1]);
			}
		}
		
		String basic = "name: " + selected + "<p></p>Id: ";
		
		request.setAttribute("basic", basic);
		request.setAttribute("Paths", Paths);
		request.setAttribute("userAuthzs", userAuthzs);
		
		request.getRequestDispatcher("scmcentral/UserManSubPage.jsp").forward(request, response);
	}

}
