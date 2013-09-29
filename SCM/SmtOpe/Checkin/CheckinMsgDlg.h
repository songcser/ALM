#pragma once
#include "afxwin.h"

// CCheckinMsgDlg dialog

class CCheckinMsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckinMsgDlg)

public:
	CCheckinMsgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckinMsgDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_CheckinMsg;
	string m_StrMsg;
	virtual BOOL OnInitDialog();
};
