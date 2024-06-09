// QuitDlg.cpp: 实现文件
//

#include "pch.h"
#include "ClassArranger.h"
#include "afxdialogex.h"
#include "QuitDlg.h"


// QuitDlg 对话框

IMPLEMENT_DYNAMIC(QuitDlg, CDialogEx)

QuitDlg::QuitDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QUIT_DIALOG, pParent)
{

}

QuitDlg::~QuitDlg()
{
}

void QuitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_MINIMUM, m_min);
	DDX_Control(pDX, IDC_RADIO3, m_close);
}


BEGIN_MESSAGE_MAP(QuitDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &QuitDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// QuitDlg 消息处理程序


void QuitDlg::OnBnClickedOk()
{
	if (m_close.GetCheck()) {
		EndDialog(4);
	}
	else if (m_min.GetCheck()) {
		EndDialog(5);
	}
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
