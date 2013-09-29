package com.prolambda.pdm.PDMplugin;

import java.util.ArrayList;
import java.util.List;

public class PDMProject {
	
	
	private String id;
	
	
	private String name;
	
	
	private SourceCode sourceCode = new SourceCode();
	
	private List<Dependence> dependences = new ArrayList<Dependence>(); 
	
	private String configFile;
	
	public PDMProject(){
		super();
	}
	public PDMProject(String id,String name,SourceCode sourceCode,List<Dependence> dependences){
		this.id = id;
		this.name = name;
		this.sourceCode = sourceCode;
		this.dependences = dependences;
	}
	
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public SourceCode getSourceCode() {
		return sourceCode;
	}
	public void setSourceCode(SourceCode sourceCode) {
		this.sourceCode = sourceCode;
	}
	public List<Dependence> getDependences() {
		return dependences;
	}
	public void setDependences(List<Dependence> dependences) {
		this.dependences = dependences;
	}
	public String getConfigFile() {
		return configFile;
	}
	public void setConfigFile(String configFile) {
		this.configFile = configFile;
	}
	public String toString(){
		String str=null;
		
		str = id +" "+name+" "+sourceCode.getUrl()+" "+sourceCode.getVersion()+" "+dependences.size();
		
		return str;
	}
}
