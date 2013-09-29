// MergeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "MergeDlg.h"
#include "afxdialogex.h"
#include "Public.h"
#include "ShowLogDlg.h"

// CMergeDlg dialog

IMPLEMENT_DYNAMIC(CMergeDlg, CDialogEx)

CMergeDlg::CMergeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMergeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
}

CMergeDlg::~CMergeDlg()
{
}

void CMergeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCEPATH_EDIT, m_eSourcePath);
	DDX_Control(pDX, IDC_DESTPATH_EDIT, m_eDestPath);
	DDX_Control(pDX, IDC_FROMREVISION_EDIT, m_eFromRevision);
	DDX_Control(pDX, IDC_TOREVISION_EDIT, m_eToRevision);
	DDX_Control(pDX, IDC_FROMVERSION_COMBO, m_cFromVersion);
}

BEGIN_MESSAGE_MAP(CMergeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SHOWLOG_BUTTON, &CMergeDlg::OnBnShowLog)
	ON_BN_CLICKED(IDOK, &CMergeDlg::OnBnOK)
	ON_MESSAGE(WM_TEAM_EXPLORER_EXIT, OnTeamExplorerExit)
	ON_CBN_SELCHANGE(IDC_FROMVERSION_COMBO, &CMergeDlg::OnSelChangeFromVersion)
END_MESSAGE_MAP()

// CMergeDlg message handlers

BOOL CMergeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	string sDestPath;
	string sSourceURL;
	char tSourceURL[255];

	if(__argc <= 2){
		m_eDestPath.SetWindowTextA("nothing need to merge");
	}
	else{
		for(int i = 2; i< __argc; i++){
			sDestPath += __argv[i];
			sDestPath += "\r\n";

			memset(tSourceURL, 0, sizeof(tSourceURL));
			m_Kernel.GetWcURL(__argv[i], tSourceURL);
			sSourceURL += tSourceURL;
			sSourceURL += "\r\n";
		}

		RidPercent20(sSourceURL);
		m_eSourcePath.SetWindowTextA(sSourceURL.c_str());
		m_eDestPath.SetWindowTextA(sDestPath.c_str());

		GetProVersion();

		int iSize = m_Kernel.m_ChildDirs.size();
		for(int i = 0; i < iSize; i++){
			m_cFromVersion.AddString(m_Kernel.m_ChildDirs[i].c_str());
		}

		m_cFromVersion.SetWindowTextA("ÇëÑ¡Ôñ");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CMergeDlg::OnTeamExplorerExit(WPARAM wParam, LPARAM lParam)
{
	m_ShowRetMsgDlg.DestroyWindow();
	CDialogEx::OnOK();
	return 0;
}

BOOL CMergeDlg::GetProVersion()
{
	string sWcPath;
	string sDepURL;
	char tDepURL[255];
	memset(tDepURL, 0, sizeof(tDepURL));

	GetWcPath(__argv[2], sWcPath);
	m_Kernel.GetWcURL((char *)sWcPath.c_str(), tDepURL);
	
	sDepURL = tDepURL;
	RidPercent20(sDepURL);

	int pos = -1;
	int pos1 = sDepURL.find("/trunk");
	int pos2 = sDepURL.find("/branches");
	if(pos1 != string::npos && pos2 != string::npos){
		pos = string::npos;
	}
	else if(pos1 != string::npos && pos2 == string::npos){
		pos = pos1;
	}
	else if(pos1 == string::npos && pos2 != string::npos){
		pos = pos2;
	}
	else{
		pos = string::npos;
	}

	if(string::npos != pos){
		sDepURL = sDepURL.substr(0, pos);
		memset(tDepURL, 0, sizeof(tDepURL));
		memcpy(tDepURL, sDepURL.c_str(), sDepURL.length());
		m_Kernel.SetDepURL(tDepURL);
		m_Kernel.GetCrtVersion(tDepURL);
	}
	
	return TRUE;
}

void CMergeDlg::OnBnShowLog()
{
	// TODO: Add your control notification handler code here

	m_Kernel.ClearRetMsg();

	CString cSourceURL;
	string sSourceURL;
	m_eSourcePath.GetWindowTextA(cSourceURL);
	sSourceURL = CStringToString(cSourceURL);

	int iFrom = 0;
	int pos = -1, i = 2;
	while(string::npos != (pos = sSourceURL.find("\r\n")) && 0 != pos){
		string tsDepURL = sSourceURL.substr(0, pos);

		m_Kernel.AddRetMsg((char *)tsDepURL.c_str());
		m_Kernel.AddRetMsg("\r\n\r\n");
		m_Kernel.ExeShowLog((char *)tsDepURL.c_str());
		m_Kernel.AddRetMsg("\r\n\r\n");

		if(sSourceURL.length()-pos > 2){
			sSourceURL = sSourceURL.substr(pos+2, sSourceURL.length());
		}
		else{
			break;
		}

		if(i >= __argc){
			break;
		}
	}

	CShowLogDlg ShowLogDlg;
	ShowLogDlg.m_pKernel = &m_Kernel;
	ShowLogDlg.DoModal();
}

void CMergeDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here
	if(__argc <= 2){
		CDialogEx::OnOK();
		return;
	}

	CString cFromRevision;
	CString cToRevision;
	string sFromRevision;
	string sToRevision;

	m_eFromRevision.GetWindowTextA(cFromRevision);
	m_eToRevision.GetWindowTextA(cToRevision);
	sFromRevision = CStringToString(cFromRevision);
	sToRevision = CStringToString(cToRevision);

	if(sFromRevision.length() <= 0 && sToRevision.length() <= 0){
		AfxMessageBox("Please input revision number in \"From\" or \"To\" text area");
		return;
	}

	m_ShowRetMsgDlg.Create(IDD_SHOWRETMSG_DIALOG);
	m_ShowRetMsgDlg.m_pKernel = &m_Kernel;
	m_ShowRetMsgDlg.ShowWindow(SW_SHOW);

	m_Kernel.ClearRetMsg();

	CString cSourceURL;
	string sSourceURL;
	m_eSourcePath.GetWindowTextA(cSourceURL);
	sSourceURL = CStringToString(cSourceURL);

	int iFrom = 0;
	int pos = -1, i = 2;
	while(string::npos != (pos = sSourceURL.find("\r\n")) && 0 != pos){
		string tsDepURL = sSourceURL.substr(0, pos);
		BOOL bMergeFlag;
		if(sFromRevision.length() <= 0){
			bMergeFlag = m_Kernel.ExeMerge((char *)tsDepURL.c_str(), __argv[i++], (char *)sToRevision.c_str());
		}
		else if(sToRevision.length() <= 0){
			bMergeFlag = m_Kernel.ExeMerge((char *)tsDepURL.c_str(), __argv[i++], (char *)sFromRevision.c_str());
		}
		else if(sFromRevision.length() > 0 && sToRevision.length() > 0){
			bMergeFlag = m_Kernel.ExeMerge((char *)tsDepURL.c_str(), __argv[i++], (char *)sFromRevision.c_str(), (char *)sToRevision.c_str());
		}
		m_ShowRetMsgDlg.ShowMergeMsg(iFrom, bMergeFlag);
		iFrom = m_Kernel.m_RetMsgs.size();
		if(sSourceURL.length()-pos > 2){
			sSourceURL = sSourceURL.substr(pos+2, sSourceURL.length());
		}
		else{
			break;
		}

		if(i >= __argc){
			break;
		}
	}

	if(m_Kernel.m_RetMsgs.size() <= 0){
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("nothing need to merge");
	}
	else{
		m_ShowRetMsgDlg.m_eShowRetMsg.ReplaceSel("merge completed!");
	}

	(CButton *)GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CMergeDlg::OnSelChangeFromVersion()
{
	// TODO: Add your control notification handler code here

	m_eSourcePath.SetWindowTextA("");

	CString csVersion;
	int index = m_cFromVersion.GetCurSel();
	m_cFromVersion.GetLBText(index,csVersion);

	string sVersion;
	sVersion = CStringToString(csVersion);

	char tSourceURL[255];
	string sSourceURL;
	int pos = -1, iDepURLLen = m_Kernel.m_DepURL.length();
	
	for(int i = 2; i< __argc; i++){
		memset(tSourceURL, 0, sizeof(tSourceURL));
		m_Kernel.GetWcURL(__argv[i], tSourceURL);
		sSourceURL = tSourceURL;
		RidPercent20(sSourceURL);
		if(iDepURLLen+1 == (pos = sSourceURL.find("trunk/"))){
			if(strcmp(sVersion.c_str(), "trunk/")){
				string tsVersion = "branches/" + sVersion;
				string tsSourceURL = sSourceURL;
				sSourceURL = tsSourceURL.substr(0, iDepURLLen+1);
				sSourceURL += tsVersion;
				sSourceURL += tsSourceURL.substr(iDepURLLen+7, tsSourceURL.length());
			}
		}
		else if(iDepURLLen+1 == (pos = sSourceURL.find("branches/"))){
			pos = sSourceURL.find("/", iDepURLLen+1+9);
			if(string::npos != pos){
				if(!strcmp(sVersion.c_str(), "trunk/")){
					string tsSourceURL = sSourceURL;
					sSourceURL = tsSourceURL.substr(0, iDepURLLen+1);
					sSourceURL += sVersion;
					sSourceURL += tsSourceURL.substr(pos+1, tsSourceURL.length());
				}
				else{
					string tsSourceURL = sSourceURL;
					sSourceURL = tsSourceURL.substr(0, iDepURLLen+10);
					sSourceURL += sVersion;
					sSourceURL += tsSourceURL.substr(pos+1, tsSourceURL.length());
				}
			}
		}
		else{
		}
		m_eSourcePath.ReplaceSel(sSourceURL.c_str(), 0);
		m_eSourcePath.ReplaceSel("\r\n", 0);
	}
}
