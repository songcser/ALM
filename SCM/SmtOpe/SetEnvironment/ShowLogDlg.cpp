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
	DDX_Control(pDX, IDC_SHOWLOG_EDIT, m_showLog);
}


BEGIN_MESSAGE_MAP(CShowLogDlg, CDialogEx)
END_MESSAGE_MAP()


// CShowLogDlg message handlers
void CShowLogDlg::ShowLog(char *message)
{
	//m_showLog.SetWindowTextA(message);
	m_Message = message;
	//ShowWindow(SW_SHOW);
}

BOOL CShowLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_showLog.SetWindowTextA(m_Message);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
