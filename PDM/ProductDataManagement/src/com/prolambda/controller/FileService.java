package com.prolambda.controller;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

public class FileService {
	
	private Document document = null;
	
	public FileService(){
		
	}
	
	public FileService(String xmlPath){
		readXML(xmlPath);
	}

	public void copyFile(File sourceFile, File targetFile) throws IOException {
        BufferedInputStream inBuff = null;
        BufferedOutputStream outBuff = null;
        try {
            // 新建文件输入流并对它进行缓冲
            inBuff = new BufferedInputStream(new FileInputStream(sourceFile));

            // 新建文件输出流并对它进行缓冲
            outBuff = new BufferedOutputStream(new FileOutputStream(targetFile));

            // 缓冲数组
            byte[] b = new byte[1024 * 10];
            int len;
            while ((len = inBuff.read(b)) != -1) {
                outBuff.write(b, 0, len);
            }
            // 刷新此缓冲的输出流
            outBuff.flush();
        } finally {
            // 关闭流
            if (inBuff != null)
                inBuff.close();
            if (outBuff != null)
                outBuff.close();
        }
    }
	
	public void delFolder(String folderPath) {
        try {
        	File myFilePath = new File(folderPath);
        	if(myFilePath.exists()){
        		delAllFile(folderPath); //删除完里面所有内容
              
                myFilePath.delete(); //删除空文件夹
        	}
           
        } catch (Exception e) {
        	e.printStackTrace(); 
        }
    }
    
    public boolean delAllFile(String path) {
        boolean flag = false;
        File file = new File(path);
        if (!file.exists()) {
          return flag;
        }
        if (!file.isDirectory()) {
          return flag;
        }
        String[] tempList = file.list();
        File temp = null;
        for (int i = 0; i < tempList.length; i++) {
           if (path.endsWith(File.separator)) {
              temp = new File(path + tempList[i]);
           } else {
               temp = new File(path + File.separator + tempList[i]);
           }
           if (temp.isFile()) {
              temp.delete();
           }
           if (temp.isDirectory()) {
              delAllFile(path + "/" + tempList[i]);//先删除文件夹里面的文件
              delFolder(path + "/" + tempList[i]);//再删除空文件夹
              flag = true;
           }
        }
        return flag;
      }

    public void zip(ZipOutputStream out,ArrayList<File> input,ArrayList<String> inputName) throws IOException{
    	FileInputStream fis = null;
    	BufferedInputStream bis = null; 
    	
    	for(int i=0;i<input.size();i++){
    		File file = input.get(i);
    		if(!file.exists()){
    			continue;
    		}
    		String name = inputName.get(i);
    		ZipEntry zipEntry = new ZipEntry(name);
    		out.putNextEntry(zipEntry);  
    		fis = new FileInputStream(file);  
            bis = new BufferedInputStream(fis);  
            int read = 0;  
            byte[] bufs = new byte[1024];  
            while((read=bis.read(bufs)) != -1) {  
            	//fileSize += read;
                out.write(bufs, 0, read);
                out.flush();
            }  
    	}
    	
    	if(null != fis){
			fis.close();
		}
		if(null != bis){
			bis.close();
		}
    }

    public Document readXML(String path) {
    	
    	DocumentBuilderFactory builderFactory = DocumentBuilderFactory.newInstance();
    	DocumentBuilder builder;
		try {
			builder = builderFactory.newDocumentBuilder();
			document = builder.parse(new File(path));
		} catch (ParserConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SAXException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	
    	
    	return document;
    }
    
    public String getContextParam(String paramName){
    	//Document document = readXML(xmlPath);
    	
    	NodeList nodes = document.getElementsByTagName("context-param");
    	//System.out.println("param size:"+nodes.getLength());
    	for(int i=0;i<nodes.getLength();i++){
    		Node node = nodes.item(i);
    		NodeList param = node.getChildNodes();
    		Node name = null;
    		for(int j=0;j<param.getLength();j++){
    			Node n = param.item(j);
        		
        		if(n.getNodeType()==Node.ELEMENT_NODE){
        			//Element en = (Element)n;
        			if("param-name".equals(n.getNodeName())){
        				name = n;
        				
        			}else if("param-value".equals(n.getNodeName())){
        				if(paramName.equals(name.getFirstChild().getNodeValue())){
        	    			//System.out.println("equals");
        	    			//n.getFirstChild().setNodeValue(paramValue);
        	    			return n.getFirstChild().getNodeValue();
        	    		}
        			}
        			
        		}
    		}
    		//System.out.println("name:"+name.getFirstChild().getNodeValue());
    		//System.out.println("value:"+value.getFirstChild().getNodeValue());
    	}
    	//doc2Xml(document,xmlPath);
    	return null;
    }
    
    public void setContextParam(String paramName,String paramValue){
    	//Document document = readXML(xmlPath);
    	
    	NodeList nodes = document.getElementsByTagName("context-param");
    	//System.out.println("param size:"+nodes.getLength());
    	for(int i=0;i<nodes.getLength();i++){
    		Node node = nodes.item(i);
    		NodeList param = node.getChildNodes();
    		Node name = null;
    		for(int j=0;j<param.getLength();j++){
    			Node n = param.item(j);
        		
        		if(n.getNodeType()==Node.ELEMENT_NODE){
        			//Element en = (Element)n;
        			if("param-name".equals(n.getNodeName())){
        				name = n;
        				
        			}else if("param-value".equals(n.getNodeName())){
        				if(paramName.equals(name.getFirstChild().getNodeValue())){
        	    			//System.out.println("equals");
        	    			n.getFirstChild().setNodeValue(paramValue);
        	    			
        	    		}
        			}
        			
        		}
    		}
    		//System.out.println("name:"+name.getFirstChild().getNodeValue());
    		//System.out.println("value:"+value.getFirstChild().getNodeValue());
    	}
    	//doc2Xml(xmlPath);
    }
    
    public void doc2Xml(String xmlPath){
    	try {
           
            TransformerFactory tFactory = TransformerFactory.newInstance();
            Transformer transformer = tFactory.newTransformer();
           
            // transformer.setOutputProperty(OutputKeys.ENCODING, "GB2312");
            DOMSource source = new DOMSource(document);
            StreamResult result = new StreamResult(new File(xmlPath));
            transformer.transform(source, result);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        //return flag;
    }
}
