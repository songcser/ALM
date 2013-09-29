
// ImportDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "ImportMsgDlg.h"

// CImportDlg dialog
class CImportDlg : public CDialogEx
{
// Construction
public:
	CImportDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_IMPORT_DIALOG };

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
	CEdit m_ImportItem;
	CComboBox m_ImportTo;
	char m_EnvPath[255];
	char m_RepURL[255];
	char m_FatherPath[255];
	CImportMsgDlg m_ImportMsgDlg;

	BOOL GetRepURL(char *pEnvPath, char *pRepURL);
	BOOL GetFatherPath(char *pCrtPath, char *pFatherPath);
	BOOL FindRecordFile(char *pCrtPath, char *pRetPath);
	string ExeCmd(char *pszCmd);
	string CStringToString(CString SourceStr);
	BOOL SwitchURL(char *pRepURL, string &doURL);
	void SetCombox();
	BOOL IsNeedList();
	BOOL GetEndPath(char *pPath, char *pRetPath);

	afx_msg void OnBnImport();
};
