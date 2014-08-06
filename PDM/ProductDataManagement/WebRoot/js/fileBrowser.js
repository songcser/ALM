function Folder(id,name){
	
	this.id = id;
	this.name = name;
	this.path = "/";
	this.folders = [];
	this.files = [];
	this.pid = -1;
	this.state = 0;
};

function File(id,name){
	this.id = id;
	this.name = name;
	this.path ='/';
	this.state = 0;
	//this.ext;
};

function FileBrowser(objName,targetId){
	//alert(objName);
	this.obj = objName;
	this.targetId = targetId;
	//alert(objName);
	this.folder = new Folder(0,'/');
	this.layer = 0;
	this.maxLayer = 0;
	this.folderCount = 0;
	//this.fileCount = 0;
	this.tempFolder = this.folder;
	this.files = [];
	this.selectedFiles = [];
	this.fullPath = '/';
	this.selectedFile = '';
	this.checkbox = false;
	//this.ext;
	
	this.icon = {
			folder			: 'images/folder.gif',
			file			: 'images/page.gif',
			checked			: 'images/checkbox_checked.png',
			tristate		: 'images/checkbox_tristate.png',
			unchecked		: 'images/checkbox_unchecked.png'
	};
};

FileBrowser.prototype.add = function(id,path){
	
	//alert(id);
	var dir = new Array();
	dir = path.split('/');
	this.layer = 0;
	this.maxLayer = dir.length-1;
	//alert(this.maxLayer);
	this.addFolder(id,dir,this.folder);
	
};

FileBrowser.prototype.addFile = function(id,name){
	//alert(name);
	//this.fileCount++;
	//alert(name);
	for(var i=0;i<this.tempFolder.files.length;i++){
		if(this.tempFolder.files[i].name==name){
			//alert(name);
			this.tempFolder.files[i].id = id;
			
			this.showFolder(this.tempFolder);
			return;
		}
	}
	var file = new File(id,name);
	file.path = this.fullPath;
	//file.ext=ext;
	this.files[this.files.length]=file;
	//alert(this.tempFolder.files.length);
	this.tempFolder.files[this.tempFolder.files.length] = file;
	//alert(this.tempFolder.files.length);
	var tmpId = this.tempFolder.id;
	if(tmpId>0){
		this.changeParentState(this.tempFolder);
		this.findFolder(tmpId,this.folder);
	}
	
	this.showFolder(this.tempFolder);
};

FileBrowser.prototype.addFolder = function(id,dir,folder){
	
	//alert(this.layer+" : "+this.maxLayer);
	if(this.layer>=this.maxLayer){
		//alert(dir[this.layer]);
		//alert(id);
		var file = new File(id,dir[this.layer]);
		//file.ext = this.ext;
		for(var i=0;i<this.maxLayer;i++){
			file.path += dir[i]+"/";
		}
		//alert(this.maxLayer);
		this.files[this.files.length] = file;
		folder.files[folder.files.length] = file;
		return;
	}
	
	var isExist = false;
	
	for(var i=0;i<folder.folders.length;i++){
		if(folder.folders[i].name==dir[this.layer]){
			//alert(this.layer);
			//alert(folder.folders[i].path);
			this.layer++;
			this.addFolder(id,dir,folder.folders[i]);
			isExist = true;
		}	
	}
	
	if(!isExist){
		this.folderCount++;
		var newFolder = new Folder(this.folderCount,dir[this.layer]);
		for(var i=0;i<=this.layer;i++){
			
			newFolder.path += dir[i]+"/";
			//alert(newFolder.path);
		}
		//alert(newFolder.path);
		newFolder.pid = folder.id;
		//alert(newFolder.pid);
		folder.folders[folder.folders.length]= newFolder;
		this.layer++;
		this.addFolder(id,dir,newFolder);
	}
	
};

FileBrowser.prototype.remove = function(){
	var tmpId = this.tempFolder.id;
	this.removeFile(this.folder);
	if(tmpId==0){
		this.showFolder(this.folder);
	}else{
		this.showFolder(this.tempFolder);
	}
	
	
}

FileBrowser.prototype.removeFile = function(folder){
	var fileSize = folder.files.length;
	var folderSize = folder.folders.length;
	for(var i=0;i<fileSize;i++){
		if(folder.files[i].state==1){
			var j=i;
			while(j<fileSize-1){
				folder.files[j]=folder.files[j+1];
				j++;
			}
			folder.files.length--;
			fileSize--;
			i--;
		}
	}
	
	for(var i=0;i<folderSize;i++){
		if(folder.folders[i].state==2){
			this.removeFile(folder.folders[i]);
		}else if(folder.folders[i].state==1){
			var  index = this.fullPath.indexOf(folder.folders[i].path);
			if(index==0){
				index = -1;
				index = this.tempFolder.path.indexOf(folder.path);
				//alert(folder.path);
				if(index==0){
					this.tempFolder = folder;
					this.fullPath = folder.path;
					//alert("ss");
				}
				
				//alert(folder.folders[i].path);
			}
			
			var j=i;
			while(j<folderSize){
				folder.folders[j]=folder.folders[j+1];
				j++;
			}
			folder.folders.length--;
			folderSize--;
			
		}
	}
	
	var tmpId = this.tempFolder.id;
	if(folder.id>0){
		this.changeParentState(folder);
		this.findFolder(tmpId,this.folder);
	}
}

FileBrowser.prototype.show = function(){
	
	this.showFolder(this.folder);
	//this.test();
	
};

FileBrowser.prototype.showFolder = function(folder){
	var targetDIV = document.getElementById(this.targetId);
	//alert(targetDIV);
	
	//this.fullPath += folder.path+"/";
	
	var obj = document.getElementById("fullPath");
	if(obj){
		obj.value = this.fullPath;
	}
	
	var str = '<table width="100%" border=1 CELLPADDING="0" CELLSPACING="0" bgcolor="#fff">';
	//alert(folder.folders.length);
	for(var i=0;i<folder.folders.length;i++){
		var node = folder.folders[i];
		str += '<tr bgcolor="#fff"><td>';
		if(this.checkbox){
			str += '<a href="javascript: '+ this.obj +'.changeFolderSelected('+node.id+'); "><img src="';
			if(node.state==0){
				str += this.icon.unchecked;
			}else if(node.state==1){
				str += this.icon.checked;
			}else if(node.state==2){
				str += this.icon.tristate;
			}
			str += '"/></a>';
		}
		str +='<a href="javascript: '+ this.obj +'.getFolder('+folder.folders[i].id+'); "><img src="'+this.icon.folder+'" />';
		str += folder.folders[i].name;
		str += '</a></td></tr>';
		//alert(str);
	}
	//alert(this.folder.files.length);
	for(var i=0;i<folder.files.length;i++){
		var node = folder.files[i];
		str += '<tr>';
		str += '<td><div id = "'+folder.files[i].id+'" onclick="'+this.obj+'.selectfile(this)">';
		if(this.checkbox){
			
			str += '<a href="javascript: '+ this.obj +'.changeFileSelected('+node.id+'); "><img src="';
			if(node.state==0){
				str += this.icon.unchecked;
			}else if(node.state==1){
				str += this.icon.checked;
			}else if(node.state==2){
				str += this.icon.tristate;
			}
			str += '"/></a>';
		}
		str += '<img src="'+this.icon.file+'" />';
		str += folder.files[i].name;
		str += '</div></td></tr>';
	}
	str += '</table>';
	//alert(str);
	targetDIV.innerHTML = str;
};

FileBrowser.prototype.changeFolderSelected = function(id){
	var folder;
	//alert(this.tempFolder.id+"---"+this.folder.id);
	//alert(this.tempFolder.id);
	for(var i=0;i<this.tempFolder.folders.length;i++){
		folder = this.tempFolder.folders[i];
		if(folder.id==id){
			break;
		}
	}
	if(folder.state==0||folder.state==2){
		folder.state = 1;
		this.changeState(folder,1);
	}else if(folder.state==1){
		folder.state = 0;
		this.changeState(folder,0);
	}
	
	var tmpId = this.tempFolder.id;
	if(tmpId>0){
		this.changeParentState(this.tempFolder);
		this.findFolder(tmpId,this.folder);
	}
	
	//alert(this.tempFolder.id+"---"+this.folder.id);
	this.showFolder(this.tempFolder);
}

FileBrowser.prototype.changeFileSelected = function(id){
	//alert(id);
	
	for(var i=0;i<this.tempFolder.files.length;i++){
		var file = this.tempFolder.files[i];
		if(file.id==id){
			//alert(file.id);
			if(file.state==0){
				this.selectedFiles[this.selectedFiles.length]=file;
				file.state = 1;
				//alert(this.selectedFiles.length);
			}else if(file.state==1){
				var length = this.selectedFiles.length;
				for(var i=0;i<length;i++){
					var selectedFile = this.selectedFiles[i];
					if(selectedFile.id==file.id){
						while(i<length-1){
							this.selectedFiles[i] = this.selectedFiles[i+1];
							i++;
						}
						this.selectedFiles.length--;
					}
				}
				file.state = 0;
			}
			break;
		}
	}
	//alert(file.state);
	
	
	var tmpId = this.tempFolder.id;
	if(tmpId>0){
		this.changeParentState(this.tempFolder);
		this.findFolder(tmpId,this.folder);
	}
	
	
	this.showFolder(this.tempFolder);
}

FileBrowser.prototype.changeParentState = function(folder){

	var flag = false;
	var flag1 = false;
	var flag0 = false;
	//alert(folder.id);
	for(var i=0;i<folder.folders.length;i++){
		var node = folder.folders[i];
		if(node.state==2){
			flag = true;
			break;
		}else if(node.state==1){
			flag1 = true;
		}else if(node.state==0){
			flag0 = true;
		}
	}
	for(var i=0;i<folder.files.length;i++){
		var node = folder.files[i];
		if(node.state==1){
			flag1 = true;
		}else if(node.state==0){
			flag0 = true;
		}
	}
	if(flag){
		//alert("ss2");
		folder.state = 2;
	}else{
		if(flag1&&flag0){
			//alert(folder.id);
			folder.state = 2;
		}else if(flag1&&!flag0){
			folder.state = 1;
		}else if(!flag1&&flag0){
			folder.state = 0;
		}
	}
	//alert(folder.id+'------'+folder.pid);
	if(folder.pid==0){
		return;
	}else{
		//alert("pid"+folder.pid);
		this.findFolder(folder.pid,this.folder);
		this.changeParentState(this.tempFolder);
	}
	
	
}

FileBrowser.prototype.changeState = function(folder,state){
	for(var i=0;i<folder.folders.length;i++){
		var node = folder.folders[i];
		node.state = state;
		this.changeState(node, state);
	}
	
	for(var i=0;i<folder.files.length;i++){
		var node = folder.files[i];
		if(state==0){
			var length = this.selectedFiles.length;
			for(var j=0;j<length;j++){
				var selectedFile = this.selectedFiles[j];
				if(selectedFile.id==node.id){
					while(j<length-1){
						this.selectedFiles[j] = this.selectedFiles[j+1];
						j++;
					}
					this.selectedFiles.length--;
				}
			}
			node.state = 0;
		}else if(state==1){
			this.selectedFiles[this.selectedFiles.length]=node;
			node.state = 1;
		}
		
		
	}
}

FileBrowser.prototype.getFolder = function(id){
	//alert(id);
	if(id==0||id==-1){
		this.tempFolder = this.folder;
		this.fullPath = "/";
		this.showFolder(this.folder);
	}else{
		this.findFolder(id,this.folder);
		//alert(this.fullPath);
		//alert(this.tempFolder.id);
		
		this.fullPath += this.tempFolder.name+"/";
		//alert(folder.files.length);
		this.showFolder(this.tempFolder);
	}
	
};

FileBrowser.prototype.findFolder = function(id,folder){
	
	
	for(var i=0;i<folder.folders.length;i++){
		if(folder.folders[i].id==id){
			//alert(folder.folders[i].files.length);
			this.tempFolder = folder.folders[i];
			//alert(this.tempFolder.pid);
		}else{
			this.findFolder(id,folder.folders[i]);
		}
	}
	
};

FileBrowser.prototype.selectfile = function(obj){
	//alert(this.tempFolder.files[0].name);
	for(var i=0;i<this.tempFolder.files.length;i++){
		var oldObj = document.getElementById(this.tempFolder.files[i].id);
		oldObj.style.background = "#fff";
	}
	this.selectedFile = obj.id;
	
	obj.style.background = "#63B8FF";
	//alert(this.selectedFile);
}

FileBrowser.prototype.getFullPath = function(){
	return this.fullPath;
};

FileBrowser.prototype.getSelectedFileId = function(){
	return this.selectedFile;
}

FileBrowser.prototype.getSelectedFile = function(){
	return this.selectedFiles;
	
}

FileBrowser.prototype.goBack = function(){
	//alert(this.fullPath);
	//alert(this.tempFolder.pid);
	
	var str = this.fullPath.substring(0, this.fullPath.length-1);
	//alert(str);
	var index = str.lastIndexOf('/');
	str = str.substring(0, index);
	index = str.lastIndexOf('/');
	this.fullPath = str.substring(0, index+1);
	//alert(this.fullPath);
	this.getFolder(this.tempFolder.pid);
	//this.goHome();
};

FileBrowser.prototype.goHome = function(){
	//alert("sss");
	this.fullPath = '/';
	this.tempFolder = this.folder;
	this.show();
};

FileBrowser.prototype.createFolder = function(name){
	this.folderCount++;
	var newFolder = new Folder(this.folderCount,name);
	newFolder.path = this.fullPath+name;
	newFolder.pid = this.tempFolder.id;
	//alert(name);
	this.tempFolder.folders[this.tempFolder.folders.length] = newFolder;
	
	this.showFolder(this.tempFolder);
};

FileBrowser.prototype.getFiles = function(){
	return this.files;
}

FileBrowser.prototype.test = function(){
	var targetDIV = document.getElementById(this.targetID);
	//alert(targetDIV);
	targetDIV.innerHTML = '<a href="javascript: alert(\"test\")">test</a>';
};

FileBrowser.prototype.tests = function(path){
	alert(path);
};