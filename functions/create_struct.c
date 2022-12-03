#include <stdlib.h>

#include "../header_files/structs.h"

text_t* create_struct_text() {
    text_t* ptr_Text = malloc(sizeof(text_t));
    *ptr_Text = (text_t){1, 10, malloc(ptr_Text->len * sizeof(sent_t))};

    create_struct_sent(ptr_Text);

    return ptr_Text;
}

void create_struct_sent(text_t* ptr_Text){

    ptr_Text->sent_arr[ptr_Text->len -1].len = 0;
    ptr_Text->sent_arr[ptr_Text->len -1].start = malloc(ptr_Text->max_sent_len * sizeof(wchar_t));
}