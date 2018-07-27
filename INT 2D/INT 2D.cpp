// INT 2D.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
bool CheckDebug_INT_2D() {
	BOOL bDebugging = FALSE;
	__asm {
		// install SEH
		push handler
		push DWORD ptr fs : [0]
		mov DWORD ptr fs : [0], esp
		// OD会忽略0x2d和nop，继续向后执行
		// 这时候可以选择只是检测调试器还是跑飞
		int 0x2d
		nop
		mov bDebugging, 1
		jmp normal_code
handler :
		mov eax, dword ptr ss : [esp + 0xc]
		mov dword ptr ds : [eax + 0xb8], offset normal_code
		mov bDebugging, 0
		xor eax, eax
		retn
normal_code :
		//   remove SEH
		pop dword ptr fs : [0]
		add esp, 4
	}
	return bDebugging;
}

int main()
{
	if (CheckDebug_INT_2D())
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
