package com.prolambda.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.prolambda.controller.UserService;
import com.prolambda.webmatrix.directory.ActiveDirectory;
import com.prolambda.webmatrix.directory.User;
import com.prolambda.webmatrix.directory.UserList;

public class LoginServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -2790047769141498730L;
	private String host;
	private String domain;
	
	public void init(){
		host = "ldap://192.168.99.10:389";
		domain = "pl.local";
	}
	
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		
		String name = request.getParameter("username");
	   	String password = request.getParameter("password");
	   	String rIdentifyCode = request.getParameter("randcode");
	   	String tIdentifyCode = (String)request.getSession().getAttribute("rand");
	   	HttpSession session = request.getSession();
		//PDMUser user = new PDMUser(name,password);
		//System.out.println("start");
		//out.print("<script language='javascript'>alert('user is not exist');</script>");
		if(!rIdentifyCode.equals(tIdentifyCode)){
			out.print("<script language='javascript'>alert('identify is error');window.location.href='index.jsp';</script>");
			//response.sendRedirect("index.jsp");
	   	} else{
	   		try {
				if(userLogin(name,password,response)){
					//UserService userServ = new UserService();
					//if(userServ.isExist(user.getName())){
					session.setAttribute("user", name);
					response.sendRedirect("home.jsp");
					
				}
				else {
					out.println("<script language='javascript'>alert('user is error');window.location.href='index.jsp';</script>");
					//response.sendRedirect("index.jsp");;
				}
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				
			}finally{
				out.flush();
				out.close();
			}
	   	}
		
		
	}
	
	public Boolean userLogin(String name,String password,HttpServletResponse response) throws Exception{
		ActiveDirectory aDirectory = new ActiveDirectory(host, domain);
		aDirectory.setUsername("pl\\"+name);
		aDirectory.setPassword(password);
		PrintWriter out = response.getWriter();
		if(aDirectory.validate()){
			UserList userList = aDirectory.getUserList("OU=pro-lambda");
			for(User user : userList){
				if(name.equals(user.getUsername())&&user.getPassword().equals(password)){
					UserService userServ = new UserService();
					if(!userServ.isExist(user.getId())){
						out.print("<script language='javascript'>alert('username or password is error');window.location.href='index.jsp';</script>");
						return false;
					}
				}
			}
			
			return true;
		}
		else{
			out.print("<script language='javascript'>alert('username or password is error');window.location.href='index.jsp';</script>");
			return false;
		}
	}

}
