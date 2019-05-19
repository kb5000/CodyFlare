#include "logo_test.h"
#include "graphics.h"
#include "imgui.h"
#include <stdio.h>
#include "input.h"
#include "timer.h"

void show_menu(void* u) {
	MovePen(0.2, 6.9);
	DrawLine(1, 0);
	
	char * menuListFile[] = { "    文 件",
		"保存",  
		"读取",
		"返回主界面",
		"返回桌面"};
	char * menuListGame[] = { "    游 戏",
		"开始新游戏",
		"加速",
		"减速",
		"暂停",
		"排行榜"};
	char * menuListCheat[] = { "  金 手 指",
		"无敌模式",
		"无限弹药",
		"回满血量",
		"清屏"};
	char * menuListAbout[] = { "    关 于",
		"帮助",
		"鸣谢" };
	char * selectedLabel = NULL;
	double winwidth = GetWindowWidth();
	double winheight = GetWindowHeight();
	//setMenuColors(char *frame, char*label, char *hotFrame, char *hotLabel, int fillflag);
	setMenuColors("LightGrey", "Blue", "DarkGrey", "Red", 1);
	int    selection;
	selection=menuList(1, 0, winheight-0.25, 0.85,1, 0.25, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if (selection > 0) selectedLabel = menuListFile[selection];
	selection=menuList(2, 0.85, winheight - 0.25, 0.85, 1, 0.25, menuListGame, sizeof(menuListGame) / sizeof(menuListGame[0]));
	if (selection > 0) selectedLabel = menuListGame[selection];
	selection = menuList(3, 1.7, winheight - 0.25, 0.85, 1, 0.25, menuListCheat, sizeof(menuListCheat) / sizeof(menuListCheat[0]));
	if (selection > 0) selectedLabel = menuListCheat[selection];
	selection = menuList(4, 2.55, winheight - 0.25, 0.85, 1, 0.25, menuListAbout, sizeof(menuListAbout) / sizeof(menuListAbout[0]));
	if (selection > 0) selectedLabel = menuListAbout[selection];
}

void test_of_logo()
{
	InitGraphics();
	InitGUI();
	init_input();
	init_global_timer();
	start_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);

	add_func_to_timer(show_menu, NULL, 1, 123, -1);
}
