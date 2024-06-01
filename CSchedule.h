#pragma once
#include "pch.h"
#include"Settings.h"
#include <afxwin.h>
#define CName  _T("CSchedule")
#ifdef AFX_DESIGN_TIME
enum { IDC = IDC_CSCHDULE };
#endif

class CSchedule :
	public CWnd {
public:
	CSchedule(Settings* set);
	~CSchedule();
	short m_lnum;
	int m_lheight;
	int m_lwidth;
	int m_lbheight;
	CFont m_lfont;
	Settings* m_set;
	CString m_lstr[NUM_LESSON];
	COLORREF m_lcolor[NUM_LESSON];
	DECLARE_DYNAMIC(CSchedule);
protected:
	DECLARE_MESSAGE_MAP()
	BOOL RegisterWindowClass();
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};