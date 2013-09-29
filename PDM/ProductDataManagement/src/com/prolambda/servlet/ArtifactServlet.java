package com.prolambda.servlet;

import java.io.IOException;
import com.prolambda.model.*;
import com.prolambda.controller.*;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@SuppressWarnings("serial")
public class ArtifactServlet extends HttpServlet {

	
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
		
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		
		String flag = request.getParameter("flag");
		if(flag.equals("select")){
			selectOption(request,response);
		}else if(flag.equals("navigation")){
			navigationOption(request,response);
		}
	}
	
	public void selectOption(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		String artId = request.getParameter("artId");
		String artName = request.getParameter("artName");
		HttpSession session = request.getSession(true);
		session.setAttribute("artId", artId);
		session.setAttribute("artName", artName);
		
		ArtifactService artSer = new ArtifactService();
		Artifact art = artSer.getById(Integer.parseInt(artId));
		BuildService buildSer = new BuildService();
		BuildList buildList = buildSer.getAll(Integer.parseInt(artId));
		//int pageCount = buildSer.getPageCount(Integer.parseInt(artId));
		
		//String repId = (String)session.getAttribute("repId");
		//String repName = (String)session.getAttribute("repName");

		//ArtifactList artList = artSer.getAll(Integer.parseInt(repId));
		
		//session.setAttribute("buildlist", buildList);
		//session.setAttribute("artifact", art);
		//request.setAttribute("repName", repName);
		//request.setAttribute("artifactlist", artList);
		request.setAttribute("buildlist", buildList);
		request.setAttribute("artifact", art);
		//request.setAttribute("pageNow","1");
		//request.setAttribute("pageCount", pageCount+"");
		
		if(session!=null)
			request.getRequestDispatcher("artifactPage.jsp").forward(request, response);
	}
	
	public void navigationOption(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		HttpSession session = request.getSession(true);
		String artId = (String)session.getAttribute("artId");
		//String artName = (String)session.getAttribute("artName");
		
		ArtifactService artSer = new ArtifactService();
		Artifact art = artSer.getById(Integer.parseInt(artId));
		BuildService buildSer = new BuildService();
		BuildList buildList = buildSer.getAll(Integer.parseInt(artId));
		//int pageCount = buildSer.getPageCount(Integer.parseInt(artId));
		
		//String repId = (String)session.getAttribute("repId");
		//String repName = (String)session.getAttribute("repName");

		//ArtifactList artList = artSer.getAll(Integer.parseInt(repId));
		
		//session.setAttribute("buildlist", buildList);
		//session.setAttribute("artifact", art);
		//request.setAttribute("repName", repName);
		//request.setAttribute("artifactlist", artList);
		request.setAttribute("buildlist", buildList);
		request.setAttribute("artifact", art);
		//request.setAttribute("pageNow","1");
		//request.setAttribute("pageCount", pageCount+"");
		
		if(session!=null)
			request.getRequestDispatcher("artifactPage.jsp").forward(request, response);
	}
	
}
