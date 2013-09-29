package com.prolambda.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.prolambda.controller.BuildManagementService;
import com.prolambda.controller.ComponentCategoryService;
import com.prolambda.controller.ComponentService;
import com.prolambda.controller.ProductCategoryService;
import com.prolambda.controller.ProductService;
import com.prolambda.controller.UserService;
import com.prolambda.model.ComponentCategory;
import com.prolambda.model.ComponentCategoryList;
import com.prolambda.model.ComponentList;
import com.prolambda.model.ConfigFileList;
import com.prolambda.model.ProductCategory;
import com.prolambda.model.ProductCategoryList;
import com.prolambda.model.ProductList;
import com.prolambda.model.RepositoryList;
import com.prolambda.model.PDMUserList;

public class PDMServlet extends HttpServlet {
	
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 2000607511752615943L;

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
		
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		String value = request.getParameter("pdm");
		if(value.equals("Home"))
		{
			response.sendRedirect("home.jsp");
		}
		else if(value.equals("BuildManagement"))
		{
			RepositoryServlet repServlet = new RepositoryServlet();
			RepositoryList repList = new RepositoryList();
			repList = repServlet.getRepositoryList();
			
			BuildManagementService manageSer = new BuildManagementService();
			ConfigFileList fileList = manageSer.getAllConfig();
			
			HttpSession session = request.getSession(true);
			
			request.setAttribute("configfilelist", fileList);
			session.setAttribute("repositorylist", repList);
			
			request.getRequestDispatcher("buildManagementPage.jsp").forward(request, response);
		}
		else if(value.equals("ProductCategory")){
			ProductCategoryService proCateSer = new ProductCategoryService();
			ProductCategoryList proCateList = proCateSer.getAll();
			ProductCategory proCate = new ProductCategory();
			ProductService proSer = new ProductService();
			ProductList proList = new ProductList();
			if(proCateList.size()>0){
				proCate = proCateList.get(0);
				proList = proSer.getAll(proCate.getId());
			}
			
			HttpSession session = request.getSession(true);
			session.setAttribute("productCategoryList", proCateList);
			session.setAttribute("productCategory", proCate);
			session.setAttribute("productList", proList);
			session.setAttribute("isTree", "0");
			if(session!=null)
				request.getRequestDispatcher("productCategory.jsp").forward(request, response);
			
		}else if(value.equals("ComponentCategory")){
			ComponentCategoryService comCateSer = new ComponentCategoryService();
			ComponentCategoryList comCateList = comCateSer.getAll();
			ComponentCategory comCate = new ComponentCategory();
			ComponentService comSer = new ComponentService();
			ComponentList comList = new ComponentList();
			if(comCateList.size()>0){
				comCate = comCateList.get(0);
				comList = comSer.getAll(comCate.getId());
			}
			
			HttpSession session = request.getSession(true);
			session.setAttribute("componentCategoryList", comCateList);
			session.setAttribute("componentCategory", comCate);
			session.setAttribute("componentList", comList);
			session.setAttribute("isTree1", "0");
			if(session!=null)
				request.getRequestDispatcher("componentCategory.jsp").forward(request, response);
		}
		else if(value.equals("SystemManagement")){
			String strFileFolder = getServletContext().getInitParameter("strFileFolder");
			
			
			UserService userSer = new UserService();
			PDMUserList userList = userSer.getUser();
			
			request.setAttribute("userList", userList);
			request.setAttribute("strFileFolder", strFileFolder);
			request.getRequestDispatcher("systemManagementPage.jsp").forward(request, response);
		}
		
	}

}
