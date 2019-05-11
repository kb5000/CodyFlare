#include "ammo_test.h"
#include "ammo.h"
#include "anime_test.h"
#include "collision.h"
#include "timer.h"
#include "input.h"
#include <stdlib.h>

static void update(int* num) {
	if (++*num == 5) {
		add_ammo(0, new_pos(3, 6), new_pos(0, -0.1));
		*num = 0;
	}
}

void test_of_ammo() {
	common_anime_test_init();
	init_col_detector();
	init_ammo_system();
	hnew(int, a);
	*a = 0;
	add_func_to_timer(update, a, 1, 1, -1);
	start_update_ammo();
}