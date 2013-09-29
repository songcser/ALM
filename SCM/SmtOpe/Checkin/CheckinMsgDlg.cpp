// CheckinMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Checkin.h"
#include "CheckinMsgDlg.h"
#include "afxdialogex.h"


// CCheckinMsgDlg dialog

IMPLEMENT_DYNAMIC(CCheckinMsgDlg, CDialogEx)

CCheckinMsgDlg::CCheckinMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCheckinMsgDlg::IDD, pParent)
{

}

CCheckinMsgDlg::~CCheckinMsgDlg()
{
}

void CCheckinMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECKINMSG, m_CheckinMsg);
}


BEGIN_MESSAGE_MAP(CCheckinMsgDlg, CDialogEx)
END_MESSAGE_MAP()


// CCheckinMsgDlg message handlers


BOOL CCheckinMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetWindowTextA("Checkin message");
	m_CheckinMsg.SetWindowTextA(m_StrMsg.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
