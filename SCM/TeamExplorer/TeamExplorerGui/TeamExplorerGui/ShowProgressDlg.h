#pragma once
#include "afxcmn.h"

#define WM_END_MESSAGE (WM_USER+100)

// CShowProgressDlg dialog

class CShowProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowProgressDlg)

public:
	CShowProgressDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CShowProgressDlg();

// Dialog Data
	enum { IDD = IDD_SHOWPROGRESS_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg LRESULT OnEndMessage(WPARAM wParam, LPARAM lParam); 

	DECLARE_MESSAGE_MAP()

public:
	CProgressCtrl m_pShowProgress;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
