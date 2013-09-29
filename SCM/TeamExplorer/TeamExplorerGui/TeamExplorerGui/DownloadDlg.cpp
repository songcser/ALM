// DownloadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "DownloadDlg.h"
#include "afxdialogex.h"
#include "Public.h"

// CDownloadDlg dialog

IMPLEMENT_DYNAMIC(CDownloadDlg, CDialogEx)

CDownloadDlg::CDownloadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDownloadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CDownloadDlg::~CDownloadDlg()
{
}

void CDownloadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RELYPATH_EDIT, m_eRelyPath);
	DDX_Control(pDX, IDC_CONFPATH_EDIT, m_eConfigFilePath);
}

BEGIN_MESSAGE_MAP(CDownloadDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SELCONFFILE_BUTTON, &CDownloadDlg::OnBnSelConfFile)
	ON_BN_CLICKED(IDOK, &CDownloadDlg::OnBnOK)
END_MESSAGE_MAP()

// CDownloadDlg message handlers
BOOL CDownloadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_eRelyPath.SetWindowText(__argv[2]);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDownloadDlg::OnBnSelConfFile()
{
	// TODO: Add your control notification handler code here
	CFileDialog OpenFileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY, "Configure file(*.xml)|*.xml||", NULL);
	OpenFileDlg.m_ofn.nFilterIndex = 1;
	OpenFileDlg.m_ofn.hwndOwner = m_hWnd;
	OpenFileDlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	OpenFileDlg.m_ofn.lpstrTitle = "Open Configue file";
	OpenFileDlg.m_ofn.nMaxFile = MAX_PATH;
	if(OpenFileDlg.DoModal() == IDOK){
		m_eConfigFilePath.SetWindowText(OpenFileDlg.GetPathName());
	}
}

DWORD WINAPI ThreadCallBack_D(LPVOID lpParamter)
{
	CDownloadDlg *pDownloadDlg = (CDownloadDlg *)lpParamter;
	pDownloadDlg->UpdateRelyFiles();
	pDownloadDlg->EndMultiThread();

	return 0;
}

BOOL CDownloadDlg::EndMultiThread()
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

BOOL CDownloadDlg::BeginMultiThread()
{
	HANDLE hThread = CreateThread(NULL, 0, ThreadCallBack_D, (LPVOID)this, 0, NULL);

	CloseHandle(hThread);

	m_ShowProgressDlg.DoModal();

	return TRUE;
}

void CDownloadDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here
	
	CString cConfigFile;
	CString cDestPath;

	m_eConfigFilePath.GetWindowText(cConfigFile);
	if("" == cConfigFile){
		AfxMessageBox("please input configure file by the button ...");
		return ;
	}

	m_eRelyPath.GetWindowText(cDestPath);
	if("" == cDestPath){
		AfxMessageBox("destination path is null");
		return ;
	}
	
	BeginMultiThread();

	m_DownloadMsgDlg.m_sRelyRet = m_sRelyRet;
	m_DownloadMsgDlg.DoModal();

	CDialogEx::OnOK();
}

BOOL CDownloadDlg::BeginDownload()
{
	BeginMultiThread();

	m_DownloadMsgDlg.m_sRelyRet = m_sRelyRet;
	m_DownloadMsgDlg.DoModal();

	return TRUE;
}

BOOL CDownloadDlg::UpdateRelyFiles()
{
	char tRevision[255];
	char tUrl[255];
	char tLocation[255];

	string sConfigPath = "";
	string sWcPath = "";
	string sCrtPath = "";
	string sDestPath = "";

	memset(tRevision, 0, sizeof(tRevision));
	memset(tUrl, 0, sizeof(tUrl));
	memset(tLocation, 0, sizeof(tLocation));

	if(__argc < 3){
		m_sRelyRet = "Error: have no enough arguments\r\n";
		m_sRelyRet += "download failed\r\n";
		return FALSE;
	}

	sCrtPath = __argv[2];
	GetWcPath(sCrtPath, sWcPath);
	sConfigPath = sWcPath;
	sConfigPath += "\\.svn\\";
	sConfigPath += CONF_FILE_NAME;

	if(setConfigXML((char *)sConfigPath.c_str())){
		getCodeInfo(tUrl, tRevision, tLocation);
		sDestPath = sWcPath;

		string sLocation = tLocation;
		if(string::npos != sLocation.find("..")){
			m_sRelyRet = "Error: can't find the rely path\r\ndownload failed\r\n";
			clean();
			return FALSE;
		}

		if(sLocation.length() <= 0 || (sLocation.length() == 2 && (string::npos != sLocation.find("./") || string::npos != sLocation.find(".\\"))) || (sLocation.length() == 1 && (sLocation[0] == '/' || sLocation[0] == '\\' || sLocation[0] == '.'))){
			getRelyFiles((char *)sDestPath.c_str(), m_sRelyRet);
		}
		else{
			char tLastChar = sLocation[sLocation.length()-1];
			if(tLastChar == '/' || tLastChar == '\\'){
				sLocation = sLocation.substr(0, sLocation.length()-1);
			}

			int len = -1;
			int pos = sLocation.find("./");
			if(pos == string::npos){
				pos = sLocation.find(".\\");
			}

			if(pos == string::npos){
				if(sLocation[0] == '\\' || sLocation[0] == '/'){
					len = sLocation.length();
				}
				else{
					len = sLocation.length() + 1;
				}
			}
			else{
				len = sLocation.length() - pos - 1;
			}

			sDestPath = sDestPath.substr(0, sDestPath.length() - len);

			getRelyFiles((char *)sDestPath.c_str(), m_sRelyRet);
		}
		
		clean();
	}
	else{
		m_sRelyRet = "Error: something wrong in configure file\r\n";
		m_sRelyRet += "download failed\r\n";
		return FALSE;
	}

	return TRUE;
}
