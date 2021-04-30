// IceTradeAPISample.h : main header file for the ICETRADEAPISAMPLE application
//

#if !defined(AFX_ICETRADEAPISAMPLE_H__9C7DA811_0E71_4E9D_A15E_829415806FBF__INCLUDED_)
#define AFX_ICETRADEAPISAMPLE_H__9C7DA811_0E71_4E9D_A15E_829415806FBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIceTradeAPISampleApp:
// See IceTradeAPISample.cpp for the implementation of this class
//

class CIceTradeAPISampleApp : public CWinApp
{
public:
	CIceTradeAPISampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIceTradeAPISampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIceTradeAPISampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICETRADEAPISAMPLE_H__9C7DA811_0E71_4E9D_A15E_829415806FBF__INCLUDED_)
