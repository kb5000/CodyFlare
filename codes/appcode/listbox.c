#include "listbox.h"
#include "graphics.h"
#include "extgraph.h"
#include "input.h"
#include "imgui.h"
#include "color.h"
#include "save.h"
#include "animes.h"
#include <Windows.h>

static int boxValidFlag = 1;
static Pos bias;
static int currentListPos = 0;
static int preserve = 0;
static int diffListPos = 0;
static int currentMovingFlag = 0;
static int lockMoveTime = 0;
static int isDelFile = 0;

typedef struct {
	ListHandler list;
	int n;
	Pos position;
} ListBoxHolder;

static Node* get_pth_cycle_entry(ListHandler* lh, int n, int p) {
	if (p < 0) p += pcall0(lh, len);
	return pcalls(lh, at, (n + p) % pcall0(lh, len));
}

static void draw_list_entries(ListHandler* list, int n, Pos position, double yBias) {
	if (!boxValidFlag) {
		//boxValidFlag = 1;
		//pcalls(list, destroy);
		disable_me_in_timer();
	}
	if (currentListPos < 0) currentListPos = pcall0(list, len) - 1;
	if (currentListPos >= (int)pcall0(list, len)) currentListPos = 0;
	FileName name[5] = {{""}}; //all clear to 0
	//if list is not empty, show cyclely
	n = currentListPos;
	if (list->head) {
		name[0] = cast(FileName, get_pth_cycle_entry(list, n, -2)->data);
		name[1] = cast(FileName, get_pth_cycle_entry(list, n, -1)->data);
		name[2] = cast(FileName, get_pth_cycle_entry(list, n, 0)->data);
		name[3] = cast(FileName, get_pth_cycle_entry(list, n, 1)->data);
		name[4] = cast(FileName, get_pth_cycle_entry(list, n, 2)->data);
	}
	if (yBias >= 0.2) {
		currentListPos++;
		bias.x = 0;
		preserve = 6;
	} else if (yBias <= -0.2) {
		currentListPos--;
		bias.x = 0;
		preserve = 6;
		currentMovingFlag = 0;
	}
	if (preserve-- > 0 || lockMoveTime++ > 24) {
		diffListPos = 0;
		bias.x = 0;
		currentMovingFlag = 0;
		lockMoveTime = 0;
	}
	if (diffListPos == 1) {
		drawBox(position.x, position.y + yBias, 1.8, 0.2, 0, name[3].name, 'M', "Blue");
	} else {
		drawBox(position.x, position.y + yBias, 1.8, 0.2, 0, name[3].name, 'M', "Red");
	}
	if (diffListPos == -1) {
		drawBox(position.x, position.y + 0.4 + yBias, 1.8, 0.2, 0, name[1].name, 'M', "Blue");
	} else {
		drawBox(position.x, position.y + 0.4 + yBias, 1.8, 0.2, 0, name[1].name, 'M', "Red");
	}

	if (yBias > 0) {
		drawBox(position.x, position.y - 0.2 + yBias , 1.8, 0.2, 0, name[4].name, 'M', "Red");
	} else if (yBias < 0) {
		drawBox(position.x, position.y + 0.6 + yBias, 1.8, 0.2, 0, name[0].name, 'M', "Red");
	}

	if (diffListPos != 0) {
		drawBox(position.x, position.y + 0.2 + yBias, 1.8, 0.2, 0, name[2].name, 'M', "Red");
	} else {
		drawBox(position.x, position.y + 0.2 + yBias, 1.8, 0.2, 0, name[2].name, 'M', "Blue");
	}

	set_color(color_by_name("White"));
	drawRectangle(position.x, position.y - 0.21, 1.8, 0.2, 1);
	drawRectangle(position.x, position.y + 0.61, 1.8, 0.2, 1);
	set_color(color_by_name("Red"));
	drawRectangle(position.x, position.y, 1.8, 0.6, 0);
	drawRectangle(position.x - 0.03, position.y - 0.03, 1.86, 0.67, 0);
}

void dir_to_change(int key, Pos* yBias, int event) {
	if (key == 0x26 && event == 0 && currentMovingFlag == 0) {			//up
		yBias->x = 0;
		draw_anime_accelerate(yBias, new_pos(-0.2, 0), 0.005);
		currentMovingFlag = 1;
		diffListPos = -1;
	} else if (key == 0x28 && event == 0 && currentMovingFlag == 0) {		//down
		yBias->x = 0;
		draw_anime_accelerate(yBias, new_pos(+0.2, 0), 0.005);
		currentMovingFlag = 1;
		diffListPos = 1;
	}
}

void draw_list_entries_pack(ListBoxHolder* lbh) {
	draw_list_entries(&lbh->list, lbh->n, lbh->position, bias.x);
}

void show_list_box(int id, ListHandler list, Pos position, int currentItem) {
	if (calls(list, len) == 0) return;
	boxValidFlag = 1;
	hnew(ListBoxHolder, lbh);
	lbh->list = list;
	lbh->n = currentItem;
	lbh->position = position;
	currentListPos = currentItem;
	add_func_to_timer(draw_list_entries_pack, lbh, 1, id, -1);
	add_to_key_process(0x26, dir_to_change, &bias); //down
	add_to_key_process(0x28, dir_to_change, &bias); //up
	add_to_key_process('A', close_list_box, NULL);
	add_to_key_process('D', del_save_file, lbh);
}

int get_current_list_index() {
	return currentListPos;
}

int is_box_open() {
	return boxValidFlag;
}

void close_list_box(int key, void* unuseful, int event) {
	boxValidFlag = 0;
	isDelFile = 0;
}

void del_save_file(int key, ListHandler* lh, int event) {
	if (boxValidFlag && event == 0) {
		isDelFile = 1;
		FileName* fn = (FileName*)pcalls(lh, at, currentListPos)->data;
		remove(fn->name);
		boxValidFlag = 0;
	}
}

int is_del_file() {
	return isDelFile;
}
