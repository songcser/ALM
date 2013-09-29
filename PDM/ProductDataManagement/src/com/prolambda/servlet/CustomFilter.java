package com.prolambda.servlet;

import java.io.IOException;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class CustomFilter implements Filter{

	@Override
	public void destroy() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void doFilter(ServletRequest request, ServletResponse response,
			FilterChain chain) throws IOException, ServletException {
		HttpServletRequest req = (HttpServletRequest) request;
		HttpServletResponse resp = (HttpServletResponse) response;
		String url = req.getRequestURI();
		//System.out.println(url);
		int index = url.lastIndexOf("/");
		//System.out.println();
		String page = url.substring(index+1);
		if("index.jsp".equals(page)||"RandCodeServlet".equals(page)||"LoginServlet".equals(page)||"DownloadServlet".equals(page)||"UploadFileServ".equals(page)||"BuildUploadServlet".equals(page)){
			chain.doFilter(request, response);
		}else{
			HttpSession session = req.getSession();
			//System.out.println(session.getAttribute("user"));
			if(session.getAttribute("user")==null){
				resp.sendRedirect("index.jsp");
				return;
			}else{
				chain.doFilter(request, response);
			}
		}
		
	}

	@Override
	public void init(FilterConfig arg0) throws ServletException {
		// TODO Auto-generated method stub
		
	}

}
