package com.prolambda.servlet;

import java.util.Timer;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;

public class BuilderContextListener implements ServletContextListener{

	private Timer buildTimer = null;
	private Timer backupTimer = null;
	@Override
	public void contextDestroyed(ServletContextEvent event) {
		// TODO Auto-generated method stub
		if(buildTimer!=null){
			buildTimer.cancel();
		}
		
		if(backupTimer!=null){
			backupTimer.cancel();
		}
		
	    event.getServletContext().log("定时器销毁");
	
		
	}

	@Override
	public void contextInitialized(ServletContextEvent event) {
		// TODO Auto-generated method stub
		buildTimer = new Timer(true);
		event.getServletContext().log("定时器已启动");//添加日志，可在tomcat日志中查看到
		buildTimer.schedule(new BuilderTask(event.getServletContext()),0,100*1000);
		
		/*
		String xmlPath = event.getServletContext().getRealPath("/")+"WEB-INF/backup.xml";
		FileService fileSer = new FileService(xmlPath);
		String isBackup = fileSer.getContextParam("isBackup");
		if("true".equals(isBackup)){
			System.out.println("Start Backup--->");
			backupTimer = new Timer(true);
			String path = fileSer.getContextParam("path");
			String type = fileSer.getContextParam("type");
			String fre = fileSer.getContextParam("frequency");
			String hour = fileSer.getContextParam("hour");
			String minute = fileSer.getContextParam("minute");
			Calendar calendar = Calendar.getInstance(); 
			calendar.set(Calendar.HOUR_OF_DAY, Integer.parseInt(hour));  
			calendar.set(Calendar.MINUTE, Integer.parseInt(minute));  
			calendar.set(Calendar.SECOND, 0);  
			if("day".equals(fre)){
				 
				Date date = calendar.getTime();
				backupTimer.schedule(new BackupService(event.getServletContext(),path,type),date,1000*60*60*24);
			}else if("week".equals(fre)){
				String week= fileSer.getContextParam("week");
				
				if("Monday".equals(week)){
					calendar.set(Calendar.DAY_OF_WEEK,1 );
				}else if("Tuesday".equals(week)){
					calendar.set(Calendar.DAY_OF_WEEK,2 );
				}else if("Wednesday".equals(week)){
					calendar.set(Calendar.DAY_OF_WEEK,3 );
				}else if("Thursday".equals(week)){
					calendar.set(Calendar.DAY_OF_WEEK,4 );
				}else if("Friday".equals(week)){
					calendar.set(Calendar.DAY_OF_WEEK,5 );
				}else if("Saturday".equals(week)){
					calendar.set(Calendar.DAY_OF_WEEK,6 );
				}else if("Sunday".equals(week)){
					calendar.set(Calendar.DAY_OF_WEEK,0 );
				}
				Date date = calendar.getTime();
				backupTimer.schedule(new BackupService(event.getServletContext(),path,type),date,1000*60*60*24*7);
			}else if("month".equals(fre)){
				String day = fileSer.getContextParam("day");
				calendar.set(Calendar.DAY_OF_MONTH, Integer.parseInt(day));
				Date date = calendar.getTime();
				backupTimer.schedule(new BackupService(event.getServletContext(),path,type),date,1000*60*60*24*7*30);
			}
		}
		*/
		//backupTimer.schedule(new BackupService(event.getServletContext()),date,1000*60*60*24);
		event.getServletContext().log("已经添加任务");
		 
	}

}
