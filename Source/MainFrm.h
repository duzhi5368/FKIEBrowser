// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
    void ChangeAddr(CString);
// ����
public:
    CMFCRibbonLabel*			m_pStatusBar;		// �ײ����״̬��Ϣ��
    CMFCRibbonProgressBar*		m_pProgressBar;		// �ײ��Ҳ������
	CMFCRibbonStatusBarPane*	m_pStatusBarPane;	// �ײ��Ҳ�������
	CMFCRibbonBar				m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages			m_PanelImages;
	CMFCRibbonStatusBar			m_wndStatusBar;
	CMFCCaptionBar				m_wndCaptionBar;	// ״̬��
    BOOL						m_bIsCanForwardPage;
    BOOL						m_bIsCanBackPage;
	float						m_fCurZoomValue;	// ��ǰҳ������ֵ
// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	// ��ʼ����������������ʽ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnOptions();
	DECLARE_MESSAGE_MAP()

	// �����ײ�״̬��
	BOOL CreateStatusBar();
	// ����������
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


