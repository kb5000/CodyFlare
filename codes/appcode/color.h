#pragma once

//if you want to use the previous color system, you also need to undefine this in graphics.h
#define NEW_COLOR_SYSTEM

#ifdef NEW_COLOR_SYSTEM

typedef struct {
	int r, g, b;
} Color;

Color get_color();
void set_color(Color color);
Color color_by_rgb(int r, int g, int b);
Color color_by_real(double r, double g, double b);
void assign_to_color(Color* target, int r, int g, int b);
Color color_by_name(const char* name);

Color color_by_yuv(int y, int u, int v);

#endif //end of NEW_COLOR_SYSTEM

