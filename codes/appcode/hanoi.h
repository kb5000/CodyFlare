#pragma once

#include <stdbool.h>

#define PI 3.1415926535

//it can express 3 pillars A, B and C
typedef enum {
	PILLAR_A, PILLAR_B, PILLAR_C
} Pillar;

//it contains all the basic infomation to draw a piece
typedef struct {
	Pillar position;
	double x, y, size;
	Pillar towardsPosition;
} HanoiHandler;

//it is a linked list
typedef struct _My_List_Node_T {
	HanoiHandler data;
	struct _My_List_Node_T* next;
} Node;

///these are functions to operate a linked list
//it expects an init data and returns a node contains this data
Node* new_nodeh(HanoiHandler initData);
//it will push the data into the tail of the linked list, expecting the tail node, 
//return the new tail node
Node* push_nodeh(Node* tail, HanoiHandler data);
//it will push the data in front of the linked list, expecting the head node, 
//return the new head node
Node* push_fronth(Node* head, HanoiHandler data);
//it will delete a node in front of the linked list, expecting the head node,
//return the new head node
Node* pop_fronth(Node* head);
//it will insert a node after the node, expecting a valid node or NULL, 
//return the node inserted
Node* insert_nodeh_after(Node* node, HanoiHandler data);
//it will return a new list which has the same content as head
Node * clone_nodeh(Node* head);
//it will return the last node of the list, expecting the head node
Node* get_last_nodeh(Node* head);
//it will delete a node right after it
void remove_nodeh_after(Node* node);
//it will destroy the whole list
int destroy_linked_listh(Node* head);


///these are functions to draw and update
//it will move a node in a small step, it will be called repeadly in each tick
bool move_element();
//it will draw a single piece
void draw_piece(double size, double startX, double startY);
//it will draw the pillars and its base
void draw_base();
//it will draw all pieces in the pillar
void draw_all_pieces();
//it will draw a textbox and some buttons, including the event handle
void draw_text_and_button();
//it will redraw the whole window, it will be called by the timer each tick
void update_window();

///these are functions to caculate and basic build
//it will place pieces in the init position, return the list containing the pieces
Node* build_nodes();
//it will solve the hanoi problem recusively
void hanoi_handler(int num, Pillar position, Pillar towardsPosition);
//it is used to get the middle pillar
Pillar get_middle_target(Pillar lhs, Pillar rhs);

//it is the main function packed, it will also start the message loop
void hanoi();

///these are basic event process functions
void CharEventProcess(char ch);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int id);


//these are functions provided in libgraphics
void DisplayClear(void);
void startTimer(int id, int timeinterval);
void cancelTimer(int id);
void SetPenColor(char* color);
