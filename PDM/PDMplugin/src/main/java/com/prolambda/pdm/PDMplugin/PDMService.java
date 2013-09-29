package com.prolambda.pdm.PDMplugin;

import java.io.File;
import java.io.RandomAccessFile;
import java.util.ArrayList;

import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.NameValuePair;
import org.apache.commons.httpclient.methods.MultipartPostMethod;
import org.apache.commons.httpclient.methods.PostMethod;
import org.apache.commons.httpclient.methods.multipart.FilePart;

@SuppressWarnings("deprecation")
public class PDMService
{
	public String uploadFiles(BuildMessage message,String workPath, String strUrl,File log)
	{
		
		strUrl += "/UploadFileServ";
		String strResponse = null;
		//File files = new File(filePath);
		HttpClient httpClient = new HttpClient();
		MultipartPostMethod multipartPostMethod = new MultipartPostMethod(strUrl);
		
		//String filename = files.getName();
		//String filepath = files.getPath();
		ArrayList<String> filePaths = message.getWorkPath();
		ArrayList<String> targetPaths = message.getTargetPath();
		
		try {
			for(int i=0;i<filePaths.size();i++){
				
				String path = workPath+"/"+filePaths.get(i);

				File files = new File(path);
				
				String filename = files.getName();
				String targetPath = targetPaths.get(i).replace('\\', '/');
				
				if(files.isDirectory()){
					File[] fileList = files.listFiles();
					for(int k=0;k<fileList.length;k++){
						multipartPostMethod.addParameter(fileList[k].getName(), targetPath+'/'+fileList[k].getName(), fileList[k]);
					}
					/*
					for(int j=0;j<fileList.length;j++){
						multipartPostMethod.addPart(new FilePart("file"+j+i,fileList[j]));
					}*/
				}else if(filename.indexOf('*')!=-1)
				{
					
					String filepath = files.getPath();
					
					int index = filepath.lastIndexOf('\\');
					String dirStr = filepath.substring(0,index);
					index = filename.indexOf('*');
					String endStr = filename.substring(index+1);
					File dir = new File(dirStr);
					
					
					try {
						if(dir.exists()){
							File[] fileList = dir.listFiles();
							for (int j = 0; j < fileList.length; j++) {
								if(fileList[j].getName().endsWith(endStr))
								{
									multipartPostMethod.addParameter(fileList[j].getName(), targetPath+'/'+fileList[j].getName(), fileList[j]);
								}
							}
							/*
							for (int j = 0; j < fileList.length; j++) {
								if(fileList[j].getName().endsWith(endStr))
								{
									multipartPostMethod.addPart(new FilePart("file"+j+i,fileList[j]));
								}
							}*/
						}
					}catch (Exception e){
						e.printStackTrace();
					}
				}else if(files.exists()){
					multipartPostMethod.addParameter(files.getName(), targetPath+'/'+files.getName(), files);
					//multipartPostMethod.addPart(new FilePart("file"+i,files));
				}
			}
			multipartPostMethod.addPart(new FilePart("log",log));
			int statusCode = httpClient.executeMethod(multipartPostMethod);
			if (statusCode == 200) {
				strResponse = multipartPostMethod.getResponseBodyAsString();
			}
		}catch (Exception e){
			e.printStackTrace();
		}
		finally
		{
			multipartPostMethod.releaseConnection();
		}
	
		
		
		return strResponse;
		
	}
	
	public String uploadFiless(String filePath, String strUrl ,File log) throws Exception
	{
		/*
		strUrl += "/UploadFileServ";
		File files = new File(filePath);
		File[] fileList = files.listFiles();
		
		HttpClient httpclient = new DefaultHttpClient();  
        //请求处理页面  
        HttpPost httppost = new HttpPost(strUrl);  
        //创建待处理的文件  
        //FileBody file = new FileBody(new File("d:/22.rar"));  
        //创建待处理的表单域内容文本  
        //StringBody repName = new StringBody(message.getRepName());
        //StringBody artName = new StringBody(message.getArtName());
  
        //对请求的表单域进行填充  
        MultipartEntity reqEntity = new MultipartEntity();
        
        try{
        	for(int i=0;i<fileList.length;i++)
        	{
        		FileBody file = new FileBody(fileList[i]);
        		reqEntity.addPart(fileList[i].getName(), file);
        	}
        	FileBody filelog = new FileBody(log);
        	reqEntity.addPart("log",filelog);
        }catch(Exception e)
        {
        	e.printStackTrace();
        }
        //reqEntity.addPart("file", file);  
        //reqEntity.addPart("RepositoryName",repName);
        //reqEntity.addPart("ArtifactName",artName);
        //设置请求  
        httppost.setEntity(reqEntity);  
        //执行  
        HttpResponse response = httpclient.execute(httppost);  
        //HttpEntity resEntity = response.getEntity();  
        //System.out.println(response.getStatusLine());  
        if(HttpStatus.SC_OK==response.getStatusLine().getStatusCode()){  
            HttpEntity entity = response.getEntity();  
            //显示内容  
            if (entity != null) {  
                System.out.println(EntityUtils.toString(entity));  
            }  
            if (entity != null) {  
                entity.consumeContent();  
            }  
        }  
        */
		return null;
	}
	
	public String postMessage(BuildMessage message,ArrayList<PDMProject> projects,String strUrl) throws Exception
	{
		
		strUrl += "/ReceivServ";
		HttpClient httpClient = new HttpClient();
		String responseBody="";
		PostMethod postMethod = new PostMethod(strUrl.trim());
		
		PDMProject project = projects.get(0);
		//String path = "";
		//for(int i=0;i<message.getTargetPath().size();i++){
		//	path += message.getTargetPath().get(i) + " ";
		//}
		try {
			/*
			NameValuePair[] nameValuePairs ={
					new NameValuePair("RepositoryName",message.getRepName()),
					new NameValuePair("ArtifactName",message.getArtName()),
					new NameValuePair("Number",message.getNumber()),
					new NameValuePair("BuildTime",message.getBuildTime()),
					new NameValuePair("Duration",message.getDuration()),
					new NameValuePair("Result",message.getResult()),
					new NameValuePair("SourcePath",message.getSourcePath()),
					new NameValuePair("SourceVersion",message.getSourceVersion()),
					new NameValuePair("TargetPath",path),
					new NameValuePair("Environment",message.getEnvironment())};
					*/
			ArrayList<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>();
			nameValuePairs.add(new NameValuePair("RepositoryName",project.getConfigFile()));
			nameValuePairs.add(new NameValuePair("ArtifactName",project.getName()));
			nameValuePairs.add(new NameValuePair("Number",message.getNumber()));
			nameValuePairs.add(new NameValuePair("BuildTime",message.getBuildTime()));
			nameValuePairs.add(new NameValuePair("Duration",message.getDuration()));
			nameValuePairs.add(new NameValuePair("Result",message.getResult()));
			nameValuePairs.add(new NameValuePair("SourcePath",project.getSourceCode().getUrl()));
			nameValuePairs.add(new NameValuePair("SourceVersion",project.getSourceCode().getVersion()));
			nameValuePairs.add(new NameValuePair("DepCount",project.getDependences().size()+""));
			for(int i=0;i<project.getDependences().size();i++){
				Dependence dep = project.getDependences().get(i);
				nameValuePairs.add(new NameValuePair("DepName_"+i,dep.getName()));
				nameValuePairs.add(new NameValuePair("DepVersion_"+i,dep.getVersion()));
				nameValuePairs.add(new NameValuePair("DepRepository_"+i,dep.getRepository()));
				nameValuePairs.add(new NameValuePair("DepPlatform_"+i,dep.getPlatform()));
				nameValuePairs.add(new NameValuePair("DepConfiguration_"+i,dep.getConfiguration()));
				nameValuePairs.add(new NameValuePair("DepLocation_"+i,dep.getLocation()));
			}
			//NameValuePair[] array = (NameValuePair[])nameValuePairs.toArray(new )
			postMethod.setRequestBody((NameValuePair[])nameValuePairs.toArray(new NameValuePair[0]));
			httpClient.getParams().setContentCharset("UTF-8");
			int status = httpClient.executeMethod(postMethod);
			if (status == 200) {
				responseBody =postMethod.getResponseBodyAsString();
			}
			return responseBody;
		} catch (Exception e) {
			throw e;
		}
		finally
		{
			postMethod.releaseConnection();
		}
	}
	
	public void changeLog(BuildMessage message,ArrayList<PDMProject> projects, File log)
	{
		PDMProject project = projects.get(0);
		String repName = project.getConfigFile();
		String artName = project.getName();
		//String repName = message.getRepName();
		//String artName = message.getArtName();
		String number = message.getNumber();
		String content = repName+"_"+artName+"_"+number;
		try{
			RandomAccessFile randomFile = new RandomAccessFile(log,"rw");
			long length = randomFile.length();
			randomFile.seek(length);
			randomFile.writeBytes(content);
		}catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}
