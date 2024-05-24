#include"StrConvert.h"
#include "pch.h"
wchar_t* AnsiToUnicode(const char* str)
{
	int    textlen;
	wchar_t* result;
	textlen = ::MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	result = (wchar_t*)malloc((textlen + 1) * sizeof(wchar_t));
	memset(result, 0, (textlen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)result, textlen);
	return    result;
}
char* CstringToChar(CString str)
{
	/*char* buf=new char[10];*/
	int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	char* buf = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, str, -1, buf, len, NULL, NULL);

	return buf;
}
CString UTF82WCS(const char* szU8)
{
	//预转换，得到所需空间的大小;
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);


	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wchar_t* wszString = new wchar_t[wcsLen + 1];


	//转换
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);


	//最后加上'\0'
	wszString[wcsLen] = '\0';


	CString unicodeString(wszString);


	delete[] wszString;
	wszString = NULL;


	return unicodeString;
}
CString CStringUtf8ToUnicode(CString Utf8)
{
	int wLen = 0;
	CString strUnicode;
	LPSTR pBufChar = NULL;
	LPWSTR pBufWchar = NULL;

	//CString to char
	wLen = WideCharToMultiByte(CP_ACP, 0, Utf8, -1, NULL, 0, NULL, NULL);
	pBufChar = new char[wLen + 1];
	memset(pBufChar, 0, wLen + 1);
	WideCharToMultiByte(CP_ACP, 0, Utf8, -1, pBufChar, wLen, NULL, NULL);

	//char to Unicode
	wLen = MultiByteToWideChar(CP_UTF8, 0, pBufChar, -1, NULL, NULL);
	pBufWchar = new wchar_t[wLen];
	memset(pBufWchar, 0, wLen * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, pBufChar, -1, pBufWchar, wLen);

	strUnicode = CString(pBufWchar);
	if (pBufChar) delete[]pBufChar;
	if (pBufWchar) delete[]pBufWchar;

	return strUnicode;
}
void ReadStrings(CString file, CString strs[],int max) {
	int s = 0;
	int length = file.GetLength();
	for (int i = 0; i <= length&&s<=max-1; i++) {
		if (file[i] == '\n') {
			s++;
			continue;
		}
		strs[s] += file[i];
	}
}