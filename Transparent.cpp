#include"Transparent.h"
#include "pch.h"

bool DrawTransparentRect(CDC* pDC, int Left, int Top, int Width, int Height, int Transparency, COLORREF Color)
{
    bool value = true;

    CDC memdc;
    CBitmap bmp, * pOldBitmap;

    memdc.CreateCompatibleDC(pDC);
    value&=bmp.CreateCompatibleBitmap(pDC, Width, Height); //该函数创建与指定的设备环境相关的设备兼容的位图。  
    //nWidth：指定位图的宽度，单位为像素。　nHeight：指定位图的高度，单位为像素。  
    pOldBitmap = memdc.SelectObject(&bmp); //选择一对象到指定的设备上下文环境中  

    CBrush brush;
    brush.CreateSolidBrush(Color);
    memdc.SelectObject(brush);
    memdc.FillSolidRect(0, 0, Width, Height, Color); //.用指定的固体色填充矩形。x,y坐标。cx,cy宽高  

    BLENDFUNCTION bf;
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = 0x2f; //半透明(0-ff,透明度从全透明到不透明)  
    bf.AlphaFormat = 0;
    value &= pDC->AlphaBlend(Left, Top, Width, Height, &memdc, 0, 0, Width, Height, bf);  //0,0表示在对话框显示的坐标

    memdc.SelectObject(pOldBitmap);
    return value;
}


