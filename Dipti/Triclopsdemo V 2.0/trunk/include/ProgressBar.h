#if !defined(AFX_PROGRESSBAR_H__C5E45AA3_24D5_435B_8183_DCEFDFB65725__INCLUDED_)
#define AFX_PROGRESSBAR_H__C5E45AA3_24D5_435B_8183_DCEFDFB65725__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressBar.h : header file
//
//#include "stdafx.h"
#include <afxcmn.h>
#include "pgrresource.h"

#define WM_USER_THREAD_FINISHED (WM_USER+0x101)			//custom messages for worker thread
#define WM_USER_THREAD_UPDATE_PROGRESS (WM_USER+0x102)

/*
typedef struct THREADINFOSTRUCT {
	HWND hWnd;
	CString someData;
} THREADINFOSTRUCT;
*/


/////////////////////////////////////////////////////////////////////////////
// CProgressBar dialog

class CProgressBar : public CDialog
{
// Construction
public:
	CProgressBar(CWnd* pParent = NULL);   // standard constructor
    BOOL Create();

// Dialog Data
	//{{AFX_DATA(CProgressBar)
	enum { IDD = IDD_ProgressBar };
	CProgressCtrl	m_progresstime;
	//}}AFX_DATA

	//static UINT ThreadFunc(LPVOID lParam);	//thread's 'controlling' function
	//afx_msg LRESULT OnThreadFinished(WPARAM wParam,LPARAM lParam);
	//afx_msg LRESULT OnThreadUpdateProgress(WPARAM wParam,LPARAM lParam);

	void SetBar(int final);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	int barLimit;
	//static int i;

	// Generated message map functions
	//{{AFX_MSG(CProgressBar)
   virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSBAR_H__C5E45AA3_24D5_435B_8183_DCEFDFB65725__INCLUDED_)
