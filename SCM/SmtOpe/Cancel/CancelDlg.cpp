
// CancelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Cancel.h"
#include "CancelDlg.h"
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

// CCancelDlg dialog
CCancelDlg::CCancelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCancelDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_EnvPath, 0, sizeof(m_EnvPath));
	memset(m_RepURL, 0, sizeof(m_RepURL));
	memset(m_FatherPath, 0, sizeof(m_FatherPath));
}

void CCancelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CANCELITEM, m_CancelItem);
}

BEGIN_MESSAGE_MAP(CCancelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCancelDlg::OnBnOK)
END_MESSAGE_MAP()

// CCancelDlg message handlers
BOOL CCancelDlg::OnInitDialog()
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

	string sCheckinItem;

	if(__argc <= 1){
		m_CancelItem.SetWindowTextA("nothing need to cancel");
		return TRUE;
	}

	for(int i = 1; i< __argc; i++){
		sCheckinItem += __argv[i];
		sCheckinItem += "\r\n";
	}
	m_CancelItem.SetWindowTextA(sCheckinItem.c_str());

	FindRecordFile(__argv[1], m_EnvPath);
	GetRepURL(m_EnvPath, m_RepURL);
	GetFatherPath(__argv[1], m_FatherPath);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCancelDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCancelDlg::OnPaint()
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
HCURSOR CCancelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCancelDlg::CharToUTF(const char* strIn, char* strOut, int sourceCodepage, int targetCodepage)
{
	int len=lstrlen(strIn);
	int unicodeLen=MultiByteToWideChar(sourceCodepage,0,strIn,-1,NULL,0);
	wchar_t* pUnicode;
	pUnicode=new wchar_t[unicodeLen+1];
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));
	MultiByteToWideChar(sourceCodepage,0,strIn,-1,(LPWSTR)pUnicode,unicodeLen);
	BYTE * pTargetData = NULL;
	int targetLen=WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,0,NULL,NULL);
	pTargetData=new BYTE[targetLen+1];
	memset(pTargetData,0,targetLen+1);
	WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,targetLen,NULL,NULL);
	lstrcpy(strOut,(char*)pTargetData);
	delete pUnicode;
	delete pTargetData;
}

string CCancelDlg::CStringToString(CString SourceStr)
{
	CStringA TempSourceStr(SourceStr.GetBuffer(0));
	SourceStr.ReleaseBuffer();

	string Name(TempSourceStr.GetBuffer(0));
	TempSourceStr.ReleaseBuffer();

	return Name;
}

BOOL CCancelDlg::GetRepURL(char *pEnvPath, char *pRepURL)
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

BOOL CCancelDlg::PathToURL(char *pDest, char *pSrc)
{
	if(NULL == pDest || NULL == pSrc){
		return FALSE;
	}

	int len = strlen(pSrc);
	int i = 0;
	for(i = 0; i < len; i++){
		if('\\' == *pSrc){
			*pDest = '/';
		}
		else{
			*pDest = *pSrc;
		}
		pDest++;
		pSrc++;
	}

	return TRUE;
}

BOOL CCancelDlg::GetFatherPath(char *pCrtPath, char *pFatherPath)
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

BOOL CCancelDlg::FindRecordFile(char *pCrtPath, char *pRetPath)
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

BOOL CCancelDlg::DealDb(LPCSTR Path)
{
	if(NULL == Path){
		return FALSE;
	}

	char *errmsg;
	char TempArgv[255];
	char TempBuff[255];
	memset(TempArgv, 0, sizeof(TempArgv));
	memcpy(TempArgv, Path, strlen(Path));
	memset(TempBuff, 0, sizeof(TempBuff));
	PathToURL(TempBuff, TempArgv+strlen(m_EnvPath)+1);
	char Sql[255];
	memset(Sql, 0, sizeof(Sql));
	sprintf(Sql,"delete from NODES where local_relpath=\"%s\"", TempBuff);
	sqlite3_exec(m_pDb, Sql, NULL, NULL, &errmsg);

	WIN32_FIND_DATA FindData;  
	HANDLE hError;  
	int FileCount = 0;  
	char FilePathName[255];
	char FullPathName[255];
	string strRet;

	strcpy(FilePathName, Path);  
	strcat(FilePathName, "\\*.*");  
	hError = FindFirstFile(FilePathName, &FindData);  

	if (hError == INVALID_HANDLE_VALUE)  
	{
		FindClose(hError);
		return FALSE;  
	}  

	while(::FindNextFile(hError, &FindData))  
	{  
		if (strcmp(FindData.cFileName, ".") == 0   || strcmp(FindData.cFileName, "..") == 0 )  
		{  
			continue;  
		}  

		memset(FullPathName, 0, sizeof(FullPathName));
		wsprintf(FullPathName, "%s\\%s", Path,FindData.cFileName);  
		FileCount++;  

		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){  
			DealDb(FullPathName);
		}
		else{
			memset(TempBuff, 0, sizeof(TempBuff));
			PathToURL(TempBuff, FullPathName+strlen(m_EnvPath)+1);
			memset(Sql, 0, sizeof(Sql));
			sprintf(Sql,"delete from NODES where local_relpath=\"%s\"", TempBuff);
			sqlite3_exec(m_pDb, Sql, NULL, NULL, &errmsg);
		}
	}

	sqlite3_free(errmsg);
	FindClose(hError);

	return FALSE;
}  

BOOL CCancelDlg::SmtCancel(char *pEnvPath, char *pFatherPath)
{
	if(NULL == pEnvPath || NULL == pFatherPath){
		return FALSE;
	}

	char DbPath[255];
	char TmpPath[255];
	memset(TmpPath, 0, sizeof(TmpPath));
	memset(DbPath, 0, sizeof(DbPath));
	sprintf(TmpPath, "%s\\.svn\\wc.db", m_EnvPath);
	CharToUTF(TmpPath, DbPath, CP_ACP, CP_UTF8); 

	int nResult = sqlite3_open(DbPath, &m_pDb);
	if (nResult != SQLITE_OK)
	{
		return FALSE;
	}

	for(int i = 1; i < __argc; i++){
		DealDb(__argv[i]);
	}

	sqlite3_close(m_pDb);

	return TRUE;
}

string CCancelDlg::ExeCmd(char *pszCmd)
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

string CCancelDlg::SmtUnlock(char *pPath)
{
	if(NULL == pPath){
		return "unlock failed";
	}

	string strRet;
	char UnlockCmd[255];

	if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(pPath)){
		memset(UnlockCmd, 0, sizeof(UnlockCmd));
		sprintf(UnlockCmd, "svn unlock \"%s\"", pPath);
		strRet += ExeCmd(UnlockCmd);
		return strRet;
	}

	char FilePath[255];
	memset(FilePath, 0, sizeof(FilePath));
	sprintf(FilePath, "%s\\SmtRec.dat", m_EnvPath);

	FILE *fp = fopen(FilePath, "r");
	if(NULL == fp){
		return "record file open failed";
	}

	fseek(fp, 0, SEEK_END);
	long fileLength = ftell(fp);
	int CycleTimes = (int)fileLength/255 - 1;
	fseek(fp, 255, SEEK_SET);

	char RecPath[255];
	char TempPath[255];
	int PathLen = strlen(pPath);

	for(int i = 0; i < CycleTimes; i++){
		memset(RecPath, 0, sizeof(RecPath));
		memset(TempPath, 0, sizeof(TempPath));
		fread(TempPath, 1, sizeof(TempPath), fp);
		sprintf(RecPath, "%s%s", m_EnvPath, TempPath);
		if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(RecPath)){
			if(PathLen < strlen(RecPath)){
				if(!memcmp(RecPath, pPath, PathLen)){
					if('\\' != RecPath[PathLen]){
						continue;
					}
					memset(UnlockCmd, 0, sizeof(UnlockCmd));
					sprintf(UnlockCmd, "svn unlock \"%s\"", RecPath);
					strRet += ExeCmd(UnlockCmd);
				}
			}
		}
	}

	fclose(fp);

	return strRet;
}

BOOL CCancelDlg::SmtDealRec(char *pPath)
{
	if(NULL == pPath){
		return FALSE;
	}

	char FilePath[255];
	char TempPath[255];
	memset(FilePath, 0, sizeof(FilePath));
	memset(TempPath, 0, sizeof(TempPath));

	sprintf(FilePath, "%s\\SmtRec.dat", m_EnvPath);
	sprintf(TempPath, "%s\\SmtRec_temp.dat", m_EnvPath);

	FILE *fp, *tfp;
	fp = fopen(FilePath, "r");
	if(NULL == fp){
		return FALSE;
	}
	tfp = fopen(TempPath, "w");
	if(NULL == tfp){
		fclose(fp);
		return FALSE;
	}

	fseek(fp, 0, SEEK_END);
	long fileLength = ftell(fp);
	int CycleTimes = (int)fileLength/255;
	fseek(fp, 0, SEEK_SET);

	char RecPath[255];
	char TempBuff[255];
	int PathLen = strlen(pPath);

	for(int i = 0; i < CycleTimes; i++){
		memset(RecPath, 0, sizeof(RecPath));
		memset(TempBuff, 0, sizeof(TempBuff));
		fread(TempBuff, 1, sizeof(TempBuff), fp);
		sprintf(RecPath, "%s%s", m_EnvPath, TempBuff);
		if(PathLen == strlen(RecPath)){
			if(!memcmp(RecPath, pPath, PathLen)){
				continue;
			}
		}
		if(PathLen < strlen(RecPath)){
			if(!memcmp(RecPath, pPath, PathLen)){
				if('\\' == RecPath[PathLen]){
					continue;
				}
			}
		}
		fwrite(TempBuff, 1, sizeof(TempBuff), tfp);
	}

	fclose(fp);
	fclose(tfp);

	while(remove(FilePath));
	while(rename(TempPath, FilePath));
	
	SetFileAttributes(FilePath, FILE_ATTRIBUTE_HIDDEN);

	return TRUE;
}

string CCancelDlg::ComplexCancel()
{
	string strRet;

	for(int i = 1; i < __argc; i++){
		strRet += SmtUnlock(__argv[i]);
		if(!SmtDealRec(__argv[i])){
			strRet += "record file deal failed\r\n";
		}
	}

	if(!strcmp(m_EnvPath, __argv[1])){
		char SvnPath[255];
		memset(SvnPath, 0, sizeof(SvnPath));
		sprintf(SvnPath, "%s\\.svn", m_EnvPath);
		while(PathFileExists(SvnPath)){
			DeleteDir(SvnPath);
		}
		return strRet;
	}
	
	if(!SmtCancel(m_EnvPath, m_FatherPath)){
		strRet += "change data base failed\n";
	}
	
	DealResidual(m_EnvPath);

	return strRet;
}

BOOL CCancelDlg::DeleteDir(char *pPath)
{
	SHFILEOPSTRUCT FileOp;
	ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));

	FileOp.fFlags = FOF_SILENT|FOF_NOCONFIRMATION;
	FileOp.hNameMappings = NULL;
	FileOp.hwnd = NULL;
	FileOp.lpszProgressTitle = NULL;
	FileOp.pFrom = pPath;
	FileOp.pTo = NULL;
	FileOp.wFunc = FO_DELETE;

	SHFileOperation(&FileOp);

	return TRUE;
}

void CCancelDlg::DealResidual(char *pEnvPath)
{
	if(NULL == pEnvPath){
		return ;
	}

	char FilePath[255];
	memset(FilePath, 0, sizeof(FilePath));
	sprintf(FilePath, "%s\\%s", pEnvPath, "SmtRec.dat");

	FILE *fp = fopen(FilePath, "r");
	if(NULL == fp){
		return ;
	}

	fseek(fp, 0, SEEK_END);
	long fileLength = ftell(fp);

	if(fileLength <= 255){
		char StatusCmd[255];
		string StatusRet;
		memset(StatusCmd, 0, sizeof(StatusCmd));

		sprintf(StatusCmd, "svn status \"%s\"", pEnvPath);
		StatusRet = ExeCmd(StatusCmd);
		if(StatusRet.npos == StatusRet.find("A       ")){
			char SvnPath[255];
			memset(SvnPath, 0, sizeof(SvnPath));
			sprintf(SvnPath, "%s\\.svn", pEnvPath);
			while(PathFileExists(SvnPath)){
				DeleteDir(SvnPath);
			}
		}
	}

	fclose(fp);
}

void CCancelDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here

	if(__argc <= 1){
		CDialogEx::OnOK();
		return ;
	}

	string strRet;

	strRet = ComplexCancel();
	
	strRet += "cancel finished";
	
	m_MsgDlg.m_StrMsg = strRet;
	m_MsgDlg.DoModal();

	::WinExec("TASKKILL /F /IM TSVNCache.exe", SW_HIDE);
	::WinExec("TSVNCache.exe", SW_HIDE);

	CDialogEx::OnOK();
}
