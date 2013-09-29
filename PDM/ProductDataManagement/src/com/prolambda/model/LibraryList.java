package com.prolambda.model;

import java.util.ArrayList;

@SuppressWarnings("serial")
public class LibraryList extends ArrayList<Library>{

	public ArrayList<String []> toArrayList()
	{
		ArrayList<String []> al = new ArrayList<String []>();
		
		for(int i=0;i<this.size();i++)
		{
			String temp[] = new String[5];
			Library lib = this.get(i);
			temp[0] = lib.getId()+"";
			temp[1] = lib.getName();
			temp[2] = lib.getDescription();
			temp[3] = lib.getType();
			temp[4] = lib.getBuildId()+"";
		
			al.add(temp);
		}
		
		return al;
	}
}
