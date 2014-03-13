package com.prolambda.scmserv.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import com.prolambda.scmserv.bll.*;
import com.prolambda.scmserv.entity.*;

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

public class SysManServlet extends HttpServlet
{
	public SysManServlet()
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
		
		String currentUserRole = (String)request.getSession().getAttribute("currentUserRole");
		if(currentUserRole == null || !currentUserRole.equals("administrator")){
			response.sendRedirect("LogoutServlet");
			return;
		}
		
		String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		String serverURL = sysMan.readServerURL(configRealPath);
		String recycleBin = sysMan.readRecycleBin(configRealPath);
		
		UserMan userMan = new UserMan();
		List<ScmUser> systemUsers = userMan.getUsersFromSystem(configRealPath);
		
		request.setAttribute("svnRoot", svnRoot);
		request.setAttribute("serverURL", serverURL);
		request.setAttribute("systemUsers", systemUsers);
		request.setAttribute("recycleBin", recycleBin);
		
		request.getRequestDispatcher("SysMan.jsp").forward(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String action = request.getParameter("action");
		if(action != null && action.equals("savesvnroot")){
			doSaveSvnRoot(request, response);
			
			return;
		}
		else if(action != null && action.equals("saveserverurl")){
			doSaveServerURL(request, response);
			
			return;
		}
		else if(action != null && action.equals("saverecycle")){
			doSaveRecycle(request,response);
		}
		else if(action != null && action.equals("addSystemUsers")){
			doAddSystemUsers(request, response);
		
			return;
		}
		else if(action != null && action.equals("deleteSystemUsers")){
			doDeleteSystemUsers(request, response);
			
			return;
		}
		else if(action != null && action.equals("setadmin")){
			doSetAdmin(request, response);
			
			return;
		}
		else if(action != null && action.equals("canceladmin")){
			doCancelAdmin(request, response);
			
			return;
		}
	}
	
	public void doSetAdmin(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String[] tpBuffer = request.getParameterValues("name");
		String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
		
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		
		List<String> adminUsers = new ArrayList<String>();
		if(tpBuffer != null && tpBuffer.length >= 1){
			for(int i = 0; i < tpBuffer.length; i++){
				adminUsers.add(tpBuffer[i]);
			}
		}
		
		sysMan.setAdmins(adminUsers, svnRoot);
	}
	
	public void doCancelAdmin(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String[] tpBuffer = request.getParameterValues("name");
		String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
		
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		
		List<String> adminUsers = new ArrayList<String>();
		if(tpBuffer != null && tpBuffer.length >= 1){
			for(int i = 0; i < tpBuffer.length; i++){
				adminUsers.add(tpBuffer[i]);
			}
		}
		
		sysMan.cancelAdmins(adminUsers, svnRoot);
	}
	
	public void doSaveSvnRoot(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
		String svnRoot = request.getParameter("svnroot");
		svnRoot = svnRoot.trim();
		if(svnRoot.lastIndexOf('\\') == svnRoot.length()-1){
			svnRoot = svnRoot.substring(0, svnRoot.length()-1);
		}
		SysMan sysMan = new SysMan();
		sysMan.setSvnRoot(svnRoot);
		//ScmUser lastLogin = sysMan.getLastLogin(configRealPath);
		String username = (String)request.getSession().getAttribute("currentUserName");
		String userpassword = (String)request.getSession().getAttribute("currentUserPassword");
		ScmUser lastLogin = new ScmUser();
		lastLogin.setName(username);
		//System.out.println("Password: "+userpassword);
		lastLogin.setAESPassword(userpassword);
		
		sysMan.saveSvnRoot(configRealPath, lastLogin);
	}

	public void doSaveServerURL(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
		String serverURL = request.getParameter("serverurl");
		serverURL = serverURL.trim();
		if(serverURL.lastIndexOf('/') == serverURL.length()-1){
			serverURL = serverURL.substring(0, serverURL.length()-1);
		}
		SysMan sysMan = new SysMan();
		sysMan.setServerURL(serverURL);
		sysMan.saveServerURL(configRealPath);
	}
	
	public void doSaveRecycle(HttpServletRequest request, HttpServletResponse response){
		String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
		String recycle = request.getParameter("recycle");
		recycle = recycle.trim();
		if(recycle.lastIndexOf('/') == recycle.length()-1){
			recycle = recycle.substring(0, recycle.length()-1);
		}
		SysMan sysMan = new SysMan();
		sysMan.setRecycleBin(recycle);
		sysMan.saveRecycleBin(configRealPath);
	}
	
	public void doAddSystemUsers(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
		UserMan userMan = new UserMan();
		List<ScmUser> companyUsers = userMan.getUsersFromCompany(configRealPath);
		
		String selected = request.getParameter("selected");
		String[] tpBuffer = selected.split("::=");
		
		for(int i = 0; i < tpBuffer.length; i++){
			for(int k = 0; k < companyUsers.size(); k++){
				String[] ttpBuffer = companyUsers.get(k).getName().split("@");
				if(ttpBuffer.length >= 2){
					if(tpBuffer[i].equals(ttpBuffer[0])){
						ScmUser user = new ScmUser(tpBuffer[i]);
						user.setId(companyUsers.get(k).getId());
						userMan.createSystemUsers(user, configRealPath);
					}
				}
			}
		}
	}
	
	public void doDeleteSystemUsers(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String[] tpBuffer = request.getParameterValues("name");
		String configRealPath = request.getSession().getServletContext().getRealPath("\\config\\Config.ini");
		
		UserMan userMan = new UserMan();
		List<ScmUser> systemUsers = userMan.getUsersFromSystem(configRealPath);
		String username = (String)request.getSession().getAttribute("currentUserName");
		String userpassword = (String)request.getSession().getAttribute("currentUserPassword");
		ScmUser lastLogin = new ScmUser();
		lastLogin.setName(username);
		lastLogin.setAESPassword(userpassword);
		
		//ScmUser lastLogin = reposMan.getLastLogin(configRealPath);
		
		for(int i = 0; i < tpBuffer.length; i++){
			if(tpBuffer[i].equals(lastLogin.getName())){
				continue;
			}
			for(int k = 0; k < systemUsers.size(); k++){
				if(tpBuffer[i].equals(systemUsers.get(k).getName())){
					userMan.deleteSystemUsers(systemUsers.get(k), configRealPath);
				}
			}
		}
		
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		
		List<String> adminUsers = new ArrayList<String>();
		if(tpBuffer != null && tpBuffer.length >= 1){
			for(int i = 0; i < tpBuffer.length; i++){
				adminUsers.add(tpBuffer[i]);
			}
		}
		
		sysMan.cancelAdmins(adminUsers, svnRoot);
	}
}
