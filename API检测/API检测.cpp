// API检测.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
bool CheckDebug_API() {
	PBYTE pCC = (PBYTE)MessageBoxW;
	if (*pCC == 0xCC)
	{
		return true;
	}
	MessageBoxW(0, L"未发现调试器！\n", 0, 0);
	return false;
}

int main()
{
	if (CheckDebug_API())
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
