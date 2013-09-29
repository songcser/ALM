
// CommitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Commit.h"
#include "CommitDlg.h"
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

// CCommitDlg dialog

CCommitDlg::CCommitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommitDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCommitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMMITITEM, m_CommitItem);
	DDX_Control(pDX, IDC_LOGMSG, m_LogMsg);
}

BEGIN_MESSAGE_MAP(CCommitDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCommitDlg::OnBnCommit)
END_MESSAGE_MAP()

// CCommitDlg message handlers

BOOL CCommitDlg::OnInitDialog()
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

	string sComItem;

	if(__argc <= 1){
		m_CommitItem.SetWindowTextA("nothing need to commit");
		return TRUE;
	}

	for(int i = 1; i< __argc; i++){
		sComItem += __argv[i];
		sComItem += "\r\n";
	}
	m_CommitItem.SetWindowTextA(sComItem.c_str());

	FindRecordFile(__argv[1], m_EnvPath);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCommitDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCommitDlg::OnPaint()
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
HCURSOR CCommitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

string CCommitDlg::CStringToString(CString SourceStr)
{
	CStringA TempSourceStr(SourceStr.GetBuffer(0));
	SourceStr.ReleaseBuffer();

	string Name(TempSourceStr.GetBuffer(0));
	TempSourceStr.ReleaseBuffer();

	return Name;
}

string CCommitDlg::ExeCmd(char *pszCmd)
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

	return strRet;
}

BOOL CCommitDlg::GetFatherPath(char *pCrtPath, char *pFatherPath)
{
	if(NULL == pCrtPath || NULL == pFatherPath){
		return FALSE;
	}

	int PathLen = strlen(pCrtPath);
	PathLen--;

	while(1){
		if('\\' == *(pCrtPath + PathLen) || '/' == *(pCrtPath + PathLen)){
			break;
		}
		PathLen--;
		if(PathLen <= 0){
			break;
		}
	}

	if(PathLen > 0){
		memcpy(pFatherPath, pCrtPath, PathLen);
		return TRUE;
	}
	else{
		return FALSE;
	}
}

BOOL CCommitDlg::FindRecordFile(char *pCrtPath, char *pRetPath)
{
	if(NULL == pCrtPath || NULL == pRetPath){
		return FALSE;
	}

	char CrtPath[255], tempPath[255];
	memset(CrtPath, 0, sizeof(CrtPath));
	memcpy(CrtPath, pCrtPath, strlen(pCrtPath));

	while(1){
		memset(tempPath, 0, sizeof(tempPath));
		sprintf(tempPath, "%s\\SmtRec.dat", CrtPath);
		if(!PathFileExists(tempPath)){
			char FatherPath[255];
			memset(FatherPath, 0, sizeof(FatherPath));
			if(!GetFatherPath(CrtPath, FatherPath)){
				return FALSE;
			}
			memset(CrtPath, 0, sizeof(CrtPath));
			memcpy(CrtPath, FatherPath, sizeof(FatherPath));
		}
		else{
			memcpy(pRetPath, CrtPath, sizeof(CrtPath));
			break;
		}
	}

	return TRUE;
}

BOOL CCommitDlg::DealAdd(string StatusStr)
{
	char FilePath[255];
	memset(FilePath, 0, sizeof(FilePath));
	sprintf(FilePath, "%s\\SmtRec.dat", m_EnvPath);

	FILE *fp = fopen(FilePath, "a+");
	if(NULL == fp){
		return FALSE;
	}
	fseek(fp, 0, SEEK_END);

	int k = 0;

	char AddPath[255];
	char TmpPath[255];

	while('\0' != StatusStr[k]){
		if('A' == StatusStr[k]){
			if((k+7) < StatusStr.length() && ' ' == StatusStr[k+1] && ' ' == StatusStr[k+2] && ' ' == StatusStr[k+3] && ' ' == StatusStr[k+4] && ' ' == StatusStr[k+5] && ' ' == StatusStr[k+6] && ' ' == StatusStr[k+7]){
				k += 8;
				int i = 0;
				memset(AddPath, 0, sizeof(AddPath));
				while('\r' != StatusStr[k]){
					AddPath[i] = StatusStr[k];
					i++;
					k++;
				}
				memset(TmpPath, 0, sizeof(TmpPath));
				memcpy(TmpPath, AddPath+strlen(m_EnvPath), strlen(AddPath) - strlen(m_EnvPath));
				fwrite(TmpPath, 1, sizeof(TmpPath), fp);
				fflush(fp);
				if(PathFileExists(AddPath)){
					if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(AddPath)){
						char LockCmd[255];
						memset(LockCmd, 0, sizeof(LockCmd));
						sprintf(LockCmd, "svn lock \"%s\"", AddPath);
						ExeCmd(LockCmd);
					}
				}
				k++;
			}
		}
		k++;
	}

	fclose(fp);

	return TRUE;
}

void CCommitDlg::OnBnCommit()
{
	// TODO: Add your control notification handler code here
	
	if(__argc <= 1){
		CDialogEx::OnOK();
		return ;
	}

	string sLogMsg, strRet;
	CString cLogMsg;

	m_LogMsg.GetWindowTextA(cLogMsg);
	sLogMsg = CStringToString(cLogMsg);
	if(strlen(sLogMsg.c_str()) <= 0){
		AfxMessageBox(CString("have no log message"));
		return ;
	}

	string StatusStr;
	string StatusCmd = "svn status ";

	for(int i = 1; i < __argc; i++){
		StatusCmd += "\"";
		StatusCmd += __argv[i];
		StatusCmd += "\"";
		if(i < __argc-1){
			StatusCmd += " ";
		}
	}
	StatusStr += ExeCmd((char *)StatusCmd.c_str());

	string CommitCmd = "svn commit --no-unlock -m \"";
	CommitCmd += sLogMsg;
	CommitCmd += "\" ";

	for(int i = 1; i < __argc; i++){
		CommitCmd += "\"";
		CommitCmd += __argv[i];
		CommitCmd += "\"";
		if(i < __argc-1){
			CommitCmd += " ";
		}
	}

	strRet = ExeCmd((char *)CommitCmd.c_str());
	if(strlen(strRet.c_str()) <= 0){
		strRet += " nothing need to commit\r\n";
	}

	if(StatusStr.npos != StatusStr.find("A       ")){
		DealAdd(StatusStr);
	}

	m_CommitMsgDlg.m_StrMsg = strRet;
	m_CommitMsgDlg.DoModal();

	::WinExec("TASKKILL /F /IM TSVNCache.exe", SW_HIDE);
	::WinExec("TSVNCache.exe", SW_HIDE);

	CDialogEx::OnOK();
}
