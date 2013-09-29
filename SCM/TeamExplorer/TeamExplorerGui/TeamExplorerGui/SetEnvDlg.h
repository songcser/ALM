
// SetEnvDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "SelectDepDlg.h"
#include "SetUserDlg.h"
#include "AdvanceDlg.h"
#include "ShowRetMsgDlg.h"
#include "TeamExplorerKernel.h"
#include "ShowProgressDlg.h"
#include "PDMBuilder.h"
#pragma comment(lib, "TeamExplorerKernel.lib")
#pragma comment(lib, "PDMBuilder.lib")

// CSetEnvDlg dialog
class CSetEnvDlg : public CDialogEx
{
// Construction
public:
	CSetEnvDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SETENV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	string m_ServerURL;

	BOOL m_AdvanceFlag;
	BOOL m_FirstFlag;

	CSetUserDlg m_SetUserDlg;
	CShowRetMsgDlg m_ShowRetMsgDlg;

	CShowProgressDlg m_ShowProgressDlg;

	CEdit m_eWcPath;
	CEdit m_eConfFile;

	CTeamExplorerKernel m_Kernel;

	BOOL ExeSetEnv();
	BOOL BeginMultiThread();
	BOOL EndMultiThread();

	afx_msg void OnBnSetUser();
	afx_msg void OnBnOK();
	afx_msg void OnBnSelConf();
};
