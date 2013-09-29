// StartHook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CmnHdr.h"
#include <windowsx.h>
#include <tchar.h>
#include "ProtectDelete.h"
#include "ReadOnlyHook.h"
#pragma comment(lib, "TeamExplorerHook.lib")
#pragma comment(lib, "ReadOnlyHook.lib")

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PTSTR pszCmdLine, int nCmdShow)
{
	DWORD dwThreadId = 0;
	ProtectDelete_HookAllApps(TRUE, dwThreadId);
	//InstallHookProc(TRUE);

	//Sleep(INFINITE);
	Sleep(100000);

	ProtectDelete_HookAllApps(FALSE, 0);
	//InstallHookProc(FALSE);

	return 0;
}

