//--------------------------------------------------------
#pragma once
//--------------------------------------------------------
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif
//--------------------------------------------------------
#include "resource.h"       // ������
//--------------------------------------------------------
class CWebBrowserApp : public CWinAppEx
{
public:
	CWebBrowserApp();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
public:
	UINT  m_nAppLook;			// �������
public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------
extern CWebBrowserApp s_WebBrowserApp;
