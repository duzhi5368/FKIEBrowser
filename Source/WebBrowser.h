//--------------------------------------------------------
#pragma once
//--------------------------------------------------------
#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif
//--------------------------------------------------------
#include "resource.h"       // 主符号
//--------------------------------------------------------
class CWebBrowserApp : public CWinAppEx
{
public:
	CWebBrowserApp();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
public:
	UINT  m_nAppLook;			// 外观类型
public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------
extern CWebBrowserApp s_WebBrowserApp;
