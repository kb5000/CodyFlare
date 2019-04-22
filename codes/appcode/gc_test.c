#include "utility.h"
#include "graphics.h"
#include "gc.h"
#include <stdio.h>
#include "gc_test.h"

void test_of_gc() {
	InitConsole();
	init_gc();
	gen_gc_data(int, a, 3);
	gen_gc_data(int, b, 5);
	printf("%d, %d\n", *a, *b);
	can_destroy_data(a);
	perform_gc(0);
	can_destroy_data(b);
	printf("%d: %d, %d: %d\n", is_safe_to_use(a), *a, is_safe_to_use(b), *b);
}