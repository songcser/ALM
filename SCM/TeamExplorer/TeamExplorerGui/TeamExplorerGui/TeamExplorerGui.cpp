
// TeamExplorerGui.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TeamExplorerGui.h"
#include "SetEnvDlg.h"
#include "CheckoutDlg.h"
#include "CommitDlg.h"
#include "CheckinDlg.h"
#include "CancelDlg.h"
#include "AddDlg.h"
#include "RevertDlg.h"
#include "MergeDlg.h"
#include "ShowLogDlg.h"
#include "DownloadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTeamExplorerGuiApp
BEGIN_MESSAGE_MAP(CTeamExplorerGuiApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CTeamExplorerGuiApp construction
CTeamExplorerGuiApp::CTeamExplorerGuiApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CTeamExplorerGuiApp object
CTeamExplorerGuiApp theApp;

// CTeamExplorerGuiApp initialization
BOOL CTeamExplorerGuiApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxInitRichEdit2();

	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	if(__argc < 2){
		if (pShellManager != NULL){
			delete pShellManager;
		}
		return FALSE;
	}

	char CmdType[255];
	memset(CmdType, 0, sizeof(CmdType));
	memcpy(CmdType, __argv[1], strlen(__argv[1]));

	if(!memcmp("00", CmdType, 2)){
		CSetEnvDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if(nResponse == IDOK){
		}
		else if(nResponse == IDCANCEL){
		}
	}
	else if(!memcmp("01", CmdType, 2)){
		CCheckoutDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if(nResponse == IDOK){
		}
		else if(nResponse == IDCANCEL){
		}
	}
	else if(!memcmp("02", CmdType, 2)){
		CShowRetMsgDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if(nResponse == IDOK){
		}
		else if(nResponse == IDCANCEL){
		}
	}
	else if(!memcmp("03", CmdType, 2)){
		CCommitDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if(nResponse == IDOK){
		}
		else if(nResponse == IDCANCEL){
		}
	}
	else if(!memcmp("04", CmdType, 2)){
		CCheckinDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if(nResponse == IDOK){
		}
		else if(nResponse == IDCANCEL){
		}
	}
	else if(!memcmp("05", CmdType, 2)){
		CCancelDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if(nResponse == IDOK){
		}
		else if(nResponse == IDCANCEL){
		}
	}
	else if(!memcmp("06", CmdType, 2)){
		CAddDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if(nResponse == IDOK){
		}
		else if(nResponse == IDCANCEL){
		}
	}
	else if(!memcmp("07", CmdType, 2)){
		CRevertDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if(nResponse == IDOK){
		}
		else if(nResponse == IDCANCEL){
		}
	}
	else if(!memcmp("08", CmdType, 2)){
		CMergeDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if(nResponse == IDOK){
		}
		else if(nResponse == IDCANCEL){
		}
	}
	else if(!memcmp("09", CmdType, 2)){
		CShowLogDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if(nResponse == IDOK){
		}
		else if(nResponse == IDCANCEL){
		}
	}
	else if(!memcmp("10", CmdType, 2)){
		if(__argc >= 3){
			string DiffCmd = "TortoiseProc /command:diff /path:\"" + string(__argv[2]) + "\"";
			WinExec((char *)DiffCmd.c_str(), SW_SHOW);
		}
	}
	else if(!memcmp("11", CmdType, 2)){
		if(__argc >= 3){
			string CompareCmd = "TortoiseMerge \"" + string(__argv[2]) + ".working\" \"" + string(__argv[2]) + "\"";
			WinExec((char *)CompareCmd.c_str(), SW_SHOW);
		}
	}
	else if(!memcmp("12", CmdType, 2)){
		if(__argc >= 3){
			CDownloadDlg dlg;
			dlg.BeginDownload();
		}
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL){
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

