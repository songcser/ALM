#pragma once
#include "afxwin.h"


// CDownloadMsgDlg dialog

class CDownloadMsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDownloadMsgDlg)

public:
	CDownloadMsgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDownloadMsgDlg();

// Dialog Data
	enum { IDD = IDD_DOWNLOADMSG_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CEdit m_eDownloadRetMsg;
	string m_sRelyRet;

	virtual BOOL OnInitDialog();
};
