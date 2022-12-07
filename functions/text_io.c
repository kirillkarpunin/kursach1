#include <stdio.h>

#include "../header_files/structs.h"
#include "../header_files/memory_interaction.h"

void get_text(text_t* ptr_Text){
    int stop = 0;
    while (!stop) {

        wchar_t c = 0;

        do {
            c = getwchar();

            if (ptr_Text->sent_arr[ptr_Text->len - 1].len >= ptr_Text->sent_arr[ptr_Text->len -1].capacity - 1) {
                increase_buffer_sent(ptr_Text);
            }

            if (c == L'\n'){
                wchar_t temp_c = c;
                c = getwchar();
                if (c == L'\n'){
                    stop = 1;

                    if (ptr_Text->sent_arr[ptr_Text->len - 1].len == 0){
                        destroy_sent(ptr_Text, ptr_Text->len - 1);
                    } else {
                        *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = L'.';
                        ptr_Text->sent_arr[ptr_Text->len - 1].len ++;
                        *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = L'\0';
                        ptr_Text->sent_arr[ptr_Text->len - 1].len ++;
                    }

                    break;
                } else {
                    *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = temp_c;
                    ptr_Text->sent_arr[ptr_Text->len - 1].len ++;
                }
            }

            *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = c;
            ptr_Text->sent_arr[ptr_Text->len - 1].len ++;

        } while (c != L'.');

        if (!stop) {
            *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = L'\0';

            ptr_Text->len ++;
            increase_buffer_text(ptr_Text);
        }
    }
}

void print_text(text_t* ptr_Text){
    wprintf(L"Обработанный текст:\n");
    for (int i = 0; i < ptr_Text->len; i++){
        fputws(ptr_Text->sent_arr[i].start, stdout);
    }
    wprintf(L"\n");
}
