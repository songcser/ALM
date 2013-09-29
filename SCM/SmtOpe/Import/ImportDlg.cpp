
// ImportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Import.h"
#include "ImportDlg.h"
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


// CImportDlg dialog




CImportDlg::CImportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImportDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_RepURL, 0, sizeof(m_RepURL));
	memset(m_EnvPath, 0, sizeof(m_EnvPath));
	memset(m_RepURL, 0, sizeof(m_RepURL));
}

void CImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMPORTITEM, m_ImportItem);
	DDX_Control(pDX, IDC_COMBO2, m_ImportTo);
}

BEGIN_MESSAGE_MAP(CImportDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CImportDlg::OnBnImport)
END_MESSAGE_MAP()


// CImportDlg message handlers

BOOL CImportDlg::OnInitDialog()
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
		m_ImportItem.SetWindowTextA("nothing need to add");
		return TRUE;
	}

	for(int i = 1; i< __argc; i++){
		sAddItem += __argv[i];
		sAddItem += "\r\n";
	}
	m_ImportItem.SetWindowTextA(sAddItem.c_str());

	FindRecordFile(__argv[1], m_EnvPath);
	GetRepURL(m_EnvPath, m_RepURL);
	GetFatherPath(__argv[1], m_FatherPath);

	SetCombox();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImportDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CImportDlg::OnPaint()
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
HCURSOR CImportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

string CImportDlg::CStringToString(CString SourceStr)
{
	CStringA TempSourceStr(SourceStr.GetBuffer(0));
	SourceStr.ReleaseBuffer();

	string Name(TempSourceStr.GetBuffer(0));
	TempSourceStr.ReleaseBuffer();

	return Name;
}

BOOL CImportDlg::GetRepURL(char *pEnvPath, char *pRepURL)
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

BOOL CImportDlg::GetFatherPath(char *pCrtPath, char *pFatherPath)
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

BOOL CImportDlg::FindRecordFile(char *pCrtPath, char *pRetPath)
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

string CImportDlg::ExeCmd(char *pszCmd)
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

BOOL CImportDlg::IsNeedList()
{
	int UrlLen = strlen(m_RepURL);

	string tmpURL = m_RepURL;
	int tmpPos = tmpURL.find("branches");
	int proPos = tmpURL.find("products");

	if(proPos == tmpURL.npos){
		if(!memcmp(m_RepURL+UrlLen-5, "trunk", 5)){
			return TRUE;
		}
	}

	if(tmpPos != tmpURL.npos || proPos != tmpURL.npos){
		int i = tmpPos+8;
		int count = 0;
		while(1){
			if(i >= UrlLen){
				break;
			}
			if('/' == m_RepURL[i]){
				count++;
			}
			i++;
			if(count >= 2){
				return FALSE;
			}
		}
	}
	else{
		return FALSE;
	}
	
	return TRUE;
}

void CImportDlg::SetCombox()
{
	string strRet;

	if(IsNeedList()){
		string ListCmd = "svn list \"";
		ListCmd += m_RepURL;
		ListCmd += "\"";

		strRet = ExeCmd((char *)ListCmd.c_str());
		int strLen = strRet.length();

		int i = 0, j = 0;
		char tmpBuff[255];
		memset(tmpBuff, 0, sizeof(tmpBuff));

		while(1){
			if(i >= strLen){
				break;
			}
			if('\r' == strRet[i]){
				tmpBuff[j-1] = '\0';
				m_ImportTo.AddString(tmpBuff);
				memset(tmpBuff, 0, sizeof(tmpBuff));
				i+=2;
				j=0;
			}
			else{
				tmpBuff[j] = strRet[i];
				j++;
				i++;
			}
		}
		m_ImportTo.SetCurSel(0);
	}
	else{
		int UrlLen = strlen(m_RepURL);
		int i = UrlLen-1;
		while(1){
			if(i < 0){
				break;
			}
			if('/' == m_RepURL[i]){
				break;
			}
			i--;
		}
		if(i >= 0){
			char tmpBuff[255];
			memset(tmpBuff, 0, sizeof(tmpBuff));
			memcpy(tmpBuff, m_RepURL+i+1, UrlLen-i+1);
			m_ImportTo.AddString(tmpBuff);
			m_ImportTo.SetCurSel(0);
		}
	}
}

BOOL CImportDlg::SwitchURL(char *pRepURL, string &doURL)
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

BOOL CImportDlg::GetEndPath(char *pPath, char *pRetPath)
{
	if(NULL == pPath || NULL == pRetPath){
		return FALSE;
	}

	int Pathlen = strlen(pPath);
	int i = Pathlen-1;

	while(1){
		if(i < 0){
			break;
		}

		if('\\' == *(pPath+i)){
			break;
		}
		i--;
	}

	if(i >= 0){
		memcpy(pRetPath, pPath+i+1, Pathlen-i+1);
		return TRUE;
	}

	return FALSE;
}

void CImportDlg::OnBnImport()
{
	// TODO: Add your control notification handler code here

	if(__argc <= 1){
		CDialogEx::OnOK();
		return;
	}

	string strRet;

	CString cImportToStr;
	string sImportToStr;

	string DeleteCmd;
	string ImportCmd;
	string doURL;
	char FileName[255];

	string tmpURL = m_RepURL;
	int tmpPos = tmpURL.find("products");
	if(tmpPos != tmpURL.npos){
		doURL = tmpURL;
		if(IsNeedList()){
			int tIndex = m_ImportTo.GetCurSel();
			m_ImportTo.GetLBText(tIndex, cImportToStr);
			sImportToStr = CStringToString(cImportToStr);
			doURL += "/";
			doURL += sImportToStr;
		}

		doURL += "/";
		for(int i = 1; i < __argc; i++){
			memset(FileName, 0, sizeof(FileName));
			GetEndPath(__argv[i], FileName);
			DeleteCmd = "svn delete -m \"\" \"";
			DeleteCmd += doURL;
			DeleteCmd += FileName;
			DeleteCmd += "\"";
			ExeCmd((char *)DeleteCmd.c_str());
			ImportCmd = "svn import -m \"\" \"";
			ImportCmd += __argv[i];
			ImportCmd += "\" ";
			ImportCmd += "\"";
			ImportCmd += doURL;
			ImportCmd += FileName;
			ImportCmd += "\"";
			strRet = ExeCmd((char *)ImportCmd.c_str());
		}
	}
	else{
		SwitchURL(m_RepURL, doURL);
		if(IsNeedList()){
			int tIndex = m_ImportTo.GetCurSel();
			m_ImportTo.GetLBText(tIndex, cImportToStr);
			sImportToStr = CStringToString(cImportToStr);
			doURL += "/";
			doURL += sImportToStr;
		}
		doURL += "/";
		for(int i = 1; i < __argc; i++){
			memset(FileName, 0, sizeof(FileName));
			GetEndPath(__argv[i], FileName);
			DeleteCmd = "svn delete -m \"\" \"";
			DeleteCmd += doURL;
			DeleteCmd += FileName;
			DeleteCmd += "\"";
			ExeCmd((char *)DeleteCmd.c_str());
			ImportCmd = "svn import -m \"\" \"";
			ImportCmd += __argv[i];
			ImportCmd += "\" ";
			ImportCmd += "\"";
			ImportCmd += doURL;
			ImportCmd += FileName;
			ImportCmd += "\"";
			strRet = ExeCmd((char *)ImportCmd.c_str());
		}
	}

	m_ImportMsgDlg.m_StrMsg = strRet;
	m_ImportMsgDlg.DoModal();

	CDialogEx::OnOK();
}
