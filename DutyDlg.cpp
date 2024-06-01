// DutyDlg.cpp: 实现文件
//

#include "pch.h"
#include "ClassArranger.h"
#include "afxdialogex.h"
#include "DutyDlg.h"
#include "StrConvert.h"
#include"Settings.h"
#include"SettingsDlg.h"
// DutyDlg 对话框

IMPLEMENT_DYNAMIC(DutyDlg, CDialogEx)

DutyDlg::DutyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DUTY, pParent)
	, m_dstr(_T("输入姓名"))
{
}

DutyDlg::~DutyDlg()
{
}

void DutyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_dedit);
	DDX_Text(pDX, IDC_EDIT1, m_dstr);
}


BEGIN_MESSAGE_MAP(DutyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON, &DutyDlg::OnBnClickedButton)
END_MESSAGE_MAP()

// DutyDlg 消息处理程序


void DutyDlg::OnBnClickedButton()
{
	GetDlgItemText(IDC_EDIT1, m_dstr);
	EndDialog(1);
	// TODO: 在此添加控件通知处理程序代码
}


