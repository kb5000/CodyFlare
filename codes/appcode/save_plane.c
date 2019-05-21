#include "save.h"
#include "plane.h"
#include "timer.h"
#include "listbox.h"
#include "save_plane.h"
#include "ingame.h"

void save_plane() {
	ListHandler* plane = plane_list();
	Vector vec = list_to_vec(plane, sizeof(Plane));
	FILE* f = start_save();
	save_vector(f, &vec);
	int a = current_score(), b = current_hit_plane();
	save_data(f, &a, sizeof(int));
	save_data(f, &b, sizeof(int));
	end_save_or_read(f);
}

void read_plane(FILE* f) {
	Vector v = read_vector(f);
	for (unsigned i = 0, len = calls(v, len); i < len; i++) {
		Plane p = cast(Plane, calls(v, at, i));
		add_plane(p);
	}
	int score, hit;
	get_data(f, &score, sizeof(int));
	get_data(f, &hit, sizeof(int));
	set_score_info(score, hit);
	end_save_or_read(f);
}

void select_saves() {
	ListHandler lh = explore_files();
	if (calls(lh, len) == 0) return;
	show_list_box(1, lh, new_pos(1, 2), 0);
	add_func_to_timer(get_element_to_load, NULL, 1, 998800, -1);
}

void get_element_to_load(void* unuseful) {
	if (!is_box_open()) {
		int n = get_current_list_index();
		ListHandler lh = explore_files();
		Node* node = (Node*)(calls(lh, at, n));
		FILE* f = start_read(cast(FileName, node->data));
		
		reload_game();
		load_from_file();
		read_plane(f);
		start_display_planes();
		disable_me_in_timer();
	}
}
