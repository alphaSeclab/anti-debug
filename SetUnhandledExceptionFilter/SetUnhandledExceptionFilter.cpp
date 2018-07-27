// SetUnhandledExceptionFilter.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

LONG WINAPI Fun(
	_In_ struct _EXCEPTION_POINTERS *ExceptionInfo
) {
	// 跳过mov bDebug, 1这条指令
	// int 3异常时，eip会被回拨到cc处，所以要+5
	ExceptionInfo->ContextRecord->Eip += 5;
	return EXCEPTION_CONTINUE_EXECUTION;
}
bool CheckDebug_SetUnhandledExceptionFilter() {
	bool bDebug = false;
	__asm {
		__emit(0xCC);
		// 正常运行时，Fun函数会跳过这条指令
		// 调试时，调试器会不停收到int 3异常，程序崩溃
		mov bDebug, 1
	}
	return bDebug;
}
int main()
{
	SetUnhandledExceptionFilter(Fun);
	if (CheckDebug_SetUnhandledExceptionFilter())
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