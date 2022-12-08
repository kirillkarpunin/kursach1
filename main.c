#include <locale.h>

#include "header_files/structs.h"
#include "header_files/text_io.h"
#include "header_files/memory_interaction.h"
#include "header_files/process_text.h"
#include "header_files/menu.h"

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");

    text_t* ptr_Text = create_struct_text();

    wprintf(L"Введите текст:\n");
    get_text(ptr_Text);

    if (ptr_Text->len == 0){
        wprintf(L"Введен пустой текст.\nПрекращение выполнения программы.\n");
        destroy_text(ptr_Text);
        return 0;
    }

    count_words(ptr_Text);
    delete_repetitive_sents(ptr_Text);

    menu(ptr_Text);

    destroy_text(ptr_Text);

    return 0;
}
