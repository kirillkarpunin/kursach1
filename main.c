#include <locale.h>
#include <stdio.h>
#include "header_files/structs.h"
#include "header_files/text_io.h"
#include "process_text.h"

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");

    text_t* ptr_Text = create_struct_text();

    get_text(ptr_Text);

    count_words(ptr_Text);

    for (int i = 0; i < ptr_Text->len; i++){
        fputws(ptr_Text->sent_arr[i].start, stdout);
    }

    return 0;
}
