// BeingDebugged.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

bool CheckDebug() {
	bool bDebugged = false;
	__asm {
		MOV EAX, DWORD PTR FS : [0x30]
		MOV AL, BYTE PTR DS : [EAX + 2]
		MOV bDebugged, AL
	}
	return bDebugged;
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


