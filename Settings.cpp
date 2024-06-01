#include "pch.h"
#include "Settings.h"
#include"SettingsDlg.h"
Settings::Settings(CString path, WCHAR start, WCHAR end, CString format)
{
	CFile f;
	int flen = format.GetLength();
	this->ItemNum = 0;
	for (int m = 0; m <= flen - 1; m++)if (format[m] == '*')this->ItemNum++;
	if (f.Open(path, CFile::modeRead)) {
		CString* s = new CString[SettingNum];
		int size = f.GetLength();
		char* buffer = new char[size + 1];
		f.Read(buffer, size * sizeof(char));
		CString s2=AnsiToUnicode(buffer);
		DivideFile(s2, s, start, end);
		delete[] buffer;
		for (int m = 0; m <= SettingNum - 1; m++) {
			this->settings[m] = new CString[ItemNum];
			DivideString(s[m], this->settings[m], format);
		}
		delete[] s;
	}
	f.Close();
	this->path = path;
	this->format = format;

	this->dlg = new SettingsDlg;
	this->dlg->m_set = this;

	this->ScheduleChoice = _ttoi(GetSetting(L"Schedule")[1]);
	this->cn = GetSetting(L"ClassName")[1];
	this->DName = GetSetting(L"值日生")[1];
}

Settings::~Settings()
{
	for (int m = 0; m <= this->SettingNum - 1; m++) {
		delete[] this->settings[m];
	}
	delete this->dlg;
}

CString* Settings::GetSetting(CString item)
{
	int index = 0;
	while (item != this->settings[index][0] && index <= this->SettingNum - 1)index++;
	return index == SettingNum ? nullptr : settings[index];
}

void Settings::SaveSettings()
{
	GetSetting(L"ClassName")[1] = cn;
	GetSetting(L"Schedule")[1].Format(L"%d",this->ScheduleChoice);
	GetSetting(L"值日生")[1] = DName;

	CFile f;
	int index = 0;
	while (index <= this->SettingNum - 1 && this->settings[index][0].GetLength() != 0)index++;
	if (f.Open(path, CFile::modeCreate|CFile::modeWrite)) {
		CString s;
		int iindex = 0;
		int fpos = 0;
		int flen = format.GetLength();
		for (int n = 0; n <= index - 1; n++) {
			for (fpos = 0; fpos <= flen - 1; fpos++) {
				if (format[fpos] != '*')s += format[fpos];
				else {
					if(iindex <= this->ItemNum - 1)s += this->settings[n][iindex];
					iindex++;
				}
			}
			iindex = 0;
			s += "\n";
		}
		char* s2=CstringToChar(s);
		f.Write(s2, strlen(s2));
		f.Flush();
		f.Close();
	}
}

