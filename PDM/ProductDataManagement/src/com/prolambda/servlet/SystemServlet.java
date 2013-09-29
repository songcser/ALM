package com.prolambda.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Calendar;
import java.util.Date;
import java.util.Timer;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.prolambda.controller.BackupService;
import com.prolambda.controller.UserService;
import com.prolambda.model.PDMUser;
import com.prolambda.model.PDMUserList;
import com.prolambda.webmatrix.directory.ActiveDirectory;
import com.prolambda.webmatrix.directory.UserList;

public class SystemServlet extends HttpServlet {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 2093894294242104192L;
	

	private String host;
	private String domain;
	Timer backupTimer = null;
	public void init(){
		host = "ldap://192.168.99.10:389";
		domain = "pl.local";
	}

	@Override
	public void destroy() {
		// TODO Auto-generated method stub
		if(backupTimer!=null)
			backupTimer.cancel();
		super.destroy();
		
	}
	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
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
		//PrintWriter out = response.getWriter();
		System.out.println("SystemServlet");
		String flag = request.getParameter("flag");
		if(flag.equals("addUser")){
			addUser(request,response);
		}else if(flag.equals("backup")){
			System.out.println("backup");
			backup(request,response);
		}
		
		//out.flush();
		//out.close();
	}
	public void backup(HttpServletRequest request,HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String isBackup = request.getParameter("isbackup");
		if("false".equals(isBackup)){
			//String xmlPath = this.getServletConfig().getServletContext().getRealPath("/")+"WEB-INF/backup.xml";
			//FileService fileSer = new FileService(xmlPath);
			
			//fileSer.setContextParam("isBackup", "false");
			if(backupTimer!=null){
				backupTimer.cancel();
			}
			out.print("<script>window.close();</script>");
			out.flush();
			out.close();
			
		}else if("true".equals(isBackup)){
			String backupPath = request.getParameter("backupPath");
			//String[] backupType = request.getParameterValues("backupType");
			String frequency = request.getParameter("frequency");
			String week = request.getParameter("week");
			String day = request.getParameter("day");
			String hour = request.getParameter("hour");
			String minute = request.getParameter("minute");
			
			//System.out.println("xml:"+backupType.length);
			String type = "File|Database";
			/*
			for(int i=0;i<backupType.length;i++){
				//System.out.println(backupType[i]);
				if(i==backupType.length-1){
					type += backupType[i];
				}else {
					type += backupType[i]+"|";
				}
			}
			/*
			String xmlPath = this.getServletConfig().getServletContext().getRealPath("/")+"WEB-INF/backup.xml";
			FileService fileSer = new FileService(xmlPath);
			
			fileSer.setContextParam("isBackup", "true");
			fileSer.setContextParam("path",backupPath);
			fileSer.setContextParam("type",type);
			fileSer.setContextParam("frequency", frequency);
			fileSer.setContextParam("week", week);
			fileSer.setContextParam("month", month);
			fileSer.setContextParam("hour", hour);
			fileSer.setContextParam("minute", minute);
			
			fileSer.doc2Xml(xmlPath);
			
			*/
			//xmlPath = event.getServletContext().getRealPath("/")+"WEB-INF/backup.xml";
			//FileService fileSer = new FileService(xmlPath);
			//isBackup = fileSer.getContextParam("isBackup");
			if("true".equals(isBackup)){
				System.out.println("Start Backup--->");
				backupTimer = new Timer(true);
				//String path = fileSer.getContextParam("path");
				//type = fileSer.getContextParam("type");
				//String fre = fileSer.getContextParam("frequency");
				//hour = fileSer.getContextParam("hour");
				//minute = fileSer.getContextParam("minute");
				Calendar calendar = Calendar.getInstance(); 
				calendar.set(Calendar.HOUR_OF_DAY, Integer.parseInt(hour));  
				calendar.set(Calendar.MINUTE, Integer.parseInt(minute));  
				calendar.set(Calendar.SECOND, 0);  
				if("day".equals(frequency)){
					System.out.println("day");
					Date date = calendar.getTime();
					System.out.println("Date:"+date);
					backupTimer.schedule(new BackupService(getServletContext(),backupPath,type),date,1000*60*60*24);
				}else if("week".equals(frequency)){
					System.out.println("week:"+week);
					//week= fileSer.getContextParam("week");
					
					if("Monday".equals(week)){
						calendar.set(Calendar.DAY_OF_WEEK,2 );
					}else if("Tuesday".equals(week)){
						calendar.set(Calendar.DAY_OF_WEEK,3 );
					}else if("Wednesday".equals(week)){
						calendar.set(Calendar.DAY_OF_WEEK,4 );
					}else if("Thursday".equals(week)){
						calendar.set(Calendar.DAY_OF_WEEK,5 );
					}else if("Friday".equals(week)){
						calendar.set(Calendar.DAY_OF_WEEK,6 );
					}else if("Saturday".equals(week)){
						calendar.set(Calendar.DAY_OF_WEEK,0 );
					}else if("Sunday".equals(week)){
						calendar.set(Calendar.DAY_OF_WEEK,1 );
					}
					Date date = calendar.getTime();
					System.out.println("Date:"+date);
					backupTimer.schedule(new BackupService(getServletContext(),backupPath,type),date,1000*60*60*24*7);
				}else if("month".equals(frequency)){
					System.out.println("month");
					//String day = fileSer.getContextParam("day");
					calendar.set(Calendar.DAY_OF_MONTH, Integer.parseInt(day));
					Date date = calendar.getTime();
					System.out.println("Date:"+date);
					backupTimer.schedule(new BackupService(getServletContext(),backupPath,type),date,1000*60*60*24*7*30);
				}
			}
			
			//out.print("<script>window.close();</script>");
			out.print("<script>parent.cancle()</script>");
			out.flush();
			out.close();
		}
		
	}
	
	public void addUser(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		
		try {
			ActiveDirectory aDirectory = new ActiveDirectory(host, domain);
			aDirectory.setUsername("pl\\test");
			aDirectory.setPassword("pro!ambDa");
			
			if(!aDirectory.validate()){
				return;
			}
			UserList userList = aDirectory.getUserList("OU=pro-lambda");
			
			for(int i=1;i<userList.size()+1;i++){
				String id = request.getParameter("id"+i);
				if(id==null){
					continue;
				}
				if(!id.equals("noselect")){
					PDMUser user = new PDMUser();
					user.setUserId(id);
					String name = userList.get(i-1).getUsername();
					String password = userList.get(i-1).getPassword();
					System.out.println("password:"+password);
					int index = name.indexOf('@');
					name = name.substring(0, index);
					user.setName(name);
					
					UserService userSer = new UserService();
					userSer.addUser(user);
				}
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		/*
		String length = request.getParameter("length");
		for(int i=1;i<Integer.parseInt(length)+1;i++){
			String id = request.getParameter("id"+i);
			if(id!=null){
				PDMUser user = new PDMUser();
				user.setUserId(id);
				user.setName("song");
				UserService userSer = new UserService();
				userSer.addUser(user);
			}
		}*/
		String strFileFolder = null;
		//ServletConfig config = getServletConfig();
		//strFileFolder = config.getInitParameter("strFileFolder");
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		//System.out.println("strFileFolder:"+strFileFolder);
		
		UserService userSer = new UserService();
		PDMUserList userList = userSer.getUser();
		
		request.setAttribute("userList", userList);
		request.setAttribute("strFileFolder", strFileFolder);
		request.getRequestDispatcher("systemManagementPage.jsp").forward(request, response);
		
	}

}
