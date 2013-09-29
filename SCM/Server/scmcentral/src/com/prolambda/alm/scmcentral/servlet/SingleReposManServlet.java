package com.prolambda.alm.scmcentral.servlet;

import java.io.IOException;

import com.prolambda.alm.scmcentral.entity.*;
import com.prolambda.alm.scmcentral.bll.*;
import java.util.*;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class SingleReposManServlet extends HttpServlet
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public SingleReposManServlet()
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
		
		String taction = request.getParameter("taction");
		if(taction != null && taction.equals("getMessage")){
			getMessage(request, response);

			return;
		}
		
		String SingleReposName = request.getParameter("SingleReposName");
		
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		SysMan sysMan = new SysMan();
		ReposMan reposMan = new ReposMan();
		
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		String currentUserRole = (String)request.getSession().getAttribute("currentUserRole");
		if(currentUserRole == null || !currentUserRole.equals("administrator")){
			String owner = reposMan.getReposOwner(SingleReposName, svnRoot);
			if(owner == null || !owner.equals(currentUserName)){
				response.sendRedirect("LogoutServlet");
				return;
			}
		}
		
		String serverURL = sysMan.readServerURL(configRealPath);
		ScmUser lastLogin = reposMan.getLastLogin(configRealPath);
		String url = serverURL + "/" + SingleReposName;

		List<String> structList = reposMan.getReposStruct(url, lastLogin);
		List<String> noteList = new ArrayList<String>();
		List<String> dirFlagList = new ArrayList<String>();
		List<String> noteIdList = new ArrayList<String>();
		List<String> fathIdList = new ArrayList<String>();
		
		for(int i = 0; i < structList.size(); i++){
			String[] tpBuffer = structList.get(i).split("::=");
			if(tpBuffer.length >= 3){
				noteList.add(tpBuffer[0]);
				dirFlagList.add(tpBuffer[2]);
				
				String CurrentNoteId = "";
				
				if(noteIdList.size() <= 0){
					CurrentNoteId = "1";
					noteIdList.add(CurrentNoteId);
					fathIdList.add("0");
				}
				else{
					int level = Integer.parseInt(tpBuffer[1]);
					String lastNoteId = noteIdList.get(noteIdList.size()-1);
					
					if(level > lastNoteId.length()){						
						CurrentNoteId = lastNoteId + "1";
						noteIdList.add(CurrentNoteId);
						fathIdList.add(lastNoteId);
					}
					else if(level == lastNoteId.length()){
						if(level != 1){
							CurrentNoteId = lastNoteId.substring(0, level-1) + (Integer.parseInt("" + lastNoteId.charAt(level-1))+1);
							fathIdList.add(lastNoteId.substring(0, level-1));
						}
						else{
							CurrentNoteId = (Integer.parseInt("" + lastNoteId.charAt(0))+1) + "";
							fathIdList.add("0");
						}
						noteIdList.add(CurrentNoteId);
					}
					else if(level < lastNoteId.length()){
						String tpId = lastNoteId.substring(0, level);
						if(level != 1){
							CurrentNoteId = tpId.substring(0, level-1) + (Integer.parseInt("" + tpId.charAt(level-1))+1);
							fathIdList.add(CurrentNoteId.substring(0, level-1));
						}
						else{
							CurrentNoteId = (Integer.parseInt("" + tpId.charAt(0))+1) + "";
							fathIdList.add("0");
						}
						noteIdList.add(CurrentNoteId);
					}
				}
			}
		}
		
		request.getSession().setAttribute("SingleReposName", SingleReposName);
		request.setAttribute("noteList", noteList);
		request.setAttribute("noteIdList", noteIdList);
		request.setAttribute("fathIdList", fathIdList);
		request.setAttribute("dirFlagList", dirFlagList);
		
		String realPath = ConfigUtil.getTempPath(getServletContext(), request);
		reposMan.setNoteList(noteList);
		reposMan.setNoteIdList(noteIdList);
		reposMan.setFathIdList(fathIdList);
		reposMan.setDirFlagList(dirFlagList);
		reposMan.saveStructTree(realPath);
		
		request.getRequestDispatcher("scmcentral/SingleReposMan.jsp").forward(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String action = request.getParameter("action");
		if(action != null && action.equals("temp")){
			doTemp(request, response);
			
			return;
		}
		else if(action != null && action.equals("delete")){
			doDelete(request, response);
			
			return;
		}
		else if(action != null && action.equals("unlock")){
			doUnlock(request, response);
			
			return;
		}
		else if(action != null && action.equals("authz")){
			doAuthz(request, response);
			
			return;
		}
		else if(action != null && action.equals("subproject")){
			doSubproject(request, response);
			
			return;
		}
		else if(action != null && action.equals("branchtag")){
			doBranchtag(request, response);
			
			return;
		}
		else if(action != null && action.equals("deleteAuthz")){
			doDeleteAuthz(request, response);
			
			return ;
		}
		else if(action != null && action.equals("modifyAuthz")){
			doModifyAuthz(request, response);
			
			return;
		}
	}
	
	public void doModifyAuthz(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		
		String section = (String)request.getParameter("section");
		List<UserGroup> groupAuthzs = null;
		List<ScmUser> userAuthzs = null;
		if(section != null){
		 	groupAuthzs = AuthzMan.findPathGroupPerm(section, svnRoot);
		 	userAuthzs = AuthzMan.findPathUserPerm(section, svnRoot);
		}
		if(groupAuthzs == null){
		 	groupAuthzs = new ArrayList<UserGroup>();
		}
		if(userAuthzs == null){
		 	userAuthzs = new ArrayList<ScmUser>();
		}
		
		int i = 0;
		
		for(;i < userAuthzs.size(); i++){
			String perm = request.getParameter("" + i);
			if(perm.equals("write")){
				userAuthzs.get(i).setPermission(1);
			}
			else{
				userAuthzs.get(i).setPermission(0);
			}
			AuthzMan.setUserPerm(section, userAuthzs.get(i), svnRoot);
			
		}
		
		ScmUser user = new ScmUser();
		for(int j = 0; j < groupAuthzs.size(); j++){
			String perm = request.getParameter("" + i);
			if(perm.equals("write")){
				user.setPermission(1);
			}
			else{
				user.setPermission(0);
			}
			
			String tpName = groupAuthzs.get(j).getName();
			user.setName(tpName);
			AuthzMan.setUserPerm(section, user, svnRoot);
			i++;
		}

		return;
	}
	
	public void doDeleteAuthz(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String section = request.getParameter("section");
		String[] selected = request.getParameterValues("name");
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		
		if(null == section || selected == null){
			return;
		}
		
		for(int i = 0; i < selected.length; i++){
			ScmUser user = new ScmUser(selected[i]);
			AuthzMan.deleleUserPerm(section, user, svnRoot);
		}
		
		return;
	}
	
	public void getMessage(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		String serverURL = sysMan.readServerURL(configRealPath);
		
		String selected = request.getParameter("tselected");
		String fathId = "";
		int fathIndex = -1;
		
		String realPath = ConfigUtil.getTempPath(getServletContext(), request);
		ReposMan reposMan = new ReposMan();
		reposMan.readStructTree(realPath);
		List<String> noteList = reposMan.getNoteList();
		List<String> noteIdList = reposMan.getNoteIdList();
		String SingleReposName = (String)request.getSession().getAttribute("SingleReposName");
		
		String destPath = "";
		String section = "";
		
		if(selected.equals("0")){
			destPath = serverURL + "/" + SingleReposName;
			section = SingleReposName + ":/";
		}
		else{
			destPath = serverURL + "/" + SingleReposName;
			section = SingleReposName + ":";
			for(int i = 1; i <= selected.length(); i++){
				fathId = selected.substring(0, i);
				fathIndex = noteIdList.indexOf(fathId);
				if(fathIndex >= 0){
					destPath += "/" + noteList.get(fathIndex);
					section += "/" + noteList.get(fathIndex);
				}
			}
		}
		
		ScmUser lastLogin = reposMan.getLastLogin(configRealPath);
		List<String> logMessage = reposMan.showLog(destPath, lastLogin);
		List<String> statusMessage = reposMan.showStatus(destPath, lastLogin);
		
		List<UserGroup> groupAuthzs = AuthzMan.findPathGroupPerm(section, svnRoot);
		List<ScmUser> userAuthzs = AuthzMan.findPathUserPerm(section, svnRoot);
		
		request.setAttribute("section", section);
		request.setAttribute("groupAuthzs", groupAuthzs);
		request.setAttribute("userAuthzs", userAuthzs);
		request.setAttribute("currentPath", destPath);
		request.setAttribute("logMessage", logMessage);
		request.setAttribute("statusMessage", statusMessage);
		
		request.getRequestDispatcher("scmcentral/SingleReposManSubPage.jsp").forward(request, response);
		return;
	}
	
	public void doTemp(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String sel = request.getParameter("selected");
		request.getSession().setAttribute("sel", sel);
		
		return;
	}
	
	public void doDelete(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String logMessage = (String)request.getParameter("logmessage");
		String[] tpBuffer = request.getParameterValues("path");
		List<String> delFullPaths = new ArrayList<String>();
		if(tpBuffer == null || tpBuffer.length <= 0){
			return;
		}
		else{
			for(int i = 0; i < tpBuffer.length; i++){
				delFullPaths.add(tpBuffer[i]);
			}
		}
		
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		SysMan sysMan = new SysMan();
		ReposMan reposMan = new ReposMan();
		
		String serverURL = sysMan.readServerURL(configRealPath);
		ScmUser lastLogin = reposMan.getLastLogin(configRealPath);
		
		List<String> urls = new ArrayList<String>();
		for(int i = 0; i < delFullPaths.size(); i++){
			String url = serverURL + "/" + delFullPaths.get(i);
			urls.add(url);
		}
		
		reposMan.deletes(urls, logMessage, lastLogin);
		
		return ;
	}
	
	public void doUnlock(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String[] tpBuffer = request.getParameterValues("path");
		List<String> unlockFullPaths = new ArrayList<String>();
		if(tpBuffer == null || tpBuffer.length <= 0){
			return;
		}
		else{
			for(int i = 0; i < tpBuffer.length; i++){
				unlockFullPaths.add(tpBuffer[i]);
			}
		}
		
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		SysMan sysMan = new SysMan();
		ReposMan reposMan = new ReposMan();
		
		String serverURL = sysMan.readServerURL(configRealPath);
		ScmUser lastLogin = reposMan.getLastLogin(configRealPath);
		
		for(int i = 0; i < unlockFullPaths.size(); i++){
			String url = serverURL + "/" + unlockFullPaths.get(i);
			reposMan.unlock(url, lastLogin);
		}
		
		return;
	}
	
	public void doAuthz(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String members = request.getParameter("selected");
		String authztype = request.getParameter("authztype");
		
		String[] ttpBuffer = request.getParameterValues("path");
		List<String> authzFullPaths = new ArrayList<String>();
		if(ttpBuffer == null || ttpBuffer.length <= 0){
			return;
		}
		else{
			for(int i = 0; i < ttpBuffer.length; i++){
				authzFullPaths.add(ttpBuffer[i]);
			}
		}
		
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		int permission = 0;
		if(authztype.equals("read")){
			permission = 0;
		}
		else if(authztype.equals("write")){
			permission = 1;
		}
		
		String[] tpBuffer = authzFullPaths.get(0).split("/");
		String section = tpBuffer[0] + ":";
		for(int i = 1; i < tpBuffer.length; i++){
			section += "/" + tpBuffer[i];
		}
		
		String[] tpMembers = members.split("::=");
		for(int i = 0; i < tpMembers.length; i++){
			if(-1 != tpMembers[i].indexOf('@')){
				UserGroup userGroup = new UserGroup(tpMembers[i].substring(1, tpMembers[i].length()));
				userGroup.setPermission(permission);
				AuthzMan.setGroupPerm(section, userGroup, svnRoot);
			}
			else{
				ScmUser user = new ScmUser(tpMembers[i], permission);
				AuthzMan.setUserPerm(section, user, svnRoot);
			}
		}
		
		return;
	}
	
	public void doSubproject(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String SingleReposName = (String)request.getSession().getAttribute("SingleReposName");
		String logMessage = (String)request.getParameter("logmessage");
		String subprojects = (String)request.getParameter("subprojects");
		
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		String realPath = ConfigUtil.getTempPath(getServletContext(), request);
		SysMan sysMan = new SysMan();
		ReposMan reposMan = new ReposMan();
		
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		String serverURL = sysMan.readServerURL(configRealPath);
		
		String[] tpBuffer = subprojects.split(";");
		ScmUser lastLogin = reposMan.getLastLogin(configRealPath);
		Repository repos = new Repository(SingleReposName, svnRoot);
		repos.setServerURL(serverURL);
		List<String> tpList = new ArrayList<String>();
		
		for(int i = 0; i < tpBuffer.length; i++){
			tpList.add(tpBuffer[i].trim());
		}
		
		repos.setSubProjects(tpList);
		
		reposMan.createSubProjects(repos, lastLogin, realPath, logMessage);
		
		return;
	}
	
	public void doBranchtag(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		String configRealPath = ConfigUtil.getConfigPath(getServletContext(), request);
		SysMan sysMan = new SysMan();
		String svnRoot = sysMan.readSvnRoot(configRealPath);
		String serverURL = sysMan.readServerURL(configRealPath);
		
		String SingleReposName = (String)request.getSession().getAttribute("SingleReposName");
		String logMessage = (String)request.getParameter("logmessage");
		String sourcePath = (String)request.getParameter("sourcepath");
		String destPath = (String)request.getParameter("destpath");
		
		Repository repos = new Repository();
		repos.setName(SingleReposName);
		repos.setSvnRoot(svnRoot);
		
		ReposMan reposMan = new ReposMan();
		ScmUser lastLogin = reposMan.getLastLogin(configRealPath);
		
		int Flag = 0;
		if(-1 != sourcePath.indexOf("trunk")){
			Flag = 0;
		}
		else if(-1 != sourcePath.indexOf("branches")){
			Flag = 1;
		}
		
		sourcePath = serverURL + "/" + sourcePath;
		destPath = serverURL + "/" + destPath;
		
		reposMan.branchTag(repos, sourcePath, destPath, logMessage, Flag, lastLogin);
		
		return;
	}
}









