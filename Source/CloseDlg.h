#pragma once
//--------------------------------------------------------
// CCloseDlg 对话框
class CCloseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCloseDlg)

public:
	CCloseDlg(CWnd* pParent = NULL);
	virtual ~CCloseDlg();

// 对话框数据
	enum { IDD = IDD_CLOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedCur();
    afx_msg void OnBnClickedAll();
};
