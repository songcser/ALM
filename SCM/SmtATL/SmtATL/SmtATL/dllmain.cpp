// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "SmtATL_i.h"
#include "dllmain.h"

CSmtATLModule _AtlModule;

class CSmtATLApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CSmtATLApp, CWinApp)
END_MESSAGE_MAP()

CSmtATLApp theApp;

BOOL CSmtATLApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CSmtATLApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
