/*--------------------------------------------------

	dTree 2.05 | www.destroydrop.com/javascript/tree/

	Rewrited by xiaosilent@gmail.com , xiangdingdang.com

	Last updated at 2007-4-28 16:32:05

	
---------------------------------------------------*/



// Node object

function Node(id, pid, name, url, title, target, icon, iconOpen, open) {

	this.id = id;

	this.pid = pid;

	this.name = name;

	this.url = url;

	this.title = title;

	this.target = target;

	this.icon = icon;

	this.iconOpen = iconOpen;
	
	this._fc = false;

	this._io = open || false;

	this._is = false;

	this._ls = false;

	this._hc = false;

	this._ai = 0;

	this._p;

};



/**
* dTree  
*
* Edited by xiaosilent.
* 
* objName: name of dTree object.
* targetID: the id of your container,which you used to display the tree
* type: which kind of category are you doing with ? It must be one of these  "goods" , "vendor" and "consumer" ,this is just for xiaosilent's Sales Management System.
*
*/
function dTree(objName,targetID,flag) {
	

	this.config = {
		

		target				: 'contentFrame',
		
		// xiaosilent changed it to be false.
		folderLinks			: true,

		useSelection		: true,

		useCookies			: false,

		useLines				: true,

		useIcons				: true,

		useStatusText		: false,

		closeSameLevel	: false,

		inOrder				: false

	}
		
	// xiaosilent changed this to his own path.
	this.icon = {
			

		root				: 'images/base.gif',

		folder			: 'images/folder.gif',

		folderOpen	: 'images/folderopen.gif',

		node				: 'images/page.gif',

		empty				: 'images/empty.gif',

		line				: 'images/line.gif',

		join				: 'images/join.gif',

		joinBottom	: 'images/joinbottom.gif',

		plus				: 'images/plus.gif',

		plusBottom	: 'images/plusbottom.gif',

		minus				: 'images/minus.gif',

		minusBottom	: 'images/minusbottom.gif',

		nlPlus			: 'images/nolines_plus.gif',

		nlMinus			: 'images/nolines_minus.gif'

	};
	

	this.obj = objName;

	this.aNodes = [];
	
	// add by xiaosilent. 
	this.aNodesData=[];	//This array save the original data all the time.
	this.targetID=targetID||'dtree';	// Tree will be displayed in this container.
	//this.type=type;	// Saves the type of tree  goods/vendor/consumer?
	this.flag=flag;

	this.aIndent = [];

	this.root = new Node(-1);

	this.selectedNode = null;

	this.selectedFound = false;

	this.completed = false;

};

dTree.prototype.clear = function(){
	this.aNodes.length = 0;
	this.aNodesData.length = 0;
	this.aIndent.length = 0;
	this.selectedNode = null;
}

// Adds a new node to the node array

dTree.prototype.changeName = function(oldName,newName){

	//alert(this.aNodesData[2].name);
	
	for(var i=1;i<this.aNodesData.length;i++){
		if(this.aNodesData[i].name == oldName){
			var id = this.aNodesData[i].id;
			//alert(i);
			this.aNodesData[i].name = newName;
			//alert(this.aNodesData[i].name);
			this.o(id);
			this.s(id);
			break;
		}
	}
};

dTree.prototype.del = function(id){
	//var n=0;
	
	for(var i=0;i<this.aNodesData.length;i++){
		if(this.aNodesData[i].id!=id){
			this.aNodesData[i] = this.aNodesData[i];
			//n++;
		}
	}
	this.aNodesData.length--;
};

dTree.prototype.add = function(id, pid, name, url, title, target, icon, iconOpen, open) {
	
	// Add by xiaosilent.
	this.completed = false;
	//alert("add");

	this.aNodesData[this.aNodesData.length] = new Node(id, pid, name, url, title, target, icon, iconOpen, open);

};



// Open/close all nodes

dTree.prototype.openAll = function() {
	

	this.oAll(true);

};
	

dTree.prototype.closeAll = function() {
	

	this.oAll(false);

};


// Add by xiaosilent .
// get child nodes from web server via AJAX automatically 
// pid : parentID.
dTree.prototype.getChildren = function(pid,nodeid){
	
	//alert("sss");
	this.aNodesData[nodeid]._fc = true;
	var ajax = null;

	if (window.ActiveXObject) {
	
		try{
		
			ajax = new ActiveXObject("Microsoft.XMLHTTP");
			
		}catch(e){
		
			alert("创建Microsoft.XMLHTTP对象失败,AJAX不能正常运行.请检查您的浏览器设置.");
		}
		
	} else {
	
		if (window.XMLHttpRequest) {
			
			try{
				
				ajax = new XMLHttpRequest();
				
			}catch(e){
			
				alert("创建XMLHttpRequest对象失败,AJAX不能正常运行.请检查您的浏览器设置.");
			}
			
		}
	}
	
	// following is just for xiaosilent's Sales Management System.  Server gives me a message like this : id1,name1,childCount1|id2,name2,childCount2|...
	//alert(this.flag);
	var url = "TreeServlet?flag="+this.flag+"&id="+pid;
	var flag = this.flag;
	//var url ="TreeServlet?id="+pid+"&count=" + this.aNodesData.length;
	
	// use this to get this dTree object in the following function.
	var tree=this;
	
	ajax.onreadystatechange = function () {
	
		if (ajax.readyState == 4&&ajax.status == 200) {
			
			if(ajax.responseText=="false") return;
			
			var categories=ajax.responseText.split('|');
			//alert(categories.length)
			
			for(var i=0;i<categories.length;i++){
			
				var aCat = categories[i].split(',');
				
				if(aCat.length==3){
					//alert(aCat[0]);
					var ret1=aCat[0];
					var ret2=aCat[1];
					var ret3=aCat[2];
					//alert(flag);
					if(flag=="build"){
						tree.add(ret1, pid,"#"+ret2,"BuildServlet?flag=select&buildId="+ret3+"&buildNumber="+ret2);
					}else if(flag=="product"){
						//alert(flag);
						tree.add(ret1,pid,ret2+"","ProductVersionServlet?flag=select&versionId="+ret3+"&version="+ret2);
					}else if(flag=="component"){
						tree.add(ret1,pid,ret2+"","ComponentVersionServlet?flag=select&versionId="+ret3+"&version="+ret2);
					}		
				}
			}
			
			
			
			tree.show();
			
			tree.openTo(pid);
		}
		
	};
	
	ajax.open("POST",url);
	ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	ajax.send(null);
	
};




dTree.prototype.showCategory = function(){

};


// Add by xiaosilent.
// Call to show the tree .
dTree.prototype.show = function(){
	
	// Renew the two array to save original data.
	//alert("in show");
	this.aNodes=new Array();
	this.aIndent=new Array();

	// Dump original data to aNode array.
	for(var i=0 ; i<this.aNodesData.length ; i++){
		
		var oneNode=this.aNodesData[i];

		this.aNodes[i]=new Node(oneNode.id,oneNode.pid,oneNode.name,oneNode.url,oneNode.title,oneNode.target,oneNode.icon,oneNode.iconOpen,oneNode.open);
		
		this.aNodes[i]._hc = oneNode._hc;
		this.aNodes[i]._fc = oneNode._fc;
	}
	
	this.rewriteHTML();
};



// Outputs the tree to the page , callled by show()
// Changed by xiaosilent.

dTree.prototype.rewriteHTML = function() {
	

	var str = '';
	
	// Added by xiaosilent. 
	var targetDIV;
	//if(this.type){
		targetDIV=document.getElementById(this.targetID);
	//}else{
		//alert(this.targetID);
	//	targetDIV=parent.leftFrame.document.getElementById(this.targetID);
		
	//}
	
	if(!targetDIV){
		
		alert('dTree can\'t find your specified container to show your tree.\n\n Please check your code!');

		return;
	}
	

	if (this.config.useCookies) this.selectedNode = this.getSelected();
	

	str += this.addNode(this.root);
		



	// Disabled by xiaosilent.
	//	str += '</div>';

	if (!this.selectedFound) this.selectedNode = null;

	this.completed = true;

	
	// Disabled and added by xiaosilent.
	//return str;
	targetDIV.innerHTML=str;
	

};



// Creates the tree structure

dTree.prototype.addNode = function(pNode) {
	

	var str = '';

	var n=0;

	if (this.config.inOrder) n = pNode._ai;

	for (n; n<this.aNodes.length; n++) {

		if (this.aNodes[n].pid == pNode.id) {

			var cn = this.aNodes[n];

			cn._p = pNode;

			cn._ai = n;

			this.setCS(cn);

			if (!cn.target && this.config.target) cn.target = this.config.target;

			if (cn._hc && !cn._io && this.config.useCookies) cn._io = this.isOpen(cn.id);

			if (!this.config.folderLinks && cn._hc) cn.url = null;

			if (this.config.useSelection && cn.id == this.selectedNode && !this.selectedFound) {

					cn._is = true;

					this.selectedNode = n;

					this.selectedFound = true;

			}

			str += this.node(cn, n);

			if (cn._ls) break;

		}

	}

	return str;

};




// Creates the node icon, url and text

dTree.prototype.node = function(node, nodeId) {
	

	var str = '<div class="dTreeNode">' + this.indent(node, nodeId);

	if (this.config.useIcons) {

		if (!node.icon) node.icon = (this.root.id == node.pid) ? this.icon.root : ((node._hc) ? this.icon.folder : this.icon.node);

		if (!node.iconOpen) node.iconOpen = (node._hc) ? this.icon.folderOpen : this.icon.node;

		if (this.root.id == node.pid) {

			node.icon = this.icon.root;

			node.iconOpen = this.icon.root;

		}

		str += '<img id="i' + this.obj + nodeId + '" src="' + ((node._io) ? node.iconOpen : node.icon) + '" alt="" />';

	}
	
	if (node.url) {

		str += '<a id="s' + this.obj + nodeId + '" class="' + ((this.config.useSelection) ? ((node._is ? 'nodeSel' : 'node')) : 'node') + '" href="' + node.url + '"';

		if (node.title) str += ' title="' + node.title + '"';

		if (node.target) str += ' target="' + node.target + '"';

		if (this.config.useStatusText) str += ' onmouseover="window.status=\'' + node.name + '\';return true;" onmouseout="window.status=\'\';return true;" ';

		if (this.config.useSelection && ((node._hc && this.config.folderLinks) || !node._hc))

			str += ' onclick="javascript: ' + this.obj + '.s(' + nodeId + ');"';

		str += '>';

	}

	else if ((!this.config.folderLinks || !node.url) && node._hc && node.pid != this.root.id)

		str += '<a href="javascript: ' + this.obj + '.o(' + nodeId + ');" class="node">';

	str += node.name;

	if (node.url || ((!this.config.folderLinks || !node.url) && node._hc)) str += '</a>';

	str += '</div>';

	if (node._hc) {

		str += '<div id="d' + this.obj + nodeId + '" class="clip" style="display:' + ((this.root.id == node.pid || node._io) ? 'block' : 'none') + ';">';

		str += this.addNode(node);

		str += '</div>';

	}

	this.aIndent.pop();
	//alert(str);
	return str;
	

};




// Adds the empty and line icons

dTree.prototype.indent = function(node, nodeId) {
	

	var str = '';

	if (this.root.id != node.pid) {

		for (var n=0; n<this.aIndent.length; n++)

			str += '<img src="' + ( (this.aIndent[n] == 1 && this.config.useLines) ? this.icon.line : this.icon.empty ) + '" alt="" />';

		(node._ls) ? this.aIndent.push(0) : this.aIndent.push(1);

		if (node._hc) {

			str += '<a href="javascript: ' + this.obj + '.o(' + nodeId + ');"><img id="j' + this.obj + nodeId + '" src="';

			if (!this.config.useLines) str += (node._io) ? this.icon.nlMinus : this.icon.nlPlus;

			else str += ( (node._io) ? ((node._ls && this.config.useLines) ? this.icon.minusBottom : this.icon.minus) : ((node._ls && this.config.useLines) ? this.icon.plusBottom : this.icon.plus ) );

			str += '" alt="" /></a>';

		} else str += '<img src="' + ( (this.config.useLines) ? ((node._ls) ? this.icon.joinBottom : this.icon.join ) : this.icon.empty) + '" alt="" />';

	}

	return str;

};




// Checks if a node has any children and if it is the last sibling

dTree.prototype.setCS = function(node) {


	var lastId;


	for (var n=0; n<this.aNodes.length; n++) {
	

		if (this.aNodes[n].pid == node.id) node._hc = true;

		if (this.aNodes[n].pid == node.pid) lastId = this.aNodes[n].id;

	}


	if (lastId==node.id) node._ls = true;

};




// Returns the selected node

dTree.prototype.getSelected = function() {
	

	var sn = this.getCookie('cs' + this.obj);

	return (sn) ? sn : null;

};



// Highlights the selected node

dTree.prototype.s = function(id) {
	

	//alert(id);
	if (!this.config.useSelection) return;

	var cn = this.aNodes[id];
	if(cn){
		if (cn._hc && !this.config.folderLinks) return;
	}
	
	
	// Disabled by xiaosilent.

	
	if (this.selectedNode != id) {

		if (this.selectedNode || this.selectedNode==0) {

			eOld = document.getElementById("s" + this.obj + this.selectedNode);
			if(eOld){
				eOld.className = "node";
			}
		}

		eNew = document.getElementById("s" + this.obj + id);
		if(eNew){
			eNew.className = "nodeSel";
		}
		

		this.selectedNode = id;

		if (this.config.useCookies) this.setCookie('cs' + this.obj, cn.id);

	}
	

};



// Toggle Open or close

dTree.prototype.o = function(id) {
	
	var cn = this.aNodes[id];
	//alert(id);
	/*
	if(!this.aNodesData[i]._fc){
		this.getChildren(id);
		cn._fc = true;
	}
	*/
	//alert("ss");
	//alert(this.aNodes[id]);
	if(!this.aNodes[id]._fc&&this.flag!="noChildren"){
		//alert(this.aNodes[id]._fc);
		this.getChildren(this.aNodes[id].id,id);
		
		//this.aNodes[id]._fc = true;
	}
	
	
	this.nodeStatus(!cn._io, id, cn._ls);

	cn._io = !cn._io;
	
	if (this.config.closeSameLevel) this.closeLevel(cn);

	if (this.config.useCookies) this.updateCookie();
	
	this.s(id);

};



// Open or close all nodes

dTree.prototype.oAll = function(status) {
	

	for (var n=0; n<this.aNodes.length; n++) {
		

		if (this.aNodes[n]._hc && this.aNodes[n].pid != this.root.id) {
			

			this.nodeStatus(status, n, this.aNodes[n]._ls)

			this.aNodes[n]._io = status;

		}

	}
			

	if (this.config.useCookies) this.updateCookie();

};




// Opens the tree to a specific node

dTree.prototype.openTo = function(nId, bSelect, bFirst) {
	

	if (!bFirst) {
		

		for (var n=0; n<this.aNodes.length; n++) {
			

			if (this.aNodes[n].id == nId) {
				

				nId=n;

				break;

			}

		}

	}
				

	var cn=this.aNodes[nId];

	if (cn.pid==this.root.id || !cn._p) return;

	cn._io = true;

	cn._is = bSelect;

	if (this.completed && cn._hc) this.nodeStatus(true, cn._ai, cn._ls);

	if (this.completed && bSelect) this.s(cn._ai);

	else if (bSelect) this._sn=cn._ai;

	this.openTo(cn._p._ai, false, true);

};


				

// Closes all nodes on the same level as certain node

dTree.prototype.closeLevel = function(node) {
	

	for (var n=0; n<this.aNodes.length; n++) {
		

		if (this.aNodes[n].pid == node.pid && this.aNodes[n].id != node.id && this.aNodes[n]._hc) {
			

			this.nodeStatus(false, n, this.aNodes[n]._ls);

			this.aNodes[n]._io = false;

			this.closeAllChildren(this.aNodes[n]);

		}

	}

};



// Closes all children of a node

dTree.prototype.closeAllChildren = function(node) {
	

	for (var n=0; n<this.aNodes.length; n++) {
		

		if (this.aNodes[n].pid == node.id && this.aNodes[n]._hc) {
			

			if (this.aNodes[n]._io) this.nodeStatus(false, n, this.aNodes[n]._ls);

			this.aNodes[n]._io = false;

			this.closeAllChildren(this.aNodes[n]);		

		}

	}

};



// Change the status of a node(open or closed)

dTree.prototype.nodeStatus = function(status, id, bottom) {
	

	eDiv	= document.getElementById('d' + this.obj + id);

	eJoin	= document.getElementById('j' + this.obj + id);
	

	if (this.config.useIcons) {
		

		eIcon	= document.getElementById('i' + this.obj + id);

		eIcon.src = (status) ? this.aNodes[id].iconOpen : this.aNodes[id].icon;

	}
		

	eJoin.src = (this.config.useLines)?

	((status)?((bottom)?this.icon.minusBottom:this.icon.minus):((bottom)?this.icon.plusBottom:this.icon.plus)):

	((status)?this.icon.nlMinus:this.icon.nlPlus);

	eDiv.style.display = (status) ? 'block': 'none';

};





// [Cookie] Clears a cookie

dTree.prototype.clearCookie = function() {
	

	var now = new Date();

	var yesterday = new Date(now.getTime() - 1000 * 60 * 60 * 24);

	this.setCookie('co'+this.obj, 'cookieValue', yesterday);

	this.setCookie('cs'+this.obj, 'cookieValue', yesterday);

};


	

// [Cookie] Sets value in a cookie

dTree.prototype.setCookie = function(cookieName, cookieValue, expires, path, domain, secure) {
	

	document.cookie =

		escape(cookieName) + '=' + escape(cookieValue)

		+ (expires ? '; expires=' + expires.toGMTString() : '')

		+ (path ? '; path=' + path : '')

		+ (domain ? '; domain=' + domain : '')

		+ (secure ? '; secure' : '');

};


	

// [Cookie] Gets a value from a cookie

dTree.prototype.getCookie = function(cookieName) {
	

	var cookieValue = '';

	var posName = document.cookie.indexOf(escape(cookieName) + '=');
	

	if (posName != -1) {
		

		var posValue = posName + (escape(cookieName) + '=').length;

		var endPos = document.cookie.indexOf(';', posValue);

		if (endPos != -1) cookieValue = unescape(document.cookie.substring(posValue, endPos));

		else cookieValue = unescape(document.cookie.substring(posValue));

	}
		

	return (cookieValue);

};




// [Cookie] Returns ids of open nodes as a string

dTree.prototype.updateCookie = function() {
	

	var str = '';

	for (var n=0; n<this.aNodes.length; n++) {
		

		if (this.aNodes[n]._io && this.aNodes[n].pid != this.root.id) {

			if (str) str += '.';

			str += this.aNodes[n].id;

		}

	}
		

	this.setCookie('co' + this.obj, str);

};




// [Cookie] Checks if a node id is in a cookie

dTree.prototype.isOpen = function(id) {
	

	var aOpen = this.getCookie('co' + this.obj).split('.');
	

	for (var n=0; n<aOpen.length; n++)

		if (aOpen[n] == id) return true;

	return false;

};




// If Push and pop is not implemented by the browser

if (!Array.prototype.push) {
	

	Array.prototype.push = function array_push() {
		

		for(var i=0;i<arguments.length;i++)

			this[this.length]=arguments[i];

		return this.length;

	}

};



if (!Array.prototype.pop) {
	

	Array.prototype.pop = function array_pop() {
		

		lastElement = this[this.length-1];

		this.length = Math.max(this.length-1,0);

		return lastElement;

	}

};

