#pragma once

#include <wchar.h>

struct Sentence{
    size_t len;
    size_t capacity;
    size_t amount_of_words;
    wchar_t* start;
};
typedef struct Sentence sent_t;

struct Text{
    size_t len;
    sent_t* sent_arr;
};
typedef struct Text text_t;

text_t* create_struct_text();

void create_struct_sent(text_t* ptr_Text);