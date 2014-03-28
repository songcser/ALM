
var curPage = 1;
//var table;
function goPage(pno,psize){
	var itable = document.getElementById("idData");
	if(!itable)
		return;
	//alert(itable);
	//table = itable;
	//alert(tablss.rows.length);
	var num = itable.rows.length;//表格行数
	//alert(num);
	var totalPage = 0;//总页数
	var pageSize = psize;//每页显示行数
	if((num-1)/pageSize > parseInt((num-1)/pageSize)){   
   		 totalPage=parseInt((num-1)/pageSize)+1;   
   	}else{   
   		totalPage=parseInt((num-1)/pageSize);   
   	}   
	var currentPage = pno;//当前页数
	curPage = currentPage;
	var startRow = (currentPage - 1) * pageSize+1;//开始显示的行   
   	var endRow = currentPage * pageSize+1;//结束显示的行   
   	endRow = (endRow > num)? num : endRow;
	//前三行始终显示
	for(i=0;i<1;i++){
		var irow = itable.rows[i];
		irow.style.display = "block";
	}
	
	for(var i=1;i<num;i++){
		var irow = itable.rows[i];
		if(i>=startRow&&i<endRow){
			irow.style.display = "block";	
		}else{
			irow.style.display = "none";
		}
	}
	var pageEnd = document.getElementById("pageEnd");
	//var tempStr = "gong "+(num-1)+" ye fen "+totalPage+"  ye dangqi "+currentPage+" ye";
	var tempStr = "";
	//alert(currentPage);
	if(currentPage>1){
		//tempStr += "<a href=\"repositoryPropertiesPage.jsp\" onClick=\"goPage("+(1)+","+psize+")\">first</a>";
		tempStr += '<a href="javascript: goPage(' + 1 + ',' + psize + ');">first  </a>'
	}else{
		tempStr += "first  ";
	}
	if(currentPage>1){
		//tempStr += "<a href=\"repositoryPropertiesPage.jsp\" onClick=\"goPage("+(currentPage-1)+","+psize+")\">last</a>"
		tempStr += '<a href="javascript: goPage('+(currentPage-1)+ ',' + psize + ');">pre    </a>'
	}else{
		tempStr += "pre    ";	
	}
	if(currentPage<totalPage){
		//tempStr += "<a href=\"repositoryPropertiesPage.jsp\" onClick=\"goPage("+(currentPage+1)+","+psize+")\">next</a>";
		tempStr += '<a href="javascript: goPage(' +(currentPage+1)+ ',' + psize + ');">next   </a>'
	}else{
		tempStr += "next   ";	
	}
	if(currentPage<totalPage){
		//tempStr += "<a href=\"repositoryPropertiesPage.jsp\" onClick=\"goPage("+(totalPage)+","+psize+")\">last</a>";
		tempStr += '<a href="javascript: goPage(' + totalPage + ',' + psize + ');">last   </a>'
	}else{
		tempStr += "last   ";
	}
	curPage = currentPage;
	document.getElementById("barcon").innerHTML = tempStr;
	
}


function writeFile(filename,filecontent){  
    var fso, f, s ;  
    fso = new ActiveXObject("Scripting.FileSystemObject");     
    f = fso.OpenTextFile(filename,8,true);  
    f.WriteLine(filecontent);    
    f.Close();  
    //alert('write ok');  
}  
function readFile(filename){
    var fso = new ActiveXObject("Scripting.FileSystemObject");  
    var f = fso.OpenTextFile(filename,1);  
    var s = "";  
    while (!f.AtEndOfStream)  
        s += f.ReadLine()+"/n";  
    f.Close();
    alert(s);
    var textBox=document.getElementById("show");
    textBox.value = s;
}  

function public_Labels(label1, label2){
	t1.innerText = label1;
	t2.innerText = label2;
}
//切换选项卡时显示选项卡的内容
function public_Contents(contents1, contents2){
	t1Contents.innerHTML = contents1;
	t2Contents.innerHTML = contents2;
	init();
}
//默认显示选项卡1

function init(id){
	
	t1base.style.backgroundColor="";
	//tabContents.innerHTML = t1Contents.innerHTML;
	var topMenus = getClass('div','cont');
	//alert(topMenus.length);
	var tabbase;
	var currenttab;
	for(var i=0;i<topMenus.length;i++){
		if(i==0){
			//alert(topMenus[i].id);
			//var tid = i+1;
			//tabbase = "t"+tid+"base";
			
			//currenttab = "t"+tid;
			//currenttab.className = "selTab";
			//alert(tabbase);
			//t1base.style.backgroundColor="";
			
			topMenus[i].style.display = "block";
		}else
			//var tid = i+1;
			//tabbase = "t"+tid+"base";
			//currenttab = "t"+tid;
			//currenttab.className = "Tab";
			//alert(tabbase);
			//tabbase.style.backgroundColor="white";
			topMenus[i].style.display = "none";
	}
	
	goPage(curPage,5);
	
}

function tab1init(){
	tabContents.innerHTML = t1Contents.innerHTML;
}

function tab2init(){
	tabContents.innerHTML = t2Contents.innerHTML;
}

//更换选项卡时的方法
var currentTab;
var tabBase;
var firstFlag = true;
function changeTabs(event){
	//alert("change");
	if(firstFlag == true){
		currentTab = t1;
		tabBase = t1base;
		firstFlag = false;
		//alert("sssss");
	}
	//alert("sss");
//当用户单击选项卡时，修改样式及内容
	//var obj = event.srcElement?event.srcElement:event.target;
	var obj = event.srcElement ? event.srcElement : event.target;
	//alert(obj);
	if(obj.className == "tab")
	{
		//alert("eee");
		currentTab.className = "tab";
		tabBase.style.backgroundColor = "white";
		currentTab = obj;
		tabBaseID = currentTab.id + "base";
		tabContentID = currentTab.id + "Contents";
		tabBase = document.all(tabBaseID);
		tabContent = document.all(tabContentID);
		currentTab.className = "selTab";
		tabBase.style.backgroundColor = "";
		//tabContents.innerHTML = tabContent.innerHTML;
		var topMenus = getClass('div','cont');
		for(var i=0;i<topMenus.length;i++){
			if(topMenus[i].id == tabContentID){
				topMenus[i].style.display = "block";
			}else
				topMenus[i].style.display = "none";
		}
		
	}
}

function getClass(tagName,className) //获得标签名为tagName,类名className的元素
{
	//alert("sss");
	if(document.getElementsByClassName) //支持这个函数
	{ 
		//alert("yes");
		return document.getElementsByClassName(className);
	}
	else
	{ 
		//alert("no");
		var tags=document.getElementsByTagName(tagName);//获取标签
		var tagArr=[];//用于返回类名为className的元素
		for(var i=0;i < tags.length; i++)
		{
			if(tags[i].className == className)
			{
				tagArr[tagArr.length] = tags[i];//保存满足条件的元素
			}
		}
		return tagArr;
	}
}

function ajaxSend(url,flag){
	
	var retStr = '';
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
	ajax.open("POST",url,flag);
	ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	ajax.send(null);
	if(flag){
		ajax.onreadystatechange = function () {

			if (ajax.readyState == 4&&ajax.status == 200) {
			
				return ajax.responseText;
			
			}
		};
	}
	else{
		if (ajax.readyState == 4&&ajax.status == 200) {
			//alert(ajax.responseText);
			return ajax.responseText;
		}
	}
		//alert(flag);
		
}
function addRow(array,width){
	//alert(name);
	
	var table = document.getElementById("idData");
	//alert(table.rows.length);
	//var leng = array.length;
	var newRow = table.insertRow(-1);
	//newRow.setAttribute("id",name);
//	newRow.id = name;
	var cells = new Array(array.length);
	//alert(array.length);
	//alert(array.length);
	for(var i=0;i<array.length;i++){
		cells[i] = document.createElement("td");
		//cells[i] = newRow.insertCell(i);
		cells[i].innerHTML = array[i];
		//alert(array[i]);
		cells[i].setAttribute("width",width[i]);
		
		newRow.appendChild(cells[i]);
		
	}
	
	goPage(curPage,5);
}

function removeRow(name){
	//var  tr  =  document.getElementById(name);
	//document.getElementById("idData").deleteRow(tr.rowIndex);
	//for(var i=0;i<table)
	
	var table = document.getElementById("idData");

	for(var i=0;i<table.rows.length;i++){
		
		var text = table.rows[i].cells[0].innerHTML;
		var index1 = text.indexOf(">");
		if(index1!=-1){
			index2 = text.indexOf("<",index1);
			var tempName = text.substring(index1+1,index2);
			if(tempName==name){
				table.deleteRow(i);
			}
			
		}
		//alert(proName);
	}
	goPage(curPage,5);
}
String.prototype.replaceAll = stringReplaceAll;

function stringReplaceAll(AFindText,ARepText){
	var raRegExp = new RegExp(AFindText,"g");
	return this.replace(raRegExp,ARepText)
}