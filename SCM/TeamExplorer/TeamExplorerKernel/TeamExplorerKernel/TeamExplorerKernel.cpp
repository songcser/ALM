// TeamExplorerKernel.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "TeamExplorerKernel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CTeamExplorerKernelApp
BEGIN_MESSAGE_MAP(CTeamExplorerKernelApp, CWinApp)
END_MESSAGE_MAP()

// CTeamExplorerKernelApp construction
CTeamExplorerKernelApp::CTeamExplorerKernelApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CTeamExplorerKernelApp object
CTeamExplorerKernelApp theApp;

// CTeamExplorerKernelApp initialization

BOOL CTeamExplorerKernelApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

void CTeamExplorerKernel::GetAddChild(LPCSTR Path)
{
	if(NULL == Path){
		return;
	}

	if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(Path)){
		m_OpeObjects.push_back(Path);
		return;
	}
	else{
		m_OpeObjects.push_back(Path);
	}

	WIN32_FIND_DATA FindData;  
	HANDLE hError;  
	int FileCount = 0;  
	char FilePathName[255];
	char FullPathName[255];

	strcpy(FilePathName, Path);  
	strcat(FilePathName, "\\*.*");  
	hError = FindFirstFile(FilePathName, &FindData);  

	if (hError == INVALID_HANDLE_VALUE){
		FindClose(hError);
		return;  
	}

	while(::FindNextFile(hError, &FindData)){  
		if(strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0 ){  
			continue;  
		}

		memset(FullPathName, 0, sizeof(FullPathName));
		wsprintf(FullPathName, "%s\\%s", Path,FindData.cFileName);  
		FileCount++;  

		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			int len = strlen(FullPathName);
			if(!memcmp(FullPathName+len-4, ".svn", 4)){
				continue;
			}

			GetAddChild(FullPathName);
		}
		else{
			m_OpeObjects.push_back(FullPathName);
		}
	}

	FindClose(hError);

	return;
}

void CTeamExplorerKernel::GetCheckoutIgnore(string strRet)
{
	while(strRet.length() > 8){
		int tmpPos = strRet.find("\r");
		if(tmpPos == string::npos){
			break;
		}

		if(0 != strRet.find("M       ")){
			string sIgnore = CutStr(8, tmpPos, strRet);
			m_IgnoreObjects.push_back(sIgnore);
		}

		if((strRet.length() - (tmpPos+2)) > 8){
			strRet = strRet.substr(tmpPos+2, strRet.length());
		}
		else{
			break;
		}
	}
}

void CTeamExplorerKernel::GetAllObject(LPCSTR Path)
{
	if(NULL == Path){
		return;
	}

	if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(Path)){
		m_OpeObjects.push_back(Path);
		return;
	}

	WIN32_FIND_DATA FindData;  
	HANDLE hError;  
	int FileCount = 0;  
	char FilePathName[255];
	char FullPathName[255];

	strcpy(FilePathName, Path);  
	strcat(FilePathName, "\\*.*");  
	hError = FindFirstFile(FilePathName, &FindData);  

	if (hError == INVALID_HANDLE_VALUE){
		FindClose(hError);
		return;  
	}

	while(::FindNextFile(hError, &FindData)){  
		if(strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0 ){  
			continue;  
		}

		memset(FullPathName, 0, sizeof(FullPathName));
		wsprintf(FullPathName, "%s\\%s", Path,FindData.cFileName);  
		FileCount++;  

		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			int len = strlen(FullPathName);
			if(!memcmp(FullPathName+len-4, ".svn", 4)){
				continue;
			}

			GetAllObject(FullPathName);
		}
		else{
			m_OpeObjects.push_back(FullPathName);
		}
	}

	FindClose(hError);

	return;
}  

string CTeamExplorerKernel::CutStr(int from, int to, string srcStr)
{
	string strRet = "";

	if(from < 0 || to > srcStr.length() || to - from >= 1024){
		return strRet;
	}

	char cRet[1024];
	memset(cRet, 0, sizeof(cRet));

	int j = 0;
	for(int i = from; i < to; i++){
		cRet[j] = srcStr[i];
		j++;
	}

	strRet += cRet;

	return strRet;
}

string CTeamExplorerKernel::ExeCmd(char *pszCmd)
{
	if(NULL == pszCmd){
		return "";
	}

	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	HANDLE hRead, hWrite;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0)){
		return "";
	}

	STARTUPINFO sii = {sizeof(STARTUPINFO)};
	GetStartupInfo(&sii);
	sii.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	sii.wShowWindow = SW_HIDE;
	sii.hStdError = hWrite;
	sii.hStdOutput = hWrite;

	PROCESS_INFORMATION pii;
	if (!CreateProcess(NULL, pszCmd, NULL, NULL, TRUE, NULL, NULL, NULL, &sii, &pii)){
		return "";
	}

	CloseHandle(hWrite);

	string strRet;
	char buff[1024] = {0};
	DWORD dwRead = 0;
	while (ReadFile(hRead, buff, 1024, &dwRead, NULL)){
		strRet.append(buff, dwRead);
	}

	CloseHandle(hRead);
	CloseHandle(pii.hProcess);
	CloseHandle(pii.hThread);

	return strRet;
}

bool CTeamExplorerKernel::HasConflict(string strRet)
{
	if(strRet.length() >= 8){
		strRet = strRet.substr(0, 8);
		if(strRet.find("C") != strRet.npos && strRet.find("K  ") != strRet.npos){
			return true;
		}
	}

	return false;
}

bool CTeamExplorerKernel::HasModify(string strRet)
{
	if(strRet.length() >= 8){
		strRet = strRet.substr(0, 8);
		if(strRet.find("C") == strRet.npos && strRet.find("M") != strRet.npos && strRet.find("K  ") != strRet.npos){
			return true;
		}
	}

	return false;
}

CTeamExplorerKernel::CTeamExplorerKernel()
{
	m_DepBuffer = "";
}

CTeamExplorerKernel::~CTeamExplorerKernel()
{
	
}

BOOL CTeamExplorerKernel::ExeShowLog(char *pPath)
{
	if(NULL == pPath){
		return FALSE;
	}

	string sShowLogCmd = "svn log --non-interactive \"";
	sShowLogCmd += pPath;
	sShowLogCmd += "\"";

	string strRet = ExeCmd((char *)sShowLogCmd.c_str());
	if(0 == strRet.find("svn: ")){
		strRet += pPath;
		strRet += " not in repository.\r\n";
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}

	m_RetMsgs.push_back(strRet);

	return TRUE;
}

BOOL CTeamExplorerKernel::ExeMerge(char *pFromURL, char *pToPath, char *pVersion)
{
	if(NULL == pToPath || NULL == pFromURL || NULL == pVersion){
		return FALSE;
	}

	string sRevertCmd = "svn merge -c ";
	sRevertCmd += pVersion;
	sRevertCmd += " --non-interactive --accept p \"";
	sRevertCmd += pFromURL;
	sRevertCmd += "\" \"";
	sRevertCmd += pToPath;
	sRevertCmd += "\"";

	string strRet = ExeCmd((char *)sRevertCmd.c_str());
	if(0 == strRet.find("svn: ")){
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}
	else if(string::npos != strRet.find("Summary of conflicts:")){
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}

	m_RetMsgs.push_back(strRet);

	return TRUE;
}

BOOL CTeamExplorerKernel::ExeMerge(char *pFromURL, char *pToPath, char *pFromVersion, char *pToVersion)
{
	if(NULL == pToPath || NULL == pFromURL || NULL == pFromVersion || NULL == pToVersion){
		return FALSE;
	}
	
	string sRevertCmd = "svn merge -r ";
	sRevertCmd += pFromVersion;
	sRevertCmd += ":";
	sRevertCmd += pToVersion;
	sRevertCmd += " --non-interactive --accept p \"";
	sRevertCmd += pFromURL;
	sRevertCmd += "\" \"";
	sRevertCmd += pToPath;
	sRevertCmd += "\"";

	string strRet = ExeCmd((char *)sRevertCmd.c_str());
	if(0 == strRet.find("svn: ")){
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}
	else if(string::npos != strRet.find("Summary of conflicts:")){
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}

	m_RetMsgs.push_back(strRet);
	
	return TRUE;
}

BOOL CTeamExplorerKernel::ExeRevert(char *pPath)
{
	if(NULL == pPath){
		return FALSE;
	}

	string sRevertCmd = "svn revert --non-interactive -R \"";
	sRevertCmd += pPath;
	sRevertCmd += "\"";

	string strRet = ExeCmd((char *)sRevertCmd.c_str());
	if(0 == strRet.find("svn: ")){
		strRet += pPath;
		strRet += " revert failed.\r\n";
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}

	m_RetMsgs.push_back(strRet);

	return TRUE;
}

BOOL CTeamExplorerKernel::ExeAdd(char *pPath)
{
	if(NULL == pPath){
		return FALSE;
	}

	string sAddCmd = "svn add --non-interactive -N \"";
	sAddCmd += pPath;
	sAddCmd += "\"";

	string strRet = ExeCmd((char *)sAddCmd.c_str());
	if(0 == strRet.find("svn: ")){
		strRet += pPath;
		strRet += " add failed.\r\n";
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}

	m_RetMsgs.push_back(strRet);

	return TRUE;
}

BOOL CTeamExplorerKernel::ExeCancel(int PathType, char *pPath)
{
	if(NULL == pPath){
		return FALSE;
	}

	string strRet = "";
	if(0 == PathType){
		string sUnLockCmd = "svn unlock --non-interactive \"";
		sUnLockCmd += pPath;
		sUnLockCmd += "\"";

		string sRevertCmd = "svn revert --non-interactive -R \"";
		sRevertCmd += pPath;
		sRevertCmd += "\"";

		strRet = ExeCmd((char *)sRevertCmd.c_str());
		strRet += ExeCmd((char *)sUnLockCmd.c_str());
		if(string::npos != strRet.find("svn: ")){
			strRet += pPath;
			strRet += " file cancel failed which had modified.\r\n";
			m_RetMsgs.push_back(strRet);
			return FALSE;
		}
	}
	else if(1 == PathType){
		string sUnLockCmd = "svn unlock --non-interactive \"";
		sUnLockCmd += pPath;
		sUnLockCmd += "\"";

		strRet = ExeCmd((char *)sUnLockCmd.c_str());
		if(string::npos != strRet.find("svn: ")){
			strRet += pPath;
			strRet += " check out file cancel failed.\r\n";
			m_RetMsgs.push_back(strRet);
			return FALSE;
		}
	}
	else if(2 == PathType){
		string sRevertCmd = "svn revert --non-interactive -R \"";
		sRevertCmd += pPath;
		sRevertCmd += "\"";

		strRet = ExeCmd((char *)sRevertCmd.c_str());
		if(string::npos != strRet.find("svn: ")){
			strRet += pPath;
			strRet += " add file cancel failed.\r\n";
			m_RetMsgs.push_back(strRet);
			return FALSE;
		}
	}

	m_RetMsgs.push_back(strRet);

	return TRUE;
}

BOOL CTeamExplorerKernel::ExeUnlock(int iIndex)
{
	if(iIndex >= m_NormalObjects.size()){
		return FALSE;
	}

	string sUnlockCmd = "svn unlock --non-interactive \"";
	sUnlockCmd += m_NormalObjects[iIndex];
	sUnlockCmd += "\"";

	string strRet = ExeCmd((char *)sUnlockCmd.c_str());
	if(0 == strRet.find("svn: ")){
		strRet += m_NormalObjects[iIndex] + " unlock failed.\r\n";
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}

	m_RetMsgs.push_back(strRet);
	return TRUE;
}

BOOL CTeamExplorerKernel::ExeCheckin(char *pLog)
{
	if(NULL == pLog){
		return FALSE;
	}

	string strRet;
	string sIgnorePaths = "";
	int iSize = m_IgnoreObjects.size();
	if(iSize > 0){
		for(int i = 0; i < iSize; i++){
			sIgnorePaths += "\"";
			sIgnorePaths += m_IgnoreObjects[i];
			sIgnorePaths += "\"";
			if(i < iSize-1){
				sIgnorePaths += " ";
			}
		}

		string AddCmd = "svn add --non-interactive ";
		AddCmd += sIgnorePaths;
		strRet = ExeCmd((char *)AddCmd.c_str());
		if(strRet.npos != strRet.find("svn: ")){
			strRet += "add unversion file failed, unknown error.\r\n";
			m_RetMsgs.push_back(strRet);
			return FALSE;
		}
	}

	string sAddPaths = "";
	iSize = m_AddObjects.size();
	if(iSize > 0){
		for(int i = 0; i < iSize; i++){
			sAddPaths += "\"";
			sAddPaths += m_AddObjects[i];
			sAddPaths += "\"";
			if(i < iSize-1){
				sAddPaths += " ";
			}
		}
	}

	string sModifyPaths = "";
	iSize = m_OpeObjects.size();
	if(iSize > 0){
		for(int i = 0; i < iSize; i++){
			sModifyPaths += "\"";
			sModifyPaths += m_OpeObjects[i];
			sModifyPaths += "\"";
			if(i < iSize-1){
				sModifyPaths += " ";
			}
		}
	}

	string CheckinCmd = "svn commit --non-interactive -m \"";
	CheckinCmd += pLog;
	CheckinCmd += "\" ";
	CheckinCmd += sModifyPaths;
	CheckinCmd += " ";
	CheckinCmd += sAddPaths;
	CheckinCmd += " ";
	CheckinCmd += sIgnorePaths;
	strRet += ExeCmd((char *)CheckinCmd.c_str());
	if(strRet.npos != strRet.find("svn: ")){
		strRet += "commit failed, unknown error.\r\n";
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}

	strRet += "commit succeeded.\r\n";
	m_RetMsgs.push_back(strRet);

	return TRUE;
}

void CTeamExplorerKernel::ExeDealAdd(LPCSTR Path)
{
	if(NULL == Path){
		return;
	}

	if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(Path)){
		string LockCmd = "svn lock --non-interactive \"";
		LockCmd += Path;
		LockCmd += "\"";

		string strRet = ExeCmd((char *)LockCmd.c_str());
		m_RetMsgs.push_back(strRet);

		return;
	}

	WIN32_FIND_DATA FindData;  
	HANDLE hError;  
	int FileCount = 0;  
	char FilePathName[255];
	char FullPathName[255];

	strcpy(FilePathName, Path);  
	strcat(FilePathName, "\\*.*");  
	hError = FindFirstFile(FilePathName, &FindData);  

	if (hError == INVALID_HANDLE_VALUE){
		FindClose(hError);
		return;  
	}

	while(::FindNextFile(hError, &FindData)){  
		if(strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0 ){  
			continue;  
		}

		memset(FullPathName, 0, sizeof(FullPathName));
		wsprintf(FullPathName, "%s\\%s", Path,FindData.cFileName);  
		FileCount++;  

		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			int len = strlen(FullPathName);
			if(!memcmp(FullPathName+len-4, ".svn", 4)){
				continue;
			}

			ExeDealAdd(FullPathName);
		}
		else{
			string LockCmd = "svn lock --non-interactive \"";
			LockCmd += FullPathName;
			LockCmd += "\"";

			string strRet = ExeCmd((char *)LockCmd.c_str());
			m_RetMsgs.push_back(strRet);
		}
	}

	FindClose(hError);

	return;
}

BOOL CTeamExplorerKernel::ExeCommit(char *pLog)
{
	if(NULL == pLog){
		return FALSE;
	}

	string strRet;
	string sIgnorePaths = "";
	int iSize = m_IgnoreObjects.size();
	if(iSize > 0){
		for(int i = 0; i < iSize; i++){
			sIgnorePaths += "\"";
			sIgnorePaths += m_IgnoreObjects[i];
			sIgnorePaths += "\"";
			if(i < iSize-1){
				sIgnorePaths += " ";
			}
		}

		string AddCmd = "svn add --non-interactive ";
		AddCmd += sIgnorePaths;
		strRet = ExeCmd((char *)AddCmd.c_str());
		if(strRet.npos != strRet.find("svn: ")){
			strRet += "add unversion file failed, unknown error.\r\n";
			m_RetMsgs.push_back(strRet);
			return FALSE;
		}
	}

	string sAddPaths = "";
	iSize = m_AddObjects.size();
	if(iSize > 0){
		for(int i = 0; i < iSize; i++){
			sAddPaths += "\"";
			sAddPaths += m_AddObjects[i];
			sAddPaths += "\"";
			if(i < iSize-1){
				sAddPaths += " ";
			}
		}
	}

	string sModifyPaths = "";
	iSize = m_OpeObjects.size();
	if(iSize > 0){
		for(int i = 0; i < iSize; i++){
			sModifyPaths += "\"";
			sModifyPaths += m_OpeObjects[i];
			sModifyPaths += "\"";
			if(i < iSize-1){
				sModifyPaths += " ";
			}
		}
	}

	string CommitCmd = "svn commit --non-interactive --no-unlock -m \"";
	CommitCmd += pLog;
	CommitCmd += "\" ";
	CommitCmd += sModifyPaths;
	CommitCmd += " ";
	CommitCmd += sAddPaths;
	CommitCmd += " ";
	CommitCmd += sIgnorePaths;
	strRet += ExeCmd((char *)CommitCmd.c_str());
	if(strRet.npos != strRet.find("svn: ")){
		strRet += "commit failed, unknown failed.\r\n";
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}

	strRet += "commit succeeded.\r\n";
	m_RetMsgs.push_back(strRet);

	return TRUE;
}

void CTeamExplorerKernel::AddRetMsg(char *pRetMsg)
{
	if(NULL == pRetMsg){
		return;
	}

	m_RetMsgs.push_back(pRetMsg);
}

void CTeamExplorerKernel::AddOpeObject(char *pOpeObject)
{
	if(NULL == pOpeObject){
		return;
	}

	m_OpeObjects.push_back(pOpeObject);
}

void CTeamExplorerKernel::AddIgnoreObject(char *pIgnoreObject)
{
	if(NULL == pIgnoreObject){
		return;
	}

	m_IgnoreObjects.push_back(pIgnoreObject);
}

void CTeamExplorerKernel::AddAddObject(char *pAddObject)
{
	if(NULL == pAddObject){
		return;
	}

	m_AddObjects.push_back(pAddObject);
}

void CTeamExplorerKernel::AddNormalObject(char *pNormalObject)
{
	if(NULL == pNormalObject){
		return;
	}

	m_NormalObjects.push_back(pNormalObject);
}

void CTeamExplorerKernel::ClearRetMsg()
{
	m_RetMsgs.clear();
}

void CTeamExplorerKernel::ClearAddObjects()
{
	m_AddObjects.clear();
}

void CTeamExplorerKernel::ClearIgnoreObjects()
{
	m_IgnoreObjects.clear();
}

void CTeamExplorerKernel::ClearOpeObjects()
{
	m_OpeObjects.clear();
}

void CTeamExplorerKernel::ClearNormalObjects()
{
	m_NormalObjects.clear();
}

void CTeamExplorerKernel::ClearReadOnlyModifyObjects()
{
	m_ReadOnlyModifyObjects.clear();
}

BOOL CTeamExplorerKernel::GetCrtVersion(char *pDepURL)
{
	if(NULL == pDepURL){
		return FALSE;
	}

	string sListTrunkCmd = "svn list --non-interactive \"";
	sListTrunkCmd += pDepURL;
	sListTrunkCmd += "/trunk";
	sListTrunkCmd += "\"";

	string strRet = ExeCmd((char *)sListTrunkCmd.c_str());
	if(string::npos == strRet.find("svn: ")){
		m_ChildDirs.push_back("trunk/");
	}

	string sListBranchCmd = "svn list --non-interactive \"";
	sListBranchCmd += pDepURL;
	sListBranchCmd += "/branches";
	sListBranchCmd += "\"";

	int pos = -1;
	strRet = ExeCmd((char *)sListBranchCmd.c_str());
	if(string::npos == strRet.find("svn: ") && strRet.length() > 2){
		while(1){
			pos = strRet.find("\r\n");
			if(0 != pos && -1 != pos){
				string sVersion = strRet.substr(0, pos);
				m_ChildDirs.push_back(sVersion);
				if(strRet.length()-pos-2 > 0){
					strRet = strRet.substr(pos+2, strRet.length());
				}
				else{
					break;
				}
			}
			else{
				break;
			}
		}
	}

	return TRUE;
}

BOOL CTeamExplorerKernel::GetWcURL(char *pPath, char *pWcURL)
{
	if(NULL == pPath || NULL == pWcURL){
		return FALSE;
	}

	string sWcURL = "";

	string InfoCmd = "svn info --non-interactive \"";
	InfoCmd += pPath;
	InfoCmd += "\"";

	string strRet = ExeCmd((char *)InfoCmd.c_str());
	if(0 == strRet.find("svn: ")){
		return FALSE;
	}

	int CycleTimes = 0;
	if(FILE_ATTRIBUTE_DIRECTORY == GetFileAttributes(pPath)){
		CycleTimes = 2;
	}
	else{
		CycleTimes = 3;
	}

	int pos;
	for(int i = 0; i < CycleTimes; i++){
		pos = strRet.find("\r\n");
		if(strRet.length() > pos+2){
			strRet = strRet.substr(pos+2, strRet.length());
		}
		else{
			return FALSE;
		}
	}

	pos = strRet.find("\r\n");
	if(pos != string::npos && pos > 0){
		sWcURL = CutStr(5, pos, strRet);
		memcpy(pWcURL, sWcURL.c_str(), sWcURL.length());
		return TRUE;
	}
	else{
		return FALSE;
	}
}

void CTeamExplorerKernel::GetReadOnlyModifyObject(char *pWcPath)
{
	if(NULL == pWcPath){
		return ;
	}

	string StatusCmd = "svn status --non-interactive \"";
	StatusCmd += pWcPath;
	StatusCmd += "\"";
	string strRet = ExeCmd((char *)StatusCmd.c_str());
	if(strRet.length() <= 2 || 0 == strRet.find("svn: ")){
		return ;
	}
	else{
		while(strRet.length() > 8){
			int tmpPos = strRet.find("\r");
			if(tmpPos == string::npos){
				break;
			}

			if(0 == strRet.find("M       ") || 0 == strRet.find("CM      ") || 0 == strRet.find("G    ") || 0 == strRet.find("   C ")){
				string ReadOnlyModify = CutStr(8, tmpPos, strRet);
				if(string::npos != ReadOnlyModify.find(".cpp") || string::npos != ReadOnlyModify.find(".c")){
					m_ReadOnlyModifyObjects.push_back(ReadOnlyModify);
				}
				else if(string::npos != ReadOnlyModify.find(".h") || string::npos != ReadOnlyModify.find(".cs")){
					m_ReadOnlyModifyObjects.push_back(ReadOnlyModify);
				}
				else if(string::npos != ReadOnlyModify.find(".vb") || string::npos != ReadOnlyModify.find(".java")){
					m_ReadOnlyModifyObjects.push_back(ReadOnlyModify);
				}
				else if(string::npos != ReadOnlyModify.find(".jsp") || string::npos != ReadOnlyModify.find(".xml")){
					m_ReadOnlyModifyObjects.push_back(ReadOnlyModify);
				}
				else if(string::npos != ReadOnlyModify.find(".sln") || string::npos != ReadOnlyModify.find(".js")){
					m_ReadOnlyModifyObjects.push_back(ReadOnlyModify);
				}
				else if(string::npos != ReadOnlyModify.find(".idl") || string::npos != ReadOnlyModify.find(".css")){
					m_ReadOnlyModifyObjects.push_back(ReadOnlyModify);
				}
				else if(string::npos != ReadOnlyModify.find(".resx") || string::npos != ReadOnlyModify.find(".html")){
					m_ReadOnlyModifyObjects.push_back(ReadOnlyModify);
				}
				else if(string::npos != ReadOnlyModify.find(".txt") || string::npos != ReadOnlyModify.find(".doc")){
					m_ReadOnlyModifyObjects.push_back(ReadOnlyModify);
				}
			}

			if((strRet.length() - (tmpPos+2)) > 8){
				strRet = strRet.substr(tmpPos+2, strRet.length());
			}
			else{
				break;
			}
		}
	}
}

void CTeamExplorerKernel::GetRevertObject()
{
	int iSize = m_WcPaths.size();
	for(int i = 0; i < iSize; i++){
		string StatusCmd = "svn status --non-interactive \"" + m_WcPaths[i] + "\"";
		string strRet = ExeCmd((char *)StatusCmd.c_str());
		if(strRet.length() <= 2 || 0 == strRet.find("svn: ")){
			continue;
		}
		else{
			while(strRet.length() > 8){
				int tmpPos = strRet.find("\r");
				if(tmpPos == string::npos){
					break;
				}

				if(HasModify(strRet)){
					string sModify = CutStr(8, tmpPos, strRet);
					m_OpeObjects.push_back(sModify);
				}
				else if(HasConflict(strRet)){
					string sNormal = CutStr(8, tmpPos, strRet);
					m_NormalObjects.push_back(sNormal);
				}
				else if(0 == strRet.find("A       ") || 0 == strRet.find("A  +    ")){
					string sAdd = CutStr(8, tmpPos, strRet);
					m_AddObjects.push_back(sAdd);
				}

				if((strRet.length() - (tmpPos+2)) > 8){
					strRet = strRet.substr(tmpPos+2, strRet.length());
				}
				else{
					break;
				}
			}
		}
	}
}

void CTeamExplorerKernel::GetAddObject()
{
	int iSize = m_WcPaths.size();
	for(int i = 0; i < iSize; i++){
		string StatusCmd = "svn status --non-interactive \"" + m_WcPaths[i] + "\"";
		string strRet = ExeCmd((char *)StatusCmd.c_str());
		if(strRet.length() <= 2 || 0 == strRet.find("svn: ")){
			continue;
		}
		else{
			while(strRet.length() > 8){
				int tmpPos = strRet.find("\r");
				if(tmpPos == string::npos){
					break;
				}

				if(0 == strRet.find("?       ")){
					string sAdd = CutStr(8, tmpPos, strRet);
					GetAddChild((char *)sAdd.c_str());
				}

				if((strRet.length() - (tmpPos+2)) > 8){
					strRet = strRet.substr(tmpPos+2, strRet.length());
				}
				else{
					break;
				}
			}
		}
	}
}

void CTeamExplorerKernel::GetCancelObject()
{
	int iSize = m_WcPaths.size();
	for(int i = 0; i < iSize; i++){
		string StatusCmd = "svn status --non-interactive \"" + m_WcPaths[i] + "\"";
		string strRet = ExeCmd((char *)StatusCmd.c_str());
		if(strRet.length() <= 2 || 0 == strRet.find("svn: ")){
			continue;
		}
		else{
			while(strRet.length() > 8){
				int tmpPos = strRet.find("\r");
				if(tmpPos == string::npos){
					break;
				}

				if(HasConflict(strRet) || HasModify(strRet)){
					string sModify = CutStr(8, tmpPos, strRet);
					m_OpeObjects.push_back(sModify);
				}
				else if(0 == strRet.find("     K  ")){
					string sNormal = CutStr(8, tmpPos, strRet);
					m_NormalObjects.push_back(sNormal);
				}
				else if(0 == strRet.find("A       ") || 0 == strRet.find("A  +    ")){
					string sAdd = CutStr(8, tmpPos, strRet);
					m_AddObjects.push_back(sAdd);
				}

				if((strRet.length() - (tmpPos+2)) > 8){
					strRet = strRet.substr(tmpPos+2, strRet.length());
				}
				else{
					break;
				}
			}
		}
	}
}

void CTeamExplorerKernel::GetCheckinObject()
{
	int iSize = m_WcPaths.size();
	for(int i = 0; i < iSize; i++){
		string StatusCmd = "svn status --non-interactive \"" + m_WcPaths[i] + "\"";
		string strRet = ExeCmd((char *)StatusCmd.c_str());
		if(strRet.length() <= 2 || 0 == strRet.find("svn: ")){
			continue;
		}
		else{
			while(strRet.length() > 8){
				int tmpPos = strRet.find("\r");
				if(tmpPos == string::npos){
					break;
				}

				if(HasModify(strRet)){
					string sModify = CutStr(8, tmpPos, strRet);
					m_OpeObjects.push_back(sModify);
				}
				else if(0 == strRet.find("     K  ")){
					string sNormal = CutStr(8, tmpPos, strRet);
					m_NormalObjects.push_back(sNormal);
				}
				else if(0 == strRet.find("A       ") || 0 == strRet.find("A  +    ")){
					string sAdd = CutStr(8, tmpPos, strRet);
					m_AddObjects.push_back(sAdd);
				}
				else if(0 == strRet.find("?       ")){
					string sIgnore = CutStr(8, tmpPos,strRet);
					m_IgnoreObjects.push_back(sIgnore);
				}

				if((strRet.length() - (tmpPos+2)) > 8){
					strRet = strRet.substr(tmpPos+2, strRet.length());
				}
				else{
					break;
				}
			}
		}
	}
}

void CTeamExplorerKernel::GetCommitObject()
{
	int iSize = m_WcPaths.size();
	for(int i = 0; i < iSize; i++){
		string StatusCmd = "svn status --non-interactive \"" + m_WcPaths[i] + "\"";
		string strRet = ExeCmd((char *)StatusCmd.c_str());
		if(strRet.length() <= 2 || 0 == strRet.find("svn: ")){
			continue;
		}
		else{
			while(strRet.length() > 8){
				int tmpPos = strRet.find("\r");
				if(tmpPos == string::npos){
					break;
				}

				if(HasModify(strRet)){
					string sModify = CutStr(8, tmpPos, strRet);
					m_OpeObjects.push_back(sModify);
				}
				else if(0 == strRet.find("A       ") || 0 == strRet.find("A  +    ")){
					string sAdd = CutStr(8, tmpPos, strRet);
					m_AddObjects.push_back(sAdd);
				}
				else if(0 == strRet.find("?       ")){
					string sIgnore = CutStr(8, tmpPos,strRet);
					m_IgnoreObjects.push_back(sIgnore);
				}

				if((strRet.length() - (tmpPos+2)) > 8){
					strRet = strRet.substr(tmpPos+2, strRet.length());
				}
				else{
					break;
				}
			}
		}
	}
}

void CTeamExplorerKernel::ExeUpdate(char *pPath)
{
	if(NULL == pPath){
		return;
	}

	string UpdateCmd = "svn update --non-interactive --accept tf \"";
	UpdateCmd += pPath;
	UpdateCmd += "\"";

	string strRet = ExeCmd((char *)UpdateCmd.c_str());
	m_RetMsgs.push_back(strRet);
}

BOOL CTeamExplorerKernel::ExeCheckout(char *pFilePath)
{
	if(NULL == pFilePath){
		return FALSE;
	}

	string CheckoutCmd = "svn lock --non-interactive \"";
	CheckoutCmd += pFilePath;
	CheckoutCmd += "\"";

	string strRet = ExeCmd((char *)CheckoutCmd.c_str());
	if(strRet.npos != strRet.find("W160035: ")){
		strRet += "the file had been locked by other, checkout failed.\r\n";
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}
	else if(strRet.npos != strRet.find("W160042: ")){
		strRet += "the file's revision had expired, please update, check out file failed.\r\n";
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}
	else if(0 == strRet.find("svn: ")){
		strRet += "unknown error.\r\n";
		m_RetMsgs.push_back(strRet);
		return FALSE;
	}

	strRet = pFilePath;
	strRet += " check out succeeded.\r\n";
	m_RetMsgs.push_back(strRet);

	return TRUE;
}

void CTeamExplorerKernel::GetCheckoutObject()
{
	int iSize = m_WcPaths.size();
	for(int i = 0; i < iSize; i++){
		string StatusCmd = "svn status --non-interactive \"" + m_WcPaths[i] + "\"";
		string strRet = ExeCmd((char *)StatusCmd.c_str());
		if(0 == strRet.find("svn: ")){
			continue;
		}
		else if(strRet.length() <= 2){
			GetAllObject((char *)m_WcPaths[i].c_str());
		}
		else if(0 == strRet.find("?       ")){
			int tmpPos = strRet.find("\r");
			string subStr = CutStr(8, tmpPos, strRet);
			if(m_WcPaths[i] == subStr){
				continue;
			}
			else{
				GetAllObject((char *)m_WcPaths[i].c_str());
				GetCheckoutIgnore(strRet);
			}
		}
		else{
			GetAllObject((char *)m_WcPaths[i].c_str());
			GetCheckoutIgnore(strRet);
		}
	}
}

void CTeamExplorerKernel::ExeSetEnv(char *pChildURL, char *pWcPath)
{
	if(NULL == pChildURL || NULL == pWcPath){
		return;
	}

	string sSetEnvCmd;
	sSetEnvCmd = "svn checkout --non-interactive \"";
	sSetEnvCmd += pChildURL;
	sSetEnvCmd += "\" \"";
	sSetEnvCmd += pWcPath;
	sSetEnvCmd += "\"";
	string sRetMsg = ExeCmd((char *)sSetEnvCmd.c_str());
	m_RetMsgs.push_back(sRetMsg);
}

void CTeamExplorerKernel::ExeSetEnv(char *pChildURL, char *pWcPath, char *pRevision)
{
	if(NULL == pChildURL || NULL == pWcPath || NULL == pRevision){
		return;
	}

	string sSetEnvCmd;
	sSetEnvCmd = "svn checkout --non-interactive -r";
	sSetEnvCmd += pRevision;
	sSetEnvCmd += " \"";
	sSetEnvCmd += pChildURL;
	sSetEnvCmd += "\" \"";
	sSetEnvCmd += pWcPath;
	sSetEnvCmd += "\"";
	string sRetMsg = ExeCmd((char *)sSetEnvCmd.c_str());
	m_RetMsgs.push_back(sRetMsg);
}

void CTeamExplorerKernel::ClearChildDirs()
{
	m_ChildDirs.clear();
}

void CTeamExplorerKernel::GetDepName(int from, int to, char *pDepName)
{
	if(NULL == pDepName){
		return;
	}

	string tDepName = m_DepURL.substr(from, to);
	memcpy(pDepName, tDepName.c_str(), tDepName.length());
}

void CTeamExplorerKernel::SetDepURL(char *pDepURL)
{
	if(NULL == pDepURL){
		return;
	}

	m_DepURL = pDepURL;
}

void CTeamExplorerKernel::AddWcPath(char *pWcPath)
{
	if(NULL == pWcPath){
		return;
	}

	m_WcPaths.push_back(pWcPath);
}

void CTeamExplorerKernel::SetWcPath(char *pWcPath)
{
	if(NULL == pWcPath){
		return;
	}

	m_WcPath = pWcPath;
}

void CTeamExplorerKernel::SetChildURL(char *pChildURL)
{
	if(NULL == pChildURL){
		return;
	}

	m_ChildURL = pChildURL;
}

void CTeamExplorerKernel::SetUserName(char *pUserName)
{
	if(NULL == pUserName){
		return;
	}
	
	m_UserName = pUserName;
}

void CTeamExplorerKernel::SetPassword(char *pPassword)
{
	if(NULL == pPassword){
		return;
	}

	m_Password = pPassword;
}

BOOL CTeamExplorerKernel::SaveServerURL(char *pConfigPath, char *pServerURL)
{
	if(NULL == pConfigPath || NULL == pServerURL){
		return FALSE;
	}

	string sServerFile = pConfigPath;
	sServerFile += "\\auth\\svn.simple\\";

	if(PathFileExists(sServerFile.c_str())){
		sServerFile += SERVER_FILE;
		FILE *fp = fopen(sServerFile.c_str(), "wb");
		if(NULL == fp){
			return FALSE;
		}

		fwrite(pServerURL, 1, 255, fp);
		fclose(fp);
	}
	else{
		return FALSE;
	}

	return TRUE;
}

BOOL CTeamExplorerKernel::GetServerURL(char *pConfigPath, char *pServerURL)
{
	if(NULL == pConfigPath || NULL == pServerURL){
		return FALSE;
	}

	string sServerFile = pConfigPath;
	sServerFile += "\\auth\\svn.simple\\";
	sServerFile += SERVER_FILE;

	if(PathFileExists(sServerFile.c_str())){
		FILE *fp = fopen(sServerFile.c_str(), "rb+");
		if(NULL == fp){
			return FALSE;
		}

		fread(pServerURL, 1, 255, fp);
		fclose(fp);
	}
	else{
		return FALSE;
	}

	return TRUE;
}

BOOL CTeamExplorerKernel::GetConfigPath(char *pConfigPath)
{
	if(NULL == pConfigPath){
		return FALSE;
	}

	string sConfigPath = "C:";
	sConfigPath += getenv("homepath");
	sConfigPath += "\\Application Data\\Subversion";

	memcpy(pConfigPath, sConfigPath.c_str(), sConfigPath.length());

	return TRUE;
}

BOOL CTeamExplorerKernel::IsFirstUse()
{
	m_ConfigFlag = 1;
	m_ConfigPath = "C:";
	m_ConfigPath += getenv("homepath");
	m_ConfigPath += "\\Application Data\\Subversion";

	if (PathFileExists(m_ConfigPath.c_str())){
		string configPath = m_ConfigPath;
		configPath += "\\auth\\svn.simple\\";
		configPath += CONFIG_FILE;
		if (PathFileExists(configPath.c_str())){
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CTeamExplorerKernel::GetDepURL()
{
	char tDepURL[255];
	memset(tDepURL, 0, sizeof(tDepURL));

	string configPath;
	configPath = m_ConfigPath + "\\auth\\svn.simple\\" + CONFIG_FILE;

	FILE *fp = fopen(configPath.c_str(), "rb+");
	if(NULL == fp){
		return FALSE;
	}

	fread(tDepURL, 1, sizeof(tDepURL), fp);
	m_DepURL = tDepURL;

	fclose(fp);

	return TRUE;
}

int CTeamExplorerKernel::GetChildDir()
{
	string sDepURL = m_DepURL;
	string ListCmd = "svn list --non-interactive \"";
	ListCmd += sDepURL;
	ListCmd += "\"";

	string strRet = ExeCmd((char *)ListCmd.c_str());
	if(2 >= strRet.length()){
		return -1;
	}
	else if(0 == strRet.find("svn: E175002")){
		return -2;
	}
	else if(0 == strRet.find("svn: E175013")){
		return -3;
	}
	else if(0 == strRet.find("svn: ")){
		return -4;
	}

	int pos = -1;
	string sProducts = "products";
	while(strRet.npos != (pos = strRet.find("\r"))){
		string sChildDir = strRet.substr(0, pos);
		if('/' == sChildDir[pos-1]){
			sChildDir = sChildDir.substr(0, pos-1);
			if(sChildDir != sProducts){
				m_ChildDirs.push_back(sChildDir);
			}
		}

		if(strRet.length() - pos > 2){
			strRet = strRet.substr(pos+2, strRet.length());
		}
		else{
			break;
		}
	}

	m_ChildDirs.push_back("|");

	string tDepURL;
	vector<string> tDirs;
	int iSize = m_ChildDirs.size() - 1;
	for(int i = 0; i < iSize; i++){
		tDepURL = sDepURL + "/" + m_ChildDirs.at(i);
		ListCmd = "svn list --non-interactive \"";
		ListCmd += tDepURL;
		ListCmd += "\"";
		strRet = ExeCmd((char *)ListCmd.c_str());
		if(strRet.length() <= 2 || 0 == strRet.find("svn: ")){
			m_ChildDirs.push_back("|");
			continue;
		}

		while(strRet.npos != (pos = strRet.find("\r"))){
			string sChildDir = strRet.substr(0, pos);
			if('/' == sChildDir[pos-1]){
				sChildDir = sChildDir.substr(0, pos-1);
				m_ChildDirs.push_back(sChildDir);
				if(m_ChildDirs.at(i) == "branches"){
					tDirs.push_back(sChildDir);
				}
			}

			if(strRet.length() - pos > 2){
				strRet = strRet.substr(pos+2, strRet.length());
			}
			else{
				break;
			}
		}

		m_ChildDirs.push_back("|");
	}

	iSize = tDirs.size();
	for(int i = 0; i < iSize; i++){
		tDepURL = sDepURL + "/branches/" + tDirs.at(i);
		ListCmd = "svn list --non-interactive \"";
		ListCmd += tDepURL;
		ListCmd += "\"";
		strRet = ExeCmd((char *)ListCmd.c_str());
		if(strRet.length() <= 2 || 0 == strRet.find("svn: ")){
			m_ChildDirs.push_back("|");
			continue;
		}

		while(strRet.npos != (pos = strRet.find("\r"))){
			string sChildDir = strRet.substr(0, pos);
			if('/' == sChildDir[pos-1]){
				sChildDir = sChildDir.substr(0, pos-1);
				m_ChildDirs.push_back(sChildDir);
			}

			if(strRet.length() - pos > 2){
				strRet = strRet.substr(pos+2, strRet.length());
			}
			else{
				break;
			}
		}

		m_ChildDirs.push_back("|");
	}

	return 0;
}

BOOL CTeamExplorerKernel::ChangeDep()
{
	string configPath;
	configPath = m_ConfigPath + "\\auth\\svn.simple\\" + CONFIG_FILE;

	char tDepURL[255];
	memset(tDepURL, 0, sizeof(tDepURL));

	FILE *fp = fopen(configPath.c_str(), "rb+");
	if(NULL == fp){
		return FALSE;
	}

	memcpy(tDepURL, m_DepURL.c_str(), m_DepURL.length());
	fwrite(tDepURL, 1, sizeof(tDepURL), fp);

	fclose(fp);

	return TRUE;
}

BOOL CTeamExplorerKernel::FirstSelectDep()
{
	string InfoCmd = "svn info --non-interactive --username ";
	InfoCmd += m_UserName + " --password " + m_Password + " \"" + m_DepURL + "\"";
	ExeCmd((char *)InfoCmd.c_str());

	string configPath;
	configPath = m_ConfigPath + "\\auth\\svn.simple\\" + CONFIG_FILE;

	char tDepURL[255];
	char tUserName[255];
	char tPassword[255];
	memset(tDepURL, 0, sizeof(tDepURL));
	memset(tUserName, 0, sizeof(tUserName));
	memset(tPassword, 0, sizeof(tPassword));

	FILE *fp = fopen(configPath.c_str(), "wb");
	if(NULL == fp){
		return FALSE;
	}

	memcpy(tDepURL, m_DepURL.c_str(), m_DepURL.length());
	memcpy(tUserName, m_UserName.c_str(), m_UserName.length());
	memcpy(tPassword, m_Password.c_str(), m_Password.length());

	fwrite(tDepURL, 1, sizeof(tDepURL), fp);
	fwrite(tUserName, 1, sizeof(tUserName), fp);
	fwrite(tPassword, 1, sizeof(tPassword), fp);

	fclose(fp);

	return TRUE;
}

BOOL CTeamExplorerKernel::GetUserInfo()
{
	string configPath;
	configPath = m_ConfigPath + "\\auth\\svn.simple\\" + CONFIG_FILE;

	FILE *fp = fopen(configPath.c_str(), "rb+");
	if(NULL == fp){
		return FALSE;
	}

	char tUserName[255];
	char tPassword[255];

	memset(tUserName, 0, sizeof(tUserName));
	memset(tPassword, 0, sizeof(tPassword));

	fseek(fp, 255, SEEK_SET);
	fread(tUserName, 1, sizeof(tUserName), fp);
	fread(tPassword, 1, sizeof(tPassword), fp);

	fclose(fp);

	string tsUserName(tUserName);
	string tsPassword(tPassword);

	m_UserName = tsUserName;
	m_Password = tsPassword;

	return TRUE;
}

BOOL CTeamExplorerKernel::SetRecordUser()
{
	string strRet;
	string InfoCmd = "svn info --non-interactive --username ";
	InfoCmd += m_UserName;
	InfoCmd += " --password ";
	InfoCmd += m_Password;
	InfoCmd += " \"" + m_DepURL + "\"";
	strRet = ExeCmd((char *)InfoCmd.c_str());
	if(0 == strRet.find("svn: ")){
		return FALSE;
	}

	char tUserName[255];
	char tPassword[255];
	char tDepURL[255];

	memset(tDepURL, 0, sizeof(tDepURL));
	memset(tUserName, 0, sizeof(tUserName));
	memset(tPassword, 0, sizeof(tPassword));

	memcpy(tUserName, m_UserName.c_str(), m_UserName.length());
	memcpy(tPassword, m_Password.c_str(), m_Password.length());
	memcpy(tDepURL, m_DepURL.c_str(), m_DepURL.length());

	string configPath = m_ConfigPath + "\\auth\\svn.simple\\" + CONFIG_FILE;

	FILE *fp = fopen(configPath.c_str(), "wb+");
	if(NULL == fp){
		return FALSE;
	}

	fwrite(tDepURL, 1, sizeof(tDepURL), fp);
	fwrite(tUserName, 1, sizeof(tUserName), fp);
	fwrite(tPassword, 1, sizeof(tPassword), fp);

	fclose(fp);

	return TRUE;
}

BOOL CTeamExplorerKernel::IsInputRight(char *pServerURL, char *pUserName, char *pPassword)
{
	if(NULL == pServerURL || NULL == pUserName || NULL == pPassword){
		return FALSE;
	}

	CString strFileURLInServer(pServerURL);
	string sUserName = pUserName;
	string sPassword = pPassword;

	ASSERT(strFileURLInServer != "");

	CInternetSession session;
	CHttpConnection* pHttpConnection = NULL;
	CHttpFile* pHttpFile = NULL;
	CString strServer, strObject;
	INTERNET_PORT wPort;

	DWORD dwType;
	const int nTimeOut = 2000;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);

	try{
		InternetSetOption(session,INTERNET_OPTION_RESET_URLCACHE_SESSION,NULL,0);
		AfxParseURL(strFileURLInServer, dwType, strServer, strObject, wPort);
		pHttpConnection = session.GetHttpConnection(strServer, wPort, sUserName.c_str(), sPassword.c_str());
		pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject);
		if (pHttpFile->SendRequest() == FALSE){
			m_SevStatusFlag = FALSE;
			return FALSE;
		}

		DWORD dwStateCode;
		pHttpFile->QueryInfoStatusCode(dwStateCode);
		if (dwStateCode != HTTP_STATUS_OK){
			if (pHttpFile != NULL){
				pHttpFile->Close();
				delete pHttpFile;
				pHttpFile = NULL;
			}

			if (pHttpConnection != NULL){
				pHttpConnection->Close();
				delete pHttpConnection;
				pHttpConnection = NULL;
			}

			session.Close();

			return FALSE;
		}
	}
	catch (...){
		if(pHttpFile != NULL){
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}

		if(pHttpConnection != NULL){
			pHttpConnection->Close();
			delete pHttpConnection;
			pHttpConnection = NULL;
		}

		session.Close();

		return FALSE;
	}

	if (pHttpFile != NULL){
		pHttpFile->Close();
		delete pHttpFile;
		pHttpFile = NULL;
	}

	if (pHttpConnection != NULL){
		pHttpConnection->Close();
		delete pHttpConnection;
		pHttpConnection = NULL;
	}

	session.Close();

	return TRUE;
}

void CTeamExplorerKernel::GetDepInfo(char *pServerURL, char *pUserName, char *pPassword)
{
	if(NULL == pServerURL || NULL == pUserName || NULL == pPassword){
		m_DepBuffer = "";
		return;
	}

	CString strFileURLInServer(pServerURL);
	string sUserName = pUserName;
	string sPassword = pPassword;

	ASSERT(strFileURLInServer != "");

	string strBuffer;

	CInternetSession session;
	CHttpConnection* pHttpConnection = NULL;
	CHttpFile* pHttpFile = NULL;
	CString strServer, strObject;
	INTERNET_PORT wPort;

	DWORD dwType;
	const int nTimeOut = 2000;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,nTimeOut);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES,1);
	char *pszBuffer = NULL;

	try{
		InternetSetOption(session,INTERNET_OPTION_RESET_URLCACHE_SESSION,NULL,0);
		AfxParseURL(strFileURLInServer,dwType,strServer,strObject,wPort);
		pHttpConnection = session.GetHttpConnection(strServer,wPort, sUserName.c_str(), sPassword.c_str());
		pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET,strObject);
		if (pHttpFile->SendRequest() == FALSE){
			m_DepBuffer = "";
			return;
		}

		DWORD dwStateCode;

		pHttpFile->QueryInfoStatusCode(dwStateCode);
		if (dwStateCode == HTTP_STATUS_OK){
			char szInfoBuffer[1000];
			DWORD dwFileSize = 0;
			DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
			BOOL bResult = FALSE;
			bResult = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,(void *)szInfoBuffer,&dwInfoBufferSize,NULL);

			dwFileSize = atoi(szInfoBuffer);
			const int BUFFER_LENGTH = 1024;
			pszBuffer = new char[BUFFER_LENGTH];
			DWORD dwWrite, dwTotalWrite = 0;
			dwWrite = dwTotalWrite = 0;
			UINT nRead = pHttpFile->Read(pszBuffer,BUFFER_LENGTH);
			while(nRead>0){
				dwTotalWrite += nRead;
				strBuffer += pszBuffer;
				nRead = pHttpFile->Read(pszBuffer,BUFFER_LENGTH);
			}
			int length = strBuffer.length();
			strBuffer.erase(dwTotalWrite,length-dwTotalWrite);
			delete[] pszBuffer;
			pszBuffer = NULL;
		}
		else{
			delete[] pszBuffer;
			pszBuffer = NULL;
			if (pHttpFile != NULL){
				pHttpFile->Close();
				delete pHttpFile;
				pHttpFile = NULL;
			}
			if (pHttpConnection != NULL){
				pHttpConnection->Close();
				delete pHttpConnection;
				pHttpConnection = NULL;
			}
			session.Close();
			m_DepBuffer = "";
			return ;
		}
	}
	catch (...){
		delete[]pszBuffer;
		pszBuffer = NULL;
		if(pHttpFile != NULL){
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
		if(pHttpConnection != NULL){
			pHttpConnection->Close();
			delete pHttpConnection;
			pHttpConnection = NULL;
		}
		session.Close();
		m_DepBuffer = "";
		return;
	}

	if (pHttpFile != NULL){
		pHttpFile->Close();
		delete pHttpFile;
		pHttpFile = NULL;
	}

	if (pHttpConnection != NULL){
		pHttpConnection->Close();
		delete pHttpConnection;
		pHttpConnection = NULL;
	}

	session.Close();

	m_DepBuffer = strBuffer;
}
