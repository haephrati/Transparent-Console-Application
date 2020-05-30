// TConsole.h : main header file for the TConsole application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CTConsoleApp:
// See TConsole.cpp for the implementation of this class
//

class CTConsoleApp : public CWinApp
{
public:
	CTConsoleApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTConsoleApp theApp;