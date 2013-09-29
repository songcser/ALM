#pragma once
#include "afxwin.h"


// CShowMessageDlg dialog

class CShowMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowMessageDlg)

public:
	CShowMessageDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CShowMessageDlg();

// Dialog Data
	enum { IDD = IDD_SHOWMESSAGE_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	string m_Message;
	CEdit m_eMessage;
};
