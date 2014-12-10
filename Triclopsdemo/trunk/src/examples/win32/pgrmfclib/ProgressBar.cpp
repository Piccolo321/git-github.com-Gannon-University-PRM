// ProgressBar.cpp : implementation file
//


#include "ProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressBar dialog


CProgressBar::CProgressBar(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProgressBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressBar)
	DDX_Control(pDX, IDC_PROGRESS1, m_progresstime);
	//}}AFX_DATA_MAP
}


/*UINT CProgressBar::ThreadFunc(LPVOID lParam) //not complete: c&p'd
{
	THREADINFOSTRUCT* tis=(THREADINFOSTRUCT*)lParam;
	for (int i=0;i<100;i++) 
	{
		//PostMessage(tis->hWnd,WM_USER_THREAD_UPDATE_PROGRESS,i,100);
		PostMessage(tis->hWnd,WM_USER_THREAD_UPDATE_PROGRESS,i,100);
		Sleep(100);
	}
	//PostMessage(tis->hWnd,WM_USER_THREAD_FINISHED,0,0);
	PostMessage(WM_USER_THREAD_FINISHED,0,0);
	delete tis;
	return 0;
}

LRESULT CProgressBar::OnThreadFinished(WPARAM wParam,LPARAM lParam)
{
	AfxMessageBox("Thread has exited");
	return 0;
}

LRESULT CProgressBar::OnThreadUpdateProgress(WPARAM wParam,LPARAM lParam)
{
	m_progresstime.SetPos(100*(int)wParam/(int)lParam);
	return 0;
}*/

void CProgressBar::SetBar(int final)
{
	barLimit = final;
	m_progresstime.SetPos(0);
	m_progresstime.SetRange32(0, barLimit);
	m_progresstime.SetStep(1);
}

BEGIN_MESSAGE_MAP(CProgressBar, CDialog)

//ON_MESSAGE(WM_USER_THREAD_FINISHED, OnThreadFinished)
//ON_MESSAGE(WM_USER_THREAD_UPDATE_PROGRESS, OnThreadUpdateProgress)
	//{{AFX_MSG_MAP(CProgressBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressBar message handlers

BOOL CProgressBar::Create()
{ 
   
   return CDialog::Create( CProgressBar::IDD, NULL );
}

BOOL CProgressBar::OnInitDialog() 
{
  CDialog::OnInitDialog();
  m_progresstime.SetStep(1);

//	SetIcon(m_hIcon, TRUE);			// Set big icon
//	SetIcon(m_hIcon, FALSE);		// Set small icon

   // m_ProgressBar.SetShowText(FALSE);
//SetTimer(IDT_progresstime, 100, NULL);

//srand(static_cast<unsigned>(time(NULL)));
	return TRUE;

}

