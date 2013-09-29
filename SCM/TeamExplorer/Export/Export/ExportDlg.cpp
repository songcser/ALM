
// ExportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Export.h"
#include "ExportDlg.h"
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

// CExportDlg dialog
CExportDlg::CExportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExportDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TEAMEXPLORER);

	memset(m_ConfigPath, 0, sizeof(m_ConfigPath));
	memset(m_ServerUrl, 0, sizeof(m_ServerUrl));

	m_RetMessage = "";
}

void CExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REP_COMBO, m_cReps);
	DDX_Control(pDX, IDC_DIR_TREE, m_tDirTree);
	DDX_Control(pDX, IDC_REPPATHEDIT, m_eSourcePath);
	DDX_Control(pDX, IDC_LOCALPATH_EDIT, m_eDestPath);
}

BEGIN_MESSAGE_MAP(CExportDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_REP_COMBO, &CExportDlg::OnComboSelChange)
	ON_NOTIFY(NM_CLICK, IDC_DIR_TREE, &CExportDlg::OnNMClickDirTree)
	ON_BN_CLICKED(IDC_SELLOCALPATH_BUTTON, &CExportDlg::OnBnSelLocalPath)
	ON_BN_CLICKED(IDOK, &CExportDlg::OnBnExport)
END_MESSAGE_MAP()


// CExportDlg message handlers

BOOL CExportDlg::OnInitDialog()
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

	m_TeamExplorer.GetConfigPath(m_ConfigPath);
	m_TeamExplorer.GetUserInfo(m_ConfigPath);
	m_TeamExplorer.GetServerURL(m_ConfigPath, m_ServerUrl);
	m_TeamExplorer.GetDepInfo(m_ServerUrl);

	InitialComboRep();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExportDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExportDlg::OnPaint()
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
HCURSOR CExportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CExportDlg::InitialDirTree()
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

string CExportDlg::CStringToString(CString SourceStr)
{
	CStringA TempSourceStr(SourceStr.GetBuffer(0));
	SourceStr.ReleaseBuffer();

	string Name(TempSourceStr.GetBuffer(0));
	TempSourceStr.ReleaseBuffer();

	return Name;
}

void CExportDlg::InitialComboRep()
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

void CExportDlg::OnComboSelChange()
{
	// TODO: Add your control notification handler code here

	CString cRepName;
	int index = m_cReps.GetCurSel();
	m_cReps.GetLBText(index, cRepName);
	m_SelRepName = CStringToString(cRepName);

	string url = m_ServerUrl + m_SelRepName;
	m_TeamExplorer.GetDirTree((char *)url.c_str());

	InitialDirTree();
}

void CExportDlg::OnNMClickDirTree(NMHDR *pNMHDR, LRESULT *pResult)
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
			CString tcText = m_tDirTree.GetItemText(currenthItem);
			string tsText = CStringToString(tcText);
			if(strcmp(tsText.c_str(), "trunk/")){
				return ;
			}
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

		m_eSourcePath.SetWindowText(currentText);
	}
}

void CExportDlg::OnBnSelLocalPath()
{
	// TODO: Add your control notification handler code here

	LPITEMIDLIST rootLoation;
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &rootLoation);
	if (rootLoation == NULL){
		return ;
	}
	
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	bi.pidlRoot = rootLoation;
	bi.lpszTitle = _T("Please select destination path");

	LPITEMIDLIST targetLocation = SHBrowseForFolder(&bi);
	if(targetLocation != NULL){
		TCHAR targetPath[MAX_PATH];
		SHGetPathFromIDList(targetLocation, targetPath);
		m_eDestPath.SetWindowText(targetPath);
	}
}

DWORD WINAPI ThreadCallBack(LPVOID lpParamter)
{
	CExportDlg * pExportDlg = (CExportDlg *)lpParamter;
	pExportDlg->Export();
	pExportDlg->EndMultiThread();

	return 0;
}

BOOL CExportDlg::BeginMultiThread()
{
	HANDLE hThread = CreateThread(NULL, 0, ThreadCallBack, (LPVOID)this, 0, NULL);

	CloseHandle(hThread);

	m_ProgressDlg.DoModal();

	return TRUE;
}

BOOL CExportDlg::EndMultiThread()
{
	while(1){
		Sleep(2);
		if(m_ProgressDlg.m_hWnd != NULL){
			m_ProgressDlg.PostMessage(WM_END_MESSAGE);
			break;
		}
	}

	return TRUE;
}

void CExportDlg::OnBnExport()
{
	// TODO: Add your control notification handler code here

	CString cSourcePath;
	CString cDestPath;
	m_eSourcePath.GetWindowText(cSourcePath);
	m_eDestPath.GetWindowTextA(cDestPath);

	if("" == cSourcePath){
		AfxMessageBox("source path is null");
		return;
	}

	if("" == cDestPath){
		AfxMessageBox("destination path is null");
		return;
	}

	BeginMultiThread();

	m_ShowMessageDlg.m_Message = m_RetMessage;
	m_ShowMessageDlg.DoModal();

	CDialogEx::OnOK();
}

void CExportDlg::Export()
{
	string sSourceUrl = m_ServerUrl;
	CString cSourcePath;
	string sSourcePath;
	m_eSourcePath.GetWindowText(cSourcePath);
	sSourcePath = CStringToString(cSourcePath);
	sSourceUrl += sSourcePath;

	CString cDestPath;
	string sDestPath;
	m_eDestPath.GetWindowTextA(cDestPath);
	sDestPath = CStringToString(cDestPath);

	m_RetMessage = m_TeamExplorer.Export(sSourceUrl, sDestPath);
}