#pragma once
#define ClassName4  _T("CDButton")
#include"DutyDlg.h"
class CDButton :
	public CWnd {
public:
	CDButton();
	~CDButton();
	DECLARE_DYNAMIC(CDButton);
	DutyDlg dutydlg;
	CFont m_font;
protected:
	DECLARE_MESSAGE_MAP()
	BOOL RegisterWindowClass();
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};