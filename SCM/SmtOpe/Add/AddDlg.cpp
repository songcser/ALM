
// AddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Add.h"
#include "AddDlg.h"
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

// CAddDlg dialog
CAddDlg::CAddDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDITEM, m_AddItem);
}

BEGIN_MESSAGE_MAP(CAddDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAddDlg::OnBnAdd)
END_MESSAGE_MAP()


// CAddDlg message handlers

BOOL CAddDlg::OnInitDialog()
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

	string sAddItem;

	if(__argc <= 1){
		m_AddItem.SetWindowTextA("nothing need to add");
		return TRUE;
	}

	for(int i = 1; i< __argc; i++){
		sAddItem += __argv[i];
		sAddItem += "\r\n";
	}
	m_AddItem.SetWindowTextA(sAddItem.c_str());


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAddDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAddDlg::OnPaint()
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
HCURSOR CAddDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

string CAddDlg::CStringToString(CString SourceStr)
{
	CStringA TempSourceStr(SourceStr.GetBuffer(0));
	SourceStr.ReleaseBuffer();

	string Name(TempSourceStr.GetBuffer(0));
	TempSourceStr.ReleaseBuffer();

	return Name;
}

string CAddDlg::ExeCmd(char *pszCmd)
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

void CAddDlg::OnBnAdd()
{
	// TODO: Add your control notification handler code here
	if(__argc <= 1){
		CDialogEx::OnOK();
		return;
	}

	char RetPath[255];
	memset(RetPath,0,sizeof(RetPath));

	if (!FindRecordFile(__argv[1],RetPath))
	{
		CDialogEx::OnOK();
		return;
	}

	FILE *file;
	file = fopen(RetPath,"r");
	if (file == NULL)
	{
		CDialogEx::OnOK();
		return;
	}

	char URLpath[255];
	if(fread(URLpath,1,255,file)!=255)
	{
		CDialogEx::OnOK();
		return;
	}

	fclose(file);
	string sAddCmd = "svn add ";

	for(int i = 1; i< __argc; i++)
	{
		char RelativePath[255];
		memset(RelativePath,0,sizeof(RelativePath));
		if (!GetRelativePath(__argv[i],RelativePath))
		{
			CDialogEx::OnOK();
			return;
		}
		if (IsExistFile(URLpath,RelativePath))
		{
			AfxMessageBox("ERROR, The File is Exist");
			return;
		}
		sAddCmd += "\"";
		sAddCmd += __argv[i];
		sAddCmd += "\"";
		if(i < __argc-1){
			sAddCmd += " ";
		}
	}

	ExeCmd((char *)sAddCmd.c_str());

	::WinExec("TASKKILL /F /IM TSVNCache.exe", SW_HIDE);
	::WinExec("TSVNCache.exe", SW_HIDE);

	CDialogEx::OnOK();
}

BOOL CAddDlg::FindRecordFile(char *pCrtPath, char *pRetPath)
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
			memcpy(pRetPath, tempPath, sizeof(tempPath));
			break;
		}
	}

	return TRUE;
}

BOOL CAddDlg::GetRelativePath(char *filePath, char *RelativePath)
{
	if(NULL == filePath || NULL == RelativePath){
		return FALSE;
	}
	int count =0;
	char CrtPath[255], tempPath[255];
	memset(CrtPath, 0, sizeof(CrtPath));
	memcpy(CrtPath, filePath, strlen(filePath));

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
			count = strlen(filePath) - strlen(CrtPath);
			//memcpy(pRetPath, CrtPath, sizeof(CrtPath));
			break;
		}
	}
	int num = strlen(CrtPath);
	for (int i =0;i<count;i++)
	{
		if ('\\'==filePath[num])
		{
			RelativePath[i] = '/';
			num++;
		}
		else
		{
			RelativePath[i] = filePath[num];
			num++;
		}
		
	}
	return TRUE;
}

BOOL CAddDlg::GetFatherPath(char *pCrtPath, char *pFatherPath)
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

BOOL CAddDlg::IsExistFile(char *URLPath, char *RelativePath)
{
	if (NULL == URLPath||NULL == RelativePath)
	{
		return FALSE;
	}
	char AbsolutePath[255];
	memset(AbsolutePath,0,sizeof(AbsolutePath));
	sprintf(AbsolutePath,"%s%s",URLPath,RelativePath);

	string RetStr;
	char InfoCmd[255];
	memset(InfoCmd,0,sizeof(InfoCmd));
	sprintf(InfoCmd,"svn info \"%s\"",AbsolutePath);
	RetStr = ExeCmd(InfoCmd);

	if (RetStr.find("Path:")==0)
	{
		return TRUE;
	}

	return FALSE;
}