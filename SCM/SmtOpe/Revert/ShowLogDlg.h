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
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ShowLog;
	CString m_Message;

	void SetMessage(char *message);
	virtual BOOL OnInitDialog();
};
