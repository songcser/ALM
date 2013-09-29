package com.prolambda.alm.scmcentral.bll;

import java.io.*;
import java.util.*;
import com.prolambda.alm.scmcentral.entity.*;
import com.prolambda.alm.scmcentral.dal.*;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class ReposMan 
{
	List<Repository> reposes;
	
	List<String> noteList;
	List<String> noteIdList;
	List<String> fathIdList;
	List<String> dirFlagList;
	
	public List<String> getNoteList()
	{
		return noteList;
	}

	public void setNoteList(List<String> noteList)
	{
		this.noteList = noteList;
	}

	public List<String> getNoteIdList()
	{
		return noteIdList;
	}

	public void setNoteIdList(List<String> noteIdList)
	{
		this.noteIdList = noteIdList;
	}

	public List<String> getFathIdList()
	{
		return fathIdList;
	}

	public void setFathIdList(List<String> fathIdList)
	{
		this.fathIdList = fathIdList;
	}

	public List<String> getDirFlagList()
	{
		return dirFlagList;
	}

	public void setDirFlagList(List<String> dirFlagList)
	{
		this.dirFlagList = dirFlagList;
	}

	public ReposMan()
	{
		reposes = new ArrayList<Repository>();
	}
	
	public ReposMan(List<Repository> reposes)
	{
		this.reposes = reposes;
	}
	
	public List<Repository> getReposes() 
	{
		return reposes;
	}

	public void setReposes(List<Repository> reposes) 
	{
		this.reposes = reposes;
	}
	
	public List<String> createRepos(Repository repos, ScmUser lastLogin, String realPath)
	{
		String svnRoot = repos.getSvnRoot();
		String destPath = svnRoot + "\\" + repos.getName();
		SvnCmd createCmd = new SvnCmd(destPath, "");
		List<String> retList = createCmd.svnAdminCreate();
		
		File tkDir = new File(realPath + "\\Temp\\trunk");
		File bhDir = new File(realPath + "\\Temp\\branches");
		File tgDir = new File(realPath + "\\Temp\\tags");
		
		tkDir.mkdirs();
		bhDir.mkdirs();
		tgDir.mkdirs();
		
		String arguments = "--username " + lastLogin.getName() + " --password " + lastLogin.getPassword();
		String message = "initial repository";
		String destURL = repos.getServerURL() + "/" + repos.getName();
		SvnCmd importCmd = new SvnCmd(realPath + "\\Temp", destURL, message, arguments);
		List<String> tempList = importCmd.svnImport();
		retList.addAll(tempList);
		
		delFolder(realPath + "\\Temp");
		
		String owner = repos.getOwner();
		String fileName = svnRoot + "\\authz";
		String section = repos.getName() + ":/";
		IniFileOpe iniFileOpe = new IniFileOpe(fileName, section, owner, "rw");
		List<String> tpList = iniFileOpe.findBySection();
		for(int k = 0; k < tpList.size(); k++){
			String[] tpBuffer = tpList.get(k).split("::=");
			if(tpBuffer.length >= 1){
				IniFileOpe tIni = new IniFileOpe(fileName, section, tpBuffer[0]);
				tIni.deleteKeyValue();
			}
		}
		iniFileOpe.writeKeyValue();
		
		return retList;
	}
	
	public boolean deleteRepos(Repository repos)
	{
		String destPath = repos.getSvnRoot() + "\\" + repos.getName();
		delFolder(destPath);
		
		return true;
	}
	
	public List<String> branchTag(Repository repos, String sourcePath, String destPath, String message, int Flag, ScmUser lastLogin)
	{
		List<String> retList;
		String arguments = "--username " + lastLogin.getName() + " --password " + lastLogin.getPassword();
		int specialFlag = 0;
		
		if(0 == Flag){
			if(-1 == sourcePath.indexOf("trunk")){
				retList = new ArrayList<String>();
				retList.add("sourcePath is illegal");
				return retList;
			}
			
			if(-1 == destPath.indexOf("branches")){
				retList = new ArrayList<String>();
				retList.add("destPath is illegal");
				return retList;
			}
			
			if(destPath.length()-8 == destPath.indexOf("branches")){
				retList = new ArrayList<String>();
				retList.add("destPath is illegal");
				return retList;
			}
			
			if(destPath.length()-9 == destPath.indexOf("branches")){
				retList = new ArrayList<String>();
				retList.add("destPath is illegal");
				return retList;
			}
			
			int index = sourcePath.indexOf("trunk");
			if(sourcePath.length()-5 == index || sourcePath.length()-6 == index){
				SvnCmd infoCmd = new SvnCmd(destPath, arguments);
				retList = infoCmd.svnInfo();
				if(retList.size() > 0){
					if(0 != retList.get(0).indexOf("svn: ")){
						retList = new ArrayList<String>();
						retList.add("dest path is existing");
						return retList;
					}
				}
			}
			else{
				SvnCmd infoCmd = new SvnCmd(destPath, arguments);
				retList = infoCmd.svnInfo();
				if(retList.size() > 0){
					if(0 != retList.get(0).indexOf("svn: ")){
						retList = new ArrayList<String>();
						retList.add("dest path is existing");
						return retList;
					}
				}
				
				String tDestPath = destPath;
				int pos  = tDestPath.lastIndexOf('/');
				if(pos == tDestPath.length()-1){
					tDestPath = tDestPath.substring(0, pos);
					pos = tDestPath.lastIndexOf('/');
				}
				tDestPath = tDestPath.substring(0, pos);
				
				infoCmd.setArguments(arguments);
				infoCmd.setDestPath(tDestPath);
				retList = infoCmd.svnInfo();
				if(retList.size() > 0){
					if(0 == retList.get(0).indexOf("svn: ")){
						SvnCmd mkdirCmd = new SvnCmd(tDestPath, arguments);
						mkdirCmd.setMessage(" ");
						mkdirCmd.svnMkdir();
					}
				}
				else{
					SvnCmd mkdirCmd = new SvnCmd(tDestPath, arguments);
					mkdirCmd.setMessage("");
					mkdirCmd.svnMkdir();
				}
				
				specialFlag = 1;
			}
		}
		
		if(1 == Flag){
			if(-1 == sourcePath.indexOf("branches")){
				retList = new ArrayList<String>();
				retList.add("sourcePath is illegal");
				return retList;
			}
			
			if(-1 == destPath.indexOf("tags")){
				retList = new ArrayList<String>();
				retList.add("destPath is illegal");
				return retList;
			}
			
			if(destPath.length()-4 == destPath.indexOf("tags")){
				retList = new ArrayList<String>();
				retList.add("destPath is illegal");
				return retList;
			}
			
			if(destPath.length()-5 == destPath.indexOf("tags")){
				retList = new ArrayList<String>();
				retList.add("destPath is illegal");
				return retList;
			}
			
			SvnCmd infoCmd = new SvnCmd(destPath, arguments);
			retList = infoCmd.svnInfo();
			if(retList.size() > 0){
				if(0 != retList.get(0).indexOf("svn: ")){
					retList = new ArrayList<String>();
					retList.add("dest path is existing");
					return retList;
				}
			}
		}
		
		SvnCmd copyCmd = new SvnCmd(sourcePath, destPath, message, arguments);
		retList = copyCmd.svnCopy();

		String fileName = repos.getSvnRoot()+ "\\authz";
		String tSection = repos.getName() + ":/";
		IniFileOpe tIni = new IniFileOpe();
		tIni.setFileName(fileName);
		tIni.setSection(tSection);
		List<String> tempList = tIni.findBySection();
		String owner = null;
		if(tempList.size() >= 1){
			String[] tpBuffer = tempList.get(0).split("::=");
			if(tpBuffer.length >= 1){
				owner = tpBuffer[0];
			}
		}
		
		IniFileOpe iniFileOpe = new IniFileOpe();
		iniFileOpe.setFileName(repos.getSvnRoot() + "\\authz");
		
		if(1 == specialFlag){
			String[] tpBuffer = destPath.split("/");
			if(tpBuffer.length >=2 ){
				iniFileOpe.setSection(repos.getName() + ":/branches/" + tpBuffer[tpBuffer.length-2] + "/" + tpBuffer[tpBuffer.length-1]);
				iniFileOpe.setKey("@build");
				iniFileOpe.setValue("r");
				iniFileOpe.writeKeyValue();
				iniFileOpe.setKey("@admin");
				iniFileOpe.setValue("rw");
				iniFileOpe.writeKeyValue();
				
				if(owner != null){
					iniFileOpe.setKey(owner);
					iniFileOpe.setValue("rw");
					iniFileOpe.writeKeyValue();
				}
				
				iniFileOpe.setKey("*");
				iniFileOpe.setValue(" ");
				iniFileOpe.writeKeyValue();
			}
			
			return retList;
		}
		
		SvnCmd listCmd = new SvnCmd(sourcePath, arguments);
		List<String> tpList = new ArrayList<String>();
		List<String> ttpList = listCmd.svnList();
		String[] tpBuffer = destPath.split("/");
		
		for(int k = 0; k < ttpList.size(); k++){
			String tpStr = ttpList.get(k);
			if(tpStr.lastIndexOf('/') == tpStr.length()-1){
				tpStr = tpStr.substring(0, tpStr.length()-1);
			}
			tpList.add(tpStr);
		}
		
		if(0 == Flag){
			for(int i = 0; i < tpList.size(); i++){
				iniFileOpe.setSection(repos.getName() + ":/branches/" + tpBuffer[tpBuffer.length-1] + "/" + tpList.get(i));
				iniFileOpe.setKey("@build");
				iniFileOpe.setValue("r");
				iniFileOpe.writeKeyValue();
				iniFileOpe.setKey("@admin");
				iniFileOpe.setValue("rw");
				iniFileOpe.writeKeyValue();
				
				if(owner != null){
					iniFileOpe.setKey(owner);
					iniFileOpe.setValue("rw");
					iniFileOpe.writeKeyValue();
				}
				
				iniFileOpe.setKey("*");
				iniFileOpe.setValue(" ");
				iniFileOpe.writeKeyValue();
			}
		}
		else if(1 == Flag){
			for(int i = 0; i < tpList.size(); i++){
				iniFileOpe.setSection(repos.getName() + ":/tags/" + tpBuffer[tpBuffer.length-1] + "/" + tpList.get(i));
				iniFileOpe.setKey("@build");
				iniFileOpe.setValue("r");
				iniFileOpe.writeKeyValue();
				
				if(owner != null){
					iniFileOpe.setKey(owner);
					iniFileOpe.setValue("rw");
					iniFileOpe.writeKeyValue();
				}
				
				iniFileOpe.setKey("*");
				iniFileOpe.setValue(" ");
				iniFileOpe.writeKeyValue();
			}
		}

		return retList;
	}

	public List<String> createSubProjects(Repository repos, ScmUser lastLogin, String realPath, String message)
	{
		List<String> retList;
		int projectCount = repos.getSubProjects().size();
		if(projectCount <= 0){
			retList = new ArrayList<String>();
			retList.add("have no sub-projects need create");
			return retList;
		}
		
		for(int i = 0; i < projectCount; i++){
			String project = repos.getSubProjects().get(i);
			File spDir = new File(realPath + "\\Temp\\" + project);
			spDir.mkdirs();
		}
		
		String arguments = "--username " + lastLogin.getName() + " --password " + lastLogin.getPassword();
		String destPath = repos.getServerURL() + "/" + repos.getName() + "/trunk";
		SvnCmd importCmd = new SvnCmd(realPath + "\\Temp", destPath, message, arguments);
		retList = importCmd.svnImport();
		
		String fileName = repos.getSvnRoot()+ "\\authz";
		String tSection = repos.getName() + ":/";
		IniFileOpe tIni = new IniFileOpe();
		tIni.setFileName(fileName);
		tIni.setSection(tSection);
		List<String> tpList = tIni.findBySection();
		String owner = null;
		if(tpList.size() >= 1){
			String[] tpBuffer = tpList.get(0).split("::=");
			if(tpBuffer.length >= 1){
				owner = tpBuffer[0];
			}
		}
		
		IniFileOpe iniFileOpe = new IniFileOpe();
		iniFileOpe.setFileName(fileName);
		
		for(int i = 0; i < repos.getSubProjects().size(); i++){
			iniFileOpe.setSection(repos.getName() + ":/trunk/" + repos.getSubProjects().get(i));
			iniFileOpe.setKey("@build");
			iniFileOpe.setValue("r");
			iniFileOpe.writeKeyValue();
			iniFileOpe.setKey("@admin");
			iniFileOpe.setValue("rw");
			iniFileOpe.writeKeyValue();
			
			if(owner != null){
				iniFileOpe.setKey(owner);
				iniFileOpe.setValue("rw");
				iniFileOpe.writeKeyValue();
			}
			
			iniFileOpe.setKey("*");
			iniFileOpe.setValue(" ");
			iniFileOpe.writeKeyValue();
		}
		
		delFolder(realPath + "\\Temp");
		
		return retList;
	}
	
	public List<String> unlocks(List<String> urls, ScmUser lastLogin)
	{
		List<String> retList;
		
		if(urls.size() <= 0){
			retList = new ArrayList<String>();
			retList.add("nothing need to unlock");
			return retList;
		}
		
		String arguments = "--username " + lastLogin.getName() + " --password " + lastLogin.getPassword() + " --force";
		SvnCmd unlockCmd = new SvnCmd("", arguments);
		retList = unlockCmd.svnUnlocks(urls);
		
		return retList;
	}
	
	public List<String> unlock(String url, ScmUser lastLogin)
	{
		List<String> retList;
		
		String arguments = "--username " + lastLogin.getName() + " --password " + lastLogin.getPassword() + " --force";
		SvnCmd unlockCmd = new SvnCmd(url, arguments);
		retList = unlockCmd.svnUnlock();
		
		return retList;
	}
	
	public List<String> deletes(List<String> urls, String message, ScmUser lastLogin)
	{
		List<String> retList;
		
		if(urls.size() <= 0){
			retList = new ArrayList<String>();
			retList.add("nothing need to delete");
			return retList;
		}
		
		String arguments = "--username " + lastLogin.getName() + " --password " + lastLogin.getPassword();
		SvnCmd deleteCmd = new SvnCmd("", message, arguments);
		retList = deleteCmd.svnDeletes(urls);
		
		return retList;
	}
	
	public List<String> delete(String url, String message, ScmUser lastLogin)
	{
		List<String> retList;
		
		String arguments = "--username " + lastLogin.getName() + " --password " + lastLogin.getPassword();
		SvnCmd deleteCmd = new SvnCmd(url, message, arguments);
		retList = deleteCmd.svnDelete();
		
		return retList;
	}
	
	public List<String> showLog(String url, ScmUser lastLogin)
	{
		List<String> retList;
		
		String arguments = "--username " + lastLogin.getName() + " --password " + lastLogin.getPassword();
		SvnCmd logCmd = new SvnCmd(url, arguments);
		retList = logCmd.svnLog();
		
		return retList;
	}
	
	public List<String> showStatus(String url, ScmUser lastLogin)
	{
		List<String> retList;
		
		String arguments = "--username " + lastLogin.getName() + " --password " + lastLogin.getPassword();
		SvnCmd statusCmd = new SvnCmd(url, arguments);
		retList = statusCmd.svnInfo();
		
		return retList;
	}
	
	public List<Repository> getAllRepos(String svnRoot, String serverURL, ScmUser lastLogin)
	{
		List<String> rpList = traversalDir(svnRoot);
		
		List<String> tkList;
		List<String> bhList;
		List<String> tgList;
		String destPath = "";
		
		String arguments = "--username " + lastLogin.getName() + " --password " + lastLogin.getPassword();
		SvnCmd listCmd = new SvnCmd("", arguments);
		for(int i = 0; i < rpList.size(); i++){
			String name = rpList.get(i);
			
			destPath = serverURL + "/" + name + "/trunk";
			listCmd.setDestPath(destPath);
			tkList = listCmd.svnList();
			
			destPath = serverURL + "/" + name + "/branches";
			listCmd.setDestPath(destPath);
			bhList = listCmd.svnList();
			
			destPath = serverURL + "/" + name + "/tags";
			listCmd.setDestPath(destPath);
			tgList = listCmd.svnList();
			
			String owner = getReposOwner(name, svnRoot);
			
			Repository repos = new Repository(name, svnRoot, serverURL, tkList, bhList, tgList);
			repos.setOwner(owner);
			reposes.add(repos);
		}
		
		return reposes;
	}
	
	public List<String> getReposStruct(String url, ScmUser lastLogin)
	{
		List<String> retList = new ArrayList<String>();
		List<String> pathList = new ArrayList<String>();
		
		String arguments = "--username " + lastLogin.getName() + " --password " + lastLogin.getPassword() + " -R";
		SvnCmd listCmd = new SvnCmd(url, arguments);
		pathList = listCmd.svnList();
		
		for(int i = 0; i < pathList.size(); i++){
			String path = pathList.get(i);
			int level = getLevel(path);
			int index = path.lastIndexOf("/");
			int dirFlag = 0;
			String note = "";
			if(index == path.length()-1){
				path = path.substring(0, index);
				index = path.lastIndexOf("/");
				note = path.substring(index+1, path.length());
				dirFlag = 1;
			}
			else{
				note = path.substring(index+1, path.length());
				dirFlag = 0;
			}
			
			retList.add(note + "::=" + level + "::=" + dirFlag);
		}
		
		return retList;
	}
	
	public ScmUser getLastLogin(String configRealPath)
	{
		ScmUser user = new ScmUser();
		
		IniFileOpe iniFileOpe = new IniFileOpe(configRealPath, "lastLogin", "name");
		String name = iniFileOpe.readKeyValue();
		iniFileOpe.setKey("password");
		String password = iniFileOpe.readKeyValue();
		
		user.setName(name);
		user.setPassword(password);
		
		return user;
	}
	
	public void readStructTree(String realPath)
	{
		noteList = new ArrayList<String>();
		noteIdList = new ArrayList<String>();
		fathIdList = new ArrayList<String>();
		dirFlagList = new ArrayList<String>();
		
		try {
			String treeFileName = realPath + "\\TreeStruct.txt";
			String str = null;
			
            FileReader reader = new FileReader(treeFileName); 
            BufferedReader br = new BufferedReader(reader);
            
            if((str = br.readLine()) != null){
            	if(!str.equals("noteList:")){
            		return;
            	}
                while((str = br.readLine()) != null){
                	if(str.equals("noteIdList:")){
                		break;
                	}
                	noteList.add(str);
                }
                while((str = br.readLine()) != null){
                	if(str.equals("fathIdList:")){
                		break;
                	}
                	noteIdList.add(str);
                }
                while((str = br.readLine()) != null){
                	if(str.equals("dirFlagList:")){
                		break;
                	}
                	fathIdList.add(str);
                }
                while((str = br.readLine()) != null){
                	dirFlagList.add(str);
                }
            }
            
            br.close();
            reader.close();
	    }
	    catch(FileNotFoundException e){
	    	e.printStackTrace();
	    }
	    catch(IOException e){
	        e.printStackTrace();
	    }
	}
	
	public void saveStructTree(String realPath)
	{
		if(noteList == null || noteIdList == null || fathIdList == null || dirFlagList == null){
			return;
		}
		
        try {
    		String treeFileName = realPath + "\\TreeStruct.txt";
    		
	        FileWriter writer = new FileWriter(treeFileName);
	        BufferedWriter bw = new BufferedWriter(writer);
	        
	        bw.write("noteList:\n");
	        for(int i = 0; i < noteList.size(); i++){
	        	bw.write(noteList.get(i)+"\n");
	        }
	        
	        bw.write("noteIdList:\n");
	        for(int i = 0; i < noteIdList.size(); i++){
	        	bw.write(noteIdList.get(i)+"\n");
	        }
	        
	        bw.write("fathIdList:\n");
	        for(int i = 0; i < fathIdList.size(); i++){
	        	bw.write(fathIdList.get(i)+"\n");
	        }
	        
	        bw.write("dirFlagList:\n");
	        for(int i = 0; i < dirFlagList.size(); i++){
	        	bw.write(dirFlagList.get(i)+"\n");
	        }
	        
	        bw.close();
	        writer.close();
        }
        catch(FileNotFoundException e){
        	e.printStackTrace();
		}
		catch(IOException e){
			e.printStackTrace();
		}
	}

	public boolean changeOwner(String svnRoot, String reposName, String owner, String newOwner)
	{
		String fileName = svnRoot + "\\authz";
		String section = reposName + ":/";
		
		IniFileOpe iniFileOpe = new IniFileOpe();
		iniFileOpe.setFileName(fileName);
		iniFileOpe.setSection(section);
		iniFileOpe.setKey(owner);
		
		if(!iniFileOpe.hasSection() || !iniFileOpe.hasOption()){
			List<String> ttpList = iniFileOpe.getAllSections();
			iniFileOpe.setKey(newOwner);
			iniFileOpe.setValue("rw");
			iniFileOpe.writeKeyValue();
			
			for(int k = 0; k < ttpList.size(); k++){
				if(0 == ttpList.get(k).indexOf(section)){
					iniFileOpe.setSection(ttpList.get(k));
					iniFileOpe.writeKeyValue();
				}
			}
			
			return true;
		}
		
		List<String> tpList = iniFileOpe.findByKey();
		for(int i = 0; i < tpList.size(); i++){
			String[] tpBuffer = tpList.get(i).split("::=");
			if(tpBuffer.length >= 1){
				if(0 == tpBuffer[0].indexOf(reposName+":/")){
					IniFileOpe tIni = new IniFileOpe(fileName, tpBuffer[0], owner);
					tIni.deleteKeyValue();
					tIni.setKey(newOwner);
					tIni.setValue("rw");
					tIni.writeKeyValue();
				}
			}
		}
		
		return true;
	}
	
	public String getReposOwner(String reposName, String svnRoot)
	{
		String fileName = svnRoot + "\\authz";
		String section = reposName + ":/";
		IniFileOpe iniFileOpe = new IniFileOpe();
		iniFileOpe.setFileName(fileName);
		iniFileOpe.setSection(section);
		List<String> tpList = iniFileOpe.findBySection();
		String owner = "unknown";
		if(tpList.size() >= 1){
			String[] tpBuffer = tpList.get(0).split("::=");
			if(tpBuffer.length >=1){
				owner = tpBuffer[0];
			}
		}
		
		return owner;
	}
	
	private int getLevel(String path)
	{
		int level = -1;
		
		String[] dirs = path.split("/");
		level = dirs.length;
		
		return level;
	}
	
	private List<String> traversalDir(String dirPath)
	{
		List<String> retList = new ArrayList<String>();
		
		File file = new File(dirPath);
		File[] list = file.listFiles();

		for(int i = 0; i < list.length; i++){
			if(list[i].isDirectory()){
				retList.add(list[i].getName());
			}
		}
		
		return retList;
	}
	
	private void delFolder(String folderPath)
	{
		try {
			delAllFiles(folderPath);
			String filePath = folderPath;
			filePath = filePath.toString();
			java.io.File myFilePath = new java.io.File(filePath);
			myFilePath.delete();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}

	private boolean delAllFiles(String path)
	{
		boolean flag = false; 
		File file = new File(path);

		if(!file.exists()){
			return flag;
		}

		if(!file.isDirectory()){
			return flag;
		}

		String[] tempList = file.list();
		File temp = null;

		for(int i = 0; i < tempList.length; i++){
			if (path.endsWith(File.separator)){
				temp = new File(path + tempList[i]);
			}
			else{
				temp = new File(path + File.separator + tempList[i]);
			}

			if(temp.isFile()){
				temp.delete();
			}

			if(temp.isDirectory()){
				delAllFiles(path + "/" + tempList[i]);
				delFolder(path + "/" + tempList[i]);
				flag = true;
			}
		}

		return flag;
	}
}








