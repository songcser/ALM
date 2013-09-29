package com.prolambda.alm.scmcentral.servlet;

import java.io.IOException;
import com.prolambda.alm.scmcentral.entity.*;
import com.prolambda.alm.scmcentral.bll.*;
import java.util.*;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ReposManServlet extends HttpServlet
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public ReposManServlet()
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
		
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		String ServerURL = sysMan.readServerURL(configRealPath);
		
		ReposMan reposMan = new ReposMan();
		ScmUser lastLogin = reposMan.getLastLogin(configRealPath);
		List<Repository> reposes = reposMan.getAllRepos(svnRoot, ServerURL, lastLogin);
		
		if(!request.getSession().getAttribute("currentUserRole").equals("administrator")){
			for(int i = reposes.size()-1; i >= 0; i--){
				String owner = reposMan.getReposOwner(reposes.get(i).getName(), svnRoot);
				if(owner == null){
					reposes.remove(i);
				}
				else{
					if(!owner.equals(currentUserName)){
						reposes.remove(i);
					}
				}
			}
		}
		
		for(int i = 0; i < reposes.size(); i++){
			for(int j = 0; j < reposes.get(i).getSubProjects().size(); j++){
				String tpString = reposes.get(i).getSubProjects().get(j);
				reposes.get(i).getSubProjects().set(j, tpString.substring(0, tpString.length()-1));
			}
			for(int j = 0; j < reposes.get(i).getBranches().size(); j++){
				String tpString = reposes.get(i).getBranches().get(j);
				reposes.get(i).getBranches().set(j, tpString.substring(0, tpString.length()-1));
			}
			for(int j = 0; j < reposes.get(i).getTags().size(); j++){
				String tpString = reposes.get(i).getTags().get(j);
				reposes.get(i).getTags().set(j, tpString.substring(0, tpString.length()-1));
			}
		}
		
		request.setAttribute("reposes", reposes);
		request.getRequestDispatcher("scmcentral/ReposMan.jsp").forward(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		String action = (String)request.getParameter("action");
		if(action.equals("delete")){
			
			SysMan sysMan = new SysMan();
			String svnRoot = sysMan.readSvnRoot(configRealPath);
			
			String[] names = request.getParameterValues("reposname");
			
			if(names.length > 0){
				Repository repos = new Repository(names[0], svnRoot);
				ReposMan reposMan = new ReposMan();
				reposMan.deleteRepos(repos);
			}
		}
		else if(action.equals("create")){
			
			String realPath = ConfigUtil.getTempPath(getServletContext(), request);
			SysMan sysMan = new SysMan();
			String svnRoot = sysMan.readSvnRoot(configRealPath);
			String serverURL = sysMan.readServerURL(configRealPath);
			String name = request.getParameter("reposname");
			String owner = request.getParameter("s1");
			Repository repos = new Repository(name, svnRoot);
			repos.setServerURL(serverURL);
			repos.setOwner(owner);
			ReposMan reposMan = new ReposMan();
			ScmUser lastLogin = reposMan.getLastLogin(configRealPath);
			reposMan.createRepos(repos, lastLogin, realPath);
		}
		else if(action.equals("changeowner")){
			
			SysMan sysMan = new SysMan();
			String svnRoot = sysMan.readSvnRoot(configRealPath);
			
			String reposName = request.getParameter("reposname");
			String newOwner = request.getParameter("s1");
			ReposMan reposMan = new ReposMan();
			String owner = reposMan.getReposOwner(reposName, svnRoot);
			reposMan.changeOwner(svnRoot, reposName, owner, newOwner);
		}
	}
}
