
// AddDlg.h : header file
//

#pragma once
#include "afxwin.h"

// CAddDlg dialog
class CAddDlg : public CDialogEx
{
// Construction
public:
	CAddDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ADD_DIALOG };

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
	CEdit m_AddItem;
	string CStringToString(CString SourceStr);
	string ExeCmd(char *pszCmd);
	afx_msg void OnBnAdd();

	BOOL FindRecordFile(char *pCrtPath, char *pRetPath);
	BOOL GetRelativePath(char *filePath, char *RelativePath);
	BOOL GetFatherPath(char *pCrtPath, char *pFatherPath);
	BOOL IsExistFile(char *URLPath, char *RelativePath);
};
