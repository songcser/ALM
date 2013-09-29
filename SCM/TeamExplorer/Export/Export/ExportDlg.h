
// ExportDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TeamExplorer.h"
#include "ProgressDlg.h"
#include "ShowMessageDlg.h"

// CExportDlg dialog
class CExportDlg : public CDialogEx
{
// Construction
public:
	CExportDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EXPORT_DIALOG };

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
	CComboBox m_cReps;
	CTreeCtrl m_tDirTree;
	CEdit m_eSourcePath;
	CEdit m_eDestPath;

	char m_ConfigPath[255];
	char m_ServerUrl[255];
	string m_SelRepName;
	string m_RetMessage;
	CImageList m_iImageList;
	CTeamExplorer m_TeamExplorer;

	CShowMessageDlg m_ShowMessageDlg;
	CProgressDlg m_ProgressDlg;

	string CStringToString(CString SourceStr);
	BOOL InitialDirTree();
	void InitialComboRep();
	void Export();

	BOOL BeginMultiThread();
	BOOL EndMultiThread();

	afx_msg void OnComboSelChange();
	afx_msg void OnNMClickDirTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnSelLocalPath();
	afx_msg void OnBnExport();
};
