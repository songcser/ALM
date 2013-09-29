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
import com.prolambda.model.ComponentList;
import com.prolambda.model.ComponentVersion;
import com.prolambda.model.ComponentVersionList;
import com.prolambda.model.Library;
import com.prolambda.model.LibraryList;

public class ComponentServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -6928077782629974344L;

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
		if(flag.equals("create")){
			create(request,response);
		}else if(flag.equals("delete")){
			delete(request,response);
		}else if(flag.equals("select")){
			select(request,response);
		}else if(flag.equals("navigation")){
			navigationOption(request,response);
		}else if(flag.equals("getTree")){
			getTree(request,response);
		}else if(flag.equals("modify")){
			modify(request,response);
		}else if(flag.equals("isModify")){
			isModify(request,response);
		}
		
		out.flush();
		out.close();
	}

	public void getTree(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		//String categoryId = request.getParameter("categoryId");
		
		HttpSession session = request.getSession(true);
		ComponentCategory category = (ComponentCategory)session.getAttribute("componentCategory");
		int categoryId = category.getId();
		ComponentService comSer = new ComponentService();
		ComponentList comList = comSer.getAll(categoryId);
		Component component = (Component)session.getAttribute("component");
		int componentId = -1;
		
		String str = category.getName()+"|";
		for(int i=0;i<comList.size();i++){
			Component com = comList.get(i);
			int id = i+1;
			str += id+","+com.getId()+","+com.getName()+"|";
			if(com.getName().equals(component.getName())&&component!=null){
				componentId = id;
			}
		}
		
		str += componentId+","+" "+","+" ";
		
		out.println(str);
		out.flush();
		out.close();
	}
	
	public void navigationOption(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		request.getRequestDispatcher("componentPage.jsp").forward(request, response);
	}
	
	public void create(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String categoryName = request.getParameter("categoryName");
		//String categoryId = request.getParameter("categoryId");
		
		ComponentCategoryService categorySer = new ComponentCategoryService();
		int categoryId = categorySer.getByName(categoryName).getId();
		
		Component com = new Component();
		String name = request.getParameter("name");
		String description = request.getParameter("description");
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp created = Timestamp.valueOf(time);
		Timestamp modified = Timestamp.valueOf(time);
		com.setName(name);
		com.setDescription(description);
		com.setCreated(created);
		com.setModified(modified);
		com.setLastVersion("0.0");
		com.setCategoryId(categoryId);
		
		ComponentService comSer = new ComponentService();
		if(comSer.contains(categoryName,name)){
			
			out.print("<script language='javascript'>alert('the repository is exist');</script>");
			
		}else if(name==""||name==null)
		{
			out.print("<script language='javascript'>alert('the name is empty');</script>");
		}else
		{
			Boolean ok = comSer.create(com);
			if(!ok)
			{
				out.write("Create Repository error");
				out.flush();
				out.close();
			}else{
				int comId = comSer.getIdByName(categoryName, name);
				String strRet = comId+"|"+name+"|"+description+"|"+created+"|"+"0.0";
				out.println(strRet);
				
				HttpSession session = request.getSession(true);
				ComponentList comList = comSer.getAll(categoryId);
				//com.setId(comId);
				session.setAttribute("componentList", comList);
				//session.setAttribute("component", com);
				out.flush();
				out.close();
			}
		}
		
	}

	public void delete(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		String categoryName = request.getParameter("categoryName");
		String componentName = request.getParameter("componentName");
		
		ComponentService comSer = new ComponentService();
		int comId = comSer.getIdByName(categoryName, componentName);
		
		ComponentCategoryService comCateSer = new ComponentCategoryService();
		ComponentCategory category = comCateSer.getByName(categoryName);
		
		ComponentVersionService versionSer = new ComponentVersionService();
		ComponentVersionList versionList = versionSer.getVersions(comId);
		
		LibraryService libSer = new LibraryService();
		for(ComponentVersion version:versionList){
			LibraryList libList = libSer.getAllByComponentId(version.getId());
			for(Library lib:libList){
				libSer.delete(lib.getId());
				
				File file = new File(strFileFolder+"/"+lib.getFileName());
				
				if(file.exists()){
					file.delete();
				}
			}
		}
		
		comSer.delete(comId);
		
		HttpSession session = request.getSession(true);
		ComponentList comList = comSer.getAll(category.getId());
		session.setAttribute("componentList", comList);
		
		out.println(categoryName+componentName);
		out.flush();
		out.close();
	}

	public void select(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		String comId = request.getParameter("componentId");
		
		ComponentService comSer = new ComponentService();
		Component com = comSer.getById(Integer.parseInt(comId));
		
		ComponentVersionService verSer = new ComponentVersionService();
		ComponentVersionList versionList = verSer.getVersions(Integer.parseInt(comId));
		
		HttpSession session = request.getSession(true);
		session.setAttribute("component", com);
		session.setAttribute("componentVersionList", versionList);

		String isFlag = (String)session.getAttribute("isTree1");
		if(isFlag==null){
			session.setAttribute("isTree1", "0");
		}else{
			int index = Integer.parseInt(isFlag)+1;
			session.setAttribute("isTree1", index+"");
		}
		
		request.getRequestDispatcher("componentPage.jsp").forward(request, response);
	}

	public void isModify(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String name = request.getParameter("name");
		HttpSession session = request.getSession(true);
		ComponentList comList = (ComponentList)session.getAttribute("componentList");
		for(Component com:comList){
			if(com.getName().equals(name)){
				out.println("false");
				out.flush();
				out.close();
				return;
			}
		}
		out.print("true");
		out.flush();
		out.close();
	}
	public void modify(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
		//PrintWriter out = response.getWriter();
		
		String name = request.getParameter("name");
		String description = request.getParameter("description");
		//String categoryName = request.getParameter("categoryName");
		HttpSession session = request.getSession(true);
		Component com = (Component)session.getAttribute("component");
		ComponentCategory comCate = (ComponentCategory)session.getAttribute("componentCategory");
		String categoryName = comCate.getName();
		ComponentService comSer = new ComponentService();
		if(name==""||name==null)
		{
			name = com.getName();
		}
		else if(comSer.contains(categoryName,name))
		{
			return;
		}
		//out.print("<script language='javascript'>alert('the product is exist');</script>");
		if(description==""||description==null||description==" "){
			description = com.getDescription();
		}
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp modified = Timestamp.valueOf(time);
		
		com.setName(name);
		com.setDescription(description);
		com.setModified(modified);
		
		comSer.update(com);
		
		int id = comSer.getIdByName(categoryName, name);
		
		com = comSer.getById(id);
		///ProductService proSer = new ProductService();
		//out.print("<script language='javascript'>alert('"+name+"');</script>");
		ComponentList comList = comSer.getAll(comCate.getId());
		
		session.setAttribute("component", com);
		session.setAttribute("componentList", comList);
		
		//if(session!=null){
			request.getRequestDispatcher("componentPage.jsp").forward(request, response);
		//}
	}
}
