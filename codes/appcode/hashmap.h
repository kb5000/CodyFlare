#pragma once
#include "vector.h"

typedef struct _My_Hash_Map {
	/*private*/Vector mapData;
	///name: hash_func
	///func: return the hash code of key
	///para: self expects the HashMap itself, key expects the key of data
	///visb: private
	int (*hash_func)(struct _My_Hash_Map* self, int key);
	///name: insert_data
	///func: insert data to hash map
	///para: self expects the HashMap itself, key expects the key, data expects memory malloced
	///visb: public
	void (*insert_data)(struct _My_Hash_Map* self, int key, void* data);
	///name: insert_key
	///func: just insert key to hash map
	///para: self expects the HashMap itself, key expects the unique key
	///visb: public
	void (*insert_key)(struct _My_Hash_Map* self, int key);
	///name: exist_data
	///func: return 1 if have key, 0 if dont
	///para: self expects the HashMap itself, key expects the unique key
	///visb: public
	int (*exist_data)(struct _My_Hash_Map* self, int key);
	///name: get_data
	///func: return data to the key or NULL if not found
	///para: self expects the HashMap itself, key expects any number
	///visb: public
	void* (*get_data)(struct _My_Hash_Map* self, int key);
	///name: remove_data
	///func: remove data to the key, return 1 if removed data, 0 if not
	///para: self expects the HashMap itself, key expects the key to data
	///visb: public
	int (*remove_data)(struct _My_Hash_Map* self, int key);
	///name: for_each
	///func: apply func to every data
	///para: self expects the HashMap itself, func expects a function which data expects map data, 
	///      para expects the para passed to, para expects a pointer
	///visb: public
	void (*for_each)(struct _My_Hash_Map* self, void func(void* data, void* para), void* para);
	///name: remove_if
	///func: remove all data func returns 1
	///para: self expects the HashMap itself, func expects a function which data expects map data, 
	///      para expects the para passed to, para expects a pointer, func return 1 means to remove,
	///      0 dont remove
	///visb: public
	int (*remove_if)(struct _My_Hash_Map* self, int func(void* data, void* para), void* para);
	///name: destroy
	///func: destroy the hashmap
	///para: self expects the HashMap itself
	///visb: public
	void (*destroy)(struct _My_Hash_Map* self);
	///name: find_if
	///func: find data if match
	///para: self expects the HashMap itself, func expects a function which data expects map data, 
	///      para expects the para passed to, para expects a pointer, func return 1 means to return,
	///visb: public
	void* (*find_if)(struct _My_Hash_Map* self, int func(void* data, void* para), void* para);
} HashMap;

///name: new_hash_map
///func: return a new hash map
///visb: public
HashMap new_hash_map();

///name: chg_hash_func
///func: change the default hash func
///para: map expects a hashmap, hash_func expects the new hash_func, bucketCap expects the new capacity of the
///      hash map vector
///visb: public
///warn: only to call it when the map is empty
void chg_hash_func(HashMap* map, int hash_func(HashMap* self, int key), unsigned bucketCap);

