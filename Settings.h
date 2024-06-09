#pragma once
#include"StrConvert.h"
//Transparent
#define TRANSPARENT_MODE LWA_COLORKEY | LWA_ALPHA
#define TRANSPARENCY 100
#define TRANSPARENT_COLOR_THROUGH	RGB(10,10,10)//Í¸Ã÷´©Í¸É«
//color
#define COLOR_WHITE	RGB(255,255,255)	
#define COLOR_YELLOW RGB(255,210,88)
#define COLOR_BLACK RGB(0,0,0)
#define COLOR_GRAY RGB(150,150,150)
//Size
#define WINDOW_WIDTH 75
#define WINDOW_HEIGHT 1000
#define TEXT_SIZE 20
//
#define NAME_HEIGHT 20
#define NAME_DBUTTON 10 
#define DBUTTON_HEIGHT 20
#define DBUTTON_DUTY 10
#define DUTY_HEIGHT 30
#define DUTY_SBUTTON 10
#define SBUTTON_HEIGHT 20
#define SBUTTON_SCHEDULE 10
#define SCHEDULE_HEIGHT 800
//Message
#define WM_GET_DIALOG_CSTRING		(WM_USER + 200)
#define WM_SHOWTASK (WM_USER+201)
//Number
#define NUM_LESSON 12

class SettingsDlg;
class Settings {
public:
	CString DName;
	int ScheduleChoice;
	CString cn;

	SettingsDlg* dlg;

	Settings(CString path, WCHAR start, WCHAR end,CString format);
	~Settings();

	bool AddSettings(CString setting, CString format=L"");
	bool ReadSetting();
	bool TransSettings();
	CString* GetSetting(CString item);
	void SaveSettings();

private:
	int SettingNum = 20;
	int ItemNum;

	WCHAR start, end;
	CString path;

	CString format;
	CString* settings[20];

	CString SName[20];
	int SNum=0;
};