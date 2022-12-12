#include "../header_files/structs.h"
#include "../header_files/text_io.h"
#include "../header_files/replace_tsya.h"
#include "../header_files/highlight_word.h"
#include "../header_files/sort_text.h"
#include "../header_files/del_sents_more_10_words.h"

#include <wctype.h>


void hint(){
    wprintf(L"\n\n-----------------------------------------------------------------------"
            "\nВыбор команды:"
            "\n\t1 - Заменить окончание -ться на окончание -тся и наоборот"
            "\n\t2 - Вывести все предложения, в которых встречается второе слово\nпервого предложения (слово выделено зеленым)"
            "\n\t3 - Отсортировать предложения по возрастанию количества слов"
            "\n\t4 - Удалить предложения, в которых больше 10 слов"
            "\n\tp - Вывод обработанного текста"
            "\n\th - Вывод подсказки"
            "\n\tq - Завершение работы программы"
            "\n-----------------------------------------------------------------------\n");
}

int menu(text_t* ptr_Text){
    hint();
    if (print_text(ptr_Text)){
        return 1;
    }

    wchar_t c = 0;
    while (c != L'q'){
        c = getwchar();
        while (c == L'\n' || iswspace(c)){
            c = getwchar();
        }


        switch (c) {
            int err;
            case L'1':
                replace_tsya(ptr_Text);
                break;
            case L'2':
                 err = highlight_word(ptr_Text);
                 if (err){
                     return err;
                 }
                continue;
            case L'3':
                sort_text(ptr_Text);
                break;
            case L'4':
                delete_sents_more_10_words(ptr_Text);
                break;
            case L'p':
                break;
            case L'h':
                hint();
                break;
            case L'q':
                break;
            default:
                wprintf(L"\nНеверный ввод\n");
                continue;
        }

        if (c != L'q' ){
            if(print_text(ptr_Text)){
                return 1;
            }
        }

    }
    return 0;
}

