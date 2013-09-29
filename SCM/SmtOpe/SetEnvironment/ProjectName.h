#pragma once
#include "afxwin.h"
#include "stdafx.h"
#include "resource.h"

// CProjectName dialog

class CProjectName : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectName)

public:
	CProjectName(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProjectName();

// Dialog Data
	enum { IDD = IDD_PROJECTNAME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ProjectPath;
//	afx_msg void OnEnChangeEdit1();

	CString m_strPath;
	afx_msg void OnBnClickedOk();
};
