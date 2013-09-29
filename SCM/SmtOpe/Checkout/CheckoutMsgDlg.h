#pragma once
#include "afxwin.h"

// CCheckoutMsgDlg dialog

class CCheckoutMsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckoutMsgDlg)

public:
	CCheckoutMsgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckoutMsgDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_CheckoutMsg;
	string m_StrMsg;
	virtual BOOL OnInitDialog();
};
