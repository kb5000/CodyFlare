#include "animes.h"

typedef struct {
	Pos* pos;
	Pos mid;
	Pos end;
	Pos accu;
	Pos speed;
} AccuAnime;

void accelerate_anime_drawer(void* data) {
	AccuAnime* acc = (AccuAnime*)data;
	if (fabs(acc->pos->x - acc->end.x) <= fabs(acc->speed.x)) {
		*acc->pos = acc->end;
		return;
	}
	if (acc->accu.x > 0 && acc->speed.x > 0 || acc->accu.x < 0 && acc->speed.x < 0) {
		*acc->pos = add_pos(*acc->pos, acc->speed);
		acc->speed = add_pos(acc->speed, acc->accu);
		if ((acc->mid.x - acc->pos->x) * (acc->end.x - acc->mid.x) < 0) {
			acc->accu = sub_pos(new_pos(0, 0), acc->accu);
		}
	} else {
		*acc->pos = add_pos(*acc->pos, acc->speed);
		acc->speed = add_pos(acc->speed, acc->accu);
	}
}

void draw_anime_accelerate(Pos* start, Pos end, double accu) {
	AccuAnime acc = {
		start,
		new_pos((end.x - start->x) / 2, (end.y - start->y) / 2),
		end,
		polar_to_rect(new_pos(accu, pos_arc(sub_pos(end, *start)))),
		new_pos(0, 0),
	};
	AccuAnime* para = (AccuAnime*)malloc(sizeof(AccuAnime));
	*para = acc;
	int t = (int)(2 * sqrt((end.x - start->x) / acc.accu.x) + 1);
	add_func_to_timer(accelerate_anime_drawer, para, 1, Unique_ID("Accu"), t);
}