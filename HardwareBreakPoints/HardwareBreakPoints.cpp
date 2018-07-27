// HardwareBreakPoints.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
// API查询
bool CheckDebug_HB()
{
	CONTEXT context;
	HANDLE hThread = GetCurrentThread();
	context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	GetThreadContext(hThread, &context);
	if (context.Dr0 != 0 || context.Dr1 != 0 || context.Dr2 != 0 || context.Dr3 != 0)
	{
		return TRUE;
	}
	return FALSE;
}
// 触发异常查询
bool CheckDebug_HB_EXCEPTION()
{
	BOOL bDebugging = FALSE;
	__asm {
		// install SEH
		push handler
		push DWORD ptr fs : [0]
		mov DWORD ptr fs : [0], esp
		__emit(0xcc)
		mov bDebugging, 1
		jmp normal_code
handler :
		mov eax, dword ptr ss : [esp + 0xc];// ContextRecord
		mov dword ptr ds : [eax + 0xb8], offset normal_code;
		mov ecx, [eax + 4];	// Dr0
		or ecx, [eax + 8];	// Dr1
		or ecx, [eax + 0x0C];// Dr2
		or ecx, [eax + 0x10];// Dr3
		je NoDebugger;
		mov ecx, [eax + 0xb4];// ebp
		// vs2015 debug下bDebugging的地址为ebp-c
		mov [ecx-0x0c],1 // bDebugging
	NoDebugger:
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
	if (CheckDebug_HB_EXCEPTION())
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
