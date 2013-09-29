
// CheckoutDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CheckoutMsgDlg.h"

// CCheckoutDlg dialog
class CCheckoutDlg : public CDialogEx
{
// Construction
public:
	CCheckoutDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CHECKOUT_DIALOG };

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
	CEdit m_CheckItem;
	CCheckoutMsgDlg m_CheckoutMsgDlg;
	char m_EnvPath[255];
	char m_RepURL[255];
	char m_FatherPath[255];
	string CStringToString(CString SourceStr);
	BOOL GetFatherPath(char *pCrtPath, char *pFatherPath);
	BOOL DeleteDir(char *pPath);
	void DeleteFile (string path);
	BOOL FindRecordFile(char *pCrtPath, char *pRetPath);
	string ExeCmd(char *pszCmd);
	bool IsFileLocked(char *pRepURL, string &LockUser);
	string DealLock(LPCSTR Path, FILE *fp);
	BOOL IsInDatFile(char *pPath);
	BOOL GetRepURL(char *pEnvPath, char *pRepURL);
	BOOL PathToURL(char *pDest, char *pSrc);
	BOOL URLToPath(char *pDest, char *pSrc);
	BOOL IsChildDir(char *pFatherPath, char *pCrtPath);
	BOOL DealFatherPath(char *pPath, FILE *fp);
	string EasyCheckout();
	string ComplexCheckout();
	string TopCheckout();
	string UpdateRely();
	BOOL SwitchURL(char *pRepURL, string &doURL);
	BOOL DealURL(string &doURL);
	//BOOL GetPathEnd(char *pPath, char *pPathEnd);
	afx_msg void OnBnCheckout();
};
