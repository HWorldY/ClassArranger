#pragma once
#include "afxdialogex.h"
#include"Settings.h"
class SettingsDlg :public CDialogEx
{
	DECLARE_DYNAMIC(SettingsDlg)

public:
	CString m_classname;
	CComboBox m_scombo;
	CButton m_autorun;
	CEdit m_cnedit;
	SettingsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SettingsDlg();
	Settings* m_set;
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTINGS_DIALOG };
#endif

protected:
	virtual BOOL OnInitDialog();
	int CheckPowerBoot();
	int SwitchPowerBoot();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboSchedule();
	afx_msg void OnBnClickedButtonAbout();
};

