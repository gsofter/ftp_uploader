
// MFCApplication2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCApplication2App:
// See MFCApplication2.cpp for the implementation of this class
//

class CMFCApplication2App : public CWinApp
{
public:
	CMFCApplication2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication2App theApp;
