#pragma once

typedef struct _My_Timer {
	UINT_PTR id;
	void (*func)(void*);
	UINT uElapse;
	void (*destroy)(struct _My_Timer* self);
	void (*reset)(struct _My_Timer* self);
} Timer;

Timer new_timer(UINT uElapse, void func(void*));
