package com.prolambda.model;

import java.util.ArrayList;

@SuppressWarnings("serial")
public class RepositoryList extends ArrayList<Repository>{
	
	public ArrayList<String []> toArrayList()
	{
		ArrayList<String []> al = new ArrayList<String []>();
		
		for(int i=0;i<this.size();i++)
		{
			String temp[] = new String[5];
			Repository rep = this.get(i);
			temp[0] = rep.getId()+"";
			temp[1] = rep.getName();
			temp[2] = rep.getDescription();
			temp[3] = rep.getCreated().toString();
			temp[4] = rep.getModified().toString();
			al.add(temp);
		}
		
		return al;
	}
}
