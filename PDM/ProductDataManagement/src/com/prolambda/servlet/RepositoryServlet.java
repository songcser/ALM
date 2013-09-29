package com.prolambda.servlet;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Date;
import com.prolambda.model.*;
import com.prolambda.controller.*;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class RepositoryServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -573291794443616453L;
	private String strFileFolder;
	
	public void init(){
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		//ServletConfig config = getServletConfig();
		//strFileFolder = config.getInitParameter("strFileFolder");
	}
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
		
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		String flag = "";
		flag = request.getParameter("flag");
		if(flag.equals("create")){
			create(request,response);
			//out.print("<script language=javascript>window.close();");
            //out.print("</script>");
            //out.flush();
            //out.close();
		}else if(flag.equals("delete"))
		{
			delete(request,response);
			
		}
		else if(flag.equals("select"))
		{
			String repId = request.getParameter("repId");
			String repName = request.getParameter("repName");
			HttpSession session = request.getSession(true);
			session.setAttribute("repId", repId);
			session.setAttribute("repName", repName);
			
			ArtifactService artSer = new ArtifactService();
			ArtifactList artList = artSer.getAll(Integer.parseInt(repId));
			RepositoryService repSer = new RepositoryService();
			Repository rep = repSer.getByName(repName);
			//int pageCount = artSer.getPageCount(Integer.parseInt(repId));
			session.setAttribute("artifactlist", artList);
			session.setAttribute("repository", rep);

			if(session!=null)
				request.getRequestDispatcher("buildmain.jsp").forward(request, response);
		}
		else if(flag.equals("modify"))
		{
			modifyProperties(request, response);
			//out.print("<script language=javascript>window.opener.location.reload();");
			//out.print("window.close();");
           // out.print("</script>");
           // out.flush();
           // out.close();
		}else if(flag.equals("clean")){
			RepositoryService repSer = new RepositoryService();
			repSer.clean();
			File dirFile = new File(strFileFolder);
			if (dirFile.exists()) {
				File[] files = dirFile.listFiles();  
			    for (int i = 0; i < files.length; i++) {  
			        //删除子文件  
			        if (files[i].isFile()) {  
			            files[i].delete();    
			        }
			    }  
			}
			RepositoryList repList = new RepositoryList();
			BuildManagementService manageSer = new BuildManagementService();
			ConfigFileList fileList = manageSer.getAllConfig();
			
			HttpSession session = request.getSession(true);
			request.setAttribute("configfilelist", fileList);
			session.setAttribute("repositorylist", repList);
			
			request.getRequestDispatcher("buildManagementPage.jsp").forward(request, response);
		}
	}
	
	public void create(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException
	{
		PrintWriter out = response.getWriter();
		Repository rep = new Repository();
		String name = request.getParameter("name");
		String description = request.getParameter("description");
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp created = Timestamp.valueOf(time);
		Timestamp modified = Timestamp.valueOf(time);
		rep.setName(name);
		rep.setDescription(description);
		rep.setCreated(created);
		rep.setModified(modified);
		
		RepositoryService repService = new RepositoryService();
		if(repService.contains(name)){
			
			out.print("<script language='javascript'>alert('the repository is exist');</script>");
			
		}else if(name==""||name==null)
		{
			out.print("<script language='javascript'>alert('the name is empty');</script>");
		}else
		{
			Boolean ok = repService.create(rep);
			if(!ok)
			{
				out.write("Create Repository error");
				out.flush();
				out.close();
			}
		}
		RepositoryList repList;
		repList = getRepositoryList();
		BuildManagementService manageSer = new BuildManagementService();
		ConfigFileList fileList = manageSer.getAllConfig();
		
		HttpSession session = request.getSession(true);
		request.setAttribute("configfilelist", fileList);
		session.setAttribute("repositorylist", repList);
		
		request.getRequestDispatcher("buildManagementPage.jsp").forward(request, response);
	}
	
	public void delete(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException
	{
		PrintWriter out = response.getWriter();
		String name = request.getParameter("repName");
		if(name!=""&&name!=null)
		{
			out.write("repName:"+name.trim());
			RepositoryService repService = new RepositoryService();
			Repository rep = repService.getByName(name);
			ArtifactService artService = new ArtifactService();
			ArtifactList artList = artService.getAll(rep.getId());
			for(Artifact art:artList){
				BuildService buildSer = new BuildService();
				BuildList buildList = buildSer.getAll(art.getId());
				artService.delete(art.getId());
				for(Build build:buildList){
					LibraryService libSer = new LibraryService();
					LibraryList libList = libSer.getAllByBuildId(build.getId());
					buildSer.delete(build.getId());
					for(Library lib:libList){
						DependenceService depSer = new DependenceService();
						DependenceList depList = depSer.getAll(lib.getId());
						libSer.delete(lib.getId());
						for(Dependence dep:depList){
							depSer.delete(dep.getId());
						}
					}
				}
			}
			Boolean ok = repService.delete(name.trim());
			
			if(!ok)
			{
				out.write("<script language=javascript>delete repository error</script>");
				out.flush();
				out.close();
			}
		}
		RepositoryList repList;
		repList = getRepositoryList();
		BuildManagementService manageSer = new BuildManagementService();
		ConfigFileList fileList = manageSer.getAllConfig();
		
		HttpSession session = request.getSession(true);
		//int pageCount=getPageCount();
		//System.out.println("repList:"+repList.get(0).getName());
		//将al,pageCount放入rquest
		request.setAttribute("configfilelist", fileList);
		//int pageCount=getPageCount();
		//System.out.println("repList:"+repList.get(0).getName());
		//将al,pageCount放入rquest
		session.setAttribute("repositorylist", repList);
		//request.setAttribute("pageCount", pageCount+"");
		//request.setAttribute("pageNow", "1");
		
		//重新跳转回Wel.jsp
		//if(!repList.isEmpty())
			request.getRequestDispatcher("buildManagementPage.jsp").forward(request, response);
		
	}

	public RepositoryList getRepositoryList()
	{
		RepositoryList repList = new RepositoryList();
		RepositoryService repService = new RepositoryService();
		repList = repService.getAll();
		
		return repList;
		
	}
	
	public void modifyProperties(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException
	{
		PrintWriter out = response.getWriter();
		RepositoryService repService = new RepositoryService();
		Repository rep = new Repository();
		//String id = (String)request.getSession().getAttribute("repId");
		HttpSession session = request.getSession(true);
		String id = (String)session.getAttribute("repId");
		
		rep = repService.getById(Integer.parseInt(id));
		//String id = request.getParameter("repId");
		String name = request.getParameter("name");
		if(name==""||name==null)
		{
			name = rep.getName();
		}
		else if(repService.contains(name))
		{
			out.print("<script language='javascript'>alert('the repository is exist');</script>");
			return;
		}
		String description = request.getParameter("description");
		if(description==""||description==null||description==" "){
			description = rep.getDescription();
		}
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp modified = Timestamp.valueOf(time);
		
		//rep.setId(Integer.parseInt(id));
		rep.setName(name);
		rep.setDescription(description);
		rep.setModified(modified);
		
		repService.update(rep);
		
		ArtifactService artSer = new ArtifactService();
		ArtifactList artList = artSer.getAll(Integer.parseInt(id));
		//RepositoryService repSer = new RepositoryService();
		//Repository rep = repSer.getByName(repName);
		//int pageCount = artSer.getPageCount(Integer.parseInt(id));
		session.setAttribute("artifactlist", artList);
		session.setAttribute("repository", rep);
		//request.setAttribute("artifactlist", artList);
		//request.setAttribute("repository", rep);
		//request.setAttribute("pageNow","1");
		//request.setAttribute("pageCount", pageCount+"");

		if(session!=null)
			request.getRequestDispatcher("repositoryPage.jsp").forward(request, response);
	}
}
