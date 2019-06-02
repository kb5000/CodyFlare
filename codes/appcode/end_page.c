#include "end_page.h"
#include "ingame.h"
#include "game_particle.h"
#include "font.h"
#include "timer.h"
#include "random.h"
#include "utility.h"

void draw_firework(void* unuseful) {
	Pos pos = new_pos(RandomReal(1, 9), RandomReal(1, 6));
	show_bonus_particle(pos);
}

void show_end_page() {
	show_font("VICTORY", 3);
	add_func_to_timer(draw_firework, NULL, 90, 123400, -1);
}