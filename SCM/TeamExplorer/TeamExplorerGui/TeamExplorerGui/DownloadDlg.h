#pragma once
#include "afxwin.h"
#include "ShowProgressDlg.h"
#include "DownloadMsgDlg.h"
#include "PDMBuilder.h"
#pragma comment(lib, "PDMBuilder.lib")

// CDownloadDlg dialog

class CDownloadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDownloadDlg)

public:
	CDownloadDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDownloadDlg();

// Dialog Data
	enum { IDD = IDD_DOWNLOAD_DIALOG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	string m_sRelyRet;
	CDownloadMsgDlg m_DownloadMsgDlg;

	CEdit m_eRelyPath;
	CEdit m_eConfigFilePath;
	CShowProgressDlg m_ShowProgressDlg;

	BOOL BeginMultiThread();
	BOOL EndMultiThread();
	BOOL UpdateRelyFiles();

	BOOL BeginDownload();

	afx_msg void OnBnSelConfFile();
	afx_msg void OnBnOK();
};
