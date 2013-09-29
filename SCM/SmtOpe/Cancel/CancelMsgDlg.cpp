// CancelMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Cancel.h"
#include "CancelMsgDlg.h"
#include "afxdialogex.h"


// CCancelMsgDlg dialog

IMPLEMENT_DYNAMIC(CCancelMsgDlg, CDialogEx)

CCancelMsgDlg::CCancelMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCancelMsgDlg::IDD, pParent)
{

}

CCancelMsgDlg::~CCancelMsgDlg()
{
}

void CCancelMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CACELMSG, m_CancelMsg);
}


BEGIN_MESSAGE_MAP(CCancelMsgDlg, CDialogEx)
END_MESSAGE_MAP()


// CCancelMsgDlg message handlers


BOOL CCancelMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetWindowTextA("Cancel message");
	m_CancelMsg.SetWindowTextA(m_StrMsg.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
