#include "spline_test.h"
#include "graphics.h"
#include "timer.h"
#include "utility.h"
#include "vector.h"
#include "object_test.h"
#include <math.h>
#include <stdlib.h>
#include "animes.h"

void draw_bonus_enemy(Pos* t);
void test_of_object()
{
	InitGraphics();
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	start_global_timer();
	//enemy1_drawer();
	hnew(Pos, pos);
	set_pos(pos, 5, 3.5);
	//add_func_to_timer(draw_player_plane, pos, 1, 1221, -1);
	*pos = add_pos(*pos, new_pos(0.5, 0));
	//draw_basic_enemy(pos);
	//hnew(double, t);
	//*t = -PI / 4;
	*pos = add_pos(*pos, new_pos(0.5, 0));
	add_func_to_timer(draw_infernal_enemy, pos, 1, 1221, -1);
}

