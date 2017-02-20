// ChildFrm.cpp : CChildFrame 类的实现
//
//--------------------------------------------------------
#include "stdafx.h"
#include "WebBrowser.h"
#include "ChildFrm.h"
//--------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//--------------------------------------------------------
IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)
//--------------------------------------------------------
BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()
//--------------------------------------------------------
CChildFrame::CChildFrame()
{
}
//--------------------------------------------------------
CChildFrame::~CChildFrame()
{
}
//--------------------------------------------------------
BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}
//--------------------------------------------------------
#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}
//--------------------------------------------------------
void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG
//--------------------------------------------------------
