#include"CQButton.h"
#include"pch.h"
#include"resource.h"
#include"Settings.h"
IMPLEMENT_DYNAMIC(CQButton, CWnd)
BEGIN_MESSAGE_MAP(CQButton, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
CQButton::CQButton()
{
    CQButton::RegisterWindowClass();

    LOGFONT lf = {};
    lf.lfHeight = SBUTTON_HEIGHT / 1.5;
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

CQButton::~CQButton()
{
}

BOOL CQButton::RegisterWindowClass()
{
    WNDCLASS windowclass;
    HINSTANCE hInstance = AfxGetInstanceHandle();
    if (!(::GetClassInfo(hInstance, CName6, &windowclass))) {
        windowclass.style = CS_DBLCLKS;
        windowclass.lpfnWndProc = ::DefWindowProc;
        windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
        windowclass.hInstance = hInstance;
        windowclass.hIcon = NULL;
        windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
        windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
        windowclass.lpszMenuName = NULL;
        windowclass.lpszClassName = CName6;
        if (!AfxRegisterClass(&windowclass))
        {
            AfxThrowResourceException();
            return false;
        }
    }
    return true;
}
void CQButton::OnPaint()
{
    CPaintDC dc(this);
    dc.SelectObject(m_font);
    CRect rt;
    this->GetClientRect(rt);
    dc.FillSolidRect(rt, RGB(200, 200, 200));
    rt.bottom -= 5;
    rt.top += 5;
    rt.right -= 5;
    rt.left += 5;
    POINT pts[5] = { {rt.left,rt.top},{rt.right,rt.bottom}, {(rt.left + rt.right) / 2,(rt.top + rt.bottom) / 2} ,{rt.left,rt.bottom},{rt.right+1,rt.top-1} };
    dc.Polyline(pts, 5);
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CWnd::OnPaint()
}


BOOL CQButton::OnEraseBkgnd(CDC* pDC)
{
    //return true;
    return CWnd::OnEraseBkgnd(pDC);
    // TODO: 在此添加消息处理程序代码和/或调用默认值
}


void CQButton::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CWnd::OnLButtonDown(nFlags, point);
    CRect rect;
    GetClientRect(rect);
    //判断鼠标的位置是否在控件里面
    if (rect.PtInRect(point))
    {
        int re = quitdlg.DoModal();
        if (re==4) {
            this->GetParent()->DestroyWindow();
        }
        if (re == 5) {
            this->GetParent()->PostMessage(WM_SYSCOMMAND,SC_MINIMIZE);
        }
    }

}
