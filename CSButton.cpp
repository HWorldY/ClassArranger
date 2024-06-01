#include"pch.h"
#include"CSButton.h"
#include"resource.h"
#include"Settings.h"
IMPLEMENT_DYNAMIC(CSButton, CWnd)
BEGIN_MESSAGE_MAP(CSButton, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
CSButton::CSButton()
{
    CSButton::RegisterWindowClass(); 

    LOGFONT lf = {};
    lf.lfHeight = SBUTTON_HEIGHT/1.5;
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
    m_font.CreateFontIndirect(&lf);
}

CSButton::~CSButton()
{
}

BOOL CSButton::RegisterWindowClass()
{
    WNDCLASS windowclass;
    HINSTANCE hInstance = AfxGetInstanceHandle();
    if (!(::GetClassInfo(hInstance, CName2, &windowclass))) {
        windowclass.style = CS_DBLCLKS;
        windowclass.lpfnWndProc = ::DefWindowProc;
        windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
        windowclass.hInstance = hInstance;
        windowclass.hIcon = NULL;
        windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
        windowclass.lpszMenuName = NULL;
        windowclass.lpszClassName = CName2;
        if (!AfxRegisterClass(&windowclass))
        {
            AfxThrowResourceException();
            return false;
        }
    }
    return true;
}
void CSButton::OnPaint()
{
    CPaintDC dc(this);
    dc.SelectObject(m_font);
    CRect rt;
    this->GetClientRect(rt);
    dc.FillSolidRect(rt, RGB(200, 200, 200));
    dc.DrawText(L"课程表", rt, DT_LEFT);
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CWnd::OnPaint()
}


BOOL CSButton::OnEraseBkgnd(CDC* pDC)
{
    //return true;
    return CWnd::OnEraseBkgnd(pDC);
    // TODO: 在此添加消息处理程序代码和/或调用默认值
}


void CSButton::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CWnd::OnLButtonDown(nFlags, point); 
    CRect rect;
    GetClientRect(rect);
    //判断鼠标的位置是否在控件里面
    if (rect.PtInRect(point))
    {
        //GetParent()->DestroyWindow();
        int re=::MessageBox(this->GetParent()->GetSafeHwnd(), L"关闭", L"退出", MB_OKCANCEL);
        if (re == IDOK)this->GetParent()->DestroyWindow();
    }

}
