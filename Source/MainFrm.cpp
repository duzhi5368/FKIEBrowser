// MainFrm.cpp : CMainFrame 类的实现
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
// 初始化创建各部件和样式
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(s_WebBrowserApp.m_nAppLook);

	// 设置页面组显示样式
	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE;	// 其他可用样式...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;			// 设置为 FALSE 会将关闭按钮放置在选项卡区域的右侧
	mdiTabParams.m_bTabIcons = TRUE;						// 设置为 TRUE 将在 MDI 选项卡上启用文档图标
	mdiTabParams.m_bAutoColor = TRUE;						// 设置为 FALSE 将禁用 MDI 选项卡的自动着色
	mdiTabParams.m_bDocumentMenu = TRUE;					// 在选项卡区域的右边缘启用文档菜单
    mdiTabParams.m_bEnableTabSwap = TRUE;
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	// 创建RibbonBar
	if(!m_wndRibbonBar.Create(this)){
		TRACE0("创建管理菜单失败\n");
		return -1;
	}
	else
	{
		m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
	}

	// 创建底部状态栏
	if (!CreateStatusBar()) {
		TRACE0("创建状态栏失败\n");
		return -1;
	}

	// 创建标题栏
	if (!CreateCaptionBar()){
		TRACE0("创建输入栏失败\n");
		return -1;
	}

	// 启用增强的窗口管理对话框
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// 将文档名和应用程序名称在窗口标题栏上的顺序进行交换。这
	// 将改进任务栏的可用性，因为显示的文档名带有缩略图。
	ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}
//--------------------------------------------------------
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return TRUE;
}
//--------------------------------------------------------
// 创建底部状态栏
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

	CDockingManager::SetDockingMode(DT_SMART);	// 启用 Visual Studio 2005 样式停靠窗口行为	
	EnableAutoHidePanes(CBRS_ALIGN_ANY);		// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	return TRUE;
}
//--------------------------------------------------------
// 创建状态栏
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

	// 警告图标
	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_RIGHT);
	bNameValid = strTemp.LoadString(AFX_IDS_IDLEMESSAGE);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp);

	// 提示信息
	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_RIGHT);

	// 选项按钮
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_RIGHT, TRUE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	return TRUE;
}
//--------------------------------------------------------
// CMainFrame 诊断
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
// CMainFrame 消息处理程序
void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}
//--------------------------------------------------------
// 更换APP外观消息
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
	//获取地址输入框
    CMFCRibbonEdit *pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(ID_ADDR));
	//获取地址框文本
    CString strUrl = pEdit->GetEditText();
    if(strUrl == "")  //数据合法性判断
        MessageBox(L"请输入要访问的网址！",L"提示",MB_ICONWARNING);
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
// 修改网页地址文本
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
{  //设置进度条
	if (m_pProgressBar)
	{
		m_pProgressBar->SetRange(0, max);
		m_pProgressBar->SetPos(value);
	}
}
//--------------------------------------------------------
//设置状态栏文本
void CMainFrame::SetStatusText(LPCTSTR str)
{
    CString strTmp = str;
    static BOOL s_bIsNavigteFinish=TRUE;
    if( m_pStatusBar && (!strTmp.IsEmpty()) && s_bIsNavigteFinish) 
		m_pStatusBar->SetText(str);
    s_bIsNavigteFinish = strTmp.Find(L"完成",0);
}
//--------------------------------------------------------
// 打开新网页通知
LRESULT CMainFrame::OnNewUrl(WPARAM wParam, LPARAM lParam)
{ 
    LPDISPATCH* ppDispatch = (LPDISPATCH*)wParam;
    SendMessage(WM_COMMAND, ID_FILE_NEW, 0);

    CChildFrame* pChildFrame = (CChildFrame*)GetActiveFrame();
    *ppDispatch = ((CHtmlView*)pChildFrame->GetActiveView())->GetApplication();
    return 0;
}
//--------------------------------------------------------
// 尝试关闭消息
void CMainFrame::OnClose()
{
    CCloseDlg closeDlg;
    UINT r = closeDlg.DoModal();  //打开关闭对话框
    if(r == IDALL) 
		CMDIFrameWndEx::OnClose();
	else if (r == IDCUR)
	{
		GetActiveFrame()->DestroyWindow();
	}
}
//--------------------------------------------------------
// 设置后退、前进按钮状态
void CMainFrame::SetButtonState(BOOL sForward,BOOL sBack)
{
    m_bIsCanBackPage = sBack;
    m_bIsCanForwardPage = sForward;
}
//--------------------------------------------------------
// 设置按钮可用
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
// 系统信息 按钮
void CMainFrame::OnButtonSystem()
{
    ShellAbout(this->m_hWnd,L"FreeKnight IE浏览器",
		L"FreeKnight IE浏览器\n\r作者：FreeKnight（Frankie.W）",
		AfxGetApp()->LoadIcon(IDR_MAINFRAME));
}
//--------------------------------------------------------