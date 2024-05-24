#include"pch.h"
#include"CDButton.h"
#include"resource.h"
#include"Settings.h"
IMPLEMENT_DYNAMIC(CDButton, CWnd)
BEGIN_MESSAGE_MAP(CDButton, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
CDButton::CDButton()
{
    CDButton::RegisterWindowClass();

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

CDButton::~CDButton()
{
}

BOOL CDButton::RegisterWindowClass()
{
    WNDCLASS windowclass;
    HINSTANCE hInstance = AfxGetInstanceHandle();
    if (!(::GetClassInfo(hInstance, ClassName4, &windowclass))) {
        windowclass.style = CS_DBLCLKS;
        windowclass.lpfnWndProc = ::DefWindowProc;
        windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
        windowclass.hInstance = hInstance;
        windowclass.hIcon = NULL;
        windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
        windowclass.lpszMenuName = NULL;
        windowclass.lpszClassName = ClassName4;
        if (!AfxRegisterClass(&windowclass))
        {
            AfxThrowResourceException();
            return false;
        }
    }
    return true;
}
void CDButton::OnPaint()
{
    CPaintDC dc(this);
    dc.SelectObject(m_font);
    CRect rt;
    this->GetClientRect(rt);
    dc.FillSolidRect(rt, RGB(200, 200, 200));
    dc.DrawText(L"值日生", rt, DT_LEFT);
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CWnd::OnPaint()
}


BOOL CDButton::OnEraseBkgnd(CDC* pDC)
{
    //return true;
    return CWnd::OnEraseBkgnd(pDC);
    // TODO: 在此添加消息处理程序代码和/或调用默认值
}


void CDButton::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CWnd::OnLButtonDown(nFlags, point);
    CRect rect;
    GetClientRect(rect);
    //判断鼠标的位置是否在控件里面
    if (rect.PtInRect(point))
    {
        //GetParent()->DestroyWindow();
        if(dutydlg.DoModal()==1)this->GetParent()->PostMessage(WM_GET_DIALOG_CSTRING, (long long int)&dutydlg.m_dstr, 0);
    }

}
