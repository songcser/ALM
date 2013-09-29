#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ShowRetMsgDlg.h"
#include "TeamExplorerKernel.h"
#pragma comment(lib, "TeamExplorerKernel.lib")

// CCheckoutDlg dialog
class CCheckoutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckoutDlg)

public:
	CCheckoutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckoutDlg();

// Dialog Data
	enum { IDD = IDD_CHECKOUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	HICON m_hIcon;

	CListCtrl m_lCheckoutFile;
	CEdit m_eCheckoutPath;

 	CShowRetMsgDlg m_ShowRetMsgDlg;
	CTeamExplorerKernel m_Kernel;

	void InitialFilesList();
	void InitImage();
	int GetIconIndex(char *path,BOOL bIsDir, BOOL bSelected);

	BOOL IsIgnoreFile(int iIndex);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnOK();
	afx_msg LRESULT OnTeamExplorerExit(WPARAM wParam, LPARAM lParam); 
};
