#pragma once
#define CName2  _T("CSButton")

class CSButton :
	public CWnd {
public:
	CSButton();
	~CSButton();
	CFont m_font;
	DECLARE_DYNAMIC(CSButton);
protected:
	DECLARE_MESSAGE_MAP()
	BOOL RegisterWindowClass();
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};