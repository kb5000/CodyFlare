#include "help_page.h"
#include "sheet.h"
#include "timer.h"
#include "input.h"
#include "imgui.h"
#include "rank.h"
#include "listbox.h"

static int page = 0;
static int pageCoolDown = 0;
static Vector helpInfo[6], aboutInfo;
static int helpValid, aboutValid;

static char helpStrs[6][30][2][80] = {
	{
		{"按键控制"},
		{"按键", "动作"},
		{"方向键上下左右", "控制战机上下左右移动"},
		{"空格（Space）键", "发射导弹"},
		{"F键（可长按）", "发射炸弹（ 根据按键时长决定发射距离）"},
		{"S键", "冲刺"},
		{"A键", "读取存档（暂停界面中）"},
		{"D键", "删除存档（暂停界面中）"},
		{"Ctrl组合键", "功能请参考菜单栏"},
	},
	{
		{"弹药介绍"},
		{"普通子弹："},
		{"无需玩家控制自动向机体上方射击，没有弹药数量限制。""伤害较低，但弹速较快。"},
		{"追踪导弹："},
		{"按空格键发射后智能选择敌人射击，没有弹药数量限制。"},
		{"但每次发射后有数秒的冷却（在玩家战机下方有冷却显示），""伤害较高。"},
		{"定时炸弹："},
		{"长按F键向玩家机体上方发射，按键时间越长发射距离越远，"},
		{"松开F键后经过数秒短暂的延迟后爆炸，"},
		{"在一定范围内对敌人和玩家均可造成大量伤害"},
		{"伤害会随与爆炸中心距离的增加逐渐递减，"},
		{"同时对玩家有一定的伤害减弱机制，"},
		{"有弹药数量限制，初始数量为五枚，可以在游戏中获取更多。"},
	},
	{
		{"敌机介绍"},
		{"普通敌机："},
		{"沿直线轨迹向下行进并向下方直线发射普通弹药（比玩家的射速慢）"},
		{"在与玩家接近时会加速向下冲刺。"},
		{"精英敌机："},
		{"可自由左右移动地向下方行进，并根据玩家位置智能选择发射导弹或普通弹药，"},
		{"导弹若一定时间内未击中玩家会自爆（自爆不会造成伤害）。"},
		{"同时在与玩家相距较远时会智能躲避玩家，"},
		{"而距玩家较近时会主动靠近玩家造成伤害。"},
		{"奖励敌机："},
		{"该类型敌机不会造成伤害且血量较少，"},
		{"与精英敌机类似会自由左右移动并向下方行进（移速较快），并会智能躲避玩家。"},
		{"击落奖励敌机后会掉落血量包（回复少量血量）或炸弹包（获得定时炸弹弹药）。"},
		{"但要注意一旦玩家距离奖励敌机过近会使其自爆，"},
		{"爆炸与定时炸弹类似在短暂延迟后对玩家和敌人造成大量伤害。"},
		{"BOSS敌机："},
		{"在剧情模式中的最终BOSS，机型庞大生命值极高。"},
		{"以360度无死角发射弹幕极密的普通子弹，并可发射追踪导弹群，但射程较短。"},
		{"还会放出炸弹对玩家造成伤害。"},
		{"由于机身过重灵活性不佳，BOSS敌机在游戏中不会闪避玩家的攻击，"},
		{"但庞大的机群会为其提供有效的掩护。"},
	},
	{
		{"作弊功能介绍"},
		{"更多炸弹", "玩家携带炸弹数量增加100枚"},
		{"更多血量", "玩家血量增加2000点"},
		{"加速", "加快游戏进行速度"},
		{"减速", "减慢游戏进行速度"},
	},
	{
		{"UI介绍"},
		{"菜单栏："},
		{"位于页面左上角，详细功能请在游戏内查看。"},
		{"快捷功能栏："},
		{"位于页面右上角，从左向右依次为："},
		{"重新开始新游戏，读取存档，切换暂停/继续，保存，退出游戏。"},
		{"状态栏："},
		{"位于页面正下方，从左到右依次为："},
		{"玩家血量、剩余炸弹个数、当前分数、击落敌机数以及当前游戏模式。"},
		{"其他："},
		{"在BOSS关卡中，BOSS敌机的血量会在屏幕正上方显示"},
		{"玩家冲刺与导弹冷却条位于玩家战机下方"},
		{"保存成功后屏幕上方会出现成功提示"},
		{"菜单栏部分功能--排行榜将出现在屏幕右下方，读档列表将出现在屏幕左下方"},
	},
	{
		{"模式介绍"},
		{"剧情模式："},
		{"玩家在敌机战斗群中存活直至BOSS出现，击败BOSS后胜利。"},
		{"玩家生命值归零视为失败，但仍会统计最终得分计入排行榜。"},
		{"生存模式："},
		{"玩家将尝试在敌机战斗群中尽可能存活更久，获取更高分数，"},
		{"敌机出现频率将随游戏时间则增加而提高，难度也将越来越大。"},
		{"在本模式中BOSS敌机不会出现。玩家生命值归零后游戏结束，"},
		{"届时将统计最终得分计入排行榜。"},
	},
};
static char aboutStrs[6][80] = {
	"关于",
	"TO THE SPACE, 由 /点一下/玩一年/ 小组开发",
	"成员：马梓睿，白凤杨，李保宏",
	"Powered by CodyFlare，基于libgraphics构建的强大游戏引擎",
	"私货：由Rust语言重写的CodyFlareR已开始开发",
	"欢迎有兴趣者到GitHub: kb5000上提建议"
};

static void move_page() {
	if (pageCoolDown < 5) return;
	DirKeys dk = get_dir_key();
	if (dk.right == 0) {
		pageCoolDown = 0;
		page = (page + 1) % 6;
	} else if (dk.left == 0) {
		pageCoolDown = 0;
		page = (page + 5) % 6; //cant be page - 1, guess why
	}
}

static void show_help_page(void* unuseful) {
	if (!helpValid) disable_me_in_timer();
	int row = 1, col = 1;
	switch (page) {
	case 0:
		row = 9;
		col = 2;
		break;
	case 1:
		row = 15;
		col = 1;
		break;
	case 2:
		row = 21;
		col = 1;
		break;
	case 3:
		row = 5;
		col = 2;
		break;
	case 4:
		row = 14;
		col = 1;
		break;
	case 5:
		row = 9;
		col = 1;
		break;
	default:
		break;
	}
	show_sheet(&helpInfo[page], new_pos(4, 1.2), new_pos(6, 5), row, col, 1, 0, 0.3, color_by_name("DarkGrey"), color_by_name("Black"),
			   color_by_rgb(216, 192, 180), "Default", 16, "宋体", 16, 'L');
	set_color(color_by_rgb(216, 192, 180));
	drawBoxFree(4, 0.98, 3, 0.22, 1, "按左右键查看更多信息", 'L', color_by_name("Black"), 1);
	drawRectangle(4, 0.98, 3, 0.22, 0);
	move_page();
	pageCoolDown++;
}

static void show_about_page(void* unuseful) {
	if (!aboutValid) disable_me_in_timer();
	show_sheet(&aboutInfo, new_pos(1, 1.2), new_pos(5, 3),  6, 1, 1, 0, 0.3, color_by_name("DarkGrey"), color_by_name("Black"),
			   color_by_rgb(216, 192, 180), "Default", 16, "宋体", 16, 'L');
}

void init_help() {
	for (int i = 0; i < 6; i++) {
		helpInfo[i] = gen_empty_vector(Vector);
		for (int j = 0; j < 30; j++) {
			Vector vec = gen_empty_vector(char[80]);
			for (int k = 0; k < 2; k++) {
				calls(vec, push, helpStrs[i][j][k]);
			}
			calls(helpInfo[i], push, &vec);
		}
	}
	aboutInfo = gen_empty_vector(Vector);
	for (int i = 0; i < 6; i++) {
		Vector vec = gen_empty_vector(char[80]);
		calls(vec, push, aboutStrs[i]);
		calls(aboutInfo, push, &vec);
	}
}

void show_help() {
	close_about();
	close_help();
	close_list_box(0, NULL, 0);
	remove_funcs_from_timer(998800);
	remove_rank();
	helpValid = 1;
	add_func_to_timer(show_help_page, NULL, 1, 8322365, -1);
}

void show_about() {
	close_about();
	close_help();
	close_list_box(0, NULL, 0);
	remove_funcs_from_timer(998800);
	remove_rank();
	aboutValid = 1;
	add_func_to_timer(show_about_page, NULL, 1, 8322366, -1);
}

void close_help() {
	helpValid = 0;
}

void close_about() {
	aboutValid = 0;
}