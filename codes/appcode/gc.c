#include "gc.h"
//#include "linked_list.h"
#include "hashmap.h"
#include <stdlib.h>
#include "utility.h"


typedef struct {
	void* data;
	unsigned size;
} GCDataPack;

//ListHandler globalVaribleList;
HashMap globalVaribleSet;

void init_gc() {
	globalVaribleSet = new_hash_map();
}

void* add_to_gc_data(void* data, unsigned size) {
	GCDataPack* gcdp = (GCDataPack*)malloc(sizeof(GCDataPack));
	gcdp->data = data;
	gcdp->size = size;
	//globalVaribleList.push_back(&globalVaribleList, (void*)gcdp);
	globalVaribleSet.insert_data(&globalVaribleSet, (int)data, gcdp);
	return gcdp->data;
}

int gc_equal_func(void* data, void* para) {
	return ((GCDataPack*)data)->data == para;
}

void can_destroy_data(void* data) {
	//GCDataPack* node = globalVaribleList.find_if(&globalVaribleList, gc_equal_func, data);
	GCDataPack* node = (GCDataPack*)globalVaribleSet.get_data(&globalVaribleSet, (int)data);
	if (node) node->size = 0;
}

int is_safe_to_use(void* data) {
	//GCDataPack* node = globalVaribleList.find_if(&globalVaribleList, gc_equal_func, data);
	GCDataPack* node = (GCDataPack*)globalVaribleSet.get_data(&globalVaribleSet, (int)data);
	return node && (node->size != 0);
}

int perform_gc_handler(void* data, void* unuseful) {
	GCDataPack* gcdp = (GCDataPack*)data;
	if (gcdp->size == 0) {
		free(gcdp->data);
		gcdp->data = NULL;
	}
	return gcdp->size == 0;
}

void perform_gc(void* unuseful) {
	globalVaribleSet.remove_if(&globalVaribleSet, perform_gc_handler, NULL);
}

int gc_all_clear_handler(void* data, void* unuseful) {
	GCDataPack* gcdp = (GCDataPack*)data;
	free(gcdp->data);
	gcdp->data = NULL;
	return 1;
}

void gc_all_clear() {
	globalVaribleSet.remove_if(&globalVaribleSet, gc_all_clear_handler, NULL);
}
