#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TeamExplorerKernel.h"
#include "ShowRetMsgDlg.h"

// CCommitDlg dialog
class CCommitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommitDlg)

public:
	CCommitDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCommitDlg();

// Dialog Data
	enum { IDD = IDD_COMMIT_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CTeamExplorerKernel m_Kernel;

	CEdit m_eCommitPath;
	CEdit m_eCommitLog;
	CListCtrl m_lCommitFile;

	CShowRetMsgDlg m_ShowRetMsgDlg;

	void InitImage();
	void InitialFilesList();
	int GetIconIndex(char *path, BOOL bIsDir, BOOL bSelected);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnOK();
	afx_msg LRESULT OnTeamExplorerExit(WPARAM wParam, LPARAM lParam);
};
