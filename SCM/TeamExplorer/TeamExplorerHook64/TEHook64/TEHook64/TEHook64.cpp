// TEHook64.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include "TEHook64Dll.h"
#pragma comment(lib, "TEHook64Dll.lib")

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main(int argc, char **argv[])
{
	InstallHookProc(TRUE);

	Sleep(INFINITE);

	InstallHookProc(FALSE);

	return 0;
}


