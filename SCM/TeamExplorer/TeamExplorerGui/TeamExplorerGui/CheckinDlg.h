#pragma once
#include "TeamExplorerKernel.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "ShowRetMsgDlg.h"

// CCheckinDlg dialog
class CCheckinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckinDlg)

public:
	CCheckinDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckinDlg();

// Dialog Data
	enum { IDD = IDD_CHECKIN_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CTeamExplorerKernel m_Kernel;

	CEdit m_eCheckinPath;
	CEdit m_eCheckinLog;
	CListCtrl m_lCheckinFile;

	CShowRetMsgDlg m_ShowRetMsgDlg;

	void InitImage();
	void InitialFilesList();
	int GetIconIndex(char *path, BOOL bIsDir, BOOL bSelected);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnOK();
	afx_msg LRESULT OnTeamExplorerExit(WPARAM wParam, LPARAM lParam);
};
