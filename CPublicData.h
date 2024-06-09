#pragma once
#include"pch.h"
class CPublicData {
public:
	static HANDLE mutex;
	static void CrtMutex();
	static void DelMutex();
};