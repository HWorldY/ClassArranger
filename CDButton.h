#pragma once
#define CName4  _T("CDButton")
#include"Settings.h"
#include"DutyDlg.h"
class CDButton :
	public CWnd {
public:
	CDButton(Settings* settings);
	~CDButton();
	DECLARE_DYNAMIC(CDButton);
public:
	DutyDlg dutydlg;
	CFont m_font;
	Settings* m_set;
protected:
	DECLARE_MESSAGE_MAP()
	BOOL RegisterWindowClass();
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};