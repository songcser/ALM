#pragma once
#include "afxwin.h"


// CImportMsgDlg dialog

class CImportMsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImportMsgDlg)

public:
	CImportMsgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImportMsgDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ImportMsg;
	string m_StrMsg;
	virtual BOOL OnInitDialog();
};
