#define WINVER       0x0500
#include "CmnHdr.h"
#include <WindowsX.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <shlwapi.h>
#include "APIHook.h"
using namespace std;

#define LASTMSGBOXINFOLIBAPI extern "C" __declspec(dllexport)
#include "ProtectDelete.h"

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

typedef BOOL (WINAPI *PFNMOVEFILEA)(__in LPCSTR lpExistingFileName, __in LPCSTR lpNewFileName);
typedef BOOL (WINAPI *PFNMOVEFILEW)(__in LPCWSTR lpExistingFileName, __in LPCWSTR lpNewFileName);
typedef BOOL (WINAPI *PFNDELETEFILEA)(__in LPCSTR lpFileName);
typedef BOOL (WINAPI *PFNDELETEFILEW)(__in LPCWSTR lpFileName);
typedef BOOL (WINAPI *PFNREMOVEDIRECTORYA)(__in LPCSTR lpPathName);
typedef BOOL (WINAPI *PFNREMOVEDIRECTORYW)(__in LPCWSTR lpPathName);
typedef int (WINAPI *PFNMESSAGEBOXA)(HWND hWnd, PCSTR pszText, PCSTR pszCaption, UINT uType);
typedef int (WINAPI *PFNMESSAGEBOXW)(HWND hWnd, PCWSTR pszText, PCWSTR pszCaption, UINT uType);

extern CAPIHook g_MoveFileA;
extern CAPIHook g_MoveFileW;
extern CAPIHook g_DeleteFileA;
extern CAPIHook g_DeleteFileW;
extern CAPIHook g_RemoveDirectoryA;
extern CAPIHook g_RemoveDirectoryW;
extern CAPIHook g_MessageBoxA;
extern CAPIHook g_MessageBoxW;

BOOL WINAPI Hook_MoveFileA(__in LPCSTR lpExistingFileName, __in LPCSTR lpNewFileName)
{
	char tSourcePath[1024];
	memset(tSourcePath, 0, sizeof(tSourcePath));
	wsprintfA(tSourcePath, "%s", lpExistingFileName);
	
	string sSourcePath(tSourcePath);
	if(!NeedProtect(sSourcePath)){
		return ((PFNMOVEFILEA)(PROC)g_MoveFileA)(lpExistingFileName, lpNewFileName);
	}

	return FALSE;
}

BOOL WINAPI Hook_MoveFileW(__in LPCWSTR lpExistingFileName, __in LPCWSTR lpNewFileName)
{
	char tSourcePath[1024];
	memset(tSourcePath, 0, sizeof(tSourcePath));
	wsprintfA(tSourcePath, "%S", lpExistingFileName);

	string sSourcePath(tSourcePath);
	if(!NeedProtect(sSourcePath)){
		return ((PFNMOVEFILEW)(PROC)g_MoveFileW)(lpExistingFileName, lpNewFileName);
	}

	return FALSE;
}

BOOL WINAPI Hook_DeleteFileA(__in LPCSTR lpFileName)
{
	char tDestPath[1024];
	memset(tDestPath, 0, sizeof(tDestPath));
	wsprintfA(tDestPath, "%s", lpFileName);

	string sDestPath(tDestPath);
	if(!NeedProtect(sDestPath)){
		return ((PFNDELETEFILEA)(PROC)g_DeleteFileA)(lpFileName);
	}
	
	return FALSE;
}

BOOL WINAPI Hook_DeleteFileW(__in LPCWSTR lpFileName)
{
	char tDestPath[1024];
	memset(tDestPath, 0, sizeof(tDestPath));
	wsprintfA(tDestPath, "%S", lpFileName);

	string sDestPath(tDestPath);
	if(!NeedProtect(sDestPath)){
		return ((PFNDELETEFILEW)(PROC)g_DeleteFileW)(lpFileName);
	}
	
	return FALSE;
}

BOOL WINAPI Hook_RemoveDirectoryA(__in LPCSTR lpPathName)
{
	char tDestPath[1024];
	memset(tDestPath, 0, sizeof(tDestPath));
	wsprintfA(tDestPath, "%s", lpPathName);

	string sDestPath(tDestPath);
	if(!NeedProtect(sDestPath)){
		return ((PFNREMOVEDIRECTORYA)(PROC)g_RemoveDirectoryA)(lpPathName);
	}

	return FALSE;
}

BOOL WINAPI Hook_RemoveDirectoryW(__in LPCWSTR lpPathName)
{
	char tDestPath[1024];
	memset(tDestPath, 0, sizeof(tDestPath));
	wsprintfA(tDestPath, "%S", lpPathName);

	string sDestPath(tDestPath);
	if(!NeedProtect(sDestPath)){
		return ((PFNREMOVEDIRECTORYW)(PROC)g_RemoveDirectoryW)(lpPathName);
	}

	return FALSE;
}

int WINAPI Hook_MessageBoxW(HWND hWnd, PCWSTR pszText, PCWSTR pszCaption, UINT uType)
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

	int nResult = ((PFNMESSAGEBOXW)(PROC) g_MessageBoxW)(hWnd, uText, uCaption, uType);

	return(nResult);
}

int WINAPI Hook_MessageBoxA(HWND hWnd, PCSTR pszText, PCSTR pszCaption, UINT uType)
{
	char tCaption[1024];
	char tText[1024];
	memset(tCaption, 0, sizeof(tCaption));
	memset(tText, 0, sizeof(tText));
	wsprintfA(tText, "%s", pszText);
	wsprintfA(tCaption, "%s", pszCaption);

	PSTR uCaption, uText;
	string sText(tText);

	if(!strcmp(tCaption, "Error Deleting File or Folder") && string::npos != sText.find("Cannot delete") && (string::npos != sText.find("The pipe has been ended") || string::npos != sText.find("The parameter is incorrect"))){
		uCaption = "Protect .svn";
		uText = "Cannot delete .svn\r\nsome files had been locked in working Copy";
	}
	else{
		uCaption = (PSTR)pszCaption;
		uText = (PSTR)pszText;
	}

	int nResult = ((PFNMESSAGEBOXA)(PROC) g_MessageBoxA)(hWnd, uText, uCaption, uType);

	return(nResult);
}

CAPIHook g_MoveFileA("Kernel32.dll", "MoveFileA", (PROC)Hook_MoveFileA, TRUE);
CAPIHook g_MoveFileW("Kernel32.dll", "MoveFileW", (PROC)Hook_MoveFileW, TRUE);
CAPIHook g_DeleteFileA("Kernel32.dll", "DeleteFileA", (PROC)Hook_DeleteFileA, TRUE);
CAPIHook g_DeleteFileW("Kernel32.dll", "DeleteFileW", (PROC)Hook_DeleteFileW, TRUE);
CAPIHook g_RemoveDirectoryA("Kernel32.dll", "RemoveDirectoryA", (PROC)Hook_RemoveDirectoryA, TRUE);
CAPIHook g_RemoveDirectoryW("Kernel32.dll", "RemoveDirectoryW", (PROC)Hook_RemoveDirectoryW, TRUE);
CAPIHook g_MessageBoxA("User32.dll", "MessageBoxA", (PROC)Hook_MessageBoxA, TRUE);
CAPIHook g_MessageBoxW("User32.dll", "MessageBoxW", (PROC)Hook_MessageBoxW, TRUE);

#pragma data_seg("Shared")
HHOOK g_hhook = NULL;
#pragma data_seg()
#pragma comment(linker, "/Section:Shared,rws")

static LRESULT WINAPI GetMsgProc(int code, WPARAM wParam, LPARAM lParam) 
{
	return(CallNextHookEx(g_hhook, code, wParam, lParam));
}

static HMODULE ModuleFromAddress(PVOID pv) 
{
	MEMORY_BASIC_INFORMATION mbi;
	return((VirtualQuery(pv, &mbi, sizeof(mbi)) != 0)?(HMODULE)mbi.AllocationBase:NULL);
}

BOOL WINAPI ProtectDelete_HookAllApps(BOOL fInstall, DWORD dwThreadId) 
{
	BOOL fOk;

	if (fInstall){
		chASSERT(g_hhook == NULL);
		g_hhook = SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, ModuleFromAddress(ProtectDelete_HookAllApps), dwThreadId);
		fOk = (g_hhook != NULL);
	}
	else{
		chASSERT(g_hhook != NULL);
		fOk = UnhookWindowsHookEx(g_hhook);
		g_hhook = NULL;
	}

	return(fOk);
}