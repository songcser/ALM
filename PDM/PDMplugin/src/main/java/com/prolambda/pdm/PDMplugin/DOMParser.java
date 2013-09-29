package com.prolambda.pdm.PDMplugin;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;



public class DOMParser {
	 private DocumentBuilderFactory builderFactory;
	 private Document document;
	 private String endStr = ".xml";
	 private String configFile;
	
	 public Document getDocument() {
		 return document;
	 }

	 public void setDocument(Document document) {
		 this.document = document;
	 }

	public String getConfigFile() {
		return configFile;
	}

	public void setConfigFile(String configFile) {
		this.configFile = configFile;
	}

	//Load and parse XML file into DOM   
	 public String parse(String filePath) {
		 File file = new File(filePath);
		 File[] fileList = file.listFiles();
		 String config = null;
		 
		 for(File confFile:fileList){
			 if(confFile.getName().endsWith(endStr)){
				 config = confFile.getAbsolutePath();
				 setConfigFile(confFile.getName());
				 break;
			 }
		 }
		 try {   
			 builderFactory = DocumentBuilderFactory.newInstance();
			  //DOM parser instance   
			  DocumentBuilder builder = builderFactory.newDocumentBuilder();   
			  //parse an XML file into a DOM tree   
			  document = builder.parse(new File(config));
			  //setDocument(builder.parse(new File(config)));
		  } catch (ParserConfigurationException e) {   
			  e.printStackTrace();    
		  } catch (SAXException e) {   
			  e.printStackTrace();   
		  } catch (IOException e) {   
			  e.printStackTrace();   
		  }   
		 return config;
	 }
	 
	 public ArrayList<PDMProject> readConfig(){
		 ArrayList<PDMProject> projects = new ArrayList<PDMProject>();
		 
		 //Element rootElement = document.getDocumentElement();
		// NodeList nodes = rootElement.getChildNodes();
		 NodeList projectsnodes = document.getElementsByTagName("projects");
		 if(projectsnodes.getLength()<1){
			 return null;
		 }
		 //return nodes.item(0).getNodeName();
		 Node projectsNode = projectsnodes.item(0);
		 if(projectsNode==null){
			 return null;
		 }
		 NodeList nodes = projectsNode.getChildNodes();
		 for(int i=0;i<nodes.getLength();i++){
			 Node node = nodes.item(i);
			 if(node.getNodeType()==Node.ELEMENT_NODE){
				 Element es = (Element)node;
				 
				 //return es.getNodeName();
				 
				 
				 if(es.getNodeName().equals("project")){
					 PDMProject project = new PDMProject();
					 NodeList projectList = es.getChildNodes();
					 for(int t=0;t<projectList.getLength();t++){
						 Node projectNode = projectList.item(t);
						 if(projectNode.getNodeType()==Node.ELEMENT_NODE){
							 Element e = (Element)projectNode;
							 if(e.getNodeName().equals("id")){
								 project.setId(e.getFirstChild().getNodeValue());
							 }else if(e.getNodeName().equals("name")){
								 project.setName(e.getFirstChild().getNodeValue());
							 }else if(e.getNodeName().equals("sourceCode")){
								 NodeList nodeChildList = e.getChildNodes();
								 SourceCode sourceCode = new SourceCode();
								 for(int j=0;j<nodeChildList.getLength();j++){
									 Node nodeChild = nodeChildList.item(j);
									 if(nodeChild.getNodeType()==Node.ELEMENT_NODE){
										 Element em = (Element)nodeChild;
										 
										 if(em.getNodeName().equals("url")){
											 sourceCode.setUrl(em.getFirstChild().getNodeValue());
										 }else if(em.getNodeName().equals("version")){
											 sourceCode.setVersion(em.getFirstChild().getNodeValue());
										 }
									 }
								 }
								 project.setSourceCode(sourceCode);
							 }else if(e.getNodeName().equals("dependences")){
								 ArrayList<Dependence> deps = new ArrayList<Dependence>();
								 NodeList nodeChildList = e.getChildNodes();
								// project.setDepCount(nodeChildList.getLength());
								 for(int j=0;j<nodeChildList.getLength();j++){
									 
									 Node nodeChild = nodeChildList.item(j);
									 if(nodeChild.getNodeType()==Node.ELEMENT_NODE){
										 Element em = (Element)nodeChild;
										 if(em.getNodeName().equals("dependence")){
											 Dependence dep = new Dependence();
											 NodeList childList = em.getChildNodes();
											 for(int k=0;k<childList.getLength();k++){
												 Node child = childList.item(k);
												 if(child.getNodeType()==Node.ELEMENT_NODE){
													 Element ems = (Element)child;
													 if(ems.getNodeName().equals("name")){
														 dep.setName(ems.getFirstChild().getNodeValue());
													 }else if(ems.getNodeName().equals("version")){
														 dep.setVersion(ems.getFirstChild().getNodeValue());
													 }else if(ems.getNodeName().equals("repository")){
														 dep.setRepository(ems.getFirstChild().getNodeValue());
													 }else if(ems.getNodeName().equals("platform")){
														 dep.setPlatform(ems.getFirstChild().getNodeValue());
													 }else if(ems.getNodeName().equals("configuration")){
														 dep.setConfiguration(ems.getFirstChild().getNodeValue());
													 }else if(ems.getNodeName().equals("location")){
														 dep.setLocation(ems.getFirstChild().getNodeValue());
													 }
												 }
											 }
											 deps.add(dep);
										 }
									 }
									 
								 }
								 project.setDependences(deps);
							 }
						 }
						 
					 }
					 int index = configFile.lastIndexOf('.');
					 String temp = configFile.substring(0, index);
					 project.setConfigFile(temp);
					 projects.add(project);
				 }
				 
			 }
			
		 }
		 
		 return projects;
	 }
	 public String readConfigs(){
		 ArrayList<PDMProject> projects = new ArrayList<PDMProject>();
		 
		 //Element rootElement = document.getDocumentElement();
		// NodeList nodes = rootElement.getChildNodes();
		 NodeList projectsnode = document.getElementsByTagName("projects");
		 //return nodes.item(0).getNodeName();
		 Node projectsNode = projectsnode.item(0);
		 NodeList nodes = projectsNode.getChildNodes();
		 for(int i=0;i<nodes.getLength();i++){
			 Node node = nodes.item(i);
			 if(node.getNodeType()==Node.ELEMENT_NODE){
				 Element es = (Element)node;
				 
				 //return es.getNodeName();
				 
				 PDMProject project = new PDMProject();
				 if(es.getNodeName().equals("project")){
					 NodeList projectList = es.getChildNodes();
					 for(int t=0;t<projectList.getLength();t++){
						 Node projectNode = projectList.item(t);
						 if(projectNode.getNodeType()==Node.ELEMENT_NODE){
							 Element e = (Element)projectNode;
							 return e.getNodeValue();
							 /*
							 if(e.getNodeName().equals("id")){
								 project.setId(e.getNodeValue());
							 }else if(e.getNodeName().equals("name")){
								 project.setName(e.getNodeValue());
							 }else if(e.getNodeName().equals("sourceCode")){
								 NodeList nodeChildList = e.getChildNodes();
								 SourceCode sourceCode = new SourceCode();
								 for(int j=0;j<nodeChildList.getLength();j++){
									 Node nodeChild = nodeChildList.item(j);
									 if(nodeChild.getNodeType()==Node.ELEMENT_NODE){
										 Element em = (Element)nodeChild;
										 
										 if(em.getNodeName().equals("URL")){
											 sourceCode.setUrl(em.getNodeValue());
										 }else if(em.getNodeName().equals("version")){
											 sourceCode.setVersion(em.getNodeValue());
										 }
									 }
								 }
								 project.setSourceCode(sourceCode);
							 }else if(e.getNodeName().equals("dependences")){
								 ArrayList<Dependence> deps = new ArrayList<Dependence>();
								 NodeList nodeChildList = e.getChildNodes();
								// project.setDepCount(nodeChildList.getLength());
								 for(int j=0;j<nodeChildList.getLength();j++){
									 Dependence dep = new Dependence();
									 Node nodeChild = nodeChildList.item(j);
									 if(nodeChild.getNodeType()==Node.ELEMENT_NODE){
										 Element em = (Element)nodeChild;
										 if(em.getNodeName().equals("dependence")){
											 NodeList childList = em.getChildNodes();
											 for(int k=0;k<childList.getLength();k++){
												 Node child = childList.item(k);
												 if(child.getNodeType()==Node.ELEMENT_NODE){
													 Element ems = (Element)child;
													 if(ems.getNodeName().equals("name")){
														 dep.setName(ems.getNodeValue());
													 }else if(ems.getNodeName().equals("version")){
														 dep.setVersion(ems.getNodeValue());
													 }else if(ems.getNodeName().equals("repository")){
														 dep.setRepository(ems.getNodeValue());
													 }else if(ems.getNodeName().equals("platform")){
														 dep.setPlatform(ems.getNodeValue());
													 }else if(ems.getNodeName().equals("configuration")){
														 dep.setConfiguration(ems.getNodeValue());
													 }else if(ems.getNodeName().equals("location")){
														 dep.setLocation(ems.getNodeValue());
													 }
												 }
											 }
										 }
									 }
									 deps.add(dep);
								 }
								 project.setDependences(deps);
							 }
							 */
						 }
						 
					 }
					 
				 }
				 
				 int index = configFile.lastIndexOf('.');
				 String temp = configFile.substring(0, index);
				 project.setConfigFile(temp);
				 projects.add(project);
				 
			 }
			
		 }
		 
		 return "";
	 }
}
