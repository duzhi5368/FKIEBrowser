// MyView.h : CMyView ��Ľӿ�
//
#include "MainFrm.h"
#include "ChildFrm.h"

#pragma once

class CMyView : public CHtmlView
{
protected: // �������л�����
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// ����
public:
	CWebBrowserDoc* GetDocument() const;
    CMainFrame *pMainFrame;
    CChildFrame *pChildFrame;
    BOOL m_bIsCanBackPage;
    BOOL m_bIsCanForwardPage;
// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEditBack();
    afx_msg void OnEditForward();
    afx_msg void OnEditRefresh();
    afx_msg void OnEditStop();
    afx_msg void OnEditHome();
    afx_msg void OnAdd();
    virtual void OnDocumentComplete(LPCTSTR lpszURL);
    void OpenUrl(CString);
    virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
    afx_msg void OnFileSelect();
    afx_msg void OnFileFind();
    afx_msg void OnFileSave();
    afx_msg void OnFilePrint();
    afx_msg void OnFilePrintSetup();
    afx_msg void OnSlider();
    virtual void OnStatusTextChange(LPCTSTR lpszText);
    virtual void OnProgressChange(long nProgress, long nProgressMax);
    virtual void OnCommandStateChange(long nCommand, BOOL bEnable);
    void GetMainFrame();
    afx_msg void OnColor();
    afx_msg void OnBHao123();
    afx_msg void OnBBaidu();
    afx_msg void OnBGoogle();
    afx_msg void OnBBing();
    afx_msg void OnBTencent();
    afx_msg void OnB163();
    afx_msg void OnBTaobao();
    afx_msg void OnBJd();
    afx_msg void OnBAmz();
    afx_msg void OnBWeibo();
    afx_msg void OnBTqq();
    afx_msg void OnBQzone();
    afx_msg void OnBRenren();
    afx_msg void OnBWhut();
    afx_msg void OnBWutnews();
    afx_msg void OnBXuan();
};

#ifndef _DEBUG  // MyView.cpp �еĵ��԰汾
inline CWebBrowserDoc* CMyView::GetDocument() const
   { return reinterpret_cast<CWebBrowserDoc*>(m_pDocument); }
#endif

