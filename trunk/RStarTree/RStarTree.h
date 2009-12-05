// RStarTree.h : main header file for the RStarTree application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRStarTreeApp:
// See RStarTree.cpp for the implementation of this class
//

class CRStarTreeApp : public CWinApp
{
public:
	CRStarTreeApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRStarTreeApp theApp;