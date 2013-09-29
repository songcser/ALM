
// CommitDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CommitMsgDlg.h"

// CCommitDlg dialog
class CCommitDlg : public CDialogEx
{
// Construction
public:
	CCommitDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COMMIT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CCommitMsgDlg m_CommitMsgDlg;
	CEdit m_CommitItem;
	CEdit m_LogMsg;
	char m_EnvPath[255];
	string CStringToString(CString SourceStr);
	string ExeCmd(char *pszCmd);
	BOOL FindRecordFile(char *pCrtPath, char *pRetPath);
	BOOL DealAdd(string StatusStr);
	BOOL GetFatherPath(char *pCrtPath, char *pFatherPath);
	afx_msg void OnBnCommit();
};
