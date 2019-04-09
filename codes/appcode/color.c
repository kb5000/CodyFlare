#include "color.h"

#ifdef NEW_COLOR_SYSTEM
#include "graphics.h"
#include <string.h>

typedef struct {
	const char* name;
	Color color;
} ColorEntry;

#define COLOR_NUMS 64

static ColorEntry globalColorTable[COLOR_NUMS] = {
	{"Black", {0, 0, 0}},
	{"DarkGrey", {90, 90, 90}},
	{"Grey", {154, 154, 154}},
	{"LightGrey", {192, 192, 192}},
	{"White", {255, 255, 255}},
	{"Brown", {90, 51, 13}},
	{"Red", {255, 0, 0}},
	{"Orange", {255, 102, 255}},
	{"Yellow", {255, 255, 0}},
	{"Green", {0, 255, 0}},
	{"Blue", {0, 0, 255}},
	{"Violet", {238, 128, 238}},
	{"Magenta", {255, 0, 255}},
	{"Cyan", {0, 255, 255}},
};


Color get_color() {
	unsigned long color = get_global_color_handler();
	Color res = {
		color & 0xFF,
		(color & 0xFF00) >> 8,
		(color & 0xFF0000) >> 16
	};
	return res;
}

void set_color(Color color) {
	Color prev = get_color();
	if (prev.r != color.r || prev.g != color.g || prev.b != color.b)
		set_global_color_handler(color.r, color.g, color.b);
}

static Color normalize_color(Color color) {
	if (color.r < 0) color.r = 0;
	if (color.g < 0) color.g = 0;
	if (color.b < 0) color.b = 0;
	if (color.r > 255) color.r = 255;
	if (color.g > 255) color.g = 255;
	if (color.b > 255) color.b = 255;
	return color;
}

Color color_by_rgb(int r, int g, int b) {
	Color color = {r, g, b};
	return color;
}

Color color_by_real(double r, double g, double b) {
	Color color = {(int)(r * 256), (int)(g * 256), (int)(b * 256)};
	return normalize_color(color);
}

void assign_to_color(Color* target, int r, int g, int b) {
	target->r = r;
	target->g = g;
	target->b = b;
}

Color color_by_name(const char* name) {
	for (int i = 0; i < COLOR_NUMS; i++) {
		if (strcmp(globalColorTable[i].name, name) == 0) {
			return globalColorTable[i].color;
		}
	}
	return globalColorTable[0].color;
}

Color color_by_hsl(int h, int s, int l) {
	double mh = h / 360.0, ms = s / 256.0, ml = l / 256.0;
	double p, q;
	if (ml < 0.5) {
		q = ml * (1 + ms);
	} else {
		q = ml + ms - ml * ms;
	}
	p = 2 * ml - q;
	double tc[3] = {mh + 1.0 / 3, mh, mh - 1.0 / 3};
	double res[3];
	for (int i = 0; i < 3; i++) {
		if (tc[i] < 0) tc[i] += 1;
		if (tc[i] > 1) tc[i] -= 1;
		if (tc[i] < 1.0 / 6) {
			res[i] = p + ((q - p) * 6 * tc[i]);
		} else if (tc[i] < 1.0 / 2) {
			res[i] = q;
		} else if (tc[i] < 2.0 / 3) {
			res[i] = p + ((q - p) * 6 * (2.0 / 3 - tc[i]));
		} else {
			res[i] = p;
		}
	}
	return color_by_real(res[0], res[1], res[2]);
}

Color color_by_yuv(int y, int u, int v) {
	u -= 128;
	v -= 128;
	Color res = {
		(int)(y + 1.403 * v),
		(int)(y - 0.343 * u - 0.714 * v),
		(int)(y + 1.77 * u)
	};
	return normalize_color(res);
}

#endif //end of NEW_COLOR_SYSTEM
