package com.prolambda.servlet;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.servlet.ServletException;
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

public class ComponentVersionServlet extends HttpServlet {

	/**
	 * 
	 */
	
	private String strFileFolder;

	public void init(){
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		//ServletConfig config = getServletConfig();
		//strFileFolder = config.getInitParameter("strFileFolder");
		File file = new File(strFileFolder);
		if (!file.exists()) {
			file.mkdirs();
		}
	}
	
	private static final long serialVersionUID = -8130764184872171770L;

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		String flag = request.getParameter("flag");
		if(flag.equals("create")){
			create(request,response);
		}else if(flag.equals("delete")){
			delete(request,response);
		}else if(flag.equals("select")){
			select(request,response);
		}else if(flag.equals("navigation")){
			request.getRequestDispatcher("componentLibraryPage.jsp").forward(request, response);
		}else if(flag.equals("getRepository")){
			getRepository(request,response);
		}else if(flag.equals("getArtifact")){
			getArtifact(request,response);
		}else if(flag.equals("importLibrary")){
			importLibrary(request,response);
		}else if(flag.equals("removeLibrary")){
			removeLibrary(request,response);
		}else if(flag.equals("selectProduct")){
			selectProduct(request,response);
		}else if(flag.equals("addDependence")){
			addDependence(request,response);
		}else if(flag.equals("removeDependence")){
			removeDependence(request,response);
		}

		out.flush();
		out.close();
	}
	

	private void removeDependence(HttpServletRequest request,HttpServletResponse response) {
		String dependenceId = request.getParameter("dependenceId");
		HttpSession session = request.getSession(true);
		String versionId = (String)session.getAttribute("versionId");
		
		ComponentVersionService cVerSer = new ComponentVersionService();
		
		cVerSer.removeDependence(Integer.parseInt(versionId),Integer.parseInt(dependenceId));
	}

	private void addDependence(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		
		HttpSession session = request.getSession(true);
		String dependenceIds = request.getParameter("componentIds");
		String componentId = (String)session.getAttribute("versionId");
		String[] idList = dependenceIds.split(",");
		
		ComponentVersionService cVerSer = new ComponentVersionService();
		for(String dependenceId:idList){
			if(!dependenceId.equals("")&&cVerSer.containDependence(Integer.parseInt(componentId), Integer.parseInt(dependenceId))){
				cVerSer.addDependence(Integer.parseInt(componentId), Integer.parseInt(dependenceId));
			}
				
		}
		
		ComponentVersionList versionList = cVerSer.getDependences(Integer.parseInt(componentId));
		ComponentList comDepList = new ComponentList();
		ComponentCategoryList catDepList = new ComponentCategoryList();
		ComponentService comSer = new ComponentService();
		ComponentCategoryService comCatSer = new ComponentCategoryService();
		
		String strRet = "";
		for(ComponentVersion cVersion:versionList){
			Component com = comSer.getById(cVersion.getComponentId());
			ComponentCategory cCategory = comCatSer.getById(com.getCategoryId());
			
			comDepList.add(com);
			catDepList.add(cCategory);
			
			strRet += cVersion.getId()+","+cVersion.getVersion()+","+com.getName()+","+cCategory.getName()+"|";
		}
		
		session.setAttribute("versionDependenceList", versionList);
		session.setAttribute("componentDependenceList", comDepList);
		session.setAttribute("categoryDependenceList", catDepList);
		
		out.print(strRet);
		out.flush();
		out.close();
		//request.getRequestDispatcher("componentLibraryPage.jsp").forward(request, response);
	}

	private void selectProduct(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		String versionId = request.getParameter("productId");
		HttpSession session = request.getSession();
		//System.out.print(versionId);
		ProductCategoryService pCategorySer = new ProductCategoryService();
		ProductService proSer = new ProductService();
		ProductVersionService versionSer = new ProductVersionService();
		
		ProductVersion pVersion = versionSer.getVersionById(Integer.parseInt(versionId));
		Product product = proSer.getById(pVersion.getProductId());
		
		
		ProductCategoryList pCategoryList = pCategorySer.getAll();
		
		ComponentVersionList versionList = versionSer.getComponents(Integer.parseInt(versionId));
		
		
		ProductList proList = proSer.getAll(product.getCategoryId());
		ProductCategory pCategory  = pCategorySer.getById(product.getCategoryId());
		ProductVersionList pVersionList = versionSer.getVersions(product.getId());
		
		String strRet = "";
		int state = product.getState();
		if(state==0){
			strRet = "internal";
			
			ComponentCategoryList cCategoryList = new ComponentCategoryList();
			ComponentList comList = new ComponentList();
			ComponentCategoryService cCategorySer = new ComponentCategoryService();
			ComponentService comSer = new ComponentService();
			StringList cLocationList = new StringList();
			
			for(ComponentVersion version:versionList){
				String location = versionSer.getComponentLocation(Integer.parseInt(versionId), version.getId());
				Component com = comSer.getById(version.getComponentId());
				ComponentCategory category = cCategorySer.getById(com.getCategoryId());
				
				cLocationList.add(location);
				comList.add(com);
				cCategoryList.add(category);
			}
			
			
			ProductDependenceList pDepVerList = versionSer.getDependences(Integer.parseInt(versionId));
			
			LibraryService libSer = new LibraryService();
			LibraryList setupFileList = libSer.getAllByProductId(Integer.parseInt(versionId));
			LibraryList  issFileList= new LibraryList();
			for(Library lib:setupFileList){
				int fileId = versionSer.getIssBySetupFile(lib.getId());
				Library issFile = libSer.getById(fileId);
				issFileList.add(issFile);
			}
			
			session.setAttribute("categoryList", cCategoryList);
			session.setAttribute("componentList", comList);
			session.setAttribute("componentVersionList", versionList);
			session.setAttribute("componentLocationList", cLocationList);
			
			session.setAttribute("issFileList", issFileList);
			session.setAttribute("setupFileList", setupFileList);
			
			session.setAttribute("pDependenceList", pDepVerList);
			

		}else if(state==1){
			strRet = "external";
			LibraryService libSer = new LibraryService();
			LibraryList libList = libSer.getAllByProductId(Integer.parseInt(versionId));
			
			session.setAttribute("productLibraryList", libList);
		}
		
		session.setAttribute("productVersionList", pVersionList);
		session.setAttribute("productList", proList);
		session.setAttribute("productCategoryList", pCategoryList);
		session.setAttribute("productCategory", pCategory);
		session.setAttribute("product", product);
		session.setAttribute("productVersion", pVersion.getVersion());
		session.setAttribute("productVersionId", versionId);
		
		
		session.setAttribute("isProduct", "yes");
		//session.setAttribute("tabId", "0");
		//request.getRequestDispatcher("productComponentPage.jsp").forward(request, response);
		out.print(strRet);
		out.flush();
		out.close();
	}

	public void removeLibrary(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		String libIds = request.getParameter("libIds");
		
		HttpSession session = request.getSession(true);
		String versionId = (String)session.getAttribute("versionId");
		
		String[] libIdList = libIds.split(",");
		
		LibraryService libSer = new LibraryService();
		
		for(String libId:libIdList){
			if("".equals(libId)||"null".equals(libId)){
				continue;
			}
			Library lib = libSer.getById(Integer.parseInt(libId));
			
			File file = new File(strFileFolder+"/"+lib.getFileName());
			
			if(file.exists()){
				file.delete();
			}
			
			libSer.delete(Integer.parseInt(libId));
		}
		
		
		
		LibraryList libList = libSer.getAllByComponentId(Integer.parseInt(versionId));
		
		session.setAttribute("componentLibraryList", libList);
		//request.getRequestDispatcher("componentLibraryPage.jsp").forward(request, response);
	}
	
	public void importLibrary(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		
		String buildIds = request.getParameter("buildId");
		HttpSession session = request.getSession(true);
		String versionId = (String)session.getAttribute("versionId");
		
		String buildList[] = buildIds.split(",");
		LibraryService libSer = new LibraryService();
		DependenceService depSer = new DependenceService();
		BuildService buildSer = new BuildService();
		
		for(String buildId:buildList){
			
			LibraryList libList = libSer.getAllByBuildId(Integer.parseInt(buildId));
			DependenceList depList = depSer.getAll(Integer.parseInt(buildId));
			for(Dependence dep:depList){
				Build build = buildSer.getById(dep.getReferenceId());
				LibraryList libLists = libSer.getAllByBuildId(build.getId());
				for(Library lib:libLists){
					lib.setComponentId(Integer.parseInt(versionId));
					
					libSer.update(lib);
				}
			}
			for(Library lib:libList){
				lib.setComponentId(Integer.parseInt(versionId));
				
				libSer.update(lib);
			}
		}
		
		LibraryList libList = libSer.getAllByComponentId(Integer.parseInt(versionId));
		session.setAttribute("componentLibraryList", libList);
		request.getRequestDispatcher("componentLibraryPage.jsp").forward(request, response);
	}
	
	public void getArtifact(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String repName = request.getParameter("repName");
		
		RepositoryService repSer = new RepositoryService();
		Repository rep = repSer.getByName(repName);
		
		ArtifactService artSer = new ArtifactService();
		ArtifactList artList = artSer.getAll(rep.getId());
		
		String strRet = "";
		for(Artifact art:artList){
			BuildService buildSer = new BuildService();
			BuildList buildList = buildSer.getAll(art.getId());
			strRet += art.getName()+",";
			for(Build build:buildList){
				strRet += build.getId()+"&"+build.getNumber()+ ",";
			}
			strRet += "|";
			
		}
		out.print(strRet);
		out.flush();
		
		out.close();
	}
	
	public void getRepository(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		RepositoryService repSer = new RepositoryService();
		
		RepositoryList repList = repSer.getAll();
		String strRet ="";
		for(Repository rep:repList){
			strRet += rep.getName()+"|";
		}
		out.print(strRet);
		out.flush();
		out.close();
		
	}

	public void select(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		String versionId = request.getParameter("versionId");
		//String version = request.getParameter("version");
		
		LibraryService libSer = new LibraryService();
		LibraryList libList = libSer.getAllByComponentId(Integer.parseInt(versionId));
		ComponentVersionService versionSer = new ComponentVersionService();
		String version = versionSer.getVersionById(Integer.parseInt(versionId)).getVersion();
		
		ComponentVersionList versionList = versionSer.getDependences(Integer.parseInt(versionId));
		ComponentList comDepList = new ComponentList();
		ComponentCategoryList catDepList = new ComponentCategoryList();
		ComponentService comSer = new ComponentService();
		ComponentCategoryService comCatSer = new ComponentCategoryService();
		for(ComponentVersion cVersion:versionList){
			Component com = comSer.getById(cVersion.getComponentId());
			ComponentCategory cCategory = comCatSer.getById(com.getCategoryId());
			
			comDepList.add(com);
			catDepList.add(cCategory);
		}
		
		ProductService proSer = new ProductService();
		ProductCategoryService pCategorySer = new ProductCategoryService();
		ProductVersionList proVersionList = versionSer.getProducts(Integer.parseInt(versionId));
		ProductList proList = new ProductList();
		ProductCategoryList categoryList = new ProductCategoryList();
		
		for(ProductVersion proVersion:proVersionList){
			Product pro = proSer.getById(proVersion.getProductId());
			ProductCategory pCategory = pCategorySer.getById(pro.getCategoryId());
			
			proList.add(pro);
			categoryList.add(pCategory);
		}
		
		HttpSession session = request.getSession(true);
		session.setAttribute("componentLibraryList", libList);
		session.setAttribute("versionId", versionId);
		session.setAttribute("componentVersion", version);
		session.setAttribute("isFlag", "yes");
		
		session.setAttribute("versionDependenceList", versionList);
		session.setAttribute("componentDependenceList", comDepList);
		session.setAttribute("categoryDependenceList", catDepList);
		
		session.setAttribute("productCategoryList", categoryList);
		session.setAttribute("productList", proList);
		session.setAttribute("productVersionList", proVersionList);
		//request.setAttribute("libraryList", libList);
		request.getRequestDispatcher("componentLibraryPage.jsp").forward(request, response);
	}
	
	public void create(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String componentName = request.getParameter("componentName");
		String componentId = request.getParameter("componentId");
		
		ComponentVersion cVersion = new ComponentVersion();
		
		String version = request.getParameter("version");
		String description = request.getParameter("description");
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp created = Timestamp.valueOf(time);
		//Timestamp modified = Timestamp.valueOf(time);
		
		cVersion.setVersion(version);
		cVersion.setDescription(description);
		cVersion.setCreated(created);
		cVersion.setComponentId(Integer.parseInt(componentId));

		HttpSession session = request.getSession(true);
		ComponentCategory category = (ComponentCategory)session.getAttribute("componentCategory");
		
		ComponentVersionService verSer = new ComponentVersionService();
		if(verSer.contains(category.getName(), componentName, version)){
			out.print("<script language='javascript'>alert('the component category is exist');</script>");
			
		}else if(version==""||version==null)
		{
			out.print("<script language='javascript'>alert('the name is empty');</script>");
		}else
		{
			Boolean ok = verSer.create(cVersion);
			if(!ok)
			{
				out.write("Create Product Version error");
				out.flush();
				out.close();
			}else{
				int versionId = verSer.getIdByVersion(category.getName(),componentName,version);
				int pid = -1;
				ComponentService comSer = new ComponentService();
				ComponentList comList = comSer.getAll(category.getId());
				for(int i=0;i<comList.size();i++){
					if(comList.get(i).getId()==Integer.parseInt(componentId))
						pid = i+1;
				}
				
				String strRet = versionId+"|"+version+"|"+description+"|"+created+"|"+pid;
				out.println(strRet);
				out.flush();
				out.close();
			}
		
		}
		
		ComponentVersionList versionList = verSer.getVersions(Integer.parseInt(componentId));
		session.setAttribute("componentVersionList", versionList);
	}

	public void delete(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();

		String versionId = request.getParameter("versionId");
		
		ComponentVersionService versionSer = new ComponentVersionService();
		
		ComponentVersion comVersion = versionSer.getVersionById(Integer.parseInt(versionId));
		int comId = comVersion.getComponentId();
		
		LibraryService libSer = new LibraryService();
		LibraryList libList = libSer.getAllByComponentId(comId);
		for(Library lib:libList){
			libSer.delete(lib.getId());
			
			File file = new File(strFileFolder+"/"+lib.getFileName());
			
			if(file.exists()){
				file.delete();
			}
		}
		
		versionSer.delete(Integer.parseInt(versionId));
		ComponentVersionList versionList = versionSer.getVersions(comId);
		HttpSession session = request.getSession(true);
		ComponentList comList = (ComponentList)session.getAttribute("componentList");
		int index = -1;
		for(int i=0;i<comList.size();i++){
			if(comId==comList.get(i).getId()){
				index = i+1;
			}
		}
		
		session.setAttribute("componentVersionList", versionList);
		
		out.println(index);
		out.flush();
		out.close();
	}
}
