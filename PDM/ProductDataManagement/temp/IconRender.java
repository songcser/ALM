package com.prolambda.applet;

import java.awt.Component;

import javax.swing.ImageIcon;
import javax.swing.JTree;
import javax.swing.tree.DefaultTreeCellRenderer;

public class IconRender extends DefaultTreeCellRenderer{

	private static final long serialVersionUID = 2237187354812040721L;

	public static final ImageIcon leafSelectedIcon = new ImageIcon("images/page.gif"); 

	public static final ImageIcon leafUnSelectedIcon = new ImageIcon("images/page.gif"); 

	public static final ImageIcon folderOpen = new ImageIcon("images/folderopen.gif"); 

	public static final ImageIcon folderClose = new ImageIcon("images/folder.gif"); 
	
	public Component getTreeCellRendererComponent(JTree tree,Object value,boolean selected,boolean expanded, 
		boolean leaf, int row,boolean hasFocus) { 
		super.getTreeCellRendererComponent(tree,value, selected, expanded, leaf, row, hasFocus); 

		if (leaf && selected) { 
			setIcon(IconRender.leafSelectedIcon); 
		} 
		else if (leaf) { 
			setIcon(IconRender.leafUnSelectedIcon); 
		} 
		return this; 
	}
	public IconRender() { 
		super(); 
		if((leafSelectedIcon != null)&&(leafUnSelectedIcon != null)) 
		System.out.println("IconRender:trace"); 

		setLeafIcon(leafUnSelectedIcon); 

		setOpenIcon(folderOpen); 

		setClosedIcon(folderClose); 

	} 
}
