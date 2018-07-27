// NtGlobalFlag.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
bool CheckDebug() {
	int nNtFlag = 0;
	__asm {
		MOV EAX, DWORD PTR FS : [0x30]
		MOV EAX, DWORD PTR DS : [EAX + 0x68]
		MOV nNtFlag, EAX
	}
	return nNtFlag==0x70;
}

int main()
{
	
	if (CheckDebug())
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