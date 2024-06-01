#pragma once
#include"Settings.h"
#define CName3  _T("CDutyDisplay")

class CDutyDisplay :
	public CWnd {
public:
	CFont m_dfont;
	int m_dheight;
	int m_dwidth;
	COLORREF m_dcolor;
	CString m_dstr;
	Settings* m_set;
	CDutyDisplay(Settings* set);
	~CDutyDisplay();
	DECLARE_DYNAMIC(CDutyDisplay);
protected:
	DECLARE_MESSAGE_MAP()
	BOOL RegisterWindowClass();
public:
	afx_msg void OnPaint();
	afx_msg LRESULT OnUpdateCString(WPARAM w, LPARAM l);// 自定义消息处理函数
};