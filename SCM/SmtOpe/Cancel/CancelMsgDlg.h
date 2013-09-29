#pragma once
#include "afxwin.h"

// CCancelMsgDlg dialog

class CCancelMsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCancelMsgDlg)

public:
	CCancelMsgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCancelMsgDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_CancelMsg;
	string m_StrMsg;
	virtual BOOL OnInitDialog();
};
