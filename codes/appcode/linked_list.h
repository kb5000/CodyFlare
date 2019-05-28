#pragma once

typedef struct _My_Node {
	void* data;
	struct _My_Node* next;
} Node;

typedef struct _My_Linked_List_Handler {
	/*public const*/Node* head;
	/*public const*/Node* tail;
	/*public*/Node* nowpos; //i.e. position now, can be modified as you wish
	/// name: len
	/// func: return the length of the list
	/// para: self expects the ListHandler itself
	/// visb: public
	/// warn: O(n)
	unsigned(*len)(struct _My_Linked_List_Handler* self);
	/// name: at
	/// func: return the node at the given position
	/// para: self expects the ListHandler itself, position expects a valid position
	/// visb: public
	/// warn: if position is greater than the length, it will return the last node
	Node* (*at)(struct _My_Linked_List_Handler* self, unsigned position);
	/// name: push_back
	/// func: push data to the end of the list
	/// para: self expects the ListHandler itself, data expects a data malloced independently
	/// visb: public
	void(*push_back)(struct _My_Linked_List_Handler* self, void* data);
	/// name: push_front
	/// func: push data to the begin of the list
	/// para: self expects the ListHandler itself, data expects a data malloced independently
	/// visb: public
	void(*push_front)(struct _My_Linked_List_Handler* self, void* data);
	/// name: pop_front
	/// func: pop data from the begin of the list
	/// para: self expects the ListHandler itself
	/// visb: public
	void(*pop_front)(struct _My_Linked_List_Handler* self);
	/// name: pop_back
	/// func: pop data from the end of the list
	/// para: self expects the ListHandler itself
	/// visb: public
	/// warn: O(n)
	void(*pop_back)(struct _My_Linked_List_Handler* self);
	/// name: insert_after
	/// func: insert data to the next of member nowpos
	/// para: self expects the ListHandler itself, data expects a data malloced independently
	/// visb: public
	/// warn: nowpos must be a valid node of this list, or NULL create a new node and throw the previous list
	void(*insert_after)(struct _My_Linked_List_Handler* self, void* data);
	/// name: remove_after
	/// func: remove data after the nowpos
	/// para: self expects the ListHandler itself
	/// visb: public
	/// warn: if nowpos is the last node, it will be O(n)
	void(*remove_after)(struct _My_Linked_List_Handler* self);
	/// name: destroy
	/// func: destroy the whole list
	/// para: self expects the ListHandler itself
	/// visb: public
	/// warn: it will also free the data inside
	void(*destroy)(struct _My_Linked_List_Handler* self);
	/// name: for_each
	/// func: apply func for every data in the list
	/// para: self expects the ListHandler itself
	/// visb: public
	/// warn: you can change the data
	void(*for_each)(struct _My_Linked_List_Handler* self, void func(void*));
	/// name: sort_by
	/// func: sort the list by func
	/// para: self expects the ListHandler itself, func expects to return negtive num when left para is smaller than right para, 
	///       0 if they are equal, positive num if left para is bigger than right para
	/// visb: public
	void(*sort_by)(struct _My_Linked_List_Handler* self, int func(void*, void*));
	/// name: find_if
	/// func: return the data of the first node matches, NULL if no match
	/// para: self expects the ListHandler itself, func expects to return 1 if match successful, 0 if match failed
	/// visb: public
	void* (*find_if)(struct _My_Linked_List_Handler* self, int func(const struct _My_Linked_List_Handler*, void*, void*), void* para);
	/// name: remove_if
	/// func: remove the node if func return 1
	/// para: self expects the ListHandler itself, func expects to return 1 if match successful, 0 if match failed, para expects para to pass
	/// visb: public
	void(*remove_if)(struct _My_Linked_List_Handler* self, int func(void* data, void* para), void* para);
} ListHandler;

/// name: new_node
/// func: create a single node which contains the init data
/// para: initData expects a data malloced independently
/// visb: public
/// warn: never use stack varible or malloced like array
Node* new_node(void* initData);

/// name: push_node
/// func: push a node after the tail and return the new node
/// para: tail expects the last node, data expects a data malloced independently
/// visb: public
/// warn: tail must be the last node, or it will cause memory leak
Node* push_node(Node* tail, void* data);

/// name: insert_node_after
/// func: insert a node after the given node and return the new node
/// para: node expects any node, data expects a data malloced independently
/// visb: public
/// warn: if node is NULL, it will return a new list
Node* insert_node_after(Node* node, void* data);

/// name: remove_node_after
/// func: remove a node after the given node
/// para: node expects any node
/// visb: public
/// warn: if node is NULL or its next is NULL, it will return directly
void remove_node_after(Node* node);

/// name: destroy_linked_list
/// func: it will destroy a whole list
/// para: head expects the head node of a list
/// visb: public
/// warn: it will also destroy the data
void destroy_linked_list(Node* head);

/// name: sort_list
/// func: it will sort a list by func
/// para: head expects a node, func expects to return negtive num when left para is smaller than right para, 
///       0 if they are equal, positive num if left para is bigger than right para
/// visb: public
/// warn: it uses merge sort
Node* sort_list(Node* head, int func(void*, void*));

/// name: new_list
/// func: it will create a new ListHandler, which contains a lot of useful info about the list
/// para: initData expects a data malloced independently
/// visb: public
/// warn: recommand use this instead of node
ListHandler new_list(void* initData);

/// name: new_empty_list
/// func: it will create a new empty ListHandler, which contains a lot of useful info about the list
/// visb: public
/// warn: recommand use this instead of node
ListHandler new_empty_list();

