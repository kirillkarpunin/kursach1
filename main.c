#include <locale.h>
#include <stdio.h>

#include "header_files/structs.h"
#include "header_files/text_io.h"
#include "header_files/memory_interaction.h"
#include "process_text.h"

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");

    text_t* ptr_Text = create_struct_text();

    wprintf(L"Введите текст:\n");
    get_text(ptr_Text);

    if (ptr_Text->len == 0){
        wprintf(L"Введен пустой текст.\nПрекращение выполнения программы.\n");
        return 0;
    }

    count_words(ptr_Text);
    delete_repetitive_sents(ptr_Text);

    for (int i = 0; i < ptr_Text->len; i++){
        fputws(ptr_Text->sent_arr[i].start, stdout);
//        wprintf(L"%lu", ptr_Text->sent_arr[i].amount_of_words);
    }

    return 0;
}
