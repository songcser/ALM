// PDMBuilder.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "PDMBuilder.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "Builder.h"
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#define BUILDNAME "jysong"
#define BUILDPASSWORD "SKYfly2012"
// This is an example of an exported variable
string workspace;
string numberFile = "nextBuildNumber";
string buildTime;
string duration;
string result;
string fileName;
int buildNumber;
string sourceVersion;
string environment;
// This is an example of an exported function.
int exitError = 0;
int exitSuccess = 0;
int exitWarning = 0;

TiXmlDocument *pDoc;
//TiXmlElement *pRootEle;
TiXmlElement *pProjectNodes;
// This is the constructor of a class that has been exported.
// see PDMBuilder.h for the class definition

/*
bool writeLog(string log)
{
	FILE *fp;
	string filePath = workspace+"\\log";
	if (fp=fopen(filePath.c_str(),"a+"))
	{
		if(EOF==fprintf(fp,"%s",log.c_str()))
		{
			fclose(fp);
			return false;
		}
		fclose(fp);
	}

	return true;
}
*/

PDMBUILDER_API void writelog(string log,string workspace){
	writeLog(log,workspace);
}

bool GetNodePointer(TiXmlElement* pRootEle, vector<TiXmlElement *> *pNodes)
{
	pNodes->clear();
	TiXmlElement *pEle = pRootEle;
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()){
		pNodes->push_back(pEle);
	}
	if (pNodes->size()<1)
	{
		return false;
	}
	return true;
}

bool GetNodePointerByName(TiXmlElement* pRootEle, string &strNodeName,TiXmlElement* &Node)
{
	if (strNodeName==pRootEle->Value()){
		Node = pRootEle;
		return true;
	}

	TiXmlElement *pEle = pRootEle;
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()){
		if(GetNodePointerByName(pEle, strNodeName, Node)){
			return true;
		}
	}

	return false;
}

bool GetChildNodeByName(TiXmlElement* pRootEle, string &strNodeName,TiXmlElement* &Node){
	TiXmlElement *pEle = pRootEle;
	for (pEle = pRootEle->FirstChildElement();pEle;pEle = pEle->NextSiblingElement())
	{
		if (strNodeName==pEle->Value())
		{
			Node = pEle;
			return true;
		}
	}
	return false;
}

PDMBUILDER_API void setWorkSpace(string ws)
{

	workspace = ws;
	
}

PDMBUILDER_API bool setConfigXML(char *xml)
{
	string xmlFile = xml;

	pDoc = new TiXmlDocument();
	if (pDoc==NULL)
	{
		return false;
	}
	pDoc->LoadFile(xmlFile.c_str());
 
	TiXmlElement *pRootEle = pDoc->RootElement();
	if(NULL == pRootEle){
		return false;
	}
	
	string entryNode = "Project";
	GetNodePointerByName(pRootEle, entryNode, pProjectNodes);
	
	int index = xmlFile.find_last_of("\\");
	fileName = xmlFile.substr(index+1);
	index = fileName.find_last_of(".");
	fileName = fileName.substr(0,index);

	return true;
}

SourceCode* getSourceCode()
{
	string SourceCodeNode = "SourceCode";
	TiXmlElement *pNode = NULL;

	vector<TiXmlElement *> Nodes;

	if (GetNodePointerByName(pProjectNodes,SourceCodeNode,pNode))
	{
		string urlNode = "Url";
		string versionNode = "Version";
		string localPathNode = "LocalPath";
		TiXmlElement *pTempNode = pNode;
		SourceCode* sourceCode = new SourceCode();
		if (GetChildNodeByName(pTempNode,urlNode,pNode))
		{
			sourceCode->SetUrl(pNode->GetText());
			if (GetChildNodeByName(pTempNode,versionNode,pNode))
			{
				sourceCode->SetVersion(pNode->GetText());
				if (GetChildNodeByName(pTempNode,localPathNode,pNode))
				{
					sourceCode->SetLocalPath(pNode->GetText());

					//delete pNode;
					//delete pTempNode;
					return sourceCode;
				}
			}
		}
	}

	return NULL;
}

PDMBUILDER_API void getCodeInfo(char *url,char *version,char *localpath)
{
	SourceCode *sourceCode = getSourceCode();
	
	strcpy(url,sourceCode->GetUrl().c_str());
	strcpy(version,sourceCode->GetVersion().c_str());
	strcpy(localpath,sourceCode->GetLocalPath().c_str());

	delete sourceCode;
	//url = (char *)sourceCode->GetUrl().c_str();
	//version = (char *)sourceCode->GetVersion().c_str();
	//localpath = (char *)sourceCode->GetLocalPath().c_str();
}

PDMBUILDER_API bool checkSourceCode()
{
	SourceCode *sourceCode = getSourceCode();

	//string url = sourceCode->GetUrl();
	
	string fullpath(workspace+"\\"+sourceCode->GetLocalPath());
	//string fullpath = sourceCode->GetLocalPath();
	string log ;
	fullpath = changeSeparator(fullpath);
	string svnPath(fullpath+"\\.svn");
	if (!PathFileExists(svnPath.c_str()))
	{
		log += checkout(workspace);
		if ("error"==log)
		{
			delete sourceCode;
			return false;
		}
		writeLog(log,workspace+"\\log");
		delete sourceCode;
		return true;
	}

	char updateCmd[500];
	memset(updateCmd,0,sizeof(updateCmd));

	sprintf(updateCmd,"svn update --force --non-interactive --username %s --password %s --accept tf \"%s\"",BUILDNAME,BUILDPASSWORD,sourceCode->GetLocalPath().c_str());

	int exitCode = 0;
	
	log = ExeCommand(updateCmd,exitCode,(char *)workspace.c_str());
	if (exitCode>0&&exitCode!=STILL_ACTIVE)
	{
		log += "update source code error";

		delete sourceCode;
		return false;
	}else if (log.find("svn cleanup")!=string::npos)
	{
		char cleanupCmd[100];
		memset(cleanupCmd,0,sizeof(cleanupCmd));
		sprintf(cleanupCmd,"svn cleanup");
		ExeCommand(cleanupCmd,exitCode,(char *)workspace.c_str());

		log = ExeCommand(updateCmd,exitCode,(char *)workspace.c_str());
		if (exitCode>0&&exitCode!=STILL_ACTIVE)
		{
			log += "update source code error";
			delete sourceCode;
			return false;
		}
	}
	int index = log.find("Updated to revision");
	if (index>0)
	{
		index += 20;
		int in = log.find_last_of(".");
		sourceVersion = log.substr(index,in-index);
		writeLog(log,workspace+"\\log");

		delete sourceCode;
		return true;
	}else
	{
		delete sourceCode;
		return false;
	}
}

PDMBUILDER_API string checkout(string workspace)
{
	SourceCode *sourceCode = getSourceCode();

	char ExportCmd[500];
	memset(ExportCmd,0,sizeof(ExportCmd));

	string url  = sourceCode->GetUrl();
	string log("<---------------------------checkout--------------------------->\nCheckout: ");
	log.append(url).append("\n");
	//string fullpath(workspace+"\\"+sourceCode->GetLocalPath());
	string fullpath = sourceCode->GetLocalPath();
	fullpath = changeSeparator(fullpath);

	if(sourceCode->GetVersion() == "head"){
		sprintf(ExportCmd, "svn checkout --force --non-interactive --username \"%s\" --password \"%s\" %s \"%s\"",BUILDNAME,BUILDPASSWORD,sourceCode->GetUrl().c_str(), fullpath.c_str());
	}else{
		sprintf(ExportCmd, "svn checkout -r %s --force  --non-interactive --username %s --password %s %s \"%s\"",BUILDNAME,BUILDPASSWORD,sourceCode->GetVersion().c_str(),sourceCode->GetUrl().c_str(),fullpath.c_str());
	}

	int exitCode = 0;
	log += ExeCommand(ExportCmd,exitCode,(char *)workspace.c_str());
	if (exitCode>0&&exitCode!=STILL_ACTIVE)
	{
		return "error";
	}

	if ("head" == sourceCode->GetVersion())
	{
		//int length = log.length();
		int index = log.rfind("Checked out revision");
		if(index!=string::npos){
			int in = log.rfind(".");
			index += 21;
			sourceVersion = log.substr(index,in-index);
		}else{
			return "error";
		}
	}else{
		sourceVersion = sourceCode->GetVersion();
	}
	delete sourceCode;
	
	return log;
}

list<Dependence *> * getDependences()
{
	vector<TiXmlElement *> Nodes;
	TiXmlElement *pNode = NULL;
	string DependencesNode = "Dependences";

	if (GetNodePointerByName(pProjectNodes,DependencesNode,pNode))
	{
		string DependenceNode = "Dependence";

		GetNodePointer(pNode, &Nodes);
		list<Dependence *> *depList = new list<Dependence *>();
		for (int i=0;i<Nodes.size();i++)
		{

			TiXmlElement *pTempNode = Nodes.at(i);
			string server = "Server";
			string flag = "Flag";
			string repository = "Repository";
			string name = "Name";
			string version = "Version";
			string path = "Path";
			string localPath = "LocalPath";

			Dependence *dep = new Dependence();
			if (GetChildNodeByName(pTempNode,server,pNode))
			{
				dep->SetServer(pNode->GetText());
			}else
			{
				return false;
			}
			if (GetChildNodeByName(pTempNode,flag,pNode))
			{
				dep->SetFlag(pNode->GetText());
			}else
			{
				return false;
			}
			if (GetChildNodeByName(pTempNode,repository,pNode))
			{
				dep->SetRepository(pNode->GetText());
			}else
			{
				return false;
			}

			if (GetChildNodeByName(pTempNode,name,pNode))
			{
				dep->SetName(pNode->GetText());
			} 
			else
			{
				return false;
			}
			if (GetChildNodeByName(pTempNode,version,pNode))
			{
				dep->SetVersion(pNode->GetText());
			}else
			{
				return false;
			}
			if(GetChildNodeByName(pTempNode,path,pNode)){
				dep->SetPath(pNode->GetText());
			}else
			{
				return false;
			}
			if (GetChildNodeByName(pTempNode,localPath,pNode))
			{
				dep->SetLocalPath(pNode->GetText());
			} 
			else
			{
				return false;
			}

			depList->push_back(dep);
			//delete dep;
			//delete pTempNode;
		}
		//delete pNode;
		return depList;
	}else
	{
		return NULL;
	}
}

PDMBUILDER_API bool getRelyFiles(char *ws,string &ret)
{
	ret.assign("\n<---------------------------Get Dependence File--------------------------->\n");
	list<Dependence *> * depList = getDependences();

	for (list<Dependence *>::iterator iter=depList->begin();iter != depList->end();++iter)
	{
		string flag = (*iter)->GetFlag();
		string server = (*iter)->GetServer();
		string repository = (*iter)->GetRepository();
		string name = (*iter)->GetName();
		string version = (*iter)->GetVersion();
		string path = (*iter)->GetPath();
		string localPath = (*iter)->GetLocalPath();

		localPath = changeSeparator(localPath);

		string pArgument = "Flag="+flag+"&Repository="+repository+"&Name="+name+"&Version="+version+"&Path="+path;

		string fullpath(ws);

		fullpath.append("\\").append(localPath);

		ret +=  ExeDownLoad((char *)server.c_str(),(char *)pArgument.c_str(),(char *)fullpath.c_str());
		//return TRUE;
	}
	delete depList;
	

	return true;
}

PDMBUILDER_API bool updateRelyFiles(char *ws,string &ret)
{
	ret.assign("\n<---------------------------Update Dependence File--------------------------->\n");
	list<Dependence *> * depList = getDependences();

	for (list<Dependence *>::iterator iter=depList->begin();iter != depList->end();++iter)
	{
		string flag = (*iter)->GetFlag();
		string server = (*iter)->GetServer();
		string repository = (*iter)->GetRepository();
		string name = (*iter)->GetName();
		string version = (*iter)->GetVersion();
		string path = (*iter)->GetPath();
		//string localPath = (*iter)->GetLocalPath();

		//int tIndex = string::npos;
		//while((tIndex = localPath.find('/')) != string::npos){
		//	localPath = localPath.replace(tIndex, 1, "\\");
		//}
		string pArgument = "Flag="+flag+"&Repository="+repository+"&Name="+name+"&Version="+version+"&Path="+path;

		//string fullpath(workspace+"\\"+localPath);

		ret +=  ExeDownLoad((char *)server.c_str(),(char *)pArgument.c_str(),ws);
		//return TRUE;
	}
	delete depList;

	//string logpath(ws);
	//writeLog(ret,logpath+"\\log");
	return true;
}

list<BuildStep *> *getBuildStep()
{
	string ProcessNode = "Process";
	TiXmlElement *pNode = NULL;
	vector<TiXmlElement *> Nodes;

	if (GetNodePointerByName(pProjectNodes,ProcessNode,pNode))
	{
		string name = "Name";
		string program = "Program";
		string options = "Options";
		GetNodePointer(pNode,&Nodes);

		list<BuildStep *> *buildStep = new list<BuildStep *>();
		for (int i=0;i<Nodes.size();i++)
		{
			BuildStep *step = new BuildStep();
			if (GetNodePointerByName(Nodes.at(i),name,pNode))
			{
				step->SetName(pNode->GetText());
			} 
			else
			{
				return false;
			}
			if (GetChildNodeByName(Nodes.at(i),program,pNode))
			{
				step->SetProgram(pNode->GetText());
			}else return false;
			if (GetChildNodeByName(Nodes.at(i),options,pNode))
			{
				step->SetOptions(pNode->GetText());
			}else return false;

			buildStep->push_back(step);

			//delete step;
		}
		//delete pNode;
		return buildStep;
	} 
	else
	{
		return NULL;
	}
}

string RunBuildStep(string name,string program,string options,int &exitCode)
{
	char BuildCmd[255];

	program = changeSeparator(program);
	//options = changeSeparator(options);
	/*
	int index = options.find_last_of(' ');
	if (index>0)
	{
		string solution = options.substr(index+1);
		string argument = options.substr(0,index);
		string fullpath(workspace+"\\"+solution);
		fullpath = changeSeparator(fullpath);
		sprintf(BuildCmd, "%s %s %s",program.c_str(),argument.c_str(),fullpath.c_str());
	}
	else
	{
		string fullpath = workspace + "\\" +options;
		fullpath = changeSeparator(fullpath);
		sprintf(BuildCmd, "%s %s",program.c_str(),fullpath.c_str());
	}
	*/
	sprintf(BuildCmd,"%s %s",program.c_str(),options.c_str());
	
	string log="\n<---------------------------"+name+"--------------------------->\n";
	
	//log += ExeCmd(BuildCmd,exitCode,(char *)workspace.c_str());
	log += ExeCommand(BuildCmd,exitCode,(char *)workspace.c_str());

	return log;
}

PDMBUILDER_API string process()
{
	list<BuildStep *> * buildStep = getBuildStep();
	string log;
	char Time[255];
	char Temp[100];
	
	int exitCode;
	
	SYSTEMTIME sys;
	GetLocalTime( &sys );
	int minute = sys.wMinute;
	int second = sys.wSecond;
	int millisecond = sys.wMilliseconds;
	sprintf(Time,"%4d-%02d-%02d %02d:%02d:%02d.%03d ",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds);
	for (list<BuildStep *>::iterator iter=buildStep->begin();iter != buildStep->end();++iter)
	{
		string name = (*iter)->GetName();
		string program = (*iter)->GetProgram();
		string options = (*iter)->GetOptions();
		environment += name +";";
		log += RunBuildStep(name,program,options,exitCode);
		int index = log.rfind("Error(s)");
		string str = log.substr(index-2,1);
		exitError += atoi(str.c_str());
		index = log.rfind("Warning(s)");
		str = log.substr(index-2,1);
		exitWarning += atoi(str.c_str());
		/*
		if (exitCode==0)
		{
			exitSuccess++;
		}else if(exitCode>0&&exitCode!=STILL_ACTIVE){
			exitError ++;
		}else if (exitCode==STILL_ACTIVE)
		{
			exitSuccess++;
		}*/
	}

	GetLocalTime(&sys);
	//float dur = (sys.wMinute - minute)*60+second - sys.wSecond + (sys.wMilliseconds-millisecond)/1000;
	int dur = (sys.wMinute-minute)*60*1000+(sys.wSecond-second)*1000+(sys.wMilliseconds-millisecond);
	sprintf(Temp,"%d",dur);
	//sprintf(Temp,"%d",millisecond-sys.wMilliseconds);
	buildTime.assign(Time);
	duration.assign(Temp);
	
	if (exitError>0&&exitSuccess>0)
	{
		result = "ERROR";
	}else if (exitError>0&&exitSuccess==0)
	{
		result = "FAILURE";
	}else if (exitError==0&&exitSuccess ==0&&exitWarning==0)
	{
		result = "SUCCESS";
	}else if (exitSuccess>0&&exitError==0)
	{
		result = "SUCCESS";
	}else if (exitError==0&&exitWarning>0)
	{
		result = "WARNING";
	}

	//result.assign("SUCCESS");


	FILE *fp;
	string filePath = workspace+"\\"+numberFile;

	if (!PathFileExists(filePath.c_str()))
	{
		buildNumber = 1;
		
		if (fp = fopen(filePath.c_str(),"w"))
		{
			if (EOF == fprintf(fp,"%d",buildNumber))
			{
				log += "[Log-->] write build number error";
			}
			fclose(fp);
		}else
		{
			log += "[log -->] open file error";
		}
	}
	else if (fp=fopen(filePath.c_str(),"r+"))
	{
		if(EOF==fscanf(fp,"%d",&buildNumber)){
			buildNumber = 0;
		}

		buildNumber ++;
		rewind(fp);
		//fseek(fp,0,SEEK_SET);
		if(EOF==fprintf(fp,"%d",buildNumber)){
			//buildNumber = 0;
			log += "[Log-->] write build number error";
		}

		fclose(fp);
	}
	
	
	//log += ExeUpLoadMessage()
	delete buildStep;
	writeLog(log,workspace+"\\log");
	return log;
}

list<ImportStep *> * getImportStep()
{
	string ImportNode = "Import";
	TiXmlElement *pNode = NULL;
	vector<TiXmlElement *> Nodes;

	if (GetNodePointerByName(pProjectNodes,ImportNode,pNode))
	{
		string name	= "Name";
		string url = "Url";
		string importItem = "ImportItem";
		GetNodePointer(pNode,&Nodes);
		list<ImportStep *> *importStep = new list<ImportStep *>();
		for (int i=0;i<Nodes.size();i++)
		{
			ImportStep *step = new ImportStep();
			vector<TiXmlElement *> tNodes;
			GetNodePointer(Nodes.at(i),&tNodes);
			step->SetName(tNodes.at(0)->GetText());
			step->SetUrl(tNodes.at(1)->GetText());
			list<ImportItem *> itemList;
			for(int i=2;i<tNodes.size();i++){

				string source = "Source";
				string target = "Target";
				ImportItem *item = new ImportItem();
				if (GetChildNodeByName(tNodes.at(i),source,pNode))
				{
					item->SetSource(pNode->GetText());
				}else return false;
				if (GetChildNodeByName(tNodes.at(i),target,pNode))
				{
					item->SetTarget(pNode->GetText());
				}else return false;

				itemList.push_back(item);
				//delete item;
			}
			step->setItem(itemList);
			importStep->push_back(step);
			//delete step;
		}
		//delete pNode;
		return importStep;
	}else 
		return NULL;
}

string getName()
{
	string NameNode = "Name";
	TiXmlElement *pNode = NULL;
	//vector<TiXmlElement *> Nodes;
	if(GetNodePointerByName(pProjectNodes, NameNode, pNode))
	{
		return pNode->GetText();
		
	}
	
	return "";
}

string ImportLibStep(string name,string url,string sourceUrl, vector<string> source, vector<string> target)
{
	char number[20];
	itoa(buildNumber,number,20);
	//string repName();
	string artName(getName());
	
	list<DepMessage> depMsgList;
	list<Dependence *> *depList = getDependences();
	for (list<Dependence *>::iterator iter=depList->begin();iter != depList->end();++iter)
	{
		DepMessage depMsg;
		depMsg.flag = (*iter)->GetFlag();
		//depMsg. server = (*iter)->GetServer();
		depMsg.repName = (*iter)->GetRepository();
		depMsg.artName = (*iter)->GetName();
		depMsg.version = (*iter)->GetVersion();
		depMsg.path = (*iter)->GetPath();
		depMsg.localPath = (*iter)->GetLocalPath();

		//log += GetDependences(server,flag,repository,name,version,path,localPath);
		depMsgList.push_back(depMsg);
	}

	stringstream ss;
	ss<<buildNumber;
	string str;
	ss>>str;
	delete depList;
	return ExeUpLoad(url,fileName,artName,str,buildTime,duration,result,sourceUrl,sourceVersion,environment,source,target,depMsgList);
	//return ExeUpLoad((char *)url.c_str(),"build",(char *)project->GetFileName().c_str(),(char *)project->GetName().c_str(),number,source,target);
}

PDMBUILDER_API string import()
{
	SourceCode *scode = getSourceCode();
	string sourceUrl = scode->GetUrl();

	int tagsIndex = sourceUrl.find("tags");
	int branchesIndex = sourceUrl.find("branches");
	int trunkIndex = sourceUrl.find("trunk");
	if (tagsIndex>0&&branchesIndex==string::npos&&trunkIndex==string::npos)
	{
		return "";
	}else if (tagsIndex>trunkIndex||tagsIndex>branchesIndex)
	{
		return "";
	}

	list<ImportStep *> *importStep = getImportStep();
	string log;

	for(list<ImportStep *>::iterator iter=importStep->begin();iter != importStep->end();++iter)
	{
		string name = (*iter)->GetName();
		string url = (*iter)->GetUrl();
		list<ImportItem *> item = (*iter)->GetItem();

		vector<string> source;
		vector<string> target;
		for(list<ImportItem *>::iterator iterItem=item.begin();iterItem != item.end();++iterItem)
		{
			string path =workspace+"\\"+(*iterItem)->GetSource();
			path = changeSeparator(path);
			source.push_back(path);
			
			target.push_back(changeSeparator((*iterItem)->GetTarget()));
		}
		//string logPath = workspace + "\\log";
		source.push_back(workspace+"\\log");
		target.push_back(".");
		//delete item;
		log += ImportLibStep(name,url,sourceUrl,source,target);
	}

	delete scode;
	delete importStep;
	return log;
}

Publish * getPublish()
{
	string PublishNode = "Publish";
	TiXmlElement *pNode = NULL;
	vector<TiXmlElement *> Nodes;

	if (GetNodePointerByName(pProjectNodes,PublishNode,pNode))
	{
		string url = "Url";
		string category = "Category";
		string component = "Component";
		string version = "Version";
		string importItem = "ImportItem";
					
		Publish *publish = new Publish();
			
		TiXmlElement * pTempNode = pNode;
		GetNodePointer(pTempNode,&Nodes);
		publish->SetUrl(Nodes.at(0)->GetText());
		publish->SetCategory(Nodes.at(1)->GetText());
		publish->SetComponent(Nodes.at(2)->GetText());
		publish->SetVersion(Nodes.at(3)->GetText());
		list<ImportItem *> itemList ;
		for(int i=4;i<Nodes.size();i++){
			string source = "Source";
			string target = "Target";
			ImportItem *item = new ImportItem();
			if (GetChildNodeByName(Nodes.at(i),source,pNode))
			{
				item->SetSource(pNode->GetText());
			}else return false;
			if (GetChildNodeByName(Nodes.at(i),target,pNode))
			{
				item->SetTarget(pNode->GetText());
			}else return false;

			itemList.push_back(item);
		}
		publish->SetImportItem(itemList);

		return publish;
	} 
	else
	{
		return NULL;
	}
}

PDMBUILDER_API string publish()
{
	
	SourceCode *scode = getSourceCode();
	string sourceUrl = scode->GetUrl();

	int tagsIndex = sourceUrl.find("tags");
	int branchesIndex = sourceUrl.find("branches");
	int trunkIndex = sourceUrl.find("trunk");
	if (tagsIndex<0&&branchesIndex>0||trunkIndex>0)
	{
		return "";
	}else if (tagsIndex<trunkIndex||tagsIndex<branchesIndex)
	{
		return "";
	}
	
	Publish *publish = getPublish();

	list<ImportItem *> itemList = publish->GetImportItem();
	vector<string> source;
	vector<string> target;
	for (list<ImportItem *>::iterator iter = itemList.begin();iter != itemList.end();++iter)
	{
		string path =workspace+"\\"+(*iter)->GetSource();
		path = changeSeparator(path);
		source.push_back(path);

		//source.push_back((*iter)->GetSource());
		target.push_back((*iter)->GetTarget());
	}

	string log = ExeComponentUpLoad((char *)publish->GetUrl().c_str(),"component",(char *)publish->GetCategory().c_str(),(char *)publish->GetComponent().c_str(),(char *)publish->GetVersion().c_str(),source,target);
	
	//delete itemList;
	delete scode;
	delete publish;

	return log;
}

PDMBUILDER_API string clean()
{
	string log;
	string localpath;
	//SourceCode *sourceCode = getSourceCode();
	//string localpath = sourceCode->GetLocalPath();
	//localpath = changeSeparator(localpath);
	//deleteDir(workspace+"\\"+localpath);
	//DeleteFile(workspace+"\\"+localpath);
	//log += "[Log-->] delete directory: "+workspace+"\\"+localpath + "\n";
	/*
	list<Dependence *> *depList = getDependences();
	for (list<Dependence *>::iterator iter=depList->begin();iter != depList->end();++iter)
	{
		localpath = (*iter)->GetLocalPath();

		localpath = changeSeparator(localpath);
		int index = localpath.find_first_of("\\");
		if (index>0)
		{
			localpath = localpath.substr(0,index);
		}

		DeleteFile(workspace+"\\"+localpath);
		log += "[Log-->] delete directory: "+workspace+"\\"+localpath + "\n";
		//return TRUE;
	}*/
	//string delLog = "del "+workspace+"\\log";
	//system(delLog.c_str()) ;
	//delete pProjectNodes;
	string logFile(workspace+"\\log");
	if (PathFileExists((char *)logFile.c_str()))
	{
		DeleteFile(logFile);
	}
	
	//printf("%s",log.c_str());
	delete pDoc;
	//TiXmlElement *pRootEle;
	return log;
}