// MainFrm.h : CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
    void ChangeAddr(CString);
// 特性
public:
    CMFCRibbonLabel*			m_pStatusBar;		// 底部左侧状态信息栏
    CMFCRibbonProgressBar*		m_pProgressBar;		// 底部右侧进度栏
	CMFCRibbonStatusBarPane*	m_pStatusBarPane;	// 底部右侧文字栏
	CMFCRibbonBar				m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages			m_PanelImages;
	CMFCRibbonStatusBar			m_wndStatusBar;
	CMFCCaptionBar				m_wndCaptionBar;	// 状态栏
    BOOL						m_bIsCanForwardPage;
    BOOL						m_bIsCanBackPage;
	float						m_fCurZoomValue;	// 当前页面缩放值
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	// 初始化创建各部件和样式
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnOptions();
	DECLARE_MESSAGE_MAP()

	// 创建底部状态栏
	BOOL CreateStatusBar();
	// 创建标题栏
	BOOL CreateCaptionBar();
public:
    afx_msg void OnAdd();
    afx_msg void OnAddr();
    afx_msg float GetZoom();
	afx_msg void SetZoom(float fZoom);
	afx_msg void SetProgress(long value, long max);
protected:
    afx_msg LRESULT OnNewUrl(WPARAM wParam, LPARAM lParam);
public:
    afx_msg void SetStatusText(LPCTSTR str);
    afx_msg void OnClose();
    afx_msg void ButtonEnable(CCmdUI *pCmdUI);
    afx_msg void SetButtonState(BOOL,BOOL);
    afx_msg void OnButtonSystem();
};


