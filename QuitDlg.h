#pragma once
#include "afxdialogex.h"


// QuitDlg 对话框

class QuitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(QuitDlg)

public:
	QuitDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~QuitDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QUIT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_min;
	CButton m_close;
	afx_msg void OnBnClickedOk();
};
