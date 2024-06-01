#pragma once
#include"pch.h"

wchar_t* AnsiToUnicode(const char* str);
char* CstringToChar(CString str);
CString UTF82WCS(const char* szU8);
CString CStringUtf8ToUnicode(CString Utf8);
void ReadStrings(CString file, CString strs[],int max=100);
bool CutString(char* exp, int start, int end, char* back, bool mode, int max);
bool CutString(CString exp, int start, int end, char* back, bool mode, int max);
void  DivideFile(CString file, CString strs[], WCHAR start, WCHAR end);
void DivideString(CString str, CString items[], CString format);