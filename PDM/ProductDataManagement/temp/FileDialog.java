package com.prolambda.applet;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.event.TreeSelectionEvent;

public class FileDialog extends JFrame implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -578568161553206330L;
	//private JPanel pnlMain; 
	private JTextField txtfile; 
	private JButton btnSelect; 
	private JFileChooser fc = new JFileChooser(); 
	
	private String root;
	private JPanel topPanel;
	public FileDialog(){
		this.setLayout(new GridLayout(1,1));
		
		topPanel=new JPanel(); 
	    this.getContentPane().add(topPanel); 
	    txtfile=new JTextField(10); 
	    btnSelect =new JButton("select"); 
	    btnSelect.addActionListener(this); 
	    topPanel.add(txtfile); 
	    topPanel.add(btnSelect);
	    
	    
	}
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
		if(e.getSource()==btnSelect){ 
			 /* 
			     这是尤为重要的。因为JFileChooser默认的是选择文件，而需要选目录。 
			     故要将DIRECTORIES_ONLY装入模型 
			 另外，若选择文件，则无需此句 
			 */ 
			 fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY); 
			 int intRetVal = fc.showOpenDialog(this); 
			 if( intRetVal == JFileChooser.APPROVE_OPTION){ 
				 root = fc.getSelectedFile().getPath();
				 txtfile.setText(root);
				 
			 }
			 /*
			 try{
				TreeNode rootNode = new TreeNode(".",root);
				top=new DefaultMutableTreeNode(rootNode);
				
				createTree(root,top);
				tree = new JTree(top);
				tree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
				tree.putClientProperty("JTree.lineStyle","Angled");
				
				tree.setShowsRootHandles(true);
				tree.setEditable(false);
				tree.addTreeSelectionListener( this );
				IconRender render=new IconRender();
				tree.setCellRenderer(render);

				//topPanel=new Panel(new BorderLayout());
				topPanel.add(tree);
				//this.add(topPanel);
			}catch(Exception ex){
				ex.printStackTrace();
			}*/
		}
	}
	/*
	public void createTree(String filepath,DefaultMutableTreeNode rootNode){
		File file = new File(filepath);
		if (!file.isDirectory()) {
		    
		    String path = file.getAbsolutePath();
		    String name = file.getName();
		    
		    TreeNode node = new TreeNode(name,path);
		    rootNode.add(new DefaultMutableTreeNode(node));
		    //files += path.substring(temp.length()+1)+"|";
		    
		        
		} else if (file.isDirectory()) {
		    //System.out.println("文件夹");
		    String[] filelist = file.list();
		    for (int i = 0; i < filelist.length; i++) {
		        File readfile = new File(filepath + "/" + filelist[i]);
		        if (!readfile.isDirectory()) {
		           // System.out.println("path=" + readfile.getPath());
		           // System.out.println("absolutepath="
		           //                             + readfile.getAbsolutePath());
		           // System.out.println("name=" + readfile.getName());

		            String path = readfile.getAbsolutePath();
		            String name = readfile.getName();
				    
				    TreeNode node = new TreeNode(name,path);
				    rootNode.add(new DefaultMutableTreeNode(node));
				    //files += path.substring(temp.length()+1)+"|";
				    
		        } else if (readfile.isDirectory()) {
		        	String path = readfile.getAbsolutePath();
		            String name = readfile.getName();
				    
				    TreeNode node = new TreeNode(name,path);
				    DefaultMutableTreeNode fatherNode = new DefaultMutableTreeNode(node);
				    rootNode.add(fatherNode);
		        	createTree(filepath + "/" + filelist[i],fatherNode);
		        }
		   }
		}
	}
	*/
	public void valueChanged(TreeSelectionEvent e) {
		// TODO Auto-generated method stub
		
	}
	

}
