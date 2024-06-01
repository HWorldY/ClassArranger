
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
	CString Path(RELATIVEPATH ? L"D://cpp//P//Projects//ClassArranger//x64//Release//Settings.txt" : L"Settings.txt");//在setting中更改RELATIVEPATH以调试
	m_set = new Settings(Path, L'[', L']', L"[*:*]");
	m_schedule = new CSchedule(m_set);
	m_duty = new CDutyDisplay(m_set);
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
}

void CClassArrangerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CSCHEDULE, *m_schedule);
	DDX_Control(pDX, IDC_CSBUTTON, m_sbutton);
	DDX_Control(pDX, IDC_CDBUTTON, m_dbutton);
	DDX_Control(pDX, IDC_CDUTYDISPLAY, *m_duty);
	DDX_Control(pDX, IDC_NAMEDISPLAY, m_cm);
}

BEGIN_MESSAGE_MAP(CClassArrangerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_GET_DIALOG_CSTRING, &CClassArrangerDlg::OnUpdateCString)// 自定义消息处理函数)
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
	SetWindowPos(&wndBottom, rc.right - WINDOW_WIDTH - 50, rc.top+50, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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
	if (IsWindow(m_cm.m_hWnd) ){
		m_dbutton.MoveWindow(0, 0, 43, NAME_HEIGHT);
	}
	if (IsWindow(m_schedule->m_hWnd)) {
		m_schedule->MoveWindow(0, NAME_HEIGHT+NAME_DBUTTON+DBUTTON_HEIGHT + DBUTTON_DUTY + DUTY_HEIGHT + DUTY_SBUTTON+ SBUTTON_HEIGHT+SBUTTON_SCHEDULE, x, SCHEDULE_HEIGHT);
	}
	if (IsWindow(m_dbutton.m_hWnd)) {
		m_dbutton.MoveWindow(0, NAME_HEIGHT+ NAME_DBUTTON, 43, DBUTTON_HEIGHT);
	}
	if (IsWindow(m_duty->m_hWnd)) {
		m_duty->MoveWindow(0, NAME_HEIGHT+NAME_DBUTTON+DBUTTON_HEIGHT + DBUTTON_DUTY, x, DUTY_HEIGHT);
	}
	if (IsWindow(m_sbutton.m_hWnd)) {
		m_sbutton.MoveWindow(0, NAME_HEIGHT+NAME_DBUTTON+DBUTTON_HEIGHT + DBUTTON_DUTY + DUTY_HEIGHT + DUTY_SBUTTON, 43, SBUTTON_HEIGHT);
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
