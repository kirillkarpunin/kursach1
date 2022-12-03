#include <stdlib.h>

#include "../header_files/structs.h"

void increase_buffer_text(text_t* ptr_Text){
    sent_t* temp = realloc(ptr_Text->sent_arr, ptr_Text->len * sizeof(sent_t));

    if (temp){
        ptr_Text->sent_arr = temp;

        create_struct_sent(ptr_Text);

    } else {
        wprintf(L"Не удалось перевыделить память\n");
        //destroy
        exit(0);
    }
}
