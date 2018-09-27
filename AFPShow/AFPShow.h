// AFPShow.h : main header file for the AFPSHOW application
//

#if !defined(AFX_AFPSHOW_H__9C54CEE4_9E34_11D6_88F9_0050BA798998__INCLUDED_)
#define AFX_AFPSHOW_H__9C54CEE4_9E34_11D6_88F9_0050BA798998__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAFPShowApp:
// See AFPShow.cpp for the implementation of this class
//

class CAFPShowApp : public CWinApp
{
public:
	CAFPShowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAFPShowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAFPShowApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AFPSHOW_H__9C54CEE4_9E34_11D6_88F9_0050BA798998__INCLUDED_)
