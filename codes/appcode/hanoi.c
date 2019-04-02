#include <stdlib.h>
#include <math.h>
#include "graphics.h"
#include "imgui.h"
#include "strlib.h"
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


///these are global consts
//global timer delay, can be changed to adjust the speed
static int timerDelay = 32;
static const int globalTimerId = 1;
//the max height
static const double heightWhenTurning = 6;
static const double heightOfPiece = 0.525;

///these are global flags
static bool startMovingFlag = false;
static bool elementTurningFlag = false;
static bool sequenceOutFlag = false;
static bool currentMovingFlag = false;

///these are global node pointers
//a queue contains the steps to solve the hanoi problem
static Node* headOfMoves, *tailOfMoves;
//stacks of 3 pillars
static Node* stkHeadA, *stkTailA, *stkHeadB, *stkTailB, *stkHeadC, *stkTailC;
//the moving node
static Node* currentMovingPiece, *currentMovingDirector;

///these are global variables
//pieces in pillarN
static int numOfPA, numOfPB, numOfPC;
//text of the text box
static char textBoxText[16];
//total number of the pieces
static int numOfElements = 3;

void CharEventProcess(char ch) {
	uiGetChar(ch); // GUI字符输入
}

void KeyboardEventProcess(int key, int event) {
	uiGetKeyboard(key, event); // GUI获取键盘
}

void MouseEventProcess(int x, int y, int button, int event) {
	uiGetMouse(x, y, button, event); //GUI获取鼠标
}

void TimerEventProcess(int id) {
	//use this to update the screen to reduce the frequency of refresh
	update_window();
}

//move the element to the certain pillar, one step
//return false means it still needs to move, true means it has done the moving task
bool move_element() {
	SetPenColor("Blue");
	//null sequency leads to stop moving
	if (!sequenceOutFlag && !headOfMoves) {
		startMovingFlag = false;
		return false;
	}
	//pop from the sequence and start moving
	if (!sequenceOutFlag) {
		//free the previous node
		if (currentMovingDirector) free(currentMovingDirector);
		currentMovingDirector = headOfMoves;
		headOfMoves = headOfMoves->next;
		sequenceOutFlag = true;
	}
	//pop from the source pillar and move
	if (!currentMovingFlag) {
		switch (currentMovingDirector->data.position) {
		case PILLAR_A:
			currentMovingPiece = stkHeadA;
			if (numOfPA > 0) {
				numOfPA--;
				stkHeadA = stkHeadA->next;
			}
			break;
		case PILLAR_B:
			currentMovingPiece = stkHeadB;
			if (numOfPB > 0) {
				numOfPB--;
				stkHeadB = stkHeadB->next;
			}
			break;
		case PILLAR_C:
			currentMovingPiece = stkHeadC;
			if (numOfPC > 0) {
				numOfPC--;
				stkHeadC = stkHeadC->next;
			}
			break;
		}
		//align it
		currentMovingPiece->data.x -= 0.02;
		currentMovingFlag = true;
	}
	//chect it twice to avoid crash
	if (!currentMovingPiece) {
		startMovingFlag = false;
		return true;
	}
	//move up
	if (currentMovingPiece->data.y < heightWhenTurning && !elementTurningFlag) {
		currentMovingPiece->data.y += 0.05;
	} else if (!elementTurningFlag) {
		//move horizontally
		const double moveRate = 0.1;
		if (currentMovingDirector->data.position == PILLAR_A && currentMovingDirector->data.towardsPosition == PILLAR_B ||
			currentMovingDirector->data.position == PILLAR_B && currentMovingDirector->data.towardsPosition == PILLAR_C) {
			if (currentMovingPiece->data.x >= 4.78 && currentMovingDirector->data.position == PILLAR_A ||
				currentMovingPiece->data.x >= 7.4 && currentMovingDirector->data.position == PILLAR_B) {
				if (currentMovingDirector->data.towardsPosition == PILLAR_B) currentMovingPiece->data.x = 4.95;
				if (currentMovingDirector->data.towardsPosition == PILLAR_C) currentMovingPiece->data.x = 7.46;
				elementTurningFlag = true;
				return false;
			}
			currentMovingPiece->data.x += moveRate;
		} else if (currentMovingDirector->data.position == PILLAR_B && currentMovingDirector->data.towardsPosition == PILLAR_A ||
				   currentMovingDirector->data.position == PILLAR_C && currentMovingDirector->data.towardsPosition == PILLAR_B) {
			if (currentMovingPiece->data.x <= 2.6 && currentMovingDirector->data.position == PILLAR_B ||
				currentMovingPiece->data.x <= 5.1 && currentMovingDirector->data.position == PILLAR_C) {
				if (currentMovingDirector->data.towardsPosition == PILLAR_B) currentMovingPiece->data.x = 4.95;
				if (currentMovingDirector->data.towardsPosition == PILLAR_A) currentMovingPiece->data.x = 2.44;
				elementTurningFlag = true;
				return false;
			}
			currentMovingPiece->data.x -= moveRate;
		} else if (currentMovingDirector->data.position == PILLAR_A && currentMovingDirector->data.towardsPosition == PILLAR_C) {
			if (currentMovingPiece->data.x >= 7.15) {
				if (currentMovingDirector->data.towardsPosition == PILLAR_C) currentMovingPiece->data.x = 7.46;
				elementTurningFlag = true;
				return false;
			}
			currentMovingPiece->data.x += 2 * moveRate;
		} else if (currentMovingDirector->data.position == PILLAR_C && currentMovingDirector->data.towardsPosition == PILLAR_A) {
			if (currentMovingPiece->data.x <= 2.8) {
				if (currentMovingDirector->data.towardsPosition == PILLAR_A) currentMovingPiece->data.x = 2.44;
				elementTurningFlag = true;
				return false;
			}
			currentMovingPiece->data.x -= 2 * moveRate;
		}
	} else {
		//move down
		double height = 1.2;
		switch (currentMovingDirector->data.towardsPosition) {
		case PILLAR_A:
			height += heightOfPiece * (numOfPA);
			break;
		case PILLAR_B:
			height += heightOfPiece * (numOfPB);
			break;
		case PILLAR_C:
			height += heightOfPiece * (numOfPC);
			break;
		}
		if (currentMovingPiece->data.y <= height) {
			//if (tailOfMoves == currentMovingPiece) tailOfMoves = NULL;
			//currentMovingPiece = pop_fronth(currentMovingPiece);

			//quit moving, push to the target pillar
			elementTurningFlag = false;
			switch (currentMovingDirector->data.towardsPosition) {
			case PILLAR_A:
				stkHeadA = push_fronth(stkHeadA, currentMovingPiece->data);
				numOfPA++;
				break;
			case PILLAR_B:
				stkHeadB = push_fronth(stkHeadB, currentMovingPiece->data);
				numOfPB++;
				break;
			case PILLAR_C:
				stkHeadC = push_fronth(stkHeadC, currentMovingPiece->data);
				numOfPC++;
				break;
			}
			currentMovingFlag = false;
			sequenceOutFlag = false;
			return true;
		}
		currentMovingPiece->data.y -= 0.05;
	}
	//draw the moving piece
	draw_piece(currentMovingPiece->data.size, currentMovingPiece->data.x, currentMovingPiece->data.y);
	return false;
}

void hanoi_handler(int num, Pillar position, Pillar towardsPosition) {
	//use this to store a piece info, may be a waste
	HanoiHandler data = {
		position,
		1, 1, 1,
		towardsPosition
	};
	//when finish the function
	if (num <= 1) {
		tailOfMoves = push_nodeh(tailOfMoves, data);
		if (!headOfMoves) {
			headOfMoves = tailOfMoves;
		}
		return;
	}
	Pillar middle = get_middle_target(position, towardsPosition);
	hanoi_handler(num - 1, position, middle);
	tailOfMoves = push_nodeh(tailOfMoves, data);
	hanoi_handler(num - 1, middle, towardsPosition);
}

Node* new_nodeh(HanoiHandler initData) {
	Node* head = (Node*)malloc(sizeof(Node));
	head->data = initData;
	head->next = NULL;
	return head;
}

Node* push_nodeh(Node* tail, HanoiHandler data) {
	if (!tail) {
		return new_nodeh(data);
	}
	Node* res = new_nodeh(data);
	tail->next = res;
	return res;
}

Node* push_fronth(Node* head, HanoiHandler data) {
	Node* res = new_nodeh(data);
	res->next = head;
	return res;
}

Node* pop_fronth(Node* head) {
	if (!head || !head->next) return NULL;
	Node* res = head->next;
	free(head);
	return res;
}

Node* insert_nodeh_after(Node* node, HanoiHandler data) {
	if (!node) {
		return new_nodeh(data);
	}
	Node* res = new_nodeh(data);
	res->next = node->next;
	node->next = res;
	return res;
}

Node* clone_nodeh(Node* head) {
	if (!head) return NULL;
	Node* res = new_nodeh(head->data);
	Node* tail = res;
	head = head->next;
	while (head) {
		tail = push_nodeh(tail, head->data);
		head = head->next;
	}
	return res;
}

Node* reverse_nodeh(Node* head) {
	//use 3 pointers to reverse it
	Node* firstN = NULL;
	Node* secondN = head;
	if (!secondN) return NULL;
	Node* thirdN = secondN->next;
	while (thirdN) {
		secondN->next = firstN;
		firstN = secondN;
		secondN = thirdN;
		thirdN = thirdN->next;
	}
	secondN->next = firstN;
	return secondN;
}

Node* get_last_nodeh(Node* head) {
	if (!head) return NULL;
	while (head->next) {
		head = head->next;
	}
	return head;
}

void remove_nodeh_after(Node* node) {
	if (!node || !node->next) {
		return;
	}
	Node* to_delete = node->next;
	node->next = node->next->next;
	free(to_delete);
}

int destroy_linked_listh(Node* head) {
	while (head) {
		Node* to_destroy = head;
		head = head->next;
		free(to_destroy);
	}
	return 1;
}

Pillar get_middle_target(Pillar lhs, Pillar rhs) {
	if (lhs != PILLAR_A && rhs != PILLAR_A) return PILLAR_A;
	if (lhs != PILLAR_B && rhs != PILLAR_B) return PILLAR_B;
	if (lhs != PILLAR_C && rhs != PILLAR_C) return PILLAR_C;
	//this is not necessary, just to avoid invalid parameter
	return PILLAR_A;
}

void draw_piece(double size, double startX, double startY) {
	MovePen(startX + size, startY);
	//DrawLine(0.001, 0.001);
	//the equation is x^2 / a + y^4 / b = 1
	for (double i = 0; i < PI; i += 0.05) {
		double drawX = size * cos(i);
		double drawY = 0.1 * pow(sin(i), 2) / 6;
		DrawLine(drawX, drawY);
	}
	for (double i = 0; i < PI; i += 0.05) {
		double drawX = -1.0 * size * cos(i);
		double drawY = -1.0 * 0.1 * pow(sin(i), 2) / 6;
		DrawLine(drawX, drawY);
	}
	//drawRectangle(startX, startY, 0.925, 0.525, 0);
}

void draw_base() {
	SetPenColor("Black");
	MovePen(1, 1);
	//the base
	drawRectangle(1, 1, 8, 0.2, 0);
	MovePen(2.5, 1.2);
	//pillar A
	DrawLine(0, 4);
	MovePen(5, 1.2);
	//pillar B
	DrawLine(0, 4);
	MovePen(7.5, 1.2);
	//pillar C
	DrawLine(0, 4);
}

void draw_all_pieces() {
	//Node* nodeOfPiece = headOfMoves;
	//SetPenColor("Blue");
	//while (nodeOfPiece) {
	//	draw_piece(nodeOfPiece->data.size, nodeOfPiece->data.x, nodeOfPiece->data.y);
	//	nodeOfPiece = nodeOfPiece->next;
	//}
	SetPenColor("Blue");
	double height = 1.2;
	//this is to repair a bug
	Node* headOfPiece;
	Node* nodeOfPiece = reverse_nodeh(clone_nodeh(stkHeadA));
	headOfPiece = nodeOfPiece;
	int i = 0;
	while (nodeOfPiece) {
		nodeOfPiece->data.x = 2.44;
		nodeOfPiece->data.y = height + heightOfPiece * i++;
		draw_piece(nodeOfPiece->data.size, nodeOfPiece->data.x, nodeOfPiece->data.y);
		nodeOfPiece = nodeOfPiece->next;
	}
	//avoid memory leak
	destroy_linked_listh(headOfPiece);
	nodeOfPiece = reverse_nodeh(clone_nodeh(stkHeadB));
	headOfPiece = nodeOfPiece;
	i = 0;
	while (nodeOfPiece) {
		nodeOfPiece->data.x = 4.95;
		nodeOfPiece->data.y = height + heightOfPiece * i++;
		draw_piece(nodeOfPiece->data.size, nodeOfPiece->data.x, nodeOfPiece->data.y);
		nodeOfPiece = nodeOfPiece->next;
	}
	destroy_linked_listh(headOfPiece);
	nodeOfPiece = reverse_nodeh(clone_nodeh(stkHeadC));
	headOfPiece = nodeOfPiece;
	i = 0;
	while (nodeOfPiece) {
		nodeOfPiece->data.x = 7.46;
		nodeOfPiece->data.y = height + heightOfPiece * i++;
		draw_piece(nodeOfPiece->data.size, nodeOfPiece->data.x, nodeOfPiece->data.y);
		nodeOfPiece = nodeOfPiece->next;
	}
	destroy_linked_listh(headOfPiece);
}

Node* build_nodes() {
	//init data
	HanoiHandler piece = {
		PILLAR_A,
		2.5,
		1.2 + (numOfElements - 1) * heightOfPiece,
		0.02,
		PILLAR_C
	};
	Node* head = new_nodeh(piece);
	Node* tail = head;
	for (int i = 1; i < numOfElements; i++) {
		piece.y -= heightOfPiece;
		piece.size *= 1.15;
		tail = push_nodeh(tail, piece);
	}
	return head;
}

void draw_text_and_button() {
	if (textbox(GenUIID(1234), 1, 0.3, 1.4, 0.3, textBoxText, 8)) {
		bool flagOfValidText = true;
		//it will update only if it is a valid number
		for (int i = 0; i < 32; i++) {
			if (!textBoxText[i]) {
				if (i == 0) flagOfValidText = false;
				break;
			}
			if (textBoxText[i] < '0' || textBoxText[i] > '9') {
				flagOfValidText = false;
				break;
			}
		}
		if (flagOfValidText) {
			int nOfElements = StringToInteger(textBoxText);
			numOfElements = nOfElements > 0 ? nOfElements : numOfElements;
			if (numOfElements > 7) numOfElements = 7;
		}
	}
	if (button(GenUIID(234), 2.8, 0.3, 0.6, 0.3, "Start")) {
		//must set the pointer to NULL
		destroy_linked_listh(headOfMoves);
		headOfMoves = tailOfMoves = NULL;
		destroy_linked_listh(stkHeadA);
		destroy_linked_listh(stkHeadB);
		destroy_linked_listh(stkHeadC);
		stkHeadA = stkHeadB = stkHeadC = stkTailA = stkTailB = stkTailC = NULL;
		numOfPA = numOfPB = numOfPC = 0;
		//free single node
		if (currentMovingPiece)
			free(currentMovingPiece);
		currentMovingPiece = NULL;

		//unset flags
		elementTurningFlag = sequenceOutFlag = currentMovingFlag = false;
		//build new nodes
		Node* baseNode = build_nodes();
		//caculate
		hanoi_handler(numOfElements, PILLAR_A, PILLAR_C);
		//push to the first
		stkHeadA = baseNode;
		//destroy_linked_listh(baseNode);
		numOfPA = numOfElements;
		startMovingFlag = true;
	}
	//set a new timer
	if (button(GenUIID(996), 3.7, 0.3, 0.6, 0.3, "Fast")) {
		if (timerDelay > 10)
			timerDelay = (int)(timerDelay / 1.5);
		cancelTimer(globalTimerId);
		startTimer(globalTimerId, timerDelay);
	}
	if (button(GenUIID(738), 4.6, 0.3, 0.6, 0.3, "Slow")) {
		if (timerDelay < 60)
			timerDelay = (int)(timerDelay * 1.5);
		cancelTimer(globalTimerId);
		startTimer(globalTimerId, timerDelay);
	}
	SetPenColor("Red");
	char p[200] = {0};
	sprintf(p, "Current num of piece is %d, piece in A is %d, piece in B is %d, piece in C is %d, "
			"moving is %d", numOfElements, numOfPA, numOfPB, numOfPC, startMovingFlag);
	drawLabel(0.1, 0.1, p);
}

void update_window() {
	DisplayClear();
	draw_all_pieces();
	draw_text_and_button();
	draw_base();
	if (startMovingFlag) {
		move_element();
	}
	//draw_piece(0.08, 1, 2);
}

void hanoi() {
	
	InitGraphics();
	InitGUI();
	registerCharEvent(CharEventProcess); 
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);      
	registerTimerEvent(TimerEventProcess); 
	//draw_base();
	//draw_piece(0.08, 1, 2);
	//draw_text_and_button();
	startTimer(globalTimerId, timerDelay);
}

void Main() {
	hanoi();
}
