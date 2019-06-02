#include "function_drawer.h"
#include <math.h>
#include "graphics.h"
#include "imgui.h"
#include "timer.h"
#include <stdlib.h>
#include "start_page.h"
#include "ingame.h"
#include "extgraph.h"
#include "animes.h"
#include "input.h"
#include "spline_interpolation.h"
#include "plane.h"
#include "sheet.h"

static int flag = 1;
static int n = 0;
Pos org;

Pos calc_det_s(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	//int r = (int)(dfh->rotate * 360 / 6.283);
	double para = dfh->extraPara;
	Pos pos = {GetCurrentX(), GetCurrentY()};
	Pos p = rect_to_polar(sub_pos(org, pos));
	int colrh = (int)(p.y * 0.2 * p.x * 180 / PI);
	int colrs = (int)((p.x - 5) * (p.x - 5) * 256);
	set_color(color_by_hsl(colrh < 0 ? 360 - colrh : colrh, colrs < 90 ? 90 : colrs, 128));
	return new_pos(-sin(3 * t) * cos(4 * dfh->rotate + PI / 3),
				   0.5 - 0.5 * sin(3 * t) * cos(para * t));
}

void tts_s(void* dds) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)dds;
	Color c;
	double para = dfh->extraPara;
	org = new_pos(6 * cos((para - 55.9) / 6.9 * PI) + 6, 4.2 * sin((para - 55.9) / 6.9 * PI) + 4.2);

	for (dfh->rotate = 0.02; dfh->rotate < 3.1416 * 2; dfh->rotate += 3.1416 / 45) {
		draw_function(dfh);
		//need to clear the t and the bias to redraw it
		dfh->tNow = 0;
		dfh->drawPositionBias = new_pos(0, 0);
	}
	//the para runs from 65.6 to 60.8
	//dfh->extraPara += 0.1;
	//char par[32];
	//sprintf(par, "ex: %f", para);
	//drawLabel(1, 1, par);

	if (para < 62.8) {
		dfh->extraPara += 0.1 * flag;
		//uncomment set_color in calc_det to see the effect
		c = color_by_real(0.6 - (para - 60.7) / 4.8 * 0.2, sin(para), cos(para));
		dfh->color = c;
	} /*else {
		flag = -flag;
		dfh->extraPara += 0.1 * flag;
	}*/
	//We can use either of them to disable the function, recommand to use disable_me_in_timer()
	//If you just want to count like this, just pass to the timer
	if (n++ > 90) {
		//remove_funcs_from_timer(1);
		//disable_me_in_timer();
	}
}

void show_start_page() {
	//We must use malloc to create parameters if it will be passed by the timer
	//DrawFuncHolder* dfh = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	hnew(DrawFuncHolder, dfh);
	//paras: func to call, origin, bias, size, t start, t max, t step, rotate radius, color, pen size, extra para
	*dfh = create_function_holder(calc_det_s, new_pos(5, 3.5), new_pos(0, 0), 0.9, 0, 13, 0.1, 0, color_by_name("Black"), 1, 55.9);
	add_func_to_timer(tts_s, dfh, 1, Unique_ID("BossAnime"), 900);
	//clear it in a long time interval, this can increase the performance
}

void game_page_handler(Pos* pos) {
	//MouseKeys mk = get_mouse_key();
	if (pos_length(sub_pos(last_mouse_up_pos(), *pos)) < 0.5) {
		if (is_pause()) continue_game();
		reload_game();
		start_game();
		set_game_mode(0);
	}
}

void game_page_handler_b(Pos* pos) {
	//MouseKeys mk = get_mouse_key();
	if (pos_length(sub_pos(last_mouse_up_pos(), *pos)) < 0.5) {
		if (is_pause()) continue_game();
		reload_game();
		start_game();
		set_game_mode(1);
	}
}

static char gamePlay[11][80] = {
	"经过在瓦坎达的殊死奋战，地球上的超级英雄们依然未",
	"能组止灭霸拿走最后一块心灵宝石，打下那夺走宇宙一",
	"半生命的响指。而远在宇宙另一边的泰坦星球上，钢铁",
	"侠托尼史塔克与星云在失去战友的悲痛中修复飞船，踏",
	"上了希望渺茫的归乡之旅。而地球上的幸存者们也在面",
	"对着浩瀚的星海，不惜一切代价地寻找史塔克的踪迹...",
	"而来自中华人民共和国，被中国人民誉为\"京奇队长\"",
	"，代号\"冷锋\"的航天员刘培强，光荣地接受了组织给",
	"他的任务--孤身驾驶战机前往宇宙寻找并拯救钢铁侠",
	"托尼史塔克。而在搜救途中，冷锋遭遇了克里人指控者",
	"部队的阻击，一场大战一触即发..."
};

void game_play_drawer(Vector* vec) {
	show_sheet(vec, new_pos(5.5, 1.2), new_pos(4.2, 3),  11, 1, 0, 0, 0.3, color_by_name("DarkGrey"), color_by_name("Black"),
			   color_by_rgb(216, 192, 180), "Default", 16, "Default", 16, 'L');
}

void draw_game_play() {
	hnew(Vector, info);
	*info = gen_empty_vector(Vector);
	for (int i = 0; i < 11; i++) {
		Vector vec = gen_empty_vector(char[80]);
		calls(vec, push, gamePlay[i]);
		pcalls(info, push, &vec);
	}
	add_func_to_timer(game_play_drawer, info, 1, 3999, -1);
}

static char shortHelp[1][80] = {
	"提示：上下左右移动，空格导弹，F键炸弹，S键加速"
};

void short_help_drawer(Vector* vec) {
	show_sheet(vec, new_pos(5.5, 0.6), new_pos(4.2, 0.3),  1, 1, 0, 0, 0.3, color_by_name("DarkGrey"), color_by_rgb(0, 17, 203),
			   color_by_rgb(216, 192, 180), "Default", 18, "Default", 18, 'L');
}

void draw_short_help() {
	hnew(Vector, info);
	*info = gen_empty_vector(Vector);
	for (int i = 0; i < 1; i++) {
		Vector vec = gen_empty_vector(char[80]);
		calls(vec, push, shortHelp[i]);
		pcalls(info, push, &vec);
	}
	add_func_to_timer(short_help_drawer, info, 1, 3999, -1);
}

void draw_game_page_anime() {
	hnew(Pos, pos);
	set_pos(pos, 4.5, 3.32);
	draw_anime_shield(83838, *pos, 0.5, -1, 0);
	hnew(Pos, posb);
	set_pos(posb, 4.5, 2.05);
	draw_anime_shield(83838, *posb, 0.5, -1, 1);
	add_func_to_timer(game_page_handler, pos, 1, 93939, -1);
	add_func_to_timer(game_page_handler_b, posb, 1, 93939, -1);
	//add_func_to_timer(big_plane, NULL, 1, 3838999, -1);
}

void big_plane(Pos* pos)
{
	double x0 = pos->x, y0 =pos->y;
	double e = 0.4;
	Pos temp;

	Vector v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x0+0.03*e, y0+0.2*e), &temp));
	calls(v, push, (temp = new_pos(x0+1.1*e, y0+3.6*e), &temp));
	Spline* sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);

	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x0 + 1.1*e, y0 + 3.6*e), &temp));
	calls(v, push, (temp = new_pos(x0+1.4*e, y0+3.55*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);

	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x0 + 1.4*e, y0 + 3.55*e), &temp));
	calls(v, push, (temp = new_pos(x0 + 1.1*e, y0 + 0.1*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);

	double x1 = x0 + 1.1*e, y1 = y0 + 0.1*e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x1, y1), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.2*e, y1 - 0.15*e), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.4*e, y1 - 0.35*e), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.6*e, y1 - 0.6*e), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.8*e, y1 - 1.0*e), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.7*e, y1 - 1.3*e), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.3*e, y1 - 1.6*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 0.3*e, y1 - 1.8*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 0.9*e, y1 - 1.8*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.05*e, y1 - 1.78*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.2*e, y1 - 1.72*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.7*e, y1 - 1.32*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.9*e, y1 - 1.07*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 2.1*e, y1 - 0.5*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.8*e, y1 - 0.1*e), &temp));
	calls(v, push, (temp = new_pos(x0 + 0.03*e, y0 + 0.2*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);

	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x0 + 1.2*e, y0 + 3.6*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.1*e, y1 - 1.7*e), &temp));
	calls(v, push, (temp = new_pos(x0 + 1.25*e, y0 + 3.55*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 0.9*e, y1 - 1.8*e), &temp));
	calls(v, push, (temp = new_pos(x0 + 1.3*e, y0 + 3.6*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 0.7*e, y1 - 1.85*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);

	double x2 = x0 + 0.33*e, y2 = y0 - 0.15*e  ;

	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x2, y2), &temp));
	calls(v, push, (temp = new_pos(x2 - 0.8*e, y2 - 0.2*e), &temp));
	calls(v, push, (temp = new_pos(x2 - 0.8*e, y2 - 0.6*e), &temp));
	calls(v, push, (temp = new_pos(x2 - 0.1*e, y2 - 1.1*e), &temp));
	calls(v, push, (temp = new_pos(x2 + 0.3*e, y2 - 1.1*e), &temp));
	calls(v, push, (temp = new_pos(x2 + 0.3*e, y2 - 1.1*e), &temp));
	calls(v, push, (temp = new_pos(x2 + 0.99*e, y2 - 0.9*e), &temp));
	calls(v, push, (temp = new_pos(x2 + 0.92*e, y2 - 0.5*e), &temp));
	calls(v, push, (temp = new_pos(x2 + 0.33*e, y2 - 0.02*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);

	

	double x3 = x0 - 0.52 * e, y3 = y0 - 0.42 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x3, y3), &temp));
	calls(v, push, (temp = new_pos(x3 - 3 * e, y3 - 1.6*e), &temp));
	calls(v, push, (temp = new_pos(x3 - 3 * e, y3 - 2.6*e), &temp));
	calls(v, push, (temp = new_pos(x3 - 0.7 * e, y3 - 3.52*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);

	double x4 = x0 + 1.36 * e, y4 = y0 - 1.0 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x4, y4), &temp));
	calls(v, push, (temp = new_pos(x4 + 2.3 * e, y4 - 2.2*e), &temp));
	calls(v, push, (temp = new_pos(x4 + 2.3 * e, y4 - 3.6*e), &temp));
	calls(v, push, (temp = new_pos(x4 - 1.2 * e, y4 - 3.1*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);
	

	double x5 = x0 + 1.1 * e, y5 = y0 - 1.6 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x5, y5), &temp));
	calls(v, push, (temp = new_pos(x5 + 1.0 * e, y5 - 1.7*e), &temp));
	calls(v, push, (temp = new_pos(x5 - .55 * e, y5 - 1.75 * e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);

	double x52 = x0 - 0.6 * e,y52 = y0 - 1.2 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x52, y52), &temp));
	calls(v, push, (temp = new_pos(x52 - 1.3 * e, y52 - 1.2*e), &temp));
	calls(v, push, (temp = new_pos(x52 - 0.33 * e, y52 - 1.9*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);

	double x6 = x0 - 0.3 * e, y6 = y0 - 1.45 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x6, y6), &temp));
	calls(v, push, (temp = new_pos(x6 - 0.5 * e, y6 - 0.6*e), &temp));
	calls(v, push, (temp = new_pos(x52 - 0.38 * e, y52 - 1.9*e), &temp));
	calls(v, push, (temp = new_pos(x3 - 0.7 * e, y3 - 3.52*e), &temp));
	calls(v, push, (temp = new_pos(x3 - 0.8 * e, y3 - 4.32*e), &temp));
	calls(v, push, (temp = new_pos(x6+0.16*e, y6), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);

	double x7 = x0 + 0.8 * e, y7 = y0 - 1.7 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x7, y7), &temp));
	calls(v, push, (temp = new_pos(x7 + 0.15 * e, y7 - 0.8*e), &temp));
	calls(v, push, (temp = new_pos(x5 - 0.5 * e, y5 - 1.7 * e), &temp));
	calls(v, push, (temp = new_pos(x4 - 1.1 * e, y4 - 3.1*e), &temp));
	calls(v, push, (temp = new_pos(x4 - 1.5 * e, y4 - 4.0*e), &temp));
	calls(v, push, (temp = new_pos(x7-0.2*e, y7+0.1*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	destroy_spline(sp);
	free(sp);

	MovePen(x7-1.64*e, y7-1.8*e);
	DrawLine(0.4*e, -0.35*e);
	DrawLine(0.55*e, 0.05*e);
	MovePen(x7 - 0.5*e, y7 - 0*e);
	DrawLine(-0.5*e, -2.15*e);
	MovePen(x7 - 0.73*e, y7 + 0.02 * e);
	DrawLine(-0.66*e, -2.03*e);

	double x8 = x0 - 3.87 * e, y8 = y0 - 2.5 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x8+0.08*e, y8+.22*e), &temp));
	calls(v, push, (temp = new_pos(x8 - 0.35 * e, y8 - 0.6*e), &temp));
	calls(v, push, (temp = new_pos(x8-0.5*e, y8-2.8*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	DrawLine(e*0.7, e * 2.36);
	destroy_spline(sp);
	free(sp);

	double x9 = x0 + 4.06 * e, y9 = y0 - 4.26 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x9-0.02*e , y9+0.28*e ), &temp));
	calls(v, push, (temp = new_pos(x9 + 0.05 * e, y9 - 0.8*e), &temp));
	calls(v, push, (temp = new_pos(x9 - 0.9 * e, y9 - 2.7*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	DrawLine(e*0.5, e * 2.34);
	destroy_spline(sp);
	free(sp);


}


