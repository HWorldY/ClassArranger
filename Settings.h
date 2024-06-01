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
//Number
#define NUM_LESSON 12
//
#define RELATIVEPATH 0
class SettingsDlg;
class Settings {
public:
	int SettingNum = 20;
	int ItemNum;

	CString DName;
	int ScheduleChoice;
	CString cn;

	CString path;
	Settings(CString path, WCHAR start, WCHAR end,CString format);
	~Settings();
	CString format;
	SettingsDlg* dlg;
	CString* settings[20];
	CString* GetSetting(CString item);
	void SaveSettings();
};