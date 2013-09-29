// AddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "AddDlg.h"
#include "afxdialogex.h"
#include "Public.h"

// CAddDlg dialog

IMPLEMENT_DYNAMIC(CAddDlg, CDialogEx)

CAddDlg::CAddDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDPATH_EDIT, m_eAddPath);
	DDX_Control(pDX, IDC_ADD_LIST, m_lAddPath);
}

BEGIN_MESSAGE_MAP(CAddDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddDlg::OnBnOK)
	ON_MESSAGE(WM_TEAM_EXPLORER_EXIT, OnTeamExplorerExit)
END_MESSAGE_MAP()

// CAddDlg message handlers
BOOL CAddDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	string sAddPath;

	if(__argc <= 2){
		m_eAddPath.SetWindowTextA("nothing need to add");
	}
	else{
		for(int i = 2; i< __argc; i++){
			sAddPath += __argv[i];
			sAddPath += "\r\n";

			m_Kernel.AddWcPath(__argv[i]);
		}
		m_eAddPath.SetWindowTextA(sAddPath.c_str());

		m_Kernel.GetAddObject();

		LONG lStyle;
		lStyle = GetWindowLong(m_lAddPath.m_hWnd, GWL_STYLE);
		lStyle &= ~LVS_TYPEMASK;
		lStyle |= LVS_REPORT;
		SetWindowLong(m_lAddPath.m_hWnd, GWL_STYLE,lStyle);

		DWORD dwStyle = m_lAddPath.GetExtendedStyle();
		dwStyle |= LVS_EX_GRIDLINES;
		dwStyle |= LVS_EX_CHECKBOXES;
		dwStyle |= LVS_EX_FULLROWSELECT;
		m_lAddPath.SetExtendedStyle(dwStyle);

		CRect rect;
		m_lAddPath.GetClientRect(rect);
		m_lAddPath.InsertColumn(0, "File Name", LVCFMT_LEFT, rect.Width() - rect.Width()/4);
		m_lAddPath.InsertColumn(1, "File Status", LVCFMT_LEFT, rect.Width()/4);

		InitImage();

		InitialFilesList();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CAddDlg::OnTeamExplorerExit(WPARAM wParam, LPARAM lParam)
{
	m_ShowRetMsgDlg.DestroyWindow();
	CDialogEx::OnOK();
	return 0;
}

void CAddDlg::InitialFilesList()
{
	int j = 0;
	int iSize = m_Kernel.m_OpeObjects.size();
	for(int i = 0; i < iSize; i++){
		int nIcon;
		if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes((char *)m_Kernel.m_OpeObjects.at(i).c_str())){
			nIcon = GetIconIndex((char *)m_Kernel.m_OpeObjects.at(i).c_str(), FALSE, FALSE);
		}
		else{
			nIcon = GetIconIndex((char *)m_Kernel.m_OpeObjects.at(i).c_str(), TRUE, FALSE);
		}

		m_lAddPath.InsertItem(j, m_Kernel.m_OpeObjects.at(i).c_str(), nIcon);
		m_lAddPath.SetItemText(j, 1, "Unversion");

		m_lAddPath.SetCheck(j);

		j++;
	}
}

int CAddDlg::GetIconIndex(char *path, BOOL bIsDir, BOOL bSelected)
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

void CAddDlg::InitImage()
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
		::SendMessage(m_lAddPath.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)himlSmall);
		::SendMessage(m_lAddPath.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)himlLarge);
	}
}

void CAddDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here
	if(__argc <= 2){
		CDialogEx::OnOK();
		return;
	}

	m_ShowRetMsgDlg.Create(IDD_SHOWRETMSG_DIALOG);
	m_ShowRetMsgDlg.m_pKernel = &m_Kernel;
	m_ShowRetMsgDlg.ShowWindow(SW_SHOW);

	string UnCheckPath = "";
	int UnCheckPos = -1;
	int FilesCount = m_lAddPath.GetItemCount();
	for(int i = 0; i < FilesCount; i++){
		CString cFilePath;
		string sFilePath;

		cFilePath = m_lAddPath.GetItemText(i, 0);
		sFilePath = CStringToString(cFilePath);

		if(m_lAddPath.GetCheck(i)){
			if(UnCheckPath.length() > 0){
				if(UnCheckPath.length() < sFilePath.length()){
					if('\\' == sFilePath[UnCheckPath.length()] && !memcmp(UnCheckPath.c_str(), sFilePath.c_str(), UnCheckPath.length())){
						if(!m_lAddPath.GetCheck(UnCheckPos)){
							m_lAddPath.SetCheck(UnCheckPos);
						}
					}
				}
			}
		}
		else{
			if(UnCheckPath.length() > 0){
				if(UnCheckPath.length() < sFilePath.length()){
					if('\\' == sFilePath[UnCheckPath.length()] && !memcmp(UnCheckPath.c_str(), sFilePath.c_str(), UnCheckPath.length())){
					}
					else{
						UnCheckPath = sFilePath;
						UnCheckPos = i;
					}
				}
				else{
					UnCheckPath = sFilePath;
					UnCheckPos = i;
				}
			}
			else{
				UnCheckPath = sFilePath;
				UnCheckPos = i;
			}
		}
	}

	int iFrom = 0;
	FilesCount = m_lAddPath.GetItemCount();
	for(int i = 0; i < FilesCount; i++){
		if(m_lAddPath.GetCheck(i)){
			CString cFilePath;
			string sFilePath;

			cFilePath = m_lAddPath.GetItemText(i, 0);
			sFilePath = CStringToString(cFilePath);

			BOOL bAddFlag = m_Kernel.ExeAdd((char *)sFilePath.c_str());
			m_ShowRetMsgDlg.ShowAddMsg(iFrom, bAddFlag);
			iFrom = m_Kernel.m_RetMsgs.size();
		}
	}

	if(m_Kernel.m_RetMsgs.size() <= 0){
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("nothing need to add");
	}
	else{
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("add completed!");
	}

	(CButton *)GetDlgItem(IDOK)->EnableWindow(FALSE);
}
