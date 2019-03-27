#include "linked_list.h"
#include <stdlib.h>

unsigned my_list_len(ListHandler* self);
Node* my_list_at(ListHandler* self, unsigned position);
void my_list_push_back(ListHandler* self, void* data);
void my_list_push_front(ListHandler* self, void* data);
void my_list_pop_front(ListHandler* self, void* data);
void my_list_pop_back(ListHandler* self, void* data);
void my_list_insert_after(ListHandler* self, void * data);
void my_list_remove_after(ListHandler* self);
void my_list_destroy(ListHandler* self);
void my_list_for_each(ListHandler* self, void func(void*));

Node* new_node(void* initData) {
	Node* head = (Node*)malloc(sizeof(Node));
	head->data = initData;
	head->next = NULL;
	return head;
}

Node* push_node(Node* tail, void* data) {
	if (!tail) {
		return new_node(data);
	}
	Node* res = new_node(data);
	tail->next = res;
	return res;
}

Node* insert_node_after(Node* node, void* data) {
	if (!node) {
		return new_node(data);
	}
	Node* res = new_node(data);
	res->next = node->next;
	node->next = res;
	return res;
}

void remove_node_after(Node* node) {
	if (!node || !node->next) {
		return NULL;
	}
	Node* to_delete = node->next;
	node->next = node->next->next;
	free(to_delete->data);
	free(to_delete);
}

void destroy_linked_list(Node* head) {
	while (head) {
		Node* to_destroy = head;
		head = head->next;
		free(to_destroy->data);
		free(to_destroy);
	}
}

ListHandler new_list(void* initData) {
	Node* head = new_node(initData);
	ListHandler listHandler = {
		head,
		head,
		head,
		my_list_len,
		my_list_at,
		my_list_push_back,
		my_list_push_front,
		my_list_pop_front,
		my_list_pop_back,
		my_list_insert_after,
		my_list_remove_after,
		my_list_destroy,
		my_list_for_each,
	};
	return listHandler;
}

unsigned my_list_len(ListHandler* self) {
	Node* head = self->head;
	unsigned length = 0;
	for (; head; length++, head = head->next);
	return length;
}

Node* my_list_at(ListHandler* self, unsigned position) {
	Node* res = self->head;
	for (unsigned i = 0; res && i < position; i++, res = res->next);
	return res;
}

void my_list_push_back(ListHandler* self, void* data) {
	self->tail = push_node(self->tail, data);
}

void my_list_push_front(ListHandler* self, void* data) {
	Node* to_push = new_node(data);
	to_push->next = self->head;
	self->head = to_push;
	if (!self->tail) {
		self->tail = to_push;
	}
}

void my_list_pop_front(ListHandler* self, void* data) {
	if (!self->head) return;
	Node* to_pop = self->head;
	if (self->tail == self->head) {
		self->tail = self->tail->next;
	}
	self->head = self->head->next;
	free(to_pop->data);
	free(to_pop);
}

void my_list_pop_back(ListHandler* self, void* data) {
	if (!self->tail) return;
	if (self->head == self->tail) {
		self->head = NULL;
	}
	free(self->tail->data);
	free(self->tail);
	Node* new_tail = self->head;
	for (; new_tail; new_tail = new_tail->next);
	self->tail = new_tail;
}

void my_list_insert_after(ListHandler* self, void* data) {
	if (!self->nowpos) {
		Node* node = insert_node_after(NULL, data);
		self->head = self->tail = self->nowpos = node;
		return;
	}
	insert_node_after(self->nowpos, data);
	if (self->tail == self->nowpos) {
		self->tail = self->tail->next;
	}
}

void my_list_remove_after(ListHandler* self) {
	remove_node_after(self->nowpos);
	if (self->tail == self->nowpos) {
		Node* new_tail = self->head;
		for (; new_tail; new_tail = new_tail->next);
		self->tail = new_tail;
	}
}

void my_list_destroy(ListHandler* self) {
	destroy_linked_list(self->head);
}

void my_list_for_each(ListHandler* self, void func(void*)) {
	Node* node = self->head;
	while (node) {
		func(node->data);
		node = node->next;
	}
}
