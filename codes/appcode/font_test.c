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
	double h = size * H / 20.0;//×ÖÌå¿ò¸ß
	double w = size * W / 40.0;//×ÖÌå¿ò¿í
	char title[20] = {"VICTORY"};
	if(title[0]=='G')
	int len = strlen(title);
	double xStart = W / 2.0 - w * len / 2.0;
	for (i = 0; i < len; i++) {
		if (title[i] == ' ')continue;
		ShowLetter(title[i], size, xStart + i * w, (H + 1.7*h) / 2);
	}

}

