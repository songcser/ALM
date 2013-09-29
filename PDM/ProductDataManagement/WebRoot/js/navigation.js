
function NNode(name,url,target){
	this.name = name;
	this.url = url;
	this.target = target;
}

function Navigation(targetId,isParent){
	//alert("sss");
	this.nodes = [];
	this.targetId=targetId;
	this.isParent = isParent; 
}

Navigation.prototype.add = function(name,url,target){
	//alert("dd");
	this.nodes[this.nodes.length]=new NNode(name,url,target);
}

Navigation.prototype.addUrl = function(){
	str='';
	//alert(this.nodes.length);
	for(var i=0;i<this.nodes.length;i++){
		var node = this.nodes[i];
		str+='<a href="'+node.url+'"';
		if(node.target){
			str+=' target="'+node.target+'" >';
		}else{
			str+='>';
		}
		str += '<font size="2px">';
		str += node.name;
		if(i==this.nodes.length-1){
			str += ' </font></a>';
		}else
			str += ' </font></a><font size="2px">>></font>';
		
		//alert(str);
	}
	return str;
}

Navigation.prototype.show = function(){
	var str = '';
	var targetDIV;
	//alert(this.targetId);
	if(this.isParent){
		targetDIV=parent.document.getElementById(this.targetId);
		//alert(this.isParent);
		var targetid = this.targetId;
		//targetDIV=parent.targetid;
	}
	else{
		targetDIV=document.getElementById(this.targetId);
		//alert(targetDIV);
	}
	str = this.addUrl()
	
	targetDIV.innerHTML=str;
}