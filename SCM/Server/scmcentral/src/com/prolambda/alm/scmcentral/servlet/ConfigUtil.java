package com.prolambda.alm.scmcentral.servlet;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;

public class ConfigUtil{
		
	public static String getConfigPath(ServletContext application, HttpServletRequest request)
	{
		String configPath = application.getInitParameter("scm_db");
		String configRealPath = request.getSession().getServletContext().getRealPath(configPath);
		
		return configRealPath;
	}
	
	public static String getTempPath(ServletContext application, HttpServletRequest request)
	{
		String configPath = application.getInitParameter("scm_temp");
		String configRealPath = request.getSession().getServletContext().getRealPath(configPath);
		
		return configRealPath;
	}
	
}
