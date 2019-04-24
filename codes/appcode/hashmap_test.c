#include "hashmap_test.h"
#include "hashmap.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

void prt(void* data, void* para) {
	printf("For %d\n", cast(int, data));
}

int rif(void* data, void* para) {
	int t = cast(int, data);
	return t > 5;
}

void test_of_hashmap() {
	InitConsole();
	HashMap map = new_hash_map(sizeof(int));
	int c[5] = {0, 22, 987, 1, 1 << 16};
	int* t[5];
	for (int i = 0; i < 5; i++) {
		t[i] = (int*)malloc(sizeof(int));
		*t[i] = 2 * i;
		map.insert_data(&map, c[i], t[i]);
	}
	map.remove_data(&map, 1 << 16);
	for (int i = 0; i < 5; i++) { 
		if (!map.exist_data(&map, c[i])) continue;
		printf("%d: %d\n", map.hash_func(&map, c[i]), cast(int, map.get_data(&map, c[i])));
	}
	map.remove_if(&map, rif, NULL);
	map.for_each(&map, prt, NULL);
	for (unsigned i = 0; i < 10; i++) {
		printf("%d\n", cast(int,map.mapData.at(&map.mapData, i)));
	}
	map.destroy(&map);
}