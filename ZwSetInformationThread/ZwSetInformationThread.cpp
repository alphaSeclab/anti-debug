// ZwSetInformationThread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#pragma comment(lib,"ntdll.lib")


bool CheckDebug_SetInformationThread() {
	enum THREAD_INFO_CLASS
	{
		ThreadHideFromDebugger = 17
	};
	typedef NTSTATUS(NTAPI *ZW_SET_INFORMATION_THREAD)(
		IN HANDLE ThreadHandle,
		IN THREAD_INFO_CLASS ThreadInformationClass,
		IN PVOID ThreadInformation,
		IN ULONG ThreadInformationLength);
	ZW_SET_INFORMATION_THREAD ZwSetInformationThread;
	ZwSetInformationThread = (ZW_SET_INFORMATION_THREAD)GetProcAddress(LoadLibrary(L"ntdll.dll"), "ZwSetInformationThread");
	ZwSetInformationThread(GetCurrentThread(), ThreadHideFromDebugger, NULL, NULL);
	return true;
}

int main()
{
	CheckDebug_SetInformationThread();
	getchar();
	return 0;
}


