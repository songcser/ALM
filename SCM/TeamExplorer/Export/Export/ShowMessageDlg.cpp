// ShowMessageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Export.h"
#include "ShowMessageDlg.h"
#include "afxdialogex.h"


// CShowMessageDlg dialog

IMPLEMENT_DYNAMIC(CShowMessageDlg, CDialogEx)

CShowMessageDlg::CShowMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowMessageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER);
}

CShowMessageDlg::~CShowMessageDlg()
{
}

void CShowMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWMESSAGE_EDIT, m_eMessage);
}


BEGIN_MESSAGE_MAP(CShowMessageDlg, CDialogEx)
END_MESSAGE_MAP()


// CShowMessageDlg message handlers


BOOL CShowMessageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_eMessage.SetWindowText(m_Message.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
