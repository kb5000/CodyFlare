#pragma once

typedef struct _My_Node {
	void* data;
	struct _My_Node* next;
} Node;

typedef struct _My_Linked_List_Handler {
	/*public const*/Node* head;
	/*public const*/Node* tail;
	/*public*/Node* nowpos; //i.e. position now, can be modified as you wish
	/*public*/unsigned (*len)(struct _My_Linked_List_Handler* self);
	/*public*/Node* (*at)(struct _My_Linked_List_Handler* self, unsigned position);
	/*public*/void (*push_back)(struct _My_Linked_List_Handler* self, void* data);
	/*public*/void (*push_front)(struct _My_Linked_List_Handler* self, void* data);
	/*public*/void (*pop_front)(struct _My_Linked_List_Handler* self);
	/*public*/void (*pop_back)(struct _My_Linked_List_Handler* self);
	/*public*/void (*insert_after)(struct _My_Linked_List_Handler* self, void* data);
	/*public*/void (*remove_after)(struct _My_Linked_List_Handler* self);
	/*public*/void (*destroy)(struct _My_Linked_List_Handler* self);
	/*public*/void (*for_each)(struct _My_Linked_List_Handler* self, void func(void*));
} ListHandler;

Node* new_node(void* initData);

Node* push_node(Node* tail, void* data);

Node* insert_node_after(Node* node, void* data);

void remove_node_after(Node* node);

void destroy_linked_list(Node* head);

ListHandler new_list(void* initData);

