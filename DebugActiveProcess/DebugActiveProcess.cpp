// DebugActiveProcess.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>

int main()
{
	// 尝试打开互斥体，确定是否首次运行程序
	HANDLE hMutex = OpenMutex(MUTEX_MODIFY_STATE, FALSE, L"Global\\MyMutex");
	if (hMutex)
	{
		// 打开成功说明第2次运行，执行正常代码
		printf("正被调试运行！\n");
		getchar();
	}
	else
	{
		// 打开失败说明第1次运行，创建互斥体，并调试创建自身进程
		CreateMutex(NULL, FALSE, L"Global\\MyMutex");
		TCHAR szPath[MAX_PATH] = {};
		GetModuleFileName(NULL, szPath, MAX_PATH);
		// 调试方式打开程序
		STARTUPINFO si = { sizeof(STARTUPINFO) };
		PROCESS_INFORMATION pi = {};
		// 正常创建，后面附加调试
		BOOL bStatus = CreateProcess(szPath, NULL, NULL, NULL, FALSE,
			CREATE_NEW_CONSOLE,
			NULL, NULL, &si, &pi);
		if (!bStatus) {
			printf("创建进程失败!\n");
			return 0;
		}
		if (!DebugActiveProcess(pi.dwProcessId)) {
			printf("附加进程失败!\n");
			return 0;
		}
		// 初始化调试事件结构体
		DEBUG_EVENT DbgEvent = { 0 };
		DWORD dwState = DBG_EXCEPTION_NOT_HANDLED;
		// 等待目标Exe产生调试事件
		BOOL bExit = FALSE;
		while (!bExit) {
			WaitForDebugEvent(&DbgEvent, INFINITE);
			if (DbgEvent.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT)
			{
				// 被调试进程退出
				bExit = TRUE;
			}
			ContinueDebugEvent(DbgEvent.dwProcessId, DbgEvent.dwThreadId, dwState);
		}
		return 0;
	}
	return 0;
}