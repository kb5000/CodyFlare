#include "vector.h"
#include "vector_test.h"
#include <stdio.h>
#include "graphics.h"
#include "gc.h"
#include <stdlib.h>

void test_of_vector() {
	InitConsole();
	Vector v = new_zero_vector(sizeof(int), 1);
	int num = *(int*)v.at(&v, 0);
	for (int i = 0; i < 100; i++) {
		v.push(&v, &i);
	}
	num++;
	v.insert(&v, 3, (void*)&num);
	v.remove(&v, 5);
	v.pop(&v);
	for (unsigned i = 0; i < v.len(&v); i++) {
		printf("%d\n", *(int*)v.at(&v, i));
	}
	v.destroy(&v);
	///there is a vector with gc example
	init_gc();
	Vector vb = gen_empty_vector(int);
	for (int i = 0; i < 1000; i++) {
		gen_gc_data(int, p, 5 * i);
		add_to_gc_data(p, sizeof(int));
		vb.push(&vb, p);
		can_destroy_data(p);
	}
	perform_gc();
	for (unsigned i = 0; i < vb.len(&vb); i++) {
		printf("%d\n", cast(int, vb.at(&vb, i)));
	}
	
}