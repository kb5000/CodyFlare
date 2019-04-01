#include <stdlib.h>
#include <math.h>
#include "graphics.h"
#include "imgui.h"
#include "strlib.h"
#include "hanoi.h"

static int timerDelay = 32;
static const int globalTimerId = 1;
static const double heightWhenTurning = 6;
static const double heightOfPiece = 0.525;
static bool startMovingFlag = false;
static bool elementTurningFlag = false;
static bool sequenceOutFlag = false;
static bool currentMovingFlag = false;
static Node* headOfMoves, *tailOfMoves;
static Node* stkHeadA, *stkTailA, *stkHeadB, *stkTailB, *stkHeadC, *stkTailC;
static Node* currentMovingPiece, *currentMovingDirector;
static int numOfPA, numOfPB, numOfPC;
static char textBoxText[32];
static int numOfElements = 3;

// 清屏函数，provided in libgraphics
void DisplayClear(void);
// 计时器启动函数，provided in libgraphics
void startTimer(int id, int timeinterval);

void cancelTimer(int id);
void SetPenColor(char* color);
// 用户的字符事件响应函数
void CharEventProcess(char ch) {
	uiGetChar(ch); // GUI字符输入
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event) {
	uiGetKeyboard(key, event); // GUI获取键盘
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event) {
	uiGetMouse(x, y, button, event); //GUI获取鼠标
}

void TimerEventProcess(int id) {
	update_window();
}

///change the num of the pillar
void changeNumOfPN(Pillar a, Pillar b) {
	switch (a) {
	case PILLAR_A:
		numOfPA--;
		break;
	case PILLAR_B:
		numOfPB--;
		break;
	case PILLAR_C:
		numOfPC--;
		break;
	}
	switch (b) {
	case PILLAR_A:
		numOfPA++;
		break;
	case PILLAR_B:
		numOfPB++;
		break;
	case PILLAR_C:
		numOfPC++;
		break;
	}
}

///move the element to the certain pillar, one step
bool move_element() {
	SetPenColor("Blue");
	if (!sequenceOutFlag && !headOfMoves) {
		startMovingFlag = false;
		return false;
	}
	if (!sequenceOutFlag) {
		if (currentMovingDirector) free(currentMovingDirector);
		currentMovingDirector = headOfMoves;
		headOfMoves = headOfMoves->next;
		sequenceOutFlag = true;
	}
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
		currentMovingPiece->data.x -= 0.04;
		currentMovingFlag = true;
	}
	if (!currentMovingPiece) {
		return true;
	}
	//if (elementMovingFlag) return false;
	if (currentMovingPiece->data.y < heightWhenTurning && !elementTurningFlag) {
		currentMovingPiece->data.y += 0.05;
		if (currentMovingPiece->data.y >= heightWhenTurning) {
			//changeNumOfPN(currentMovingDirector->data.position, currentMovingDirector->data.towardsPosition);
		}
	} else if (!elementTurningFlag) {
		const double moveRate = 0.1;
		if (currentMovingDirector->data.position == PILLAR_A && currentMovingDirector->data.towardsPosition == PILLAR_B ||
			currentMovingDirector->data.position == PILLAR_B && currentMovingDirector->data.towardsPosition == PILLAR_C) {
			if (currentMovingPiece->data.x >= 4.78 && currentMovingDirector->data.position == PILLAR_A ||
				currentMovingPiece->data.x >= 7.4 && currentMovingDirector->data.position == PILLAR_B) {
				elementTurningFlag = true;
			}
			currentMovingPiece->data.x += moveRate;
		} else if (currentMovingDirector->data.position == PILLAR_B && currentMovingDirector->data.towardsPosition == PILLAR_A ||
				   currentMovingDirector->data.position == PILLAR_C && currentMovingDirector->data.towardsPosition == PILLAR_B) {
			if (currentMovingPiece->data.x <= 2.6 && currentMovingDirector->data.position == PILLAR_B ||
				currentMovingPiece->data.x <= 5.1 && currentMovingDirector->data.position == PILLAR_C) {
				elementTurningFlag = true;
			}
			currentMovingPiece->data.x -= moveRate;
		} else if (currentMovingDirector->data.position == PILLAR_A && currentMovingDirector->data.towardsPosition == PILLAR_C) {
			if (currentMovingPiece->data.x >= 7.15) {
				elementTurningFlag = true;
			}
			currentMovingPiece->data.x += 2 * moveRate;
		} else if (currentMovingDirector->data.position == PILLAR_C && currentMovingDirector->data.towardsPosition == PILLAR_A) {
			if (currentMovingPiece->data.x <= 2.8) {
				elementTurningFlag = true;
			}
			currentMovingPiece->data.x -= 2 * moveRate;
		}
	} else {
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
	draw_piece(currentMovingPiece->data.size, currentMovingPiece->data.x, currentMovingPiece->data.y);
	return false;
}

void hanoi_handler(int num, Pillar position, Pillar towardsPosition) {
	//if (!head->next) {
	//	head->data.towardsPosition = position;
	//	tailOfMoves = push_nodeh(tailOfMoves, head->data);
	//	if (!headOfMoves) {
	//		headOfMoves = tailOfMoves;
	//	}
	//	return;
	//}
	//hanoi_handler(head->next, get_move_target(head->next->data.position, position));
	//head->data.towardsPosition = position;
	//tailOfMoves = push_nodeh(tailOfMoves, head->data);
	//if (!headOfMoves) {
	//	headOfMoves = tailOfMoves;
	//}
	//hanoi_handler(head->next, position);
	HanoiHandler data = {
		position,
		1, 1, 1,
		towardsPosition
	};
	if (num <= 1) {
		tailOfMoves = push_nodeh(tailOfMoves, data);
		if (!headOfMoves) {
			headOfMoves = tailOfMoves;
		}
		return;
	}
	Pillar middle = get_move_target(position, towardsPosition);
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
	Node* t = NULL;
	Node* u = head;
	if (!u) return NULL;
	Node* s = u->next;
	while (s) {
		u->next = t;
		t = u;
		u = s;
		s = s->next;
	}
	u->next = t;
	return u;
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

Pillar get_move_target(Pillar lhs, Pillar rhs) {
	if (lhs != PILLAR_A && rhs != PILLAR_A) return PILLAR_A;
	if (lhs != PILLAR_B && rhs != PILLAR_B) return PILLAR_B;
	if (lhs != PILLAR_C && rhs != PILLAR_C) return PILLAR_C;
	return PILLAR_A;
}

void draw_piece(double size, double startX, double startY) {
	MovePen(startX + size, startY);
	//DrawLine(0.001, 0.001);
	for (double i = 0; i < PI; i += 0.05) {
		double drawX = size * cos(i);
		double drawY = 0.1 * pow(sin(i), 2) / 3 / 2;
		DrawLine(drawX, drawY);
	}
	for (double i = 0; i < PI; i += 0.05) {
		double drawX = -1.0 * size * cos(i);
		double drawY = -1.0 * 0.1 * pow(sin(i), 2) / 3 / 2;
		DrawLine(drawX, drawY);
	}
	//drawRectangle(startX, startY, 0.925, 0.525, 0);
}

void draw_base() {
	SetPenColor("Black");
	MovePen(1, 1);
	drawRectangle(1, 1, 8, 0.2, 0);
	MovePen(2.5, 1.2);
	DrawLine(0, 4);
	MovePen(5, 1.2);
	DrawLine(0, 4);
	MovePen(7.5, 1.2);
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
	Node* nodeOfPiece = reverse_nodeh(clone_nodeh(stkHeadA));
	int i = 0;
	while (nodeOfPiece) {
		nodeOfPiece->data.x = 2.43;
		nodeOfPiece->data.y = height + heightOfPiece * i++;
		draw_piece(nodeOfPiece->data.size, nodeOfPiece->data.x, nodeOfPiece->data.y);
		nodeOfPiece = nodeOfPiece->next;
	}
	nodeOfPiece = reverse_nodeh(clone_nodeh(stkHeadB));
	i = 0;
	while (nodeOfPiece) {
		nodeOfPiece->data.x = 4.95;
		nodeOfPiece->data.y = height + heightOfPiece * i++;
		draw_piece(nodeOfPiece->data.size, nodeOfPiece->data.x, nodeOfPiece->data.y);
		nodeOfPiece = nodeOfPiece->next;
	}
	nodeOfPiece = reverse_nodeh(clone_nodeh(stkHeadC));
	i = 0;
	while (nodeOfPiece) {
		nodeOfPiece->data.x = 7.45;
		nodeOfPiece->data.y = height + heightOfPiece * i++;
		draw_piece(nodeOfPiece->data.size, nodeOfPiece->data.x, nodeOfPiece->data.y);
		nodeOfPiece = nodeOfPiece->next;
	}
}

Node* build_nodes() {
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
	if (textbox(GenUIID(1234), 1, 0.3, 1.4, 0.3, textBoxText, 32)) {
		bool flagOfValidText = true;
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
		headOfMoves && destroy_linked_listh(headOfMoves);
		headOfMoves = tailOfMoves = NULL;
		stkHeadA && destroy_linked_listh(stkHeadA);
		stkHeadB && destroy_linked_listh(stkHeadB);
		stkHeadC && destroy_linked_listh(stkHeadC);
		stkHeadA = stkHeadB = stkHeadC = stkTailA = stkTailB = stkTailC = NULL;
		numOfPA = numOfPB = numOfPC = 0;
		if (currentMovingPiece)
			free(currentMovingPiece);
		currentMovingPiece = NULL;
		sequenceOutFlag = currentMovingFlag = false;
		Node* baseNode = build_nodes();
		hanoi_handler(numOfElements, PILLAR_A, PILLAR_C);
		stkHeadA = clone_nodeh(baseNode);
		numOfPA = numOfElements;
		startMovingFlag = true;
		//InitConsole();
		//Node* u = headOfMoves;
		//while (u) {
		//	printf("%d -> %d\n", u->data.position, u->data.towardsPosition);
		//	u = u->next;
		//}
	}
	if (button(GenUIID(996), 3.7, 0.3, 0.6, 0.3, "Fast")) {
		if (timerDelay > 10)
			timerDelay /= 1.25;
		cancelTimer(globalTimerId);
		startTimer(globalTimerId, timerDelay);
	}
	if (button(GenUIID(738), 4.6, 0.3, 0.6, 0.3, "Slow")) {
		if (timerDelay < 60)
			timerDelay *= 1.2;
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
	registerCharEvent(CharEventProcess); // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess);
	//draw_base();
	//draw_piece(0.08, 1, 2);
	//draw_text_and_button();
	startTimer(globalTimerId, timerDelay);
}
