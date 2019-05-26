#include "sheet.h"
#include "save.h"
#include <stdio.h>
#include <string.h>
#include "timer.h"
#include "rank.h"
#include <stdlib.h>
#include "input_box.h"

typedef struct {
	char name[16];
	int score;
} RankEntry;

static const RankEntry defaultRank[16] = {
	{"ARISTOTLE", 8000},
	{"BOOLE", 7600},
	{"TUKEY", 6650},
	{"SMULLYAN", 6310},
	{"DEMORGAN", 6200},
	{"ADA", 5840},
	{"SHEFFER", 5300},
	{"PERICE", 4030},
	{"DODGSON", 3700},
	{"HARDY", 3400},
	{"RAMANUJAN", 2600},
	{"CANTOR", 2200},
	{"RUSSELL", 1850},
	{"VENN", 1500},
	{"DESCARTES", 1000},
	{"STIRLING", 650},
};


static char rankFileName[32] = "rankfile.sav";
Vector rankInfo;

void init_rank() {
	FILE* file;
	if (rankInfo.len && calls(rankInfo, len) > 0) {
		calls(rankInfo, destroy);
	}
	if (file = fopen(rankFileName, "rb")) {
		if (rankInfo.len && calls(rankInfo, len) > 0) {
			calls(rankInfo, destroy);
		}
		rankInfo = read_vector(file);
		end_save_or_read(file);
		if (calls(rankInfo, len) == 16) return;
		else calls(rankInfo, destroy);
	}
	rankInfo = gen_empty_vector(RankEntry);
	for (unsigned i = 0; i < 16; i++) {
		calls(rankInfo, push, (RankEntry*)&defaultRank[i]);
	}
	//for (int i = 0; i < 16; i++) {
	//	Vector v = gen_empty_vector(char[16]);
	//	char score[16];
	//	sprintf(score, "%d", defaultRank[i].score);
	//	calls(v, push, defaultRank[i].name);
	//	calls(v, push, score);
	//	calls(rankInfo, push, &v);
	//}
	file = fopen(rankFileName, "wb");
	save_vector(file, &rankInfo);
	end_save_or_read(file);
}

int saa_add_rank(char* name, int score) {
	int res = 0;
	RankEntry toAdd;
	strcpy(toAdd.name, name);
	toAdd.score = score;
	for (int i = 0; i < 16; i++) {
		RankEntry re = cast(RankEntry, calls(rankInfo, at, i));
		if (re.score <= score) {
			calls(rankInfo, insert, i, &toAdd);
			break;
		}
	}
	if (calls(rankInfo, len) > 16) {
		calls(rankInfo, remove, 16);
		res = 1;
	}
	FILE* file = fopen(rankFileName, "wb");
	save_vector(file, &rankInfo);
	end_save_or_read(file);
	return res;
}

void show_each_rank(Vector* vec) {
	if (show_sheet(vec, new_pos(7.7, 1), new_pos(2, 5), 16, 2, 0, 1, 0, color_by_name("DarkGrey"), color_by_name("Black"),
				   color_by_rgb(216, 192, 180), "ºÚÌå", 20, "¿¬Ìå", 18, 'C'));//disable_me_in_timer();
}

void show_rank() {
	init_rank();
	hnew(Vector, strs);
	*strs = gen_empty_vector(Vector);
	for (int i = 0; i < 16; i++) {
		Vector v = gen_empty_vector(char[16]);
		RankEntry re = cast(RankEntry, calls(rankInfo, at, i));
		char score[16];
		sprintf(score, "%d", re.score);
		calls(v, push, re.name);
		calls(v, push, score);
		pcalls(strs, push, &v);
	}
	add_func_to_timer(show_each_rank, strs, 1, 4587444, -1);
}

void update_rank(int score) {
	init_rank();
	RankEntry re = cast(RankEntry, calls(rankInfo, at, 15));
	if (score >= re.score) {
		show_input_box(score);
	}
}