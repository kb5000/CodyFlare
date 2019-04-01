#pragma once

#include <stdbool.h>

#define PI 3.1415926535


typedef enum {
	PILLAR_A, PILLAR_B, PILLAR_C
} Pillar;

typedef struct {
	Pillar position;
	double x, y, size;
	Pillar towardsPosition;
} HanoiHandler;

typedef struct _My_List_Node_T {
	HanoiHandler data;
	struct _My_List_Node_T* next;
} Node;

Node* new_nodeh(HanoiHandler initData);
Node* push_nodeh(Node* tail, HanoiHandler data);
Node* push_fronth(Node* head, HanoiHandler data);
Node* pop_fronth(Node* head);
Node* insert_nodeh_after(Node* node, HanoiHandler data);
Node* push_fronth(Node* head, HanoiHandler data);
Node* get_last_nodeh(Node* head);
void remove_nodeh_after(Node* node);
int destroy_linked_listh(Node* head);

Pillar get_move_target(Pillar lhs, Pillar rhs);
void draw_piece(double size, double startX, double startY);
void draw_base();

void hanoi();

void update_window();

