#include "save.h"
#include "plane.h"
#include "timer.h"

void save_plane() {
	ListHandler* plane = plane_list();
	Vector vec = list_to_vec(plane, sizeof(Plane));
	FILE* f = start_save();
	save_vector(f, &vec);
	save_data(f, current_score(), sizeof(int));
	save_data(f, current_hit_plane(), sizeof(int));
	end_save_or_read(f);
}

void read_plane(FILE* f) {
	read_vector(f);
	int score, hit;
	get_data(f, &score, sizeof(int));
	get_data(f, &hit, sizeof(int));
	set_score_info(score, hit);
	end_save_or_read(f);
}
