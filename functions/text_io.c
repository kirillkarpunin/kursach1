#include <stdio.h>
#include <stdlib.h>

#include "../header_files/structs.h"
#include "../header_files/process_text.h"
#include "../header_files/memory_interaction.h"

void get_text(text_t* ptr_Text){
    int stop = 0;
    while (!stop) {

        wchar_t c = 0;

        do {
            c = getwchar();

            if (ptr_Text->sent_arr[ptr_Text->len - 1].len >= ptr_Text->sent_arr[ptr_Text->len -1].capacity - 1) {
                increase_buffer_sent(ptr_Text, ptr_Text->len -1);
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

    if (ptr_Text->len == 0){
        wprintf(L"Получен пустой текст.\nПрекращение выполнения программы.\n");
        destroy_text(ptr_Text);
        exit(0);
    }
    wprintf(L"\nОбработанный текст:\n");
    for (size_t i = 0; i < ptr_Text->len; i++){
        fputws(ptr_Text->sent_arr[i].start, stdout);
    }
    wprintf(L"\n");
}

void spec_print_text(text_t* ptr_Text, size_t i, wchar_t* word_index, size_t word_len){

    add_color_symbols(ptr_Text, i, word_index, word_len);

    fputws(ptr_Text->sent_arr[i].start, stdout);


}
