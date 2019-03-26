#pragma once
#include <time.h>
#include <minwindef.h>
#include <WinBase.h>

typedef struct _My_Timer {
	DWORD startTime;
	DWORD tickPeroid;
	void (*start)(struct _My_Timer* self);
	void (*stop)(struct _My_Timer* self);
	void (*func_when_tick)(void* paras);
} Timer;