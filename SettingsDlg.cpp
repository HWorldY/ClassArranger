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
		m_scombo.AddString(temp); //���ѡ����
	}
	m_scombo.AddString(L"Ĭ��");
	m_scombo.SetCurSel(this->m_set->ScheduleChoice); //����Ĭ��ѡ����
	m_autorun.SetCheck(CheckPowerBoot());
	return 0;
}

int SettingsDlg::CheckPowerBoot()
{
		HKEY hKey;

		//�ҵ�ϵͳ��������
		CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

		//��������
		long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
		if (lRet != ERROR_SUCCESS)
			MessageBox(_T("��������ʧ��"));

		//�ҵ���������·��
		TCHAR pFileName[MAX_PATH] = {};
		GetModuleFileName(NULL, pFileName, MAX_PATH);

		//�ж��Ƿ��Ѿ����ÿ�������
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

		//�ر�ע���
		RegCloseKey(hKey);
	
}
int SettingsDlg::SwitchPowerBoot()
{
	try
	{
		HKEY hKey;

		//�ҵ�ϵͳ��������
		CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

		//��������
		long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
		if (lRet != ERROR_SUCCESS)
			MessageBox(_T("��������ʧ��"));

		//�ҵ���������·��
		TCHAR pFileName[MAX_PATH] = {};
		GetModuleFileName(NULL, pFileName, MAX_PATH);

		//�ж��Ƿ��Ѿ����ÿ�������
		TCHAR PowerBoot[MAX_PATH] = {};
		DWORD nLongth = MAX_PATH;
		long result = RegGetValue(hKey, NULL, _T("CA"), RRF_RT_REG_SZ, 0, PowerBoot, &nLongth);
		if (result == ERROR_SUCCESS)        //����״̬
		{
			//ȡ���Զ�����
			lRet = RegDeleteValue(hKey, _T("CA"));
			if (lRet == ERROR_SUCCESS)
			{
				//MessageBox(_T("�ر������ɹ�"));
			}
		}
		else        //δ����״̬
		{
			//��������
			lRet = RegSetValueEx(hKey, _T("CA"), 0, REG_SZ, (LPBYTE)pFileName, (lstrlen(pFileName) + 1) * sizeof(TCHAR));
			if (lRet == ERROR_SUCCESS)
			{
				//MessageBox(_T("���������ɹ�"));
			}
		}

		//�ر�ע���
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

// SettingsDlg ��Ϣ�������
//��������





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

	//��������	
	STARTUPINFO StartInfo;
	PROCESS_INFORMATION procStruct;
	memset(&StartInfo, 0, sizeof(STARTUPINFO));
	StartInfo.cb = sizeof(STARTUPINFO);
	// ����Ҫ�Ļ��ڣ�����һ���µĽ���
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
	// ��ֹԭ���ĳ���
	::TerminateProcess(::GetCurrentProcess(), 0);


	CDialogEx::OnOK();
}




void SettingsDlg::OnCbnSelchangeComboSchedule()
{
	int temp = m_scombo.GetCurSel();
	this->m_set->ScheduleChoice = temp;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void SettingsDlg::OnBnClickedButtonAbout()
{
	MessageBox(L"https://github.com/HWorldY/ClassArranger");
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
