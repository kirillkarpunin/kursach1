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

void replace_tsya(text_t* ptr_Text){
    wchar_t* substr = L"ться";
    for (int i = 0; i < ptr_Text->len; i++){
        wchar_t* index = ptr_Text->sent_arr[i].start;
        wchar_t* end = ptr_Text->sent_arr[i].start + ptr_Text->sent_arr[i].len;

        while (index < end){
            index = wcsstr(index, substr);
            if (index == NULL){
                break;
            }

            for (int j = 0; j < 4; j++){
                *(index+j) = L'ф';
            }
            index+=4;
        }
    }


    substr = L"тся";
    for (int i = 0; i < ptr_Text->len; i++){
        wchar_t* index = ptr_Text->sent_arr[i].start;
        wchar_t* end = ptr_Text->sent_arr[i].start + ptr_Text->sent_arr[i].len;

        while (index < end) {
            index = wcsstr(index, substr);
            if (index == NULL) {
                break;
            }

            if (ptr_Text->sent_arr[i].len == ptr_Text->sent_arr[i].capacity){
                increase_buffer_sent(ptr_Text, i);
            }

            index++;
            *(index) = L'ь';
            index++;
            *(index) = L'с';
            index++;

            memmove(index+1, index, (end - index) * sizeof(wchar_t));
            ptr_Text->sent_arr[i].len++;
            end ++;

            *(index) = L'я';

        }
    }

    substr = L"фффф";
    for (int i = 0; i < ptr_Text->len; i++) {
        wchar_t *index = ptr_Text->sent_arr[i].start;
        wchar_t *end = ptr_Text->sent_arr[i].start + ptr_Text->sent_arr[i].len;

        while (index < end) {
            index = wcsstr(index, substr);
            if (index == NULL) {
                break;
            }

            *(index) = L'т';
            index++;
            *(index) = L'с';
            index++;
            *(index) = L'я';
            index++;

            memmove(index, index+1, (end - index) * sizeof(wchar_t));
            ptr_Text->sent_arr[i].len--;
            end --;
        }
    }
}