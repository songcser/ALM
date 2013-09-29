
// SmATL_RevertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SmATL_Revert.h"
#include "SmATL_RevertDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSmATL_RevertDlg dialog




CSmATL_RevertDlg::CSmATL_RevertDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmATL_RevertDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmATL_RevertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_RetEdit);
}

BEGIN_MESSAGE_MAP(CSmATL_RevertDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSmATL_RevertDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSmATL_RevertDlg message handlers

BOOL CSmATL_RevertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	string ParmStr;
	string EnterStr("\r\n");

	for (int i=1;i<__argc;i++)
	{
		string sargv(__argv[i]);
		ParmStr += sargv+EnterStr;
	}
	m_RetEdit.SetWindowTextA(ParmStr.c_str());

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSmATL_RevertDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSmATL_RevertDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSmATL_RevertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSmATL_RevertDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	if (__argc<=1)
	{
		AfxMessageBox("No File to Revert");
		return;
	}
	string retstr;
	char RevetCmd[255];
	char FilePath[255];
	memset(FilePath,0,sizeof(FilePath));
	memset(RevetCmd,0,sizeof(RevetCmd));

	for (int i=1;i<__argc;i++)
	{
		memset(FilePath,0,sizeof(FilePath));
		memset(RevetCmd,0,sizeof(RevetCmd));

		strcpy(FilePath,__argv[i]);

		sprintf(RevetCmd,"svn revert --depth infinity \"%s\"",FilePath);
		retstr += ExeCmd(RevetCmd);
	}

	//m_RetEdit.SetWindowTextA(retstr.c_str());
	retstr += "revert finished";
	m_ShowLog.SetMessage((char *)retstr.c_str());
	if (m_ShowLog.DoModal() == IDOK)
	{
		CDialogEx::OnOK();
	}
	//AfxMessageBox(retstr.c_str());

	::WinExec("TASKKILL /F /IM TSVNCache.exe", SW_HIDE);
	::WinExec("TSVNCache.exe", SW_HIDE);

	CDialogEx::OnOK();
}

string CSmATL_RevertDlg::ExeCmd(char *pszCmd)
{
	if(NULL == pszCmd){
		return "";
	}

	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	HANDLE hRead, hWrite;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return "";
	}

	STARTUPINFO sii = {sizeof(STARTUPINFO)};
	GetStartupInfo(&sii);
	sii.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	sii.wShowWindow = SW_HIDE;
	sii.hStdError = hWrite;
	sii.hStdOutput = hWrite;

	PROCESS_INFORMATION pii;
	if (!CreateProcess(NULL, pszCmd, NULL, NULL, TRUE, NULL, NULL, NULL, &sii, &pii))
	{
		return "";
	}

	CloseHandle(hWrite);

	string strRet;
	char buff[1024] = {0};
	DWORD dwRead = 0;
	while (ReadFile(hRead, buff, 1024, &dwRead, NULL))
	{
		strRet.append(buff, dwRead);
	}
	CloseHandle(hRead);

	CloseHandle(pii.hProcess);
	CloseHandle(pii.hThread);
	//	CloseHandle(sii.hStdError);
	//	CloseHandle(sii.hStdInput);
	//	CloseHandle(sii.hStdOutput);

	return strRet;
}