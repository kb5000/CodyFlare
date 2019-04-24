#include "rbtree.h"
#include <stdlib.h>


RBNode* my_rb_search_data(RBTree* self, int func(RBNode* target, void* para), void* para);
void* my_rb_search_by_key(RBTree* self, int key);
void my_rb_destroy_rb_tree(RBTree* self);
void my_rb_insert_to_rb_tree(RBTree* self, int key, void* data);
void my_rb_remove_from_rb_tree(RBTree* self, int key);

void preserve_root(RBTree* tree) {
	while (tree->root->parent) {
		tree->root = tree->root->parent;
	}
	tree->root->color = 'b';
}

void left_rotate(RBTree* self, RBNode* x) {
	RBNode* y = x->left;
	if (!y) return;
	if (y->left) y->left->parent = x;
	y->parent = x->parent;
	if (!x->parent) self->root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void right_rotate(RBTree* self, RBNode* x) {
	RBNode* y = x->right;
	if (!y) return;
	if (y->right) y->left->parent = x;
	y->parent = x->parent;
	if (!x->parent) self->root = y;
	else if (x == x->parent->right) x->parent->left = y;
	else x->parent->left = y;
	y->right = x;
	x->parent = y;
}

RBNode* new_rb_node(int key, void* data) {
	RBNode* res = (RBNode*)malloc(sizeof(RBNode));
	res->key = key;
	res->data = data;
	res->color = 'r';
	res->parent = res->left = res->right = NULL;
	return res;
}

void push_rb_node_leaf(RBNode* parent, char position, RBNode* child) {
	if (!parent) {
		parent = child;
		child->color = 'b';
		return;
	}
	if (position == 'l') {
		parent->left = child;
		child->parent = parent;
	} else {
		parent->right = child;
		child->parent = parent;
	}
}

void remove_rb_node_leaf(RBNode* node) {
	if (node->parent && node->parent->left == node) node->parent->left = NULL;
	else if (node->parent && node->parent->right == node) node->parent->right = NULL;
	free(node->data);
	free(node);
}

RBNode* rb_successor(RBNode* node) {
	if (node->right) {
		RBNode* res = node->right;
		while (res->left) {
			res = res->left;
		}
		return res;
	}
	RBNode* parent = node->parent;
	while (parent && node == parent->right) {
		node = parent;
		parent = node->parent;
	}
	return parent;
}

RBTree new_rb_tree() {
	RBTree res = {
		NULL,
		my_rb_search_data,
		my_rb_search_by_key,
		my_rb_destroy_rb_tree,
		my_rb_insert_to_rb_tree,
		my_rb_remove_from_rb_tree,
	};
	return res;
}

RBNode* my_rb_search_data(RBTree* self, int func(RBNode* target, void* para), void* para) {
	return NULL;
}

void* my_rb_search_by_key(RBTree* self, int key) {
	RBNode* node = self->root;
	while (node) {
		if (node->key == key) return node->data;
		if (node->key < key) node = node->right;
		else node = node->left;
	}
	return NULL;
}

void my_rb_destroy_rb_tree(RBTree* self) {
}

void rb_insert_fixup(RBTree* root, RBNode* node) {
	while (node && node->parent && node->parent->color == 'r') {
		if (!node->parent->parent || node->parent == node->parent->parent->left) {
			RBNode* uncle = (node->parent->parent ? node->parent->parent->right : NULL);
			if (uncle && uncle->color == 'r') {
				node->parent->color = 'b';
				uncle->color = 'b';
				node->parent->parent->color = 'r';
				node = node->parent->parent;
				continue;
			} else if (node == node->parent->right) {
				node = node->parent;
				left_rotate(root, node);
			}
			if (node->parent) {
				node->parent->color = 'b';
				node->parent->parent && (node->parent->parent->color = 'r');
				right_rotate(root, node->parent->parent);
			}
		} else if (node->parent == node->parent->parent->right) {
			RBNode* uncle = node->parent->parent->left;
			if (uncle && uncle->color == 'r') {
				node->parent->color = 'b';
				uncle->color = 'b';
				node->parent->parent->color = 'r';
				node = node->parent->parent;
				continue;
			} else if (node == node->parent->left) {
				node = node->parent;
				right_rotate(root, node);
			}
			if (node->parent) {
				node->parent->color = 'b';
				node->parent->parent->color = 'r';
				left_rotate(root, node->parent->parent);
			}
		}
	}
}

void my_rb_insert_to_rb_tree(RBTree* self, int key, void* data) {
	RBNode* z = new_rb_node(key, data);
	RBNode* y = NULL, *x = self->root;
	while (x) {
		y = x;
		if (key < x->key) x = x->left;
		else x = x->right;
	}
	z->parent = y;
	if (!y) self->root = z;
	else if (key < y->key) y->left = z;
	else y->right = z;
	z->left = NULL;
	z->right = NULL;
	z->color = 'r';
	rb_insert_fixup(self, z);
}

void rb_trans_plant(RBTree* self, RBNode* u, RBNode* v) {
	if (!u->parent) self->root = v;
	else if (u == u->parent->left) u->parent->left = v;
	else u->parent->right = v;
	v->parent = u->parent;
}

RBNode* rb_tree_minimum(RBNode* node) {
	while (node && node->left) {
		node = node->left;
	}
	return node;
}


void rb_remove_fixup(RBTree* root, RBNode* node, RBNode* par) {
	int flag = 0;
	RBNode* preNode = node;
	if (!node) {
		flag = 1;
		node = new_rb_node(0, NULL);
		node->parent = par;
		node->color = 'b';
		par->left = node;
	}
	while (node->parent && node->color == 'b') {
		if (node == node->parent->left) {
			RBNode* uncle = node->parent->right;
			if (uncle && uncle->color == 'r') {
				uncle->color = 'b';
				node->parent->color = 'r';
				left_rotate(root, node->parent);
				uncle = node->parent->right;
			}
			if ((!uncle->left || uncle->left->color == 'b') && (!uncle->right || uncle->right->color == 'b')) {
				uncle->color = 'r';
				node = node->parent;
			} else {
				if (!uncle->right || uncle->right->color == 'b') {
					uncle->left && (uncle->left->color = 'b');
					uncle->color = 'r';
					right_rotate(root, uncle);
					uncle = node->parent->right;
				}
				uncle && (uncle->color = node->parent->color);
				node->parent->color = 'b';
				uncle->right && (uncle->right->color = 'b');
				left_rotate(root, node->parent);
				preserve_root(root);
				node = root->root;
			}
		} else {
			RBNode* uncle = node->parent->left;
			if (uncle && uncle->color == 'r') {
				uncle->color = 'b';
				node->parent->color = 'r';
				right_rotate(root, node->parent);
				uncle = node->parent->left;
			}
			if ((!uncle->right || uncle->right->color == 'b') && (!uncle->left || uncle->left->color == 'b')) {
				uncle->color = 'r';
				node = node->parent;
			} else {
				if (!uncle->left || uncle->left->color == 'b') {
					uncle->right && (uncle->right->color = 'b');
					uncle->color = 'r';
					left_rotate(root, uncle);
					uncle = node->parent->left;
				}
				uncle && (uncle->color = node->parent->color);
				node->parent->color = 'b';
				uncle->left && (uncle->left->color = 'b');
				right_rotate(root, node->parent);
				preserve_root(root);
				node = root->root;
			}
		}
	}
	node->color = 'b';
	if (flag) {
		if (preNode->parent = preNode->parent->left) preNode->parent->left = NULL;
		else preNode->parent->right = NULL;
		free(preNode);
	}
}


void my_rb_remove_from_rb_tree(RBTree* self, int key) {
	RBNode* z = self->search_by_key(self, key);
	if (!z) return;
	RBNode* y = z;
	RBNode* x, *xP;
	char origColor = y->color;
	if (!z->left) {
		x = z->right;
		xP = z;
		rb_trans_plant(self, z, z->left);
	} else if (!z->right) {
		x = z->left;
		xP = z;
		rb_trans_plant(self, z, z->right);
	} else {
		y = rb_tree_minimum(z->right);
		origColor = y->color;
		x = y->right;
		xP = y;
		if (y->parent == z) x && (x->parent = y);
		else {
			rb_trans_plant(self, y, y->right);
			y->right = z->right;
			y->right && (y->right->parent = y);
		}
		rb_trans_plant(self, z, y);
		y->left = z->left;
		y->left && (y->left->parent = y);
		y->color = z->color;
	}
	if (origColor == 'b') rb_remove_fixup(self, x, xP);
	remove_rb_node_leaf(z);
}

