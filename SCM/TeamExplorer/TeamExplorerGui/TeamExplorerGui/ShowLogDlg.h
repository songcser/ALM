#pragma once
#include "TeamExplorerKernel.h"
#include "afxwin.h"

// CShowLogDlg dialog
class CShowLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowLogDlg)

public:
	CShowLogDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CShowLogDlg();

// Dialog Data
	enum { IDD = IDD_SHOWLOG_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CTeamExplorerKernel *m_pKernel;
	CTeamExplorerKernel m_Kernel;

	CEdit m_eShowLog;

	virtual BOOL OnInitDialog();
};
