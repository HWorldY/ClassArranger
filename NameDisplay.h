#pragma once
#include"pch.h"

#include"Settings.h"
#include <afxwin.h>
#define CName5  _T("NameDisplay")
#ifdef AFX_DESIGN_TIME
enum { IDC = IDC_NAMEDISPLAY };
#endif

class NameDisplay :
	public CWnd {
public:
	NameDisplay();
	~NameDisplay();
	DECLARE_DYNAMIC(NameDisplay);
	Settings* m_set;
protected:
	DECLARE_MESSAGE_MAP()
	BOOL RegisterWindowClass();
	CFont m_font;
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};