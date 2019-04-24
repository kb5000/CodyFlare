#pragma once
#include "vector.h"

typedef struct _My_Hash_Map {
	Vector mapData;
	//unsigned sizeOfElement;
	int (*hash_func)(struct _My_Hash_Map* self, int key);
	void (*insert_data)(struct _My_Hash_Map* self, int key, void* data);
	void (*insert_key)(struct _My_Hash_Map* self, int key);
	int (*exist_data)(struct _My_Hash_Map* self, int key);
	void* (*get_data)(struct _My_Hash_Map* self, int key);
	int (*remove_data)(struct _My_Hash_Map* self, int key);
	void (*for_each)(struct _My_Hash_Map* self, void func(void* data, void* para), void* para);
	int (*remove_if)(struct _My_Hash_Map* self, int func(void* data, void* para), void* para);
	void (*destroy)(struct _My_Hash_Map* self);
	void* (*find_if)(struct _My_Hash_Map* self, int func(void* data, void* para), void* para);
} HashMap;

HashMap new_hash_map();

void chg_hash_func(HashMap* map, int hash_func(HashMap* self, int key), unsigned bucketCap);

