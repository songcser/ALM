package com.prolambda.scmserv.servlet;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.sun.image.codec.jpeg.JPEGCodec;
import com.sun.image.codec.jpeg.JPEGImageEncoder;

public class RandCodeServlet extends HttpServlet
{
	public RandCodeServlet()
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

	protected static Random random = new Random();
	
	protected static Color getBack()
	{
		return new Color(random.nextInt(255), random.nextInt(255), random.nextInt(255));  
	}

	protected static Color getFront(Color c)
	{
		return new Color(255-c.getRed(),255-c.getGreen(),255-c.getBlue());
	}
	
    protected static String getString()
    {  
    	String old="23456789abcdefghijkmnpqrstuvwxyz";
    	StringBuffer sb=new StringBuffer();  
    	int j=0;  

    	for(int i=0;i<4;i++){  
    		j=random.nextInt(old.length());  
    		sb.append(old.substring(j,j+1));  
    	}
    	
    	return sb.toString();      
    }
	
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		doPost(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
	{
		request.setCharacterEncoding("utf-8");
		response.setCharacterEncoding("utf-8");
		response.setContentType("image/jpeg");
		
		int width = 60;
		int height = 25;
		Color back = getBack();
		Color front = getFront(back);
		String code = getString();
		
		if(request.getSession().getAttribute("rand")!=null){
			request.getSession().removeAttribute("rand");
		}
		request.getSession().setAttribute("rand", code);
		
		BufferedImage bi=new BufferedImage(width,height,BufferedImage.TYPE_INT_BGR); 
		
		Graphics2D g=bi.createGraphics();
		g.setFont(new Font("font",Font.BOLD,20));
		g.setColor(back);
		g.fillRect(0, 0, width, height);
		g.setColor(front);
		g.drawString(code,8,20);
		
		for(int i=0,n=random.nextInt(20);i<n;i++){
			g.fillRect(random.nextInt(width),random.nextInt(height),1,1);
		}
		
		ServletOutputStream so=response.getOutputStream();
		JPEGImageEncoder je=JPEGCodec.createJPEGEncoder(so);
		
		je.encode(bi);
		so.flush();
	}
}
