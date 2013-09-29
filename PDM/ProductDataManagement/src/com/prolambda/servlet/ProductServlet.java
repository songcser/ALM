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
import com.prolambda.model.ProductList;
import com.prolambda.model.ProductVersion;
import com.prolambda.model.ProductVersionList;

public class ProductServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 5856222327795719030L;
	
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
		ProductCategory category = (ProductCategory)session.getAttribute("productCategory");
		int categoryId = category.getId();
		ProductService proSer = new ProductService();
		ProductList proList = proSer.getAll(categoryId);
		Product product = (Product)session.getAttribute("product");
		int productId = -1;
		
		String str = category.getName()+"|";
		for(int i=0;i<proList.size();i++){
			Product pro = proList.get(i);
			int id = i+1;
			str += id+","+pro.getId()+","+pro.getName()+"|";
			if(pro.getName().equals(product.getName())&&product!=null){
				productId = id;
			}
		}
		
		
		str += productId+","+" "+","+" ";
		
		out.println(str);
		out.flush();
		out.close();
	}
	
	public void navigationOption(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		request.getRequestDispatcher("productPage.jsp").forward(request, response);
	}
	
	public void create(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String categoryName = request.getParameter("categoryName");
		
		//String categoryId = request.getParameter("categoryId");
		
		ProductCategoryService categorySer = new ProductCategoryService();
		int categoryId = categorySer.getByName(categoryName).getId();
		
		Product pro = new Product();
		String name = request.getParameter("name");
		String description = request.getParameter("description");
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp created = Timestamp.valueOf(time);
		Timestamp modified = Timestamp.valueOf(time);
		String state = request.getParameter("state");
		
		pro.setName(name);
		pro.setDescription(description);
		pro.setCreated(created);
		pro.setModified(modified);
		pro.setState(Integer.parseInt(state));
		pro.setLastVersion("0.0");
		pro.setCategoryId(categoryId);
		
		ProductService proSer = new ProductService();
		if(proSer.contains(categoryName,name)){
			
			out.print("<script language='javascript'>alert('the repository is exist');</script>");
			
		}else if(name==""||name==null)
		{
			out.print("<script language='javascript'>alert('the name is empty');</script>");
		}else
		{
			Boolean ok = proSer.create(pro);
			if(!ok)
			{
				out.write("Create Repository error");
				out.flush();
				out.close();
			}else{
				int proId = proSer.getIdByName(categoryName, name);
				String strRet = proId+"|"+name+"|"+description+"|"+created+"|"+"0.0";
				out.println(strRet);
				
				HttpSession session = request.getSession(true);
				ProductList proList = proSer.getAll(categoryId);
				//pro.setId(proId);
				//session.setAttribute("product",pro);
				session.setAttribute("productList", proList);
				out.flush();
				out.close();
			}
		}
		
		
	}

	public void delete(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		String categoryName = request.getParameter("categoryName");
		String productName = request.getParameter("productName");
		
		ProductService proSer = new ProductService();
		int proId = proSer.getIdByName(categoryName, productName);
		
		ProductCategoryService proCateSer = new ProductCategoryService();
		ProductCategory category = proCateSer.getByName(categoryName);
		
		ProductVersionService versionSer = new ProductVersionService();
		ProductVersionList versionList = versionSer.getVersions(proId);
		
		for(ProductVersion version:versionList){
			versionSer.delete(version.getId());
		}
		
		proSer.delete(proId);
		
		HttpSession session = request.getSession(true);
		ProductList proList = proSer.getAll(category.getId());
		session.setAttribute("productList", proList);
		
		out.println(categoryName+productName);
		out.flush();
		out.close();
	}

	public void select(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		String proId = request.getParameter("productId");
		
		ProductService proSer = new ProductService();
		Product pro = proSer.getById(Integer.parseInt(proId));
		
		ProductVersionService verSer = new ProductVersionService();
		ProductVersionList versionList = verSer.getVersions(Integer.parseInt(proId));
		
		HttpSession session = request.getSession(true);
		session.setAttribute("product", pro);
		session.setAttribute("productVersionList", versionList);
		
		String isFlag = (String)session.getAttribute("isTree");
		if(isFlag==null){
			session.setAttribute("isTree", "0");
		}else{
			int index = Integer.parseInt(isFlag)+1;
			session.setAttribute("isTree", index+"");
		}
		
		request.getRequestDispatcher("productPage.jsp").forward(request, response);
	}

	public void isModify(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String name = request.getParameter("name");
		HttpSession session = request.getSession(true);
		ProductList proList = (ProductList)session.getAttribute("productList");
		for(Product pro:proList){
			if(pro.getName().equals(name)){
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
		Product pro = (Product)session.getAttribute("product");
		ProductCategory proCate = (ProductCategory)session.getAttribute("productCategory");
		String categoryName = proCate.getName();
		ProductService proSer = new ProductService();
		if(name==""||name==null)
		{
			name = pro.getName();
		}
		else if(proSer.contains(categoryName,name))
		{
			//out.print("<script language='javascript'>alert('the product is exist');</script>");
			//request.getRequestDispatcher("productPage.jsp").forward(request, response);
			return;
		}
		//out.print("<script language='javascript'>alert('the product is exist');</script>");
		if(description==""||description==null||description==" "){
			description = pro.getDescription();
		}
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp modified = Timestamp.valueOf(time);
		
		pro.setName(name);
		pro.setDescription(description);
		pro.setModified(modified);
		
		proSer.update(pro);
		
		int id = proSer.getIdByName(categoryName, name);
		
		pro = proSer.getById(id);
		///ProductService proSer = new ProductService();
		//out.print("<script language='javascript'>alert('"+name+"');</script>");
		ProductList proList = proSer.getAll(proCate.getId());
		
		session.setAttribute("product", pro);
		session.setAttribute("productList", proList);
		
		//if(session!=null){
			request.getRequestDispatcher("productPage.jsp").forward(request, response);
		//}
	}
	
}
