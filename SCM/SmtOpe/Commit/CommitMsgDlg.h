#pragma once
#include "afxwin.h"

// CCommitMsgDlg dialog

class CCommitMsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommitMsgDlg)

public:
	CCommitMsgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCommitMsgDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_CommitMsg;
	string m_StrMsg;
	virtual BOOL OnInitDialog();
};
