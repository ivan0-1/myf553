// myf553Doc.h : interface of the CMyf553Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYF553DOC_H__4BA0EE7E_F88E_44E5_9D67_FF3C60D14613__INCLUDED_)
#define AFX_MYF553DOC_H__4BA0EE7E_F88E_44E5_9D67_FF3C60D14613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyf553Doc : public CDocument
{
protected: // create from serialization only
	CMyf553Doc();
	DECLARE_DYNCREATE(CMyf553Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyf553Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyf553Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyf553Doc)
	afx_msg void OnReload();
	afx_msg void OnUpdateReload(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYF553DOC_H__4BA0EE7E_F88E_44E5_9D67_FF3C60D14613__INCLUDED_)
