package com.prolambda.alm.scmcentral.servlet;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.prolambda.alm.scmcentral.bll.*;
import com.prolambda.alm.scmcentral.entity.*;

public class UserGroupManServlet extends HttpServlet
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public UserGroupManServlet()
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
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		
		UserGroupMan userGroupMan = new UserGroupMan();
		List<UserGroup> userGroups = userGroupMan.getGroupsFromRepos(svnRoot);
		if(userGroups == null){
			userGroups = new ArrayList<UserGroup>();
		}

		request.setAttribute("userGroups", userGroups);
		request.getRequestDispatcher("scmcentral/UserGroupMan.jsp").forward(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		
		String action = request.getParameter("action");
		if(action != null && action.equals("new")){
			doNew(request, response, svnRoot);
			return ;
		}
		
		if(action != null && action.equals("modify")){
			doModify(request, response, svnRoot);
			return ;
		}
		
		getMessage(request, response, svnRoot);
		return;
	}
	
	public void doModify(HttpServletRequest request, HttpServletResponse response, String svnRoot)
			throws ServletException, IOException
	{
		String groupName = request.getParameter("groupname");
		
		String tMembers = request.getParameter("selected");
		String[] Members = tMembers.split("::=");

		List<String> groupMembers = new ArrayList<String>();
		for(int i = 0; i < Members.length; i++){
			groupMembers.add(Members[i]);
		}
		
		UserGroup userGroup = new UserGroup(groupName, groupMembers);
		UserGroupMan userGroupMan = new UserGroupMan();
		userGroupMan.createGroup(userGroup, svnRoot);
		
		return;
	}
	
	public void doNew(HttpServletRequest request, HttpServletResponse response, String svnRoot)
			throws ServletException, IOException
	{
		String groupName = request.getParameter("groupname");
		
		String tMembers = request.getParameter("selected");
		String[] Members = tMembers.split("::=");
		
		List<String> groupMembers = new ArrayList<String>();
		for(int i = 0; i < Members.length; i++){
			groupMembers.add(Members[i]);
		}
		
		UserGroup userGroup = new UserGroup(groupName, groupMembers);
		UserGroupMan userGroupMan = new UserGroupMan();
		userGroupMan.createGroup(userGroup, svnRoot);
		
		return;
	}
	
	public void getMessage(HttpServletRequest request, HttpServletResponse response, String svnRoot)
			throws ServletException, IOException
	{
		String selected = request.getParameter("selected");
		
		UserGroupMan userGroupMan = new UserGroupMan();
		List<UserGroup> userGroups = userGroupMan.getGroupsFromRepos(svnRoot);
		if(userGroups == null){
			userGroups = new ArrayList<UserGroup>();
		}
		
		List<String> Authz = AuthzMan.findGroupPerm(selected, svnRoot);
		List<String> Paths = new ArrayList<String>();
		List<String> groupAuthzs = new ArrayList<String>();
		List<String> groupMembers = new ArrayList<String>();
		
		if(Authz == null){
			Authz = new ArrayList<String>();
		}
		
		for(int i = 0; i < Authz.size(); i++){
			String[] tpBuffer = Authz.get(i).split("::=");
			if(tpBuffer.length >= 2){
				Paths.add(tpBuffer[0]);
				groupAuthzs.add(tpBuffer[1]);
			}
		}
		
		for(int i = 0; i < userGroups.size(); i++){
			String tName = userGroups.get(i).getName();
			if(tName.equals(selected)){
				groupMembers = userGroups.get(i).getMembers();
			}
		}
		
		String basic = "name: " + selected + "<p></p>Id: ";
		
		request.setAttribute("basic", basic);
		request.setAttribute("groupMembers", groupMembers);
		request.setAttribute("Paths", Paths);
		request.setAttribute("userAuthzs", groupAuthzs);
		
		request.getRequestDispatcher("scmcentral/UserGroupManSubPage.jsp").forward(request, response);
		
		return;
	}
}
