#pragma once
#include "afxwin.h"
#include "TeamExplorerKernel.h"

// CAdvanceDlg dialog

class CAdvanceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdvanceDlg)

public:
	CAdvanceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdvanceDlg();

// Dialog Data
	enum { IDD = IDD_ADVANCE_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	string m_ServerURL;

	CTeamExplorerKernel *m_pKernel;

	CComboBox m_cServerURL;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnOK();
};
