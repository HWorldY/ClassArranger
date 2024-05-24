#pragma once
#include "afxdialogex.h"


// DutyDlg 对话框

class DutyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DutyDlg)

public:
	DutyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DutyDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DUTY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_dstr;
	CEdit m_dedit;
	afx_msg void OnBnClickedButton();
};
