#include "rbtree.h"
#include <stdlib.h>


RBNode* my_rb_search_data(RBTree* self, int func(RBNode* target, void* para), void* para);
void* my_rb_search_by_key(RBTree* self, int key);
void my_rb_destroy_rb_node(RBTree* self);
void my_rb_insert_to_rb_node(RBTree* self, int key, void* data);
void my_rb_remove_from_rb_node(RBTree* self, int key);


void left_rotate(RBNode* parent) {
	if (!parent->right) return;
	int key = parent->key;
	int data = parent->data;
	char color = parent->color;
	parent->key = parent->right->key;
	parent->data = parent->right->data;
	parent->color = parent->right->color;
	parent->right->key = key;
	parent->right->data = data;
	parent->right->color = color;
	RBNode* temp = parent->left;
	parent->left = parent->right;
	parent->right = parent->left->right;
	parent->left->right = parent->left->left;
	parent->left->left = temp;
	parent->left->right->parent = parent->left;
}

void right_rotate(RBNode* parent) {
	if (!parent->left) return;
	int key = parent->key;
	int data = parent->data;
	int color = parent->color;
	parent->key = parent->left->key;
	parent->data = parent->left->data;
	parent->color = parent->left->color;
	parent->left->key = key;
	parent->left->data = data;
	parent->left->color = color;
	RBNode* temp = parent->right;
	parent->right = parent->left;
	parent->left = parent->right->left;
	parent->right->left = parent->right->right;
	parent->right->right = temp;
	parent->right->left->parent = parent->right;
}

RBTree new_rb_tree() {
	RBTree res = {
		NULL,
		my_rb_search_data,
		my_rb_search_by_key,
		my_rb_destroy_rb_node,
		my_rb_insert_to_rb_node,
		my_rb_remove_from_rb_node,
	};
	return res;
}

void rb_insert_fixup(RBTree* root, RBNode* node) {
	while (node && node->parent && node->parent->color == 'r') {
		if (node->parent && node->parent == node->parent->parent->left) {
			RBNode* y = node->parent->parent->right;
			if (y->color == 'r') {
				node->parent->color = 'b';
				y->color = 'b';
				node->parent->parent->color = 'r';
				node = node->parent->parent;
			} else if (node == node->parent->right) {
				node = node->parent;
				left_rotate(node);
			}

		}
	}
}

