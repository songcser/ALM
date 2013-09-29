// SmtShell.cpp : Implementation of CSmtShell

#include "stdafx.h"
#include "SmtShell.h"

// CSmtShell
HRESULT STDMETHODCALLTYPE CSmtShell::Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject *pdtobj, HKEY hkeyProgID)
{
	FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stg = { TYMED_HGLOBAL };
	HDROP      hDrop;

	if ( FAILED( pdtobj->GetData ( &fmt, &stg ) ))
		return E_INVALIDARG;

	hDrop = (HDROP) GlobalLock ( stg.hGlobal );

	if ( NULL == hDrop )
		return E_INVALIDARG;

	UINT uNumFiles = DragQueryFile ( hDrop, 0xFFFFFFFF, NULL, 0 );
	HRESULT hr = S_OK;

	if ( 0 == uNumFiles )
	{
		GlobalUnlock ( stg.hGlobal );
		ReleaseStgMedium ( &stg );
		return E_INVALIDARG;
	}

	m_NumFiles = uNumFiles;
	for(int i = 0; i < uNumFiles; i++){
		if ( 0 == DragQueryFile ( hDrop, i, m_szFile[i], 255 ) )
			hr = E_INVALIDARG;
	}

	GlobalUnlock ( stg.hGlobal );
	ReleaseStgMedium ( &stg );

	return hr;

	//return S_OK;
}

HRESULT STDMETHODCALLTYPE CSmtShell::GetCommandString(THIS_ UINT_PTR idCmd, UINT uType, UINT *pwReserved, LPSTR pszName, UINT cchMax)
{
	if (idCmd < 101 || idCmd >109)
	{
		return E_INVALIDARG;
	}

	lstrcpynA(pszName,"Warning! Something is wrong", cchMax);

	return S_OK;
}

BOOL CSmtShell::GetFatherPath(char *pCrtPath, char *pFatherPath)
{
	if(NULL == pCrtPath || NULL == pFatherPath){
		return FALSE;
	}

	int PathLen = strlen(pCrtPath);
	if(PathLen <= 1){
		return FALSE;
	}

	PathLen--;

	while(1){
		if('\\' == *(pCrtPath + PathLen) || '/' == *(pCrtPath + PathLen)){
			break;
		}
		PathLen--;
		if(PathLen <= 0){
			break;
		}
	}

	if(PathLen > 0){
		memcpy(pFatherPath, pCrtPath, PathLen);
		return TRUE;
	}
	else{
		return FALSE;
	}
}

BOOL CSmtShell::IsWorkEvn(char *pCrtPath, char *pRetPath)
{
	if(NULL == pCrtPath || NULL == pRetPath){
		return FALSE;
	}

	char CrtPath[255], tempPath[255];
	memset(CrtPath, 0, sizeof(CrtPath));
	memcpy(CrtPath, pCrtPath, strlen(pCrtPath));

	while(1){
		memset(tempPath, 0, sizeof(tempPath));
		sprintf(tempPath, "%s\\SmtRec.dat", CrtPath);
		if(!PathFileExists(tempPath)){
			char FatherPath[255];
			memset(FatherPath, 0, sizeof(FatherPath));
			if(!GetFatherPath(CrtPath, FatherPath)){
				return FALSE;
			}
			memset(CrtPath, 0, sizeof(CrtPath));
			memcpy(CrtPath, FatherPath, sizeof(FatherPath));
		}
		else{
			memcpy(pRetPath, CrtPath, sizeof(CrtPath));
			break;
		}
	}

	return TRUE;
}

string CSmtShell::ExeCmd(char *pszCmd)
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

BOOL CSmtShell::IsInCtr()
{
	m_FathAddFlag = FALSE;
	m_CouldAdd = TRUE;
	if(IsFatherAdd()){
		m_FathAddFlag = TRUE;
		for(int i = 0; i < m_NumFiles; i++){
			string StatusStr;
			string StatusCmd = "svn status ";
			StatusCmd += "\"";
			StatusCmd += m_szFile[i];
			StatusCmd += "\"";
			StatusStr += ExeCmd((char *)StatusCmd.c_str());
			if(0 == StatusStr.find("A       ")){
				m_InCtrNo[m_InCtrCount] = i;
				m_InCtrCount++;
				m_CouldAdd = FALSE;
			}
		}
		return FALSE;
	}

	char FilePath[255];
	memset(FilePath, 0, sizeof(FilePath));
	sprintf(FilePath, "%s\\SmtRec.dat", m_EnvPath);

	FILE *fp = fopen(FilePath, "r");
	if(NULL == fp){
		return FALSE;
	}

	fseek(fp, 0, SEEK_END);
	long fileLength = ftell(fp);
	int CycleTimes = (int)fileLength/255 - 1;
	fseek(fp, 255, SEEK_SET);

	m_RecFileLen = fileLength;

	char RecPath[255];
	char TmpPath[255];

	m_InCtrCount = 0;
	memset(m_InCtrNo, 0, sizeof(m_InCtrNo));

	BOOL TFlag = FALSE;

	for(int i = 0; i < m_NumFiles; i++){
		int PathLen = strlen(m_szFile[i]);
		int k = 0;
		for(k = 0; k < CycleTimes; k++){
			memset(RecPath, 0, sizeof(RecPath));
			memset(TmpPath, 0, sizeof(TmpPath));
			fread(RecPath, 1, sizeof(RecPath), fp);
			sprintf(TmpPath, "%s%s", m_EnvPath, RecPath);
			if((PathLen == strlen(TmpPath)) && (!memcmp(m_szFile[i], TmpPath, PathLen))){
				break;
			}
		}
		if(k < CycleTimes){
			m_InCtrNo[m_InCtrCount] = i;
			m_InCtrCount++;
			TFlag = TRUE;
			/*if(!m_AddFlag){
				if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(m_szFile[i])){
					string StatusStr;
					string StatusCmd = "svn status ";
					StatusCmd += "\"";
					StatusCmd += m_szFile[i];
					StatusCmd += "\"";
					StatusStr += ExeCmd((char *)StatusCmd.c_str());
					if(StatusStr.npos != StatusStr.find("A       ")){
						m_AddFlag = TRUE;
					}
				}
			}*/
		}
		else{
			string StatusStr;
			string StatusCmd = "svn status ";
			StatusCmd += "\"";
			StatusCmd += m_szFile[i];
			StatusCmd += "\"";
			StatusStr += ExeCmd((char *)StatusCmd.c_str());
			if(0 == StatusStr.find("A       ")){
				m_InCtrNo[m_InCtrCount] = i;
				m_InCtrCount++;
				TFlag = TRUE;
				m_AddFlag = TRUE;
			}
		}
		fseek(fp, 255, SEEK_SET);
	}

	fclose(fp);

	if(TFlag){
		return TRUE;
	}

	for(int i = 0; i < m_NumFiles; i++){
		if((!strcmp(m_EnvPath, m_szFile[i])) && m_RecFileLen > 255){
			return TRUE;
		}
	}

	if(1 == m_NumFiles){
		if(!strcmp(m_EnvPath, m_szFile[0])){
			char SvnPath[255];
			memset(SvnPath, 0, sizeof(SvnPath));
			sprintf(SvnPath, "%s\\.svn", m_EnvPath);
			if(PathFileExists(SvnPath)){
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

BOOL CSmtShell::IsFatherAdd()
{
	if(!strcmp(m_EnvPath, m_szFile[0])){
		return FALSE;
	}

	char FatherPath[255];
	memset(FatherPath, 0, sizeof(FatherPath));

	if(!GetFatherPath(m_szFile[0], FatherPath)){
		return FALSE;
	}

	if(!strcmp(m_EnvPath, FatherPath)){
		return FALSE;
	}

	string StatusStr;
	string StatusCmd = "svn status ";
	StatusCmd += "\"";
	StatusCmd += FatherPath;
	StatusCmd += "\"";
	StatusStr += ExeCmd((char *)StatusCmd.c_str());
	if(0 == StatusStr.find("A       ")){
		if(IsSamePath(StatusStr, FatherPath)){
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSmtShell::IsSamePath(string StatusStr, char *pPath)
{
	if(NULL == pPath){
		return FALSE;
	}

	char tempBuff[255];
	memset(tempBuff, 0, sizeof(tempBuff));

	int i = 8;
	int j = 0;

	if(i >= StatusStr.length()){
		return FALSE;
	}

	while('\r' != StatusStr[i]){
		if(i >= StatusStr.length()){
			break;
		}
		tempBuff[j] = StatusStr[i];
		j++;
		i++;
	}

	if(!strcmp(pPath, tempBuff)){
		return TRUE;
	}

	return FALSE;
}

BOOL CSmtShell::IsFatherInCtr()
{
	char FatherPath[255];
	memset(FatherPath, 0, sizeof(FatherPath));

	if(!GetFatherPath(m_szFile[0], FatherPath)){
		return FALSE;
	}

	if(!strcmp(FatherPath, m_EnvPath)){
		char SvnPath[255];
		memset(SvnPath, 0, sizeof(SvnPath));
		sprintf(SvnPath, "%s\\.svn", m_EnvPath);
		if(PathFileExists(SvnPath)){
			return TRUE;
		}
	}

	char FilePath[255];
	memset(FilePath, 0, sizeof(FilePath));
	sprintf(FilePath, "%s\\SmtRec.dat", m_EnvPath);

	FILE *fp = fopen(FilePath, "r");
	if(NULL == fp){
		return FALSE;
	}

	fseek(fp, 0, SEEK_END);
	long fileLength = ftell(fp);
	int CycleTimes = (int)fileLength/255 - 1;
	fseek(fp, 255, SEEK_SET);

	char ReadBuff[255];
	int i = 0;

	for(i = 0; i < CycleTimes; i++){
		memset(ReadBuff, 0, sizeof(ReadBuff));
		fread(ReadBuff, 1, sizeof(ReadBuff), fp);
		if(!strcmp(ReadBuff, FatherPath+strlen(m_EnvPath))){
			break;
		}
	}

	fclose(fp);

	if(i < CycleTimes){
		return TRUE;
	}

	return FALSE;
}

BOOL CSmtShell::IsHaveEnvPath()
{
	if(m_NumFiles >= 2){
		for(int i = 0; i < m_NumFiles; i++){
			if(!strcmp(m_EnvPath, m_szFile[i])){
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CSmtShell::GetRepURL(char *pEnvPath, char *pRepURL)
{
	if(NULL == pEnvPath || NULL == pRepURL){
		return FALSE;
	}

	char FilePath[255];
	memset(FilePath, 0, sizeof(FilePath));
	sprintf(FilePath, "%s\\%s", pEnvPath, "SmtRec.dat");

	FILE *fp = fopen(FilePath, "r");
	if(NULL == fp){
		return FALSE;
	}

	char RepURL[255];
	memset(RepURL, 0, sizeof(RepURL));
	fread(RepURL, 1, sizeof(RepURL), fp);
	memcpy(pRepURL, RepURL, strlen(RepURL));

	fclose(fp);
	return TRUE;
}

BOOL CSmtShell::IsProductEnv()
{
	char RepURL[255];
	string sRepURL;
	memset(RepURL, 0, sizeof(RepURL));
	
	GetRepURL(m_EnvPath, RepURL);
	sRepURL = RepURL;

	if(sRepURL.npos != sRepURL.find("products")){
		return TRUE;
	}

	return FALSE;
}

HRESULT STDMETHODCALLTYPE CSmtShell::QueryContextMenu(THIS_ HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{ 
	HMENU SubMenu = CreatePopupMenu();
	memset(m_EnvPath, 0, sizeof(m_EnvPath));

	if(!IsWorkEvn(m_szFile[0], m_EnvPath)){
		if(FILE_ATTRIBUTE_DIRECTORY == GetFileAttributes(m_szFile[0])){
			if(m_NumFiles <= 1){
				InsertMenu(SubMenu, 0, MF_STRING | MF_BYPOSITION, idCmdFirst +101, _T("Set Environment"));
				
				InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
				InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Smt Operate"));
				InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
			}
		}
	}
	else{
		if(IsProductEnv()){
			int i = 0;
			InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +103, _T("Update"));
			
			InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
			InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Smt Operate"));
			InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
		}
		else{
			if(!IsInCtr()){
				int i = 0;
				if(!IsHaveEnvPath()){
					if(m_FathAddFlag){
						if(m_CouldAdd){
							InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +107, _T("Add"));
						}
						else{
							InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +108, _T("Revert"));
						}
					}
					else{
						InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +102, _T("Check out"));
						InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +103, _T("Update"));
						if(IsFatherInCtr()){
							InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
							InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +107, _T("Add"));
							InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +108, _T("Revert"));
						}
					}

					//InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +110, _T("Import"));
					
					InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
					InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Smt Operate"));
					InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
				}
			}
			else{
				int i = 0;
				if(!IsHaveEnvPath()){
					InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +104, _T("Commit"));
					InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +105, _T("Check in"));
					InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
					if(!m_AddFlag){
						InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +103, _T("Update"));
						InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +106, _T("Cancel"));
						InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
						InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +109, _T("Merge"));
					}
					InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst +108, _T("Revert"));
					
					InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
					InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Smt Operate"));
					InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
				}
			}
		}
	}

	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(109 + 1));
}

HRESULT STDMETHODCALLTYPE CSmtShell::InvokeCommand( __in CMINVOKECOMMANDINFO *pici)
{
	if(HIWORD(((CMINVOKECOMMANDINFOEX *) pici)->lpVerbW))
	{
		return S_OK;
	}
	else
	{
		if(LOWORD(pici->lpVerb)==101)
		{
			SmtSetEnv();
		}
		if(LOWORD(pici->lpVerb)==102)
		{
			SmtCheckout();
		}
		if(LOWORD(pici->lpVerb)==103)
		{
			SmtUpdate();
		}
		if(LOWORD(pici->lpVerb)==104)
		{
			SmtCommit();
		}
		if(LOWORD(pici->lpVerb)==105)
		{
			SmtCheckin();
		}
		if(LOWORD(pici->lpVerb)==106)
		{
			SmtCancel();
		}
		if(LOWORD(pici->lpVerb)==107)
		{
			SmtAdd();
		}
		if(LOWORD(pici->lpVerb)==108)
		{
			SmtRevert();
		}
		if(LOWORD(pici->lpVerb)==109)
		{
			SmtMerge();
		}
		/*
		if(LOWORD(pici->lpVerb)==110)
		{
			SmtImport();
		}
		*/
	}

	return S_OK;
}

STDMETHODIMP CSmtShell::SmtSetEnv(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here

	char SetEnvCmd[255];
	memset(SetEnvCmd, 0, sizeof(SetEnvCmd));
	sprintf(SetEnvCmd, "SetEnv \"%s\"", m_szFile[0]);

	::WinExec(SetEnvCmd, SW_HIDE);

	return S_OK;
}

STDMETHODIMP CSmtShell::SmtCheckout(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here

	string CheckoutCmd = "CheckOut ";

	for(int i = 0; i < m_NumFiles; i++){
		CheckoutCmd += "\"";
		CheckoutCmd += m_szFile[i];
		CheckoutCmd += "\"";
		if(i < m_NumFiles-1){
			CheckoutCmd += " ";
		}
	}

	::WinExec((char *)CheckoutCmd.c_str(), SW_HIDE);

	return S_OK;
}

STDMETHODIMP CSmtShell::SmtUpdate(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here

	string UpdateCmd = "Update ";

	for(int i = 0; i < m_NumFiles; i++){
		UpdateCmd += "\"";
		UpdateCmd += m_szFile[i];
		UpdateCmd += "\"";
		if(i < m_NumFiles-1){
			UpdateCmd += " ";
		}
	}

	::WinExec((char *)UpdateCmd.c_str(), SW_HIDE);

	return S_OK;
}

STDMETHODIMP CSmtShell::SmtCommit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here

	string CommitCmd = "Commit ";

	if(!strcmp(m_EnvPath, m_szFile[0])){
		CommitCmd += "\"";
		CommitCmd += m_szFile[0];
		CommitCmd += "\"";
		::WinExec((char *)CommitCmd.c_str(), SW_HIDE);
		return S_OK;
	}

	int tIndex = 0;

	for(int i = 0; i < m_InCtrCount; i++){
		tIndex = m_InCtrNo[i];
		CommitCmd += "\"";
		CommitCmd += m_szFile[tIndex];
		CommitCmd += "\"";
		if(i < m_InCtrCount-1){
			CommitCmd += " ";
		}
	}
	
	::WinExec((char *)CommitCmd.c_str(), SW_HIDE);

	return S_OK;
}

STDMETHODIMP CSmtShell::SmtCheckin(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here

	string CheckinCmd = "Checkin ";

	if(!strcmp(m_EnvPath, m_szFile[0])){
		CheckinCmd += "\"";
		CheckinCmd += m_szFile[0];
		CheckinCmd += "\"";
		::WinExec((char *)CheckinCmd.c_str(), SW_HIDE);
		return S_OK;
	}

	int tIndex = 0;

	for(int i = 0; i < m_InCtrCount; i++){
		tIndex = m_InCtrNo[i];
		CheckinCmd += "\"";
		CheckinCmd += m_szFile[tIndex];
		CheckinCmd += "\"";
		if(i < m_InCtrCount-1){
			CheckinCmd += " ";
		}
	}

	::WinExec((char *)CheckinCmd.c_str(), SW_HIDE);

	return S_OK;
}

STDMETHODIMP CSmtShell::SmtCancel(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here

	string CancelCmd = "Cancel ";

	if(!strcmp(m_EnvPath, m_szFile[0])){
		CancelCmd += "\"";
		CancelCmd += m_szFile[0];
		CancelCmd += "\"";
		::WinExec((char *)CancelCmd.c_str(), SW_HIDE);
		return S_OK;
	}

	int tIndex = 0;

	for(int i = 0; i < m_InCtrCount; i++){
		tIndex = m_InCtrNo[i];
		CancelCmd += "\"";
		CancelCmd += m_szFile[tIndex];
		CancelCmd += "\"";
		if(i < m_InCtrCount-1){
			CancelCmd += " ";
		}
	}

	::WinExec((char *)CancelCmd.c_str(), SW_HIDE);

	return S_OK;
}

STDMETHODIMP CSmtShell::SmtAdd(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here

	string AddCmd = "Add ";

	for(int i = 0; i < m_NumFiles; i++){
		AddCmd += "\"";
		AddCmd += m_szFile[i];
		AddCmd += "\"";
		if(i < m_NumFiles-1){
			AddCmd += " ";
		}
	}

	::WinExec((char *)AddCmd.c_str(), SW_HIDE);

	return S_OK;
}

STDMETHODIMP CSmtShell::SmtRevert(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here

	string RevertCmd = "Revert ";

	if(!strcmp(m_EnvPath, m_szFile[0])){
		RevertCmd += "\"";
		RevertCmd += m_szFile[0];
		RevertCmd += "\"";
		::WinExec((char *)RevertCmd.c_str(), SW_HIDE);
		return S_OK;
	}

	int tIndex = 0;

	for(int i = 0; i < m_InCtrCount; i++){
		tIndex = m_InCtrNo[i];
		RevertCmd += "\"";
		RevertCmd += m_szFile[tIndex];
		RevertCmd += "\"";
		if(i < m_InCtrCount-1){
			RevertCmd += " ";
		}
	}

	::WinExec((char *)RevertCmd.c_str(), SW_HIDE);

	return S_OK;
}

STDMETHODIMP CSmtShell::SmtMerge(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here

	string MergeCmd = "Merge ";

	if(!strcmp(m_EnvPath, m_szFile[0])){
		MergeCmd += "\"";
		MergeCmd += m_szFile[0];
		MergeCmd += "\"";
		::WinExec((char *)MergeCmd.c_str(), SW_HIDE);
		return S_OK;
	}

	int tIndex = 0;

	for(int i = 0; i < m_InCtrCount; i++){
		tIndex = m_InCtrNo[i];
		MergeCmd += "\"";
		MergeCmd += m_szFile[tIndex];
		MergeCmd += "\"";
		if(i < m_InCtrCount-1){
			MergeCmd += " ";
		}
	}

	::WinExec((char *)MergeCmd.c_str(), SW_HIDE);

	return S_OK;
}

STDMETHODIMP CSmtShell::SmtImport(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here

	string ImportCmd = "Import ";

	for(int i = 0; i < m_NumFiles; i++){
		ImportCmd += "\"";
		ImportCmd += m_szFile[i];
		ImportCmd += "\"";
		if(i < m_NumFiles-1){
			ImportCmd += " ";
		}
	}

	::WinExec((char *)ImportCmd.c_str(), SW_HIDE);

	return S_OK;
}
