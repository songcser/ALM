
// MergeDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "ShowLogDlg.h"

#include <string>

using namespace std;

// CMergeDlg dialog
class CMergeDlg : public CDialogEx
{
// Construction
public:
	CMergeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MERGE_DIALOG };

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
	CShowLogDlg m_ShowLog;
	//afx_msg void OnBnClickedShowlogButton();
	//afx_msg void OnBnClickedOk();
	CEdit m_SourceEdit;
	CEdit m_DestinationEdit;
	CEdit m_VersionFrom;
	CEdit m_VersionTo;

	BOOL FindRecordFile(char *pCrtPath, char *pRetPath);
	BOOL GetFatherPath(char *pCrtPath, char *pFatherPath);
	BOOL GetRepURL(char *pEnvPath, char *pRepURL);
	BOOL GetRelativeURL(char *filePath, char *RelativePath);
	string ExeCmd(char *pszCmd);
	string CStringToString(CString SourceStr);
	void branchesTotrunk(char *AbsolationURL,char *branchesPos);
	void trunkTobranches(char *AbsolationURL,char *trunk);
	void SetLibrary(char *LibPath);

private:
	char m_EnvPath[255];
	char m_RepURL[255];
	char m_AbsolationURL[255];
	char m_MyPath[255];
	char m_RelativePath[255];
	char m_LastPath[255];
	char m_FirstPath[255];
	char m_LibPath[255];
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedShowlogButton();
	//CComboBox m_Library;
	CComboBox m_Library;
//	afx_msg void OnCloseupLibraryCombo();
	afx_msg void OnSelchangeLibraryCombo();
};
