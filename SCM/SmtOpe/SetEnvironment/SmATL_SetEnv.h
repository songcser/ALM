
// SmATL_SetEnv.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSmATL_SetEnvApp:
// See SmATL_SetEnv.cpp for the implementation of this class
//

class CSmATL_SetEnvApp : public CWinApp
{
public:
	CSmATL_SetEnvApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSmATL_SetEnvApp theApp;