#include"Transparent.h"
#include "pch.h"

bool DrawTransparentRect(CDC* pDC, int Left, int Top, int Width, int Height, int Transparency, COLORREF Color)
{
    bool value = true;

    CDC memdc;
    CBitmap bmp, * pOldBitmap;

    memdc.CreateCompatibleDC(pDC);
    value&=bmp.CreateCompatibleBitmap(pDC, Width, Height); //�ú���������ָ�����豸������ص��豸���ݵ�λͼ��  
    //nWidth��ָ��λͼ�Ŀ�ȣ���λΪ���ء���nHeight��ָ��λͼ�ĸ߶ȣ���λΪ���ء�  
    pOldBitmap = memdc.SelectObject(&bmp); //ѡ��һ����ָ�����豸�����Ļ�����  

    CBrush brush;
    brush.CreateSolidBrush(Color);
    memdc.SelectObject(brush);
    memdc.FillSolidRect(0, 0, Width, Height, Color); //.��ָ���Ĺ���ɫ�����Ρ�x,y���ꡣcx,cy���  

    BLENDFUNCTION bf;
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = 0x2f; //��͸��(0-ff,͸���ȴ�ȫ͸������͸��)  
    bf.AlphaFormat = 0;
    value &= pDC->AlphaBlend(Left, Top, Width, Height, &memdc, 0, 0, Width, Height, bf);  //0,0��ʾ�ڶԻ�����ʾ������

    memdc.SelectObject(pOldBitmap);
    return value;
}


