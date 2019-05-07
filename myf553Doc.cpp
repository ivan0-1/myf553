// myf553Doc.cpp : implementation of the CMyf553Doc class
//

#include "stdafx.h"
#include "myf553.h"

#include "myf553Doc.h"

#include "Bmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyf553Doc

IMPLEMENT_DYNCREATE(CMyf553Doc, CDocument)

BEGIN_MESSAGE_MAP(CMyf553Doc, CDocument)
	//{{AFX_MSG_MAP(CMyf553Doc)
	ON_COMMAND(ID_RELOAD, OnReload)
	ON_UPDATE_COMMAND_UI(ID_RELOAD, OnUpdateReload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyf553Doc construction/destruction

CMyf553Doc::CMyf553Doc()
{
	// TODO: add one-time construction code here

}

CMyf553Doc::~CMyf553Doc()
{
}

BOOL CMyf553Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyf553Doc serialization

void CMyf553Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyf553Doc diagnostics

#ifdef _DEBUG
void CMyf553Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyf553Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyf553Doc commands

char *fileName = NULL;
extern int showHistogram;

BOOL CMyf553Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	free(fileName);

	int len = strlen((char *)lpszPathName);
	fileName = (char *)malloc(len + 1);
	memcpy(fileName,(char *)lpszPathName,len);
	fileName[len] = 0;

	loadBmpFile(fileName);

	return TRUE;
}

void CMyf553Doc::OnReload() 
{
	// TODO: Add your command handler code here
	loadBmpFile(fileName);
	showHistogram = FALSE;
	UpdateAllViews(0);
}

void CMyf553Doc::OnUpdateReload(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(fileName != NULL);
}
