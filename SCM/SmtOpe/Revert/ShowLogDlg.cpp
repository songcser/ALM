// ShowLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShowLogDlg.h"
#include "afxdialogex.h"


// CShowLogDlg dialog

IMPLEMENT_DYNAMIC(CShowLogDlg, CDialogEx)

CShowLogDlg::CShowLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowLogDlg::IDD, pParent)
{

}

CShowLogDlg::~CShowLogDlg()
{
}

void CShowLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWLOG_EDIT, m_ShowLog);
}


BEGIN_MESSAGE_MAP(CShowLogDlg, CDialogEx)
END_MESSAGE_MAP()


// CShowLogDlg message handlers
void CShowLogDlg::SetMessage(char *message)
{
	m_Message = message;
}

BOOL CShowLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ShowLog.SetWindowTextA(m_Message);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
