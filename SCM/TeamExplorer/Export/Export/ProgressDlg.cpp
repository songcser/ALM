// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Export.h"
#include "ProgressDlg.h"
#include "afxdialogex.h"


// CProgressDlg dialog

IMPLEMENT_DYNAMIC(CProgressDlg, CDialogEx)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgressDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER);
}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_pProgress);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialogEx)
	ON_MESSAGE(WM_END_MESSAGE, OnEndMessage)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CProgressDlg message handlers


BOOL CProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	SetTimer(1001, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	m_pProgress.StepIt();

	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CProgressDlg::OnEndMessage(WPARAM wParam, LPARAM lParam) 
{ 
	KillTimer(1001);
	CDialogEx::OnOK();
	return 0; 
}