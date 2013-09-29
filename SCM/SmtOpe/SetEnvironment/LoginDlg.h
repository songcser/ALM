#pragma once
#include "afxwin.h"
#include "resource.h"

// CLoginDlg dialog

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDlg();

// Dialog Data
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Name;
	CEdit m_Password;

	CString m_strName;
	CString m_strPassword;

//	afx_msg void OnEnChangeEdit1();
//	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedOk();
};
