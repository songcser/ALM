
// UnlockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Unlock.h"
#include "UnlockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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

CUnlockDlg::CUnlockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUnlockDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAM_EXPLORER);

	memset(m_ConfigPath, 0, sizeof(m_ConfigPath));
	memset(m_ServerUrl, 0, sizeof(m_ServerUrl));
}

void CUnlockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REP_COMBO, m_cReps);
	DDX_Control(pDX, IDC_DIR_TREE, m_tDirTree);
	DDX_Control(pDX, IDC_FILTER_EDIT, m_eFilter);
	DDX_Control(pDX, IDC_FILE_LIST, m_lLockFiles);
}

BEGIN_MESSAGE_MAP(CUnlockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_REP_COMBO, &CUnlockDlg::OnComboSelChange)
	ON_NOTIFY(NM_CLICK, IDC_DIR_TREE, &CUnlockDlg::OnNMClickDirTree)
	ON_BN_CLICKED(IDOK, &CUnlockDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SA_BUTTON, &CUnlockDlg::OnBnSelectAll)
	ON_BN_CLICKED(IDC_NS_BUTTON, &CUnlockDlg::OnBnNotSelect)
	ON_BN_CLICKED(IDC_FILTER_BUTTON, &CUnlockDlg::OnBnFilter)
END_MESSAGE_MAP()

BOOL CUnlockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_tDirTree.ModifyStyle(0, TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS);

	m_iImageList.Create(16, 16, ILC_COLOR16, 0, 1);
	HINSTANCE hIntance=::LoadLibrary("shell32.dll");
	m_iImageList.SetBkColor(RGB(255, 255, 255));

	HICON hIcon1=(HICON)::LoadImage(hIntance, MAKEINTRESOURCE(004), IMAGE_ICON, 16, 16, 0);
	m_iImageList.Add(hIcon1);

	HICON hIcon2=(HICON)::LoadImage(hIntance, MAKEINTRESOURCE(005), IMAGE_ICON, 16, 16, 0);
	m_iImageList.Add(hIcon2);

	m_tDirTree.SetImageList(&m_iImageList, TVSIL_NORMAL);

	::FreeLibrary(hIntance);

	DWORD dwStyle = m_lLockFiles.GetExtendedStyle();
	dwStyle |= LVS_EX_CHECKBOXES;
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_lLockFiles.SetExtendedStyle(dwStyle);

	CRect rect;
	m_lLockFiles.GetClientRect(rect);
	m_lLockFiles.InsertColumn(0, "had been locked files", LVCFMT_LEFT, rect.Width()-2);

	m_TeamExplorer.GetConfigPath(m_ConfigPath);
	m_TeamExplorer.GetUserInfo(m_ConfigPath);
	m_TeamExplorer.GetServerURL(m_ConfigPath, m_ServerUrl);
	m_TeamExplorer.GetDepInfo(m_ServerUrl);

	InitialComboRep();

	return TRUE; 
}

void CUnlockDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUnlockDlg::OnPaint()
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

HCURSOR CUnlockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CUnlockDlg::InitialDirTree()
{
	m_tDirTree.DeleteAllItems();

	HTREEITEM hRoot, hTrunk, hBranches;
	hRoot = m_tDirTree.InsertItem(m_SelRepName.c_str(), 0, 1);

	for(int i = 0; i < m_TeamExplorer.m_ListRep.size(); i++){
		if(!strcmp(m_TeamExplorer.m_ListRep.at(i).c_str(), "trunk/")){
			hTrunk = m_tDirTree.InsertItem(m_TeamExplorer.m_ListRep.at(i).c_str(), 0, 1, hRoot);
		}
		if(!strcmp(m_TeamExplorer.m_ListRep.at(i).c_str(), "branches/")){
			hBranches = m_tDirTree.InsertItem(m_TeamExplorer.m_ListRep.at(i).c_str(), 0, 1, hRoot);
		}
	}

	for(int i = 0; i < m_TeamExplorer.m_ListTrunk.size(); i++){
		m_tDirTree.InsertItem(m_TeamExplorer.m_ListTrunk.at(i).c_str(), 0, 1, hTrunk);
	}

	int k = 0;
	for(int i = 0; i < m_TeamExplorer.m_ListBranches.size(); i++){
		HTREEITEM hVersion = m_tDirTree.InsertItem(m_TeamExplorer.m_ListBranches.at(i).c_str(), 0, 1, hBranches);
		while(1){
			if(k >= m_TeamExplorer.m_ListSubpro.size() || !strcmp(m_TeamExplorer.m_ListSubpro.at(k).c_str(), "|")){
				k++;
				break;
			}
			m_tDirTree.InsertItem(m_TeamExplorer.m_ListSubpro.at(k).c_str(), 0, 1, hVersion);
			k++;
		}
	}

	m_tDirTree.Expand(hRoot, TVE_EXPAND);

	return TRUE;
}

string CUnlockDlg::CStringToString(CString SourceStr)
{
	CStringA TempSourceStr(SourceStr.GetBuffer(0));
	SourceStr.ReleaseBuffer();

	string Name(TempSourceStr.GetBuffer(0));
	TempSourceStr.ReleaseBuffer();

	return Name;
}

void CUnlockDlg::InitialComboRep()
{
	int len = m_TeamExplorer.m_DepBuffer.length();
	int index = m_TeamExplorer.m_DepBuffer.find("<li>",0);

	char tDepName[255];
	memset(tDepName, 0, sizeof(tDepName));

	while(index < len){
		if((index = m_TeamExplorer.m_DepBuffer.find(">",index))==string::npos){
			break;
		}

		index++;
		int buf = 0;
		while(1){
			if (m_TeamExplorer.m_DepBuffer[index] == ' '||m_TeamExplorer.m_DepBuffer[index] == '\n'){
				index++;
			}
			else if (m_TeamExplorer.m_DepBuffer[index] == '<'){
				break;
			}
			else if (m_TeamExplorer.m_DepBuffer[index] == '/'){
				break;
			}
			else{
				tDepName[buf] = m_TeamExplorer.m_DepBuffer[index];
				index++;
				buf++;
			}
		}

		int res = strcmp(tDepName, "");
		if (res != 0){
			m_cReps.AddString(tDepName);
		}

		memset(tDepName, 0, sizeof(tDepName));
	}
}

void CUnlockDlg::InitialListLockFile(CString currentPath)
{
	m_lLockFiles.DeleteAllItems();

	vector<string> lockFiles;
	string sUrl = m_ServerUrl;
	sUrl += currentPath;

	m_TeamExplorer.GetLockFileList((char *)sUrl.c_str(), &lockFiles);

	for(int i = 0; i < lockFiles.size(); i++){
		m_lLockFiles.InsertItem(i, lockFiles.at(i).c_str());
	}
}

void CUnlockDlg::OnComboSelChange()
{
	CString cRepName;
	int index = m_cReps.GetCurSel();
	m_cReps.GetLBText(index, cRepName);
	m_SelRepName = CStringToString(cRepName);

	string url = m_ServerUrl + m_SelRepName;
	m_TeamExplorer.GetDirTree((char *)url.c_str());

	InitialDirTree();
}

void CUnlockDlg::OnNMClickDirTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	CPoint currentPoint; 
	GetCursorPos(&currentPoint); 
	m_tDirTree.ScreenToClient(&currentPoint);

	UINT uflags;
	HTREEITEM hRoot = m_tDirTree.GetRootItem();
	HTREEITEM currenthItem = m_tDirTree.HitTest(currentPoint, &uflags);
	if((currenthItem != NULL) && (TVHT_ONITEM & uflags)){
		HTREEITEM thItem;
		if(currenthItem == hRoot){
			return ;
		}
		else if((thItem = m_tDirTree.GetParentItem(currenthItem)) == hRoot){
			return ;
		}

		CString tcText = m_tDirTree.GetItemText(thItem);
		string tsText = CStringToString(tcText);
		if(!strcmp(tsText.c_str(), "branches/")){
			return ;
		}

		CString currentText = m_tDirTree.GetItemText(currenthItem);
		while(1){
			if(currenthItem != hRoot){
				currenthItem = m_tDirTree.GetParentItem(currenthItem);
				if(currenthItem == hRoot){
					currentText = m_tDirTree.GetItemText(currenthItem) + "/" + currentText;
				}
				else{
					currentText = m_tDirTree.GetItemText(currenthItem) + currentText;
				}
			}
			else{
				break;
			}
		}

		m_eFilter.SetWindowText(currentText);
		InitialListLockFile(currentText);
	}
}

void CUnlockDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	int iLockFileCount = m_lLockFiles.GetItemCount();
	vector<string> unlockFiles;
	CString cItemText;
	string sItemText;

	for(int i = 0; i < iLockFileCount; i++){
		if(m_lLockFiles.GetCheck(i)){
			cItemText = m_lLockFiles.GetItemText(i, 0);
			sItemText = CStringToString(cItemText);
			unlockFiles.push_back(sItemText);
		}
	}

	if(unlockFiles.size() > 0){
		m_TeamExplorer.Unlock(&unlockFiles);
		AfxMessageBox("The operation has completed");
	}
	else{
		AfxMessageBox("Nothing need to unlock");
	}

	//CDialogEx::OnOK();
}

void CUnlockDlg::OnBnSelectAll()
{
	// TODO: Add your control notification handler code here

	int iLockFileCount = m_lLockFiles.GetItemCount();
	for(int i = 0; i < iLockFileCount; i++){
		if(!m_lLockFiles.GetCheck(i)){
			m_lLockFiles.SetCheck(i);
		}
	}
}

void CUnlockDlg::OnBnNotSelect()
{
	// TODO: Add your control notification handler code here

	int iLockFileCount = m_lLockFiles.GetItemCount();
	for(int i = 0; i < iLockFileCount; i++){
		if(m_lLockFiles.GetCheck(i)){
			m_lLockFiles.SetCheck(i, 0);
		}
	}
}

void CUnlockDlg::OnBnFilter()
{
	// TODO: Add your control notification handler code here

	CString cFilterPath;
	m_eFilter.GetWindowText(cFilterPath);

	InitialListLockFile(cFilterPath);
}
