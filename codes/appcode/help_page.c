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
		{"��������"},
		{"����", "����"},
		{"�������������", "����ս�����������ƶ�"},
		{"�ո�Space����", "���䵼��"},
		{"F�����ɳ�����", "����ը�����ݰ���ʱ������������룩"},
		{"S��", "���"},
		{"A��", "��ȡ�浵����ͣ�����У�"},
		{"D��", "ɾ���浵����ͣ�����У�"},
		{"Ctrl��ϼ�", "������ο��˵���"},
	},
	{
		{"��ҩ����"},
		{"��ͨ�ӵ���"},
		{"������ҿ����Զ�������Ϸ������û�е�ҩ�������ơ�""�˺��ϵͣ������ٽϿ졣"},
		{"׷�ٵ�����"},
		{"���ո�����������ѡ����������û�е�ҩ�������ơ�"},
		{"��ÿ�η�������������ȴ�������ս���·�����ȴ��ʾ����""�˺��ϸߡ�"},
		{"��ʱը����"},
		{"����F������һ����Ϸ����䣬����ʱ��Խ���������ԽԶ��"},
		{"�ɿ�F���󾭹�������ݵ��ӳٺ�ը��"},
		{"��һ����Χ�ڶԵ��˺���Ҿ�����ɴ����˺�"},
		{"�˺������뱬ը���ľ���������𽥵ݼ���"},
		{"ͬʱ�������һ�����˺��������ƣ�"},
		{"�е�ҩ�������ƣ���ʼ����Ϊ��ö����������Ϸ�л�ȡ���ࡣ"},
	},
	{
		{"�л�����"},
		{"��ͨ�л���"},
		{"��ֱ�߹켣�����н������·�ֱ�߷�����ͨ��ҩ������ҵ���������"},
		{"������ҽӽ�ʱ��������³�̡�"},
		{"��Ӣ�л���"},
		{"�����������ƶ������·��н������������λ������ѡ���䵼������ͨ��ҩ��"},
		{"������һ��ʱ����δ������һ��Ա����Ա���������˺�����"},
		{"ͬʱ�����������Զʱ�����ܶ����ң�"},
		{"������ҽϽ�ʱ�����������������˺���"},
		{"�����л���"},
		{"�����͵л���������˺���Ѫ�����٣�"},
		{"�뾫Ӣ�л����ƻ����������ƶ������·��н������ٽϿ죩���������ܶ����ҡ�"},
		{"���佱���л�������Ѫ�������ظ�����Ѫ������ը��������ö�ʱը����ҩ����"},
		{"��Ҫע��һ����Ҿ��뽱���л�������ʹ���Ա���"},
		{"��ը�붨ʱը�������ڶ����ӳٺ����Һ͵�����ɴ����˺���"},
		{"BOSS�л���"},
		{"�ھ���ģʽ�е�����BOSS�������Ӵ�����ֵ���ߡ�"},
		{"��360�������Ƿ��䵯Ļ���ܵ���ͨ�ӵ������ɷ���׷�ٵ���Ⱥ������̽϶̡�"},
		{"����ų�ը�����������˺���"},
		{"���ڻ����������Բ��ѣ�BOSS�л�����Ϸ�в���������ҵĹ�����"},
		{"���Ӵ�Ļ�Ⱥ��Ϊ���ṩ��Ч���ڻ���"},
	},
	{
		{"���׹��ܽ���"},
		{"����ը��", "���Я��ը����������100ö"},
		{"����Ѫ��", "���Ѫ������2000��"},
		{"����", "�ӿ���Ϸ�����ٶ�"},
		{"����", "������Ϸ�����ٶ�"},
	},
	{
		{"UI����"},
		{"�˵�����"},
		{"λ��ҳ�����Ͻǣ���ϸ����������Ϸ�ڲ鿴��"},
		{"��ݹ�������"},
		{"λ��ҳ�����Ͻǣ�������������Ϊ��"},
		{"���¿�ʼ����Ϸ����ȡ�浵���л���ͣ/���������棬�˳���Ϸ��"},
		{"״̬����"},
		{"λ��ҳ�����·�������������Ϊ��"},
		{"���Ѫ����ʣ��ը����������ǰ����������л����Լ���ǰ��Ϸģʽ��"},
		{"������"},
		{"��BOSS�ؿ��У�BOSS�л���Ѫ��������Ļ���Ϸ���ʾ"},
		{"��ҳ���뵼����ȴ��λ�����ս���·�"},
		{"����ɹ�����Ļ�Ϸ�����ֳɹ���ʾ"},
		{"�˵������ֹ���--���а񽫳�������Ļ���·��������б���������Ļ���·�"},
	},
	{
		{"ģʽ����"},
		{"����ģʽ��"},
		{"����ڵл�ս��Ⱥ�д��ֱ��BOSS���֣�����BOSS��ʤ����"},
		{"�������ֵ������Ϊʧ�ܣ����Ի�ͳ�����յ÷ּ������а�"},
		{"����ģʽ��"},
		{"��ҽ������ڵл�ս��Ⱥ�о����ܴ����ã���ȡ���߷�����"},
		{"�л�����Ƶ�ʽ�����Ϸʱ�������Ӷ���ߣ��Ѷ�Ҳ��Խ��Խ��"},
		{"�ڱ�ģʽ��BOSS�л�������֡��������ֵ�������Ϸ������"},
		{"��ʱ��ͳ�����յ÷ּ������а�"},
	},
};
static char aboutStrs[6][80] = {
	"����",
	"TO THE SPACE, �� /��һ��/��һ��/ С�鿪��",
	"��Ա��������׷�����",
	"Powered by CodyFlare������libgraphics������ǿ����Ϸ����",
	"˽������Rust������д��CodyFlareR�ѿ�ʼ����",
	"��ӭ����Ȥ�ߵ�GitHub: kb5000���Ὠ��"
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
			   color_by_rgb(216, 192, 180), "Default", 16, "Default", 16, 'L');
	set_color(color_by_rgb(216, 192, 180));
	drawBoxFree(4, 0.98, 3, 0.22, 1, "�����Ҽ��鿴������Ϣ", 'L', color_by_name("Black"), 1);
	drawRectangle(4, 0.98, 3, 0.22, 0);
	move_page();
	pageCoolDown++;
}

static void show_about_page(void* unuseful) {
	if (!aboutValid) disable_me_in_timer();
	show_sheet(&aboutInfo, new_pos(1, 1.2), new_pos(5, 3),  6, 1, 1, 0, 0.3, color_by_name("DarkGrey"), color_by_name("Black"),
			   color_by_rgb(216, 192, 180), "Default", 16, "Default", 16, 'L');
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