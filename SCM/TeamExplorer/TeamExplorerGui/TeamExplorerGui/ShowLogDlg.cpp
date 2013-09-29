// ShowLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "ShowLogDlg.h"
#include "afxdialogex.h"
#include "Public.h"

// CShowLogDlg dialog

IMPLEMENT_DYNAMIC(CShowLogDlg, CDialogEx)

CShowLogDlg::CShowLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowLogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CShowLogDlg::~CShowLogDlg()
{
}

void CShowLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWLOG_EDIT, m_eShowLog);
}

BEGIN_MESSAGE_MAP(CShowLogDlg, CDialogEx)
END_MESSAGE_MAP()

// CShowLogDlg message handlers
BOOL CShowLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	char tSourceURL[255];

	if(__argc <= 2){
		m_eShowLog.SetWindowTextA("nothing need to show log");
	}
	else{
		if(!memcmp("09", __argv[1], 2)){
			for(int i = 2; i< __argc; i++){
				memset(tSourceURL, 0, sizeof(tSourceURL));
				m_Kernel.GetWcURL(__argv[i], tSourceURL);
				string sSourceURL = tSourceURL;
				RidPercent20(sSourceURL);
				m_Kernel.AddRetMsg((char *)sSourceURL.c_str());
				m_Kernel.AddRetMsg("\r\n\r\n");
				m_Kernel.ExeShowLog(((char *)sSourceURL.c_str()));
				m_Kernel.AddRetMsg("\r\n\r\n");
			}
			m_pKernel = &m_Kernel;
		}
	}

	int iSize = m_pKernel->m_RetMsgs.size();
	for(int i = 0; i < iSize; i++){
		m_eShowLog.ReplaceSel(m_pKernel->m_RetMsgs[i].c_str(), 0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
