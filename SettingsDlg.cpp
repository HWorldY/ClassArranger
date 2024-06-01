#include "pch.h"
#include "afxdialogex.h"
#include"ClassArranger.h"
#include "SettingsDlg.h"

IMPLEMENT_DYNAMIC(SettingsDlg, CDialogEx)

SettingsDlg::SettingsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTINGS_DIALOG, pParent)
{
}

SettingsDlg::~SettingsDlg()
{
}

BOOL SettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	for (int i = 0; i <= 7; i++)
	{
		CString temp;
		temp.Format(L"%d.txt", i);
		m_scombo.AddString(temp); //添加选择项
	}
	m_scombo.AddString(L"默认");
	m_scombo.SetCurSel(this->m_set->ScheduleChoice); //设置默认选择项
	m_autorun.SetCheck(CheckPowerBoot());
	return 0;
}

int SettingsDlg::CheckPowerBoot()
{
		HKEY hKey;

		//找到系统的启动项
		CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

		//打开启动项
		long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
		if (lRet != ERROR_SUCCESS)
			MessageBox(_T("打开启动项失败"));

		//找到程序自身路径
		TCHAR pFileName[MAX_PATH] = {};
		GetModuleFileName(NULL, pFileName, MAX_PATH);

		//判断是否已经设置开机启动
		TCHAR PowerBoot[MAX_PATH] = {};
		DWORD nLongth = MAX_PATH;
		long result = RegGetValue(hKey, NULL, _T("CA"), RRF_RT_REG_SZ, 0, PowerBoot, &nLongth);
		if (result == ERROR_SUCCESS)
		{
	return 1;
		}
		else
		{
		return 0;
		}

		//关闭注册表
		RegCloseKey(hKey);
	
}
int SettingsDlg::SwitchPowerBoot()
{
	try
	{
		HKEY hKey;

		//找到系统的启动项
		CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

		//打开启动项
		long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
		if (lRet != ERROR_SUCCESS)
			MessageBox(_T("打开启动项失败"));

		//找到程序自身路径
		TCHAR pFileName[MAX_PATH] = {};
		GetModuleFileName(NULL, pFileName, MAX_PATH);

		//判断是否已经设置开机启动
		TCHAR PowerBoot[MAX_PATH] = {};
		DWORD nLongth = MAX_PATH;
		long result = RegGetValue(hKey, NULL, _T("CA"), RRF_RT_REG_SZ, 0, PowerBoot, &nLongth);
		if (result == ERROR_SUCCESS)        //自启状态
		{
			//取消自动启动
			lRet = RegDeleteValue(hKey, _T("CA"));
			if (lRet == ERROR_SUCCESS)
			{
				//MessageBox(_T("关闭自启成功"));
			}
		}
		else        //未自启状态
		{
			//设置自启
			lRet = RegSetValueEx(hKey, _T("CA"), 0, REG_SZ, (LPBYTE)pFileName, (lstrlen(pFileName) + 1) * sizeof(TCHAR));
			if (lRet == ERROR_SUCCESS)
			{
				//MessageBox(_T("设置自启成功"));
			}
		}

		//关闭注册表
		RegCloseKey(hKey);
	}
	catch (...) {
		return 0;
	}
	return 1;
}
void SettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK, m_autorun);
	DDX_Control(pDX, IDC_EDIT_CLASSNAME, m_cnedit);
	DDX_Text(pDX, IDC_EDIT_CLASSNAME, this->m_set->cn);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE, m_scombo);
}


BEGIN_MESSAGE_MAP(SettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SettingsDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_SCHEDULE, &SettingsDlg::OnCbnSelchangeComboSchedule)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &SettingsDlg::OnBnClickedButtonAbout)
END_MESSAGE_MAP()

// SettingsDlg 消息处理程序
//开机启动





void SettingsDlg::OnBnClickedOk()
{
	if(m_autorun.GetCheck()!=CheckPowerBoot())SwitchPowerBoot();
	GetDlgItemText(IDC_EDIT_CLASSNAME, this->m_set->cn);
	this->m_set->SaveSettings();
	extern CClassArrangerApp theApp;

	TCHAR szAppName[MAX_PATH];
	::GetModuleFileName(theApp.m_hInstance, szAppName, MAX_PATH);

	CString strAppFullName;
	strAppFullName.Format(_T("%s"), szAppName);

	//重启程序	
	STARTUPINFO StartInfo;
	PROCESS_INFORMATION procStruct;
	memset(&StartInfo, 0, sizeof(STARTUPINFO));
	StartInfo.cb = sizeof(STARTUPINFO);
	// 最重要的环节，产生一个新的进程
	::CreateProcess(
		(LPCTSTR)strAppFullName,
		NULL,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS,
		NULL,
		NULL,
		&StartInfo,
		&procStruct);
	// 终止原来的程序
	::TerminateProcess(::GetCurrentProcess(), 0);


	CDialogEx::OnOK();
}




void SettingsDlg::OnCbnSelchangeComboSchedule()
{
	int temp = m_scombo.GetCurSel();
	this->m_set->ScheduleChoice = temp;
	// TODO: 在此添加控件通知处理程序代码
}


void SettingsDlg::OnBnClickedButtonAbout()
{
	MessageBox(L"https://github.com/HWorldY/ClassArranger");
	// TODO: 在此添加控件通知处理程序代码
}
