// CommitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "CommitDlg.h"
#include "afxdialogex.h"
#include "Public.h"

// CCommitDlg dialog

IMPLEMENT_DYNAMIC(CCommitDlg, CDialogEx)

CCommitDlg::CCommitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommitDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CCommitDlg::~CCommitDlg()
{
}

void CCommitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMMITPATH_EDIT, m_eCommitPath);
	DDX_Control(pDX, IDC_COMMITFILE_LIST, m_lCommitFile);
	DDX_Control(pDX, IDC_COMMITLOG_EDIT, m_eCommitLog);
}

BEGIN_MESSAGE_MAP(CCommitDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCommitDlg::OnBnOK)
	ON_MESSAGE(WM_TEAM_EXPLORER_EXIT, OnTeamExplorerExit)
END_MESSAGE_MAP()

// CCommitDlg message handlers
BOOL CCommitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	string sCommitPath;

	if(__argc <= 2){
		m_eCommitPath.SetWindowTextA("nothing need to commit");
	}
	else{
		for(int i = 2; i< __argc; i++){
			sCommitPath += __argv[i];
			sCommitPath += "\r\n";

			m_Kernel.AddWcPath(__argv[i]);
		}
		m_eCommitPath.SetWindowTextA(sCommitPath.c_str());

		m_Kernel.GetCommitObject();

		LONG lStyle;
		lStyle = GetWindowLong(m_lCommitFile.m_hWnd, GWL_STYLE);
		lStyle &= ~LVS_TYPEMASK;
		lStyle |= LVS_REPORT;
		SetWindowLong(m_lCommitFile.m_hWnd, GWL_STYLE,lStyle);

		DWORD dwStyle = m_lCommitFile.GetExtendedStyle();
		dwStyle |= LVS_EX_GRIDLINES;
		dwStyle |= LVS_EX_CHECKBOXES;
		dwStyle |= LVS_EX_FULLROWSELECT;
		m_lCommitFile.SetExtendedStyle(dwStyle);

		CRect rect;
		m_lCommitFile.GetClientRect(rect);
		m_lCommitFile.InsertColumn(0, "File Name", LVCFMT_LEFT, rect.Width() - rect.Width()/4);
		m_lCommitFile.InsertColumn(1, "File Status", LVCFMT_LEFT, rect.Width()/4);

		InitImage();

		InitialFilesList();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CCommitDlg::OnTeamExplorerExit(WPARAM wParam, LPARAM lParam)
{
	m_ShowRetMsgDlg.DestroyWindow();
	CDialogEx::OnOK();
	return 0;
}

void CCommitDlg::InitialFilesList()
{
	int iSize = m_Kernel.m_OpeObjects.size();

	int j = 0;
	for(int i = 0; i < iSize; i++){
		int nIcon = GetIconIndex((char *)m_Kernel.m_OpeObjects.at(i).c_str(), FALSE, FALSE);

		m_lCommitFile.InsertItem(j, m_Kernel.m_OpeObjects.at(i).c_str(), nIcon);
		m_lCommitFile.SetItemText(j, 1, "Modify");

		m_lCommitFile.SetCheck(j);

		j++;
	}

	iSize = m_Kernel.m_AddObjects.size();
	for(int i = 0; i < iSize; i++){
		int nIcon;
		if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes((char *)m_Kernel.m_AddObjects.at(i).c_str())){
			nIcon = GetIconIndex((char *)m_Kernel.m_AddObjects.at(i).c_str(), FALSE, FALSE);
		}
		else{
			nIcon = GetIconIndex((char *)m_Kernel.m_AddObjects.at(i).c_str(), TRUE, FALSE);
		}

		m_lCommitFile.InsertItem(j, m_Kernel.m_AddObjects.at(i).c_str(), nIcon);
		m_lCommitFile.SetItemText(j, 1, "Add");

		m_lCommitFile.SetCheck(j);

		j++;
	}

	iSize = m_Kernel.m_IgnoreObjects.size();
	for(int i = 0; i < iSize; i++){
		int nIcon;
		if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes((char *)m_Kernel.m_IgnoreObjects.at(i).c_str())){
			nIcon = GetIconIndex((char *)m_Kernel.m_IgnoreObjects.at(i).c_str(), FALSE, FALSE);
		}
		else{
			nIcon = GetIconIndex((char *)m_Kernel.m_IgnoreObjects.at(i).c_str(), TRUE, FALSE);
		}

		m_lCommitFile.InsertItem(j, m_Kernel.m_IgnoreObjects.at(i).c_str(), nIcon);
		m_lCommitFile.SetItemText(j, 1, "Unversion");

		j++;
	}
}

int CCommitDlg::GetIconIndex(char *path, BOOL bIsDir, BOOL bSelected)
{
	SHFILEINFO sfi;
	memset(&sfi,0,sizeof(sfi));

	if (bIsDir){
		SHGetFileInfo(path,
			FILE_ATTRIBUTE_DIRECTORY,
			&sfi,
			sizeof(sfi),
			SHGFI_SMALLICON|SHGFI_SYSICONINDEX|
			SHGFI_USEFILEATTRIBUTES|(bSelected?SHGFI_OPENICON:0));
		return sfi.iIcon;
	}
	else{
		SHGetFileInfo(path,
			FILE_ATTRIBUTE_NORMAL,
			&sfi,
			sizeof(sfi),
			SHGFI_SMALLICON|SHGFI_SYSICONINDEX|
			SHGFI_USEFILEATTRIBUTES|(bSelected?SHGFI_OPENICON:0));
		return sfi.iIcon;
	}

	return -1;
}

void CCommitDlg::InitImage()
{
	HIMAGELIST himlSmall;
	HIMAGELIST himlLarge;

	SHFILEINFO sfi;
	char cSysDir[MAX_PATH];
	memset(cSysDir,0,sizeof(cSysDir));

	CString strBuf;
	GetWindowsDirectory(cSysDir,MAX_PATH);
	strBuf = cSysDir;
	sprintf(cSysDir,"%s",strBuf.Left(strBuf.Find("\\")+1));

	himlSmall = (HIMAGELIST)SHGetFileInfo((LPCSTR)cSysDir,
		0,
		&sfi,
		sizeof(SHFILEINFO),
		SHGFI_SYSICONINDEX|SHGFI_SMALLICON);
	himlLarge = (HIMAGELIST)SHGetFileInfo((LPCSTR)cSysDir,
		0,
		&sfi,
		sizeof(SHFILEINFO),
		SHGFI_SYSICONINDEX|SHGFI_SMALLICON);

	if (himlLarge&&himlSmall){
		::SendMessage(m_lCommitFile.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)himlSmall);
		::SendMessage(m_lCommitFile.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)himlLarge);
	}
}

void CCommitDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here
	
	if(__argc <= 2){
		CDialogEx::OnOK();
		return;
	}

	string sWcPath;
	if(GetWcPath(__argv[2], sWcPath)){
		m_Kernel.GetReadOnlyModifyObject((char *)sWcPath.c_str());
		int iSize = m_Kernel.m_ReadOnlyModifyObjects.size();
		if(iSize > 0){
			string sReadOnlyModify = "these read only files had been modified, make sure commit?\r\n";
			for(int i = 0; i < iSize; i++){
				string tmpStr(m_Kernel.m_ReadOnlyModifyObjects[i].c_str());
				sReadOnlyModify += tmpStr;
				if(i < iSize-1){
					sReadOnlyModify += "\r\n";
				}
			}
			if(IDYES != AfxMessageBox(sReadOnlyModify.c_str(), MB_YESNO)){
				m_Kernel.ClearReadOnlyModifyObjects();
				CDialogEx::OnOK();
				return ;
			}
			m_Kernel.ClearReadOnlyModifyObjects();
		}
	}

	CString cLog;
	string sLog;
	m_eCommitLog.GetWindowTextA(cLog);
	sLog = CStringToString(cLog);
	if(sLog.length() <= 0){
		AfxMessageBox("Please input log message, thank you!");
		return;
	}

	m_ShowRetMsgDlg.Create(IDD_SHOWRETMSG_DIALOG);
	m_ShowRetMsgDlg.m_pKernel = &m_Kernel;
	m_ShowRetMsgDlg.ShowWindow(SW_SHOW);

	m_Kernel.ClearAddObjects();
	m_Kernel.ClearIgnoreObjects();
	m_Kernel.ClearOpeObjects();

	string sAddPath = "";
	int FilesCount = m_lCommitFile.GetItemCount();
	for(int i = 0; i < FilesCount; i++){
		if(m_lCommitFile.GetCheck(i)){
			CString cFilePath;
			CString cFileStatus;
			string sFileStatus;
			string sFilePath;

			cFilePath = m_lCommitFile.GetItemText(i, 0);
			cFileStatus = m_lCommitFile.GetItemText(i, 1);
			sFilePath = CStringToString(cFilePath);
			sFileStatus = CStringToString(cFileStatus);

			if(!strcmp("Modify", sFileStatus.c_str())){
				m_Kernel.AddOpeObject((char *)sFilePath.c_str());
			}
			else if(!strcmp("Add", sFileStatus.c_str())){
				if(sAddPath.length() > 0){
					if(sAddPath.length() < sFilePath.length()){
						if('\\' == sFilePath[sAddPath.length()] && !memcmp(sAddPath.c_str(), sFilePath.c_str(), sAddPath.length())){
							continue;
						}
					}
				}
				m_Kernel.AddAddObject((char *)sFilePath.c_str());
				sAddPath = sFilePath;
			}
			else if(!strcmp("Unversion", sFileStatus.c_str())){
				m_Kernel.AddIgnoreObject((char *)sFilePath.c_str());
			}
		}
	}

	if((m_Kernel.m_OpeObjects.size()+m_Kernel.m_AddObjects.size()+m_Kernel.m_IgnoreObjects.size()) <= 0){
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("nothing need to commit", 0);
		return;
	}

	int iFrom = 0;
	BOOL bCommitFlag = m_Kernel.ExeCommit((char *)sLog.c_str());
	m_ShowRetMsgDlg.ShowCommitMsg(iFrom, bCommitFlag);
	iFrom = m_Kernel.m_RetMsgs.size();

	if(bCommitFlag){
		int iSize = m_Kernel.m_AddObjects.size();
		for(int i = 0; i < iSize; i++){
			m_Kernel.ExeDealAdd((char *)(m_Kernel.m_AddObjects[i].c_str()));
			m_ShowRetMsgDlg.ShowCommitMsg(iFrom, TRUE);
			iFrom = m_Kernel.m_RetMsgs.size();
		}

		iSize = m_Kernel.m_IgnoreObjects.size();
		for(int i = 0; i < iSize; i++){
			m_Kernel.ExeDealAdd((char *)(m_Kernel.m_IgnoreObjects[i].c_str()));
			m_ShowRetMsgDlg.ShowCommitMsg(iFrom, TRUE);
			iFrom = m_Kernel.m_RetMsgs.size();
		}
	}

	if(m_Kernel.m_RetMsgs.size() <= 0){
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("nothing need to commit", 0);
	}
	else{
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("commit completed!", 0);
	}

	(CButton *)GetDlgItem(IDOK)->EnableWindow(FALSE);
}
