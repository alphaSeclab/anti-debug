// NtQqueryObject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#pragma comment(lib,"ntdll.lib")
bool CheckDebug_QueryObject() {
	typedef struct _OBJECT_TYPE_INFORMATION
	{
		UNICODE_STRING TypeNames;
		ULONG TotalNumberOfHandles;
		ULONG TotalNumberOfObjects;
	}OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;
	typedef struct _OBJECT_ALL_INFORMATION
	{
		ULONG NumberOfObjectsTypes;
		OBJECT_TYPE_INFORMATION ObjectTypeInfo[1];
	}OBJECT_ALL_INFORMATION, *POBJECT_ALL_INFORMATION;
	//1.获取欲查询信息大小
	ULONG uSize = 0;
	NtQueryObject(NULL, (OBJECT_INFORMATION_CLASS)0x03, &uSize, sizeof(uSize), &uSize);
	//2.获取对象大信息
	POBJECT_ALL_INFORMATION pObjectAllInfo = (POBJECT_ALL_INFORMATION) new BYTE[uSize+4];
	NtQueryObject(NULL, (OBJECT_INFORMATION_CLASS)0x03, pObjectAllInfo, uSize, &uSize);
	//3.循环遍历并处理对象信息
	POBJECT_TYPE_INFORMATION pObjectTypeInfo = pObjectAllInfo->ObjectTypeInfo;
	for (int i = 0; i < pObjectAllInfo->NumberOfObjectsTypes; i++)
	{
		//3.1查看此对象的类型是否为DebugObject
		if (!wcscmp(L"DebugObject", pObjectTypeInfo->TypeNames.Buffer))
		{
			delete[] pObjectAllInfo;
			return true;
		}
		//3.2获取对象名占用空间大小(考虑到了结构体对齐问题)
		ULONG uNameLength = pObjectTypeInfo->TypeNames.Length;
		ULONG uDataLength = uNameLength - uNameLength % sizeof(ULONG) + sizeof(ULONG);
		//3.3指向下一个对象信息
		pObjectTypeInfo = (POBJECT_TYPE_INFORMATION)pObjectTypeInfo->TypeNames.Buffer;
		pObjectTypeInfo = (POBJECT_TYPE_INFORMATION)((PBYTE)pObjectTypeInfo + uDataLength);
	}
	delete[] pObjectAllInfo;
	return false;
}

int main()
{
	if (CheckDebug_QueryObject())
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
