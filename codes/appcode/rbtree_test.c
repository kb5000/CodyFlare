#include "rbtree_test.h"
#include "rbtree.h"
#include "graphics.h"
#include <stdio.h>

void test_of_rb_tree() {
	InitConsole();
	RBTree rbt = new_rb_tree();
	rbt.insert_to_rb_tree(&rbt, 1, 1);
	rbt.insert_to_rb_tree(&rbt, 2, 2);
	rbt.insert_to_rb_tree(&rbt, 3, 3);
	rbt.insert_to_rb_tree(&rbt, 4, 3);
	rbt.insert_to_rb_tree(&rbt, 7, 3);
	rbt.insert_to_rb_tree(&rbt, 9, 3);
	rbt.insert_to_rb_tree(&rbt, 6, 3);
	rbt.insert_to_rb_tree(&rbt, 12, 3);
	rbt.insert_to_rb_tree(&rbt, 15, 3);
	rbt.insert_to_rb_tree(&rbt, 12, 3);
	RBNode* root = rbt.root;
	printf("%d", root->key);
}