#ifndef file_reader_h
#define file_reader_h

#include <stdio.h>
#include <stdlib.h>


typedef struct string{
    char* data;
    int size;
} string;

string reader(char* path);

#endif
