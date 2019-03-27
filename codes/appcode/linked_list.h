#pragma once

typedef struct _My_Node {
	void* data;
	struct _My_Node* next;
} Node;

typedef struct _My_Linked_List_Handler {
	/*public const*/Node* head;
	/*public const*/Node* tail;
	/*public*/Node* nowpos; //i.e. position now, can be modified as you wish
	///name: len
	///func: return the length of the list
	///para: self expects the ListHandler itself
	///visb: public
	///warn: O(n)
	unsigned (*len)(struct _My_Linked_List_Handler* self);
	///name: at
	///func: return the node at the given position
	///para: self expects the ListHandler itself, position expects a valid position
	///visb: public
	///warn: if position is greater than the length, it will return the last node
	Node* (*at)(struct _My_Linked_List_Handler* self, unsigned position);
	///name: push
	///func: 
	///para: self expects the ListHandler itself
	///visb: 
	///warn: 
	void (*push)(struct _My_Linked_List_Handler* self, void* data);
	///name: 
	///func: 
	///para: self expects the ListHandler itself
	///visb: 
	///warn: 
	void (*insert_after)(struct _My_Linked_List_Handler* self, void* data);
	///name: 
	///func: 
	///para: self expects the ListHandler itself
	///visb: 
	///warn: 
	void (*remove_after)(struct _My_Linked_List_Handler* self);
	///name: 
	///func: 
	///para: self expects the ListHandler itself
	///visb: 
	///warn: 
	void (*destroy)(struct _My_Linked_List_Handler* self);
} ListHandler;

///name: new_node
///func: create a single node which contains the init data
///para: initData expects a data malloced independently
///visb: public
///warn: never use stack varible or malloced like array
Node* new_node(void* initData);

///name: push_node
///func: push a node after the tail and return the new node
///para: tail expects the last node, data expects a data malloced independently
///visb: public
///warn: tail must be the last node, or it will cause memory leak
Node* push_node(Node* tail, void* data);

///name: insert_node_after
///func: insert a node after the given node and return the new node
///para: node expects any node, data expects a data malloced independently
///visb: public
///warn: if node is NULL, it will return a new list
Node* insert_node_after(Node* node, void* data);

///name: remove_node_after
///func: remove a node after the given node
///para: node expects any node
///visb: public
///warn: if node is NULL or its next is NULL, it will return directly
void remove_node_after(Node* node);

///name: destroy_linked_list
///func: it will destroy a whole list
///para: head expects the head node of a list
///visb: public
///warn: it will also destroy the data
void destroy_linked_list(Node* head);

///name: new_list
///func: it will create a new ListHandler, which contains a lot of useful info about the list
///para: initData expects a data malloced independently
///visb: public
///warn: recommand use this instead of node
ListHandler new_list(void* initData);

