#include "save_test.h"
#include "save.h"
#include <string.h>
#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>

void test_of_save() {
	InitConsole();
	char p[32] = "i8ufsssrhne";
	FILE* f = start_save();
	save_data(f, p, strlen(p) + 1);
	end_save_or_read(f);
	ListHandler lh = explore_files();
	char pp[32];
	for (Node* node = lh.head; node; node = node->next) {
		FileName fl = *(FileName*)(node->data);
		f = start_read(*(FileName*)node->data);
		get_data(f, pp, 32);
		end_save_or_read(f);
		printf("%s\n", fl.name);
		printf("%s\n", pp);
	}
}