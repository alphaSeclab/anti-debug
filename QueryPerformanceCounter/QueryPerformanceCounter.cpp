// QueryPerformanceCounter.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
bool CheckDebug_QueryPerformanceCounter() {
	LARGE_INTEGER startTime , endTime ;
	QueryPerformanceCounter(&startTime);
	printf("我是核心代码\n也可以是核心代码前的反调试时间检测代码\n");
	QueryPerformanceCounter(&endTime);
	printf("%llx\n", endTime.QuadPart - startTime.QuadPart);
	return endTime.QuadPart - startTime.QuadPart > 0x500;
}

int main()
{
	if (CheckDebug_QueryPerformanceCounter())
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

