package com.prolambda.model;

import java.util.ArrayList;

@SuppressWarnings("serial")
public class BuildList extends ArrayList<Build>{

	public ArrayList<String []> toArrayList()
	{
		ArrayList<String []> al = new ArrayList<String []>();
		
		for(int i=0;i<this.size();i++)
		{
			String temp[] = new String[9];
			Build build = this.get(i);
			temp[0] = build.getId()+"";
			temp[1] = build.getNumber()+"";
			temp[2] = build.getStarted().toString();
			temp[3] = build.getDuration()+"";
			temp[4] = build.getSourcePath();
			temp[5] = build.getSourceVersion();
			temp[6] = build.getEnvironment();
			temp[7] = build.getArtifactId()+"";
			temp[8] = build.getLog();
			al.add(temp);
		}
		
		return al;
	}
}
