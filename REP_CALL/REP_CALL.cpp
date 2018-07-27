// REP_CALL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
bool CheckDebug_CheckRepCC()
{
	BOOL bDebugging = FALSE;
	__asm {
		xor eax,eax
		xor ecx,ecx
		inc ecx
		lea esi,key
		// 此处步过时key处会被下0xCC断点
		// 将key处的首字节给AL
		rep lodsb
key:
		cmp al,0xcc
		je debuging
		jmp over
debuging:
		mov bDebugging,1
over :
	}
	return bDebugging;
}
int main()
{
	if (CheckDebug_CheckRepCC())
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
