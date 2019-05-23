#include "logo_test.h"
#include "graphics.h"
#include "imgui.h"
#include <stdio.h>
#include "input.h"
#include "timer.h"
#include "tortoise.h"
#include "color.h"

#define POC 2

void show_menu(void* u) {
	char * menuListFile[] = { "    文 件",
		"保存 | Ctrl-S",  
		"读取 | Ctrl-L",
		"返回主界面 | Ctrl-B",
		"退出 | Ctrl-E"};
	char * menuListGame[] = { "    游 戏",
		"开始新游戏 | Ctrl-R",
		"暂停 | Ctrl-P",
		"切换游戏模式 | Ctrl-O",
		"排行榜 | Ctrl-C"};
	char * menuListCheat[] = { "  金 手 指",
		"无限弹药 | Ctrl-M",
		"无限血量 | Ctrl-F",
		"加速 | Ctrl-A",
		"减速 | Ctrl-D"};
	char * menuListAbout[] = { "    关 于",
		"帮助 | Ctrl-H",
		"开发团队 | Ctrl-T" };
	char * selectedLabel = NULL;
	double winwidth = GetWindowWidth();
	double winheight = GetWindowHeight();
	//setMenuColors(char *frame, char*label, char *hotFrame, char *hotLabel, int fillflag);
	int    selection;
	selection=menuList(1, 0, winheight-0.25, 0.85,2, 0.25, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection > 0) selectedLabel = menuListFile[selection];
	selection=menuList(2, 0.85, winheight - 0.25, 0.85, 2, 0.25, menuListGame, sizeof(menuListGame) / sizeof(menuListGame[0]));
	if (selection > 0) selectedLabel = menuListGame[selection];
	selection = menuList(3, 1.7, winheight - 0.25, 0.85, 2, 0.25, menuListCheat, sizeof(menuListCheat) / sizeof(menuListCheat[0]));
	if (selection > 0) selectedLabel = menuListCheat[selection];
	selection = menuList(4, 2.55, winheight - 0.25, 0.85, 2, 0.25, menuListAbout, sizeof(menuListAbout) / sizeof(menuListAbout[0]));
	if (selection > 0) selectedLabel = menuListAbout[selection];

	
	//上面的代码没有颜色，下面所有图标0.25*0.25大小，图标左下顶点间距离为0.6
	
	//下列代码是存档图标
	MovePen(winwidth-1.2,winheight-0.3);
	DrawLine(0, 0.25);
	DrawLine(0.05, 0);
	DrawLine(0, -0.125);
	DrawLine(0.15, 0);
	DrawLine(0, 0.125);
	DrawLine(0.05, -0.05);
	DrawLine(0, -0.2);
	DrawLine(-0.25, 0);
	MovePen(winwidth - 1.075, winheight - 0.05);
	DrawLine(0.025, 0);
	DrawLine(0, -0.05);
	DrawLine(-0.025, 0);
	DrawLine(0, 0.05);
	MovePen(winwidth - 1.2, winheight - 0.05);
	DrawLine(0.2, 0);

	//下列代码是退出图标
	MovePen(winwidth - 0.4, winheight - 0.25);
	DrawLine(0, -0.05);
	DrawLine(-0.2, 0);
	DrawLine(0, 0.25);
	DrawLine(0.2, 0);
	DrawLine(0, -0.05);
	MovePen(winwidth - 0.35, winheight - 0.225);
	DrawLine(-0.1, 0);
	DrawLine(0, -0.05);
	DrawLine(-0.1, 0.1);
	DrawLine(0.1, 0.1);
	DrawLine(0, -0.05);
	DrawLine(0.1, 0);
	DrawLine(0, -0.1);

	//下列代码是暂停图标
	if (POC==1){
		MovePen(winwidth - 1.8, winheight - 0.3);
		DrawLine(0, 0.25);
		DrawLine(0.25, 0);
		DrawLine(0, -0.25);
		DrawLine(-0.25, 0);
		MovePen(winwidth - 1.7375, winheight - 0.1125);
		DrawLine(0.05, 0);
		DrawLine(0, -0.125);
		DrawLine(-0.05, 0);
		DrawLine(0, 0.125);
		MovePen(winwidth - 1.6625, winheight - 0.1125);
		DrawLine(0.05, 0);
		DrawLine(0, -0.125);
		DrawLine(-0.05, 0);
		DrawLine(0, 0.125);
	}

	//下列代码是播放图标
	else if (POC==2) {
		MovePen(winwidth - 1.8, winheight - 0.3);
		DrawLine(0, 0.25);
		DrawLine(0.25, 0);
		DrawLine(0, -0.25);
		DrawLine(-0.25, 0);
		MovePen(winwidth - 1.7375, winheight - 0.1);
		DrawLine(0, -0.15);
		DrawLine(0.125,0.075);
		DrawLine(-0.125, 0.075);
	}

	//下列代码是金手指图标

	//下列代码是加速图标

	//下列代码是读档图标

	//下列代码是重开图标

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
