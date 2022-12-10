#include "../header_files/structs.h"
#include "../header_files/text_io.h"
#include "../header_files/process_text.h"

void hint(){
    wprintf(L"\n\n-----------------------------------------------------------------------"
            "\nВыбор команды:"
            "\n\t1 - Заменить -ться на -тся и наоборот"
            "\n\t2 - Вывести все предложения, в которых встречается второе слово\nпервого предложения (слово выделено зеленым)"
            "\n\t3 - Отсортировать предложения по возрастанию количества слов"
            "\n\t4 - Удалить предложения, в которых больше 10 слов"
            "\n\tp - Вывод обработанного текста"
            "\n\th - Вывод подсказки"
            "\n\tq - Завершение работы программы"
            "\n-----------------------------------------------------------------------\n");
}

void menu(text_t* ptr_Text){
    hint();
    print_text(ptr_Text);

    wchar_t c = 0;
    while (c != L'q'){
        c = getwchar();
        while (c == L'\n'){
            c = getwchar();
        }


        switch (c) {
            case L'1':
                replace_tsya(ptr_Text);
                break;
            case L'2':
                highlight_word(ptr_Text);
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
                wprintf(L"Неверный ввод\n");
                continue;
        }

        if (c != L'q' ){
            print_text(ptr_Text);
        }

    }

}

