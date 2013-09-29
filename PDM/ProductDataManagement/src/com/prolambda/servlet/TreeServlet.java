package com.prolambda.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.prolambda.controller.ArtifactService;
import com.prolambda.controller.BuildService;
import com.prolambda.controller.ComponentVersionService;
import com.prolambda.controller.ProductVersionService;
import com.prolambda.model.Artifact;
import com.prolambda.model.Build;
import com.prolambda.model.BuildList;
import com.prolambda.model.Component;
import com.prolambda.model.ComponentList;
import com.prolambda.model.ComponentVersion;
import com.prolambda.model.ComponentVersionList;
import com.prolambda.model.Product;
import com.prolambda.model.ProductList;
import com.prolambda.model.ProductVersion;
import com.prolambda.model.ProductVersionList;

@SuppressWarnings("serial")
public class TreeServlet extends HttpServlet {

	private int count = 500;
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
		
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		
		String flag = request.getParameter("flag");
		if(flag.equals("build")){
			buildOption(request,response);
		}else if(flag.equals("product")){
			productOption(request,response);
		}else if(flag.equals("component")){
			componentOption(request,response);
		}
		
	}
	
	public void componentOption(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String tree = "";
		
		//String countId = request.getParameter("count");
		String id = request.getParameter("id");
		
		HttpSession session = request.getSession(true);
		ComponentList comList = (ComponentList)session.getAttribute("componentList");
		Component com = comList.get(Integer.parseInt(id)-1);
		
		ComponentVersionService versionSer = new ComponentVersionService();
		ComponentVersionList versionList = versionSer.getVersions(com.getId());
		
		for(ComponentVersion version:versionList){
			int versionId = version.getId()+count;
			tree += versionId + "," + version.getVersion() + "," + version.getId()+"|";
		}
		out.println(tree);
		out.flush();
		out.close();
	}
	
	public void productOption(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String tree = "";
		
		//String countId = request.getParameter("count");
		String id = request.getParameter("id");
		
		HttpSession session = request.getSession(true);
		ProductList proList = (ProductList)session.getAttribute("productList");
		//ProductService proSer = new ProductService();
		Product pro = proList.get(Integer.parseInt(id)-1);
		
		ProductVersionService versionSer = new ProductVersionService();
		ProductVersionList versionList = versionSer.getVersions(pro.getId());
		
		for(ProductVersion version:versionList){
			int versionId = version.getId()+count;
			tree += versionId + "," + version.getVersion() + "," + version.getId()+"|";
		}
		out.println(tree);
		out.flush();
		out.close();
	}
	
	public void buildOption(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String tree = "";
		//String flag = request.getParameter("flag");
		//String countId = request.getParameter("count");
		String id = request.getParameter("id");
		//System.out.println("Building");
		//System.out.println("id:"+id);
		ArtifactService artSer = new ArtifactService();
		Artifact art = artSer.getById(Integer.parseInt(id));
			
		HttpSession session = request.getSession(true);
		session.setAttribute("artId", id);
		session.setAttribute("artName", art.getName());
			
		BuildService buildSer = new  BuildService();
		BuildList buildList = buildSer.getAll(Integer.parseInt(id));
			
		//System.out.println("build size"+buildList.size());
		for(Build build:buildList){
			int buildid = build.getId()+count;
				//tree.append(id+","+build.getNumber()+"|");
			tree += buildid + "," +build.getNumber() + ","+build.getId()+"|";
		}
		
		out.println(tree);
		out.flush();
		out.close();
	}

}
