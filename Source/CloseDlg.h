#pragma once
//--------------------------------------------------------
// CCloseDlg �Ի���
class CCloseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCloseDlg)

public:
	CCloseDlg(CWnd* pParent = NULL);
	virtual ~CCloseDlg();

// �Ի�������
	enum { IDD = IDD_CLOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedCur();
    afx_msg void OnBnClickedAll();
};
