// POP SS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
bool CheckDebug_PopSS()
{
	bool bDebugged = false;
	__asm {
		push ss
		pop ss
		pushfd
		test BYTE PTR SS : [ESP + 1], 1
		jne debugged
		jmp over
debugged:
		mov bDebugged,1
over:
		popfd
	}
	return bDebugged;
}
int main()
{
	if (CheckDebug_PopSS())
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
