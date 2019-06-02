#include "font.h"
#include "spline_interpolation.h"
#include "animes.h"

static int letterColor;

Color changing_color(DrawFuncHolder* dfh)
{
	double t = dfh->tNow;
	switch (letterColor)
	{
	case 1:return color_by_rgb(90 + t * 156, t * 96, 100 - 20 * t);break;
	case 2:return color_by_rgb(40 + t * 20, 60 + t * 192, 20);break;
	case 3:return color_by_rgb(60 + t * 192, 60 + t * 192, 0);break;
	case 4:return color_by_rgb(t * 192, t * 40, 30 + t * 128);break;
	case 5:return color_by_rgb(20 - t * 20, 128 + t * 128, 128 + t * 128);break;
	default:return color_by_name("Black");break;
	}
}

Color changing_color_sp(DrawFuncHolder* dfh)
{
	double t = (dfh->tNow + dfh->extraPara) / 6;
	switch (letterColor)
	{
	case 1:return color_by_rgb(90 + t * 156, t * 96, 100 - 20 * t);break;
	case 2:return color_by_rgb(40 + t * 20, 60 + t * 192, 20);break;
	case 3:return color_by_rgb(40 + t * 192, 40 + t * 192, 0);break;
	case 4:return color_by_rgb(t * 192, t * 40, 30 + t * 128);break;
	case 5:return color_by_rgb(20 - t * 20, 128 + t * 128, 128 + t * 128);break;
	default:return color_by_name("Black");break;
	}
}

void show_font(const char* str, int color) {
	letterColor = color;
	double size = 2.8;
	double H = GetWindowHeight();
	double W = GetWindowWidth();
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽
	int len = strlen(str);
	double xStart = W / 2.0 - w * len / 2.0;
	for (int i = 0; i < len; i++) {
		if (str[i] == ' ')continue;
		ShowLetter(str[i], size, xStart + i * w, (H + 5*h) / 2);
	}

}

void ShowLetter(char ch, double size, double x, double y) {
	int X = ch - 'A';

	hnew(FontData, pack);//pack是一对数字，xy是字体对应长方形区域左上角的坐标
	pack->size = size;
	pack->x = x;
	pack->y = y;


	switch (X) {
	case 0:add_func_to_timer(showA, pack, 1, 74, -1); break;
	case 2:add_func_to_timer(showC, pack, 1, 74, -1); break;
	case 4:add_func_to_timer(showE, pack, 1, 74, -1); break;
	case 6:add_func_to_timer(showG, pack, 1, 74, -1); break;
	case 7:add_func_to_timer(showH, pack, 1, 74, -1); break;
	case 8:add_func_to_timer(showI, pack, 1, 74, -1); break;
	case 12:add_func_to_timer(showM, pack, 1, 74, -1); break;
	case 14:add_func_to_timer(showO, pack, 1, 74, -1); break;
	case 15:add_func_to_timer(showP, pack, 1, 74, -1); break;
	case 17:add_func_to_timer(showR, pack, 1, 74, -1); break;
	case 18:add_func_to_timer(showS, pack, 1, 74, -1); break;
	case 19:add_func_to_timer(showT, pack, 1, 74, -1); break;
	case 20:add_func_to_timer(showU, pack, 1, 74, -1); break;
	case 21:add_func_to_timer(showV, pack, 1, 74, -1); break;
	case 24:add_func_to_timer(showY, pack, 1, 74, -1); break;
	default:break;
	}
}
void showA(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y - 0.015*size;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		ParabolaHolder ph = create_parabola(74, new_pos(x + e, y - 0.9*h), new_pos(x + w / 1.5 + e, y), new_pos(x + w * 0.9 + e, y - 0.86*h), changing_color, 1);
		draw_parabola(ph, 1);
		ph = create_parabola(74, new_pos(x + w / 4.0, y - h * 0.65 + e), new_pos(x + w * 0.4, y - h * 0.5 + e), new_pos(x + w, y - 0.35*h + e), changing_color, 1);
		draw_parabola(ph, 1);
	}
}


void showC(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y - 0.015*size;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		Vector v = gen_empty_vector(Pos);
		Pos temp;
		calls(v, push, (temp = new_pos(x + 0.8*w + e, y - 0.2*h ), &temp));
		calls(v, push, (temp = new_pos(x + 0.5*w, y - 0.1*h + e), &temp));
		calls(v, push, (temp = new_pos(x + w * 0.1, y - 0.7*h + e), &temp));
		calls(v, push, (temp = new_pos(x + 0.4*w, y - 0.9*h + e), &temp));
		calls(v, push, (temp = new_pos(x + 0.95*w, y - 0.75*h + e), &temp));

		Spline* sp = create_spline(&v, changing_color_sp, 0);
		//add_func_to_timer(draw_spline, sp, 1, 1, -1);
		draw_spline(sp);
		destroy_spline(sp);
		free(sp);
	}
}

void showE(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		ParabolaHolder ph = create_parabola(74, new_pos(x, y - h / 4.0 + e), new_pos(x + w / 2.0, y - h / 8.0 + e), new_pos(x + w, y + e), changing_color, 1);
		draw_parabola(ph, 1);
		ph = create_parabola(74, new_pos(x + w / 8.0 + e, y - h / 4.0 - h / 3.0 + 2 * e), new_pos(x + 9 * w / 16.0 + e, y - h / 8.0 - h / 3.0 + 1.5*e), new_pos(x + w + e, y - h / 3.0 + e), changing_color, 1);
		draw_parabola(ph, 1);
		ph = create_parabola(74, new_pos(x + w / 8.0, y - h / 4.0 - h / 1.5 + 2 * e), new_pos(x + 9 * w / 16.0, y - h / 8.0 - h / 1.5 + 1.5*e), new_pos(x + w, y - h / 1.5 + e), changing_color, 1);
		draw_parabola(ph, 1);
		ph = create_parabola(74, new_pos(x + w * 0.35 + e, y - h / 6.0), new_pos(x + 0.2*w + 1.5*e, y - h * 7 / 12 + 0.5*e), new_pos(x + 2.0*e, y - 0.9*h + e), changing_color, 1);
		draw_parabola(ph, 1);
	}
}

void showG(FontData *FD) {
	double H = GetWindowHeight();
	double W = GetWindowWidth();
	double size = FD->size;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽
	double x = FD->x - size * 0.015;
	double y = FD->y;

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		Vector v = gen_empty_vector(Pos);
		Pos temp;
		calls(v, push, (temp = new_pos(x + 0.9*w + e, y - h / 4.0), &temp));
		calls(v, push, (temp = new_pos(x + 0.91*w + e, y - h / 8), &temp));
		calls(v, push, (temp = new_pos(x + 0.65*w + e, y), &temp));
		calls(v, push, (temp = new_pos(x + 0.3*w + e, y - 0.3*h), &temp));
		calls(v, push, (temp = new_pos(x + 0.1*w + e, y - 0.65*h), &temp));
		calls(v, push, (temp = new_pos(x + 0.4*w + e, y - 0.8*h), &temp));
		calls(v, push, (temp = new_pos(x + 0.8*w + e, y - 0.55*h), &temp));
		calls(v, push, (temp = new_pos(x + 0.98*w + e, y - 0.85*h), &temp));
		Spline* sp = create_spline(&v, changing_color_sp, 0);
		//add_func_to_timer(draw_spline, sp, 1, 1, -1);
		draw_spline(sp);
		destroy_spline(sp);
		free(sp);

	}
}

void showH(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y + 0.005*size;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		double x1, x2, y1, y2;
		x1 = x + 0.1*w;
		x2 = x1;
		y1 = y;
		y2 = y - 0.9*h;
		ParabolaHolder ph = create_parabola(74, new_pos(x1 + 2 * e, y1), new_pos((x1 + x2) / 2.0 + size * 0.01 + e, (y1 + y2) / 2.0), new_pos(x2 + 2 * e, y2), changing_color, 1);
		draw_parabola(ph, 1);
		x1 += 0.7*w;
		x2 += 0.7*w;
		ph = create_parabola(74, new_pos(x1 + 2 * e, y1), new_pos((x1 + x2) / 2.0 + size * 0.01 + e, (y1 + y2) / 2.0), new_pos(x2 + 2 * e, y2), changing_color, 1);
		draw_parabola(ph, 1);
		x1 = x + 0.17*w;
		x2 = x + 0.97*w;
		y1 = y - h * 0.5;
		y2 = y1;
		ph = create_parabola(74, new_pos(x1, y1 + 1.5*e), new_pos((x1 + x2) / 2.0, (y1 + y2) / 2.0 + size * 0.02 + 1.5*e), new_pos(x2, y2 + 1.5*e), changing_color, 1);
		draw_parabola(ph, 1);
	}
}

void showI(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		double x1, x2, y1, y2;
		x1 = x + 0.3*w;
		x2 = x + w * 0.9;
		y1 = y;
		y2 = y + 0.05*h;
		ParabolaHolder ph = create_parabola(74, new_pos(x1, y1 - e), new_pos((x2 + x1) / 2, (y1 + y2) / 2 - e), new_pos(x2, y2 - e), changing_color, 1);
		draw_parabola(ph, 1);
		double t1 = x1, t2 = x2;
		x1 = (x1 + x2) / 2.0 - size * 0.01;
		x2 = x1 - size * 0.03;
		y2 = y - 0.9*h;
		ph = create_parabola(74, new_pos(x1 + e, y1), new_pos((x1 + x2) / 2 + e, (y1 + y2) / 2 - 0.03*h), new_pos(x2 + e, y2), changing_color, 1);
		draw_parabola(ph, 1);
		x1 = t1 - 0.03*size, x2 = t2 - 0.03*size;
		y1 = y2;
		y2 = y1 + 0.02*size;
		ph = create_parabola(74, new_pos(x1, y1 - e), new_pos((x1 + x2) / 2, (y1 + y2) / 2 - e), new_pos(x2 + e, y2 - e), changing_color, 1);
		draw_parabola(ph, 1);

	}
}


void showM(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y - 0.01*size;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		double x1, x2, y1, y2;
		x1 = x + 0.1*w;
		x2 = x1 + 0.5*w;
		y1 = y - 0.66*h;
		y2 = y;
		ParabolaHolder ph = create_parabola(74, new_pos(x1, y1 + e), new_pos(x1 + w / 8, y1 - h / 16 + e), new_pos(x2, y2 + e), changing_color, 1);
		draw_parabola(ph, 1);
		x1 = x2; y1 = y2;
		x2 += 0.3*w;
		ph = create_parabola(74, new_pos(x1, y1 + e), new_pos(x1 + 0.05*w, y1 - 0.5*h + e), new_pos(x2, y2 + e), changing_color, 1);
		draw_parabola(ph, 1);
		x1 = x2; y1 = y2;
		x2 = x + 0.97*w;
		y2 = y - 0.66*h - h / 8;
		ph = create_parabola(74, new_pos(x1, y1 + e), new_pos(x1 + 0.5*e, y1 - 0.6*h + e), new_pos(x2 + 0.5*e, y2 + e), changing_color, 1);
		draw_parabola(ph, 1);
	}
}

void showO(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		Vector v = gen_empty_vector(Pos);
		Pos temp;
		calls(v, push, (temp = new_pos(x + 0.5*w, y - 0.1*h + e), &temp));
		calls(v, push, (temp = new_pos(x + 0.87*w, y - 0.33*h + e), &temp));
		calls(v, push, (temp = new_pos(x + w * 0.8, y - 0.75*h + e), &temp));
		calls(v, push, (temp = new_pos(x + 0.4*w, y - 0.9*h + e), &temp));
		calls(v, push, (temp = new_pos(x + 0.1*w, y - 0.7*h + e), &temp));
		calls(v, push, (temp = new_pos(x + w * 0.2, y - 0.25*h + e), &temp));

		Spline* sp = create_spline(&v, changing_color_sp, 1);
		//add_func_to_timer(draw_spline, sp, 1, 1, -1);
		draw_spline(sp);
		destroy_spline(sp);
		free(sp);

	}
}

void showP(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		double x1, x2, y1, y2;
		x1 = x + 0.2*w;
		x2 = x;
		y1 = y;
		y2 = y - 0.97*h;
		ParabolaHolder ph = create_parabola(74, new_pos(x1 + e, y1), new_pos((x2 + x1) / 2 + e - 0.01*size, (y1 + y2) / 2 - 0.02*size), new_pos(x2 + e, y2), changing_color, 1);
		draw_parabola(ph, 1);
		x2 = x1 - 0.25*w;
		y1 = y1 - 0.05*h;
		y2 = y1 - 0.54*h;
		ph = create_parabola(74, new_pos(x1 + e, y1), new_pos(x1 + 0.6*w + e, y1 - 0.05*h), new_pos(x2 + e, y2), changing_color, 1);
		draw_parabola(ph, 1);

	}
}

void showR(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		double x1, x2, y1, y2;
		x1 = x + 0.3*w;
		x2 = x;
		y1 = y;
		y2 = y - 0.95*h;
		ParabolaHolder ph = create_parabola(74, new_pos(x1 + e, y1), new_pos((x2 + x1) / 2 + e, (y1 + y2) / 2), new_pos(x2 + e, y2), changing_color, 1);
		draw_parabola(ph, 1);
		x2 = x1 - 0.65*(x1 - x);
		y2 = y1 - 0.65*h;
		y1 -= 0.1*h;
		ph = create_parabola(74, new_pos(x1, y1 + e), new_pos(x + 0.75*w, y - 0.25*h + e), new_pos(x2, y2 + e), changing_color, 1);
		draw_parabola(ph, 1);
		x1 = x2; y1 = y2;
		x2 = x + w;
		y2 = y - h * 0.8;
		ph = create_parabola(74, new_pos(x1, y1 + e), new_pos(x2 - 0.3*w, y2 - 0.1*h + e), new_pos(x2, y2 + e), changing_color, 1);
		draw_parabola(ph, 1);

	}
}

void showS(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y - 0.007*size;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		Vector v = gen_empty_vector(Pos);
		Pos temp;
		calls(v, push, (temp = new_pos(x + 0.95*w, y - 0.05*h + e), &temp));
		calls(v, push, (temp = new_pos(x + 0.3*w, y - 0.3*h + e), &temp));
		calls(v, push, (temp = new_pos(x + w * 0.85, y - 0.7*h + e), &temp));
		calls(v, push, (temp = new_pos(x + 0.05*w, y - 0.95*h + e), &temp));

		Spline* sp = create_spline(&v, changing_color_sp, 0);
		//add_func_to_timer(draw_spline, sp, 1, 1, -1);
		draw_spline(sp);
		destroy_spline(sp);
		free(sp);

	}
}


void showT(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		double x1, x2, y1, y2;
		x1 = x + 0.07*w;
		x2 = x + w * 0.93;
		y1 = y - 0.1*h;
		y2 = y - 0.05*h;
		ParabolaHolder ph = create_parabola(74, new_pos(x1, y1 - e), new_pos((x2 + x1) / 2, (y1 + y2) / 2 - e), new_pos(x2, y2 - e), changing_color, 1);
		draw_parabola(ph, 1);
		x1 = x + w / 2.0 - 0.02*w;
		x2 = x + w / 2.0 - 0.1*w;

		y2 = y - 0.95*h;
		ph = create_parabola(74, new_pos(x1 + e, y1), new_pos((x1 + x2) / 2 + e, (y1 + y2) / 2 - 0.03*h), new_pos(x2 + e, y2), changing_color, 1);
		draw_parabola(ph, 1);

	}
}

void showU(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y - 0.015*size;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		Vector v = gen_empty_vector(Pos);
		Pos temp;
		calls(v, push, (temp = new_pos(x + 0.2*w + e, y - 0.02*h ), &temp));
		calls(v, push, (temp = new_pos(x + 0.28*w + e, y - 0.7*h ), &temp));
		calls(v, push, (temp = new_pos(x + 0.46*w + e, y - 0.9*h ), &temp));
		calls(v, push, (temp = new_pos(x + 0.8*w + e, y - 0.7*h), &temp));
		calls(v, push, (temp = new_pos(x + 0.9*w + e, y - 0.02*h), &temp));

		Spline* sp = create_spline(&v, changing_color_sp, 0);
		//add_func_to_timer(draw_spline, sp, 1, 1, -1);
		draw_spline(sp);
		destroy_spline(sp);
		free(sp);
	}
}

void showV(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		double x1, x2, y1, y2;
		x1 = x;
		x2 = x + 0.2*w;
		y1 = y;
		y2 = y - h * 0.9;
		ParabolaHolder ph = create_parabola(74, new_pos(x1 + e, y1), new_pos((x2 + x1) / 2 + e, (y1 + y2) / 2), new_pos(x2 + e, y2), changing_color, 1);
		draw_parabola(ph, 1);
		x1 = x2; y1 = y2;
		x2 = x + 0.9*w;
		y2 = y;
		ph = create_parabola(74, new_pos(x1 + e, y1), new_pos((x2 + x1) / 2 + e, (y1 + y2) / 2), new_pos(x2 + e, y2), changing_color, 1);
		draw_parabola(ph, 1);
	}
}

void showY(FontData *FD) {
	double H = GetWindowHeight(), W = GetWindowWidth();
	double size = FD->size, x = FD->x, y = FD->y;
	double h = size * H / 20.0;//字体框高
	double w = size * W / 40.0;//字体框宽

	double i = 0.0;
	for (; i < 2.1; i += 1.0) {
		double e = size * i*0.01;
		double x1, x2, y1, y2;
		x1 = x + 0.1*w;
		x2 = x + w * 0.9;
		y1 = y - 0.1*h;
		y2 = y - 0.05*h;
		ParabolaHolder ph = create_parabola(74, new_pos(x1, y1 - e), new_pos((x2 + x1) / 2 - 0.04*w, (y1 + y2) / 2 - 0.35*h - e), new_pos(x2, y2 - e), changing_color, 1);
		draw_parabola(ph, 1);
		x1 = x + w / 2.0 - 0.07*w;
		x2 = x + w / 2.0 - 0.17*w;
		y1 = y1 - 0.35*h;
		y2 = y - 0.95*h;
		ph = create_parabola(74, new_pos(x1 + e, y1), new_pos((x1 + x2) / 2 + e, (y1 + y2) / 2 - 0.03*h), new_pos(x2 + e, y2), changing_color, 1);
		draw_parabola(ph, 1);

	}
}
