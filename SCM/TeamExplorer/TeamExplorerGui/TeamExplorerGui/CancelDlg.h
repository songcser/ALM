#pragma once
#include "TeamExplorerKernel.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "ShowRetMsgDlg.h"

// CCancelDlg dialog

class CCancelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCancelDlg)

public:
	CCancelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCancelDlg();

// Dialog Data
	enum { IDD = IDD_CANCEL_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CTeamExplorerKernel m_Kernel;
	CEdit m_eCancelPath;
	CListCtrl m_lCancelFile;

	CShowRetMsgDlg m_ShowRetMsgDlg;

	void InitImage();
	void InitialFilesList();
	int GetIconIndex(char *path, BOOL bIsDir, BOOL bSelected);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnOK();
	afx_msg LRESULT OnTeamExplorerExit(WPARAM wParam, LPARAM lParam);
};
