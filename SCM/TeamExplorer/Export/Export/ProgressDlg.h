#pragma once
#include "afxcmn.h"

#define WM_END_MESSAGE (WM_USER+101)

// CProgressDlg dialog

class CProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressDlg)

public:
	CProgressDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProgressDlg();

// Dialog Data
	enum { IDD = IDD_PROGRESS_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg LRESULT OnEndMessage(WPARAM wParam, LPARAM lParam); 

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CProgressCtrl m_pProgress;
};
