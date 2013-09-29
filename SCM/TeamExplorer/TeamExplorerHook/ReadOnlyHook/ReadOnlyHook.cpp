// dllmain.cpp : Defines the entry point for the DLL application.
// ReadOnlyHook.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <shellapi.h>
#include "ReadOnlyHook.h"
#include "detours.h"
#pragma comment(lib, "detours.lib")


#pragma data_seg(".WXW")
HHOOK g_hHook = NULL; 
#pragma data_seg()
#pragma comment(linker,"/section:.WXW,rws")


string ExeCmd(char *pszCmd)
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

	return strRet;
}

bool GetFatherPath(string sCrtPath, string &sFatherPath)
{
	int pos = sCrtPath.rfind('\\');
	if(pos == string::npos){
		return false;
	}

	sFatherPath = sCrtPath.substr(0, pos);

	return true;
}

BOOL IsWorkCopy(string sCrtPath, string &sWcPath)
{
	string sSvnPath, sFathPath;

	while(1){
		sSvnPath = sCrtPath + "\\.svn";
		if(PathFileExists(sSvnPath.c_str())){
			sWcPath = sCrtPath;
			break;
		}
		else{
			if(!GetFatherPath(sCrtPath, sFathPath)){
				return FALSE;
			}
			sCrtPath = sFathPath;
			sFathPath = "";
		}
	}

	return TRUE;
}

BOOL IsReadOnly(string sCrtPath)
{
	if(sCrtPath.find("\\.svn") != sCrtPath.npos){
		return FALSE;
	}

	string sStatusCmd = "svn status --non-interactive \"" + sCrtPath + "\"";
	string strRet = ExeCmd((char *)sStatusCmd.c_str());
	if(strRet.length() < 8){
		return TRUE;
	}

	return FALSE;
}

HMODULE	g_hDll = NULL;
//HHOOK g_hHook = NULL;

DETOUR_TRAMPOLINE(HANDLE WINAPI CopyCreateFileW(LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile), CreateFileW);

HANDLE WINAPI Bio_CreateFileW( LPCWSTR lpFileName, 
	DWORD dwDesiredAccess, 
	DWORD dwShareMode, 
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
	DWORD dwCreationDisposition, 
	DWORD dwFlagsAndAttributes, 
	HANDLE hTemplateFile )
{
	/*

	*/

	if((dwDesiredAccess == (GENERIC_WRITE | GENERIC_READ)) || (dwDesiredAccess == GENERIC_WRITE)){
		char tDestPath[1024];
		memset(tDestPath, 0, sizeof(tDestPath));
		wsprintfA(tDestPath, "%S", lpFileName);

		string sWcPath;
		if(IsWorkCopy(tDestPath, sWcPath)){
			if(PathFileExists(tDestPath) && (GetFileAttributes(tDestPath) != FILE_ATTRIBUTE_DIRECTORY)){
				if(IsReadOnly(tDestPath)){
					char szMsg[MAX_PATH];
					sprintf( szMsg, "Hook it! 文件:%s \n\n确定要继续吗？", lpFileName );

					if( IDNO == MessageBox( NULL, szMsg, "操作确认", MB_YESNO ) )
					{
						CopyCreateFileW( NULL, dwDesiredAccess,dwShareMode,
							lpSecurityAttributes,dwCreationDisposition,
							dwFlagsAndAttributes,hTemplateFile );
						return	INVALID_HANDLE_VALUE;
					}
				}
			}
		}
	}

	return CopyCreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
		lpSecurityAttributes, dwCreationDisposition,
		dwFlagsAndAttributes, hTemplateFile);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hDll = hModule;
		DetourFunctionWithTrampoline((PBYTE)CopyCreateFileW, (PBYTE)Bio_CreateFileW);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		DetourRemove((PBYTE)CopyCreateFileW, (PBYTE)Bio_CreateFileW);
		break;
	}
	return TRUE;
}

LRESULT	WINAPI MsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	return (CallNextHookEx(NULL, code, wParam, lParam));
}

READONLYHOOK_API LRESULT WINAPI InstallHookProc(BOOL bInstall)
{
	if(bInstall){
		g_hHook	= SetWindowsHookEx(WH_GETMESSAGE, MsgProc, g_hDll, 0 );
	}
	else{
		UnhookWindowsHookEx(g_hHook);
	}

	return 1;
}



