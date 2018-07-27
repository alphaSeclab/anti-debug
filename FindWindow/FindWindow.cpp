// FindWindow.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
bool CheckDebug_FindWindow() {
	// OD的主窗口类名为 OLLYDBG，也可以查询其他调试器的类名
	// 其他常用调试器的类名可以使用Spy++查看
	if (FindWindow(TEXT("OLLYDBG"), NULL))
		return true;
	return false;
}
BOOL CALLBACK EnumWindowProc(HWND hWnd, LPARAM lParam) {
	TCHAR winTitle[0x100] = {};
	GetWindowText(hWnd, winTitle, 0x100);
	if (_tcsstr(winTitle, TEXT("OllyDbg")))
	{
		// nFind=true
		*((int*)lParam) = true;
		// 找到目标窗口停止遍历
		return false;
	}
	// 继续遍历下一个窗口
	return true;
}
bool CheckDebug_EnumWindow() {
	int nFind = false;
	EnumWindows(EnumWindowProc, (LPARAM)&nFind);
	return nFind != 0;
}
int main()
{
	if (CheckDebug_EnumWindow())
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
