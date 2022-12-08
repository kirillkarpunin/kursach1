#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../header_files/structs.h"

void destroy_sent(text_t* ptr_Text, size_t index){
    free(ptr_Text->sent_arr[index].start);

    memmove(ptr_Text->sent_arr + index, ptr_Text->sent_arr + index + 1, (ptr_Text->len-1 - index) * sizeof(sent_t));

    ptr_Text->sent_arr[ptr_Text->len -1].len = 0;
    ptr_Text->sent_arr[ptr_Text->len -1].capacity = 0;
    ptr_Text->sent_arr[ptr_Text->len -1].amount_of_words = 0;
    ptr_Text->sent_arr[ptr_Text->len -1].start = NULL;

    ptr_Text->len --;
}

void destroy_text(text_t* ptr_Text){
    for (int i = 0; i < ptr_Text->len;){
        destroy_sent(ptr_Text, i);
    }
    free(ptr_Text);
}

void increase_buffer_sent(text_t* ptr_Text, size_t index){
    ptr_Text->sent_arr[index].capacity += INCREASE_BUFFER_SENT;
    if (ptr_Text->sent_arr[index].capacity > SIZE_MAX){
        wprintf(L"Достигнута максимальная длина предложения.\nПрекращение выполнения программы.\n");
        destroy_text(ptr_Text);
        exit(0);
    }
    wchar_t* temp = realloc(ptr_Text->sent_arr[index].start, ptr_Text->sent_arr[index].capacity * sizeof(wchar_t));

    if (temp){
        ptr_Text->sent_arr[index].start = temp;
        temp = NULL;

    } else{
        wprintf(L"Не удалось перевыделить память.\nПрекращение выполнения программы.\n");
        destroy_text(ptr_Text);
        exit(0);
    }
}

void increase_buffer_text(text_t* ptr_Text){
    if (ptr_Text->len > SIZE_MAX){
        wprintf(L"Достигнута максимальная длина текста.\nПрекращение выполнения программы.\n");
        destroy_text(ptr_Text);
        exit(0);
    }
    sent_t* temp = realloc(ptr_Text->sent_arr, ptr_Text->len * sizeof(sent_t));

    if (temp){
        ptr_Text->sent_arr = temp;
        temp = NULL;

        create_struct_sent(ptr_Text);

    } else {
        wprintf(L"Не удалось перевыделить память.\nПрекращение выполнения программы.\n");
        destroy_text(ptr_Text);
        exit(0);
    }
}
