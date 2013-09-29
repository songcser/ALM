#pragma once
#include "TeamExplorerKernel.h"
#include "ShowRetMsgDlg.h"
#include "afxwin.h"
#include "afxcmn.h"

// CRevertDlg dialog

class CRevertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRevertDlg)

public:
	CRevertDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRevertDlg();

// Dialog Data
	enum { IDD = IDD_REVERT_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CTeamExplorerKernel m_Kernel;
	CShowRetMsgDlg m_ShowRetMsgDlg;


	CEdit m_eRevertPath;
	CListCtrl m_lRevertPath;

	void InitImage();
	void InitialFilesList();
	int GetIconIndex(char *path, BOOL bIsDir, BOOL bSelected);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnOK();
	afx_msg LRESULT OnTeamExplorerExit(WPARAM wParam, LPARAM lParam);
};
