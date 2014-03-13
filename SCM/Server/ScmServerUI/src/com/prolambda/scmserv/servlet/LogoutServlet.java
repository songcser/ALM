package com.prolambda.scmserv.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class LogoutServlet extends HttpServlet
{
	public LogoutServlet()
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
		request.getSession().invalidate();
		response.sendRedirect("LoginServlet");
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		request.getSession().invalidate();
		response.sendRedirect("LoginServlet");
	}
}
