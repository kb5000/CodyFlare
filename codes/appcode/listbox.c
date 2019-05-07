#include "listbox.h"
#include "graphics.h"
#include "extgraph.h"
#include "input.h"
#include "imgui.h"
#include "color.h"
#include "save.h"

static int entryAddFlag = 0;

static void draw_list_entries(ListHandler list, int n, Pos position) {
	FileName name[3] = {{""}}; //all clear to 0
	//if list is not empty, show cyclely
	if (list.head) {
		name[1] = cast(FileName, calls(list, at, n));
		if (n == 0) {
			name[0] = cast(FileName, list.tail->data);
		} else {
			name[0] = cast(FileName, calls(list, at, n - 1));
		}
		if (n == calls(list, len) - 1) {
			name[2] = cast(FileName, list.head->data);
		} else {
			name[2] = cast(FileName, calls(list, at, n + 1));
		}
	}
	//set_color(color_by_name("Red"));
	drawBox(position.x, position.y, 1.4, 0.2, 0, name[2].name, 'M', "Red");
	drawBox(position.x, position.y + 0.2, 1.4, 0.2, 0, name[1].name, 'M', "Red");
	drawBox(position.x, position.y + 0.4, 1.4, 0.2, 0, name[0].name, 'M', "Red");
}

void dir_to_change(int key, ListHandler* list, int event) {
	if (key == 0x26 && event == 0) {			//up
		entryAddFlag--;
		if (entryAddFlag < 0) entryAddFlag = pcall0(list, len) - 1;
	} else if (key == 0x28 && event == 0) {		//down
		entryAddFlag++;
		if (entryAddFlag >= (int)pcall0(list, len)) entryAddFlag = 0;
	}
}

Node* show_list_box(int id, ListHandler list, Pos position, int currentItem) {
	
	return NULL;
}
