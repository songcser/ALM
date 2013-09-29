#pragma once
#include "afxwin.h"
#include "resource.h"

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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:
	CEdit m_ShowLog;

	CString m_Message;
	virtual BOOL OnInitDialog();

	void SetMessage(char *message);
};
