#include <stdlib.h>

#include "../header_files/structs.h"

void increase_buffer_text(text_t* ptr_Text){
    sent_t* temp = realloc(ptr_Text->sent_arr, ptr_Text->len * sizeof(sent_t));

    if (temp){
        ptr_Text->sent_arr = temp;

        create_struct_sent(ptr_Text);

    } else {
        wprintf(L"Не удалось перевыделить память\n");
        //destroy
        exit(0);
    }
}

void increase_buffer_sent(text_t* ptr_Text){
    ptr_Text->sent_arr[ptr_Text->len -1].capacity += ptr_Text->increase_buffer_sent;
    wchar_t* temp = realloc(ptr_Text->sent_arr[ptr_Text->len -1].start, ptr_Text->sent_arr[ptr_Text->len -1].capacity * sizeof(wchar_t));

    if (temp){
        ptr_Text->sent_arr[ptr_Text->len -1].start = temp;

    } else{
        wprintf(L"Не удалось перевыделить память\n");
        //destroy
        exit(0);
    }
}

void destroy_sent(text_t* ptr_Text){
    free(ptr_Text->sent_arr[ptr_Text->len - 1].start);
    free(ptr_Text->sent_arr+(ptr_Text->len - 1));
    ptr_Text->sent_arr+(ptr_Text->len - 1) = NULL;

    ptr_Text->len --;
}
