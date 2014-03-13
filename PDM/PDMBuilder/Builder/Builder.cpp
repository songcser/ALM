// Builder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PDMBuilder.h"
#include <string>
#pragma comment(lib,"PDMBuilder.lib")

using namespace std;

int main(int argc, char* argv[])
{
	if (argc<3)
	{
		return -1;
	}
	string workspace(argv[1]);
	char *configFile = argv[2];
	string flag = "";
	if (argc==4)
	{
		flag.assign(argv[3]);
	}
	//string workspace = "E:\\Test\\Test7";
	string log;
	//char *configFile = "E:\\Test\\P-EF.xml";
	setWorkSpace(workspace,flag);
	setConfigXML(configFile);

	if (!checkSourceCode()&&flag=="false")
	{
		//printf("")
	//	getchar();
		return 1;
	}
	string temp;
	getRelyFiles((char *)workspace.c_str(),temp);

	//string logpath(ws);
	writelog(temp,workspace+"\\log");
//	getchar();
	log += temp;
	//updateRelyFiles(workspace);
	log += process();

	log += import();

	log += publish();
//	getchar();
	log += clean();
	
	//printf("%s",log.c_str());
//	getchar();
	return 0;
}

