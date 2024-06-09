#pragma once
#define CName6  _T("CQButton")
#include"Settings.h"
#include"pch.h"
#include"QuitDlg.h"
class CQButton :
	public CWnd {
public:
	CQButton();
	~CQButton();
	DECLARE_DYNAMIC(CQButton);
	QuitDlg quitdlg;
	CFont m_font;
protected:
	DECLARE_MESSAGE_MAP()
	BOOL RegisterWindowClass();
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};