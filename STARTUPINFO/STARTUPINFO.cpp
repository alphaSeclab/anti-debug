// STARTUPINFO.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
bool CheckDebug_STARTUPINFO() {
	STARTUPINFO si = {};
	GetStartupInfo(&si);
	if (si.dwX || si.dwY || si.dwXSize || si.dwYSize)
	{
		printf("%x %x %x %x\n", si.dwX, si.dwY, si.dwXSize, si.dwYSize);
		return true;
	}
	return false;
}

int main()
{
	if (CheckDebug_STARTUPINFO())
	{
		printf("发现调试器\n");
	}
	else
	{
		printf("正常运行\n");
	}
	getchar();
	return 0;
}
