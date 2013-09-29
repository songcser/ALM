// DownloadMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "DownloadMsgDlg.h"
#include "afxdialogex.h"


// CDownloadMsgDlg dialog

IMPLEMENT_DYNAMIC(CDownloadMsgDlg, CDialogEx)

CDownloadMsgDlg::CDownloadMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDownloadMsgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CDownloadMsgDlg::~CDownloadMsgDlg()
{
}

void CDownloadMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DOWNLOADRETMSG_EDIT, m_eDownloadRetMsg);
}


BEGIN_MESSAGE_MAP(CDownloadMsgDlg, CDialogEx)
END_MESSAGE_MAP()


// CDownloadMsgDlg message handlers


BOOL CDownloadMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(m_hIcon,TRUE);
	SetIcon(m_hIcon, FALSE);

	m_eDownloadRetMsg.SetWindowText(m_sRelyRet.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
