// Explorer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#include <process.h>
#include <TlHelp32.h>
#pragma comment(lib,"ntdll.lib")
bool CheckDebug_Explorer() {
	struct PROCESS_BASIC_INFORMATION
	{
		DWORD ExitStatus;
		DWORD PebBaseAddress;
		DWORD AffinityMask;
		DWORD BasePriority;
		ULONG UniqueProcessId;
		ULONG InheritedFromUniqueProcessId;
	}pbi = {};
	NtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, (PVOID)&pbi, sizeof(pbi), NULL);
	PROCESSENTRY32 pe32 = { sizeof(pe32) };
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	Process32First(hProcessSnap, &pe32);
	do
	{
		if (pbi.InheritedFromUniqueProcessId == pe32.th32ProcessID)
		{
			if (_tcsicmp(pe32.szExeFile, TEXT("explorer.exe")) == 0)
			{
				CloseHandle(hProcessSnap);
				return FALSE;
			}
			else
			{
				CloseHandle(hProcessSnap);
				return TRUE;
			}
		}
	} while (Process32Next(hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);
	return FALSE;
}

int main()
{
	if (CheckDebug_Explorer())
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