#include <stdio.h>
#include <time.h>
#include "save.h"
#include <stdint.h>
#include <io.h>
#include <string.h>
#include <stdlib.h>

void generate_file_name(char* buffer) {
	char* timeBuffer = (char*)malloc(20);
	time_t timeNow = time(NULL);
	struct tm* tmt = localtime(&timeNow);
	strftime(timeBuffer, 20, "%m%d_%H%M%S", tmt);
	sprintf(buffer, "save_%s.sav", timeBuffer);
	free(timeBuffer);
}

FILE* start_save() {
	char fileName[32];
	generate_file_name(fileName);
	FILE* file = fopen(fileName, "wb");
	return file;
}

FILE* start_read(FileName name) {
	FILE* file = fopen(name.name, "rb");
	return file;
}

void end_save_or_read(FILE* file) {
	fclose(file);
}

ListHandler explore_files() {
	ListHandler lh = new_empty_list();
	struct _finddata_t fileInfo;
	int fileHandle = _findfirst("save_*.sav", &fileInfo);
	do {
		FileName* fileName = (FileName*)malloc(sizeof(FileName));
		strcpy(fileName->name, fileInfo.name);
		lh.push_back(&lh, (void*)fileName);
	} while (_findnext(fileHandle, &fileInfo) == 0);
	return lh;
}

int save_data(FILE* file, void* data, int size) {
	int8_t* readPtr = (int8_t*)data;
	int chr;
	for (int i = 0; i < size; i++) {
		chr = putc(readPtr[i], file);
		if (chr == EOF) break;
	}
	if (ferror(file)) return 0;
	return 1;
}

int get_data(FILE* file, void* buffer, int maxSize) {
	int8_t* writePtr = (int8_t*)buffer;
	int chr;
	for (int i = 0; i < maxSize; i++) {
		chr = getc(file);
		if (chr == EOF) break;
		writePtr[i] = chr;
	}
	if (chr != EOF) return 0;
	return 1;
}

void base64_encode(void* buffer, const void* data, int size) {
	int length = 0;
	const int8_t* buf = data;
	int8_t* writebuf = buffer;
	while (length - size >= 3) {
		int8_t bases[4];
		bases[0] = (*buf & 0xFFFFFF00 >> 8);
		bases[1] = ((*buf & 0x000000FF) << 16) | ((*(buf + 1) & 0xFFFF0000) >> 16);
		bases[2] = ((*(buf + 1)) & 0x0000FFFF << 8) | ((*(buf + 2)) & 0xFF000000 >> 24);
		bases[3] = (*(buf + 2) & 0x00FFFFFF);
		for (int i = 0; i < 4; i++) {
			int8_t chr = bases[i];
			if (chr < 26) chr += 'A';
			else if (chr < 52) chr += 'a' - 26;
			else if (chr < 62) chr += '0' - 52;
			else if (chr == 62) chr = '+';
			else if (chr == 63) chr = '/';
			else chr = '#';
			writebuf[i] = chr;
		}
		buf += 3;
		writebuf += 4;
		length += 3;
	}
	//int8_t source[3], bases[4];
	
}

int base64_decode(void* buffer, const void* source, int size) {
	return 0;
}
