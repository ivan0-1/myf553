// myf553View.h : interface of the CMyf553View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYF553VIEW_H__74E14758_4C05_44E7_BFC0_7BB8ABD1973A__INCLUDED_)
#define AFX_MYF553VIEW_H__74E14758_4C05_44E7_BFC0_7BB8ABD1973A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyf553View : public CScrollView
{
protected: // create from serialization only
	CMyf553View();
	DECLARE_DYNCREATE(CMyf553View)

// Attributes
public:
	CMyf553Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyf553View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyf553View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyf553View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnGray();
	afx_msg void OnUpdateGray(CCmdUI* pCmdUI);
	afx_msg void OnHistogram();
	afx_msg void OnUpdateHistogram(CCmdUI* pCmdUI);
	afx_msg void OnHistogramSuper();
	afx_msg void OnUpdateHistogramSuper(CCmdUI* pCmdUI);
	afx_msg void OnLineartrans();
	afx_msg void OnUpdateLineartrans(CCmdUI* pCmdUI);
	afx_msg void OnEqualize();
	afx_msg void OnUpdateEqualize(CCmdUI* pCmdUI);
	afx_msg void OnFourier();
	afx_msg void OnUpdateFourier(CCmdUI* pCmdUI);
	afx_msg void OnInvertFourier();
	afx_msg void OnUpdateInvertFourier(CCmdUI* pCmdUI);
	afx_msg void OnFastFourier();
	afx_msg void OnUpdateFastFourier(CCmdUI* pCmdUI);
	afx_msg void OnInvertFastFourier();
	afx_msg void OnUpdateInvertFastFourier(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in myf553View.cpp
inline CMyf553Doc* CMyf553View::GetDocument()
   { return (CMyf553Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYF553VIEW_H__74E14758_4C05_44E7_BFC0_7BB8ABD1973A__INCLUDED_)
