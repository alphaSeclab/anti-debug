// NtQuerySystemInformation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#pragma comment(lib,"ntdll.lib")
bool CheckDebug_KernelDebug() {
	struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION
	{
		BOOLEAN DebuggerEnabled;
		BOOLEAN DebuggerNotPresent;
	}DebuggerInfo = { 0 };
	NtQuerySystemInformation(
		(SYSTEM_INFORMATION_CLASS)0x23,		//查询信息类型
		&DebuggerInfo,						//输出查询信息
		sizeof(DebuggerInfo),				//查询类型大小
		NULL);								//实际返回数据大小
	return DebuggerInfo.DebuggerEnabled;
}

int main()
{
	if (CheckDebug_KernelDebug())
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


