#include "hashmap.h"
#include <stdint.h>
#include "linked_list.h"
#include <stdlib.h>
#include "utility.h"

typedef struct _My_Hash_Node {
	int key;
	void* data;
	struct _My_Hash_Node* next;
}HNode;


int my_map_hash_func(HashMap* self, int key);
void my_map_insert_data(HashMap* self, int key, void* data);
void my_map_insert_key(HashMap* self, int key);
int my_map_exist_data(HashMap* self, int key);
void* my_map_get_data(HashMap* self, int key);
int my_map_remove_data(HashMap* self, int key);
void my_map_for_each(HashMap* self, void func(void* data, void* para), void* para);
int my_map_remove_if(HashMap* self, int func(void* data, void* para), void* para);
void my_map_destroy(HashMap* self);
void* my_map_find_if(HashMap* self, int func(void* data, void* para), void* para);

HNode* new_hash_node(int key, void* data) {
	HNode* res = (HNode*)malloc(sizeof(HNode));
	res->data = data;
	res->key = key;
	res->next = NULL;
	return res;
}

void destroy_hash_nodes(HNode* head) {
	while (head) {
		HNode* next = head->next;
		if (head->data) free(head->data);
		free(head);
		head = next;
	}
}


HashMap new_hash_map() {
	HNode* h = NULL;
	HashMap res = {
		new_vector(sizeof(HNode*), 65536, &h),
		my_map_hash_func,
		my_map_insert_data,
		my_map_insert_key,
		my_map_exist_data,
		my_map_get_data,
		my_map_remove_data,
		my_map_for_each,
		my_map_remove_if,
		my_map_destroy,
		my_map_find_if,
	};
	return res;
}

void chg_hash_func(HashMap* map, int hash_func(HashMap* self, int key), unsigned bucketCap) {
	map->hash_func = hash_func;
	map->mapData.shrink_to(&map->mapData, bucketCap);
}

int my_map_hash_func(HashMap* self, int key) {
	int code = (key ^ (key >> 16)) & 0xFFFF;
	return code;
}

void my_map_insert_data(HashMap* self, int key, void* data) {
	unsigned code = (unsigned)self->hash_func(self, key);
	HNode* head = cast(HNode*,self->mapData.at(&self->mapData, code));
	while (head && head->next) {
		if (head->key == key) return;
		head = head->next;
	}
	if (!head) {
		HNode** p = (HNode**)self->mapData.at(&self->mapData, code);
		*p = new_hash_node(key, data);
		return;
	}
	if (head->key == key) return;
	HNode* next = head->next;
	head->next = new_hash_node(key, data);
	head->next->next = next;
}

void my_map_insert_key(HashMap* self, int key) {
	self->insert_data(self, key, NULL);
}

int my_map_exist_data(HashMap* self, int key) {
	unsigned code = (unsigned)self->hash_func(self, key);
	HNode* head = cast(HNode*,self->mapData.at(&self->mapData, code));
	while (head && head->next) {
		if (head->key == key) return 1;
		head = head->next;
	}
	if (!head) return 0;
	if (head->key == key) return 1;
	return 0;
}

void* my_map_get_data(HashMap* self, int key) {
	unsigned code = (unsigned)self->hash_func(self, key);
	HNode* head = cast(HNode*,self->mapData.at(&self->mapData, code));
	while (head && head->next) {
		if (head->key == key) return head->data;
		head = head->next;
	}
	if (!head) return NULL;
	if (head->key == key) return head->data;
	return NULL;
}

int my_map_remove_data(HashMap* self, int key) {
	unsigned code = (unsigned)self->hash_func(self, key);
	HNode* head = cast(HNode*,self->mapData.at(&self->mapData, code));
	if (!head) return 0;
	if (head->key == key) {
		cast(HNode*, self->mapData.at(&self->mapData, code)) = head->next;
		if (head->data) free(head->data);
		free(head);
		return 1;
	}
	while (head && head->next) {
		if (head->next->key == key) {
			HNode* next = head->next;
			head->next = head->next->next;
			if (next->data) free(next->data);
			free(next);
			return 1;
		}
		head = head->next;
	}
	return 0;
}

void my_map_for_each(HashMap* self, void func(void* data, void* para), void* para) {
	for (unsigned i = 0; i < self->mapData.numOfElement; i++) {
		HNode* node = cast(HNode*,self->mapData.at(&self->mapData, i));
		while (node) {
			func(node->data, para);
			node = node->next;
		}
	}
}

int my_map_remove_if(HashMap* self, int func(void* data, void* para), void* para) {
	for (unsigned i = 0; i < self->mapData.numOfElement; i++) {
		HNode* head = cast(HNode*, self->mapData.at(&self->mapData, i));
		while (head && func(head->data, para)) {
			HNode* p = head->next;
			cast(HNode*, self->mapData.at(&self->mapData, i)) = p;
			if (head->data) free(head->data);
			free(head);
			head = p;
		}
		while (head && head->next) {
			if (func(head->next->data, para)) {
				HNode* next = head->next;
				head->next = head->next->next;
				if (next->data) free(next->data);
				free(next);
			}
			head = head->next;
		}
	}
	return 0;
}

void my_map_destroy(HashMap* self) {
	for (unsigned i = 0; i < self->mapData.numOfElement; i++) {
		HNode* node = cast(HNode*,self->mapData.at(&self->mapData, i));
		destroy_hash_nodes(node);
	}
	self->mapData.destroy(&self->mapData);
}

void* my_map_find_if(HashMap* self, int func(void* data, void* para), void* para) {
	for (unsigned i = 0; i < self->mapData.numOfElement; i++) {
		HNode* node = cast(HNode*,self->mapData.at(&self->mapData, i));
		while (node) {
			if (func(node->data, para)) return node->data;
			node = node->next;
		}
	}
	return NULL;
}
