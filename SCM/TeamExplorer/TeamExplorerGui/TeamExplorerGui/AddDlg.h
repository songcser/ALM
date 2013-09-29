#pragma once
#include "TeamExplorerKernel.h"
#include "ShowRetMsgDlg.h"
#include "afxwin.h"
#include "afxcmn.h"

// CAddDlg dialog

class CAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDlg)

public:
	CAddDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddDlg();

// Dialog Data
	enum { IDD = IDD_ADD_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CTeamExplorerKernel m_Kernel;
	CShowRetMsgDlg m_ShowRetMsgDlg;

	CEdit m_eAddPath;
	CListCtrl m_lAddPath;

	void InitImage();
	void InitialFilesList();
	int GetIconIndex(char *path, BOOL bIsDir, BOOL bSelected);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnOK();
	afx_msg LRESULT OnTeamExplorerExit(WPARAM wParam, LPARAM lParam);
};
