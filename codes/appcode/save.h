#pragma once
#include "linked_list.h"
#include <stdio.h>

typedef struct {
	char name[32];
} FileName;

void generate_file_name(char* buffer);

FILE* start_save();

FILE* start_read(FileName name);

void end_save_or_read(FILE* file);

ListHandler explore_files();

int save_data(FILE* file, const void* data, int size);

int get_data(FILE* file, void* buffer, int maxSize);

void base64_encode(void* buffer, const void* data, int size);

int base64_decode(void* buffer, const void* source, int size);

