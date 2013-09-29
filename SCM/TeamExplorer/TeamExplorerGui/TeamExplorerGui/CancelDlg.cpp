// CancelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "CancelDlg.h"
#include "afxdialogex.h"
#include "Public.h"

// CCancelDlg dialog

IMPLEMENT_DYNAMIC(CCancelDlg, CDialogEx)

CCancelDlg::CCancelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCancelDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CCancelDlg::~CCancelDlg()
{
}

void CCancelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CANCELPATH_EDIT, m_eCancelPath);
	DDX_Control(pDX, IDC_CANCELFILE_LIST, m_lCancelFile);
}

BEGIN_MESSAGE_MAP(CCancelDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCancelDlg::OnBnOK)
	ON_MESSAGE(WM_TEAM_EXPLORER_EXIT, OnTeamExplorerExit)
END_MESSAGE_MAP()

// CCancelDlg message handlers
BOOL CCancelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	string sCancelPath;

	if(__argc <= 2){
		m_eCancelPath.SetWindowTextA("nothing need to cancel");
	}
	else{
		for(int i = 2; i< __argc; i++){
			sCancelPath += __argv[i];
			sCancelPath += "\r\n";

			m_Kernel.AddWcPath(__argv[i]);
		}
		m_eCancelPath.SetWindowTextA(sCancelPath.c_str());

		m_Kernel.GetCancelObject();

		LONG lStyle;
		lStyle = GetWindowLong(m_lCancelFile.m_hWnd, GWL_STYLE);
		lStyle &= ~LVS_TYPEMASK;
		lStyle |= LVS_REPORT;
		SetWindowLong(m_lCancelFile.m_hWnd, GWL_STYLE,lStyle);

		DWORD dwStyle = m_lCancelFile.GetExtendedStyle();
		dwStyle |= LVS_EX_GRIDLINES;
		dwStyle |= LVS_EX_CHECKBOXES;
		dwStyle |= LVS_EX_FULLROWSELECT;
		m_lCancelFile.SetExtendedStyle(dwStyle);

		CRect rect;
		m_lCancelFile.GetClientRect(rect);
		m_lCancelFile.InsertColumn(0, "File Name", LVCFMT_LEFT, rect.Width() - rect.Width()/4);
		m_lCancelFile.InsertColumn(1, "File Status", LVCFMT_LEFT, rect.Width()/4);

		InitImage();

		InitialFilesList();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CCancelDlg::OnTeamExplorerExit(WPARAM wParam, LPARAM lParam)
{
	m_ShowRetMsgDlg.DestroyWindow();
	CDialogEx::OnOK();
	return 0;
}

void CCancelDlg::InitialFilesList()
{
	int iSize = m_Kernel.m_OpeObjects.size();

	int j = 0;
	for(int i = 0; i < iSize; i++){
		int nIcon = GetIconIndex((char *)m_Kernel.m_OpeObjects.at(i).c_str(), FALSE, FALSE);

		m_lCancelFile.InsertItem(j, m_Kernel.m_OpeObjects.at(i).c_str(), nIcon);
		m_lCancelFile.SetItemText(j, 1, "Modify");

		m_lCancelFile.SetCheck(j);

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

		m_lCancelFile.InsertItem(j, m_Kernel.m_AddObjects.at(i).c_str(), nIcon);
		m_lCancelFile.SetItemText(j, 1, "Add");

		m_lCancelFile.SetCheck(j);

		j++;
	}

	iSize = m_Kernel.m_NormalObjects.size();
	for(int i = 0; i < iSize; i++){
		int nIcon = GetIconIndex((char *)m_Kernel.m_NormalObjects.at(i).c_str(), FALSE, FALSE);

		m_lCancelFile.InsertItem(j, m_Kernel.m_NormalObjects.at(i).c_str(), nIcon);
		m_lCancelFile.SetItemText(j, 1, "Normal");

		m_lCancelFile.SetCheck(j);

		j++;
	}
}

int CCancelDlg::GetIconIndex(char *path, BOOL bIsDir, BOOL bSelected)
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

void CCancelDlg::InitImage()
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
		::SendMessage(m_lCancelFile.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)himlSmall);
		::SendMessage(m_lCancelFile.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)himlLarge);
	}
}

void CCancelDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here
	if(__argc <= 2){
		CDialogEx::OnOK();
		return;
	}

	m_ShowRetMsgDlg.Create(IDD_SHOWRETMSG_DIALOG);
	m_ShowRetMsgDlg.m_pKernel = &m_Kernel;
	m_ShowRetMsgDlg.ShowWindow(SW_SHOW);

	int iFrom = 0;
	string sAddPath = "";
	int FilesCount = m_lCancelFile.GetItemCount();
	for(int i = 0; i < FilesCount; i++){
		if(m_lCancelFile.GetCheck(i)){
			CString cFilePath;
			CString cFileStatus;
			string sFileStatus;
			string sFilePath;

			cFilePath = m_lCancelFile.GetItemText(i, 0);
			cFileStatus = m_lCancelFile.GetItemText(i, 1);
			sFilePath = CStringToString(cFilePath);
			sFileStatus = CStringToString(cFileStatus);

			if(!strcmp("Modify", sFileStatus.c_str())){
				BOOL bCancelFlag = m_Kernel.ExeCancel(0, (char *)sFilePath.c_str());
				m_ShowRetMsgDlg.ShowCancelMsg(iFrom, bCancelFlag);
				iFrom = m_Kernel.m_RetMsgs.size();
			}
			else if(!strcmp("Normal", sFileStatus.c_str())){
				BOOL bCancelFlag = m_Kernel.ExeCancel(1, (char *)sFilePath.c_str());
				m_ShowRetMsgDlg.ShowCancelMsg(iFrom, bCancelFlag);
				iFrom = m_Kernel.m_RetMsgs.size();
			}
			else if(!strcmp("Add", sFileStatus.c_str())){
				if(sAddPath.length() > 0){
					if(sAddPath.length() < sFilePath.length()){
						if('\\' == sFilePath[sAddPath.length()] && !memcmp(sAddPath.c_str(), sFilePath.c_str(), sAddPath.length())){
							continue;
						}
					}
				}
				BOOL bCancelFlag = m_Kernel.ExeCancel(2, (char *)sFilePath.c_str());
				m_ShowRetMsgDlg.ShowCancelMsg(iFrom, bCancelFlag);
				iFrom = m_Kernel.m_RetMsgs.size();
				sAddPath = sFilePath;
			}
		}
	}

	if(m_Kernel.m_RetMsgs.size() <= 0){
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("nothing need to cancel");
	}
	else{
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("cancel completed!");
	}

	(CButton *)GetDlgItem(IDOK)->EnableWindow(FALSE);
}
