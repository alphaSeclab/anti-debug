// EnumProcess.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <TlHelp32.h>
bool CheckDebug_EnumProcess() {
	PROCESSENTRY32 pe32 = { sizeof(pe32) };
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	Process32First(hProcessSnap, &pe32);
	do
	{
		// 这里只比较了OllyDbg,也可以添加其他的调试分析工具名
		if (_tcsicmp(pe32.szExeFile, TEXT("OllyDbg.exe")) == 0)
		{
			CloseHandle(hProcessSnap);
			return TRUE;
		}
	} while (Process32Next(hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);
	return FALSE;
}

int main()
{
	if (CheckDebug_EnumProcess())
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