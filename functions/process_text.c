#include <wctype.h>
#include <string.h>

#include "../header_files/structs.h"
#include "../header_files/memory_interaction.h"

void count_words(text_t* ptr_Text){
    for (int i = 0; i < ptr_Text->len; i++){

        if (ptr_Text->sent_arr[i].len == 1){
            if (!(iswspace(*(ptr_Text->sent_arr[i].start)) || *(ptr_Text->sent_arr[i].start) == L',' || *(ptr_Text->sent_arr[i].start) == L'.')){
                ptr_Text->sent_arr[i].amount_of_words ++;
            }

        } else {

            for (int j = 0; j < ptr_Text->sent_arr[i].len -1; j++){
                if (!(iswspace(*(ptr_Text->sent_arr[i].start + j)) || *(ptr_Text->sent_arr[i].start + j) == L',' || *(ptr_Text->sent_arr[i].start + j) == L'.') &&
                    (iswspace(*(ptr_Text->sent_arr[i].start + j + 1)) || *(ptr_Text->sent_arr[i].start + j + 1) == L',' || *(ptr_Text->sent_arr[i].start + j + 1) == L'.')){
                    ptr_Text->sent_arr[i].amount_of_words ++;
                }

            }
        }

    }
}

void delete_repetitive_sents(text_t* ptr_Text){
    for (int i = 0; i < ptr_Text->len -1; i++){
        if (ptr_Text->len == 1){
            break;
        }

        for (int j = i+1; j < ptr_Text->len; j++){

            if (ptr_Text->sent_arr[i].amount_of_words != ptr_Text->sent_arr[j].amount_of_words){
                continue;
            }

            if (!wcscasecmp(ptr_Text->sent_arr[i].start, ptr_Text->sent_arr[j].start)){
                destroy_sent(ptr_Text, j);
                j --;
            }

        }
    }
}

void delete_sents_more_10_words(text_t* ptr_Text){
    for (int i = 0; i < ptr_Text->len; i++){
        if (ptr_Text->sent_arr[i].amount_of_words > 10){
            destroy_sent(ptr_Text, i);
        }
    }
}

void replace_tsya(text_t* ptr_Text) {
    wchar_t *substr1 = L"ться";
    wchar_t *substr2 = L"тся";

    for (int i = 0; i < ptr_Text->len; i++) {
        wchar_t *start = ptr_Text->sent_arr[i].start;
        wchar_t *end = ptr_Text->sent_arr[i].start + ptr_Text->sent_arr[i].len;

        while (start < end) {
            wchar_t *index1 = wcsstr(start, substr1);
            wchar_t *index2 = wcsstr(start, substr2);

            if (index1 < start || index1 > end){
                index1 = NULL;
            }
            if (index2 < start || index2 > end){
                index2 = NULL;
            }

            if (index1 == NULL && index2 == NULL ) {
                break;
            } else {
                if ((index2 == NULL || index1 < index2) && index1 != NULL) {
                    index1++;
                    *(index1) = L'с';
                    index1++;
                    *(index1) = L'я';
                    index1++;

                    memmove(index1, index1 + 1, (end - index1) * sizeof(wchar_t));
                    ptr_Text->sent_arr[i].len--;

                    end--;
                    start = index1;

                } else {
                    if (ptr_Text->sent_arr[i].len == ptr_Text->sent_arr[i].capacity) {
                        increase_buffer_sent(ptr_Text, i);
                    }

                    index2++;
                    *(index2) = L'ь';
                    index2++;
                    *(index2) = L'с';
                    index2++;

                    memmove(index2 + 1, index2, (end - index2) * sizeof(wchar_t));
                    ptr_Text->sent_arr[i].len++;
                    end++;

                    *(index2) = L'я';
                    index2++;

                    start = index2;
                }
            }
        }
    }
}