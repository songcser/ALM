// BuildTest.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "BuildTest.h"


#include "StdAfx.h"
#include "Builder.h"

Project *project;
string workspace;
int buildNumber;
char *numberFile ;
string buildTime;
string duration;
string result;

Builder::Builder(void)
{

	project = new Project();
	char directory[1000];
	memset(directory,0,sizeof(directory));

	GetCurrentDirectory(1000,directory);

	numberFile= "nextBuildNumber";
	
	workspace.append(directory);

	FILE * fp;

	string filePath = workspace.append("\\").append(numberFile);
	if (fp=fopen(filePath.c_str(),"a+"))
	{
		if(EOF==fscanf(fp,"%d",buildNumber)){
			buildNumber = 0;
		}

		fclose(fp);
	}
}

Builder::Builder(string worksapce){

	numberFile= "nextBuildNumber";
	workspace = worksapce;
	FILE * fp;

	string filePath = workspace.append("\\").append(numberFile);
	if (fp=fopen(filePath.c_str(),"a+"))
	{
		fscanf(fp,"%d",buildNumber);
		
		fclose(fp);
	}

}


Builder::~Builder(void)
{
	delete project;
}

void Builder::SetWorkSpace(string workspace){
	workspace = workspace;
}

bool Builder::GetNodePointer(TiXmlElement* pRootEle, vector<TiXmlElement *> *pNodes)
{
	pNodes->clear();
	TiXmlElement *pEle = pRootEle;
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()){
		pNodes->push_back(pEle);
	}

	return false;
}

bool Builder::GetNodePointerByName(TiXmlElement* pRootEle, string &strNodeName,TiXmlElement* &Node)
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

bool Builder::GetChildNodeByName(TiXmlElement* pRootEle, string &strNodeName,TiXmlElement* &Node){
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

string Builder::ExeCommand(char *pszCmd)
{
	if(NULL == pszCmd){
		return "";
	}
	
	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	HANDLE hRead, hWrite;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return "";
	}

	STARTUPINFO sii = {sizeof(STARTUPINFO)};
	GetStartupInfo(&sii);
	sii.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	sii.wShowWindow = SW_HIDE;
	sii.hStdError = hWrite;
	sii.hStdOutput = hWrite;

	PROCESS_INFORMATION pii;
	if (!CreateProcess(NULL, pszCmd, NULL, NULL, TRUE, NULL, NULL, NULL, &sii, &pii))
	{
		return "";
	}

	DWORD rc = WaitForSingleObject(
		pii.hProcess, // process handle
		INFINITE);


	CloseHandle(hWrite);

	string strRet;
	char buff[1024] = {0};
	DWORD dwRead = 0;
	while (ReadFile(hRead, buff, 1024, &dwRead, NULL))
	{
		strRet.append(buff, dwRead);
	}
	CloseHandle(hRead);

	CloseHandle(pii.hProcess);
	CloseHandle(pii.hThread);
	CloseHandle(sii.hStdError);
	CloseHandle(sii.hStdInput);
	CloseHandle(sii.hStdOutput);

	return strRet;
}

bool Builder::ReadConfigXML(string XmlFile)
{
	int index = XmlFile.find_last_of("\\");
	string fileName = XmlFile.substr(index+1);

	project->SetFileName(fileName);
	TiXmlDocument *pDoc = new TiXmlDocument();
	if(NULL == pDoc){
		return false;

	}

	pDoc->LoadFile(XmlFile.c_str());
	TiXmlElement *pRootEle = pDoc->RootElement();
	if(NULL == pRootEle){
		return false;
	}

	vector<TiXmlElement *> Nodes;
	TiXmlElement *pProjectNodes;
	string entryNode = "Project";
	GetNodePointerByName(pRootEle, entryNode, pProjectNodes);
	//GetNodePointer(pNodes, &Nodes);

	//TiXmlElement *pUrlNode = NULL;
	TiXmlElement *pNode = NULL;
	string IdNode = "Id";
	string NameNode = "Name";
	string SourceCodeNode = "SourceCode";
	string DependencesNode = "Dependences";
	string ProcessNode = "Process";
	string ImportNode = "Import";
	string PublishNode = "Publish";

	if(GetNodePointerByName(pProjectNodes, IdNode, pNode)){
		project->SetId(pNode->GetText());
		if(GetNodePointerByName(pProjectNodes, NameNode, pNode)){
			project->SetName(pNode->GetText());
			//printf("%s\r\n%s\r\n", pUrlNode->GetText(), plockNode->GetText());
			if (GetNodePointerByName(pProjectNodes,SourceCodeNode,pNode))
			{
				string urlNode = "Url";
				string versionNode = "Version";
				string localPathNode = "LocalPath";
				TiXmlElement *pTempNode = pNode;
				SourceCode sourceCode ;
				if (GetChildNodeByName(pTempNode,urlNode,pNode))
				{
					sourceCode.SetUrl(pNode->GetText());
					if (GetChildNodeByName(pTempNode,versionNode,pNode))
					{
						sourceCode.SetVersion(pNode->GetText());
						if (GetChildNodeByName(pTempNode,localPathNode,pNode))
						{
							sourceCode.SetLocalPath(pNode->GetText());

							project->SetSourceCode(sourceCode);
						}else
						{
							return false;	
						}
					}else
					{
						return false;
					}
				}else
				{
					return false;
				}
				if (GetNodePointerByName(pProjectNodes,DependencesNode,pNode))
				{
					string DependenceNode = "Dependence";
					
					GetNodePointer(pNode, &Nodes);
					list<Dependence *> *depList = new list<Dependence *>();
					for (int i=0;i<Nodes.size();i++)
					{
						
							pTempNode = Nodes.at(i);
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
					}
					project->SetDependences(depList);
				}else
				{
					return false;
				}
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
					}
					project->SetBuildStep(buildStep);
				} 
				else
				{
					return false;
				}
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
						}
						step->setItem(itemList);
						importStep->push_back(step);
					}
					project->SetImportStep(importStep);
				}else return false;
				
				if (GetNodePointerByName(pProjectNodes,PublishNode,pNode))
				{
					string url = "Url";
					string category = "Category";
					string component = "Component";
					string version = "Version";
					string importItem = "ImportItem";
					
					Publish publish;
					/*
					pTempNode = pNode;
					if (GetChildNodeByName(pTempNode,url,pNode))
					{
						publish.SetUrl(pNode->GetText());
					}else return false;
					if (GetChildNodeByName(pTempNode,category,pNode))
					{
						publish.SetCategory(pNode->GetText());
					}else return false;
					if (GetChildNodeByName(pTempNode,component,pNode))
					{
						publish.SetComponent(pNode->GetText());
					}else return false;
					if (GetChildNodeByName(pTempNode,version,pNode))
					{
						publish.SetVersion(pNode->GetText());
					}else return false;*/
					GetNodePointer(pTempNode,&Nodes);
					publish.SetUrl(Nodes.at(0)->GetText());
					publish.SetCategory(Nodes.at(1)->GetText());
					publish.SetComponent(Nodes.at(2)->GetText());
					publish.SetVersion(Nodes.at(3)->GetText());
					list<ImportItem *> itemList ;
					for(int i=4;i<Nodes.size();i++){
						string source = "Source";
						string target = "Target";
						ImportItem *item = new ImportItem();
						if (GetChildNodeByName(Nodes.at(i),source,pNode))
						{
							item->SetSource(pNode->GetText());
						}else return false;
						if (GetChildNodeByName(Nodes.at(i),source,pNode))
						{
							item->SetTarget(pNode->GetText());
						}else return false;

						itemList.push_back(item);
					}
					publish.SetImportItem(itemList);
				} 
				else
				{
					return false;
				}
			}
		}
	

	}
	return true;
}

string Builder::ExportSourceCode()
{
	SourceCode sourceCode = project->GetSourceCode();
	return ExportSourceCode(sourceCode.GetUrl(),sourceCode.GetVersion(),sourceCode.GetLocalPath());
}

string Builder::ExportSourceCode(string url,string version,string localPath)
{
	char ExportCmd[255];
	memset(ExportCmd,0,sizeof(ExportCmd));
	
	
	string fullpath(workspace+"\\"+localPath);
	if(version == "head"){
		sprintf(ExportCmd, "svn export --force %s %s", url, fullpath);
	}else{
		sprintf(ExportCmd, "svn export -r %s --force %s %s",version,url,fullpath);
	}

	string log = ExeCommand(ExportCmd);
	
	return log;
}

string Builder::SetEnviroment()
{
	string log;
	list<Dependence *> *depList = project->GetDependences();
	for (list<Dependence *>::iterator iter=depList->begin();iter != depList->end();++iter)
	{
		string flag = (*iter)->GetFlag();
		string server = (*iter)->GetServer();
		string repository = (*iter)->GetRepository();
		string name = (*iter)->GetName();
		string version = (*iter)->GetVersion();
		string path = (*iter)->GetPath();
		string localPath = (*iter)->GetLocalPath();

		log += GetDependences(server,flag,repository,name,version,path,localPath);
		
	}
	return log;
}

string  Builder::GetDependences(string server,string flag,string repository,string name,string version,string path,string localPath)
{
	
	string pArgument = "Flag="+flag+"&Repository="+repository+"&Name="+name+"&Version="+version+"&Path="+path;

	string fullpath(workspace+"\\"+localPath);
	return ExeDownLoad((char *)server.c_str(),(char *)pArgument.c_str(),(char *)fullpath.c_str());
}

string Builder::Process()
{
	list<BuildStep *> *buildStep = project->GetBuildStep();

	string log;
	for (list<BuildStep *>::iterator iter=buildStep->begin();iter != buildStep->end();++iter)
	{
		string name = (*iter)->GetName();
		string program = (*iter)->GetProgram();
		string options = (*iter)->GetOptions();

		log += RunBuildStep(name,program,options);
	}

	return log;
}

string Builder::RunBuildStep(string name, string program,string options)
{
	char BuildCmd[255];
	char Time[255];
	char Temp[100];
	SYSTEMTIME sys;
	

	string fullpath(workspace+"\\"+options);
	sprintf(BuildCmd, "%s %s",program,fullpath);

	GetLocalTime( &sys );
	int minute = sys.wMinute;
	int second = sys.wSecond;
	int millisecond = sys.wMilliseconds;
	sprintf(Time,"%4d/%02d/%02d %02d:%02d:%02d.%03d ",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds);
	string log = ExeCommand(BuildCmd);
	
	GetLocalTime(&sys);
	float dur = (sys.wMinute - minute)*60+second - sys.wSecond + (sys.wMilliseconds-millisecond)/1000;
	sprintf(Temp,"%.4f",dur);
	buildTime.assign(Time);
	duration.assign(Temp);
	result.assign("SUCCESS");


	return log;
}

string Builder::Import()
{
	list<ImportStep *> *importStep = project->GetImportStep();

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
			source.push_back((*iterItem)->GetSource());
			target.push_back((*iterItem)->GetTarget());
		}

		log += ImportLibStep(name,url,source,target);
	}

	return log;
}

string Builder::ImportLibStep(string name,string url, vector<string> source, vector<string> target)
{
	char number[20];
	itoa(buildNumber,number,20);
	string repName(project->GetFileName());
	string artName(project->GetName());
	SourceCode scode = project->GetSourceCode();
	list<DepMessage> depMsgList;
	list<Dependence *> *depList = project->GetDependences();
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

	return ExeUpLoad(url,repName,artName,number,buildTime,duration,result,scode.GetUrl(),scode.GetVersion(),source,target,depMsgList);
	//return ExeUpLoad((char *)url.c_str(),"build",(char *)project->GetFileName().c_str(),(char *)project->GetName().c_str(),number,source,target);
}

string Builder::PublishLibrary()
{
	Publish publish = project->GetPublish();

	list<ImportItem *> itemList = publish.GetImportItem();
	vector<string> source;
	vector<string> target;
	for (list<ImportItem *>::iterator iter = itemList.begin();iter != itemList.end();++iter)
	{
		source.push_back((*iter)->GetSource());
		target.push_back((*iter)->GetTarget());
	}

	return PublishItem(publish.GetUrl(),publish.GetCategory(),publish.GetComponent(),publish.GetVersion(),source,target);
}

string Builder::PublishItem(string url,string category,string component, string version, vector<string> source,vector<string> target)
{
	return ExeUpLoad((char *)url.c_str(),"component",(char *)category.c_str(),(char *)component.c_str(),(char *)version.c_str(),source,target);
}
