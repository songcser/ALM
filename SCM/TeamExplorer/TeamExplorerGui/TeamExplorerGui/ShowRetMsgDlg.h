#pragma once
#include "afxwin.h"
#include "TeamExplorerKernel.h"
#include "afxcmn.h"

// CShowRetMsgDlg dialog
class CShowRetMsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowRetMsgDlg)

public:
	CShowRetMsgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CShowRetMsgDlg();

// Dialog Data
	enum { IDD = IDD_SHOWRETMSG_DIALOG };

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CTeamExplorerKernel *m_pKernel;
	CRichEditCtrl m_eShowRetMsg;

	void ShowSetEnvMsg();
	void ShowCheckoutMsg(int iIndex, BOOL bCheckoutFlag);
	void ShowUpdateMsg();
	void ShowCommitMsg(int iFrom, BOOL bCommitFlag);
	void ShowCheckinMsg(int iFrom, BOOL bCheckinFlag);
	void ShowCancelMsg(int iFrom, BOOL bCancelFlag);
	void ShowAddMsg(int iFrom, BOOL bAddFlag);
	void ShowRevertMsg(int iFrom, BOOL bRevertFlag);
	void ShowMergeMsg(int iFrom, BOOL bMergeFlag);

	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBnOK();
	afx_msg void OnBnCancel();
};
