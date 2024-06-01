
// ClassArrangerDlg.h: 头文件
//

#pragma once
#include"CSchedule.h"
#include"CSButton.h"
#include"CDutyDisplay.h"
#include"CDButton.h"
#include"Settings.h"
#include"NameDisplay.h"
// CClassArrangerDlg 对话框
class CClassArrangerDlg : public CDialogEx
{
// 构造
public:
	CClassArrangerDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CClassArrangerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLASSARRANGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	BOOL PreTranslateMessage(MSG* pMsg);
// 实现
protected:
	Settings* m_set;
	HICON m_hIcon;
	CBrush m_brush;
	CBrush m_oldbrush;
	CFont m_font;
	CSchedule* m_schedule;
	CDutyDisplay* m_duty;
	CDButton m_dbutton;
	CSButton m_sbutton;
	NameDisplay m_cm;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL MoveCtrl(int x, int y);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnUpdateCString(WPARAM w, LPARAM l);// 自定义消息处理函数
	afx_msg void OnOK();
};
