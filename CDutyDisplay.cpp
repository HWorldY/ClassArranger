#include "pch.h"
#include"CDutyDisplay.h"
#include"Settings.h"
#include"resource.h"
IMPLEMENT_DYNAMIC(CDutyDisplay, CWnd)
BEGIN_MESSAGE_MAP(CDutyDisplay, CWnd)
    ON_WM_PAINT()
    ON_MESSAGE(WM_GET_DIALOG_CSTRING, OnUpdateCString)
END_MESSAGE_MAP()
CDutyDisplay::CDutyDisplay(Settings* set)
{
    this->m_set = set;
    CDutyDisplay::RegisterWindowClass();
   
    m_dcolor= COLOR_YELLOW;//RGB(255, 0, 0);
    LOGFONT lf = {};
    lf.lfHeight = 18;
    lf.lfWidth = 0;
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    lf.lfWeight = 300;
    lf.lfItalic = 0;
    lf.lfUnderline = 0;
    lf.lfStrikeOut = 0;
    lf.lfCharSet = ANSI_CHARSET;
    lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = DEFAULT_PITCH;
    wcscpy_s(lf.lfFaceName, L"宋体");
    m_dfont.CreateFontIndirect(&lf);
    m_dstr = set->GetSetting(L"SOD")[1];
}

CDutyDisplay::~CDutyDisplay()
{
}

BOOL CDutyDisplay::RegisterWindowClass()
{
    WNDCLASS windowclass;
    HINSTANCE hInstance = AfxGetInstanceHandle();
    if (!(::GetClassInfo(hInstance, CName3, &windowclass))) {
        windowclass.style = CS_DBLCLKS;
        windowclass.lpfnWndProc = ::DefWindowProc;
        windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
        windowclass.hInstance = hInstance;
        windowclass.hIcon = NULL;
        windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
        windowclass.lpszMenuName = NULL;
        windowclass.lpszClassName = CName3;
        if (!AfxRegisterClass(&windowclass))
        {
            AfxThrowResourceException();
            return false;
        }
    }
    return true;
}
void CDutyDisplay::OnPaint()
{
    CPaintDC dc(this);
    dc.SelectObject(m_dfont);
    dc.SetBkColor(TRANSPARENT);
    dc.SetTextColor(COLOR_BLACK);
    CRect rt;
    GetWindowRect(rt);
    ScreenToClient(rt);
    dc.FillSolidRect(0, 0, rt.right, rt.bottom, m_dcolor);
    dc.DrawText(m_dstr, rt, DT_VCENTER | DT_SINGLELINE);
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CWnd::OnPaint()
}
LRESULT CDutyDisplay::OnUpdateCString(WPARAM w, LPARAM l) {
    m_dstr = *((CString*)w);
    this->m_set->DName = m_dstr;
    this->m_set->SaveSettings();
    Invalidate(1);
    return 1;
}