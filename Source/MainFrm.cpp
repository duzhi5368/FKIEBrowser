// MainFrm.cpp : CMainFrame ���ʵ��
//
//--------------------------------------------------------
#include "stdafx.h"
#include "WebBrowser.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "CloseDlg.h"
//--------------------------------------------------------
#define WM_NEWURL WM_USER+104
#define ID_STATUSBAR_PROGRESS 9999
//--------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//--------------------------------------------------------
IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)
//--------------------------------------------------------
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
    ON_UPDATE_COMMAND_UI(ID_EDIT_BACK,&CMainFrame::ButtonEnable)
    ON_UPDATE_COMMAND_UI(ID_EDIT_FORWARD,&CMainFrame::ButtonEnable)
    ON_UPDATE_COMMAND_UI(ID_STATUSBAR_PANE1,&CMainFrame::ButtonEnable)
	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
    ON_COMMAND(ID_ADDR, &CMainFrame::OnAddr)
    ON_MESSAGE(WM_NEWURL, &CMainFrame::OnNewUrl)
    ON_WM_CLOSE()
    ON_COMMAND(ID_BUTTON_SYSTEM, &CMainFrame::OnButtonSystem)
END_MESSAGE_MAP()
//--------------------------------------------------------
CMainFrame::CMainFrame()
{
	s_WebBrowserApp.m_nAppLook = s_WebBrowserApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
	m_bIsCanBackPage = FALSE;
	m_bIsCanForwardPage = FALSE;
}
//--------------------------------------------------------
CMainFrame::~CMainFrame()
{
}
//--------------------------------------------------------
// ��ʼ����������������ʽ
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(s_WebBrowserApp.m_nAppLook);

	// ����ҳ������ʾ��ʽ
	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE;	// ����������ʽ...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;			// ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	mdiTabParams.m_bTabIcons = TRUE;						// ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	mdiTabParams.m_bAutoColor = TRUE;						// ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	mdiTabParams.m_bDocumentMenu = TRUE;					// ��ѡ�������ұ�Ե�����ĵ��˵�
    mdiTabParams.m_bEnableTabSwap = TRUE;
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	// ����RibbonBar
	if(!m_wndRibbonBar.Create(this)){
		TRACE0("��������˵�ʧ��\n");
		return -1;
	}
	else
	{
		m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
	}

	// �����ײ�״̬��
	if (!CreateStatusBar()) {
		TRACE0("����״̬��ʧ��\n");
		return -1;
	}

	// ����������
	if (!CreateCaptionBar()){
		TRACE0("����������ʧ��\n");
		return -1;
	}

	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// ���ĵ�����Ӧ�ó��������ڴ��ڱ������ϵ�˳����н�������
	// ���Ľ��������Ŀ����ԣ���Ϊ��ʾ���ĵ�����������ͼ��
	ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}
//--------------------------------------------------------
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return TRUE;
}
//--------------------------------------------------------
// �����ײ�״̬��
BOOL CMainFrame::CreateStatusBar()
{
	if (!m_wndStatusBar.Create(this)){
		return FALSE;
	}

	BOOL bNameValid;
	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);

	m_pStatusBar = new CMFCRibbonLabel(strTitlePane1, FALSE);
	m_pProgressBar = new CMFCRibbonProgressBar(ID_STATUSBAR_PROGRESS, 160);
	m_pStatusBarPane = new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE);

	m_wndStatusBar.AddDynamicElement(m_pStatusBar);
	m_wndStatusBar.AddSeparator();
	m_wndStatusBar.AddExtendedElement(m_pProgressBar, L"...");
	m_wndStatusBar.AddSeparator();
	m_wndStatusBar.AddExtendedElement(m_pStatusBarPane, strTitlePane2);

	CDockingManager::SetDockingMode(DT_SMART);	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ	
	EnableAutoHidePanes(CBRS_ALIGN_ANY);		// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	return TRUE;
}
//--------------------------------------------------------
// ����״̬��
BOOL CMainFrame::CreateCaptionBar()
{
	return TRUE;
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 
		this, ID_VIEW_CAPTION_BAR, -1, FALSE))
	{
		return FALSE;
	}

	BOOL bNameValid;
	CString strTemp;

	// ����ͼ��
	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_RIGHT);
	bNameValid = strTemp.LoadString(AFX_IDS_IDLEMESSAGE);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp);

	// ��ʾ��Ϣ
	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_RIGHT);

	// ѡ�ť
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_RIGHT, TRUE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	return TRUE;
}
//--------------------------------------------------------
// CMainFrame ���
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG
//--------------------------------------------------------
// CMainFrame ��Ϣ�������
void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}
//--------------------------------------------------------
// ����APP�����Ϣ
void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;
	s_WebBrowserApp.m_nAppLook = id;
	switch (s_WebBrowserApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;
	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;
	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;
	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;
	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;
	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;
	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;
	default:
		switch (s_WebBrowserApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;
		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;
		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;
		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);
	s_WebBrowserApp.WriteInt(_T("ApplicationLook"), s_WebBrowserApp.m_nAppLook);
}
//--------------------------------------------------------
void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(s_WebBrowserApp.m_nAppLook == pCmdUI->m_nID);
}
//--------------------------------------------------------
void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}
//--------------------------------------------------------
void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != NULL);
	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}
//--------------------------------------------------------
void CMainFrame::OnAddr()
{
	//��ȡ��ַ�����
    CMFCRibbonEdit *pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(ID_ADDR));
	//��ȡ��ַ���ı�
    CString strUrl = pEdit->GetEditText();
    if(strUrl == "")  //���ݺϷ����ж�
        MessageBox(L"������Ҫ���ʵ���ַ��",L"��ʾ",MB_ICONWARNING);
    else
    {
        CChildFrame *pChildFrame = (CChildFrame*)GetActiveFrame();
        CHtmlView *pBrowser = (CHtmlView*)pChildFrame->GetActiveView();
		if (pBrowser->GetLocationURL() != strUrl)
		{
			pBrowser->Navigate(strUrl);
		}
    }
}
//--------------------------------------------------------
// �޸���ҳ��ַ�ı�
void CMainFrame::ChangeAddr(CString str)
{
    CMFCRibbonEdit *pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(ID_ADDR));
    pEdit->SetEditText(str);
}
//--------------------------------------------------------
void CMainFrame::SetZoom(float fZoom)
{
	m_fCurZoomValue = fZoom;
}
//--------------------------------------------------------
float CMainFrame::GetZoom()
{
	return m_fCurZoomValue;
}
//--------------------------------------------------------
void CMainFrame::SetProgress(long value, long max)
{  //���ý�����
	if (m_pProgressBar)
	{
		m_pProgressBar->SetRange(0, max);
		m_pProgressBar->SetPos(value);
	}
}
//--------------------------------------------------------
//����״̬���ı�
void CMainFrame::SetStatusText(LPCTSTR str)
{
    CString strTmp = str;
    static BOOL s_bIsNavigteFinish=TRUE;
    if( m_pStatusBar && (!strTmp.IsEmpty()) && s_bIsNavigteFinish) 
		m_pStatusBar->SetText(str);
    s_bIsNavigteFinish = strTmp.Find(L"���",0);
}
//--------------------------------------------------------
// ������ҳ֪ͨ
LRESULT CMainFrame::OnNewUrl(WPARAM wParam, LPARAM lParam)
{ 
    LPDISPATCH* ppDispatch = (LPDISPATCH*)wParam;
    SendMessage(WM_COMMAND, ID_FILE_NEW, 0);

    CChildFrame* pChildFrame = (CChildFrame*)GetActiveFrame();
    *ppDispatch = ((CHtmlView*)pChildFrame->GetActiveView())->GetApplication();
    return 0;
}
//--------------------------------------------------------
// ���Թر���Ϣ
void CMainFrame::OnClose()
{
    CCloseDlg closeDlg;
    UINT r = closeDlg.DoModal();  //�򿪹رնԻ���
    if(r == IDALL) 
		CMDIFrameWndEx::OnClose();
	else if (r == IDCUR)
	{
		GetActiveFrame()->DestroyWindow();
	}
}
//--------------------------------------------------------
// ���ú��ˡ�ǰ����ť״̬
void CMainFrame::SetButtonState(BOOL sForward,BOOL sBack)
{
    m_bIsCanBackPage = sBack;
    m_bIsCanForwardPage = sForward;
}
//--------------------------------------------------------
// ���ð�ť����
void CMainFrame::ButtonEnable(CCmdUI *pCmdUI)
{
    if(pCmdUI->m_nID==ID_EDIT_FORWARD)
		pCmdUI->Enable(m_bIsCanForwardPage);
    else if(pCmdUI->m_nID==ID_EDIT_BACK) 
		pCmdUI->Enable(m_bIsCanBackPage);
    else 
		pCmdUI->Enable(TRUE);
}
//--------------------------------------------------------
// ϵͳ��Ϣ ��ť
void CMainFrame::OnButtonSystem()
{
    ShellAbout(this->m_hWnd,L"FreeKnight IE�����",
		L"FreeKnight IE�����\n\r���ߣ�FreeKnight��Frankie.W��",
		AfxGetApp()->LoadIcon(IDR_MAINFRAME));
}
//--------------------------------------------------------