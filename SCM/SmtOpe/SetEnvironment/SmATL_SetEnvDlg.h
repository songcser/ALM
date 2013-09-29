
// SmATL_SetEnvDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <string>
#include "LoginDlg.h"
#include "ProjectName.h"
#include "ShowLogDlg.h"
#include <direct.h>

using namespace std;

// CSmATL_SetEnvDlg dialog
class CSmATL_SetEnvDlg : public CDialogEx
{
// Construction
public:
	CSmATL_SetEnvDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SMATL_SETENV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	void GetListView();

//public:
	//string ExeCmd(char *pszCmd);
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
	//CEdit m_URL_Repository;
	CEdit m_Path_WorkCopy;
	CTreeCtrl m_treeCtrl;
	//BOOL m_result;
	string m_URL_Repository;
	BOOL m_firstLogin;
	string m_congifPath;
	char m_ProjectName[255];
	string m_strRet;

	CLoginDlg m_Login;
	CProjectName m_ProjectPathDlg;
	CString m_strName;
	CString m_strPassword;
	BOOL m_IsCleanLogin;
	string m_ProductPath;
	//afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
//	afx_msg void OnClose();
//	afx_msg void OnDestroy();

	string CStringToString(CString SourceStr);
	string ExeCmd(char *pszCmd);
	void GetCongifPath();
	void GetProjectName();
	void GetProjectNameFromFile();
	void IsLogin();
	void ChangeProjectName();
	BOOL DeleteDir(char *pPath);
	string SetProductPath(string Path);
	BOOL GetFatherPath(char *pCrtPath, char *pFatherPath);


	//afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedProjectButton();
//	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCleanButton();
	CButton m_CleanLoginBtn;
//	afx_msg void OnBnClickedButton1();
//	CButton m_CheckBox;
	CEdit m_Product;
//	afx_msg void OnBnClickedChangeproductpathButton();
	CButton m_CheckBox;
};
