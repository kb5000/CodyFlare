#include "list_test.h"
#include "linked_list.h"
#include <stdio.h>

void display_node(void* data) {
	printf("%d, ", *(int*)data);
}

void test_of_list() {
	int* c[10];
	for (int i = 0; i < 10; i++) {
		c[i] = (int*)malloc(sizeof(int));
		*c[i] = i;
	}
	ListHandler listHandler = new_list(c[0]);
	for (int i = 2; i < 10; i++) {
		listHandler.push_back(&listHandler, c[i]);
	}
	printf("len = %u\n", listHandler.len(&listHandler));
	printf("tail is %d\n", *(int*)listHandler.tail->data);
	listHandler.nowpos = listHandler.at(&listHandler, 3);
	listHandler.remove_after(&listHandler);
	listHandler.insert_after(&listHandler, c[1]);
	listHandler.for_each(&listHandler, display_node);
	listHandler.destroy(&listHandler);
}
