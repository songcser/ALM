package com.prolambda.controller;

import com.prolambda.dal.LibraryDAL;
import com.prolambda.model.Library;
import com.prolambda.model.LibraryList;

public class LibraryService {

	public Boolean create(Library lib)
	{
		LibraryDAL libDAL = new LibraryDAL();
		return libDAL.create(lib);
	}
	
	public Boolean delete(int id)
	{
		LibraryDAL libDAL = new LibraryDAL();
		return libDAL.delete(id);
	}
	
	public Boolean deleteByBuildId(int buildId){
		LibraryDAL libDAL = new LibraryDAL();
		return libDAL.deleteByBuildId(buildId);
	}
	
	
	
	public Boolean update(Library lib)
	{
		LibraryDAL libDAL = new LibraryDAL();
		return libDAL.update(lib);
	}
	
	public LibraryList getAllByBuildId(int buildId)
	{
		LibraryDAL libDAL = new LibraryDAL();
		
		return libDAL.getAllByBuildId(buildId);
	}
	
	public LibraryList getAllByComponentId(int componentId)
	{
		LibraryDAL libDAL = new LibraryDAL();
		
		return libDAL.getAllByComponentId(componentId);
	}
	
	public Library getById(int id)
	{
		LibraryDAL libDAL = new LibraryDAL();
		
		return libDAL.getById(id);
	}
	
	public LibraryList getAllByProductId(int productId){
		LibraryDAL libDAL = new LibraryDAL();
		
		return libDAL.getAllByProductId(productId);
	}

	public int getIdByFileName(String fileName){
		LibraryDAL libDAL = new LibraryDAL();
		return libDAL.getIdByFileName(fileName);
	}
}
