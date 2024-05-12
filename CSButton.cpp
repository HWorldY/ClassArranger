#include"pch.h"
#include"CSButton.h"
#include"resource.h"
IMPLEMENT_DYNAMIC(CSButton, CWnd)
BEGIN_MESSAGE_MAP(CSButton, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
CSButton::CSButton()
{
    CSButton::RegisterWindowClass(); 
    
}

CSButton::~CSButton()
{
}

BOOL CSButton::RegisterWindowClass()
{
    WNDCLASS windowclass;
    HINSTANCE hInstance = AfxGetInstanceHandle();
    if (!(::GetClassInfo(hInstance, ClassName2, &windowclass))) {
        windowclass.style = CS_DBLCLKS;
        windowclass.lpfnWndProc = ::DefWindowProc;
        windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
        windowclass.hInstance = hInstance;
        windowclass.hIcon = NULL;
        windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
        windowclass.lpszMenuName = NULL;
        windowclass.lpszClassName = ClassName2;
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
    CRect rt;
    this->GetClientRect(rt);
    dc.FillSolidRect(rt, RGB(200, 200, 200));
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
