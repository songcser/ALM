// PopupMenu.cpp : Implementation of CPopupMenu

#include "stdafx.h"
#include "PopupMenu.h"
#include "TeamExplorerCore.h"
#pragma comment(lib, "TeamExplorerCore.lib")

// CPopupMenu
HRESULT STDMETHODCALLTYPE CPopupMenu::Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject *pdtobj, HKEY hkeyProgID)
{
	FORMATETC fmt = {CF_HDROP,NULL,DVASPECT_CONTENT,-1,TYMED_HGLOBAL};
	STGMEDIUM stg = {TYMED_HGLOBAL};
	HDROP hDrop;

	if (FAILED(pdtobj->GetData(&fmt,&stg))){
		return E_INVALIDARG;
	}

	hDrop = (HDROP)GlobalLock (stg.hGlobal);

	if (NULL == hDrop){
		return E_INVALIDARG;
	}

	UINT uNumFiles = DragQueryFile (hDrop, 0xFFFFFFFF, NULL, 0);
	HRESULT hr = S_OK;

	if (0 == uNumFiles){
		GlobalUnlock (stg.hGlobal);
		ReleaseStgMedium (&stg);
		return E_INVALIDARG;
	}

	m_NumFiles = uNumFiles;
	char szFile[1024];
	for(int i = 0; i < uNumFiles; i++){
		memset(szFile, 0, sizeof(szFile));
		if (0 == DragQueryFile (hDrop, i, szFile, sizeof(szFile))){
			hr = E_INVALIDARG;
		}
		string sFile(szFile);
		m_Files.push_back(sFile);
	}

	GlobalUnlock (stg.hGlobal);
	ReleaseStgMedium (&stg);

	return hr;
}

HRESULT STDMETHODCALLTYPE CPopupMenu::GetCommandString(THIS_ UINT_PTR idCmd, UINT uType, UINT *pwReserved, LPSTR pszName, UINT cchMax)
{
	if (idCmd < 1 || idCmd > 13)
	{
		return E_INVALIDARG;
	}

	lstrcpynA(pszName,"Warning! Something is wrong", cchMax);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPopupMenu::QueryContextMenu(THIS_ HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	if(!IsWorkCopy(&m_Files, m_NumFiles, m_WcPath)){
		if(m_NumFiles >= 2){
		}
		else{
			if (FILE_ATTRIBUTE_DIRECTORY == GetFileAttributes(m_Files[0].c_str())){
				int i = 0;
				HMENU SubMenu = CreatePopupMenu();
				m_hInstance = GetModuleHandle("TeamExplorerShellMenu.dll");

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 1, _T("Set Environment"));
				m_hSetEnv = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_SETENV)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hSetEnv, m_hSetEnv);

				InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

				InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Team Explorer"));
				m_hPopupMenu = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_POPUPMENU)); 
				SetMenuItemBitmaps(hmenu, indexMenu+1, MF_BYPOSITION, m_hPopupMenu, m_hPopupMenu);

				InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

				DestroyMenu(SubMenu);
			}
		}
	}
	else{
		if(!IsTeamExplorer(m_WcPath)){
			return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(13 + 1));
		}

		int i = 0;
		HMENU SubMenu = CreatePopupMenu();
		m_hInstance = GetModuleHandle("TeamExplorerShellMenu.dll");

		if(IsProductOrTags(m_WcPath)){
			InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 2, _T("Update"));
			m_hUpdate = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_UPDATE)); 
			SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hUpdate, m_hUpdate);
		}
		else{
			if(CouldWrite(&m_Files, &m_WriteFiles, m_NumFiles)){
				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 3, _T("Check out"));
				m_hCheckout = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_CHECKOUT)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCheckout, m_hCheckout);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 4, _T("Commit"));
				m_hCommit = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_COMMIT)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCommit, m_hCommit);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 5, _T("Check in"));
				m_hCheckin = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_CHECKIN)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCheckin, m_hCheckin);

				InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 2, _T("Update"));
				m_hUpdate = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_UPDATE)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hUpdate, m_hUpdate);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 6, _T("Cancel"));
				m_hCancel = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_CANCEL)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCancel, m_hCancel);

				InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 8, _T("Revert"));
				m_hRevert = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_REVERT)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hRevert, m_hRevert);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 9, _T("Merge"));
				m_hMerge = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_MERGE)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hMerge, m_hMerge);
			}
			else{
				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 3, _T("Check out"));
				m_hCheckout = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_CHECKOUT)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCheckout, m_hCheckout);

				InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 7, _T("Add"));
				m_hAdd = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_ADD)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hAdd, m_hAdd);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 2, _T("Update"));
				m_hUpdate = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_UPDATE)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hUpdate, m_hUpdate);
			}
		}

		InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 10, _T("Show log"));
		m_hShowLog = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_SHOWLOG)); 
		SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hShowLog, m_hShowLog);

		InsertMenu(SubMenu, i++, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);

		InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 11, _T("Diff"));
		m_hDiff = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_DIFF));
		SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hDiff, m_hDiff);

		InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 12, _T("Compare"));
		m_hCompare = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_COMPARE));
		SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCompare, m_hCompare);

		InsertMenu(SubMenu, i++, MF_BYPOSITION | MF_STRING, idCmdFirst + 13, _T("Update Rely Files"));
		m_hDownload = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_DOWNLOAD));
		SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hDownload, m_hDownload);

		InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

		InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Team Explorer"));
		m_hPopupMenu = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_POPUPMENU)); 
		SetMenuItemBitmaps(hmenu, indexMenu+1, MF_BYPOSITION, m_hPopupMenu, m_hPopupMenu);

		InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

		DestroyMenu(SubMenu);
	}

	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(13 + 1));
}

HRESULT STDMETHODCALLTYPE CPopupMenu::InvokeCommand( __in CMINVOKECOMMANDINFO *pici)
{
	if(HIWORD(((CMINVOKECOMMANDINFOEX *)pici)->lpVerbW)){
		return S_OK;
	}
	else
	{
		if(1 == LOWORD(pici->lpVerb)){
			SetEnv();
		}
		else if(2 == LOWORD(pici->lpVerb)){
			Update();
		}
		else if(3 == LOWORD(pici->lpVerb)){
			Checkout();
		}
		else if(4 == LOWORD(pici->lpVerb)){
			Commit();
		}
		else if(5 == LOWORD(pici->lpVerb)){
			Checkin();
		}
		else if(6 == LOWORD(pici->lpVerb)){
			Cancel();
		}
		else if(7 == LOWORD(pici->lpVerb)){
			Add();
		}
		else if(8 == LOWORD(pici->lpVerb)){
			Revert();
		}
		else if(9 == LOWORD(pici->lpVerb)){
			Merge();
		}
		else if(10 == LOWORD(pici->lpVerb)){
			ShowLog();
		}
		else if(11 == LOWORD(pici->lpVerb)){
			Diff();
		}
		else if(12 == LOWORD(pici->lpVerb)){
			Compare();
		}
		else if(13 == LOWORD(pici->lpVerb)){
			UpdateRelyFiles();
		}
	}

	return S_OK;
}

STDMETHODIMP CPopupMenu::SetEnv(void)
{
	// TODO: Add your implementation code here

	char SetEnvCmd[255];
	memset(SetEnvCmd, 0, sizeof(SetEnvCmd));
	sprintf(SetEnvCmd, "TeamExplorerGui 00 \"%s\"", m_Files[0].c_str());

	::WinExec(SetEnvCmd, SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::Checkout(void)
{
	// TODO: Add your implementation code here

	string CheckoutCmd = "TeamExplorerGui 01 ";

	for(int i = 0; i < m_NumFiles; i++){
		CheckoutCmd += "\"";
		CheckoutCmd += m_Files[i].c_str();
		CheckoutCmd += "\"";
		if(i < m_NumFiles-1){
			CheckoutCmd += " ";
		}
	}

	::WinExec((char *)CheckoutCmd.c_str(), SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::Update(void)
{
	// TODO: Add your implementation code here

	string UpdateCmd = "TeamExplorerGui 02 ";

	for(int i = 0; i < m_NumFiles; i++){
		UpdateCmd += "\"";
		UpdateCmd += m_Files[i].c_str();
		UpdateCmd += "\"";
		if(i < m_NumFiles-1){
			UpdateCmd += " ";
		}
	}

	::WinExec((char *)UpdateCmd.c_str(), SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::Commit(void)
{
	// TODO: Add your implementation code here

	string CommitCmd = "TeamExplorerGui 03 ";

	int iSize = m_WriteFiles.size();
	for(int i = 0; i < iSize; i++){
		CommitCmd += "\"";
		CommitCmd += m_WriteFiles[i].c_str();
		CommitCmd += "\"";
		if(i < iSize-1){
			CommitCmd += " ";
		}
	}

	::WinExec((char *)CommitCmd.c_str(), SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::Checkin(void)
{
	// TODO: Add your implementation code here

	string CheckinCmd = "TeamExplorerGui 04 ";

	int iSize = m_WriteFiles.size();
	for(int i = 0; i < iSize; i++){
		CheckinCmd += "\"";
		CheckinCmd += m_WriteFiles[i].c_str();
		CheckinCmd += "\"";
		if(i < iSize-1){
			CheckinCmd += " ";
		}
	}

	::WinExec((char *)CheckinCmd.c_str(), SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::Cancel(void)
{
	// TODO: Add your implementation code here

	string CancelCmd = "TeamExplorerGui 05 ";

	int iSize = m_WriteFiles.size();
	for(int i = 0; i < iSize; i++){
		CancelCmd += "\"";
		CancelCmd += m_WriteFiles[i].c_str();
		CancelCmd += "\"";
		if(i < iSize-1){
			CancelCmd += " ";
		}
	}

	::WinExec((char *)CancelCmd.c_str(), SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::Add(void)
{
	// TODO: Add your implementation code here

	string AddCmd = "TeamExplorerGui 06 ";

	for(int i = 0; i < m_NumFiles; i++){
		AddCmd += "\"";
		AddCmd += m_Files[i].c_str();
		AddCmd += "\"";
		if(i < m_NumFiles-1){
			AddCmd += " ";
		}
	}

	::WinExec((char *)AddCmd.c_str(), SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::Revert(void)
{
	// TODO: Add your implementation code here

	string RevertCmd = "TeamExplorerGui 07 ";

	int iSize = m_WriteFiles.size();
	for(int i = 0; i < iSize; i++){
		RevertCmd += "\"";
		RevertCmd += m_WriteFiles[i].c_str();
		RevertCmd += "\"";
		if(i < iSize-1){
			RevertCmd += " ";
		}
	}

	::WinExec((char *)RevertCmd.c_str(), SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::Merge(void)
{
	// TODO: Add your implementation code here

	string MergeCmd = "TeamExplorerGui 08 ";

	int iSize = m_WriteFiles.size();
	for(int i = 0; i < iSize; i++){
		MergeCmd += "\"";
		MergeCmd += m_WriteFiles[i].c_str();
		MergeCmd += "\"";
		if(i < iSize-1){
			MergeCmd += " ";
		}
	}

	::WinExec((char *)MergeCmd.c_str(), SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::ShowLog(void)
{
	// TODO: Add your implementation code here

	string ShowLogCmd = "TeamExplorerGui 09 ";

	for(int i = 0; i < m_NumFiles; i++){
		ShowLogCmd += "\"";
		ShowLogCmd += m_Files[i].c_str();
		ShowLogCmd += "\"";
		if(i < m_NumFiles-1){
			ShowLogCmd += " ";
		}
	}

	::WinExec((char *)ShowLogCmd.c_str(), SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::Diff(void)
{
	// TODO: Add your implementation code here

	string DiffCmd = "TeamExplorerGui 10 ";

	for(int i = 0; i < m_NumFiles; i++){
		DiffCmd += "\"";
		DiffCmd += m_Files[i].c_str();
		DiffCmd += "\"";
		if(i < m_NumFiles-1){
			DiffCmd += " ";
		}
	}

	::WinExec((char *)DiffCmd.c_str(), SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::Compare(void)
{
	// TODO: Add your implementation code here

	string CompareCmd = "TeamExplorerGui 11 ";

	for(int i = 0; i < m_NumFiles; i++){
		CompareCmd += "\"";
		CompareCmd += m_Files[i].c_str();
		CompareCmd += "\"";
		if(i < m_NumFiles-1){
			CompareCmd += " ";
		}
	}

	::WinExec((char *)CompareCmd.c_str(), SW_SHOW);

	return S_OK;
}

STDMETHODIMP CPopupMenu::UpdateRelyFiles(void)
{
	// TODO: Add your implementation code here

	string DownloadCmd = "TeamExplorerGui 12 ";

	for(int i = 0; i < m_NumFiles; i++){
		DownloadCmd += "\"";
		DownloadCmd += m_Files[i].c_str();
		DownloadCmd += "\"";
		if(i < m_NumFiles-1){
			DownloadCmd += " ";
		}
	}

	::WinExec((char *)DownloadCmd.c_str(), SW_SHOW);

	return S_OK;
}
