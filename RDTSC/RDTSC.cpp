// RDTSC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdint.h>
bool CheckDebug_RDTSC() {
	int64_t t1=0, t2=0;
	int lo=0, hi=0;
	__asm {
		rdtsc
		mov [lo], eax
		mov [hi], edx
	}
	t1 = ((int64_t)lo) | ((int64_t)hi << 32);
	__asm{
		rdtsc
		mov[lo], eax
		mov[hi], edx
	}
	t2 = ((int64_t)lo) | ((int64_t)hi << 32);
	printf("t2-t1=%llx\n", t2 - t1);
	// 不同的CPU该差值不同，所以谨慎使用这种反调试方法
	return t2 - t1 > 0x100;
}

int main()
{
	if (CheckDebug_RDTSC())
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
