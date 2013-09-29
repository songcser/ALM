#pragma once
#include "afxwin.h"
#include "colorstatic.h"

class CTeamExplorerKernel;

// CSetUserDlg dialog
class CSetUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetUserDlg)

public:
	CSetUserDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetUserDlg();

// Dialog Data
	enum { IDD = IDD_SETUSER_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString m_ServerURL;

	CTeamExplorerKernel *m_pKernel;

	CEdit m_ePassword;
	CEdit m_eUserName;
	CColorStatic m_sInputMention;

	afx_msg void OnBnOK();
	virtual BOOL OnInitDialog();
};
