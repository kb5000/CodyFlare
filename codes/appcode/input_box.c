#include "input_box.h"
#include "imgui.h"
#include "extgraph.h"
#include "timer.h"
#include "rank.h"
#include <string.h>
#include <ctype.h>
#include "utility.h"
#include "plane.h"

static char buffer[16], name[16];

void input_box(int* score) {
	set_color(color_by_rgb(216, 192, 180));
	drawRectangle(3, 1.2, 4, 1.6, 1);
	set_color(color_by_name("Black"));
	char sc[64];
	sprintf(sc, "Congratulations! Your score is %d", current_score());
	drawLabel(3.8, 2.5, sc);
	drawLabel(4.5, 2.2, "Enter Your Name");
	if (textbox(2423423, 3.5, 1.7, 3, 0.3, buffer, 10)) {
		for (int i = 0; i < 9; i++) {
			buffer[i] = toupper(buffer[i]);
		}
		for (int i = 0, j = 0; i < 10; i++) {
			if (buffer[i] >= 'A' && buffer[i] <= 'Z' || buffer[i] == '\0') {
				name[j] = buffer[i];
				j++;
			}
		}
		strcpy(buffer, name);
	}
	if (button(20413433, 4.6, 1.4, 0.8, 0.2, "È·¶¨")) {
		saa_add_rank(name, *score);
		show_rank();
		disable_me_in_timer();
	}
}

void show_input_box(int score) {
	hnew(int, scr);
	*scr = score;
	add_func_to_timer(input_box, scr, 1, 48984874, -1);
}

