package com.prolambda.servlet;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.prolambda.controller.ComponentCategoryService;
import com.prolambda.controller.ComponentService;
import com.prolambda.controller.ComponentVersionService;
import com.prolambda.controller.LibraryService;
import com.prolambda.controller.ProductCategoryService;
import com.prolambda.controller.ProductService;
import com.prolambda.controller.ProductVersionService;
import com.prolambda.model.Component;
import com.prolambda.model.ComponentCategory;
import com.prolambda.model.ComponentCategoryList;
import com.prolambda.model.ComponentList;
import com.prolambda.model.ComponentVersion;
import com.prolambda.model.ComponentVersionList;
import com.prolambda.model.GuidCreator;
import com.prolambda.model.Library;
import com.prolambda.model.LibraryList;
import com.prolambda.model.Product;
import com.prolambda.model.ProductCategory;
import com.prolambda.model.ProductCategoryList;
import com.prolambda.model.ProductDependence;
import com.prolambda.model.ProductDependenceList;
import com.prolambda.model.ProductList;
import com.prolambda.model.ProductTree;
import com.prolambda.model.ProductTreeList;
import com.prolambda.model.ProductVersion;
import com.prolambda.model.ProductVersionList;
import com.prolambda.model.StringList;

public class ProductVersionServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1347662064294295208L;

	private String strFileFolder;
	private String ultraISO ;
	private String tempPath;
	
	public void init(){
		strFileFolder = getServletContext().getInitParameter("strFileFolder");
		//ServletConfig config = getServletConfig();
		//strFileFolder = config.getInitParameter("strFileFolder");
		ultraISO = getServletContext().getInitParameter("ultraISO");
		File file = new File(strFileFolder);
		if (!file.exists()) {
			file.mkdirs();
		}
		
	}
	
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request,response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		
		
		String flag = request.getParameter("flag");
		if(flag.equals("create")){
			create(request,response);
		}else if(flag.equals("delete")){
			delete(request,response);
		}else if(flag.equals("select")){
			select(request,response);
		}else if(flag.equals("getComponentCategory")){
			getComponentCategory(request,response);
		}else if(flag.equals("getComponents")){
			getComponents(request,response);
		}else if(flag.equals("addComponent")){
			addComponent(request,response);
		}else if(flag.equals("navigation")){
			navigation(request,response);
		}else if(flag.equals("deleteComponent")){
			deleteComponent(request,response);
		}else if(flag.equals("selectComponent")){
			selectComponent(request,response);
		}else if(flag.equals("getLastVersion")){
			getLastVersion(request,response);
		}else if(flag.equals("getLibrary")){
			getLibrary(request,response);
		}else if(flag.equals("getProductCategory")){
			getProductCategory(request,response);
		}else if(flag.equals("getProducts")){
			getProducts(request,response);
		}else if(flag.equals("addDependence")){
			addDependence(request,response);
		}else if(flag.equals("getDependenceLibrary")){
			getDependenceLibrary(request,response);
		}else if(flag.equals("removeDependence")){
			removeDependence(request,response);
		}else if(flag.equals("packageIso")){
			packageIso(request,response);
		}else if(flag.equals("getTree")){
			getTree(request,response);
		}else if(flag.equals("removeFile")){
			removeFile(request,response);
		}else if(flag.equals("getDependenceFile")){
			getDpendenceFile(request,response);
		}else if(flag.equals("changeDependenceLocation")){
			changeDependenceLocation(request,response);
		}else if(flag.equals("changeLocation")){
			changeLocation(request,response);
		}else if(flag.equals("changeComponentLocation")){
			changeComponentLocation(request,response);
		}else if(flag.equals("getSetupFile")){
			getSetupFile(request,response);
		}else if(flag.equals("showLibrary")){
			showLibrary(request,response);
		}
		
	}
	
	private void showLibrary(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException{
		String versionid = request.getParameter("versionId");
		LibraryService libSer = new LibraryService();
		LibraryList libList = libSer.getAllByProductId(Integer.parseInt(versionid));
		request.setAttribute("libraryList", libList);
		request.getRequestDispatcher("showLibrary.jsp").forward(request, response);
	}
	
	private void getSetupFile(HttpServletRequest request,HttpServletResponse response) throws IOException {
		HttpSession session = request.getSession(true);
        PrintWriter out = response.getWriter();
        
        LibraryList libList = (LibraryList)session.getAttribute("setupFileList");
        String strRet = "";
        for(Library lib:libList){
        	strRet += lib.getId()+","+lib.getName()+"|";
        }
        System.out.println("strRet:"+strRet);
        out.print(strRet);
        out.flush();
        out.close();
	}

	private void changeComponentLocation(HttpServletRequest request,HttpServletResponse response) {
		String location = request.getParameter("location");
		String componentId = request.getParameter("componentId");
		
		if("".equals(componentId))
			return;
		
		HttpSession session = request.getSession(true);
		String versionId = (String)session.getAttribute("productVersionId");
		
		ProductVersionService pVerSer = new ProductVersionService();
		
		pVerSer.setComponentLocation(Integer.parseInt(versionId), Integer.parseInt(componentId), location);
	}

	private void changeLocation(HttpServletRequest request,HttpServletResponse response) {
		String location = request.getParameter("location");
		String libId = request.getParameter("libId");
		
		if("".equals(libId))
			return;
		location = location.replace("\\", "/");
		LibraryService libSer = new LibraryService();
		Library lib = libSer.getById(Integer.parseInt(libId));
		/*String name = lib.getName();
		int index = name.lastIndexOf("/");
		if(index!=-1){
			name = name.substring(index+1);
		}
		if(".".equals(location)){
			lib.setName(name);
		}else{
			lib.setName(location+"/"+name);
		}
		*/
		lib.setName(location);
		libSer.update(lib);
	}

	private void changeDependenceLocation(HttpServletRequest request,HttpServletResponse response) {
		String location = request.getParameter("location");
		String fileId = request.getParameter("fileId");
		if("".equals(fileId)){
			return;
		}
		location = location.replace("\\", "/");
		HttpSession session = request.getSession(true);
		String versionId = (String)session.getAttribute("productVersionId");
		
		ProductVersionService pVerSer = new ProductVersionService();
		//System.out.println(fileId+"--"+versionId);
		pVerSer.setDependenceLocation(Integer.parseInt(versionId), Integer.parseInt(fileId), location);
	}

	private void getDpendenceFile(HttpServletRequest request,HttpServletResponse response) throws IOException {
		PrintWriter out = response.getWriter();
		HttpSession session = request.getSession(true);
		
		String versionId = (String)session.getAttribute("productVersionId");
		ProductVersionService pVerSer = new ProductVersionService();
		LibraryService libSer = new LibraryService();
		String strRet ="";
		
		LibraryList setupFileList = libSer.getAllByProductId(Integer.parseInt(versionId));
		for(Library lib:setupFileList){
			
			strRet+=lib.getName()+",";
		}
		
		ProductDependenceList pDepList = pVerSer.getDependences(Integer.parseInt(versionId));
		for(ProductDependence pDep:pDepList){
			String location = pDep.getRelativePath();
			/*
			String fileName = pDep.getFileName();
			
			int index = fileName.lastIndexOf("/")+1;
			if(index>0){
				fileName = fileName.substring(index+1);
			}
			
			if(".".equals(location)){
				strRet += fileName + ",";
			}else {
				strRet += location+"/"+fileName+",";
			}*/
			strRet += location+",";
		}
		/*
		ProductVersionList pDepList = pVerSer.getDependences(Integer.parseInt(versionId));
		
		for(ProductVersion pDep:pDepList){
			String location = pVerSer.getDependenceLocation(Integer.parseInt(versionId), pDep.getId());
			LibraryList libList = libSer.getAllByProductId(pDep.getId());
			
			
			for(Library lib:libList){
				String name = lib.getName();
				int index = name.lastIndexOf("/");
				name = name.substring(index+1);
				if(".".equals(location)){
					strRet += name+",";
				}else{
					strRet += location+"/"+name+",";
				}
				
			}
			
		}*/
		//System.out.println(strRet);
		out.print(strRet);
		out.flush();
		out.close();
	}

	private void removeFile(HttpServletRequest request,HttpServletResponse response) {
		String issId = request.getParameter("issId");
		if("".equals(issId))
			return;
		HttpSession session = request.getSession(true);
		String versionId = (String)session.getAttribute("productVersionId");
		//System.out.println(issId);
		LibraryService libSer = new LibraryService();
		
		Library lib = libSer.getById(Integer.parseInt(issId));
		
		File file = new File(strFileFolder+"/"+lib.getFileName());
		//System.out.println(lib.getFileName());
		if(file.exists()){
			file.delete();
		}
		
		
		ProductVersionService pVerSer = new ProductVersionService();
		int fileId = pVerSer.getFileByIss(Integer.parseInt(issId));
		if(fileId!=-1){
			Library oldLib = libSer.getById(fileId);
			libSer.delete(fileId);
			File oldfile = new File(strFileFolder+"/"+oldLib.getFileName());
			//System.out.println(lib.getFileName());
			if(oldfile.exists()){
				oldfile.delete();
			}
		}
		pVerSer.deleteByIssId(Integer.parseInt(issId));
		
		pVerSer.deleteTreeByLibrary(fileId);
		
		libSer.delete(Integer.parseInt(issId));
		
		LibraryList libList = libSer.getAllByProductId(Integer.parseInt(versionId));
		LibraryList setupFileList = new LibraryList();
		for(Library tlib:libList){
			int tfileId = pVerSer.getFileByIss(tlib.getId());
			Library setupFile = libSer.getById(tfileId);
			setupFileList.add(setupFile);
		}
		
		session.setAttribute("issFileList", libList);
		session.setAttribute("setupFileList", setupFileList);
	}

	private void getTree(HttpServletRequest request,HttpServletResponse response) throws IOException {
		PrintWriter out = response.getWriter();
		HttpSession session = request.getSession(true);
		String versionId = (String)session.getAttribute("productVersionId");
		
		ProductVersionService pVerSer = new ProductVersionService();
		ProductTreeList pTreeList = pVerSer.getTrees(Integer.parseInt(versionId));
		
		String strRet = "";
		for(ProductTree tree:pTreeList){
			strRet += tree.getLibraryId()+","+tree.getPath()+"|";
		}
		//System.out.println(strRet);
		out.print(strRet);
		out.flush();
		out.close();
	}

	private void packageIso(HttpServletRequest request,HttpServletResponse response) throws IOException {
		String root = request.getParameter("root");
		
		GuidCreator gc = new GuidCreator();
    	String guidPath = gc.toString();
    	if(".".equals(root)){
    		tempPath = strFileFolder + "/" + guidPath;
    	}else
    		tempPath = strFileFolder + "/" + guidPath+"/"+root;
		
    	File file = new File(tempPath);
		if (!file.exists()) {
			file.mkdirs();
		}
		System.out.print(tempPath);
		HttpSession session = request.getSession(true);
		String versionId = (String)session.getAttribute("productVersionId");
		//System.out.print(treeStr);
		ProductVersionService pVerSer = new ProductVersionService();
		LibraryService libSer = new LibraryService();
		
		ProductDependenceList pDepList = pVerSer.getDependences(Integer.parseInt(versionId));
		
		for(ProductDependence pDep:pDepList){
			Library lib = libSer.getById(pDep.getFileId());
			String fileName = lib.getName();
			int index = fileName.lastIndexOf("/")+1;
			if(index>0){
				fileName = fileName.substring(index);
			}
			String location = pDep.getRelativePath();
			
			File targetFile = new File(tempPath+"/"+location);
			//System.out.println(targetFile.getParent());
			File tmpPath = new File(targetFile.getParent());
			if(!tmpPath.exists()){
				tmpPath.mkdirs();
			}
			
			File sourceFile = new File(strFileFolder+"/"+lib.getFileName());
			
			copyFile(sourceFile,targetFile);
		}
		
		LibraryList libList = libSer.getAllByProductId(Integer.parseInt(versionId));
		for(Library lib:libList){
			File sourceFile = new File(strFileFolder+"/"+lib.getFileName());
			File targetFile = new File(tempPath+"/"+lib.getName());
			
			File path = new File(targetFile.getParent());
			if(!path.exists()){
				path.mkdirs();
			}
			
			copyFile(sourceFile,targetFile);
		}
		
		createIsoFile(request,response,root);
		
		delFolder(tempPath);
		
	}

	public void createIsoFile(HttpServletRequest request,HttpServletResponse response,String root) throws IOException{
		Runtime runtime = Runtime.getRuntime();
		
		HttpSession session = request.getSession(true);
		String version = (String)session.getAttribute("productVersion");
		Product pro = (Product)session.getAttribute("product");
		
		String isoName = pro.getName()+"_"+version+".iso";
		if(!".".equals(root)){
			isoName = root+".iso";
		}
		Process process = runtime.exec(ultraISO+" -imax -l -d "+tempPath+" " +
 				"-volu \""+root+"\" -out "+tempPath+"\\"+isoName);
		
		try {
 			process.waitFor();
 			if(process.exitValue()!=0){
 				System.out.print("failed");
 			}
 		} catch (InterruptedException e) {
 			e.printStackTrace();
 		}
		
		ServletOutputStream out = response.getOutputStream();
		response.setHeader("Content-disposition", "attachment;filename=" + isoName);
		BufferedInputStream bis = null;
		BufferedOutputStream bos = null;
		try {
			bis = new BufferedInputStream(new FileInputStream(tempPath+"/"+isoName));
		    bos = new BufferedOutputStream(out);
		    byte[] buff = new byte[2048];
		    int bytesRead;
		    while (-1 != (bytesRead = bis.read(buff, 0, buff.length))) {
		    	bos.write(buff, 0, bytesRead);
		    }
		} catch (IOException e) {
		    throw e;
		} finally {
			out.flush();
			out.close();
		    if (bis != null)
		    	bis.close();
		    if (bos != null)
		        bos.close();
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
	
	public  void copyFile(File sourceFile, File targetFile) throws IOException {
        BufferedInputStream inBuff = null;
        BufferedOutputStream outBuff = null;
        try {
            // 新建文件输入流并对它进行缓冲
            inBuff = new BufferedInputStream(new FileInputStream(sourceFile));

            // 新建文件输出流并对它进行缓冲
            outBuff = new BufferedOutputStream(new FileOutputStream(targetFile));

            // 缓冲数组
            byte[] b = new byte[1024 * 5];
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
	
	private void removeDependence(HttpServletRequest request,HttpServletResponse response) {
		String dependenceId = request.getParameter("dependenceId");
		HttpSession session = request.getSession(true);
		String versionId = (String)session.getAttribute("productVersionId");
		ProductVersionService pVerSer = new ProductVersionService();
		
		/*LibraryService libSer = new LibraryService();
		LibraryList libList = libSer.getAllByProductId(Integer.parseInt(dependenceId));
		for(Library lib:libList){
			if(!pVerSer.containTree(Integer.parseInt(versionId), lib.getId())){
				pVerSer.deleteTree(Integer.parseInt(versionId), lib.getId());
			}
		}*/
		
		pVerSer.removeDependence(Integer.parseInt(versionId), Integer.parseInt(dependenceId));
	}

	private void getDependenceLibrary(HttpServletRequest request,HttpServletResponse response) throws IOException {
		PrintWriter out = response.getWriter();
		//HttpSession session = request.getSession(true);
		//String versionId = (String)session.getAttribute("productVersionId");
		
		//ProductVersionService pVerSer = new ProductVersionService();
		String retStr = "";
		/*
		ProductVersionList pDepList = pVerSer.getDependences(Integer.parseInt(versionId));
		LibraryService libSer = new LibraryService();
		
		
		ProductTreeList treeList = pVerSer.getTrees(Integer.parseInt(versionId));
		
		for(ProductVersion pDep:pDepList){
			LibraryList libList = libSer.getAllByProductId(pDep.getId());
			for(Library lib:libList){
				int fId = pVerSer.getFileByIss(lib.getId());
				Library fLib = libSer.getById(fId);
				Boolean flag = true;
				for(ProductTree tree:treeList){
					if(tree.getLibraryId()==fLib.getId()){
						flag = false;
						break;
					}
				}
				if(flag){
					retStr += fLib.getId()+","+fLib.getName()+"|";
				}
				
			}
		}
		
		LibraryList libList = libSer.getAllByProductId(Integer.parseInt(versionId));
		
		for(Library lib:libList){
			Boolean flag = true;
			int fId = pVerSer.getFileByIss(lib.getId());
			Library fLib = libSer.getById(fId);
			for(ProductTree tree:treeList){
				
				if(tree.getLibraryId()==fLib.getId()){
					flag = false;
					break;
				}
			}
			if(flag){
				retStr += fLib.getId()+","+fLib.getName()+"|";
			}
			
		}
		//System.out.println("dependenceLibrary:"+retStr+";");
		 * */
		 
		out.print(retStr);
		out.flush();
		out.close();
	}

	private void addDependence(HttpServletRequest request,HttpServletResponse response) throws IOException {
		PrintWriter out = response.getWriter();
		
		HttpSession session = request.getSession(true);
		String dependenceIds = request.getParameter("productIds");
		String productId = (String)session.getAttribute("productVersionId");
		String[] idList = dependenceIds.split(",");
		
		LibraryService libSer = new LibraryService();
		ProductVersionService pVerSer = new ProductVersionService();
		ProductService proSer = new ProductService();
		
		String strRet = "";
		for(String dependenceId:idList){
			if("".equals(dependenceId))
				continue;
			int depId = Integer.parseInt(dependenceId);
			System.out.println(depId);
			ProductVersion pVer = pVerSer.getVersionById(depId);
			String name = proSer.getById(pVer.getProductId()).getName();
			LibraryList libList = libSer.getAllByProductId(depId);
			for(Library lib:libList){
			
				if(pVerSer.containDependence(Integer.parseInt(productId),lib.getId())){
					ProductDependence pDep = new ProductDependence();
					pDep.setProductId(Integer.parseInt(productId));
					pDep.setDependenceId(depId);
					pDep.setDependenceName(name);
					pDep.setDependenceVersion(pVer.getVersion());
					pDep.setFileId(lib.getId());
					pDep.setFileName(lib.getName());
					pDep.setRelativePath(lib.getName());
					pVerSer.addDependence(pDep);
					
					strRet += depId+","+pDep.getDependenceVersion()+","+pDep.getDependenceName()+","+pDep.getFileId()+","+pDep.getFileName()+","+pDep.getRelativePath()+"|";
				}
			}
		}
		
		ProductDependenceList depList = pVerSer.getDependences(Integer.parseInt(productId));
		
		
		session.setAttribute("pDependenceList", depList);
		
		
		out.print(strRet);
		out.flush();
		out.close();
	}
	
	private void getProducts(HttpServletRequest request,HttpServletResponse response) throws IOException {
		PrintWriter out = response.getWriter();
		
		String categoryName = request.getParameter("categoryName");
		
		ProductCategoryService categorySer = new ProductCategoryService();
		ProductCategory category = categorySer.getByName(categoryName);
		
		ProductService proSer = new ProductService();
		ProductList proList = proSer.getAll(category.getId());
		ProductVersionService versionSer = new ProductVersionService();
		
		String strRet = "";
		for(Product pro:proList){
			ProductVersionList versionList = versionSer.getVersions(pro.getId());
			
			strRet += pro.getName()+",";
			for(ProductVersion version:versionList){
				strRet += version.getId() +"&"+version.getVersion()+",";
			}
			strRet += "|";
		}
		
		out.print(strRet);
		out.flush();
		out.close();
	}

	private void getProductCategory(HttpServletRequest request,HttpServletResponse response) throws IOException {
		PrintWriter out = response.getWriter();
		
		ProductCategoryService categorySer = new ProductCategoryService();
		ProductCategoryList categoryList = categorySer.getAll();
		
		String strRet = "";
		for(ProductCategory category:categoryList){
			strRet += category.getName()+"|";
		}
		
		out.print(strRet);
		out.flush();
		out.close();
	}

	private void getLibrary(HttpServletRequest request,HttpServletResponse response) throws IOException {
		PrintWriter out = response.getWriter();
		HttpSession session = request.getSession(true);
		
		String versionId = (String)session.getAttribute("productVersionId");
		ProductVersionService versionSer = new ProductVersionService();
		ComponentVersionList versionList = versionSer.getComponents(Integer.parseInt(versionId));
		LibraryService libSer = new LibraryService();
		ComponentService comSer = new ComponentService();
		//ComponentCategoryService cCatSer = new ComponentCategoryService();
		String strRet ="";
		for(ComponentVersion comVersion:versionList){
			Component com = comSer.getById(comVersion.getComponentId());
			String location = versionSer.getComponentLocation(Integer.parseInt(versionId), comVersion.getId());
			//ComponentCategory cCategory = cCatSer.getById(com.getCategoryId());
			strRet += com.getName()+","+comVersion.getVersion()+",";
			LibraryList libList = libSer.getAllByComponentId(comVersion.getId());
			for(Library lib:libList){
				if(location.equals(".")){
					strRet += lib.getName()+",";
				}else{
					strRet += location + "/" + lib.getName()+",";
				}
				strRet += lib.getId()+",";
			}
			strRet += "|";
		}
		
		out.print(strRet);
		out.flush();
		out.close();
	}


	private void getLastVersion(HttpServletRequest request,HttpServletResponse response) throws IOException {
		PrintWriter out = response.getWriter();
		
		HttpSession session = request.getSession(true);
		
		ProductVersionList versionList = (ProductVersionList)session.getAttribute("productVersionList");
		
		String version = versionList.get(versionList.size()-1).getVersion();
		
		out.println(version);
		out.flush();
		out.close();
	}

	private void selectComponent(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException {
		String versionId = request.getParameter("componentId");
		
		ComponentCategoryService categorySer = new ComponentCategoryService();
		ComponentCategoryList categoryList = categorySer.getAll();
		
		ComponentVersionService versionSer = new ComponentVersionService();
		ComponentService comSer = new ComponentService();
		LibraryService libSer = new LibraryService();
		
		LibraryList libList = libSer.getAllByComponentId(Integer.parseInt(versionId));
		ComponentVersion version = versionSer.getVersionById(Integer.parseInt(versionId));
		Component com = comSer.getById(version.getComponentId());
		ComponentCategory category = categorySer.getById(com.getCategoryId());
		ComponentList comList = comSer.getAll(category.getId());
		ComponentVersionList versionList = versionSer.getVersions(com.getId());
		
		
		ComponentVersionList versionDepList = versionSer.getDependences(Integer.parseInt(versionId));
		ComponentList comDepList = new ComponentList();
		ComponentCategoryList catDepList = new ComponentCategoryList();
		//ComponentService comSer = new ComponentService();
		//ComponentCategoryService comCatSer = new ComponentCategoryService();
		for(ComponentVersion cVersion:versionDepList){
			Component comDep = comSer.getById(cVersion.getComponentId());
			ComponentCategory cCategory = categorySer.getById(comDep.getCategoryId());
			
			comDepList.add(comDep);
			catDepList.add(cCategory);
		}
		
		ProductService proSer = new ProductService();
		ProductCategoryService pCategorySer = new ProductCategoryService();
		ProductVersionList proVersionList = versionSer.getProducts(Integer.parseInt(versionId));
		ProductList proList = new ProductList();
		ProductCategoryList pCategoryList = new ProductCategoryList();
		
		for(ProductVersion proVersion:proVersionList){
			Product pro = proSer.getById(proVersion.getProductId());
			ProductCategory pCategory = pCategorySer.getById(pro.getCategoryId());
			
			proList.add(pro);
			pCategoryList.add(pCategory);
		}
		HttpSession session = request.getSession();
		session.setAttribute("componentCategoryList", categoryList);
		session.setAttribute("componentCategory", category);
		session.setAttribute("componentList", comList);
		session.setAttribute("component", com);
		session.setAttribute("componentVersionList", versionList);
		session.setAttribute("componentLibraryList", libList);
		session.setAttribute("versionId", versionId);
		session.setAttribute("componentVersion", version.getVersion());
		session.setAttribute("isFlag", "no");
		session.setAttribute("isTree1", "0");
		
		session.setAttribute("versionDependenceList", versionDepList);
		session.setAttribute("componentDependenceList", comDepList);
		session.setAttribute("categoryDependenceList", catDepList);
		
		session.setAttribute("productCategoryList", pCategoryList);
		session.setAttribute("productList", proList);
		session.setAttribute("productVersionList", proVersionList);
		//request.getRequestDispatcher("componentLibraryPage.jsp").forward(request, response);
		
	}

	private void deleteComponent(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException {
		String componentId = request.getParameter("componentId");
		
		ProductVersionService versionSer = new ProductVersionService();
		HttpSession session = request.getSession(true);
		String productId = (String)session.getAttribute("productVersionId");
		
		if(!versionSer.containsComponent(Integer.parseInt(productId), Integer.parseInt(componentId))){
			versionSer.deleteComponent(Integer.parseInt(productId),Integer.parseInt(componentId));
		}
		
		ComponentVersionList versionList = versionSer.getComponents(Integer.parseInt(productId));
		
		ComponentCategoryList categoryList = new ComponentCategoryList();
		ComponentList comList = new ComponentList();
		StringList cLocationList = new StringList();
		ComponentCategoryService categorySer = new ComponentCategoryService();
		ComponentService comSer = new ComponentService();
		for(ComponentVersion version:versionList){
			String location = versionSer.getComponentLocation(Integer.parseInt(productId), version.getId());
			Component com = comSer.getById(version.getComponentId());
			ComponentCategory category = categorySer.getById(com.getCategoryId());
			
			cLocationList.add(location);
			comList.add(com);
			categoryList.add(category);
		}
		
		session.setAttribute("componentLocationList", cLocationList);
		session.setAttribute("categoryList", categoryList);
		session.setAttribute("componentList", comList);
		
		session.setAttribute("componentVersionList", versionList);
		request.getRequestDispatcher("productComponentPage.jsp").forward(request, response);
	}

	public void navigation(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException{
		
		String state = request.getParameter("state");
		if("external".equals(state)){
			request.getRequestDispatcher("externalProductPage.jsp").forward(request, response);
		}else if("internal".equals(state)){
			request.getRequestDispatcher("productComponentPage.jsp").forward(request, response);
		}
		
	}
	
	public void addComponent(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException {
		String componentIds = request.getParameter("componentIds");
		
		String[] idList = componentIds.split(",");
		
		ProductVersionService versionSer = new ProductVersionService();
		HttpSession session = request.getSession(true);
		String productId = (String)session.getAttribute("productVersionId");
		
		
		for(String componentId:idList){
			if(!componentId.equals("")&&versionSer.containsComponent(Integer.parseInt(productId), Integer.parseInt(componentId))){
				versionSer.addComponent(Integer.parseInt(productId), Integer.parseInt(componentId));
			}
		}
		ComponentVersionList versionList = versionSer.getComponents(Integer.parseInt(productId));
		
		ComponentCategoryList categoryList = new ComponentCategoryList();
		ComponentList comList = new ComponentList();
		StringList cLocationList = new StringList();
		ComponentCategoryService categorySer = new ComponentCategoryService();
		ComponentService comSer = new ComponentService();
		for(ComponentVersion version:versionList){
			String location = versionSer.getComponentLocation(Integer.parseInt(productId), version.getId());
			Component com = comSer.getById(version.getComponentId());
			ComponentCategory category = categorySer.getById(com.getCategoryId());
			
			cLocationList.add(location);
			comList.add(com);
			categoryList.add(category);
		}
		
		session.setAttribute("componentLocationList", cLocationList);
		session.setAttribute("categoryList", categoryList);
		session.setAttribute("componentList", comList);
		
		session.setAttribute("componentVersionList", versionList);
		request.getRequestDispatcher("productComponentPage.jsp").forward(request, response);
	}

	public void getComponents(HttpServletRequest request,HttpServletResponse response) throws IOException {
		PrintWriter out = response.getWriter();
		
		String categoryName = request.getParameter("categoryName");
		
		ComponentCategoryService categorySer = new ComponentCategoryService();
		ComponentCategory category = categorySer.getByName(categoryName);
		
		ComponentService comSer = new ComponentService();
		ComponentList comList = comSer.getAll(category.getId());
		ComponentVersionService versionSer = new ComponentVersionService();
		
		String strRet = "";
		for(Component com:comList){
			ComponentVersionList versionList = versionSer.getVersions(com.getId());
			
			strRet += com.getName()+",";
			for(ComponentVersion version:versionList){
				strRet += version.getId() +"&"+version.getVersion()+",";
			}
			strRet += "|";
		}
		
		out.print(strRet);
		out.flush();
		out.close();
		
	}

	public void getComponentCategory(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		ComponentCategoryService categorySer = new ComponentCategoryService();
		ComponentCategoryList categoryList = categorySer.getAll();
		
		String strRet = "";
		for(ComponentCategory category:categoryList){
			strRet += category.getName()+"|";
		}
		
		out.print(strRet);
		out.flush();
		out.close();
	}
	
	public void select(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		String versionId = request.getParameter("versionId");
		ProductVersionService versionSer = new ProductVersionService();
		ComponentVersionList versionList = versionSer.getComponents(Integer.parseInt(versionId));
		ProductVersion pVersion = versionSer.getVersionById(Integer.parseInt(versionId));
		
		HttpSession session = request.getSession(true);
		session.setAttribute("productVersionId", versionId);
		ProductService proSer = new ProductService();
		Product pro = proSer.getById(pVersion.getProductId());
		int state = pro.getState();
		//System.out.println(state);
		if(state==0){
			ComponentCategoryList categoryList = new ComponentCategoryList();
			ComponentList comList = new ComponentList();
			StringList cLocationList = new StringList();
			ComponentCategoryService categorySer = new ComponentCategoryService();
			ComponentService comSer = new ComponentService();
			for(ComponentVersion version:versionList){
				String location = versionSer.getComponentLocation(Integer.parseInt(versionId), version.getId());
				Component com = comSer.getById(version.getComponentId());
				ComponentCategory category = categorySer.getById(com.getCategoryId());
				
				cLocationList.add(location);
				comList.add(com);
				categoryList.add(category);
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
			
			session.setAttribute("categoryList", categoryList);
			session.setAttribute("componentList", comList);
			session.setAttribute("componentVersionList", versionList);
			session.setAttribute("componentLocationList", cLocationList);
			
			session.setAttribute("productVersion", pVersion.getVersion());
			
			session.setAttribute("issFileList", issFileList);
			session.setAttribute("setupFileList", setupFileList);
			
			session.setAttribute("pDependenceList", pDepVerList);
			
			session.setAttribute("isProduct", "no");
			//session.setAttribute("tabId", "0");
			request.getRequestDispatcher("productComponentPage.jsp").forward(request, response);
		}else if(state==1){
			LibraryService libSer = new LibraryService();
			LibraryList libList = libSer.getAllByProductId(Integer.parseInt(versionId));
			
			session.setAttribute("productLibraryList", libList);
			session.setAttribute("productVersion", pVersion.getVersion());
			session.setAttribute("isProduct", "no");
			
			request.getRequestDispatcher("externalProductPage.jsp").forward(request, response);
		}
		
	}
	
	public void create(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String productName = request.getParameter("productName");
		String productId = request.getParameter("productId");
		
		ProductVersion pVersion = new ProductVersion();
		
		String version = request.getParameter("version");
		String description = request.getParameter("description");
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date date = new Date();
		String time = df.format(date);
		Timestamp created = Timestamp.valueOf(time);
		//Timestamp modified = Timestamp.valueOf(time);
		
		pVersion.setVersion(version);
		pVersion.setDescription(description);
		pVersion.setCreated(created);
		pVersion.setProductId(Integer.parseInt(productId));

		HttpSession session = request.getSession(true);
		ProductCategory category = (ProductCategory)session.getAttribute("productCategory");
		
		ProductVersionService verSer = new ProductVersionService();
		if(verSer.contains(category.getName(), productName, version)){
			out.print("<script language='javascript'>alert('the repository is exist');</script>");
			
		}else if(version==""||version==null)
		{
			out.print("<script language='javascript'>alert('the name is empty');</script>");
		}else
		{
			Boolean ok = verSer.create(pVersion);
			if(!ok)
			{
				out.write("Create Product Version error");
				out.flush();
				out.close();
			}else{
				int versionId = verSer.getIdByVersion(category.getName(),productName,version);
				int pid = -1;
				ProductService proSer = new ProductService();
				ProductList proList = proSer.getAll(category.getId());
				for(int i=0;i<proList.size();i++){
					if(proList.get(i).getId()==Integer.parseInt(productId))
						pid = i+1;
				}
				
				String strRet = versionId+"|"+version+"|"+description+"|"+created+"|"+pid;
				out.println(strRet);
				out.flush();
				out.close();
			}
		
		}
		
		ProductVersionList versionList = verSer.getVersions(Integer.parseInt(productId));
		session.setAttribute("productVersionList", versionList);
	}

	public void delete(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String versionId = request.getParameter("versionId");

		ProductVersionService versionSer = new ProductVersionService();
		
		ProductVersion proVersion = versionSer.getVersionById(Integer.parseInt(versionId));
		int proId = proVersion.getProductId();
		versionSer.delete(Integer.parseInt(versionId));
		ProductVersionList versionList = versionSer.getVersions(proId);
		HttpSession session = request.getSession(true);
		ProductList proList = (ProductList)session.getAttribute("productList");
		int index = -1;
		for(int i=0;i<proList.size();i++){
			if(proId==proList.get(i).getId()){
				index = i+1;
			}
		}
		
		session.setAttribute("productVersionList", versionList);
		
		out.println(index);
		out.flush();
		out.close();
	}

}
