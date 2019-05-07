#if !defined(AFX_DLGHISTOGRAM_H__2A5BDACE_F1AA_4926_83B6_32D45A5A2F52__INCLUDED_)
#define AFX_DLGHISTOGRAM_H__2A5BDACE_F1AA_4926_83B6_32D45A5A2F52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHistogram.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHistogram dialog

class CDlgHistogram : public CDialog
{
// Construction
public:
	CDlgHistogram(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgHistogram)
	enum { IDD = IDD_HISTOGRAM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHistogram)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHistogram)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHISTOGRAM_H__2A5BDACE_F1AA_4926_83B6_32D45A5A2F52__INCLUDED_)
