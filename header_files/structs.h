#pragma once

#include <wchar.h>

struct Sentence{
    unsigned long len;
    unsigned long capacity;
    wchar_t* start;
};
typedef struct Sentence sent_t;

struct Text{
    unsigned long len;
    int increase_buffer_sent;
    sent_t* sent_arr;
};
typedef struct Text text_t;

text_t* create_struct_text();

void create_struct_sent(text_t* ptr_Text);