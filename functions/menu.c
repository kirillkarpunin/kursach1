#include "../header_files/structs.h"
#include "../header_files/text_io.h"

void hint(){
    wprintf(L"\n\n-----------------------------------------------------------------------"
            "\nВыбор команды:"
            "\n\t1 - Заменить -ться на -тся"
            "\n\t2 - Вывести все предложения, в которых встречается второе слово\nпервого предложения (слово выделено зеленым)"
            "\n\t3 - Отсортировать предложения по возрастанию количества слов"
            "\n\t4 - Удалить предложения, в которых больше 10 слов"
            "\n\th - Вывод подсказки"
            "\n\tq - Завершение работы программы"
            "\n-----------------------------------------------------------------------\n\n");
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
                wprintf(L"1\n");
                break;
            case L'2':
                wprintf(L"2\n");
                break;
            case L'3':
                wprintf(L"3\n");
                break;
            case L'4':
                wprintf(L"4\n");
                break;
            case L'h':
                hint();
                print_text(ptr_Text);
                break;
            case L'q':
                wprintf(L"q\n");
                break;
            default:
                wprintf(L"Неверный ввод\n");
        }

    }

}

