
// UpdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Update.h"
#include "UpdateDlg.h"
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

// CUpdateDlg dialog
CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	memset(m_EnvPath, 0, sizeof(m_EnvPath));
	memset(m_RcvPath, 0, sizeof(m_RcvPath));
	memset(m_RepURL, 0, sizeof(m_RepURL));
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UPDATE, m_RetMsg);
}

BEGIN_MESSAGE_MAP(CUpdateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

// CUpdateDlg message handlers
BOOL CUpdateDlg::OnInitDialog()
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
	
	if(__argc <= 1){
		m_RetStr = "have no arguments";
		m_RetMsg.SetWindowTextA(m_RetStr.c_str());
		return TRUE;
	}
	
	memcpy(m_RcvPath, __argv[1], strlen(__argv[1]));

	if(!FindRecordFile(m_RcvPath, m_EnvPath)){
		m_RetStr = "is not a working environment";
		m_RetMsg.SetWindowTextA(m_RetStr.c_str());
		return TRUE;
	}

	if(!GetRepURL(m_EnvPath, m_RepURL)){
		m_RetStr = "get URL failed";
		m_RetMsg.SetWindowTextA(m_RetStr.c_str());
		return TRUE;
	}

	for (int i=1;i<__argc;i++)
	{
		SmtUpdate(__argv[i]);
	}
	
	//m_RetStr += UpdateRely();

	m_RetStr += "update finished";

	m_RetMsg.SetWindowTextA(m_RetStr.c_str());

	::WinExec("TASKKILL /F /IM TSVNCache.exe", SW_HIDE);
	::WinExec("TSVNCache.exe", SW_HIDE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUpdateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUpdateDlg::OnPaint()
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
HCURSOR CUpdateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CUpdateDlg::SwitchURL(char *pRepURL, string &doURL)
{
	if(NULL == pRepURL){
		return FALSE;
	}

	string tmpURL = pRepURL;
	int tmpPos = tmpURL.find("branches");

	if(tmpURL.npos != tmpPos){
		doURL = pRepURL;
		doURL.replace(tmpPos, strlen("branches"), "products");
	}
	else{
		int truPos = tmpURL.find("trunk");
		if(tmpURL.npos != truPos){
			doURL = tmpURL.substr(0, truPos);
			doURL += "products/";
			doURL += tmpURL.substr(truPos, strlen(pRepURL));
		}
	}

	return TRUE;
}

BOOL CUpdateDlg::DealURL(string &doURL)
{
	int proPos = doURL.find("products");
	if(proPos != doURL.npos){
		int i = proPos+8;
		int count = 0;
		while(1){
			if(i >= doURL.length()){
				break;
			}
			if('/' == doURL[i]){
				count++;
			}
			if(count >= 2){
				break;
			}
			i++;
		}
		doURL = doURL.substr(0, i);
	}

	return TRUE;
}

string CUpdateDlg::UpdateRely()
{
	string strRet;
	string ExportCmd;
	string doURL;
	string WcPath(m_EnvPath);
	string tmpURL(m_RepURL);

	int tmpPos = tmpURL.find("products");
	if(tmpPos == tmpURL.npos){
		SwitchURL(m_RepURL, doURL);
		DealURL(doURL);

		WcPath += "\\";
		WcPath += "products.rely";

		ExportCmd = "svn export --force \"";
		ExportCmd += doURL;
		ExportCmd += "\" \"";
		ExportCmd += WcPath;
		ExportCmd += "\"";

		strRet += ExeCmd((char *)ExportCmd.c_str());
	}

	return strRet;
}

BOOL CUpdateDlg::GetRepURL(char *pEnvPath, char *pRepURL)
{
	if(NULL == pEnvPath || NULL == pRepURL){
		return FALSE;
	}

	char FilePath[255];
	memset(FilePath, 0, sizeof(FilePath));
	sprintf(FilePath, "%s\\%s", pEnvPath, "SmtRec.dat");

	FILE *fp = fopen(FilePath, "r");
	if(NULL == fp){
		return FALSE;
	}

	char RepURL[255];
	memset(RepURL, 0, sizeof(RepURL));
	fread(RepURL, 1, sizeof(RepURL), fp);
	memcpy(pRepURL, RepURL, strlen(RepURL));

	fclose(fp);
	return TRUE;
}

BOOL CUpdateDlg::GetFatherPath(char *pCrtPath, char *pFatherPath)
{
	if(NULL == pCrtPath || NULL == pFatherPath){
		return FALSE;
	}

	int PathLen = strlen(pCrtPath);
	if(PathLen <= 1){
		return FALSE;
	}

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

BOOL CUpdateDlg::FindRecordFile(char *pCrtPath, char *pRetPath)
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

string CUpdateDlg::ExeCmd(char *pszCmd)
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

string CUpdateDlg::SmtUpdate(char* pPath)
{
	if (NULL == pPath)
	{
		m_RetStr = "Error, Selected File error";
		return m_RetStr;
	}

	char RelativePath[255];
	memset(RelativePath,0,sizeof(RelativePath));
	char RelativeURL[255];
	memset(RelativeURL,0,sizeof(RelativeURL));
	if (!GetRelativePath(pPath,RelativePath))
	{
		m_RetStr = "Error, GetRelativePath error";
		return m_RetStr;
	}
	if (!GetRelativeURL(pPath,RelativeURL))
	{
		m_RetStr = "Error, GetRelativeURL error";
		return m_RetStr;
	}
	char AbsolateURL[255];
	memset(AbsolateURL,0,sizeof(AbsolateURL));
	sprintf(AbsolateURL,"%s%s",m_RepURL,RelativeURL);

	if (FILE_ATTRIBUTE_DIRECTORY == GetFileAttributes(pPath))
	{
		char tmpName[] = ".tmpName";
		if (!GetExistFile(RelativePath,tmpName,false))
		{
			m_RetStr = "Error, GetExistFile error";
			return m_RetStr;
		}
		
		char ExportCmd[255];
		memset(ExportCmd,0,sizeof(ExportCmd));
		sprintf(ExportCmd,"svn export --force \"%s\" \"%s\"", AbsolateURL, pPath);
		m_RetStr += ExeCmd(ExportCmd);

		if (!GetExistFile(RelativePath,tmpName,true))
		{
			m_RetStr = "Error, GetExistFile error";
			return m_RetStr;
		}
	}
	else
	{
		if (!IsExist(RelativePath))
		{
			char ExportCmd[255];
			memset(ExportCmd,0,sizeof(ExportCmd));
			sprintf(ExportCmd,"svn export --force \"%s\" \"%s\"",AbsolateURL,pPath);
			m_RetStr += ExeCmd(ExportCmd);
		}
	}
	return m_RetStr;
}

BOOL CUpdateDlg::IsExist(char *pPath)
{
	char SmtFile[255];
	memset(SmtFile,0,sizeof(SmtFile));
	sprintf(SmtFile,"%s\\SmtRec.dat",m_EnvPath);

	FILE *file;
	file = fopen(SmtFile,"r");
	
	char TmpPath[255];
	memset(TmpPath,0,sizeof(TmpPath));
	fseek(file,255,SEEK_SET);
	while(fread(TmpPath,1,sizeof(TmpPath),file)==sizeof(TmpPath))
	{
		if (strcmp(pPath,TmpPath)==0)
		{
			fclose(file);
			return TRUE;
		}
	}

	fclose(file);

	return FALSE;
}

BOOL CUpdateDlg::RenameFileBack(char *files,char *tmpName)
{
	if (NULL == files||NULL == tmpName)
	{
		return FALSE;
	}
	char OldName[255];
	char NewName[255];
	char fileName[255];
	memset(OldName,0,sizeof(OldName));
	memset(NewName,0,sizeof(NewName));

	sprintf(OldName,"%s%s%s",m_EnvPath,files,tmpName);
	sprintf(NewName,"%s%s",m_EnvPath,files);
	if (PathFileExists(OldName)&&PathFileExists(NewName)&&(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(NewName)))
	{
		while(remove(NewName));
		while(rename(OldName,NewName));	
	}
	
	return TRUE;
}

BOOL CUpdateDlg::RenameFile(char *files,char *tmpName)
{
	if (NULL == files||NULL == tmpName)
	{
		return FALSE;
	}
	char OldName[255];
	char NewName[255];
	char fileName[255];
	memset(OldName,0,sizeof(OldName));
	memset(NewName,0,sizeof(NewName));
	memset(fileName,0,sizeof(fileName));

	sprintf(OldName,"%s%s",m_EnvPath,files);
	sprintf(NewName,"%s%s%s",m_EnvPath,files,tmpName);
	if (PathFileExists(OldName)&&(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(OldName)))
	{
		while(rename(OldName,NewName));
	}

	return TRUE;
}

BOOL CUpdateDlg::GetExistFile(char *pRelativePath,char *tmpName,bool isRenameBack)
{
	if (NULL == pRelativePath||NULL == tmpName)
	{
		return FALSE;
	}
	char filePath[255];
	memset(filePath,0,sizeof(filePath));
	sprintf(filePath,"%s\\SmtRec.dat",m_EnvPath);
	
	char ExistFile[255];
	memset(ExistFile,0,sizeof(ExistFile));

	FILE *file;
	if ((file = fopen(filePath,"r"))==NULL)
	{
		return FALSE;
	}
	int count = 0;
	char tempPath[255];
	memset(tempPath,0,sizeof(tempPath));
	fseek(file,255,SEEK_SET);
	while(fread(tempPath,1,sizeof(tempPath),file)==sizeof(tempPath))
	{
		int num = strlen(pRelativePath);
		int i;
		for (i=0;i<num;i++)
		{
			if (pRelativePath[i]!=tempPath[i])
			{
				break;
			}
			else
			{
				ExistFile[count] = tempPath[i];
				count++;
			}
		}
		if (i==num&&tempPath[i]=='\\')
		{
			while('\0' != tempPath[i])
			{
				ExistFile[count] = tempPath[i];
				count++;
				i++;
			}

			if (!isRenameBack)
			{
				RenameFile(ExistFile,tmpName);
			}
			else
			{
				RenameFileBack(ExistFile,tmpName);
			}
		}
		
		memset(ExistFile,0,sizeof(ExistFile));
		count = 0;
	}

	fclose(file);

	return TRUE;
}

BOOL CUpdateDlg::GetRelativePath(char *filePath, char *RelativePath)
{
	if(NULL == filePath || NULL == RelativePath){
		return FALSE;
	}
	int count =strlen(filePath) - strlen(m_EnvPath);
	
	int num = strlen(m_EnvPath);
	for (int i =0;i<count;i++)
	{
		RelativePath[i] = filePath[num];
		num++;
	}
	return TRUE;
}

BOOL CUpdateDlg::GetRelativeURL(char *filePath,char *RelativeURL)
{
	if(NULL == filePath || NULL == RelativeURL){
		return FALSE;
	}
	int count =strlen(filePath) - strlen(m_EnvPath);
	
	int num = strlen(m_EnvPath);
	for (int i =0;i<count;i++)
	{
		if ('\\'==filePath[num])
		{
			RelativeURL[i] = '/';
			num++;
		}
		else
		{
			RelativeURL[i] = filePath[num];
			num++;
		}
	}
	return TRUE;
}