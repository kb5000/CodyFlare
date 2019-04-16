#pragma once

#include <stdint.h>

typedef struct _My_Vector {
	//it contains the content of the vector
	/*private*/void* content;
	//it means the size of a single element, it shouldn't be changed by the user
	const unsigned sizeOfElement;
	//don't change it mannually, use len function to get the length
	/*protected*/unsigned numOfElement;
	/*private*/unsigned poolLength;
	///name: push
	///func: push an element into the end of the vector
	///para: self expects the struct itself, content expects a pointer refering to the data which have a match type
	///visb: public
	///warn: it may cause memory realloc, which can change the content pointer
	void (*push)(struct _My_Vector* self, void* content);
	///name: pop
	///func: pop an element from the vector and return the point of the element
	///para: self expects the struct itself
	///visb: public
	///warn: it will return NULL for an empty vector, and the content returned may be invalid if you called shrink_to function
	void* (*pop)(struct _My_Vector* self);
	///name: at
	///func: return the head pointer of the data in the certain position
	///para: self expects the struct itself, number expects a valid subscript
	///visb: public
	///warn: it will return NULL if the number is out of bounds
	void* (*at)(struct _My_Vector* self, unsigned number);
	///name: insert
	///func: insert an element to the certain position
	///para: self expects the struct itself, number expects a valid subscript, content expects a pointer refering to the data
	///visb: public
	///warn: it will work even the vector is empty, and it will call push if the subscript is bigger or equal to the length
	void (*insert)(struct _My_Vector* self, unsigned number, void* content);
	///name: remove
	///func: remove an element from the certain position
	///para: self expects the struct itself, number expects a valid subscript
	///visb: public
	///warn: it wont change the memory size
	void (*remove)(struct _My_Vector* self, unsigned number);
	///name: len
	///func: return the number of elements
	///para: self expects the struct itself
	///visb: public
	///warn: always use this to aquire the length
	unsigned (*len)(struct _My_Vector* self);
	///name: shrink_to
	///func: change the memory size of the vector
	///para: self expects the struct itself, length expects the number of the elements it can hold
	///visb: public
	///warn: it wont work if length is smaller than the number of the elements, 
	///      and it may cause the element returned from pop function invalid
	void (*shrink_to)(struct _My_Vector* self, unsigned length);
	///name: destroy
	///func: destroy the vector
	///para: self expects the struct itself
	///visb: public
	///warn: always remember to destroy it and the vector will be invalid and not able to reuse
	void (*destroy)(struct _My_Vector* self);
	///name: clone
	///func: return a vector that have the same content by itself
	///para: self expects the struct itself
	///visb: public
	///warn: use this to deep copy, and the common assignment is move or shallow copy
	struct _My_Vector (*clone)(struct _My_Vector* self);
} Vector;

///name: new_vector
///func: construct a new vector
///para: sizeOfElement expects the size of one element, numOfElement expects the initial size of the vector, 
///      content expects the initial value of each element
///visb: public
///warn: content expects a pointer so it must be a left-value
Vector new_vector(unsigned sizeOfElement, unsigned numOfElement, void* content);

///name: new_zero_vector
///func: construct a new vector which have initial value 0
///para: sizeOfElement expects the size of one element, numOfElement expects the initial size of the vector
///visb: public
Vector new_zero_vector(unsigned sizeOfElement, unsigned numOfElement);

///name: gen_empty_vector
///func: construct a new empty vector with the type
///para: type expects a typename
///visb: public
///exam: Vector v = gen_empty_vector(int);
#define gen_empty_vector(type) new_zero_vector(sizeof(type), 0)

///name: cast
///func: cast var from void* to type
///para: type expects a typename, var expects void* data
///visb: public
#define cast(type, var) (*(type*)(var))