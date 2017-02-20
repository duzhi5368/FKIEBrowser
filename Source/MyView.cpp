// MyView.cpp : CMyView ���ʵ��
//

#include "stdafx.h"

#include "WebBrowser.h"
#include "WebBrowserDoc.h"
#include "MyView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_NEWURL WM_USER+104
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CHtmlView)

BEGIN_MESSAGE_MAP(CMyView, CHtmlView)
	// ��׼��ӡ����
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_COMMAND(ID_EDIT_BACK, &CMyView::OnEditBack)
    ON_COMMAND(ID_EDIT_FORWARD, &CMyView::OnEditForward)
    ON_COMMAND(ID_EDIT_REFRESH, &CMyView::OnEditRefresh)
    ON_COMMAND(ID_EDIT_STOP, &CMyView::OnEditStop)
    ON_COMMAND(ID_EDIT_HOME, &CMyView::OnEditHome)
    ON_COMMAND(ID_FILE_SELECT, &CMyView::OnFileSelect)
    ON_COMMAND(ID_FILE_FIND, &CMyView::OnFileFind)
    ON_COMMAND(ID_FILE_SAVE, &CMyView::OnFileSave)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMyView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyView::OnFilePrintPreview)
    ON_COMMAND(ID_FILE_PRINT_SETUP, &CMyView::OnFilePrintSetup)
    ON_COMMAND(ID_SLIDER2, &CMyView::OnSlider)
    ON_COMMAND(ID_BUTTON17, &CMyView::OnColor)
    ON_COMMAND(ID_B_HAO123, &CMyView::OnBHao123)
    ON_COMMAND(ID_B_BAIDU, &CMyView::OnBBaidu)
    ON_COMMAND(ID_B_GOOGLE, &CMyView::OnBGoogle)
    ON_COMMAND(ID_B_BING, &CMyView::OnBBing)
    ON_COMMAND(ID_B_TENCENT, &CMyView::OnBTencent)
    ON_COMMAND(ID_B_163, &CMyView::OnB163)
    ON_COMMAND(ID_B_TAOBAO, &CMyView::OnBTaobao)
    ON_COMMAND(ID_B_JD, &CMyView::OnBJd)
    ON_COMMAND(ID_B_AMZ, &CMyView::OnBAmz)
    ON_COMMAND(ID_B_WEIBO, &CMyView::OnBWeibo)
    ON_COMMAND(ID_B_TQQ, &CMyView::OnBTqq)
    ON_COMMAND(ID_B_QZONE, &CMyView::OnBQzone)
    ON_COMMAND(ID_B_RENREN, &CMyView::OnBRenren)
    ON_COMMAND(ID_B_WHUT, &CMyView::OnBWhut)
    ON_COMMAND(ID_B_WUTNEWS, &CMyView::OnBWutnews)
    ON_COMMAND(ID_B_XUAN, &CMyView::OnBXuan)
END_MESSAGE_MAP()

// CMyView ����/����

CMyView::CMyView()
{
    m_bIsCanBackPage=m_bIsCanForwardPage=FALSE;
}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CHtmlView::PreCreateWindow(cs);
}

void CMyView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	OnEditHome();
    SetSilent(TRUE);
}


// CMyView ��ӡ

void CMyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
}


// CMyView ���

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CWebBrowserDoc* CMyView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWebBrowserDoc)));
	return (CWebBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

void CMyView::GetMainFrame()
{   //��ȡ����ܲ���¼
    pChildFrame=(CChildFrame*)GetParentFrame();
    if(pChildFrame) pMainFrame=(CMainFrame*)pChildFrame->GetParentFrame();
}

// CMyView ��Ϣ�������
void CMyView::OnEditBack()
{  //���������
    if(m_bIsCanBackPage) GoBack();
    else MessageBox(L"��������ܺ��˵�ǰһ��ҳ�棡",L"FreeKnight IE�����",MB_ICONWARNING);
}

void CMyView::OnEditForward()
{  //�����ǰ��
    if(m_bIsCanForwardPage) GoForward();
    else MessageBox(L"���������ǰ����ָ��ҳ�棡",L"FreeKnight IE�����",MB_ICONWARNING);
}

void CMyView::OnEditRefresh()
{  //�����ˢ��
    Refresh();
}

void CMyView::OnEditStop()
{  //�����ֹͣ
    Stop();
}

void CMyView::OpenUrl(CString url)
{  //���������url
    Navigate(url,NULL,NULL);
}

void CMyView::OnEditHome()
{  //������򿪰ٶ�
    OpenUrl(L"http://www.baidu.com");
}

void CMyView::OnDocumentComplete(LPCTSTR lpszURL)
{  //������������
    CComPtr<IHTMLDocument2> pDoc = (IHTMLDocument2*)this->GetHtmlDocument();
    BSTR *bstrTitle = NULL;
    pDoc->get_title(bstrTitle);
    CString title;
    title.Empty();
	if (bstrTitle == NULL)
	{
		return;
	}
    title=*bstrTitle;
    title=title.Left(20);
    GetMainFrame();
    //���õ�ǰ�ӿ�ܱ���
    pChildFrame->SetWindowText(title);
    //���õ�ַ��
    pMainFrame->ChangeAddr(GetLocationURL());
    //��������ܱ���
    pMainFrame->UpdateFrameTitleForDocument(title);
    CHtmlView::OnDocumentComplete(lpszURL);
}

void CMyView::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel)
{   //����������´��ڣ��Զ�����Ϣ��
    ::SendMessage(AfxGetMainWnd()->m_hWnd,WM_NEWURL,(WPARAM)ppDisp,NULL);
    *Cancel=TRUE;
    CHtmlView::OnNewWindow2(ppDisp, Cancel);
}

void CMyView::OnFileSelect()
{  //ȫѡ
    SetFocus();
    ExecWB(OLECMDID_SELECTALL,OLECMDEXECOPT_DODEFAULT,NULL,NULL);
}

void CMyView::OnFileFind()
{  //����
    ExecWB(OLECMDID_FIND,OLECMDEXECOPT_DODEFAULT,NULL,NULL); 
}

void CMyView::OnFileSave()
{  //���Ϊ
    ExecWB(OLECMDID_SAVEAS,OLECMDEXECOPT_DODEFAULT,NULL,NULL);
}

void CMyView::OnFilePrint()
{  //��ӡ
    ExecWB(OLECMDID_PRINT,OLECMDEXECOPT_DODEFAULT,NULL,NULL);
}

void CMyView::OnFilePrintPreview()
{  //��ӡԤ��
    ExecWB(OLECMDID_PRINTPREVIEW,OLECMDEXECOPT_DODEFAULT,NULL,NULL);
}

void CMyView::OnFilePrintSetup()
{  //ҳ������
    ExecWB(OLECMDID_PAGESETUP,OLECMDEXECOPT_DODEFAULT,NULL,NULL);
}

void CMyView::OnSlider()
{  //ҳ������
    GetMainFrame();
	float fZoom=pMainFrame->GetZoom();
    CComPtr<IHTMLDocument2> pDoc = (IHTMLDocument2*)this->GetHtmlDocument();
    ASSERT(pDoc);
    CComPtr<IHTMLElement> pElem;
    pDoc->get_body(&pElem);
    ASSERT(pElem);
    CComPtr<IHTMLStyle> pStyle;
    pElem->get_style(&pStyle);
    CString str;
    str.Format(L"zoom:%f;",fZoom);
    pStyle->put_cssText(str.AllocSysString());
}

void CMyView::OnStatusTextChange(LPCTSTR lpszText)
{  //�����״̬�ı䣬�޸ĳ����״̬������Bug��
    GetMainFrame();
    if(pMainFrame) pMainFrame->SetStatusText(lpszText);
    CHtmlView::OnStatusTextChange(lpszText);
}

void CMyView::OnProgressChange(long nProgress, long nProgressMax)
{  //��������ȸı䣬�޸ĳ���Ľ�����
    GetMainFrame();
    if(pMainFrame) pMainFrame->SetProgress(nProgress,nProgressMax);
    CHtmlView::OnProgressChange(nProgress, nProgressMax);
}

void CMyView::OnCommandStateChange(long nCommand, BOOL bEnable)
{   //���ð�ť״̬
    if(pMainFrame)
        if(nCommand==CSC_NAVIGATEFORWARD) m_bIsCanForwardPage=bEnable;
        else if(nCommand==CSC_NAVIGATEBACK) m_bIsCanBackPage=bEnable;
    GetMainFrame();
    pMainFrame->SetButtonState(m_bIsCanForwardPage,m_bIsCanBackPage);
    CHtmlView::OnCommandStateChange(nCommand, bEnable);
}

void CMyView::OnColor()
{
}

void CMyView::OnBHao123()
{
    OpenUrl(L"http://www.hao123.com/");
}

void CMyView::OnBBaidu()
{
    OpenUrl(L"http://www.baidu.com/");
}

void CMyView::OnBGoogle()
{
    OpenUrl(L"http://www.google.com/");
}

void CMyView::OnBBing()
{
    OpenUrl(L"http://cn.bing.com/");
}

void CMyView::OnBTencent()
{
    OpenUrl(L"http://www.qq.com/");
}

void CMyView::OnB163()
{
    OpenUrl(L"http://www.163.com/");
}

void CMyView::OnBTaobao()
{
    OpenUrl(L"http://www.taobao.com/");
}

void CMyView::OnBJd()
{
    OpenUrl(L"http://www.jd.com/");
}

void CMyView::OnBAmz()
{
    OpenUrl(L"http://www.z.cn/");
}

void CMyView::OnBWeibo()
{
    OpenUrl(L"http://www.weibo.com/");
}

void CMyView::OnBTqq()
{
    OpenUrl(L"http://t.qq.com/");
}

void CMyView::OnBQzone()
{
    OpenUrl(L"http://qzone.qq.com/");
}

void CMyView::OnBRenren()
{
    OpenUrl(L"http://www.renren.com/");
}

void CMyView::OnBWhut()
{
    OpenUrl(L"http://www.whut.edu.cn/");
}

void CMyView::OnBWutnews()
{
    OpenUrl(L"http://www.wutnews.net/");
}

void CMyView::OnBXuan()
{
    OpenUrl(L"http://xuan.wutnews.net/");
}
