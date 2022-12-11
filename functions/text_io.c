#include <stdio.h>
#include <stdlib.h>

#include "../header_files/structs.h"
#include "../header_files/memory_interaction.h"

void get_text(text_t* ptr_Text){
    wprintf(L"-----------------------------------------------------------------------"
            "\nФормат ввода текста:"
            "\n\tОдиночный символ точки - разделитель предложений"
            "\n\tЗапятая и пробельные символы - разделители слов"
            "\n\tДвойной символ переноса строки - конец ввода"
            "\n-----------------------------------------------------------------------\n");
    wprintf(L"Введите текст:\n");
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

                    *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = L'.';
                    ptr_Text->sent_arr[ptr_Text->len - 1].len ++;
                    *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = L'\0';
                    ptr_Text->sent_arr[ptr_Text->len - 1].len ++;

                    break;
                } else {
                    *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = temp_c;
                    ptr_Text->sent_arr[ptr_Text->len - 1].len ++;
                }
            }

            *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = c;
            ptr_Text->sent_arr[ptr_Text->len - 1].len ++;

        } while (c != L'.');

        if (*(ptr_Text->sent_arr[ptr_Text->len - 1].start) == L'.') {
            destroy_sent(ptr_Text, ptr_Text->len - 1);
        }

        if (!stop) {
            if (ptr_Text->len != 0 && ptr_Text->sent_arr[ptr_Text->len-1].start != NULL){
                *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = L'\0';
            }

            ptr_Text->len ++;
            increase_buffer_text(ptr_Text);
        }
    }
}

void print_text(text_t* ptr_Text){

    if (ptr_Text->len == 0){
        wprintf(L"\nПолучен пустой текст.\nПрекращение выполнения программы.\n");
        destroy_text(ptr_Text);
        exit(0);
    }
    wprintf(L"\nОбработанный текст:\n");
    for (size_t i = 0; i < ptr_Text->len; i++){
        fputws(ptr_Text->sent_arr[i].start, stdout);
    }
    wprintf(L"\n");
}

void spec_print_text(sent_t sent){

    fputws(sent.start, stdout);

}
