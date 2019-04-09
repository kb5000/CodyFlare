#pragma once

//if you want to use the previous color system, you also need to undefine this in graphics.h
#define NEW_COLOR_SYSTEM

#ifdef NEW_COLOR_SYSTEM

typedef struct {
	int r, g, b;
} Color;

///name: get_color
///func: get current color
///visb: public
Color get_color();
///name: set_color
///func: set pen color
///para: color expects a color which r, g, b is a int from 0 to 255
///visb: public
void set_color(Color color);
///name: assign_to_color
///func: assign to a color by r, g and b
///para: r, g, b expect int from 0 to 255
///visb: public
void assign_to_color(Color* target, int r, int g, int b);
///name: color_by_rgb
///func: return the Color determined by r, g and b
///para: r, g, b expect int from 0 to 255
///visb: public
Color color_by_rgb(int r, int g, int b);
///name: color_by_real
///func: return the Color determined by r, g and b
///para: r, g, b expect double from 0 to 1
///visb: public
Color color_by_real(double r, double g, double b);
///name: color_by_name
///func: return the Color in the color list(see color.c for more infomation)
///para: name expects a valid name in the list
///visb: public
Color color_by_name(const char* name);
///name: color_by_hsl
///func: return the Color determined by h, s and l
///para: h expects int from 0 to 359, s and l expect int from 0 to 255
///visb: public
Color color_by_hsl(int h, int s, int l);
///name: color_by_yuv
///func: return the Color determined by y, u and v
///para: y, u, v expect int from 0 to 255
///visb: public
Color color_by_yuv(int y, int u, int v);

#endif //end of NEW_COLOR_SYSTEM

