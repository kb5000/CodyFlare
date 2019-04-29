#pragma once
#include "linked_list.h"
#include <stdio.h>

typedef struct {
	char name[32];
} FileName;

///name: generate_file_name
///func: generate a unique name according to the current time
///para: buffer expects a char* which contains at least 32 bytes
///visb: public
void generate_file_name(char* buffer);

///name: start_save
///func: open a file to save
///visb: public
///warn: never forget to end it
FILE* start_save();

///name: start_read
///func: open a file to read
///para: name expects a filename packed by the FileName struct
///visb: public
///warn: never forget to end it
FILE* start_read(FileName name);

///name: end_save_or_read
///func: close a file
///para: file expects the file to close
///visb: public
///warn: use this instead of fclose
void end_save_or_read(FILE* file);

///name: explore_files
///func: return a linked list contains the files match the save_*.sav
///visb: public
ListHandler explore_files();

///name: save_data
///func: save the data to file, return 0 means write failed, 1 means success
///para: file expects a valid file can be written, data expects a block of memory, 
///      size expects the length of the memory
///visb: public
int save_data(FILE* file, const void* data, int size);

///name: get_data
///func: get data from the file, return 0 means the size is too small
///para: file expects a valid file can be read, buffer expects a block of memory, 
///      maxSize expects the length of the buffer
///visb: public
int get_data(FILE* file, void* buffer, int maxSize);


/////name: base64_encode
/////func: encode binary bits to base64
/////para: buffer expects the memory to write, data expects the memory to encode, 
/////      size expects the length of data
/////visb: public
//void base64_encode(void* buffer, const void* data, int size);
//
/////name: base64_decode
/////func: decode base64 to binary bits, return 1 means success, 0 means it's not a valid base64
/////para: buffer expects the memory to write, source expects the memory contains base64, 
/////      size expects the length of source
/////visb: public
//int base64_decode(void* buffer, const void* source, int size);
//
