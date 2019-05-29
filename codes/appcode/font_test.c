#include "font_test.h"
#include "font.h"
#include "anime_test.h"
#include "graphics.h"
#include "animes.h"
#include "spline_test.h"
#include "spline_interpolation.h"
#include "utility.h"

void test_of_font() {
	common_anime_test_init();
	int i;
	double size = 2.8;
	double H = GetWindowHeight();
	double W = GetWindowWidth();
	double h = size * H / 20.0;//������
	double w = size * W / 40.0;//������
	char title[10][20] = { "TO THE SPACE","START","VICTORY","GAME OVER","PAUSE" };
	char letters[20];

	strcpy(letters, title[4]);//title[i]

	if (!strcmp(letters, "TO THE SPACE"))
		letter_color = 1;
	else if (!strcmp(letters, "START"))
		letter_color = 2;
	else if (!strcmp(letters, "VICTORY"))
		letter_color = 3;
	else if (!strcmp(letters, "GAME OVER"))
		letter_color = 4;
	else if (!strcmp(letters, "PAUSE"))
		letter_color = 5;

	int len = strlen(letters);
	double xStart = W / 2.0 - w * len / 2.0;
	for (i = 0; i < len; i++) {
		if (letters[i] == ' ')continue;
		ShowLetter(letters[i], size, xStart + i * w, (H + 1.7*h) / 2, letter_color);
	}

}

