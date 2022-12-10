#include "../header_files/structs.h"

#include <stdlib.h>

int cmp (const void* a, const void* b);

void sort_text(text_t* ptr_Text){
    qsort(ptr_Text->sent_arr, ptr_Text->len, sizeof(sent_t), cmp);
}

int cmp (const void* a, const void* b){
    const sent_t* first = (sent_t*)a;
    const sent_t* second = (sent_t*)b;

    if (first->amount_of_words == second->amount_of_words){
        return 0;
    } else {
        if (first->amount_of_words > second->amount_of_words){
            return 1;
        } else {
            return -1;
        }
    }
}