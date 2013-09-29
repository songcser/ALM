#pragma once
#include "afxwin.h"
#include "TeamExplorerKernel.h"
#include "ShowRetMsgDlg.h"

// CMergeDlg dialog

class CMergeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMergeDlg)

public:
	CMergeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMergeDlg();

// Dialog Data
	enum { IDD = IDD_MERGE_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CTeamExplorerKernel m_Kernel;
	CShowRetMsgDlg m_ShowRetMsgDlg;

	CEdit m_eSourcePath;
	CEdit m_eDestPath;
	CEdit m_eFromRevision;
	CEdit m_eToRevision;
	CComboBox m_cFromVersion;

	BOOL GetProVersion();

	afx_msg void OnBnShowLog();
	afx_msg void OnBnOK();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnTeamExplorerExit(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelChangeFromVersion();
};
