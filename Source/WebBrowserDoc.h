#pragma once


class CWebBrowserDoc : public CDocument
{
protected: // �������л�����
	CWebBrowserDoc();
	DECLARE_DYNCREATE(CWebBrowserDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();

// ʵ��
public:
	virtual ~CWebBrowserDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

};
