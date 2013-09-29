// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "TEHook32Dll.h"
#include "detours.h"
#pragma comment(lib, "detours.lib")


#pragma data_seg(".WXW32")
HHOOK g_hHook = NULL; 
#pragma data_seg()
#pragma comment(linker,"/section:.WXW32,rws")

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

BOOL NeedProtect(string sCrtPath)
{
	string sWcPath;
	int pos = sCrtPath.find("\\.svn");

	if(string::npos != pos && pos > 1){
		sWcPath = sCrtPath.substr(0, pos);
		string sStatusCmd = "svn status --non-interactive \"" + sWcPath + "\"";
		string strRet = ExeCmd((char *)sStatusCmd.c_str());
		if(string::npos != strRet.find("K  ")){
			return TRUE;
		}
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
					CopyCreateFileW(NULL, dwDesiredAccess,dwShareMode,
						lpSecurityAttributes,dwCreationDisposition,
						dwFlagsAndAttributes,hTemplateFile);
					return INVALID_HANDLE_VALUE;
				}
			}
		}
	}

	return CopyCreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
		lpSecurityAttributes, dwCreationDisposition,
		dwFlagsAndAttributes, hTemplateFile);
}

static BOOL (WINAPI *CopyMoveFileW)(__in LPCWSTR lpExistingFileName, __in LPCWSTR lpNewFileName) = MoveFileW;

BOOL WINAPI Bio_MoveFileW(__in LPCWSTR lpExistingFileName, __in LPCWSTR lpNewFileName)
{
	char tSourcePath[1024];
	memset(tSourcePath, 0, sizeof(tSourcePath));
	wsprintfA(tSourcePath, "%S", lpExistingFileName);

	string sSourcePath(tSourcePath);
	if(!NeedProtect(sSourcePath)){
		return CopyMoveFileW(lpExistingFileName, lpNewFileName);
	}

	return FALSE;
}

static BOOL (WINAPI *CopyDeleteFileW)(__in LPCWSTR lpFileName) = DeleteFileW;

BOOL WINAPI Bio_DeleteFileW(__in LPCWSTR lpFileName)
{
	char tDestPath[1024];
	memset(tDestPath, 0, sizeof(tDestPath));
	wsprintfA(tDestPath, "%S", lpFileName);

	string sDestPath(tDestPath);
	if(!NeedProtect(sDestPath)){
		return CopyDeleteFileW(lpFileName);
	}

	return FALSE;
}

static BOOL (WINAPI *CopyRemoveDirectoryW)(__in LPCWSTR lpPathName) = RemoveDirectoryW;

BOOL WINAPI Bio_RemoveDirectoryW(__in LPCWSTR lpPathName)
{
	char tDestPath[1024];
	memset(tDestPath, 0, sizeof(tDestPath));
	wsprintfA(tDestPath, "%S", lpPathName);

	string sDestPath(tDestPath);
	if(!NeedProtect(sDestPath)){
		return CopyRemoveDirectoryW(lpPathName);
	}

	return FALSE;
}

static int (WINAPI *CopyMessageBoxW)(HWND hWnd, PCWSTR pszText, PCWSTR pszCaption, UINT uType) = MessageBoxW;

int WINAPI Bio_MessageBoxW(HWND hWnd, PCWSTR pszText, PCWSTR pszCaption, UINT uType)
{
	char tCaption[1024];
	char tText[1024];
	memset(tCaption, 0, sizeof(tCaption));
	memset(tText, 0, sizeof(tText));
	wsprintfA(tText, "%S", pszText);
	wsprintfA(tCaption, "%S", pszCaption);

	PWSTR uCaption, uText;
	string sText(tText);

	if(!strcmp(tCaption, "Error Deleting File or Folder") && string::npos != sText.find("Cannot delete") && (string::npos != sText.find("The pipe has been ended") || string::npos != sText.find("The parameter is incorrect"))){
		uCaption = L"Protect .svn";
		uText = L"Cannot delete .svn\r\nsome files had been locked in working Copy";
	}
	else{
		uCaption = (PWSTR)pszCaption;
		uText = (PWSTR)pszText;
	}

	int nResult = CopyMessageBoxW(hWnd, uText, uCaption, uType);

	return(nResult);
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
		DetourAttach(&(PVOID&)CopyMoveFileW, Bio_MoveFileW);
		DetourAttach(&(PVOID&)CopyDeleteFileW, Bio_DeleteFileW);
		DetourAttach(&(PVOID&)CopyRemoveDirectoryW, Bio_RemoveDirectoryW);
		DetourAttach(&(PVOID&)CopyMessageBoxW, Bio_MessageBoxW);
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
		DetourDetach(&(PVOID&)CopyMoveFileW, Bio_MoveFileW);
		DetourDetach(&(PVOID&)CopyDeleteFileW, Bio_DeleteFileW);
		DetourDetach(&(PVOID&)CopyRemoveDirectoryW, Bio_RemoveDirectoryW);
		DetourDetach(&(PVOID&)CopyMessageBoxW, Bio_MessageBoxW);
		DetourTransactionCommit();
		break;
	}
	return TRUE;
}


LRESULT	WINAPI MsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	return (CallNextHookEx(NULL, code, wParam, lParam));
}

extern "C" TEHOOK32DLL_API LRESULT WINAPI InstallHookProc(BOOL bInstall)
{
	if(bInstall){
		g_hHook	= SetWindowsHookEx(WH_GETMESSAGE, MsgProc, g_hDll, 0 );
	}
	else{
		UnhookWindowsHookEx(g_hHook);
	}

	return 1;
}
