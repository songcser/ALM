// CheckoutMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Checkout.h"
#include "CheckoutMsgDlg.h"
#include "afxdialogex.h"


// CCheckoutMsgDlg dialog

IMPLEMENT_DYNAMIC(CCheckoutMsgDlg, CDialogEx)

CCheckoutMsgDlg::CCheckoutMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCheckoutMsgDlg::IDD, pParent)
{

}

CCheckoutMsgDlg::~CCheckoutMsgDlg()
{
}

void CCheckoutMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECKOUTMSG, m_CheckoutMsg);
}


BEGIN_MESSAGE_MAP(CCheckoutMsgDlg, CDialogEx)
END_MESSAGE_MAP()


// CCheckoutMsgDlg message handlers


BOOL CCheckoutMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetWindowTextA("Checkout message");
	m_CheckoutMsg.SetWindowTextA(m_StrMsg.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
