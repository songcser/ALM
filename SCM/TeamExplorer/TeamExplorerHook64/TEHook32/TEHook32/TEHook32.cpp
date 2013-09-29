// TEHook32.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include "TEHook32Dll.h"
#pragma comment(lib, "TEHook32Dll.lib")

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main(int argc, char **argv[])
{
	InstallHookProc(TRUE);

	Sleep(INFINITE);

	InstallHookProc(FALSE);

	return 0;
}

