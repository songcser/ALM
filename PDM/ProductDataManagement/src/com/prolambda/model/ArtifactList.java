package com.prolambda.model;

import java.util.ArrayList;

@SuppressWarnings("serial")
public class ArtifactList extends ArrayList<Artifact>{

	public ArrayList<String []> toArrayList()
	{
		ArrayList<String []> al = new ArrayList<String []>();
		
		for(int i=0;i<this.size();i++)
		{
			String temp[] = new String[6];
			Artifact art = this.get(i);
			temp[0] = art.getId()+"";
			temp[1] = art.getName();
			temp[2] = art.getCount()+"";
			temp[3] = art.getStarted().toString();
			temp[4] = art.getLasttime().toString();
			temp[5] = art.getRepId()+"";
			al.add(temp);
		}
		
		return al;
	}
}
