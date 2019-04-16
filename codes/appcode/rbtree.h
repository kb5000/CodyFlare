#pragma once

typedef struct _My_RB_Node {
	int key;
	void* data;
	struct _My_RB_Node* left, *right, *parent;
	char color;
} RBNode;

typedef struct _My_RB_Tree {
	RBNode* root;
	RBNode* (*search_data)(RBTree* self, int func(RBNode* target, void* para), void* para);
	void* (*search_by_key)(RBTree* self, int key);
	void (*destroy_rb_node)(RBTree* self);
	void (*insert_to_rb_node)(RBTree* self, int key, void* data);
	void (*remove_from_rb_node)(RBTree* self, int key);
} RBTree;

RBNode* new_rb_node(int key, void* data);
void push_rb_node(RBNode* parent, char position, RBNode* child);
void remove_rb_node(RBNode* parent, char position);

RBTree new_rb_tree();
