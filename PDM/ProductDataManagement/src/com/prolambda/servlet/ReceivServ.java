package com.prolambda.servlet;

import java.io.PrintWriter;
import java.sql.Timestamp;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.prolambda.controller.ArtifactService;
import com.prolambda.controller.BuildService;
import com.prolambda.controller.DependenceService;
import com.prolambda.controller.RepositoryService;
import com.prolambda.model.Artifact;
import com.prolambda.model.ArtifactList;
import com.prolambda.model.Build;
import com.prolambda.model.BuildResult;
import com.prolambda.model.Dependence;
import com.prolambda.model.Repository;

@SuppressWarnings("serial")
public class ReceivServ extends HttpServlet {

	
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)  {
		doPost(req, resp);
	}

	protected void doPost(HttpServletRequest req, HttpServletResponse resp) {
		try {
			//String strFileFolder = "E:\\TempFolder";
			PrintWriter out = resp.getWriter();
			
			String repName = req.getParameter("RepositoryName");
			String artName = req.getParameter("ArtifactName");
			String number = req.getParameter("Number");
			String buildTime = req.getParameter("BuildTime");
			String duration = req.getParameter("Duration");
			String result = req.getParameter("Result");
			String sourcePath = req.getParameter("SourcePath");
			String sourceVersion = req.getParameter("SourceVersion");
			//String environment = req.getParameter("Environment");
			//String targetPath = req.getParameter("TargetPath");
			
			if(number.equals("1"))
			{
				Artifact art = new Artifact();
				art.setName(artName);
				art.setCount(Integer.parseInt(number));
				art.setStarted(Timestamp.valueOf(buildTime));
				art.setLasttime(Timestamp.valueOf(buildTime));
				Repository rep = new Repository();
				RepositoryService repSer = new RepositoryService();
				rep = repSer.getByName(repName);
				art.setRepId(rep.getId());
				
				ArtifactService artSer = new ArtifactService();
				if(artSer.contains(rep.getId(), artName)){
					return;
				}
				artSer.create(art);
			} 
			
			String path = sourcePath.replace('\\', '/');
			//String logt = log.replace('\\', '/');
			Build build = new Build();
			build.setNumber(Integer.parseInt(number));
			build.setStarted(Timestamp.valueOf(buildTime));
			build.setDuration(Long.parseLong(duration));
			build.setResult(BuildResult.valueOf(result));
			build.setSourcePath(path);
			build.setSourceVersion(sourceVersion);
			//build.setEnvironment(environment);
			//build.setLog(logt);
			RepositoryService repSer = new RepositoryService();
			Repository rep = repSer.getByName(repName);
			ArtifactService artSer = new ArtifactService();
			ArtifactList artList = artSer.getAll(rep.getId());
			int artId = 0 ;
			for(Artifact art:artList)
			{
				if(art.getName().equals(artName))
				{
					artId = art.getId();
					break;
				}
			}
			build.setArtifactId(artId);
			BuildService buildSer = new BuildService();
			if(buildSer.contains(artId, Integer.parseInt(number))){
				return;
			}
			buildSer.create(build);
			
			
			int buildId = buildSer.getIdByRepArt(repName, artName, Integer.parseInt(number));
			String depCount = req.getParameter("DepCount");
			DependenceService depSer = new DependenceService();
			for(int i=0;i<Integer.parseInt(depCount);i++){
				Dependence dep = new Dependence();
				
				String depArtName = req.getParameter("DepName_"+i);
				String depNumber = req.getParameter("DepVersion_"+i);
				String depRepName = req.getParameter("DepRepository_"+i);
				//if(depArtName==null||depNumber==null||depRepName==null){
				//	continue;
				//}
				int depBuildId = buildSer.getIdByRepArt(depRepName, depArtName, Integer.parseInt(depNumber));
				if(depBuildId<0){
					continue;
				}
				dep.setBuildId(buildId);
				dep.setReferenceId(depBuildId);
				//dep.setPlatform(req.getParameter("DepPlatform_"+i));
				//dep.setConfiguration(req.getParameter("DepConfiguration_"+i));
				
				dep.setLocation(req.getParameter("DepLocation_"+i));
				
				if(number.equals("1")||!depSer.contains(dep)){
					depSer.create(dep);
				}
				else {
					depSer.update(dep);
				}
			}
			
			out.write(" ReceivMessage: You are success!");
			out.flush();
			out.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
