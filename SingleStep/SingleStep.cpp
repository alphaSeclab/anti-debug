// SingleStep.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
bool CheckDebug_SingleStep()
{
	bool bDebugged = false;
	__asm {
		// install SEH
		push handler
		push DWORD ptr fs : [0]
		mov DWORD ptr fs : [0], esp
		pushfd
		or dword ptr ss : [esp], 0x100
		popfd
		// 被调试就继续执行
		nop
		mov bDebugged,1
		jmp normal_code
handler :
		mov bDebugged, 1
		mov eax, dword ptr ss : [esp + 0xc]
		mov ebx, normal_code
		mov dword ptr ds : [eax + 0xb8], ebx
		xor eax, eax
		retn
normal_code :
		//   remove SEH
		pop dword ptr fs : [0]
		add esp, 4
	}
	return bDebugged;
}
int main()
{
	if (CheckDebug_SingleStep())
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