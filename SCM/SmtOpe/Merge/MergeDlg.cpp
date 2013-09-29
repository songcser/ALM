
// MergeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Merge.h"
#include "MergeDlg.h"
#include "afxdialogex.h"
#include "resource.h"

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


// CMergeDlg dialog




CMergeDlg::CMergeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMergeDlg::IDD, pParent)
{
	memset(m_RepURL,0,sizeof(m_RepURL));
	memset(m_EnvPath,0,sizeof(m_EnvPath));
	//memset(m_RelativePath,0,sizeof(m_RelativePath));
	memset(m_AbsolationURL,0,sizeof(m_AbsolationURL));
	memset(m_MyPath,0,sizeof(m_MyPath));
	memset(m_FirstPath,0,sizeof(m_FirstPath));
	memset(m_LastPath,0,sizeof(m_LastPath));
	memset(m_LibPath,0,sizeof(m_LibPath));
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMergeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCE_EDIT, m_SourceEdit);
	DDX_Control(pDX, IDC_DESTINATION_EDIT, m_DestinationEdit);
	DDX_Control(pDX, IDC_VERSIONFROM_EDIT, m_VersionFrom);
	DDX_Control(pDX, IDC_VERSIONTO_EDIT, m_VersionTo);
	//DDX_Control(pDX, IDC_COMBO1, m_Library);
	DDX_Control(pDX, IDC_LIBRARY_COMBO, m_Library);
}

BEGIN_MESSAGE_MAP(CMergeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMergeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SHOWLOG_BUTTON, &CMergeDlg::OnBnClickedShowlogButton)
//	ON_CBN_CLOSEUP(IDC_LIBRARY_COMBO, &CMergeDlg::OnCloseupLibraryCombo)
ON_CBN_SELCHANGE(IDC_LIBRARY_COMBO, &CMergeDlg::OnSelchangeLibraryCombo)
END_MESSAGE_MAP()


// CMergeDlg message handlers

BOOL CMergeDlg::OnInitDialog()
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
	if (__argc==2)
	{
		strcpy(m_MyPath,__argv[1]);
		if (!FindRecordFile(m_MyPath,m_EnvPath))
		{
			AfxMessageBox("Is not a work environment");
			return TRUE;
		}

		if(!GetRepURL(m_EnvPath, m_RepURL)){
			AfxMessageBox("Get URL Failed");
			return TRUE;
		}

		//char RelativePath[255];
		memset(m_RelativePath,0,sizeof(m_RelativePath));
		if (!GetRelativeURL(m_MyPath,m_RelativePath))
		{
			AfxMessageBox("Error GetRelativePath");
			return TRUE;
		}

		char AbsolationURL[255];
		memset(AbsolationURL,0,sizeof(AbsolationURL));
		sprintf(AbsolationURL,"%s%s",m_RepURL,m_RelativePath);
		//strcpy(AbsolationURL,m_RepURL);

		char *trunkPos = strstr(AbsolationURL,"/trunk/");
		char *branchesPos = strstr(AbsolationURL,"/branches/");
		if (trunkPos == NULL && branchesPos != NULL)
		{
			branchesTotrunk(AbsolationURL,branchesPos);
		}
		else if(trunkPos != NULL && branchesPos == NULL)
		{
			trunkTobranches(AbsolationURL,trunkPos);
		}
		else if (trunkPos == NULL && branchesPos == NULL)
		{
			AfxMessageBox("Error, Input Parameter is wrong");
		}
		else if (trunkPos<branchesPos)
		{
			trunkTobranches(AbsolationURL,trunkPos);
		}
		else if (trunkPos>branchesPos)
		{
			branchesTotrunk(AbsolationURL,branchesPos);
		}

		m_SourceEdit.SetWindowTextA(m_AbsolationURL);
		m_DestinationEdit.SetWindowTextA(m_MyPath);
	}
	else
	{
		AfxMessageBox("Error, Input Parameter is wrong");
		return FALSE;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMergeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMergeDlg::OnPaint()
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
HCURSOR CMergeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMergeDlg::branchesTotrunk(char *AbsolationURL,char *branchesPos)
{
	int count = strlen(AbsolationURL)-strlen(branchesPos);
	memcpy(m_FirstPath,AbsolationURL,count);

	char *temp = "/trunk";
	char libPath[10];
	memset(libPath,0,sizeof(libPath));
	count = 0;
	for (int i=0;i<6;i++)
	{
		m_LibPath[count] = temp[i];
		count++;
	}
	branchesPos+=10;
	int j=0;
	//libPath[j]='/';
	m_LibPath[count] = '/';
	count++;

	while('/'!= *branchesPos)
	{
		
		libPath[j]=*branchesPos;
		//m_AbsolationURL[count] = *branchesPos;
		//count;
		branchesPos++;
		j++;
	}
	branchesPos++;
	count = 0;
	while('\0'!=*branchesPos)
	{
		m_LastPath[count] = *branchesPos;
		count++;
		branchesPos++;
	}
	
	sprintf(m_AbsolationURL,"%s%s%s",m_FirstPath,m_LibPath,m_LastPath);

	char LibTemp[255];
	memset(LibTemp,0,sizeof(LibTemp));
	strcpy(LibTemp,m_FirstPath);
	//strcat(LibTemp,"/branches");

	SetLibrary(LibTemp);

	int nIndex = 0;
	while((nIndex = m_Library.FindString(nIndex,libPath))!=LB_ERR)
	{
		m_Library.DeleteString(nIndex);
	}

	m_Library.AddString("trunk");
	nIndex = m_Library.FindString(0,"trunk");
	m_Library.SetCurSel(nIndex);
	//m_AbsolationURL[count] = '\0';
	//strcat(m_AbsolationURL,m_RelativePath);

	//m_Library.ModifyStyle(0,WS_DISABLED);
	//m_Library.AddString(libPath);
	//m_Library.SetCurSel(0);
	//m_Library.
}

void CMergeDlg::trunkTobranches(char *AbsolationURL,char *trunk)
{
	int count = strlen(AbsolationURL)-strlen(trunk);
	memcpy(m_FirstPath,AbsolationURL,count);
	/*
	char *temp = "/branches/";
	for (int i=0;i<9;i++)
	{
		m_FirstPath[count] = temp[i];
		count++;
	}*/
	//char firstName[255];
	//memset(firstName,0,sizeof(firstName));
	SetLibrary(m_FirstPath);

	trunk+=7;
	int k=0;
	while('\0'!=*trunk)
	{
		m_LastPath[k] = *trunk;
		k++;
		trunk++;
	}
	memset(m_AbsolationURL,0,sizeof(m_AbsolationURL));
	sprintf(m_AbsolationURL,"%s/branches/%s/%s",m_FirstPath,m_LibPath,m_LastPath);
}

void CMergeDlg::SetLibrary(char *LibPath)
{
	char ListCmd[255];
	memset(ListCmd,0,sizeof(ListCmd));
	
	char tempPathLib[255];
	memset(tempPathLib,0,sizeof(tempPathLib));
	strcpy(tempPathLib,LibPath);
	char *temp = "/branches/";
	int count = strlen(LibPath);
	for (int i=0;i<9;i++)
	{
		tempPathLib[count] = temp[i];
		count++;
	}

	sprintf(ListCmd,"svn list %s",tempPathLib);
	string strRet = ExeCmd(ListCmd);

	//while(strtok(strRet.c_str(),"\n\\"))
	int len = 0;
	int num = 0;
	char Libname[255];
	while((len = strRet.find("/",len))!=string::npos)
	{
		memset(Libname,0,sizeof(Libname));
		int count = len - num;
		strRet.copy(Libname,count,num);
		m_Library.AddString(Libname);

		len+=3;
		num = len;
	}

	//int index = m_Library.GetTopIndex();
	m_Library.SetCurSel(0);

	memset(Libname,0,sizeof(Libname));
	m_Library.GetLBText(0,Libname);
	int length = strlen(Libname);

	int j = 0;
	for (int i = 0;i<length;i++)
	{
		
		if (Libname[i] == '\n'||Libname[i]=='\r')
		{
			i++;
			continue;
		}
		m_LibPath[j] = Libname[i];
		j++;
	}
	//strcpy(m_LibPath,Libname);
}

string CMergeDlg::CStringToString(CString SourceStr)
{
	CStringA TempSourceStr(SourceStr.GetBuffer(0));
	SourceStr.ReleaseBuffer();

	string Name(TempSourceStr.GetBuffer(0));
	TempSourceStr.ReleaseBuffer();

	return Name;
}

BOOL CMergeDlg::FindRecordFile(char *pCrtPath, char *pRetPath)
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

BOOL CMergeDlg::GetFatherPath(char *pCrtPath, char *pFatherPath)
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

string CMergeDlg::ExeCmd(char *pszCmd)
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

BOOL CMergeDlg::GetRepURL(char *pEnvPath, char *pRepURL)
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

BOOL CMergeDlg::GetRelativeURL(char *filePath,char *RelativeURL)
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

void CMergeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CString strFrom;
	m_VersionFrom.GetWindowTextA(strFrom);
	CString strTo;
	m_VersionTo.GetWindowTextA(strTo);
	string strTmpFrom = CStringToString(strFrom);
	string strTmpTo = CStringToString(strTo);
	//int numFrom = atoi(strTmpFrom.c_str());
	//int numTo = atoi(strTmpTo.c_str());
	char MargeCmd[255];
	memset(MargeCmd,0,sizeof(MargeCmd));


	if (strTmpTo == ""&&strTmpFrom == "")
	{
		AfxMessageBox("please input version! Thank you");
		return;
	}
	else if (strTmpFrom == strTmpTo)
	{
		sprintf(MargeCmd,"svn merge -c %s --ignore-ancestry \"%s\" \"%s\"",strTmpTo.c_str(),m_AbsolationURL,m_MyPath);
	}
	else if (strTmpTo == "" && strTmpFrom != "")
	{
		sprintf(MargeCmd,"svn merge -c %s --ignore-ancestry \"%s\" \"%s\"",strTmpFrom.c_str(),m_AbsolationURL,m_MyPath);
	}
	else if (strTmpFrom == "" && strTmpTo != "")
	{
		sprintf(MargeCmd,"svn merge -c %s --ignore-ancestry \"%s\" \"%s\"",strTmpTo.c_str(),m_AbsolationURL,m_MyPath);
	}
	else
	{
		sprintf(MargeCmd,"svn merge -r %s:%s --ignore-ancestry \"%s\" \"%s\"",strTmpFrom.c_str(),strTmpTo.c_str(),m_AbsolationURL,m_MyPath);
	}
	
	string mStrRet;
	mStrRet = ExeCmd(MargeCmd);

	mStrRet += "Merge Finished!";
	m_ShowLog.SetMessage((char *)mStrRet.c_str());
	if (m_ShowLog.DoModal() == IDOK)
	{
		CDialogEx::OnOK();
	}
	//AfxMessageBox(mStrRet.c_str());

	::WinExec("TASKKILL /F /IM TSVNCache.exe", SW_HIDE);
	::WinExec("TSVNCache.exe", SW_HIDE);

	CDialogEx::OnOK();
}


void CMergeDlg::OnBnClickedShowlogButton()
{
	// TODO: Add your control notification handler code here

	char showLog[255];
	memset(showLog,0,sizeof(showLog));
	sprintf(showLog,"svn log \"%s\"",m_AbsolationURL);
	//AfxMessageBox(m_AbsolationURL);
	string mLogMessage;
	mLogMessage = ExeCmd(showLog);

	char FilePath[255];
	memset(FilePath,0,sizeof(FilePath));
	sprintf(FilePath,"%s\\log.txt",m_EnvPath);
	int i = 0;
	while(PathFileExists(FilePath))
	{
		sprintf(FilePath,"%s\\log%d.txt",m_EnvPath,i);
		i++;
	}
	FILE *file;
	file = fopen(FilePath,"w");
	if (file == NULL)
	{
		AfxMessageBox("Error,create log file error");
		return;
	}
	fwrite(mLogMessage.c_str(),1,strlen(mLogMessage.c_str()),file);
	fclose(file);

	char OpenFileCmd[255];
	memset(OpenFileCmd,0,sizeof(OpenFileCmd));
	sprintf(OpenFileCmd,"NOTEPAD %s",FilePath);
	::WinExec(OpenFileCmd,SW_SHOW);
	//system(FilePath);

	while(remove(FilePath));
}


//void CMergeDlg::OnCloseupLibraryCombo()
//{
//	// TODO: Add your control notification handler code here
//
//}


void CMergeDlg::OnSelchangeLibraryCombo()
{
	// TODO: Add your control notification handler code here
	CString csValue;
	int index = m_Library.GetCurSel();
	m_Library.GetLBText(index,csValue);

	string strLib;
	strLib = CStringToString(csValue);

	if (strLib == "trunk")
	{
		strLib = "trunk/";
		sprintf(m_AbsolationURL,"%s/%s%s",m_FirstPath,strLib.c_str(),m_LastPath);
	}
	else
	{
		string strTemp = "branches/";
		//string tmp = strLib.find('\r',0);
		char tmp[20];
		memset(tmp,0,sizeof(tmp));
		strcpy(tmp,strLib.c_str());
		char tmp1[20];
		memset(tmp1,0,sizeof(tmp1));
		int len = strlen(tmp);
		int j = 0;
		for (int i=0;i<len;i++)
		{
			if (tmp[i] == '\n'||tmp[i] == '\r')
			{
				i++;
				continue;
			}
			tmp1[j] = tmp[i];
			j++;
		}
		strTemp += tmp1;
		sprintf(m_AbsolationURL,"%s/%s/%s",m_FirstPath,strTemp.c_str(),m_LastPath);
	}

	
	m_SourceEdit.SetWindowTextA(m_AbsolationURL);
}
