#pragma once


class CWebBrowserDoc : public CDocument
{
protected: // 仅从序列化创建
	CWebBrowserDoc();
	DECLARE_DYNCREATE(CWebBrowserDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();

// 实现
public:
	virtual ~CWebBrowserDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

};
