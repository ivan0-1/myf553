// myf553.h : main header file for the MYF553 application
//

#if !defined(AFX_MYF553_H__37D39F0F_8DD8_4973_B06E_598D9BCB37BC__INCLUDED_)
#define AFX_MYF553_H__37D39F0F_8DD8_4973_B06E_598D9BCB37BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyf553App:
// See myf553.cpp for the implementation of this class
//

class CMyf553App : public CWinApp
{
public:
	CMyf553App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyf553App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyf553App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYF553_H__37D39F0F_8DD8_4973_B06E_598D9BCB37BC__INCLUDED_)
