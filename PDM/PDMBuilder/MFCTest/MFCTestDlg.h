
// MFCTestDlg.h : header file
//

#pragma once

#include "PDMBuilder.h"


#pragma comment(lib,"PDMBuilder.lib")
// CMFCTestDlg dialog
using namespace std;
class CMFCTestDlg : public CDialogEx
{
// Construction
public:
	CMFCTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCTEST_DIALOG };

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
};
