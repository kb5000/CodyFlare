#include "menu.h"
#include "graphics.h"
#include "imgui.h"
#include <stdio.h>
#include "input.h"
#include "timer.h"
#include "tortoise.h"
#include "color.h"
#include "ingame.h"
#include <stdlib.h>
#include "save_plane.h"
#include "game_particle.h"
#include "extgraph.h"
#include "plane.h"

//#define POC 2
static char * menuListFile[] = {"    �� ��",
		"���� | Ctrl-S",
		"��ȡ | Ctrl-L",
	//"���������� | Ctrl-B",
	"�˳� | Ctrl-X"};
static char * menuListGame[] = {"    �� Ϸ",
		"��ʼ����Ϸ | Ctrl-R",
		"�л���ͣ | Ctrl-P",
		"�л�������Ч | Ctrl-G",
		"�л���Ϸģʽ | Ctrl-O",
		"���а� | Ctrl-C"};
static char * menuListCheat[] = {"  �� �� ָ",
		"����ը�� | Ctrl-M",
		"����Ѫ�� | Ctrl-F",
		"���� | Ctrl-A",
		"���� | Ctrl-D"};
static char * menuListAbout[] = {"    �� ��",
		"�鿴���� | Ctrl-H",
		"���� | Ctrl-T"};

void draw_tool_animes();

void show_menu(void* u) {
	int inPause = is_pause();
	char * selectedLabel = NULL;
	double winwidth = GetWindowWidth();
	double winheight = GetWindowHeight();
	//setMenuColors(char *frame, char*label, char *hotFrame, char *hotLabel, int fillflag);
	setMenuColors("Menu1", "Black", "Menu2", "Black", 1);
	SetFont("Default");
	int selection;
	selection = menuList(1, 0, winheight - 0.3, 0.85, 2, 0.3, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection > 0) {
		selectedLabel = menuListFile[selection];
		switch (selection) {
		case 1:	//save
			if (inPause) break;
			save_plane();
			break;
		case 2:	//load
			if (!inPause) pause_game();
			select_saves();
			break;
		case 3: //exit
			exit(0);
			break;
		default:
			break;
		}
	}
	if (selection >= 0) reset_mouse_key(1);
	selection = menuList(2, 0.85, winheight - 0.3, 0.85, 2, 0.3, menuListGame, sizeof(menuListGame) / sizeof(menuListGame[0]));
	if (selection > 0) {
		selectedLabel = menuListGame[selection];
		switch (selection) {
		case 1: //reload
			if (inPause) continue_game();
			reload_game();
			start_game();
			break;
		case 2: //pause
			if (inPause) continue_game();
			else pause_game();
			break;
		case 3: //background
			if (inPause) break;
			toggle_long_particle();
			break;
		case 4: //gamemode
			if (inPause) break;
			set_game_mode(!get_game_mode());
			break;
		case 5: //rank
			break;
		default:
			break;
		}
	}
	if (selection >= 0) reset_mouse_key(1);
	selection = menuList(3, 1.7, winheight - 0.3, 0.85, 2, 0.3, menuListCheat, sizeof(menuListCheat) / sizeof(menuListCheat[0]));
	if (selection > 0) {
		selectedLabel = menuListCheat[selection];
		if (!inPause) {
			switch (selection) {
			case 1: //infbomb
				god_bomb_mode();
				break;
			case 2: //infhp
				god_mode();
				break;
			case 3: //spdup
				speed_up();
				break;
			case 4: //spddown
				speed_down();
				break;
			default:
				break;
			}
		}
	}
	if (selection >= 0) reset_mouse_key(1);
	selection = menuList(4, 2.55, winheight - 0.3, 0.85, 2, 0.3, menuListAbout, sizeof(menuListAbout) / sizeof(menuListAbout[0]));
	if (selection > 0) {
		selectedLabel = menuListAbout[selection];
		switch (selection) {
		case 1: //help
			break;
		case 2: //about
			break;
		default:
			break;
		}
	}
	if (selection >= 0) reset_mouse_key(1);

	//����Ĵ���û����ɫ����������ͼ��0.25*0.25��С��ͼ�����¶�������Ϊ0.6

	draw_tool_animes();

}

void draw_tool_animes() {
	double winwidth = GetWindowWidth();
	double winheight = GetWindowHeight();
	set_color(color_by_name("Menu1"));
	drawRectangle(7.05, 6.68, 3.1, 0.32, 1);
	//set_color(color_by_rgb(190, 45, 106));
	Color entryColor = color_by_rgb(190, 45, 106);
	Color activeColor = color_by_rgb(92, 45, 186);
	MouseKeys ms = get_mouse_key();
	int inPause = is_pause();
	//���д����Ǵ浵ͼ��
	if (pos_in_rect(ms.pos, new_pos(8.9, 6.65), new_pos(9.4, 7))) {
		set_color(activeColor);
		if (ms.left == 2 && pos_in_rect(last_mouse_up_pos(), new_pos(8.9, 6.65), new_pos(9.4, 7))) {
			if (!inPause) save_plane();
			reset_mouse_key(1);
		}
	} else {
		set_color(entryColor);
	}
	MovePen(winwidth - 1.0, winheight - 0.275);
	DrawLine(0, 0.25);
	DrawLine(0.05, 0);
	DrawLine(0, -0.125);
	DrawLine(0.15, 0);
	DrawLine(0, 0.125);
	DrawLine(0.05, -0.05);
	DrawLine(0, -0.2);
	DrawLine(-0.25, 0);
	MovePen(winwidth - 0.875, winheight - 0.025);
	DrawLine(0.025, 0);
	DrawLine(0, -0.05);
	DrawLine(-0.025, 0);
	DrawLine(0, 0.05);
	MovePen(winwidth - 1.0, winheight - 0.025);
	DrawLine(0.2, 0);

	//���д������˳�ͼ��
	if (pos_in_rect(ms.pos, new_pos(9.4, 6.65), new_pos(9.9, 7))) {
		set_color(activeColor);
		if (ms.left == 2 && pos_in_rect(last_mouse_up_pos(), new_pos(9.4, 6.65), new_pos(9.9, 7))) {
			exit(0);
			reset_mouse_key(1);
		}
	} else {
		set_color(entryColor);
	}
	MovePen(winwidth - 0.2, winheight - 0.225);
	DrawLine(0, -0.05);
	DrawLine(-0.2, 0);
	DrawLine(0, 0.25);
	DrawLine(0.2, 0);
	DrawLine(0, -0.05);
	MovePen(winwidth - 0.15, winheight - 0.2);
	DrawLine(-0.1, 0);
	DrawLine(0, -0.05);
	DrawLine(-0.1, 0.1);
	DrawLine(0.1, 0.1);
	DrawLine(0, -0.05);
	DrawLine(0.1, 0);
	DrawLine(0, -0.1);


	if (pos_in_rect(ms.pos, new_pos(8.3, 6.65), new_pos(8.9, 7))) {
		set_color(activeColor);
		if (ms.left == 2 && pos_in_rect(last_mouse_up_pos(), new_pos(8.3, 6.65), new_pos(8.9, 7))) {
			if (inPause) {
				continue_game();
			} else {
				pause_game();
			}
			reset_mouse_key(1);
		}
	} else {
		set_color(entryColor);
	}
	if (inPause == 0) {
		//���д�������ͣͼ��
		MovePen(winwidth - 1.6, winheight - 0.275);
		DrawLine(0, 0.25);
		DrawLine(0.25, 0);
		DrawLine(0, -0.25);
		DrawLine(-0.25, 0);
		MovePen(winwidth - 1.5375, winheight - 0.0875);
		DrawLine(0.05, 0);
		DrawLine(0, -0.125);
		DrawLine(-0.05, 0);
		DrawLine(0, 0.125);
		MovePen(winwidth - 1.4625, winheight - 0.0875);
		DrawLine(0.05, 0);
		DrawLine(0, -0.125);
		DrawLine(-0.05, 0);
		DrawLine(0, 0.125);
	} else {
		//���д����ǲ���ͼ��
		MovePen(winwidth - 1.6, winheight - 0.275);
		DrawLine(0, 0.25);
		DrawLine(0.25, 0);
		DrawLine(0, -0.25);
		DrawLine(-0.25, 0);
		MovePen(winwidth - 1.5375, winheight - 0.075);
		DrawLine(0, -0.15);
		DrawLine(0.125, 0.075);
		DrawLine(-0.125, 0.075);
	}

	if (pos_in_rect(ms.pos, new_pos(7.6, 6.65), new_pos(8.3, 7))) {
		set_color(activeColor);
		if (ms.left == 2 && pos_in_rect(last_mouse_up_pos(), new_pos(7.6, 6.65), new_pos(8.3, 7))) {
			if (!inPause) pause_game();
			select_saves();
			reset_mouse_key(1);
		}
	} else {
		set_color(entryColor);
	}
	//���д����Ƕ���ͼ��
	MovePen(winwidth - 2.2, winheight - 0.275);
	DrawLine(0, 0.2);
	DrawLine(0.05, 0.05);
	DrawLine(0.15, 0);
	DrawLine(0.05, -0.05);
	DrawLine(0, -0.2);
	DrawLine(-0.25, 0);
	MovePen(winwidth - 2.125, winheight - 0.05);
	DrawLine(0.1, 0);
	DrawLine(0.025, -0.025);
	DrawLine(-0.15, 0);
	DrawLine(0.025, 0.025);
	MovePen(winwidth - 2.15, winheight - 0.175);
	DrawLine(0.05, 0);
	DrawLine(0, -0.05);
	DrawLine(0.05, 0);
	DrawLine(0, 0.05);
	DrawLine(0.05, 0);
	DrawLine(-0.075, 0.05);
	DrawLine(-0.075, -0.05);

	if (pos_in_rect(ms.pos, new_pos(7.05, 6.65), new_pos(7.6, 7))) {
		set_color(activeColor);
		if (ms.left == 2 && pos_in_rect(last_mouse_up_pos(), new_pos(7.05, 6.65), new_pos(7.6, 7))) {
			if (inPause) continue_game();
			reload_game();
			start_game();
			reset_mouse_key(1);
		}
	} else {
		set_color(entryColor);
	}
	//���д������ؿ�ͼ��
	MovePen(winwidth - 2.8, winheight - 0.275);
	DrawLine(0, 0.25);
	DrawLine(0.25, 0);
	DrawLine(0, -0.25);
	DrawLine(-0.25, 0);
	MovePen(winwidth - 2.755, winheight - 0.175);
	DrawLine(0, -0.08);
	DrawLine(0.16, 0);
	DrawLine(0, 0.19);
	DrawLine(-0.14, 0);
	DrawLine(0, 0.025);
	DrawLine(-0.04, -0.05);
	DrawLine(0.04, -0.05);
	DrawLine(0, 0.025);
	DrawLine(0.1, 0);
	DrawLine(0, -0.105);
	DrawLine(-0.08, 0);
	DrawLine(0, 0.0425);
	DrawLine(-0.04, 0);
}

