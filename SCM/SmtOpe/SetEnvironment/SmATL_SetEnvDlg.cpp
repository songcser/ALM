
// SmATL_SetEnvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SmATL_SetEnv.h"
#include "SmATL_SetEnvDlg.h"
#include "afxdialogex.h"
//#include "direct.h"
//#include "SmPubFun.h"
//#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
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


// CSmATL_SetEnvDlg dialog




CSmATL_SetEnvDlg::CSmATL_SetEnvDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmATL_SetEnvDlg::IDD, pParent)
	
{
	memset(m_ProjectName,0,sizeof(m_ProjectName));
	m_IsCleanLogin = FALSE;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmATL_SetEnvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_URL_REPOSITORY_EDIT, m_URL_Repository);
	DDX_Control(pDX, IDC_PATH_WORKCOPY_EDIT, m_Path_WorkCopy);
	DDX_Control(pDX, IDC_TREE1, m_treeCtrl);
	DDX_Control(pDX, IDC_CLEAN_BUTTON, m_CleanLoginBtn);
	//  DDX_Control(pDX, IDC_CHECK1, m_CheckBox);
	DDX_Control(pDX, IDC_EDIT1, m_Product);
	DDX_Control(pDX, IDC_CHECK1, m_CheckBox);
}

BEGIN_MESSAGE_MAP(CSmATL_SetEnvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CSmATL_SetEnvDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CSmATL_SetEnvDlg::OnBnClickedOk)
//	ON_WM_CLOSE()
//ON_WM_DESTROY()
//ON_BN_CLICKED(IDC_BUTTON1, &CSmATL_SetEnvDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_PROJECT_BUTTON, &CSmATL_SetEnvDlg::OnBnClickedProjectButton)
//ON_BN_CLICKED(IDC_BUTTON2, &CSmATL_SetEnvDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_CLEAN_BUTTON, &CSmATL_SetEnvDlg::OnBnClickedCleanButton)
//ON_BN_CLICKED(IDC_BUTTON1, &CSmATL_SetEnvDlg::OnBnClickedButton1)
//ON_BN_CLICKED(IDC_CHANGEPRODUCTPATH_BUTTON, &CSmATL_SetEnvDlg::OnBnClickedChangeproductpathButton)
END_MESSAGE_MAP()


// CSmATL_SetEnvDlg message handlers

BOOL CSmATL_SetEnvDlg::OnInitDialog()
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
	//m_URL_Repository.SetWindowTextA("http://192.168.99.10:8081/svn/test");
	m_URL_Repository =  "http://192.168.99.10:8081/svn/test";
	m_Path_WorkCopy.SetWindowTextA(__argv[1]);

	char tempPath[255];
	memset(tempPath,0,sizeof(tempPath));
	m_ProductPath = __argv[1];
	int index = m_ProductPath.find_last_of('\\');
	int num = m_ProductPath.length() - index;
	m_ProductPath.erase(index,num);
	m_ProductPath +=  "\\products.rely";

	m_CheckBox.SetCheck(1);
	m_Product.SetWindowTextA(m_ProductPath.c_str());

	strcpy(m_ProjectName,"test");
	//m_result = FALSE;
	GetCongifPath();
	
	IsLogin();

	//GetProjectName();

	m_treeCtrl.ModifyStyle(0,TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS);
	GetListView();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSmATL_SetEnvDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSmATL_SetEnvDlg::OnPaint()
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
HCURSOR CSmATL_SetEnvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSmATL_SetEnvDlg::ChangeProjectName()
{
	char tempPath[255];
	memset(tempPath,0,sizeof(tempPath));

	char projectName[255];
	memset(projectName,0,sizeof(projectName));
	int index = 0;
	index = m_URL_Repository.find_last_of("/");

	if (index != string::npos)
	{
		//int len = m_URL_Repository.length()-index;
		m_URL_Repository.copy(tempPath,index+1,0);
		strcat(tempPath,m_ProjectName);
		m_URL_Repository = tempPath;
	}
	//int length = m_URL_Repository.length()-strlen(m_ProjectName);


}

void CSmATL_SetEnvDlg::GetProjectName()
{

	int index = 0;
	index = m_URL_Repository.find_last_of("/");
	memset(m_ProjectName,0,sizeof(m_ProjectName));
	int length;
	if (index != string::npos)
	{
		length = m_URL_Repository.length()-index;
		m_URL_Repository.copy(m_ProjectName,length,index+1);
	}
}

void CSmATL_SetEnvDlg::GetProjectNameFromFile()
{
	string filePath = m_congifPath;
	filePath += "\\auth\\ProjectName.tmp";

	if (!PathFileExists(filePath.c_str()))
	{
		strcpy(m_ProjectName,"test");
		return;
	}

	FILE *file;
	file = fopen(filePath.c_str(),"r");
	
	char tempPath[255];
	memset(tempPath,0,sizeof(tempPath));

	if (fread(tempPath,1,sizeof(tempPath),file) != sizeof(tempPath))
	{
		AfxMessageBox("read file error");
	}
	m_URL_Repository = tempPath;
	GetProjectName();

	fclose(file);
}
void CSmATL_SetEnvDlg::GetCongifPath()
{
	//string congifPath;
	char userName[255];
	memset(userName,0,sizeof(userName));
	DWORD NameNum = sizeof(userName);
	GetUserName(userName,&NameNum);

	OSVERSIONINFO osvi;
	ZeroMemory(&osvi,sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osvi);

	switch(osvi.dwPlatformId)
	{
	case VER_PLATFORM_WIN32_NT:
		if (osvi.dwMajorVersion == 5&& osvi.dwMinorVersion == 1)
		{
			m_congifPath = "C:\\Documents and Settings\\";
		}
		else if (osvi.dwMajorVersion == 6&& osvi.dwMinorVersion == 1)
		{
			m_congifPath = "C:\\users\\";
		}
		else
		{
			AfxMessageBox("Windows Version is ERROR");
		}
		break;
	default:
		AfxMessageBox("Windows Version is ERROR");
	}

	m_congifPath += userName;
	m_congifPath += "\\Application Data\\Subversion";

	if (PathFileExists(m_congifPath.c_str()))
	{
		string configPath = m_congifPath;
		configPath += "\\auth\\svn.simple\\b7e1baeb3e2c3bdb4ddd982957d6ccd3";
		if (PathFileExists(configPath.c_str()))
		{
			//m_CleanLoginBtn.ModifyStyle(WS_DISABLED,0);
			//m_CleanLoginBtn.EnableWindow(TRUE);
			GetProjectNameFromFile();
			m_firstLogin = FALSE;
		}
		else
		{
			GetProjectName();
			m_firstLogin = TRUE;
		}
	}
	else
	{
		GetProjectName();
		m_firstLogin = TRUE;
	}
}

void CSmATL_SetEnvDlg::IsLogin()
{
	char ListCmd[255];
	memset(ListCmd,0,sizeof(ListCmd));

	if (m_firstLogin)
	{
		//GetProjectName();
		//string configFile = m_congifPath;
		//configFile += "\\auth\\svn.simple\\b7e1baeb3e2c3bdb4ddd982957d6ccd3";

		//CString strName;
		//CString strPassword;
		string Name;
		string Password;

		BOOL IsInputError = TRUE;
		while(IsInputError)
		{

		
			int res = m_Login.DoModal();
			if ( res == IDOK)
			{
				Name = CStringToString(m_Login.m_strName);
				Password = CStringToString(m_Login.m_strPassword);
			}
			else if (res == IDCANCEL)
			{
				exit(0);
				return;
			}
			//Name = CStringToString(strName);
			//Password = CStringToString(strPassword);
			ChangeProjectName();
			sprintf_s(ListCmd,"svn list -R --non-interactive --username %s --password %s \"%s\"",Name.c_str(),Password.c_str(),m_URL_Repository.c_str());
			//AfxMessageBox(ListCmd);
			m_strRet = ExeCmd(ListCmd);

			char tmpRet[255];
			memset(tmpRet,0,sizeof(tmpRet));
			sprintf_s(tmpRet,"Access to \'%s\' forbidden",m_URL_Repository.c_str());
			char inputError[255];
			memset(inputError,0,sizeof(inputError));
			sprintf_s(inputError,"svn: E170001:");
			if (m_strRet.find(tmpRet,0)!=string::npos)
			{
				AfxMessageBox("Permission Denied!");
				continue;
				//	return;
			}
			if (m_strRet.find(inputError,0)!=string::npos)
			{
				AfxMessageBox("Input username or password error");
				continue;
			}
			IsInputError = FALSE;

		}
		string filePath = m_congifPath;
		filePath += "\\auth\\ProjectName.tmp";

		FILE *file;
		file = fopen(filePath.c_str(),"w");

		char tempPath[255];
		memset(tempPath,0,sizeof(tempPath));
		strcpy(tempPath,m_URL_Repository.c_str());
		if (fwrite(tempPath,1,sizeof(tempPath),file)!= sizeof(tempPath))
		{
			AfxMessageBox("write temp file error");
			return;
		}
		
		fclose(file);

		m_CleanLoginBtn.EnableWindow(TRUE);
	}
	else
	{
		//GetProjectNameFromFile();
		string filePath = m_congifPath;
		filePath += "\\auth\\ProjectName.tmp";
		if (!PathFileExists(filePath.c_str()))
		{
			FILE *file;
			file = fopen(filePath.c_str(),"w");

			char tempPath[255];
			memset(tempPath,0,sizeof(tempPath));
			strcpy(tempPath,m_URL_Repository.c_str());
			if (fwrite(tempPath,1,sizeof(tempPath),file)!= sizeof(tempPath))
			{
				AfxMessageBox("write temp file error");
				return;
			}

			fclose(file);

			m_CleanLoginBtn.EnableWindow(FALSE);
		}
		ChangeProjectName();
		sprintf_s(ListCmd,"svn list -R \"%s\"",m_URL_Repository.c_str());
		m_strRet = ExeCmd(ListCmd);
	}
}

void CSmATL_SetEnvDlg::GetListView()
{
	string strRet;
	
	//CString strTemp;
	string strTmp;

	strTmp = m_URL_Repository;

//	AfxMessageBox(strTemp);
	
	HTREEITEM root;
	root = m_treeCtrl.InsertItem(m_ProjectName);
	//CString CStr = strRet.c_str();
	//MessageBoxA(CStr);
	
	int num=0;
	int numLast =0;
	string TreeItem[3];
	string ItemBackup[3];
	//memset(TreeItem,0,sizeof(TreeItem));
	//memset(ItemBackup,0,sizeof(ItemBackup));

	while(num < (int)m_strRet.length())
	{
		for(int i=0;i<3;i++)
		{
			ItemBackup[i] = TreeItem[i];
			TreeItem[i] = "";
		}
		int numTemp;
		numTemp = m_strRet.find('\n',num);
		
		string strSub = m_strRet.substr(num,numTemp-num-1);

		int MaxNum = 0;
		if (strSub.find("branches",0)!=string::npos)
		{
			MaxNum = 3;
		}
		else if (strSub.find("trunk",0) != string::npos&&strSub.find("products") == string::npos)
		{
			MaxNum = 2;
		}
		/*
		else if(strSub.find("products") != string::npos)
		{
			MaxNum = 3;
		}
		*/
		int numSub = 0;
		int count = 0;
		while(numSub<numTemp-numLast)
		{
			int subTemp =0;
			subTemp = strSub.find('/',numSub);
			
			if (subTemp<0||count>=MaxNum)
			{
				break;
			}
			string strItem = strSub.substr(numSub,subTemp-numSub);
			if (TreeItem[count]!= strItem)
			{
				TreeItem[count] = strItem;
			}
			
			count++;
			//strSub = subTemp;
			numSub = subTemp + 1;
		}
		numLast = numTemp;

		//HTREEITEM root;
		HTREEITEM parent;
		HTREEITEM child[3];
		for(int i=0;i<3;i++)
		{
			if (TreeItem[i]=="\0")
			{
				break;
			}
			if (TreeItem[i] != ItemBackup[i]&&TreeItem[i]!= "tags")
			{
				if (i==0)
				{
					parent = m_treeCtrl.InsertItem(TreeItem[i].c_str(),root);
				}
				else if(i==1)
				{
					child[i] = m_treeCtrl.InsertItem(TreeItem[i].c_str(),parent);
				}
				else
				{
					child[i] = m_treeCtrl.InsertItem(TreeItem[i].c_str(),child[i-1],NULL);
				}
			}
			
		}
		num = numTemp+1;
	}
	
}


void CSmATL_SetEnvDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here


	if (PathFileExists(m_ProductPath.c_str()))
	{
		int index = AfxMessageBox("The path of product has already existed.\nIf you click OK, the original products to be replace !\ndo you want to continue?",MB_OKCANCEL);
		if (index == IDCANCEL)
		{
			return;
		}
	}

	if (m_IsCleanLogin)
	{
		//m_treeCtrl.DeleteAllItems();

		GetCongifPath();

		//GetProjectName();

		IsLogin();
		//GetListView();

		m_IsCleanLogin = FALSE;

		//return;
	}

	HTREEITEM root = m_treeCtrl.GetRootItem();
	HTREEITEM hSelectedItem = m_treeCtrl.GetSelectedItem();

	string RetStr;
	if (hSelectedItem == NULL)
	{
		//DestroyWindow();
		if(AfxMessageBox("Export Nothing, Set Environment Error") == IDOK)
		{
			return;
		}
	}
	string pathStr[100];
	int num =0;

	if (__argc<=1)
	{
		AfxMessageBox("Don't input your Workcopy Driectory");
		return;
	}

	string sourcesPath = m_URL_Repository;
	string destinationPath(__argv[1]);
	//CString strtmp ;
	//m_Path_WorkCopy.GetWindowTextA(strtmp);
	//destinationPath = CStringToString(strtmp);

	

	while (root != hSelectedItem )
	{
		pathStr[num] = m_treeCtrl.GetItemText(hSelectedItem);
		hSelectedItem = m_treeCtrl.GetParentItem(hSelectedItem);
		num++;
	}
	num--;
	for (; num>=0 ; num--)
	{
		sourcesPath.append(1,'/');
		sourcesPath.append(pathStr[num]);
	}
	//string tempPath = sourcesPath + "/branches";
	if (sourcesPath.compare(m_URL_Repository) == 0||sourcesPath.compare(m_URL_Repository+"/branches") == 0||
		   sourcesPath.compare(m_URL_Repository+"/products")==0)
	{
		AfxMessageBox("Can't Export this Folder");
		return;
	}
	char ExportCmd[255];
	memset(ExportCmd,0,sizeof(ExportCmd));
	sprintf_s(ExportCmd,"svn export --force \"%s\" \"%s\"",sourcesPath.c_str(),destinationPath.c_str());
	RetStr = ExeCmd(ExportCmd);


	string sourceTemp = sourcesPath;
	sourceTemp.append(255-sourcesPath.length(),'\0');
	string filePath = destinationPath;
	filePath.append(1,'\\');
	filePath.append("SmtRec.dat");



	CFile mFile;

	if(mFile.Open(filePath.c_str(),CFile::modeWrite|CFile::modeCreate)==0)
	{
		AfxMessageBox("open error");
	}

	mFile.Write(sourceTemp.c_str(),255);
	mFile.Flush();
	mFile.Close();

	if (!SetFileAttributes(filePath.c_str(),FILE_ATTRIBUTE_HIDDEN))
	{
		AfxMessageBox("Dat file not hidden");
		CDialogEx::OnOK();
		return;
	}
/*
	int trunkIndex = sourcesPath.find("trunk",0);
	int branchesIndex = sourcesPath.find("branches",0);
	int productsIndex = sourcesPath.find("products",0);

	string sourcesTemp = sourcesPath;
	string destinationTemp = destinationPath + "\\products.rely";

	if (trunkIndex != string::npos&&branchesIndex == string::npos)
	{
		if (productsIndex != string::npos&&productsIndex<trunkIndex)
		{
			m_ShowLog.ShowLog((char *)RetStr.c_str());

			if (m_ShowLog.DoModal() == IDOK)
			{
				CDialogEx::OnOK();
			}
			return;
		}
		char *product = "products/";

		sourcesTemp.insert(trunkIndex,product);

		string strTemp = sourcesTemp;
		int lastIndex = strTemp.find_last_of('/');
		strTemp.erase(lastIndex,sourcesTemp.length()-lastIndex);
		//strTemp[lastIndex] = 0;
		int findindex = strTemp.find("trunk");
		if (findindex!=string::npos)
		{
			sourcesTemp = strTemp;
		}
	}
	else if (trunkIndex == string::npos&&branchesIndex != string::npos)
	{
		char *product = "products";

		sourcesTemp.replace(branchesIndex,strlen(product),product);

		
		string strTemp = sourcesTemp;
		int lastIndex = strTemp.find_last_of('/');
		strTemp.erase(lastIndex,sourcesTemp.length()-lastIndex);
		//strTemp[lastIndex] = 0;
		int firstIndex = sourcesTemp.find("products");
		if (lastIndex != firstIndex+8)
		{
			sourcesTemp = strTemp;
		}
		
	}
	else if (trunkIndex == string::npos&&branchesIndex == string::npos)
	{
		//AfxMessageBox("Export products error");
		m_ShowLog.ShowLog((char *)RetStr.c_str());
		//m_ShowLog.ShowWindow(SW_SHOW);
		//m_ShowLog.ShowLog((char *)RetStr.c_str());
		if (m_ShowLog.DoModal() == IDOK)
		{
			CDialogEx::OnOK();
		}
		return;
	}
	else if (trunkIndex > branchesIndex)
	{
		char *product = "products";

		sourcesTemp.replace(branchesIndex,strlen(product),product);


		string strTemp = sourcesTemp;
		int lastIndex = strTemp.find_last_of('/');
		strTemp.erase(lastIndex,sourcesTemp.length()-lastIndex);
		//strTemp[lastIndex] = 0;
		int firstIndex = sourcesTemp.find("products");
		if (lastIndex != firstIndex+9)
		{
			sourcesTemp = strTemp;
		}
	}
	else if (trunkIndex < branchesIndex)
	{
		char *product = "products/";

		sourcesTemp.insert(trunkIndex,product);

		string strTemp = sourcesTemp;
		int lastIndex = strTemp.find_last_of('/');
		strTemp.erase(lastIndex,sourcesTemp.length()-lastIndex);
		//strTemp[lastIndex] = 0;
		if (strTemp.find("trunk")!=string::npos)
		{
			sourcesTemp = strTemp;
		}
	}

	memset(ExportCmd,0,sizeof(ExportCmd));
	sprintf_s(ExportCmd,"svn export --force \"%s\" \"%s\"",sourcesTemp.c_str(),destinationTemp.c_str());

	string RetStrTemp =  "Export rely file: \r\n";
	RetStrTemp += ExeCmd(ExportCmd);

	if (RetStrTemp.find("svn E720003:")!=string::npos||RetStrTemp.find("svn E170000:")!=string::npos)
	{
		RetStrTemp = "Can't find Products file";
	}
	
	RetStr += RetStrTemp;
	//AfxMessageBox(CString(ExportCmd));
	*/

//	if (m_CheckBox.GetCheck())
	{
		RetStr += SetProductPath(sourcesPath);
	}
	
	//m_ShowLog.m_showLog.SetWindowTextA(RetStr.c_str());
	m_ShowLog.ShowLog((char *)RetStr.c_str());
	//m_ShowLog.ShowWindow(SW_SHOW);
	//m_ShowLog.ShowLog((char *)RetStr.c_str());
	if (m_ShowLog.DoModal() == IDOK)
	{
		CDialogEx::OnOK();
	}
	//AfxMessageBox(RetStr.c_str());
	CDialogEx::OnOK();
}

string CSmATL_SetEnvDlg::SetProductPath(string sourcesPath)
{
	int trunkIndex = sourcesPath.find("trunk",0);
	int branchesIndex = sourcesPath.find("branches",0);
	int productsIndex = sourcesPath.find("products",0);

	string sourcesTemp = sourcesPath;

	string destinationTemp = m_ProductPath ;

	

	if (trunkIndex != string::npos&&branchesIndex == string::npos)
	{
		if (productsIndex != string::npos&&productsIndex<trunkIndex)
		{
			/*
			m_ShowLog.ShowLog((char *)RetStr.c_str());

			if (m_ShowLog.DoModal() == IDOK)
			{
				CDialogEx::OnOK();
			}*/

			return "";
		}
		char *product = "products/";

		sourcesTemp.insert(trunkIndex,product);

		string strTemp = sourcesTemp;
		int lastIndex = strTemp.find_last_of('/');
		strTemp.erase(lastIndex,sourcesTemp.length()-lastIndex);
		//strTemp[lastIndex] = 0;
		int findindex = strTemp.find("trunk");
		if (findindex!=string::npos)
		{
			sourcesTemp = strTemp;
		}
	}
	else if (trunkIndex == string::npos&&branchesIndex != string::npos)
	{
		char *product = "products";

		sourcesTemp.replace(branchesIndex,strlen(product),product);


		string strTemp = sourcesTemp;
		int lastIndex = strTemp.find_last_of('/');
		strTemp.erase(lastIndex,sourcesTemp.length()-lastIndex);
		//strTemp[lastIndex] = 0;
		int firstIndex = sourcesTemp.find("products");
		if (lastIndex != firstIndex+8)
		{
			sourcesTemp = strTemp;
		}

	}
	else if (trunkIndex == string::npos&&branchesIndex == string::npos)
	{
		//AfxMessageBox("Export products error");
		//m_ShowLog.ShowLog((char *)RetStr.c_str());
		//m_ShowLog.ShowWindow(SW_SHOW);
		//m_ShowLog.ShowLog((char *)RetStr.c_str());
		/*if (m_ShowLog.DoModal() == IDOK)
		{
			CDialogEx::OnOK();
		}*/
		return "";
	}
	else if (trunkIndex > branchesIndex)
	{
		char *product = "products";

		sourcesTemp.replace(branchesIndex,strlen(product),product);


		string strTemp = sourcesTemp;
		int lastIndex = strTemp.find_last_of('/');
		strTemp.erase(lastIndex,sourcesTemp.length()-lastIndex);
		//strTemp[lastIndex] = 0;
		int firstIndex = sourcesTemp.find("products");
		if (lastIndex != firstIndex+9)
		{
			sourcesTemp = strTemp;
		}
	}
	else if (trunkIndex < branchesIndex)
	{
		char *product = "products/";

		sourcesTemp.insert(trunkIndex,product);

		string strTemp = sourcesTemp;
		int lastIndex = strTemp.find_last_of('/');
		strTemp.erase(lastIndex,sourcesTemp.length()-lastIndex);
		//strTemp[lastIndex] = 0;
		if (strTemp.find("trunk")!=string::npos)
		{
			sourcesTemp = strTemp;
		}
	}

	char ExportCmd[255];
	memset(ExportCmd,0,sizeof(ExportCmd));
	sprintf_s(ExportCmd,"svn export --force \"%s\" \"%s\"",sourcesTemp.c_str(),destinationTemp.c_str());

	string RetStrTemp =  "Export rely file: \r\n";
	RetStrTemp += ExeCmd(ExportCmd);

	if (RetStrTemp.find("svn: E720003:")!=string::npos||RetStrTemp.find("svn: E170000:")!=string::npos)
	{
		RetStrTemp = "Can't find Products file";
		//return RetStrTemp;
	}

	if (!PathFileExists(m_ProductPath.c_str()))
	{
		mkdir(m_ProductPath.c_str());
	}
	string Temp = sourcesTemp;
	Temp.append(255-sourcesPath.length(),'\0');

	CFile mFile;
	string filePath = m_ProductPath + "\\SmtRec.dat";
	if (PathFileExists(filePath.c_str()))
	{
		while(remove(filePath.c_str()));
	}
	if(mFile.Open(filePath.c_str(),CFile::modeWrite|CFile::modeCreate)==0)
	{
		AfxMessageBox("open error");
	}

	mFile.Write(Temp.c_str(),255);
	mFile.Flush();
	mFile.Close();

	if (!SetFileAttributes(filePath.c_str(),FILE_ATTRIBUTE_HIDDEN))
	{
		AfxMessageBox("dat file not hidden");
		CDialogEx::OnOK();
		return "";
	}

	return RetStrTemp;
}

string CSmATL_SetEnvDlg::CStringToString(CString SourceStr)
{
	CStringA TempSourceStr(SourceStr.GetBuffer(0));
	SourceStr.ReleaseBuffer();

	string Name(TempSourceStr.GetBuffer(0));
	TempSourceStr.ReleaseBuffer();

	return Name;
}

string CSmATL_SetEnvDlg::ExeCmd(char *pszCmd)
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
	//	CloseHandle(sii.hStdError);
	//	CloseHandle(sii.hStdInput);
	//	CloseHandle(sii.hStdOutput);

	return strRet;
}


void CSmATL_SetEnvDlg::OnBnClickedProjectButton()
{
	// TODO: Add your control notification handler code here
	if (m_ProjectPathDlg.DoModal() == IDOK)
	{
		m_treeCtrl.DeleteAllItems();

		string projectName;
		projectName = CStringToString(m_ProjectPathDlg.m_strPath);
		

		int len = projectName.length();
		if (projectName[len-1] == '/')
		{
			projectName[len-1] = 0;
		}

		m_URL_Repository = projectName;
		
		string filePath = m_congifPath;
		filePath += "\\auth";

		if (PathFileExists(filePath.c_str()))
		{
			filePath += "\\ProjectName.tmp";
			FILE *file;
			file = fopen(filePath.c_str(),"w");

			char tempPath[255];
			memset(tempPath,0,sizeof(tempPath));
			strcpy(tempPath,m_URL_Repository.c_str());
			if (fwrite(tempPath,1,sizeof(tempPath),file)!= sizeof(tempPath))
			{
				AfxMessageBox("write temp file error");
				return;
			}
			fclose(file);
		}
		GetCongifPath();

		//GetProjectName();

		IsLogin();

		GetListView();
	
	}

}


//void CSmATL_SetEnvDlg::OnBnClickedButton2()
//{
//	// TODO: Add your control notification handler code here
//
//}
BOOL CSmATL_SetEnvDlg::DeleteDir(char *pPath)
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

void CSmATL_SetEnvDlg::OnBnClickedCleanButton()
{
	// TODO: Add your control notification handler code here
	//return;
	//GetCongifPath();

	string loginFile = m_congifPath;
	loginFile += "\\auth";

	char Temp[255];
	memset(Temp,0,sizeof(Temp));
	strcpy(Temp,loginFile.c_str());

	if (PathFileExists(loginFile.c_str()))
	{
		DeleteDir(Temp);
		//RemoveDirectory(loginFile.c_str());
		//CString strLogin(loginFile.c_str());
		//RemoveFolder(CString(loginFile.c_str()));
		m_IsCleanLogin = TRUE;
		m_firstLogin = TRUE;
	}

	m_CleanLoginBtn.EnableWindow(FALSE);
	//m_CleanLoginBtn.ModifyStyle(0,WS_DISABLED);
	//DeleteDir((const char *)loginFile.c_str());
}



//void CSmATL_SetEnvDlg::OnBnClickedChangeproductpathButton()
//{
//	// TODO: Add your control notification handler code here
//
//	TCHAR   szPath[MAX_PATH]={0};
//	LPITEMIDLIST   pitem;
//	BROWSEINFO   info;
//	::ZeroMemory(&info,sizeof(info));
//	info.hwndOwner=this->m_hWnd;  
//	info.lpszTitle=_T( "Choose   the   Folder: ");
//	//info.ulFlags=BIF_USENEWUI;
//	info.pszDisplayName = szPath;
//	//info.lpfn=BrowseCallbackProc;
//	//info.lParam= long(&DefaultDir);
//	if(pitem=::SHBrowseForFolder(&info))
//	{
//		::SHGetPathFromIDList(pitem,szPath);
//		UpdateData(FALSE);
//
//
//		string strTemp = szPath;
//		if (strTemp.find(__argv[1])!=string::npos&&strTemp.length() == strlen(__argv[1]))
//		{
//			AfxMessageBox("Can't Select This Path!");
//			//m_Product.SetWindowTextA(m_ProductPath.c_str());
//			return;
//		}
//
//		//string strPath = strTemp + "\\SmtRec.dat";
//		char pCtrPath[255];
//		char pFatherPath[255];
//
//		memset(pCtrPath,0,sizeof(pCtrPath));
//		memset(pFatherPath,0,sizeof(pFatherPath));
//		strcpy(pCtrPath,strTemp.c_str());
//		while(GetFatherPath(pCtrPath,pFatherPath))
//		{
//			string strPath = pCtrPath;
//			strPath += "\\SmtRec.dat";
//			if (PathFileExists(strPath.c_str()))
//			{
//				AfxMessageBox("Can't Select This Path!");
//				return;
//			}
//
//			strcpy(pCtrPath,pFatherPath);
//			memset(pFatherPath,0,sizeof(pFatherPath));
//		}
//
//		m_ProductPath = strTemp;
//		//m_ProductPath = CStringToString(FileName);
//		m_Product.SetWindowTextA(m_ProductPath.c_str());
//	} 
//}

BOOL CSmATL_SetEnvDlg::GetFatherPath(char *pCrtPath, char *pFatherPath)
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