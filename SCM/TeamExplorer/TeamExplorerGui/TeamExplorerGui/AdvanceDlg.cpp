// AdvanceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "AdvanceDlg.h"
#include "afxdialogex.h"
#include "Public.h"
#include "SetEnvDlg.h"

// CAdvanceDlg dialog

IMPLEMENT_DYNAMIC(CAdvanceDlg, CDialogEx)

CAdvanceDlg::CAdvanceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdvanceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CAdvanceDlg::~CAdvanceDlg()
{
}

void CAdvanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SERVERURL_COMBO, m_cServerURL);
}

BEGIN_MESSAGE_MAP(CAdvanceDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAdvanceDlg::OnBnOK)
END_MESSAGE_MAP()

// CAdvanceDlg message handlers

BOOL CAdvanceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_cServerURL.AddString("http://192.168.99.10:8081/svn/");
	m_cServerURL.AddString("http://192.168.99.16:8081/svn/");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAdvanceDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here
	CString cServerURL;

	m_cServerURL.GetWindowTextA(cServerURL);
	if(cServerURL.GetLength() <= 0){
		AfxMessageBox("URL can't empty!");
		return ;
	}

	m_ServerURL = CStringToString(cServerURL);
	((CSetEnvDlg *)GetParent())->m_ServerURL = m_ServerURL;

	((CSetEnvDlg *)GetParent())->m_AdvanceFlag = TRUE;

	CDialogEx::OnOK();
}
