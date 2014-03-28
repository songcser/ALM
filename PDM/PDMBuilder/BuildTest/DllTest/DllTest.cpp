// DllTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BuildTest.h"

using namespace std;

#pragma comment(lib,"BuildTest.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	Builder *builder = new Builder();
	builder->ReadConfigXML("E:\\workspace\\PDMBuilder\\BuildTest\\P-EF.xml");
	return 0;
}

