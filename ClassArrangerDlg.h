﻿
// ClassArrangerDlg.h: 头文件
//

#pragma once
#include"CSchedule.h"
#include"CSButton.h"
#include"Settings.h"
// CClassArrangerDlg 对话框
class CClassArrangerDlg : public CDialogEx
{
// 构造
public:
	CClassArrangerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLASSARRANGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CBrush m_brush;
	CBrush m_oldbrush;
	CFont m_font;
	CSchedule m_schedule;
	CSButton m_sbutton;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEdit1();
};