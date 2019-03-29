#include "graphics.h"
#include "imgui.h"
#include <stdlib.h>

const int timerDelay = 32;
const int globalTimerId = 1;

typedef enum {
	PILLAR_A, PILLAR_B, PILLAR_C
} Pillar;

typedef struct {
	Pillar position;
} HanoiHandler;

typedef struct _My_List_Node_T {
	HanoiHandler data;
	struct _My_List_Node_T* next;
} Node;

Node * new_node(HanoiHandler initData);
Node * push_node(Node * tail, HanoiHandler data);
Node * insert_node_after(Node * node, HanoiHandler data);
void remove_node_after(Node* node);
void destroy_linked_list(Node* head);

Pillar get_move_target(Pillar lhs, Pillar rhs);

void move_element(Node* target, Pillar position) {

}

void hanoi_handler(Node* head, Pillar position) {
	if (!head->next) {
		move_element(head, position);
		return;
	}
	hanoi_handler(head->next, get_move_target(head->next->data.position, position));
	move_element(head, position);
	hanoi_handler(head->next, position);
}

void hanoi() {

}

Node* new_node(HanoiHandler initData) {
	Node* head = (Node*)malloc(sizeof(Node));
	head->data = initData;
	head->next = NULL;
	return head;
}

Node* push_node(Node* tail, HanoiHandler data) {
	if (!tail) {
		return new_node(data);
	}
	Node* res = new_node(data);
	tail->next = res;
	return res;
}

Node* insert_node_after(Node* node, HanoiHandler data) {
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
		return;
	}
	Node* to_delete = node->next;
	node->next = node->next->next;
	free(to_delete);
}

void destroy_linked_list(Node* head) {
	while (head) {
		Node* to_destroy = head;
		head = head->next;
		free(to_destroy);
	}
}

Pillar get_move_target(Pillar lhs, Pillar rhs)
{
	if (lhs != PILLAR_A && rhs != PILLAR_A) return PILLAR_A;
	if (lhs != PILLAR_B && rhs != PILLAR_B) return PILLAR_B;
	if (lhs != PILLAR_C && rhs != PILLAR_C) return PILLAR_C;
	return PILLAR_A;
}