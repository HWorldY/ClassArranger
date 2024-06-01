#include"pch.h"
#include"NameDisplay.h"
#include"SettingsDlg.h"
IMPLEMENT_DYNAMIC(NameDisplay, CWnd)
BEGIN_MESSAGE_MAP(NameDisplay, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
NameDisplay::NameDisplay()
{
	NameDisplay::RegisterWindowClass();

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
	wcscpy_s(lf.lfFaceName, L"����");
	m_font.CreateFontIndirectW(&lf);
}

NameDisplay::~NameDisplay()
{
}

BOOL NameDisplay::RegisterWindowClass()
{
	WNDCLASS windowclass;
	HINSTANCE hInstance = AfxGetInstanceHandle();
	if (!(::GetClassInfo(hInstance, CName5, &windowclass))) {
		windowclass.style = CS_DBLCLKS;
		windowclass.lpfnWndProc = ::DefWindowProc;
		windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
		windowclass.hInstance = hInstance;
		windowclass.hIcon = NULL;
		windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
		windowclass.lpszMenuName = NULL;
		windowclass.lpszClassName = CName5;
		if (!AfxRegisterClass(&windowclass))
		{
			AfxThrowResourceException();
			return false;
		}
	}
	return true;
}
void NameDisplay::OnPaint()
{
	CPaintDC dc(this);
	dc.SelectObject(m_font);
	CRect rt;
	this->GetClientRect(rt);
	dc.FillSolidRect(rt, RGB(200, 200, 200));
	CString name = L"#";
	name+=m_set->cn;
	dc.DrawText(name, rt, DT_LEFT);
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
}


BOOL NameDisplay::OnEraseBkgnd(CDC* pDC)
{
	//return true;
	return CWnd::OnEraseBkgnd(pDC);
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
}


void NameDisplay::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CWnd::OnLButtonDown(nFlags, point);
	CRect rect;
	GetClientRect(rect);
	//�ж�����λ���Ƿ��ڿؼ�����
	if (rect.PtInRect(point))
	{
		m_set->dlg->DoModal();
		//GetParent()->DestroyWindow();
	}

}