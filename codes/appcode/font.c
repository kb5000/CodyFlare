#include "font.h"
#include "spline_interpolation.h"
#include "animes.h"

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
	case 12:add_func_to_timer(showM, pack, 1, 74, -1); break;
	case 14:add_func_to_timer(showO, pack, 1, 74, -1); break;
	case 15:add_func_to_timer(showP, pack, 1, 74, -1); break;
	case 17:add_func_to_timer(showR, pack, 1, 74, -1); break;
	case 18:add_func_to_timer(showS, pack, 1, 74, -1); break;
	case 19:add_func_to_timer(showT, pack, 1, 74, -1); break;
	case 21:add_func_to_timer(showV, pack, 1, 74, -1); break;
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
		ParabolaHolder ph = create_parabola(74, new_pos(x + e, y - 0.9*h), new_pos(x + w / 1.5 + e, y), new_pos(x + w * 0.9 + e, y - 0.86*h), NULL, 1);
		draw_parabola(ph, 1);
		ph = create_parabola(74, new_pos(x + w / 4.0, y - h * 0.65 + e), new_pos(x + w * 0.4, y - h * 0.5 + e), new_pos(x + w, y - 0.35*h + e), NULL, 1);
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
		calls(v, push, (temp = new_pos(x + 0.85*w, y - 0.2*h + e), &temp));
		calls(v, push, (temp = new_pos(x + 0.5*w, y - 0.1*h + e), &temp));
		calls(v, push, (temp = new_pos(x + w * 0.1, y - 0.7*h + e), &temp));
		calls(v, push, (temp = new_pos(x + 0.4*w, y - 0.9*h + e), &temp));
		calls(v, push, (temp = new_pos(x + 0.95*w, y - 0.75*h + e), &temp));

		Spline* sp = create_spline(&v, NULL, 0);
		add_func_to_timer(draw_spline, sp, 1, 1, -1);

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
		ParabolaHolder ph = create_parabola(74, new_pos(x, y - h / 4.0 + e), new_pos(x + w / 2.0, y - h / 8.0 + e), new_pos(x + w, y + e), NULL, 1);
		draw_parabola(ph, 1);
		ph = create_parabola(74, new_pos(x + w / 8.0 + e, y - h / 4.0 - h / 3.0 + 2 * e), new_pos(x + 9 * w / 16.0 + e, y - h / 8.0 - h / 3.0 + 1.5*e), new_pos(x + w + e, y - h / 3.0 + e), NULL, 1);
		draw_parabola(ph, 1);
		ph = create_parabola(74, new_pos(x + w / 8.0, y - h / 4.0 - h / 1.5 + 2 * e), new_pos(x + 9 * w / 16.0, y - h / 8.0 - h / 1.5 + 1.5*e), new_pos(x + w, y - h / 1.5 + e), NULL, 1);
		draw_parabola(ph, 1);
		ph = create_parabola(74, new_pos(x + w * 0.35 + e, y - h / 6.0), new_pos(x + 0.2*w + 1.5*e, y - h * 7 / 12 + 0.5*e), new_pos(x + 2.0*e, y - 0.9*h + e), NULL, 1);
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
		Spline* sp = create_spline(&v, NULL, 0);
		add_func_to_timer(draw_spline, sp, 1, 1, -1);

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
		ParabolaHolder ph = create_parabola(74, new_pos(x1 + 2 * e, y1), new_pos((x1 + x2) / 2.0 + size * 0.01 + e, (y1 + y2) / 2.0), new_pos(x2 + 2 * e, y2), NULL, 1);
		draw_parabola(ph, 1);
		x1 += 0.7*w;
		x2 += 0.7*w;
		ph = create_parabola(74, new_pos(x1 + 2 * e, y1), new_pos((x1 + x2) / 2.0 + size * 0.01 + e, (y1 + y2) / 2.0), new_pos(x2 + 2 * e, y2), NULL, 1);
		draw_parabola(ph, 1);
		x1 = x + 0.17*w;
		x2 = x + 0.97*w;
		y1 = y - h * 0.5;
		y2 = y1;
		ph = create_parabola(74, new_pos(x1, y1 + 1.5*e), new_pos((x1 + x2) / 2.0, (y1 + y2) / 2.0 + size * 0.02 + 1.5*e), new_pos(x2, y2 + 1.5*e), NULL, 1);
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
		ParabolaHolder ph = create_parabola(74, new_pos(x1, y1 + e), new_pos(x1 + w / 8, y1 - h / 16 + e), new_pos(x2, y2 + e), NULL, 1);
		draw_parabola(ph, 1);
		x1 = x2; y1 = y2;
		x2 += 0.3*w;
		ph = create_parabola(74, new_pos(x1, y1 + e), new_pos(x1 + 0.05*w, y1 - 0.5*h + e), new_pos(x2, y2 + e), NULL, 1);
		draw_parabola(ph, 1);
		x1 = x2; y1 = y2;
		x2 = x + 0.97*w;
		y2 = y - 0.66*h - h / 8;
		ph = create_parabola(74, new_pos(x1, y1 + e), new_pos(x1 + 0.5*e, y1 - 0.6*h + e), new_pos(x2 + 0.5*e, y2 + e), NULL, 1);
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

		Spline* sp = create_spline(&v, NULL, 1);
		add_func_to_timer(draw_spline, sp, 1, 1, -1);

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
		ParabolaHolder ph = create_parabola(74, new_pos(x1 + e, y1), new_pos((x2 + x1) / 2 + e - 0.01*size, (y1 + y2) / 2 - 0.02*size), new_pos(x2 + e, y2), NULL, 1);
		draw_parabola(ph, 1);
		x2 = x1 - 0.25*w;
		y1 = y1 - 0.05*h;
		y2 = y1 - 0.54*h;
		ph = create_parabola(74, new_pos(x1 + e, y1), new_pos(x1 + 0.6*w + e, y1 - 0.05*h), new_pos(x2 + e, y2), NULL, 1);
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
		ParabolaHolder ph = create_parabola(74, new_pos(x1 + e, y1), new_pos((x2 + x1) / 2 + e, (y1 + y2) / 2), new_pos(x2 + e, y2), NULL, 1);
		draw_parabola(ph, 1);
		x2 = x1 - 0.65*(x1 - x);
		y2 = y1 - 0.65*h;
		y1 -= 0.1*h;
		ph = create_parabola(74, new_pos(x1, y1 + e), new_pos(x + 0.75*w, y - 0.25*h + e), new_pos(x2, y2 + e), NULL, 1);
		draw_parabola(ph, 1);
		x1 = x2; y1 = y2;
		x2 = x + w;
		y2 = y - h * 0.8;
		ph = create_parabola(74, new_pos(x1, y1 + e), new_pos(x2 - 0.3*w, y2 - 0.1*h + e), new_pos(x2, y2 + e), NULL, 1);
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

		Spline* sp = create_spline(&v, NULL, 0);
		add_func_to_timer(draw_spline, sp, 1, 1, -1);

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
		y1 = y - 0.05*h;
		y2 = y - 0.05*h;
		ParabolaHolder ph = create_parabola(74, new_pos(x1, y1 - 2 * e), new_pos((x2 + x1) / 2, (y1 + y2) / 2 - 0.03*h - e), new_pos(x2, y2 - 2 * e), NULL, 1);
		draw_parabola(ph, 1);
		x1 = x + w / 2.0 - 0.02*w;
		x2 = x + w / 2.0 - 0.1*w;
		y1 -= 0.06*h;
		y2 = y - 0.95*h;
		ph = create_parabola(74, new_pos(x1 + 0.7*e, y1), new_pos((x1 + x2)*0.5 + (x1 - x2)*0.3 + e, (y1 + y2) / 2 - 0.03*h), new_pos(x2 + 2.5*e, y2), NULL, 1);
		draw_parabola(ph, 1);

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
		ParabolaHolder ph = create_parabola(74, new_pos(x1 + e, y1), new_pos((x2 + x1) / 2 + e, (y1 + y2) / 2), new_pos(x2 + e, y2), NULL, 1);
		draw_parabola(ph, 1);
		x1 = x2; y1 = y2;
		x2 = x + 0.9*w;
		y2 = y;
		ph = create_parabola(74, new_pos(x1 + e, y1), new_pos((x2 + x1) / 2 + e, (y1 + y2) / 2), new_pos(x2 + e, y2), NULL, 1);
		draw_parabola(ph, 1);
	}
}
