// TeamExplorerKernel.h : main header file for the TeamExplorerKernel DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTeamExplorerKernelApp
// See TeamExplorerKernel.cpp for the implementation of this class
//

class CTeamExplorerKernelApp : public CWinApp
{
public:
	CTeamExplorerKernelApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

#define CONFIG_FILE "TeamExplorer.dat"
#define SERVER_FILE "Server.dat"

class __declspec(dllexport) CTeamExplorerKernel{
public:
	CTeamExplorerKernel();
	~CTeamExplorerKernel();

public:
	int m_ConfigFlag;
	BOOL m_SevStatusFlag;

	string m_DepURL;
	string m_ChildURL;
	string m_ConfigPath;
	string m_UserName;
	string m_Password;
	string m_WcPath;
	string m_DepBuffer;

	vector<string> m_AddObjects;
	vector<string> m_OpeObjects;
	vector<string> m_WcPaths;
	vector<string> m_ChildDirs;
	vector<string> m_RetMsgs;
	vector<string> m_IgnoreObjects;
	vector<string> m_NormalObjects;
	vector<string> m_ReadOnlyModifyObjects;

private:
	string CutStr(int from, int to, string srcStr);
	string ExeCmd(char *pszCmd);
	void GetAllObject(LPCSTR Path);
	void GetCheckoutIgnore(string strRet);
	void GetAddChild(LPCSTR Path);
	bool HasModify(string strRet);
	bool HasConflict(string strRet);

public:
	BOOL ChangeDep();
	BOOL FirstSelectDep();
	BOOL GetUserInfo();
	BOOL SetRecordUser();
	int GetChildDir();
	BOOL GetDepURL();
	BOOL IsFirstUse();

	BOOL IsInputRight(char *pServerURL, char *pUserName, char *pPassword);
	void GetDepInfo(char *pServerURL, char *pUserName, char *pPassword);

	BOOL ExeShowLog(char *pPath);
	BOOL ExeMerge(char *pFromURL, char *pToPath, char *pVersion);
	BOOL ExeMerge(char *pFromURL, char *pToPath, char *pFromVersion, char *pToVersion);
	BOOL ExeRevert(char *pPath);
	BOOL ExeAdd(char *pPath);
	BOOL ExeCancel(int PathType, char *pPath);
	BOOL ExeUnlock(int iIndex);
	BOOL ExeCheckin(char *pLog);
	void ExeDealAdd(LPCSTR Path);
	BOOL ExeCommit(char *pLog);
	void ExeUpdate(char *pPath);
	BOOL ExeCheckout(char *pFilePath);
	void ExeSetEnv(char *pChildURL, char *pWcPath);
	void ExeSetEnv(char *pChildURL, char *pWcPath, char *pRevision);

	void AddRetMsg(char *pRetMsg);
	void AddOpeObject(char *pOpeObject);
	void AddIgnoreObject(char *pIgnoreObject);
	void AddAddObject(char *pAddObject);
	void AddWcPath(char *pWcPath);
	void AddNormalObject(char *pNormalObject);

	void ClearRetMsg();
	void ClearOpeObjects();
	void ClearAddObjects();
	void ClearIgnoreObjects();
	void ClearChildDirs();
	void ClearNormalObjects();
	void ClearReadOnlyModifyObjects();

	BOOL GetConfigPath(char *pConfigPath);
	BOOL GetServerURL(char *pConfigPath, char *pServerURL);
	BOOL GetCrtVersion(char *pDepURL);
	BOOL GetWcURL(char *pPath, char *pWcURL);
	void GetReadOnlyModifyObject(char *pWcPath);
	void GetRevertObject();
	void GetAddObject();
	void GetCancelObject();
	void GetCheckinObject();
	void GetCommitObject();
	void GetCheckoutObject();
	void GetDepName(int from, int to, char *pDepName);
	
	BOOL SaveServerURL(char *pConfigPath, char *pServerURL);
	void SetWcPath(char *pWcPath);
	void SetChildURL(char *pChildURL);
	void SetUserName(char *pUserName);
	void SetPassword(char *pPassword);
	void SetDepURL(char *pDepURL);
};