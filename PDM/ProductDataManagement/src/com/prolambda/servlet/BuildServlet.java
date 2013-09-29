package com.prolambda.servlet;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.prolambda.controller.ArtifactService;
import com.prolambda.controller.BuildService;
import com.prolambda.controller.ComponentCategoryService;
import com.prolambda.controller.ComponentService;
import com.prolambda.controller.ComponentVersionService;
import com.prolambda.controller.DependenceService;
import com.prolambda.controller.LibraryService;
import com.prolambda.controller.ProductCategoryService;
import com.prolambda.controller.ProductService;
import com.prolambda.controller.ProductVersionService;
import com.prolambda.controller.RepositoryService;
import com.prolambda.model.*;

public class BuildServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 714403452360800820L;
	private String strFileFolder;

	public void init(){
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		//ServletConfig config = getServletConfig();
		//strFileFolder = config.getInitParameter("strFileFolder");
	}
	
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
		
		String flag = request.getParameter("flag");
		if(flag.equals("select")){
			selectOption(request, response);
		}else if(flag.equals("navigation")){
			navigationOption(request,response);
		}else if(flag.equals("package")){
			packageOption(request,response);
		}
		
	}
	public void navigationOption(HttpServletRequest request, HttpServletResponse response){
	
		HttpSession session = request.getSession(true);
		String buildId = (String)session.getAttribute("buildId");
		//String number = (String)session.getAttribute("buildNumber");
		
		//String repId = (String)session.getAttribute("repId");
		//ArtifactService artSer = new ArtifactService();
		//ArtifactList artList = artSer.getAll(Integer.parseInt(repId));
		BuildService buildSer = new BuildService();
		Build build = buildSer.getById(Integer.parseInt(buildId));
		ArtifactService artSer = new ArtifactService();
		Artifact art = artSer.getById(build.getArtifactId());
		
		LibraryService libSer = new LibraryService();
		LibraryList libList = libSer.getAllByBuildId(Integer.parseInt(buildId));
		DependenceService depSer = new DependenceService();
		DependenceList depList = depSer.getAll(Integer.parseInt(buildId));

		DepInfoList depInfoList = new DepInfoList();
		for(Dependence dep:depList){
			DepInfo info = new DepInfo();
			String flag = dep.getFlag();
			info.setFlag(flag);
			info.setPath(dep.getPath());
			info.setLocation(dep.getLocation());
			if("Build".equals(flag)){
				//BuildService buildSer = new BuildService();
				Build depBuild = buildSer.getById(dep.getReferenceId());
				//ArtifactService artSer = new ArtifactService();
				Artifact depArt = artSer.getById(depBuild.getArtifactId());
				RepositoryService repSer = new RepositoryService();
				Repository depRep = repSer.getById(depArt.getRepId());
				
				info.setRepository(depRep.getName());
				info.setName(depArt.getName());
				info.setVersion(depBuild.getNumber()+"");
			}else if("Component".equals(flag)){
				ComponentVersionService cVerSer = new ComponentVersionService();
				ComponentVersion comVer = cVerSer.getVersionById(dep.getReferenceId());
				ComponentService comSer = new ComponentService();
				Component com = comSer.getById(comVer.getComponentId());
				ComponentCategoryService cCatSer = new ComponentCategoryService();
				ComponentCategory comCat = cCatSer.getById(com.getCategoryId());
				
				info.setRepository(comCat.getName());
				info.setName(com.getName());
				info.setVersion(comVer.getVersion());
			}else if("Product".equals(flag)){
				ProductVersionService pVerSer = new ProductVersionService();
				ProductVersion proVer = pVerSer.getVersionById(dep.getReferenceId());
				ProductService proSer = new ProductService();
				Product pro = proSer.getById(proVer.getProductId());
				ProductCategoryService cCatSer = new ProductCategoryService();
				ProductCategory proCat = cCatSer.getById(pro.getCategoryId());
				
				info.setRepository(proCat.getName());
				info.setName(pro.getName());
				info.setVersion(proVer.getVersion());
			}
			depInfoList.add(info);
		}
		
		//int pageCount = libSer.getPageCount(Integer.parseInt(buildId));
		String log = build.getLog();
		String logPath = strFileFolder+"/"+log;
		
		request.setAttribute("artName", art.getName());
		request.setAttribute("librarylist", libList);
		request.setAttribute("build", build);
		request.setAttribute("dependencelist", depInfoList);
		
		request.setAttribute("log", logPath);
		
		if(session!=null){
			try {
				request.getRequestDispatcher("buildPage.jsp").forward(request, response);
			} catch (ServletException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public void packageOption(HttpServletRequest request, HttpServletResponse response) throws IOException{
		//PrintWriter out = response.getWriter();;
		HttpSession session = request.getSession(true);
		String buildId = request.getParameter("buildId");
		String repName = (String)session.getAttribute("repName");
		String artName = (String)session.getAttribute("artName");
		String number = (String)session.getAttribute("buildNumber");
		FileInputStream fis = null;  
	    BufferedInputStream bis = null;  
	    //FileOutputStream fos = null;
	    BufferedOutputStream bos = null;
	    ZipOutputStream zos = null;  
		
	    //File zipFile = new File(strFileFolder+"/temp.zip");
		//	if(zipFile.exists()){
		//		out.println("package file is exist");
		//	}else{
				try {
					
					DependenceService depSer = new DependenceService();
					DependenceList depList = depSer.getAll(Integer.parseInt(buildId));
					//out.println(depList.size()+"");
					if(depList.size()<1){
						return;
					}
					ServletOutputStream out = response.getOutputStream();
				    response.setHeader("Content-disposition", "attachment;filename="+repName+"_"+artName+"_"+number+"_"+"Dependence.zip");
					bos = new BufferedOutputStream(out);
				//	fos = new FileOutputStream(zipFile);
					zos = new ZipOutputStream(bos);  
	                byte[] bufs = new byte[1024*100];  
	                LibraryService libSer = new LibraryService();
	                LibraryList libList = null;
	                String filePath = "";
					for(Dependence dep:depList){
						if("Build".equals(dep.getFlag())){
							BuildService buildSer = new BuildService();
							
							Build build = buildSer.getById(dep.getReferenceId());
							
							libList = libSer.getAllByBuildId(build.getId());
							ArtifactService artSer = new ArtifactService();
							Artifact art = artSer.getById(build.getArtifactId());
							RepositoryService repSer = new RepositoryService();
							Repository rep = repSer.getById(art.getRepId());
							
							filePath = rep.getName()+"/"+art.getName()+"/"+build.getNumber()+"/";
						}else if("Component".equals(dep.getFlag())){
							ComponentVersionService cVerSer = new ComponentVersionService();
							
							ComponentVersion comVer = cVerSer.getVersionById(dep.getReferenceId());
							
							libList = libSer.getAllByComponentId(comVer.getId());
							
							ComponentService comSer = new ComponentService();
							Component com = comSer.getById(comVer.getComponentId());
							ComponentCategoryService cCateSer = new ComponentCategoryService();
							ComponentCategory comCate = cCateSer.getById(com.getCategoryId());
							
							filePath = comCate.getName()+"/"+com.getName()+"/"+comVer.getVersion()+"/";
							
						}else if("Product".equals(dep.getFlag())){
							ProductVersionService pVerSer = new ProductVersionService();
							ProductVersion proVer = pVerSer.getVersionById(dep.getReferenceId());
							libList = libSer.getAllByProductId(proVer.getId());
							
							ProductService proSer = new ProductService();
							Product pro = proSer.getById(proVer.getProductId());
							ProductCategoryService proCateSer = new ProductCategoryService();
							ProductCategory proCate = proCateSer.getById(pro.getCategoryId());
							
							filePath = proCate.getName()+"/"+pro.getName()+"/"+proVer.getVersion()+"/";
						}
						DownloadServlet down = new DownloadServlet();
						libList = down.filterLibList(libList, dep.getPath());
						for(Library lib:libList){
							File sourceFile = new File(strFileFolder+"/"+lib.getFileName());
							if(sourceFile.exists()==false){
								 try {  
					                    if(null != bos) bos.close();  
					                    if(null != zos) zos.close();  
					                } catch (IOException e) {  
					                    e.printStackTrace();  
					                    throw new RuntimeException(e);  
					                }
								 //return;
								 //out.println(">>>>>> 待压缩的文件目录：" + lib.getFileName() + " 不存在. <<<<<<");
							}else{
								ZipEntry zipEntry=null;
								if(depList.size()>1){
									//ArtifactService artSer = new ArtifactService();
									//Artifact art = artSer.getById(build.getArtifactId());
									//RepositoryService repSer = new RepositoryService();
									//Repository rep = repSer.getById(art.getRepId());
									zipEntry = new ZipEntry(filePath+lib.getName());
								}else{
									zipEntry = new ZipEntry(lib.getName());
								}
								
								zos.putNextEntry(zipEntry);
		                        // 读取待压缩的文件并写进压缩包里  
		                        fis = new FileInputStream(sourceFile);  
		                        bis = new BufferedInputStream(fis,1024*100);  
		                        int read = 0;  
		                        while((read=bis.read(bufs, 0, 1024*10)) != -1) {  
		                            zos.write(bufs, 0, read);  
		                        }  
							}
						}
						
					}
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {  
	                e.printStackTrace();  
	                throw new RuntimeException(e);  
	            } finally {  
	                // 关闭流  
	                try {  
	                    if(null != bis) bis.close();  
	                    if(null != zos) zos.close();  
	                } catch (IOException e) {  
	                    e.printStackTrace();  
	                    throw new RuntimeException(e);  
	                }
	            }   
                
			//}
	}

	public boolean fileToZip(String sourceFilePath,String zipFilePath,String fileName) {  
        boolean flag = false;
        File sourceFile = new File(sourceFilePath);  
        FileInputStream fis = null;  
        BufferedInputStream bis = null;  
        FileOutputStream fos = null;  
        ZipOutputStream zos = null;  
          
        if(sourceFile.exists() == false) {  
            System.out.println(">>>>>> 待压缩的文件目录：" + sourceFilePath + " 不存在. <<<<<<");  
        } else {  
            try {  
                File zipFile = new File(zipFilePath + "/" + fileName + ".zip");  
                if(zipFile.exists()) {  
                    System.out.println(">>>>>> " + zipFilePath + " 目录下存在名字为：" + fileName + ".zip" + " 打包文件. <<<<<<");  
                } else {  
                    File[] sourceFiles = sourceFile.listFiles();  
                    if(null == sourceFiles || sourceFiles.length < 1) {  
                        System.out.println(">>>>>> 待压缩的文件目录：" + sourceFilePath + " 里面不存在文件,无需压缩. <<<<<<");  
                    } else {  
                        fos = new FileOutputStream(zipFile);  
                        zos = new ZipOutputStream(new BufferedOutputStream(fos));  
                        byte[] bufs = new byte[1024*10];  
                        for(int i=0;i<sourceFiles.length;i++) {  
                            // 创建ZIP实体,并添加进压缩包  
                            ZipEntry zipEntry = new ZipEntry(sourceFiles[i].getName());  
                            zos.putNextEntry(zipEntry);  
                            // 读取待压缩的文件并写进压缩包里  
                            fis = new FileInputStream(sourceFiles[i]);  
                            bis = new BufferedInputStream(fis,1024*10);  
                            int read = 0;  
                            while((read=bis.read(bufs, 0, 1024*10)) != -1) {  
                                zos.write(bufs, 0, read);  
                            }  
                        }  
                        flag = true;  
                    }  
                }  
            } catch (FileNotFoundException e) {  
                e.printStackTrace();  
                throw new RuntimeException(e);  
            } catch (IOException e) {  
                e.printStackTrace();  
                throw new RuntimeException(e);  
            } finally {  
                // 关闭流  
                try {  
                    if(null != bis) bis.close();  
                    if(null != zos) zos.close();  
                } catch (IOException e) {  
                    e.printStackTrace();  
                    throw new RuntimeException(e);  
                }  
            }  
        }  
          
        return flag;  
    }  
	
	public void selectOption(HttpServletRequest request, HttpServletResponse response) throws FileNotFoundException
	{
		String buildId = request.getParameter("buildId");
		String number = request.getParameter("buildNumber");
		HttpSession session = request.getSession(true);
		session.setAttribute("buildId", buildId);
		session.setAttribute("buildNumber", number);
		
		//String repId = (String)session.getAttribute("repId");
		//ArtifactService artSer = new ArtifactService();
		//ArtifactList artList = artSer.getAll(Integer.parseInt(repId));
		BuildService buildSer = new BuildService();
		Build build = buildSer.getById(Integer.parseInt(buildId));
		ArtifactService artSer = new ArtifactService();
		Artifact art = artSer.getById(build.getArtifactId());
		
		LibraryService libSer = new LibraryService();
		LibraryList libList = libSer.getAllByBuildId(Integer.parseInt(buildId));
		DependenceService depSer = new DependenceService();
		DependenceList depList = depSer.getAll(Integer.parseInt(buildId));

		
		DepInfoList depInfoList = new DepInfoList();
		for(Dependence dep:depList){
			DepInfo info = new DepInfo();
			String flag = dep.getFlag();
			info.setFlag(flag);
			info.setPath(dep.getPath());
			info.setLocation(dep.getLocation());
			if("Build".equals(flag)){
				//BuildService buildSer = new BuildService();
				Build depBuild = buildSer.getById(dep.getReferenceId());
				//ArtifactService artSer = new ArtifactService();
				Artifact depArt = artSer.getById(depBuild.getArtifactId());
				RepositoryService repSer = new RepositoryService();
				Repository depRep = repSer.getById(depArt.getRepId());
				
				info.setRepository(depRep.getName());
				info.setName(depArt.getName());
				info.setVersion(depBuild.getNumber()+"");
			}else if("Component".equals(flag)){
				ComponentVersionService cVerSer = new ComponentVersionService();
				ComponentVersion comVer = cVerSer.getVersionById(dep.getReferenceId());
				ComponentService comSer = new ComponentService();
				Component com = comSer.getById(comVer.getComponentId());
				ComponentCategoryService cCatSer = new ComponentCategoryService();
				ComponentCategory comCat = cCatSer.getById(com.getCategoryId());
				
				info.setRepository(comCat.getName());
				info.setName(com.getName());
				info.setVersion(comVer.getVersion());
			}else if("Product".equals(flag)){
				ProductVersionService pVerSer = new ProductVersionService();
				ProductVersion proVer = pVerSer.getVersionById(dep.getReferenceId());
				ProductService proSer = new ProductService();
				Product pro = proSer.getById(proVer.getProductId());
				ProductCategoryService cCatSer = new ProductCategoryService();
				ProductCategory proCat = cCatSer.getById(pro.getCategoryId());
				
				info.setRepository(proCat.getName());
				info.setName(pro.getName());
				info.setVersion(proVer.getVersion());
			}
			depInfoList.add(info);
		}
		
		//int pageCount = libSer.getPageCount(Integer.parseInt(buildId));
		String log = build.getLog();
		String logPath = strFileFolder+"/"+log;
		
		request.setAttribute("artName", art.getName());
		request.setAttribute("librarylist", libList);
		request.setAttribute("build", build);
		request.setAttribute("dependencelist", depInfoList);
		request.setAttribute("log", logPath);
		
		if(session!=null){
			try {
				request.getRequestDispatcher("buildPage.jsp").forward(request, response);
			} catch (ServletException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public String readFile(String filePath) throws FileNotFoundException{
		String text = "";
		BufferedReader file = new BufferedReader(new FileReader(filePath));
		try{
			text = file.readLine();
		}catch(IOException e){
			System.out.print("read File error");
		}
		if(text==null){
			text = "nothing";
		}
		
		return text;
	}

}
