// ShowProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "ShowProgressDlg.h"
#include "afxdialogex.h"


// CShowProgressDlg dialog

IMPLEMENT_DYNAMIC(CShowProgressDlg, CDialogEx)

CShowProgressDlg::CShowProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowProgressDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CShowProgressDlg::~CShowProgressDlg()
{
}

void CShowProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOW_PROGRESS, m_pShowProgress);
}

BEGIN_MESSAGE_MAP(CShowProgressDlg, CDialogEx)
	ON_WM_TIMER()
	ON_MESSAGE(WM_END_MESSAGE, OnEndMessage)
END_MESSAGE_MAP()

// CShowProgressDlg message handlers
BOOL CShowProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	SetTimer(1000, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CShowProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	m_pShowProgress.StepIt();

	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CShowProgressDlg::OnEndMessage(WPARAM wParam, LPARAM lParam) 
{ 
	KillTimer(1000);
	CDialogEx::OnOK();
	return 0; 
}