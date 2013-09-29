// CommitMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Commit.h"
#include "CommitMsgDlg.h"
#include "afxdialogex.h"


// CCommitMsgDlg dialog

IMPLEMENT_DYNAMIC(CCommitMsgDlg, CDialogEx)

CCommitMsgDlg::CCommitMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommitMsgDlg::IDD, pParent)
{

}

CCommitMsgDlg::~CCommitMsgDlg()
{
}

void CCommitMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMMITMSG, m_CommitMsg);
}


BEGIN_MESSAGE_MAP(CCommitMsgDlg, CDialogEx)
END_MESSAGE_MAP()


// CCommitMsgDlg message handlers


BOOL CCommitMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetWindowTextA("Commit message");
	m_CommitMsg.SetWindowTextA(m_StrMsg.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
