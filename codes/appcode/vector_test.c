#include "vector.h"
#include "vector_test.h"

void test_of_vector() {
	Vector v = new_zero_vector(sizeof(int), 1);
	int num = *(int*)v.at(&v, 0);
	for (int i = 0; i < 5; i++) {
		v.push(&v, &i);
	}
	num++;
	v.insert(&v, 3, (void*)&num);
	v.remove(&v, 5);
	v.pop(&v);
	
	for (int i = 0; i < v.len(&v); i++) {
		printf("%d\n", *(int*)v.at(&v, i));
	}
	v.destroy(&v);
}