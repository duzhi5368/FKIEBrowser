//--------------------------------------------------------
#include "stdafx.h"
#include "WebBrowser.h"
#include "WebBrowserDoc.h"
#include <propkey.h>
//--------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//--------------------------------------------------------
IMPLEMENT_DYNCREATE(CWebBrowserDoc, CDocument)
//--------------------------------------------------------
BEGIN_MESSAGE_MAP(CWebBrowserDoc, CDocument)
END_MESSAGE_MAP()
//--------------------------------------------------------
CWebBrowserDoc::CWebBrowserDoc()
{
}
//--------------------------------------------------------
CWebBrowserDoc::~CWebBrowserDoc()
{
}
//--------------------------------------------------------
BOOL CWebBrowserDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}
//--------------------------------------------------------
#ifdef _DEBUG
void CWebBrowserDoc::AssertValid() const
{
	CDocument::AssertValid();
}
//--------------------------------------------------------
void CWebBrowserDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
//--------------------------------------------------------