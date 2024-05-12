#include "pch.h"
#include "CSchedule.h"
#include "resource.h"
#include"Transparent.h"
#include"Lessons.h"
IMPLEMENT_DYNAMIC(CSchedule, CWnd)
BEGIN_MESSAGE_MAP(CSchedule, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CSchedule::CSchedule()
{
    CSchedule::RegisterWindowClass(); 
    CTime time = CTime::GetCurrentTime();
    CString str = time.Format("%w");
    int week = ((str == "0") ? 7 : str == "1" ? 1 : str == "2" ? 2 : str == "3" ?
        3 : str == "4" ? 4 : str == "5" ? 5 : str == "6" ? 6 : 0)-1;
    for (int m = 0; m <= 10; m++) {
        m_lstr[m] = LESSONS[week][m];//RGB(255, 0, 0);
    }
    m_lnum = 11;
    m_lheight = 25*SCALE;
    m_lwidth = WINDOW_WIDTH * SCALE;
    m_lbheight = 5 * SCALE;
    for (int m = 1; m <= 11; m++) {
        m_lcolor[m] = COLOR_2;//RGB(255, 0, 0);
    }
    m_lcolor[0] = RGB(150, 150, 150);
    m_lcolor[6] = RGB(150, 150, 150);
    LOGFONT lf = {};
    lf.lfHeight = TEXT_SIZE * SCALE;
    lf.lfWidth = 0;
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    lf.lfWeight = 500;
    lf.lfItalic = 0;
    lf.lfUnderline = 0;
    lf.lfStrikeOut = 0;
    lf.lfCharSet = ANSI_CHARSET;
    lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = DEFAULT_PITCH;
    wcscpy_s(lf.lfFaceName, L"宋体");
    m_lfont.CreateFontIndirect(&lf);
}

CSchedule::~CSchedule()
{
}

BOOL CSchedule::RegisterWindowClass()
{
    WNDCLASS windowclass;
    HINSTANCE hInstance = AfxGetInstanceHandle();
    if (!(::GetClassInfo(hInstance, ClassName, &windowclass))) {
        windowclass.style = CS_DBLCLKS;
        windowclass.lpfnWndProc = ::DefWindowProc;
        windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
        windowclass.hInstance = hInstance;
        windowclass.hIcon = NULL;
        windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
        windowclass.lpszMenuName = NULL;
        windowclass.lpszClassName = ClassName;
        if (!AfxRegisterClass(&windowclass))
        {
            AfxThrowResourceException();
            return false;
        }
    }
    return true;
}


void CSchedule::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    int hpos = 0; 
        dc.SelectObject(m_lfont);
        dc.SetBkColor(TRANSPARENT);
        dc.SetTextColor(TEXTCOLOR_ACTIVE);
    for (int m = 0; m <= m_lnum - 1; m++) {
        dc.FillSolidRect(0, hpos, m_lwidth, m_lheight,m_lcolor[m]);
        CRect rt(0, hpos, m_lwidth, hpos + m_lheight);
        dc.DrawText(m_lstr[m], rt,DT_VCENTER|DT_SINGLELINE);
        hpos += (m_lheight);
        dc.FillSolidRect(0, hpos, m_lwidth, m_lbheight, TRANSPARENT_COLOR_THROUGH);
        hpos += m_lbheight;
    }
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CWnd::OnPaint()
}


BOOL CSchedule::OnEraseBkgnd(CDC* pDC)
{
    return true;
    // TODO: 在此添加消息处理程序代码和/或调用默认值
}
