#include <wctype.h>

#include "../header_files/structs.h"

void count_words(text_t* ptr_Text){
    for (int i = 0; i < ptr_Text->len; i++){
        for (int j = 0; j < ptr_Text->sent_arr[i].len -2; j++){
            if ((iswspace(*(ptr_Text->sent_arr[i].start + j)) || *(ptr_Text->sent_arr[i].start + j) == L',') &&
            !(iswspace(*(ptr_Text->sent_arr[i].start + j + 1)) || *(ptr_Text->sent_arr[i].start + j + 1) == L',')){
//                ptr_Text->sent_arr[i].amount_of_words ++;
            }
        }
    }
}