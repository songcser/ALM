package com.prolambda.servlet;

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

import com.prolambda.controller.ProductCategoryService;
import com.prolambda.controller.ProductService;
import com.prolambda.controller.ProductVersionService;
import com.prolambda.model.Product;
import com.prolambda.model.ProductCategory;
import com.prolambda.model.ProductCategoryList;
import com.prolambda.model.ProductList;
import com.prolambda.model.ProductVersion;
import com.prolambda.model.ProductVersionList;

public class ProductCategoryServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 7600413694434587854L;


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
		ProductCategoryService proCateSer = new ProductCategoryService();
		if(proCateSer.contains(name)){
			out.print("no");
		}else
			out.print("yes");
		out.flush();
		out.close();
	}
	
	public void create(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
		PrintWriter out = response.getWriter();
		ProductCategory proCategory = new ProductCategory();
		String name = request.getParameter("name");
		String description = request.getParameter("description");
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp created = Timestamp.valueOf(time);
		Timestamp modified = Timestamp.valueOf(time);
		proCategory.setName(name);
		proCategory.setDescription(description);
		proCategory.setCreated(created);
		proCategory.setModified(modified);
		proCategory.setProductCount(0);
		
		ProductCategoryService proCateSer = new ProductCategoryService();
		if(proCateSer.contains(name)){
			
			out.print("<script language='javascript'>alert('the product category is exist');</script>");
			return ;
			
		}else if(name==""||name==null)
		{
			out.print("<script language='javascript'>alert('the name is empty');</script>");
		}else
		{
			Boolean ok = proCateSer.create(proCategory);
			if(!ok)
			{
				out.write("Create Product Category error");
				out.flush();
				out.close();
			}else{
				HttpSession session = request.getSession(true);
				ProductCategoryList proCateList = proCateSer.getAll();

				ProductCategory category = proCateSer.getByName(name);
				ProductService proSer = new ProductService();
				ProductList proList = proSer.getAll(category.getId());
				session.setAttribute("productCategory", category);
				session.setAttribute("productCategoryList", proCateList);
				if(proList==null){
					session.setAttribute("productList", null);
				}else
					session.setAttribute("productList", proList);
				response.sendRedirect("productContentPage.jsp");
			}
		}
	}

	public void delete(HttpServletRequest request, HttpServletResponse response){
		String name = request.getParameter("name");
		ProductCategoryService proCateSer = new ProductCategoryService();
		ProductService proSer = new ProductService();
		ProductVersionService versionSer = new ProductVersionService();
		ProductCategory category = proCateSer.getByName(name);
		ProductList proList = proSer.getAll(category.getId());
		
		for(Product pro:proList){
			ProductVersionList versionList = versionSer.getVersions(pro.getId());
			
			for(ProductVersion version:versionList){
				
				if(!versionSer.delete(version.getId())){
					return;
				}
			}
			if(!proSer.delete(pro.getId())){
				return;
			}
		}
		
		if(!proCateSer.delete(name)){
			return;
		}
		
		HttpSession session = request.getSession(true);
		ProductCategoryList proCateList = proCateSer.getAll();
		
		session.setAttribute("productCategoryList", proCateList);
	}
	
	public void select(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		String categoryName = request.getParameter("categoryName");
		//System.out.println("Name:"+categoryName);
		String name = categoryName.replace('$', ' ');
		PrintWriter out = response.getWriter();
		ProductCategoryService proCateSer = new ProductCategoryService();
		ProductCategory proCate = proCateSer.getByName(name);
		ProductService proSer = new ProductService();
		//out.print("<script language='javascript'>alert('"+name+"');</script>");
		ProductList proList = proSer.getAll(proCate.getId());
		//out.println(proCate.getId());
		//out.println(name);
		HttpSession session = request.getSession(true);
		session.setAttribute("productCategory", proCate);
		if(proList==null){
			session.setAttribute("productList", null);
		}else
			session.setAttribute("productList", proList);
		
		if(session!=null){
			
			response.sendRedirect("productContentPage.jsp");
			//request.getRequestDispatcher("productContentPage.jsp").forward(request, response);
		}
		out.flush();
		out.close();
	}
	
	public void isModify(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String name = request.getParameter("name");
		ProductCategoryService categorySer = new ProductCategoryService();
		ProductCategoryList categoryList = categorySer.getAll();
		
		for(ProductCategory category:categoryList){
			if(category.getName().equals(name)&&!"".equals(name)){
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
		ProductCategory proCate = (ProductCategory)session.getAttribute("productCategory");
		ProductCategoryService proCateSer = new ProductCategoryService();
		if(name==""||name==null)
		{
			name = proCate.getName();
		}
		else if(proCateSer.contains(name))
		{
			out.print("<script language='javascript'>alert('the product category is exist');</script>");
			return;
		}
		
		if(description==""||description==null||description==" "){
			description = proCate.getDescription();
		}
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp modified = Timestamp.valueOf(time);
		
		proCate.setName(name);
		proCate.setDescription(description);
		proCate.setModified(modified);
		
		proCateSer.update(proCate);
		
		ProductService proSer = new ProductService();
		//out.print("<script language='javascript'>alert('"+name+"');</script>");
		ProductList proList = proSer.getAll(proCate.getId());
		proCate = proCateSer.getByName(name);
		session.setAttribute("productCategory", proCate);
		session.setAttribute("productList", proList);
		
		if(session!=null){
			request.getRequestDispatcher("productContentPage.jsp").forward(request, response);
		}
	}
}
