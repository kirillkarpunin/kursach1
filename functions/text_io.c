#include <stdio.h>

#include "../header_files/structs.h"
#include "../header_files/memory_interaction.h"

int get_text(text_t* ptr_Text){
    int err = 0;
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
                err = increase_buffer_sent(ptr_Text, ptr_Text->len -1);
                if (err){
                    return err;
                }
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
            err = increase_buffer_text(ptr_Text);
            if (err){
                return err;
            }
        }
    }
    return 0;
}

int print_text(text_t* ptr_Text){

    if (ptr_Text->len == 0){
        return 1;
    }
    wprintf(L"\nОбработанный текст:\n");
    for (size_t i = 0; i < ptr_Text->len; i++){
        fputws(ptr_Text->sent_arr[i].start, stdout);
    }
    wprintf(L"\n");
    return 0;
}

void spec_print_text(sent_t sent){

    fputws(sent.start, stdout);

}

void err_print(int code){
    switch (code) {
        case 0:
            wprintf(L"Введен пустой текст.\nПрекращение выполнения программы.\n");
        case 1:
            wprintf(L"\nПолучен пустой текст.\nПрекращение выполнения программы.\n");
        case 2:
            wprintf(L"\nНе удалось перевыделить память.\nПрекращение выполнения программы.\n");
        case 3:
            wprintf(L"\nДостигнута максимальная длина предложения.\nПрекращение выполнения программы.\n");
        case 4:
            wprintf(L"\nДостигнута максимальная длина текста.\nПрекращение выполнения программы.\n");
    }
}
