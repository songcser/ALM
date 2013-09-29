// ImportMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Import.h"
#include "ImportMsgDlg.h"
#include "afxdialogex.h"


// CImportMsgDlg dialog

IMPLEMENT_DYNAMIC(CImportMsgDlg, CDialogEx)

CImportMsgDlg::CImportMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImportMsgDlg::IDD, pParent)
{

}

CImportMsgDlg::~CImportMsgDlg()
{
}

void CImportMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMPORTMSG, m_ImportMsg);
}


BEGIN_MESSAGE_MAP(CImportMsgDlg, CDialogEx)
END_MESSAGE_MAP()


// CImportMsgDlg message handlers

BOOL CImportMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetWindowTextA("Import");
	m_ImportMsg.SetWindowText(m_StrMsg.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
