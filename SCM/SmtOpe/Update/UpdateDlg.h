
// UpdateDlg.h : header file
//

#pragma once
#include "afxwin.h"

// CUpdateDlg dialog
class CUpdateDlg : public CDialogEx
{
// Construction
public:
	CUpdateDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UPDATE_DIALOG };

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
	CEdit m_RetMsg;
	char m_EnvPath[255];
	char m_RcvPath[255];
	char m_RepURL[255];
	string m_RetStr;
	BOOL FindRecordFile(char *pCrtPath, char *pRetPath);
	BOOL GetFatherPath(char *pCrtPath, char *pFatherPath);
	BOOL GetRepURL(char *pEnvPath, char *pRepURL);
	BOOL GetPathEnd(char *pPath, char *pPathEnd);
	string ExeCmd(char *pszCmd);
	//string SmtUpdate(char *pEnvPath, char *pRepURL);
	string SmtUpdate(char *pPath);
	BOOL GetExistFile(char *pPath,char *pExistFiles,bool isBack);
	BOOL GetRelativePath(char *filePath, char *RelativePath);
	BOOL GetRelativeURL(char *filePath,char *RelativeURL);
	BOOL RenameFile(char *files,char *tmpName);
	BOOL RenameFileBack(char *file,char *tmpName);
	BOOL IsExist(char *pPath);
	string UpdateRely();
	BOOL SwitchURL(char *pRepURL, string &doURL);
	BOOL DealURL(string &doURL);
};
