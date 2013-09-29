
// SmATL_RevertDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <string>
#include "ShowLogDlg.h"

using namespace std;
// CSmATL_RevertDlg dialog
class CSmATL_RevertDlg : public CDialogEx
{
// Construction
public:
	CSmATL_RevertDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SMATL_REVERT_DIALOG };

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
	afx_msg void OnBnClickedOk();
	CEdit m_RetEdit;
	CShowLogDlg m_ShowLog;
	string ExeCmd(char *pszCmd);
};
