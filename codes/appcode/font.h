#pragma once

typedef struct {
	double size,x,y;
} FontData;

int get_letter_color();

void set_letter_color(int color);

void show_font(const char* str, int color);

//int letterColor;

void ShowLetter(char ch, double size, double x, double y);
void showA(FontData*);
void showC(FontData*);
void showE(FontData*);
void showG(FontData*);
void showH(FontData*);
void showI(FontData*);
void showM(FontData*);
void showO(FontData*);
void showP(FontData*);
void showR(FontData*);
void showS(FontData*);
void showT(FontData*);
void showU(FontData*);
void showV(FontData*);
void showY(FontData*);


