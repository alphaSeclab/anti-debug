// NtQueryInformationProcess.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#pragma comment(lib,"ntdll.lib")


bool CheckDebug_DebugPort() {
	DWORD dwDebugPort = 0;
	NtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort, &dwDebugPort, 4, 0);
	return dwDebugPort == -1;
}

bool CheckDebug_DebugHandle() {
	DWORD dwDebugHandle = 0;
	NtQueryInformationProcess(GetCurrentProcess(), (PROCESSINFOCLASS)0x1E, &dwDebugHandle, 4, 0);
	return dwDebugHandle != 0;
}

// 此方法win7下已失效
bool CheckDebug_DebugFlags() {
	bool bDebugFlags = 0;
	NtQueryInformationProcess(GetCurrentProcess(), (PROCESSINFOCLASS)0x1F, &bDebugFlags, 1, 0);
	printf("%d\n", bDebugFlags);
	return bDebugFlags == 0;
}


int main()
{

	if (CheckDebug_DebugHandle())
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