#include <locale.h>

#include "header_files/structs.h"
#include "header_files/text_io.h"
#include "header_files/memory_interaction.h"
#include "header_files/preprocess_text.h"
#include "header_files/menu.h"

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");

    text_t* ptr_Text = create_struct_text();

    get_text(ptr_Text);

    if (ptr_Text->len == 0){
        wprintf(L"Введен пустой текст.\nПрекращение выполнения программы.\n");
        destroy_text(ptr_Text);
        return 0;
    }

    count_words(ptr_Text);
    delete_repetitive_sents(ptr_Text);

    int err = menu(ptr_Text);
    if (err){
        switch (err) {
            case 1:
                wprintf(L"\nПолучен пустой текст.\nПрекращение выполнения программы.\n");
                destroy_text(ptr_Text);
                return 0;
            case 2:
                wprintf(L"\nНе удалось перевыделить память.\nПрекращение выполнения программы.\n");
                destroy_text(ptr_Text);
                return 0;
            case 3:
                wprintf(L"\nДостигнута максимальная длина предложения.\nПрекращение выполнения программы.\n");
                destroy_text(ptr_Text);
                return 0;

        }

    }

    destroy_text(ptr_Text);

    return 0;
}
