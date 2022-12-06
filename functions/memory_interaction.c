#pragma once

#include <stdlib.h>
#include <string.h>

#include "../header_files/structs.h"

void increase_buffer_text(text_t* ptr_Text){
    sent_t* temp = realloc(ptr_Text->sent_arr, ptr_Text->len * sizeof(sent_t));

    if (temp){
        ptr_Text->sent_arr = temp;

        create_struct_sent(ptr_Text);

    } else {
        wprintf(L"Не удалось перевыделить память.\nПрекращение выполнения программы.\n");
        //destroy
        exit(0);
    }
}

void increase_buffer_sent(text_t* ptr_Text){
    ptr_Text->sent_arr[ptr_Text->len -1].capacity += INCREASE_BUFFER_SENT;
    wchar_t* temp = realloc(ptr_Text->sent_arr[ptr_Text->len -1].start, ptr_Text->sent_arr[ptr_Text->len -1].capacity * sizeof(wchar_t));

    if (temp){
        ptr_Text->sent_arr[ptr_Text->len -1].start = temp;

    } else{
        wprintf(L"Не удалось перевыделить память.\nПрекращение выполнения программы.\n");
        //destroy
        exit(0);
    }
}

void destroy_sent(text_t* ptr_Text, size_t index){
    free(ptr_Text->sent_arr[index].start);

    memmove(ptr_Text->sent_arr + index, ptr_Text->sent_arr + index + 1, (ptr_Text->len-1 - index) * sizeof(sent_t));

    ptr_Text->sent_arr[ptr_Text->len -1].len = 0;
    ptr_Text->sent_arr[ptr_Text->len -1].capacity = 0;
    ptr_Text->sent_arr[ptr_Text->len -1].amount_of_words = 0;
    ptr_Text->sent_arr[ptr_Text->len -1].start = NULL;

    ptr_Text->len --;
}
