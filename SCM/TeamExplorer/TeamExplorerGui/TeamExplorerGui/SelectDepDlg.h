#pragma once
#include "afxcmn.h"

class CTeamExplorerKernel;

// CSelectDepDlg dialog
class CSelectDepDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectDepDlg)

public:
	CSelectDepDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectDepDlg();

// Dialog Data
	enum { IDD = IDD_SELECTDEP_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString m_ServerURL;
	string m_DepName;

	CTeamExplorerKernel *m_pKernel;
	
	CListCtrl m_lDepList;

	void InitialListDep();

	afx_msg void OnBnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickDepList(NMHDR *pNMHDR, LRESULT *pResult);
};
