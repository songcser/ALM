// SelectDepDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "SelectDepDlg.h"
#include "afxdialogex.h"
#include "Public.h"
#include "SetEnvDlg.h"

// CSelectDepDlg dialog
IMPLEMENT_DYNAMIC(CSelectDepDlg, CDialogEx)

CSelectDepDlg::CSelectDepDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSelectDepDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER_ICON);
	m_ServerURL.Format(_T("%s"), "http://192.168.99.10:8081/svn/");
	m_DepName = "";
}

CSelectDepDlg::~CSelectDepDlg()
{
}

void CSelectDepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEP_LIST, m_lDepList);
}

BEGIN_MESSAGE_MAP(CSelectDepDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSelectDepDlg::OnBnOK)
	ON_NOTIFY(NM_CLICK, IDC_DEP_LIST, &CSelectDepDlg::OnNMClickDepList)
END_MESSAGE_MAP()

// CSelectDepDlg message handlers
void CSelectDepDlg::OnBnOK()
{
	// TODO: Add your control notification handler code here
	
	if(m_DepName.length() <= 0){
		AfxMessageBox("Please select a depository");
		return;
	}

	string sServerURL;
	sServerURL = CStringToString(m_ServerURL);

	char tServerURL[255];
	memset(tServerURL, 0, sizeof(tServerURL));
	memcpy(tServerURL, sServerURL.c_str(), sServerURL.length());

	char tDepURL[255];
	memset(tDepURL, 0, sizeof(tDepURL));
	memcpy(tDepURL, (sServerURL+m_DepName).c_str(), ((sServerURL+m_DepName)).length());

	if(((CSetEnvDlg *)GetParent())->m_FirstFlag){
		m_pKernel->SetDepURL(tDepURL);

		if(!m_pKernel->FirstSelectDep()){
			AfxMessageBox("select depository failed, open configure file failed");
			return;
		}

		((CSetEnvDlg *)GetParent())->m_FirstFlag = FALSE;
		((CSetEnvDlg *)GetParent())->GetDlgItem(IDC_SETUSER_BUTTON)->EnableWindow(TRUE);
		//((CSetEnvDlg *)GetParent())->m_InitFlag = ((CSetEnvDlg *)GetParent())->InitDepTree();

		m_pKernel->SaveServerURL((char *)m_pKernel->m_ConfigPath.c_str(), tServerURL);
	}
	else{
		m_pKernel->SetDepURL(tDepURL);

		if(!m_pKernel->ChangeDep()){
			AfxMessageBox("change depository failed, open configure file failed");
			return;
		}

		//((CSetEnvDlg *)GetParent())->m_tDepTree.DeleteAllItems();
		//((CSetEnvDlg *)GetParent())->m_InitFlag = ((CSetEnvDlg *)GetParent())->InitDepTree();
	}
	
	CDialogEx::OnOK();
}

BOOL CSelectDepDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	if(((CSetEnvDlg *)GetParent())->m_FirstFlag || ((CSetEnvDlg *)GetParent())->m_AdvanceFlag){
		m_ServerURL.Format(_T("%s"), ((CSetEnvDlg *)GetParent())->m_ServerURL);
	}
	else{
		char tServerURL[255];
		memset(tServerURL, 0, sizeof(tServerURL));
		BOOL Flag = m_pKernel->GetServerURL((char *)m_pKernel->m_ConfigPath.c_str(), tServerURL);
		if(Flag){
			m_ServerURL.Format(_T("%s"), tServerURL);
		}
	}

	CRect rect;
	m_lDepList.GetClientRect(rect);
	m_lDepList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_lDepList.InsertColumn(0, "Depositories Name", LVCFMT_CENTER, rect.Width()/2, 0);

	string sServerURL = CStringToString(m_ServerURL);
	if(((CSetEnvDlg *)GetParent())->m_FirstFlag){
		m_pKernel->GetDepInfo("http://192.168.99.10:8081/svn/", (char *)m_pKernel->m_UserName.c_str(), (char *)m_pKernel->m_Password.c_str());
		m_pKernel->GetDepInfo((char *)sServerURL.c_str(), (char *)m_pKernel->m_UserName.c_str(), (char *)m_pKernel->m_Password.c_str());
	}
	else{
		if(!m_pKernel->GetUserInfo()){
			return TRUE;
		}

		m_pKernel->GetDepInfo("http://192.168.99.10:8081/svn/", (char *)m_pKernel->m_UserName.c_str(), (char *)m_pKernel->m_Password.c_str());
		m_pKernel->GetDepInfo((char *)sServerURL.c_str(), (char *)m_pKernel->m_UserName.c_str(), (char *)m_pKernel->m_Password.c_str());
	}

	InitialListDep();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectDepDlg::InitialListDep()
{
	int len = m_pKernel->m_DepBuffer.length();
	int index = m_pKernel->m_DepBuffer.find("<li>",0);

	char tDepName[255];
	memset(tDepName, 0, sizeof(tDepName));

	int nItem = 0;
	while(index < len){
		if((index = m_pKernel->m_DepBuffer.find(">",index))==string::npos){
			break;
		}

		index++;
		int buf = 0;
		while(1){
			if (m_pKernel->m_DepBuffer[index] == ' '||m_pKernel->m_DepBuffer[index] == '\n'){
				index++;
			}
			else if (m_pKernel->m_DepBuffer[index] == '<'){
				break;
			}
			else if (m_pKernel->m_DepBuffer[index] == '/'){
				break;
			}
			else{
				tDepName[buf] = m_pKernel->m_DepBuffer[index];
				index++;
				buf++;
			}
		}

		int res = strcmp(tDepName, "");
		if (res != 0){
			m_lDepList.InsertItem(nItem, tDepName);
		}
		memset(tDepName, 0, sizeof(tDepName));
	}
}

void CSelectDepDlg::OnNMClickDepList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;

	if (-1!=pNMListView->iItem)
	{
		m_DepName = m_lDepList.GetItemText(pNMListView->iItem,0);
	}
}
