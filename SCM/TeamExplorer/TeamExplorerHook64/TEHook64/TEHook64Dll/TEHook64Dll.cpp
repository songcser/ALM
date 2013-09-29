// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "TEHook64Dll.h"
#include "detours.h"
#pragma comment(lib, "detours.lib")


#pragma data_seg(".WXW64")
HHOOK g_hHook = NULL; 
#pragma data_seg()
#pragma comment(linker,"/section:.WXW64,rws")

HMODULE	g_hDll = NULL;


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
	if(pos == string::npos || pos == 0){
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

	if(!memcmp(sCrtPath.c_str(), "C:\\Documents and Settings", strlen("C:\\Documents and Settings")) && (string::npos == sCrtPath.find("\\Desktop"))){
		return FALSE;
	}

	if(!memcmp(sCrtPath.c_str(), "C:\\Users", strlen("C:\\Users")) && (string::npos == sCrtPath.find("\\Desktop"))){
		return FALSE;
	}

	string sStatusCmd = "svn status --non-interactive \"" + sCrtPath + "\"";
	string strRet = ExeCmd((char *)sStatusCmd.c_str());
	if(strRet.length() == 0){
		return TRUE;
	}

	return FALSE;
}


static HANDLE (WINAPI * CopyCreateFileW)(LPCWSTR lpFileName, 
	DWORD dwDesiredAccess, 
	DWORD dwShareMode, 
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
	DWORD dwCreationDisposition, 
	DWORD dwFlagsAndAttributes, 
	HANDLE hTemplateFile) = CreateFileW;

HANDLE WINAPI Bio_CreateFileW( LPCWSTR lpFileName, 
	DWORD dwDesiredAccess, 
	DWORD dwShareMode, 
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
	DWORD dwCreationDisposition, 
	DWORD dwFlagsAndAttributes, 
	HANDLE hTemplateFile )
{
	if((dwDesiredAccess == (GENERIC_WRITE | GENERIC_READ)) || (dwDesiredAccess == GENERIC_WRITE)){
		char tDestPath[1024];
		memset(tDestPath, 0, sizeof(tDestPath));
		wsprintfA(tDestPath, "%S", lpFileName);

		if(0 == dwShareMode){
			return CopyCreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
				lpSecurityAttributes, dwCreationDisposition,
				dwFlagsAndAttributes, hTemplateFile);
		}

		if((dwFlagsAndAttributes & FILE_ATTRIBUTE_READONLY) == FILE_ATTRIBUTE_READONLY){
			return CopyCreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
				lpSecurityAttributes, dwCreationDisposition,
				dwFlagsAndAttributes, hTemplateFile);
		}

		if((dwFlagsAndAttributes & FILE_ATTRIBUTE_COMPRESSED) == FILE_ATTRIBUTE_COMPRESSED){
			return CopyCreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
				lpSecurityAttributes, dwCreationDisposition,
				dwFlagsAndAttributes, hTemplateFile);
		}

		if((dwFlagsAndAttributes & FILE_FLAG_DELETE_ON_CLOSE) == FILE_FLAG_DELETE_ON_CLOSE){
			return CopyCreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
				lpSecurityAttributes, dwCreationDisposition,
				dwFlagsAndAttributes, hTemplateFile);
		}

		string stDp(tDestPath);
		if(PathIsNetworkPath(tDestPath) || PathIsUNC(tDestPath) || PathIsRelative(tDestPath) || string::npos != stDp.find(".zip")){
			return CopyCreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
				lpSecurityAttributes, dwCreationDisposition,
				dwFlagsAndAttributes, hTemplateFile);
		}

		string sWcPath;
		string sDestPath(tDestPath);
		int pos = sDestPath.find(":\\");
		if(1 == pos && (CREATE_ALWAYS == dwCreationDisposition || OPEN_ALWAYS == dwCreationDisposition) && IsWorkCopy(tDestPath, sWcPath)){
			if(PathFileExists(tDestPath) && (GetFileAttributes(tDestPath) != FILE_ATTRIBUTE_DIRECTORY)){
				if(IsReadOnly(tDestPath)){
					CopyCreateFileW( NULL, dwDesiredAccess,dwShareMode,
						lpSecurityAttributes,dwCreationDisposition,
						dwFlagsAndAttributes,hTemplateFile );
					return INVALID_HANDLE_VALUE;
				}
			}
		}
	}

	return CopyCreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
		lpSecurityAttributes, dwCreationDisposition,
		dwFlagsAndAttributes, hTemplateFile);
}


BOOL APIENTRY DllMain( HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hDll = hModule;
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)CopyCreateFileW, Bio_CreateFileW);
		DetourTransactionCommit();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)CopyCreateFileW, Bio_CreateFileW);
		DetourTransactionCommit();
		break;
	}

	return TRUE;
}


LRESULT	WINAPI MsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	return (CallNextHookEx(NULL, code, wParam, lParam));
}

extern "C" TEHOOK64DLL_API LRESULT WINAPI InstallHookProc(BOOL bInstall)
{
	if(bInstall){
		g_hHook	= SetWindowsHookEx(WH_GETMESSAGE, MsgProc, g_hDll, 0 );
	}
	else{
		UnhookWindowsHookEx(g_hHook);
	}

	return 1;
}

