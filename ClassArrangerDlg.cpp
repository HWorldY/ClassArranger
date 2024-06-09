
// ClassArrangerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ClassArranger.h"
#include "ClassArrangerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClassArrangerDlg 对话框



CClassArrangerDlg::CClassArrangerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLASSARRANGER_DIALOG, pParent)
{
	CString Path(GetPath(0) + L"Settings.txt");
	m_set = new Settings(Path, L'[', L']', L"[*:*]");
	m_schedule = new CSchedule(m_set);
	m_duty = new CDutyDisplay(m_set);
	m_dbutton = new CDButton(m_set);
	m_cm.m_set = m_set;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_brush.CreateSolidBrush(TRANSPARENT_COLOR_THROUGH);
	m_oldbrush.CreateSolidBrush(RGB(0, 0, 0));
}

CClassArrangerDlg::~CClassArrangerDlg()
{
	delete m_set;
	delete m_schedule;
	delete m_duty;
	delete m_dbutton;
}

void CClassArrangerDlg::ToTray()
{
	ShowWindow(SW_HIDE);    //隐藏主窗口
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//自定义的消息名称
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	StrCpy(nid.szTip, L"ClassArranger"); //信息提示条
	Shell_NotifyIcon(NIM_ADD, &nid);    //在托盘区添加图标
}

void CClassArrangerDlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;          //自定义的消息名称
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	StrCpy(nid.szTip, L"ClassArranger");    //信息提示条为“计划任务提醒”  
	Shell_NotifyIcon(NIM_DELETE, &nid);    //在托盘区删除图标
}

void CClassArrangerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CSCHEDULE, *m_schedule);
	DDX_Control(pDX, IDC_CSBUTTON, m_sbutton);
	DDX_Control(pDX, IDC_CDBUTTON, *m_dbutton);
	DDX_Control(pDX, IDC_CDUTYDISPLAY, *m_duty);
	DDX_Control(pDX, IDC_CNAMEDISPLAY, m_cm);
	DDX_Control(pDX, IDC_CQBUTTON, m_quit);
}

BEGIN_MESSAGE_MAP(CClassArrangerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_GET_DIALOG_CSTRING, &CClassArrangerDlg::OnUpdateCString)// 自定义消息处理函数
	ON_MESSAGE(WM_SHOWTASK, &CClassArrangerDlg::OnShowTask)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CClassArrangerDlg 消息处理程序

BOOL CClassArrangerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowLong(this->m_hWnd, GWL_EXSTYLE, GetWindowLong(this->m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED & (~WS_CAPTION));//要使使窗体拥有透明效果,首先要有WS_EX_LAYERED扩展属性// 让本程序不在任务栏显示(创建一个工具条窗口)
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	SetLayeredWindowAttributes(TRANSPARENT_COLOR_THROUGH, TRANSPARENCY, TRANSPARENT_MODE);

	CRect rc;
	GetDesktopWindow()->GetWindowRect(rc);
	SetWindowText((CString)"CA");
	ShowWindow(SW_SHOWNOACTIVATE);
	SetWindowPos(&wndBottom, rc.right - WINDOW_WIDTH - 50, rc.top + 50, WINDOW_WIDTH, WINDOW_HEIGHT, SWP_NOACTIVATE);
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CRect wrc;
	GetClientRect(wrc);
	MoveCtrl(wrc.right, wrc.bottom);
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClassArrangerDlg::OnPaint()
{
	//AfxMessageBox(L"?");
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClassArrangerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CClassArrangerDlg::MoveCtrl(int x, int y)
{
	if (IsWindow(m_cm.m_hWnd)) {
		m_cm.MoveWindow(0, 0, 43, NAME_HEIGHT);
	}
	if (IsWindow(m_quit.m_hWnd)) {
		m_quit.MoveWindow(x - 20, 0, 20, NAME_HEIGHT);
	}
	if (IsWindow(m_dbutton->m_hWnd)) {
		m_dbutton->MoveWindow(0, NAME_HEIGHT + NAME_DBUTTON, 43, DBUTTON_HEIGHT);
	}
	if (IsWindow(m_duty->m_hWnd)) {
		m_duty->MoveWindow(0, NAME_HEIGHT + NAME_DBUTTON + DBUTTON_HEIGHT + DBUTTON_DUTY, x, DUTY_HEIGHT);
	}
	if (IsWindow(m_sbutton.m_hWnd)) {
		m_sbutton.MoveWindow(0, NAME_HEIGHT + NAME_DBUTTON + DBUTTON_HEIGHT + DBUTTON_DUTY + DUTY_HEIGHT + DUTY_SBUTTON, 43, SBUTTON_HEIGHT);
	}
	if (IsWindow(m_schedule->m_hWnd)) {
		m_schedule->MoveWindow(0, NAME_HEIGHT + NAME_DBUTTON + DBUTTON_HEIGHT + DBUTTON_DUTY + DUTY_HEIGHT + DUTY_SBUTTON + SBUTTON_HEIGHT + SBUTTON_SCHEDULE, x, SCHEDULE_HEIGHT);
	}
	return true;
}



HBRUSH CClassArrangerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	int wnd = pWnd->GetDlgCtrlID();
	if (wnd == IDC_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_brush;
	}
	if (wnd == IDC_CSCHEDULE)
	{
		return m_brush;
	}
	if (wnd == IDC_CSBUTTON)
	{
		return hbr;
	}
	if (wnd == IDC_CDUTYDISPLAY) {
		return m_brush;
	}
	return m_brush;
	return hbr;
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
}


BOOL CClassArrangerDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return true;
}

LRESULT CClassArrangerDlg::OnUpdateCString(WPARAM w, LPARAM l)
{
	this->m_duty->PostMessage(WM_GET_DIALOG_CSTRING, w, 0);
	return 1;
}
LRESULT CClassArrangerDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”
	{
		CMenu menu;
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置
		menu.CreatePopupMenu();//声明一个弹出式菜单
		SetForegroundWindow();
		menu.AppendMenu(MF_STRING, WM_DESTROY, L"关闭"); //增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已隐藏），将程序结束。              
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this); //确定弹出式菜单的位置                
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu(); //资源回收
		delete lpoint;
	}  break;
	case WM_LBUTTONDBLCLK:      //双击左键的处理
	{
		this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿
		DeleteTray();
	}  break;
	default:   break;
	}
	return 0;
}


void CClassArrangerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nID == SC_MINIMIZE) {
		ToTray();
		return;
	}
	CDialogEx::OnSysCommand(nID, lParam);
}




