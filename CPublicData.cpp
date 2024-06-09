#include"CPublicData.h"
void CPublicData::CrtMutex() {
	CPublicData::mutex = CreateMutex(NULL, true, L"{hj7r-b78o-85x9}");
}
void CPublicData::DelMutex() {
	CloseHandle(CPublicData::mutex);
}
HANDLE CPublicData::mutex = 0;