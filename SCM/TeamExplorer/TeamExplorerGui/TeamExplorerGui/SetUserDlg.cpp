// SetUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "SetUserDlg.h"
#include "afxdialogex.h"
#include "SetEnvDlg.h"
#include "Public.h"

// CSetUserDlg dialog
IMPLEMENT_DYNAMIC(CSetUserDlg, CDialogEx)

CSetUserDlg::CSetUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetUserDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
	m_ServerURL.Format(_T("%s"), "http://192.168.99.10:8081/svn/");
}

CSetUserDlg::~CSetUserDlg()
{
}

void CSetUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PASSWORD_EDIT, m_ePassword);
	DDX_Control(pDX, IDC_USERNAME_EDIT, m_eUserName);
	DDX_Control(pDX, IDC_INPUTMENTION_STATIC, m_sInputMention);
}

BEGIN_MESSAGE_MAP(CSetUserDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetUserDlg::OnBnOK)
END_MESSAGE_MAP()

// CSetUserDlg message handlers
void CSetUserDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here
	CString cUserName, cPassword;
	string sUserName, sPassword, sServerURL;

	m_eUserName.GetWindowTextA(cUserName);
	m_ePassword.GetWindowTextA(cPassword);

	sUserName = CStringToString(cUserName);
	sPassword = CStringToString(cPassword);
	sServerURL = CStringToString(m_ServerURL);

	if(sUserName.length() <= 0){
		AfxMessageBox("Please input username");
		return;
	}

	if(sPassword.length() <= 0){
		AfxMessageBox("Please input password");
		return;
	}

	if(sServerURL.length() <= 0){
		AfxMessageBox("Have no a right server url");
		return;
	}

	BOOL InputFlag = m_pKernel->IsInputRight((char *)sServerURL.c_str(), (char *)sUserName.c_str(), (char *)sPassword.c_str());
	if(!InputFlag){
		if(m_pKernel->m_SevStatusFlag){
			m_sInputMention.SetTextColor(RGB(255, 0, 0));
			m_sInputMention.SetWindowTextA("*username or password error");
			m_eUserName.SetWindowTextA("");
			m_ePassword.SetWindowTextA("");
		}
		else{
			AfxMessageBox("Please make sure that the server is starting!");
			return;
		}
	}
	else{
		if(((CSetEnvDlg *)GetParent())->m_FirstFlag){
			m_pKernel->SetUserName((char *)sUserName.c_str());
			m_pKernel->SetPassword((char *)sPassword.c_str());
			m_pKernel->SetDepURL((char *)sServerURL.c_str());
			if(!m_pKernel->SetRecordUser()){
				AfxMessageBox("the account have no permission to this depository");
				return;
			}
			((CSetEnvDlg *)GetParent())->GetDlgItem(IDOK)->EnableWindow(TRUE);
			((CSetEnvDlg *)GetParent())->m_FirstFlag = FALSE;
		}else{
			m_pKernel->SetUserName((char *)sUserName.c_str());
			m_pKernel->SetPassword((char *)sPassword.c_str());
			if(!m_pKernel->SetRecordUser()){
				AfxMessageBox("the account have no permission to this depository");
				return;
			}
		}

		CDialogEx::OnOK();
	}
}

BOOL CSetUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_sInputMention.SetTextColor(RGB(0, 0, 0));
	m_sInputMention.SetWindowTextA("Please input username and password");

	char tUrl[255];
	char tRevesion[255];
	char tLocation[255];

	memset(tUrl, 0, sizeof(tUrl));
	memset(tRevesion, 0, sizeof(tRevesion));
	memset(tLocation, 0, sizeof(tLocation));

	if(((CSetEnvDlg *)GetParent())->m_FirstFlag){
		CString cConfigFile;
		string sConfigfile;
		((CSetEnvDlg *)GetParent())->m_eConfFile.GetWindowText(cConfigFile);
		sConfigfile = CStringToString(cConfigFile);

		if(setConfigXML((char *)sConfigfile.c_str())){
			getCodeInfo(tUrl, tRevesion, tLocation);
			m_ServerURL.Format(_T("%s"), tUrl);
		}
		else{
			m_ServerURL = "";
		}

		clean();
	}
	else{
		char tServerURL[255];
		memset(tServerURL, 0, sizeof(tServerURL));
		BOOL Flag = m_pKernel->GetDepURL();
		if(Flag){
			m_ServerURL.Format(_T("%s"), m_pKernel->m_DepURL.c_str());
		}
		else{
			m_ServerURL = "";
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
