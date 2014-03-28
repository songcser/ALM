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
	//printf("%s\n",workspace.c_str());
	char *configFile = argv[2];
	//printf("%s\n",configFile);
	string flag = "";
	string username = "";
	string userpassword = "";
	if (argc==6)
	{
		flag.assign(argv[3]);
		//printf("%s\n",flag.c_str());
		username.assign(argv[4]);
		//printf("%s\n",username.c_str());
		userpassword.assign(argv[5]);
		//printf("%s\n",userpassword.c_str());
	}
	//string workspace = "E:\\Test\\Test7";
	string log;
	//char *configFile = "E:\\Test\\P-EF.xml";
	//printf("setxml\n");
	setConfigXML(configFile);
	setWorkSpace(workspace,flag,username,userpassword);
	
	if (!checkSourceCode()&&flag=="false")
	{
		//printf("")
	//	getchar();
		return 1;
	}
	//printf("checkout\n");
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
	
//	printf("%s",log.c_str());
//	getchar();
	return 0;
}

