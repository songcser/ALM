
// CheckoutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Checkout.h"
#include "CheckoutDlg.h"
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

// CCheckoutDlg dialog
CCheckoutDlg::CCheckoutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCheckoutDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_EnvPath, 0, sizeof(m_EnvPath));
	memset(m_FatherPath, 0, sizeof(m_FatherPath));
	memset(m_RepURL, 0, sizeof(m_RepURL));
}

void CCheckoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECKOUTITEM, m_CheckItem);
}

BEGIN_MESSAGE_MAP(CCheckoutDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCheckoutDlg::OnBnCheckout)
END_MESSAGE_MAP()


// CCheckoutDlg message handlers

BOOL CCheckoutDlg::OnInitDialog()
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

	string sCheckItem;

	if(__argc <= 1){
		m_CheckItem.SetWindowTextA("nothing need to check out");
		return TRUE;
	}

	for(int i = 1; i< __argc; i++){
		sCheckItem += __argv[i];
		sCheckItem += "\r\n";
	}
	m_CheckItem.SetWindowTextA(sCheckItem.c_str());

	if (FindRecordFile(__argv[1], m_EnvPath))
	{
		GetRepURL(m_EnvPath, m_RepURL);
		GetFatherPath(__argv[1], m_FatherPath);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCheckoutDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCheckoutDlg::OnPaint()
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
HCURSOR CCheckoutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

string CCheckoutDlg::TopCheckout()
{
	string strRet;
	string LockUser;

	if (IsFileLocked(m_RepURL, LockUser))
	{
		LockUser += " had locked this file";
		strRet = LockUser;
		return strRet;
	}

	char datFile[255];
	memset(datFile,0,sizeof(datFile));
	sprintf(datFile,"%s\\SmtRec.dat",m_EnvPath);

	while(PathFileExists(m_EnvPath)){
		DeleteDir(m_EnvPath);
	}

	char CheckoutCmd[255];
	memset(CheckoutCmd, 0, sizeof(CheckoutCmd));
	sprintf(CheckoutCmd, "svn checkout \"%s\" \"%s\"", m_RepURL, m_EnvPath);
	strRet += ExeCmd(CheckoutCmd);

	FILE *fp;
	fp = fopen(datFile,"a+");
	if (NULL==fp)
	{
		strRet += "open dat file error";
		return strRet;
	}

	fwrite(m_RepURL, 1, sizeof(m_RepURL), fp);

	WIN32_FIND_DATA FindData;
	HANDLE hError;

	char FilePathName[255];
	char FullPathName[255];

	memset(FilePathName,0,sizeof(FilePathName));
	memset(FullPathName,0,sizeof(FullPathName));

	strcpy(FilePathName,m_EnvPath);
	strcat(FilePathName,"\\*.*");
	hError = FindFirstFile(FilePathName,&FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
		FindClose(hError);
		strRet = "FindFirstFile Error";
		fclose(fp);
		return strRet;
	}
	
	while(::FindNextFileA(hError,&FindData))
	{
		if (strcmp(FindData.cFileName, ".") == 0   || strcmp(FindData.cFileName, "..") == 0 )  
		{  
			continue;  
		}  

		memset(FullPathName, 0, sizeof(FullPathName));
		wsprintf(FullPathName, "%s\\%s", m_EnvPath,FindData.cFileName);  

		if (strcmp(datFile, FullPathName)==0)
		{
			continue;
		}
		if(!memcmp(FullPathName+strlen(FullPathName)-4, ".svn", 4)){
			continue;
		}

		strRet += DealLock(FullPathName, fp);
	}
	
	fclose(fp);
	FindClose(hError);

	//strRet += UpdateRely();

	SetFileAttributes(datFile, FILE_ATTRIBUTE_HIDDEN);

	return strRet;
}

BOOL CCheckoutDlg::SwitchURL(char *pRepURL, string &doURL)
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

BOOL CCheckoutDlg::DealURL(string &doURL)
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

string CCheckoutDlg::UpdateRely()
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

string CCheckoutDlg::CStringToString(CString SourceStr)
{
	CStringA TempSourceStr(SourceStr.GetBuffer(0));
	SourceStr.ReleaseBuffer();

	string Name(TempSourceStr.GetBuffer(0));
	TempSourceStr.ReleaseBuffer();

	return Name;
}

BOOL CCheckoutDlg::GetRepURL(char *pEnvPath, char *pRepURL)
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

BOOL CCheckoutDlg::URLToPath(char *pDest, char *pSrc)
{
	if(NULL == pDest || NULL == pSrc){
		return FALSE;
	}

	int len = strlen(pSrc);
	int i = 0;
	for(i = 0; i < len; i++){
		if('/' == *pSrc){
			*pDest = '\\';
		}
		else{
			*pDest = *pSrc;
		}
		pDest++;
		pSrc++;
	}

	return TRUE;
}

BOOL CCheckoutDlg::PathToURL(char *pDest, char *pSrc)
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

bool CCheckoutDlg::IsFileLocked(char* pRepURL, string &LockUser)
{
	if(NULL == pRepURL){
		return true;
	}

	string strList, strInfo;
	char ListCmd[255];
	char InfoCmd[255];
	char tmpBuff[255];
	string tmpPath;

	int EnglishPos = 0;
	int ChinesePos = 0;
	char UserName[255];

	memset(UserName, 0, sizeof(UserName));
	memset(InfoCmd, 0, sizeof(InfoCmd));
	memset(tmpBuff, 0, sizeof(tmpBuff));
	memset(ListCmd, 0, sizeof(ListCmd));

	sprintf(ListCmd, "svn list -R \"%s\"", pRepURL);
	strList = ExeCmd(ListCmd);

	sprintf(InfoCmd, "svn info \"%s\"", pRepURL);
	strInfo = ExeCmd(InfoCmd);

	EnglishPos = strInfo.find("Lock Owner:");
	ChinesePos = strInfo.find("Ëø¶¨");
	if(strInfo.npos != EnglishPos || strInfo.npos != ChinesePos){
		if(strInfo.npos != EnglishPos){
			int i = EnglishPos+11;
			int j = 0;
			while(strInfo[i] != '\r'){
				UserName[j] = strInfo[i];
				i++;
				j++;
			}
			string tmpStr(UserName);
			LockUser = tmpStr;
		}
		return true;
	}
	
	if(0 == strlen(strList.c_str())){
		return false;
	}

	int ExecTimes = 0;
	int i=0;
	int j=0;
	while(1)
	{
		if ('\0'==strList[i])
		{
			break;
		}

		if ('\r'==strList[i])
		{
			ExecTimes++;
			tmpBuff[j] = '\"';
			tmpBuff[j+1] = ' ';
			j=0;

			char temp[255];
			memset(temp,0,sizeof(temp));
			sprintf_s(temp,"\"%s/%s",pRepURL,tmpBuff);
			tmpPath += temp;
			i += 2;
			memset(tmpBuff, 0, sizeof(tmpBuff));
			if(ExecTimes >= 5){
				ExecTimes = 0;
				string strInfoCmd = "svn info ";
				strInfoCmd += tmpPath;
				strInfo = ExeCmd((char *)strInfoCmd.c_str());
				EnglishPos = strInfo.find("Lock Owner:");
				ChinesePos = strInfo.find("Ëø¶¨");
				if(strInfo.npos != EnglishPos || strInfo.npos != ChinesePos){
					if(strInfo.npos != EnglishPos){
						int i = EnglishPos+11;
						int j = 0;
						while(strInfo[i] != '\r'){
							UserName[j] = strInfo[i];
							i++;
							j++;
						}
						string tmpStr(UserName);
						LockUser = tmpStr;
					}
					return true;
				}
				tmpPath = "";
			}
		}
		else
		{
			tmpBuff[j]=strList[i];
			j++;
			i++;
		}
	}

	if(0 != ExecTimes){
		string strInfoCmd = "svn info ";
		strInfoCmd += tmpPath;
		strInfo = ExeCmd((char *)strInfoCmd.c_str());
		EnglishPos = strInfo.find("Lock Owner:");
		ChinesePos = strInfo.find("Ëø¶¨");
		if(strInfo.npos != EnglishPos || strInfo.npos != ChinesePos){
			if(strInfo.npos != EnglishPos){
				int i = EnglishPos+11;
				int j = 0;
				while(strInfo[i] != '\r'){
					UserName[j] = strInfo[i];
					i++;
					j++;
				}
				string tmpStr(UserName);
				LockUser = tmpStr;
			}
			return true;
		}
	}

	return false;
}

string CCheckoutDlg::DealLock(LPCSTR Path, FILE *fp)
{
	if(NULL == Path){
		return "";
	}

	if(!PathFileExists(Path)){
		return "";
	}

	if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(Path)){
		char LockCmd[255];
		memset(LockCmd, 0, sizeof(LockCmd));
		sprintf(LockCmd, "svn lock -m \"test checkout and lock\" \"%s\"", Path);
		ExeCmd(LockCmd);

		char TempBuff[255];
		memset(TempBuff, 0, sizeof(TempBuff));
		memcpy(TempBuff, Path+strlen(m_EnvPath), strlen(Path)-strlen(m_EnvPath));
		fwrite(TempBuff, 1, sizeof(TempBuff), fp);

		return "";
	}
	else{
		char TempBuff[255];
		memset(TempBuff, 0, sizeof(TempBuff));
		if(strlen(Path) > strlen(m_EnvPath)){
			memcpy(TempBuff, Path+strlen(m_EnvPath), strlen(Path)-strlen(m_EnvPath));
			fwrite(TempBuff, 1, sizeof(TempBuff), fp);
		}
	}

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
		return "";  
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
			int len = strlen(FullPathName);
			if(!memcmp(FullPathName+len-4, ".svn", 4)){
				continue;
			}

			strRet += DealLock(FullPathName, fp);
		}
		else{
			char LockCmd[255];
			memset(LockCmd, 0, sizeof(LockCmd));
			sprintf(LockCmd, "svn lock -m \"test checkout and lock\" \"%s\"", FullPathName);
			strRet += ExeCmd(LockCmd);

			char TempBuff[255];
			memset(TempBuff, 0, sizeof(TempBuff));
			memcpy(TempBuff, FullPathName+strlen(m_EnvPath), strlen(FullPathName)-strlen(m_EnvPath));
			fwrite(TempBuff, 1, sizeof(TempBuff), fp);
		}
	}

	FindClose(hError);
	
	return strRet;
}  

BOOL CCheckoutDlg::IsChildDir(char *pFatherPath, char *pCrtPath)
{
	if(NULL == pFatherPath || NULL == pCrtPath){
		return FALSE;
	}

	int FatherPathLen = strlen(pFatherPath);
	int CrtPathLen = strlen(pCrtPath);
	if(FatherPathLen < CrtPathLen){
		if(!memcmp(pCrtPath, pFatherPath, FatherPathLen)){
			if('\\' == *(pCrtPath+FatherPathLen)){
				int i = 0, j = 0;
				int CycleTimes = CrtPathLen - FatherPathLen;
				for(i = 0; i < CycleTimes; i++){
					if('\\' == *(pCrtPath+FatherPathLen+i)){
						j++;
					}
					if(j >= 2){
						return FALSE;
					}
				}
				if(1 == j){
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

BOOL CCheckoutDlg::GetFatherPath(char *pCrtPath, char *pFatherPath)
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

BOOL CCheckoutDlg::FindRecordFile(char *pCrtPath, char *pRetPath)
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

BOOL CCheckoutDlg::DeleteDir(char *pPath)
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

void CCheckoutDlg::DeleteFile (string path)
{
	string DirName = path ;
	string Dot1(".");
	string Dot2("..");

	WIN32_FIND_DATA FindData ;
	HANDLE Find ;
	string DirFindName = DirName+"\\*.*";
	Find = FindFirstFile(DirFindName.c_str() , &FindData);
	FindNextFile(Find,&FindData);
	if ( Find == INVALID_HANDLE_VALUE )
	{
		FindClose(Find);
		return;
	}
	while (1)
	{
		if (!FindNextFile(Find,&FindData))
			break;
		//string strTmpName = DirName + FindData.cFileName ;
		if ( Dot1 != FindData.cFileName || Dot2 != FindData.cFileName )
		{
			if ( FindData.dwFileAttributes == 16 )
			{
				string NewDirName = DirName + "\\" + FindData.cFileName + "\\" ;
				DeleteFile(NewDirName);
			}
		}
		string strImg = DirName + "\\" + FindData.cFileName ;
		string dele = "del \"" + strImg + "\"";
		ExeCmd((char *)dele.c_str()) ;
	}
	FindClose(Find);
	RemoveDirectory(path.c_str());
}

string CCheckoutDlg::ExeCmd(char *pszCmd)
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

BOOL CCheckoutDlg::IsInDatFile(char* pPath)
{
	char filePath[255];
	memset(filePath,0,sizeof(filePath));
	sprintf(filePath,"%s\\SmtRec.dat",m_EnvPath);

	FILE *file;
	file = fopen(filePath,"r");
	if (file == NULL)
	{
		return FALSE;
	}

	char tempPath[255];
	memset(tempPath,0,sizeof(tempPath));

	fseek(file,255,SEEK_SET);
	while(fread(tempPath,1,255,file)==255)
	{
		if (strcmp(tempPath,pPath+strlen(m_EnvPath))==0)
		{
			fclose(file);
			return TRUE;
		}
	}

	fclose(file);
	return FALSE;
}

string CCheckoutDlg::EasyCheckout()
{
	string strRet;
	
	char UpdateCmd[255];

	char FilePath[255];
	memset(FilePath, 0, sizeof(FilePath));
	sprintf(FilePath, "%s\\SmtRec.dat", m_EnvPath);

	FILE *fp = fopen(FilePath, "a+");
	if(NULL == fp){
		return "record file open failed";
	}

	char TmpPath[255];
	for(int i = 1; i < __argc; i++){
		memset(TmpPath, 0, sizeof(TmpPath));
		memcpy(TmpPath, __argv[i], strlen(__argv[i]));
		if(PathFileExists(TmpPath)){
			if(FILE_ATTRIBUTE_DIRECTORY == GetFileAttributes(TmpPath)){
				DeleteDir(TmpPath);
			}
			else{
				while(remove(TmpPath));
			}
		}
		memset(UpdateCmd, 0, sizeof(UpdateCmd));
		sprintf(UpdateCmd, "svn up \"%s\"", TmpPath);
		strRet += ExeCmd(UpdateCmd);
		DealLock(TmpPath, fp);
	}

	fclose(fp);

	return strRet;
}

BOOL CCheckoutDlg::DealFatherPath(char *pPath, FILE *fp)
{
	if(NULL == pPath){
		return FALSE;
	}

	char TempBuff[255];
	char FatherPath[255];

	if((strlen(pPath) == strlen(m_EnvPath)) && (!memcmp(pPath, m_EnvPath, strlen(m_EnvPath)))){
		char SvnPath[255];
		memset(SvnPath, 0, sizeof(SvnPath));
		sprintf(SvnPath, "%s\\.svn", m_EnvPath);
		if(PathFileExists(SvnPath)){
			return TRUE;
		}
		char CoCmd[255];
		memset(CoCmd, 0, sizeof(CoCmd));
		sprintf(CoCmd, "svn co --depth=empty \"%s\" \"%s\"", m_RepURL, m_EnvPath);
		ExeCmd(CoCmd);
		return TRUE;
	}

	if(IsInDatFile(pPath)){
		return TRUE;
	}
	else{
		memset(FatherPath, 0, sizeof(FatherPath));
		GetFatherPath(pPath, FatherPath);
		DealFatherPath(FatherPath, fp);
	}

	memset(TempBuff, 0, sizeof(TempBuff));
	memcpy(TempBuff, pPath+strlen(m_EnvPath), strlen(pPath)-strlen(m_EnvPath));
	fwrite(TempBuff, 1, sizeof(TempBuff), fp);

	char UpCmd[255];
	memset(UpCmd, 0, sizeof(UpCmd));
	sprintf(UpCmd, "svn up --depth=empty --force \"%s\"", pPath);
	ExeCmd(UpCmd);

	return TRUE;
}

string CCheckoutDlg::ComplexCheckout()
{
	string strRet;

	char FilePath[255];
	memset(FilePath, 0, sizeof(FilePath));
	sprintf(FilePath, "%s\\SmtRec.dat", m_EnvPath);

	FILE *fp = fopen(FilePath, "r+");
	if(NULL == fp){
		return "record file open failed";
	}

	fseek(fp, 0, SEEK_END);

	DealFatherPath(m_FatherPath, fp);

	fclose(fp);

	strRet += EasyCheckout();

	return strRet;
}

void CCheckoutDlg::OnBnCheckout()
{
	// TODO: Add your control notification handler code here
	if(__argc <= 1){
		CDialogEx::OnOK();
		return ;
	}
	
	string strRet;
	string LockUser;

	if (strcmp(__argv[1],m_EnvPath)==0)
	{
		strRet = TopCheckout();
		m_CheckoutMsgDlg.m_StrMsg = strRet;
		m_CheckoutMsgDlg.DoModal();

		::WinExec("TASKKILL /F /IM TSVNCache.exe", SW_HIDE);
		::WinExec("TSVNCache.exe", SW_HIDE);

		CDialogEx::OnOK();
		return;
	}

	char TempURL[255];
	char CheckURL[255];
	char *pArgv;

	for(int i = 1; i < __argc; i++){
		memset(TempURL, 0, sizeof(TempURL));
		memset(CheckURL, 0, sizeof(CheckURL));
		pArgv = __argv[i];
		sprintf(TempURL, "%s%s", m_RepURL, pArgv+strlen(m_EnvPath));
		PathToURL(CheckURL, TempURL);
		if(IsFileLocked(CheckURL, LockUser)){
			LockUser += " had locked this file";
			AfxMessageBox((char *)LockUser.c_str());
			CDialogEx::OnOK();
			return;
		}
	}

	strRet = ComplexCheckout();

	m_CheckoutMsgDlg.m_StrMsg = strRet;
	m_CheckoutMsgDlg.DoModal();
	
	::WinExec("TASKKILL /F /IM TSVNCache.exe", SW_HIDE);
	::WinExec("TSVNCache.exe", SW_HIDE);

	/*
	char CleanupCmd[255];
	memset(CleanupCmd,0,sizeof(CleanupCmd));
	sprintf(CleanupCmd,"svn cleanup \"%s\"",__argv[1]);
	ExeCmd(CleanupCmd);
	*/

	CDialogEx::OnOK();
}
