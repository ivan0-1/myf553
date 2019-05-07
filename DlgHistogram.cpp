// DlgHistogram.cpp : implementation file
//

#include "stdafx.h"
#include "myf553.h"
#include "DlgHistogram.h"

#include "Bmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHistogram dialog


CDlgHistogram::CDlgHistogram(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHistogram::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHistogram)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgHistogram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHistogram)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHistogram, CDialog)
	//{{AFX_MSG_MAP(CDlgHistogram)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHistogram message handlers

BOOL CDlgHistogram::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText("ª“∂»÷±∑ΩÕº");
	SetWindowPos(NULL, 0, 0, 280, 190, SWP_NOZORDER|SWP_NOMOVE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHistogram::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	
	int x1 = 10, x2 = x1 + 256;
	int y1 = 10, y2 = 140;

	dc.Rectangle(x1,y1,x2,y2);
	
	int i;
	int max = 0;
	for(i = 0; i < 256; i++) {
		if(H[i] > max) {
			max = H[i];
		}
	}

	for(i = 0; i < 256; i++) {
		dc.MoveTo(x1 + i, y2 - 1);
		dc.LineTo(x1 + i, (y2 - 1 - H[i] / (max / (y2 - y1 - 20))));
	}

}
