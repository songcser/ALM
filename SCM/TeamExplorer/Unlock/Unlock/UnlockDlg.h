
// UnlockDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "TeamExplorer.h"
#include "afxcmn.h"

class CUnlockDlg : public CDialogEx
{
public:
	CUnlockDlg(CWnd* pParent = NULL);	// standard constructor

	enum { IDD = IDD_UNLOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	string CStringToString(CString SourceStr);
	BOOL InitialDirTree();

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void InitialComboRep();
	void InitialListLockFile(CString currentPath);

	CTeamExplorer m_TeamExplorer;
	CComboBox m_cReps;
	CImageList m_iImageList;
	CTreeCtrl m_tDirTree;
	CEdit m_eFilter;
	CListCtrl m_lLockFiles;

	char m_ConfigPath[255];
	char m_ServerUrl[255];
	string m_SelRepName;

	afx_msg void OnComboSelChange();
	afx_msg void OnNMClickDirTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnSelectAll();
	afx_msg void OnBnNotSelect();
	afx_msg void OnBnFilter();
};
