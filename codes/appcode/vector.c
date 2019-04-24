#include "vector.h"
#include <stdlib.h>

void my_vector_push(Vector* self, void* content);

void* my_vector_pop(Vector* self);

void* my_vector_at(Vector* self, unsigned number);

void my_vector_insert(Vector* self, unsigned number, void* content);

void my_vector_remove(Vector* self, unsigned number);

unsigned my_vector_len(Vector* self);

void my_vector_shrink_to(Vector* self, unsigned length);

void my_vector_destroy(Vector* self);

Vector my_vector_clone(Vector* self);

Vector new_vector(unsigned sizeOfElement, unsigned numOfElement, void* content) {
	Vector res = {
		NULL,
		sizeOfElement,
		numOfElement,
		sizeOfElement * numOfElement,
		my_vector_push,
		my_vector_pop,
		my_vector_at,
		my_vector_insert,
		my_vector_remove,
		my_vector_len,
		my_vector_shrink_to,
		my_vector_destroy,
		my_vector_clone,
	};
	if (sizeOfElement == 0 || numOfElement == 0) {
		return res;
	}
	int8_t* pool = (int8_t*)malloc(sizeOfElement * numOfElement);
	for (unsigned i = 0; i < numOfElement; i++) {
		for (unsigned j = 0; j < sizeOfElement; j++) {
			int8_t byteNum = *((int8_t*)content + j);
			*(pool + i * sizeOfElement + j) = byteNum;
		}
	}
	res.content = (void*)pool;
	return res;
}

Vector new_zero_vector(unsigned sizeOfElement, unsigned numOfElement) {
	int8_t* zeros = (int8_t*)calloc(1, sizeOfElement);
	Vector res = new_vector(sizeOfElement, numOfElement, zeros);
	free(zeros);
	return res;
}

void my_vector_push(Vector* self, void* content) {
	if (self->poolLength == 0) {
		self->content = malloc(self->sizeOfElement);
		self->poolLength = self->sizeOfElement;
	}
	if (self->poolLength - self->sizeOfElement * self->numOfElement < self->sizeOfElement) {
		self->poolLength *= 2;
		self->content = realloc(self->content, self->poolLength);
	}
	int8_t* pool = (int8_t*)self->content;
	for (unsigned i = 0; i < self->sizeOfElement; i++) {
		*(pool + self->numOfElement * self->sizeOfElement + i) = *((int8_t*)content + i);
	}
	self->numOfElement++;
}

void* my_vector_pop(Vector* self) {
	if (self->numOfElement == 0) return NULL;
	self->numOfElement--;
	int8_t* pool = (int8_t*)self->content + self->sizeOfElement * self->numOfElement;
	return (void*)pool;
}

void* my_vector_at(Vector* self, unsigned number) {
	if (number >= self->numOfElement) return NULL;
	int8_t* pool = (int8_t*)self->content + self->sizeOfElement * number;
	return (void*)pool;
}

void my_vector_insert(Vector* self, unsigned number, void* content) {
	if (self->poolLength == 0) {
		self->content = malloc(self->sizeOfElement);
		self->poolLength = 1;
	}
	if (number >= self->numOfElement) {
		self->push(self, content);
		return;
	}
	if (self->poolLength - self->sizeOfElement * self->numOfElement < self->sizeOfElement) {
		self->content = realloc(self->content, 2 * self->poolLength);
		self->poolLength *= 2;
	}
	int8_t* pool = (int8_t*)self->content;
	for (unsigned i = self->numOfElement; i != number; i--) {
		for (unsigned j = 0; j < self->sizeOfElement; j++) {
			*(pool + i * self->sizeOfElement + j) = *(pool + (i - 1) * self->sizeOfElement + j);
		}
	}
	for (unsigned i = 0; i < self->sizeOfElement; i++) {
		*(pool + number * self->sizeOfElement + i) = *((int8_t*)content + i);
	}
	self->numOfElement++;
}

void my_vector_remove(Vector* self, unsigned number) {
	if (number >= self->numOfElement || self->numOfElement == 0) return;
	int8_t* pool = (int8_t*)self->content;
	for (unsigned i = number; i < self->numOfElement - 1; i++) {
		for (unsigned j = 0; j < self->sizeOfElement; j++) {
			*(pool + i * self->sizeOfElement + j) = *(pool + (i + 1) * self->sizeOfElement + j);
		}
	}
	self->numOfElement--;
}

unsigned my_vector_len(Vector* self) {
	return self->numOfElement;
}

void my_vector_shrink_to(Vector* self, unsigned length) {
	if (length >= self->numOfElement) {
		self->content = realloc(self->content, length * self->sizeOfElement);
		self->poolLength = length * self->sizeOfElement;
	} else {
		self->destroy(self);
		*self = new_zero_vector(self->sizeOfElement, 0);
	}
}

void my_vector_destroy(Vector* self) {
	self->numOfElement = 0;
	free(self->content);
	self->content = NULL;
}

Vector my_vector_clone(Vector* self) {
	Vector res = new_zero_vector(self->sizeOfElement, self->numOfElement);
	int8_t* targetPool = (int8_t*)res.content;
	int8_t* sourcePool = (int8_t*)self->content;
	for (unsigned i = 0; i < self->sizeOfElement * self->numOfElement; i++) {
		*(targetPool + i) = *(sourcePool + i);
	}
	return res;
}

