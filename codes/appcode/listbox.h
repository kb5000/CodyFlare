#pragma once

#include "linked_list.h"
#include "utility.h"

void show_list_box(int id, ListHandler list, Pos position, int currentItem);

int get_current_list_index();

int is_box_open();

void close_list_box(int key, void * unuseful, int event);

void del_save_file(int key, ListHandler* lbh, int event);

int is_del_file();

