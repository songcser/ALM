package com.prolambda.servlet;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.prolambda.controller.ComponentCategoryService;
import com.prolambda.controller.ComponentService;
import com.prolambda.controller.ComponentVersionService;
import com.prolambda.controller.LibraryService;
import com.prolambda.model.Component;
import com.prolambda.model.ComponentCategory;
import com.prolambda.model.ComponentCategoryList;
import com.prolambda.model.ComponentList;
import com.prolambda.model.ComponentVersion;
import com.prolambda.model.ComponentVersionList;
import com.prolambda.model.Library;
import com.prolambda.model.LibraryList;

public class ComponentCategoryServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -132259992914363201L;

	private String strFileFolder;

	public void init(){
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		//ServletConfig config = getServletConfig();
		//strFileFolder = config.getInitParameter("strFileFolder");
		File file = new File(strFileFolder);
		if (!file.exists()) {
			file.mkdirs();
		}
	}
	
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		
		String flag = request.getParameter("flag");
		//out.print("test");
		if(flag.equals("create")){
			create(request,response);
		}else if(flag.equals("delete")){
			delete(request,response);
		}else if(flag.equals("select")){
			select(request,response);
		}else if(flag.equals("modify")){
			modify(request,response);
		}else if(flag.equals("isCreate")){
			isCreate(request,response);
		}else if(flag.equals("isModify")){
			isModify(request,response);
		}
		
		out.flush();
		out.close();
	}
	
	public void isCreate(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		String name = request.getParameter("name");
		ComponentCategoryService comCateSer = new ComponentCategoryService();
		if(comCateSer.contains(name)){
			out.print("no");
		}else
			out.print("yes");
		out.flush();
		out.close();
	}
	
	public void create(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
		PrintWriter out = response.getWriter();
		ComponentCategory comCategory = new ComponentCategory();
		String name = request.getParameter("name");
		String description = request.getParameter("description");
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp created = Timestamp.valueOf(time);
		Timestamp modified = Timestamp.valueOf(time);
		comCategory.setName(name);
		comCategory.setDescription(description);
		comCategory.setCreated(created);
		comCategory.setModified(modified);
		comCategory.setComponentCount(0);
		
		ComponentCategoryService comCateSer = new ComponentCategoryService();
		if(comCateSer.contains(name)){
			
			out.print("<script language='javascript'>alert('the repository is exist');</script>");
			
		}else if(name==""||name==null)
		{
			out.print("<script language='javascript'>alert('the name is empty');</script>");
		}else
		{
			Boolean ok = comCateSer.create(comCategory);
			if(!ok)
			{
				out.write("Create Component Category error");
				out.flush();
				out.close();
			}else{
				HttpSession session = request.getSession(true);
				ComponentCategoryList comCateList = comCateSer.getAll();
				ComponentCategory category = comCateSer.getByName(name);
				ComponentService comSer = new ComponentService();
				ComponentList comList = comSer.getAll(category.getId());
				
				if(comList==null){
					session.setAttribute("componentList", null);
				}else
					session.setAttribute("componentList", comList);
				
				session.setAttribute("componentCategoryList", comCateList);
				session.setAttribute("componentCategory", category);
				
				response.sendRedirect("componentContentPage.jsp");
			}
		}
	}

	public void delete(HttpServletRequest request, HttpServletResponse response){
		String name = request.getParameter("name");
		ComponentCategoryService comCateSer = new ComponentCategoryService();
		ComponentService comSer = new ComponentService();
		ComponentVersionService versionSer = new ComponentVersionService();
		LibraryService libSer = new LibraryService();
		
		ComponentCategory category = comCateSer.getByName(name);
		ComponentList comList = comSer.getAll(category.getId());
		
		for(Component com:comList){
			ComponentVersionList versionList = versionSer.getVersions(com.getId());
			
			for(ComponentVersion version:versionList){
				LibraryList libList = libSer.getAllByComponentId(version.getId());
				
				for(Library lib:libList){
					libSer.delete(lib.getId());
					
					File file = new File(strFileFolder+"/"+lib.getFileName());
					
					if(file.exists()){
						file.delete();
					}
				}
				
				if(!versionSer.delete(version.getId())){
					return;
				}
			}
			if(!comSer.delete(com.getId())){
				return;
			}
		}
		
		
		if(!comCateSer.delete(name)){
			return;
		}
		
		HttpSession session = request.getSession(true);
		ComponentCategoryList comCateList = comCateSer.getAll();
		session.setAttribute("componentCategoryList", comCateList);
	}
	
	public void select(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		String categoryName = request.getParameter("categoryName");
		String name = categoryName.replace('*', ' ');
		PrintWriter out = response.getWriter();
		ComponentCategoryService comCateSer = new ComponentCategoryService();
		ComponentCategory comCate = comCateSer.getByName(name);
		ComponentService comSer = new ComponentService();
		//out.print("<script language='javascript'>alert('"+name+"');</script>");
		ComponentList comList = comSer.getAll(comCate.getId());
		//out.println(comList.size()+"");
		//out.println(name);
		HttpSession session = request.getSession(true);
		session.setAttribute("componentCategory",comCate);
		if(comList==null){
			session.setAttribute("componentList", null);
		}else
			session.setAttribute("componentList", comList);
		
		if(session!=null){
			response.sendRedirect("componentContentPage.jsp");
			//request.getRequestDispatcher("productContentPage.jsp").forward(request, response);
		}
		out.flush();
		out.close();
	}
	
	public void isModify(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String name = request.getParameter("name");
		ComponentCategoryService categorySer = new ComponentCategoryService();
		ComponentCategoryList categoryList = categorySer.getAll();
		
		for(ComponentCategory category:categoryList){
			if(category.getName().equals(name)){
				out.print("no");
				out.flush();
				out.close();
				return;
			}
		}
		
		out.print("yes");
		out.flush();
		out.close();
		
	}
	
	public void modify(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
		PrintWriter out = response.getWriter();
		
		String name = request.getParameter("name");
		String description = request.getParameter("description");
		HttpSession session = request.getSession(true);
		ComponentCategory comCate = (ComponentCategory)session.getAttribute("componentCategory");
		ComponentCategoryService comCateSer = new ComponentCategoryService();
		if(name==""||name==null)
		{
			name = comCate.getName();
		}
		else if(comCateSer.contains(name))
		{
			out.print("<script language='javascript'>alert('the component category is exist');</script>");
			return;
		}
		
		if(description==""||description==null||description==" "){
			description = comCate.getDescription();
		}
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp modified = Timestamp.valueOf(time);
		
		comCate.setName(name);
		comCate.setDescription(description);
		comCate.setModified(modified);
		
		comCateSer.update(comCate);
		
		ComponentService comSer = new ComponentService();
		//out.print("<script language='javascript'>alert('"+name+"');</script>");
		ComponentList comList = comSer.getAll(comCate.getId());
		comCate = comCateSer.getByName(name);
		session.setAttribute("componentCategory", comCate);
		session.setAttribute("componentList", comList);
		
		if(session!=null){
			request.getRequestDispatcher("componentContentPage.jsp").forward(request, response);
		}
	}
}
