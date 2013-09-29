// CheckoutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "CheckoutDlg.h"
#include "afxdialogex.h"
#include "Public.h"

// CCheckoutDlg dialog

IMPLEMENT_DYNAMIC(CCheckoutDlg, CDialogEx)

CCheckoutDlg::CCheckoutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCheckoutDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CCheckoutDlg::~CCheckoutDlg()
{
}

void CCheckoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECKOUTFILE_LIST, m_lCheckoutFile);
	DDX_Control(pDX, IDC_CHECKOUTPATH_EDIT, m_eCheckoutPath);
}

BEGIN_MESSAGE_MAP(CCheckoutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCheckoutDlg::OnBnOK)
	ON_MESSAGE(WM_TEAM_EXPLORER_EXIT, OnTeamExplorerExit)
END_MESSAGE_MAP()

// CCheckoutDlg message handlers
BOOL CCheckoutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	string sCheckoutPath;

	if(__argc <= 2){
		m_eCheckoutPath.SetWindowTextA("nothing need to check out");
	}
	else{
		for(int i = 2; i< __argc; i++){
			sCheckoutPath += __argv[i];
			sCheckoutPath += "\r\n";

			m_Kernel.AddWcPath(__argv[i]);
		}
		m_eCheckoutPath.SetWindowTextA(sCheckoutPath.c_str());

		m_Kernel.GetCheckoutObject();

		LONG lStyle;
		lStyle = GetWindowLong(m_lCheckoutFile.m_hWnd, GWL_STYLE);
		lStyle &= ~LVS_TYPEMASK;
		lStyle |= LVS_REPORT;
		SetWindowLong(m_lCheckoutFile.m_hWnd, GWL_STYLE,lStyle);

		DWORD dwStyle = m_lCheckoutFile.GetExtendedStyle();
		dwStyle |= LVS_EX_GRIDLINES;
		dwStyle |= LVS_EX_CHECKBOXES;
		dwStyle |= LVS_EX_FULLROWSELECT;
		m_lCheckoutFile.SetExtendedStyle(dwStyle);

		CRect rect;
		m_lCheckoutFile.GetClientRect(rect);
		m_lCheckoutFile.InsertColumn(0, "File Name", LVCFMT_LEFT, rect.Width() - rect.Width()/4);
		m_lCheckoutFile.InsertColumn(1, "File Status", LVCFMT_LEFT, rect.Width()/4);

		InitImage();

		InitialFilesList();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CCheckoutDlg::OnTeamExplorerExit(WPARAM wParam, LPARAM lParam)
{
	m_ShowRetMsgDlg.DestroyWindow();
	CDialogEx::OnOK();
	return 0;
}

void CCheckoutDlg::InitialFilesList()
{
	int count = m_Kernel.m_OpeObjects.size();

	int j = 0;
	for(int i=0; i<count; i++){
		if(IsIgnoreFile(i)){
			continue;
		}
		
		int nIcon = GetIconIndex((char *)m_Kernel.m_OpeObjects.at(i).c_str(),FALSE,FALSE);

		m_lCheckoutFile.InsertItem(j, m_Kernel.m_OpeObjects.at(i).c_str(), nIcon);
		m_lCheckoutFile.SetItemText(j, 1, "Read Only");

		m_lCheckoutFile.SetCheck(j);

		j++;
	}
}

BOOL CCheckoutDlg::IsIgnoreFile(int iIndex)
{
	int iSize = m_Kernel.m_IgnoreObjects.size();
	for(int i = 0; i < iSize; i++){
		int OpeObjectLen = m_Kernel.m_OpeObjects[iIndex].length();
		int IgnoreObjectLen = m_Kernel.m_IgnoreObjects[i].length();
		if(OpeObjectLen == IgnoreObjectLen){
			if(!memcmp(m_Kernel.m_OpeObjects[iIndex].c_str(), m_Kernel.m_IgnoreObjects[i].c_str(), IgnoreObjectLen)){
				return TRUE;
			}
		}
		if(OpeObjectLen > IgnoreObjectLen){
			if('\\' == m_Kernel.m_OpeObjects[iIndex][IgnoreObjectLen] && !memcmp(m_Kernel.m_OpeObjects[iIndex].c_str(), m_Kernel.m_IgnoreObjects[i].c_str(), IgnoreObjectLen)){
				return TRUE;
			}
		}
	}

	return FALSE;
}

int CCheckoutDlg::GetIconIndex(char *path,BOOL bIsDir, BOOL bSelected)
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

void CCheckoutDlg::InitImage()
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
		::SendMessage(m_lCheckoutFile.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)himlSmall);
		::SendMessage(m_lCheckoutFile.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)himlLarge);
	}
}

void CCheckoutDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here

	m_ShowRetMsgDlg.Create(IDD_SHOWRETMSG_DIALOG);
	m_ShowRetMsgDlg.m_pKernel = &m_Kernel;
	m_ShowRetMsgDlg.ShowWindow(SW_SHOW);

	int j = 0;
	int FilesCount = m_lCheckoutFile.GetItemCount();
	for(int i = 0; i < FilesCount; i++){
		if(m_lCheckoutFile.GetCheck(i)){
			CString cFilePath;
			string sFilePath;
			cFilePath = m_lCheckoutFile.GetItemText(i, 0);
			sFilePath = CStringToString(cFilePath);
			BOOL CheckoutFlag = m_Kernel.ExeCheckout((char *)sFilePath.c_str());
			m_ShowRetMsgDlg.ShowCheckoutMsg(j, CheckoutFlag);
			j++;
		}
	}

	if(m_Kernel.m_RetMsgs.size() <= 0){
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("nothing need to check out", 0);
	}
	else{
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("check out completed!");
	}

	(CButton *)GetDlgItem(IDOK)->EnableWindow(FALSE);
}
