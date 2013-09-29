// RevertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "RevertDlg.h"
#include "afxdialogex.h"
#include "Public.h"

// CRevertDlg dialog
IMPLEMENT_DYNAMIC(CRevertDlg, CDialogEx)

CRevertDlg::CRevertDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRevertDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CRevertDlg::~CRevertDlg()
{
}

void CRevertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REVERT_EDIT, m_eRevertPath);
	DDX_Control(pDX, IDC_REVERT_LIST, m_lRevertPath);
}

BEGIN_MESSAGE_MAP(CRevertDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRevertDlg::OnBnOK)
	ON_MESSAGE(WM_TEAM_EXPLORER_EXIT, OnTeamExplorerExit)
END_MESSAGE_MAP()

// CRevertDlg message handlers
BOOL CRevertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	string sRevertPath;

	if(__argc <= 2){
		m_eRevertPath.SetWindowTextA("nothing need to revert");
	}
	else{
		for(int i = 2; i< __argc; i++){
			sRevertPath += __argv[i];
			sRevertPath += "\r\n";

			m_Kernel.AddWcPath(__argv[i]);
		}
		m_eRevertPath.SetWindowTextA(sRevertPath.c_str());

		m_Kernel.GetRevertObject();

		LONG lStyle;
		lStyle = GetWindowLong(m_lRevertPath.m_hWnd, GWL_STYLE);
		lStyle &= ~LVS_TYPEMASK;
		lStyle |= LVS_REPORT;
		SetWindowLong(m_lRevertPath.m_hWnd, GWL_STYLE,lStyle);

		DWORD dwStyle = m_lRevertPath.GetExtendedStyle();
		dwStyle |= LVS_EX_GRIDLINES;
		dwStyle |= LVS_EX_CHECKBOXES;
		dwStyle |= LVS_EX_FULLROWSELECT;
		m_lRevertPath.SetExtendedStyle(dwStyle);

		CRect rect;
		m_lRevertPath.GetClientRect(rect);
		m_lRevertPath.InsertColumn(0, "File Name", LVCFMT_LEFT, rect.Width() - rect.Width()/4);
		m_lRevertPath.InsertColumn(1, "File Status", LVCFMT_LEFT, rect.Width()/4);

		InitImage();

		InitialFilesList();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CRevertDlg::OnTeamExplorerExit(WPARAM wParam, LPARAM lParam)
{
	m_ShowRetMsgDlg.DestroyWindow();
	CDialogEx::OnOK();
	return 0;
}

void CRevertDlg::InitialFilesList()
{
	int j = 0;
	int iSize = m_Kernel.m_OpeObjects.size();
	for(int i = 0; i < iSize; i++){
		int nIcon;
		nIcon = GetIconIndex((char *)m_Kernel.m_OpeObjects.at(i).c_str(), FALSE, FALSE);

		m_lRevertPath.InsertItem(j, m_Kernel.m_OpeObjects.at(i).c_str(), nIcon);
		m_lRevertPath.SetItemText(j, 1, "Modify");

		m_lRevertPath.SetCheck(j);

		j++;
	}

	iSize = m_Kernel.m_NormalObjects.size();
	for(int i = 0; i < iSize; i++){
		int nIcon;
		nIcon = GetIconIndex((char *)m_Kernel.m_NormalObjects.at(i).c_str(), FALSE, FALSE);

		m_lRevertPath.InsertItem(j, m_Kernel.m_NormalObjects.at(i).c_str(), nIcon);
		m_lRevertPath.SetItemText(j, 1, "Conflict");

		m_lRevertPath.SetCheck(j);

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

		m_lRevertPath.InsertItem(j, m_Kernel.m_AddObjects.at(i).c_str(), nIcon);
		m_lRevertPath.SetItemText(j, 1, "Add");

		m_lRevertPath.SetCheck(j);

		j++;
	}
}

int CRevertDlg::GetIconIndex(char *path, BOOL bIsDir, BOOL bSelected)
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

void CRevertDlg::InitImage()
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
		::SendMessage(m_lRevertPath.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)himlSmall);
		::SendMessage(m_lRevertPath.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)himlLarge);
	}
}

void CRevertDlg::OnBnOK()
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
	int FilesCount = m_lRevertPath.GetItemCount();
	for(int i = FilesCount-1; i >= 0; i--){
		if(m_lRevertPath.GetCheck(i)){
			CString cFilePath;
			string sFilePath;

			cFilePath = m_lRevertPath.GetItemText(i, 0);
			sFilePath = CStringToString(cFilePath);

			BOOL bRevertFlag = m_Kernel.ExeRevert((char *)sFilePath.c_str());
			m_ShowRetMsgDlg.ShowRevertMsg(iFrom, bRevertFlag);
			iFrom = m_Kernel.m_RetMsgs.size();
		}
	}

	if(m_Kernel.m_RetMsgs.size() <= 0){
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("nothing need to revert");
	}
	else{
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("revert completed!");
	}

	(CButton *)GetDlgItem(IDOK)->EnableWindow(FALSE);
}
