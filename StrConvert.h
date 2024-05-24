#pragma once
#include"pch.h"

wchar_t* AnsiToUnicode(const char* str);
char* CstringToChar(CString str);
CString UTF82WCS(const char* szU8);
CString CStringUtf8ToUnicode(CString Utf8);
void ReadStrings(CString file, CString strs[],int max=100);