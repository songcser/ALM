
// CancelDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CancelMsgDlg.h"
#include "sqlite3.h"
#pragma comment(lib, "sqlite3.lib")

// CCancelDlg dialog
class CCancelDlg : public CDialogEx
{
// Construction
public:
	CCancelDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CANCEL_DIALOG };

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
	CEdit m_CancelItem;
	void CharToUTF(const char* strIn, char* strOut, int sourceCodepage, int targetCodepage);
	void DealResidual(char *pEnvPath);
	string CStringToString(CString SourceStr);
	BOOL GetFatherPath(char *pCrtPath, char *pFatherPath);
	BOOL FindRecordFile(char *pCrtPath, char *pRetPath);
	string ExeCmd(char *pszCmd);
	string ComplexCancel();
	string SmtUnlock(char *pPath);
	BOOL DeleteDir(char *pPath);
	BOOL SmtDealRec(char *pPath);
	BOOL GetRepURL(char *pEnvPath, char *pRepURL);
	BOOL PathToURL(char *pDest, char *pSrc);
	BOOL DealDb(LPCSTR Path);
	BOOL SmtCancel(char *pEnvPath, char *pFatherPath);
	CCancelMsgDlg m_MsgDlg;
	CEdit m_LogMsg;
	char m_EnvPath[255];
	char m_RepURL[255];
	char m_FatherPath[255];
	sqlite3 *m_pDb;
	afx_msg void OnBnOK();
};
