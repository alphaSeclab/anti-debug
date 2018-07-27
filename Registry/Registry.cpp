// Registry.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
bool CheckDebug_Registry() {
	// 判断当前系统是32还是64位
	BOOL b64 = FALSE;
	IsWow64Process(GetCurrentProcess(), &b64);
	HKEY hkey = NULL;
	TCHAR *reg = b64 ?
		TEXT("SOFTWARE\\Wow6432Node\\Microsoft\\WindowsNT\\CurrentVersion\\AeDebug")
		: TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug");
	// 打开注册表键
	DWORD ret = RegCreateKey(HKEY_LOCAL_MACHINE, reg, &hkey);
	if (ret != ERROR_SUCCESS) return FALSE;
	TCHAR *subkey = TEXT("Debugger");
	TCHAR value[256] = {};
	DWORD len = 256;
	// 查询对应项的值
	ret = RegQueryValueEx(hkey, subkey, NULL,NULL,(LPBYTE)value, &len);
	RegCloseKey(hkey);
	// 这里只查找了OD，也可以同时查找WinDbg,x64Dbg等常用调试器
	if (_tcsstr(value, TEXT("OLLYDBG")) != NULL)
		return TRUE;
	return FALSE;
}

int main()
{
	if (CheckDebug_Registry())
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
