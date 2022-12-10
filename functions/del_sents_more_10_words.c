#include "../header_files/structs.h"
#include "../header_files/memory_interaction.h"

void delete_sents_more_10_words(text_t* ptr_Text){
    for (size_t i = 0; i < ptr_Text->len; i++){
        if (ptr_Text->sent_arr[i].amount_of_words > 10){
            destroy_sent(ptr_Text, i);
            i--;
        }
    }
}
