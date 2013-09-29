
// SetEnvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "SetEnvDlg.h"
#include "afxdialogex.h"
#include "Public.h"

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

// CSetEnvDlg dialog
CSetEnvDlg::CSetEnvDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetEnvDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
	m_ServerURL = "http://192.168.99.10:8081/svn/";
	m_Kernel.m_ConfigFlag = 0;
	m_FirstFlag = FALSE;
	m_AdvanceFlag = FALSE;
	m_Kernel.m_SevStatusFlag = TRUE;
}

void CSetEnvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WCPATH_EDIT, m_eWcPath);
	DDX_Control(pDX, IDC_CONFFILE_EDIT, m_eConfFile);
}

BEGIN_MESSAGE_MAP(CSetEnvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SETUSER_BUTTON, &CSetEnvDlg::OnBnSetUser)
	ON_BN_CLICKED(IDOK, &CSetEnvDlg::OnBnOK)
	ON_BN_CLICKED(IDC_SELCONF_BUTTON, &CSetEnvDlg::OnBnSelConf)
END_MESSAGE_MAP()

// CSetEnvDlg message handlers
BOOL CSetEnvDlg::OnInitDialog()
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
	
	if(__argc >= 3){
		m_eWcPath.SetWindowTextA(__argv[2]);
	}
	
	if(!m_Kernel.IsFirstUse()){
		m_FirstFlag = TRUE;
		if(!m_Kernel.m_ConfigFlag){
			GetDlgItem(IDC_SETUSER_BUTTON)->EnableWindow(FALSE);
		}
		GetDlgItem(IDOK)->EnableWindow(FALSE);
	}
	else{
		m_Kernel.GetDepURL();
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSetEnvDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CSetEnvDlg::OnPaint()
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
HCURSOR CSetEnvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI ThreadCallBack(LPVOID lpParamter)
{
	CSetEnvDlg * pSetEnvDlg = (CSetEnvDlg *)lpParamter;
	pSetEnvDlg->ExeSetEnv();
	pSetEnvDlg->EndMultiThread();

	return 0;
}

BOOL CSetEnvDlg::BeginMultiThread()
{
	HANDLE hThread = CreateThread(NULL, 0, ThreadCallBack, (LPVOID)this, 0, NULL);

	CloseHandle(hThread);

	m_ShowProgressDlg.DoModal();

	return TRUE;
}

BOOL CSetEnvDlg::EndMultiThread()
{
	while(1){
		Sleep(2);
		if(m_ShowProgressDlg.m_hWnd != NULL){
			m_ShowProgressDlg.PostMessage(WM_END_MESSAGE);
			break;
		}
	}

	return TRUE;
}

void CSetEnvDlg::OnBnSetUser()
{
	// TODO: Add your control notification handler code here

	if(m_FirstFlag){
		CString cConfigFile;
		m_eConfFile.GetWindowText(cConfigFile);
		if(cConfigFile == ""){
			AfxMessageBox("please select a configure file");
			return;
		}
	}

	m_SetUserDlg.m_pKernel = &m_Kernel;
	m_SetUserDlg.DoModal();
}

void CSetEnvDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here
	if(!m_Kernel.m_ConfigFlag || m_FirstFlag){
		CDialogEx::OnOK();
		return;
	}
	
	if(__argc < 3){
		CDialogEx::OnOK();
		return;
	}

	CString cConfigFile;
	m_eConfFile.GetWindowText(cConfigFile);
	if(cConfigFile == ""){
		AfxMessageBox("Please select configure file");
		return;
	}

	BeginMultiThread();

	m_ShowRetMsgDlg.m_pKernel = &m_Kernel;
	m_ShowRetMsgDlg.DoModal();

	CDialogEx::OnOK();
}

BOOL CSetEnvDlg::ExeSetEnv()
{
	CString cConfigFile;
	string sConfigFile = "";
	string sChildURL = "";

	char tRevision[255];
	char tChildURL[255];
	char tWcPath[255];
	char ttWcPath[255];

	memset(tRevision, 0, sizeof(tRevision));
	memset(tChildURL, 0, sizeof(tChildURL));
	memset(tWcPath, 0, sizeof(tWcPath));
	memset(ttWcPath, 0, sizeof(tWcPath));

	m_eConfFile.GetWindowText(cConfigFile);

	sConfigFile = CStringToString(cConfigFile);
	if(setConfigXML((char *)sConfigFile.c_str())){
		getCodeInfo(tChildURL, tRevision, ttWcPath);
	}
	else{
		m_Kernel.m_RetMsgs.push_back("Error: something wrong in configure files\r\n");
		return FALSE;
	}

	sChildURL = tChildURL;
	sprintf(tWcPath, "%s\\%s", __argv[2], ttWcPath);

	if(!strcmp(tRevision, "head") || !strcmp(tRevision, "HEAD")){
		m_Kernel.ExeSetEnv(tChildURL, tWcPath);
	}
	else{
		m_Kernel.ExeSetEnv(tChildURL, tWcPath, tRevision);
	}

	string sFlagFile = tWcPath;
	sFlagFile += "\\.svn\\";
	if(PathFileExists(sFlagFile.c_str())){
		sFlagFile += FLAG_FILE_NAME;
		if(string::npos == sChildURL.find("/tags")){
			FILE *tfp = fopen(sFlagFile.c_str(), "wb");
			if(NULL != tfp){
				fclose(tfp);
			}
		}
	}

	string tsConfigFile = tWcPath;
	tsConfigFile += "\\.svn\\";
	tsConfigFile += CONF_FILE_NAME;
	CopyFile(sConfigFile.c_str(), tsConfigFile.c_str(), FALSE);

	if(m_Kernel.m_RetMsgs.size() > 0 && string::npos == m_Kernel.m_RetMsgs.at(0).find("svn:")){
		m_Kernel.SetDepURL(tChildURL);
		m_Kernel.ChangeDep();
	}

	string sRelyRet;
	getRelyFiles(__argv[2], sRelyRet);
	m_Kernel.m_RetMsgs.push_back(sRelyRet);

	clean();

	return TRUE;
}

void CSetEnvDlg::OnBnSelConf()
{
	// TODO: Add your control notification handler code here

	CFileDialog OpenFileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY, "Configure file(*.xml)|*.xml||", NULL);
	OpenFileDlg.m_ofn.nFilterIndex = 1;
	OpenFileDlg.m_ofn.hwndOwner = m_hWnd;
	OpenFileDlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	OpenFileDlg.m_ofn.lpstrTitle = "Open Configue file";
	OpenFileDlg.m_ofn.nMaxFile = MAX_PATH;
	if(OpenFileDlg.DoModal() == IDOK){
		m_eConfFile.SetWindowText(OpenFileDlg.GetPathName());
	}
}
