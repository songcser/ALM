package com.prolambda.pdm.PDMplugin;

import hudson.model.AbstractBuild;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;

public class BuildMessage
{
	//private String repName;
	//private String artName;
	private String number;
	private String buildTime;
	private String duration;
	//private String state;
	//private String sourcePath;
	//private String sourceVersion;
	private String environment;
	private String result;
	private String log;
	private ArrayList<String> workPath;
	private ArrayList<String> targetPath;
	
	public BuildMessage(){
		workPath = new ArrayList<String>();
		targetPath = new ArrayList<String>();
	}
	
	public String getNumber()
	{
		return number;
	}
	public void setNumber(String number)
	{
		this.number = number;
	}
	public String getBuildTime()
	{
		return buildTime;
	}
	public void setBuildTime(String buildTime)
	{
		this.buildTime = buildTime;
	}
	public String getDuration()
	{
		return duration;
	}
	public void setDuration(String duration)
	{
		this.duration = duration;
	}

	public String getEnvironment()
	{
		return environment;
	}
	public void setEnvironment(String environment)
	{
		this.environment = environment;
	}
	public void setResult(String result)
	{
		this.result = result;
	}
	public String getResult()
	{
		return result;
	}
	
	public void setLog(String log)
	{
		this.log = log;
	}
	public String getLog()
	{
		return log;
	}
	
	public ArrayList<String> getWorkPath() {
		return workPath;
	}
	public void setWorkPath(ArrayList<String> workPath) {
		this.workPath = workPath;
	}
	
	public ArrayList<String> getTargetPath() {
		return targetPath;
	}
	public void setTargetPath(ArrayList<String> targetPath) {
		this.targetPath = targetPath;
	}
	
	public void getPath(String path){
		String item[] = path.split("\\n");
		
		for(int i=0;i<item.length;i++){
			String str[] = item[i].split(" ");
			if(str.length==2){
				workPath.add(str[0]);
				targetPath.add(str[1]);
			}
		}
		
	}
	
	public void readConfig(String path){
		
	}
	
	@SuppressWarnings("rawtypes")
	public void getMessage(AbstractBuild build)
	{
		
		Calendar startedTime = build.getTimestamp();
		SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd' 'HH:mm:ss");
		this.buildTime = simpleDateFormat.format(startedTime.getTime());
		//this.duration = (System.currentTimeMillis() - startedTime.getTimeInMillis())+"";
		this.duration = build.getDuration()+"";
		int num = build.getNumber();
		this.number = num+"";
		
		BuildResult buildResult = BuildResult.fromBuild(build);
		if(buildResult!=null){
			this.result = buildResult.name();
		}
		
		this.environment = System.getProperty("os.name")+" "+System.getProperty("os.version");
		//this.environment = "VS 2010";
		File logfile = build.getLogFile();
		this.log = logfile.getAbsolutePath();
		
	}
	
	
	public String sendMessage()
	{
		String fileName = "E:\\workspace\\PDMplugin\\BuildLog" + number + ".txt";
		String content;
		
		content = "number: "+number+"\n"
			+"buildTime: "+buildTime+"\n"
			+"duration: "+duration+"\n"
			+"environment: "+environment+"\n"
			+"result: "+result+"\n"
			+"log: "+log+"\n";
		
		try
		{
			FileWriter writer = new FileWriter(fileName,true);
			writer.write(content);
			writer.close();
		}catch(IOException e)
		{
			e.printStackTrace();
		}
		
		return content;
	}
	
}
