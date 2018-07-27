// SEH.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

bool CheckDebug_SEH() {
	BOOL bDebugging = FALSE;
	__asm {
		// install SEH
		push handler
		push DWORD ptr fs : [0]
		mov DWORD ptr fs : [0], esp
		__emit(0xcc)
		// 只检测有无调试器
		// 若把mov bDebugging, 1改成__emit(0xE9)
		// 在调试器中就会跑飞
		mov bDebugging, 1
		jmp normal_code
handler :
		mov eax, dword ptr ss : [esp + 0xc];// ContextRecord
		mov dword ptr ds : [eax + 0xb8], offset normal_code
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
	if (CheckDebug_SEH())
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