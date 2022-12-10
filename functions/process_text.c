#include <wctype.h>
#include <stdlib.h>
#include <string.h>

#include "../header_files/structs.h"
#include "../header_files/text_io.h"
#include "../header_files/memory_interaction.h"

void count_words(text_t* ptr_Text){
    for (size_t i = 0; i < ptr_Text->len; i++){

        if (ptr_Text->sent_arr[i].len == 1){
            if (!(iswspace(*(ptr_Text->sent_arr[i].start)) || *(ptr_Text->sent_arr[i].start) == L',' || *(ptr_Text->sent_arr[i].start) == L'.')){
                ptr_Text->sent_arr[i].amount_of_words ++;
            }

        } else {

            for (size_t j = 0; j < ptr_Text->sent_arr[i].len -1; j++){
                if (!(iswspace(*(ptr_Text->sent_arr[i].start + j)) || *(ptr_Text->sent_arr[i].start + j) == L',' || *(ptr_Text->sent_arr[i].start + j) == L'.') &&
                    (iswspace(*(ptr_Text->sent_arr[i].start + j + 1)) || *(ptr_Text->sent_arr[i].start + j + 1) == L',' || *(ptr_Text->sent_arr[i].start + j + 1) == L'.')){
                    ptr_Text->sent_arr[i].amount_of_words ++;
                }

            }
        }

    }
}

void delete_repetitive_sents(text_t* ptr_Text){
    for (size_t i = 0; i < ptr_Text->len -1; i++){
        if (ptr_Text->len == 1){
            break;
        }

        for (size_t j = i+1; j < ptr_Text->len; j++){

            if (ptr_Text->sent_arr[i].amount_of_words != ptr_Text->sent_arr[j].amount_of_words){
                continue;
            }

            if (!wcscasecmp(ptr_Text->sent_arr[i].start, ptr_Text->sent_arr[j].start)){
                destroy_sent(ptr_Text, j);
                j--;
            }

        }
    }
}

void delete_sents_more_10_words(text_t* ptr_Text){
    for (size_t i = 0; i < ptr_Text->len; i++){
        if (ptr_Text->sent_arr[i].amount_of_words > 10){
            destroy_sent(ptr_Text, i);
            i--;
        }
    }
}

void replace_tsya(text_t* ptr_Text) {
    wchar_t *substr1 = L"ться";
    wchar_t *substr2 = L"тся";

    for (size_t i = 0; i < ptr_Text->len; i++) {
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
                    *(index1) = substr2[1];
                    index1++;
                    *(index1) = substr2[2];
                    index1++;

                    memmove(index1, index1 + 1, (end - index1 + 1) * sizeof(wchar_t));
                    ptr_Text->sent_arr[i].len--;

                    end--;
                    start = index1;

                } else {
                    if (ptr_Text->sent_arr[i].len == ptr_Text->sent_arr[i].capacity) {
                        increase_buffer_sent(ptr_Text, i);
                    }

                    index2++;
                    *(index2) = substr1[1];
                    index2++;
                    *(index2) = substr1[2];
                    index2++;

                    memmove(index2 + 1, index2, (end - index2 + 1) * sizeof(wchar_t));
                    ptr_Text->sent_arr[i].len++;
                    end++;

                    *(index2) = substr1[3];
                    index2++;

                    start = index2;
                }
            }
        }
    }
}

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

wchar_t* get_second_word(text_t* ptr_Text);
wchar_t* scan_separators(wchar_t* temp);
wchar_t* scan_graph(wchar_t* temp);
void add_color_symbols(text_t* ptr_Text, size_t i, wchar_t* word_index, size_t word_len);
void remove_color_symbols(text_t* ptr_Text, size_t i);


void highlight_word(text_t* ptr_Text){
    if (ptr_Text->sent_arr[0].amount_of_words < 2){
        wprintf(L"В первом предложении нет второго слова.\n");
    } else {
        wchar_t* word = get_second_word(ptr_Text);
        size_t word_len = wcslen(word);

        wprintf(L"\nПредложения со словом \"\033[0;32m%ls\033[0m\":\n", word);

        for (size_t i = 0; i < ptr_Text->len;i++){
            int isprint = 0;

            wchar_t* word_index = wcsstr(ptr_Text->sent_arr[i].start, word);
            while (word_index != NULL){
                if ((word_index == ptr_Text->sent_arr[i].start || iswspace(*(word_index-1)) || *(word_index-1) == L',') &&
                    (*(word_index+word_len) == L'.' || iswspace(*(word_index+word_len)) || *(word_index+word_len) == L',')){

                    if (ptr_Text->sent_arr[i].len >= ptr_Text->sent_arr[i].capacity - 11) { //11 - len of color symbols
                        increase_buffer_sent(ptr_Text, i);
                        word_index = wcsstr(ptr_Text->sent_arr[i].start, word);
                        continue;
                    }

                    add_color_symbols(ptr_Text, i, word_index, word_len);
                    isprint = 1;
                    word_index = wcsstr(word_index+word_len+11, word); //11 - len of color symbols
                } else {
                    word_index = wcsstr(word_index+word_len, word);
                }

            }
            if (isprint){
                spec_print_text(ptr_Text->sent_arr[i]);
                remove_color_symbols(ptr_Text, i);
            }
        }
        wprintf(L"\n");
        free(word);
    }
}

void add_color_symbols(text_t* ptr_Text, size_t i, wchar_t* word_index, size_t word_len){
    wchar_t* green_color = L"\033[0;32m";
    wchar_t* default_color = L"\033[0m";

    wchar_t* end_sent = ptr_Text->sent_arr[i].start+ptr_Text->sent_arr[i].len;

    memmove(word_index + wcslen(green_color), word_index, (end_sent - word_index + 1) * sizeof(wchar_t));
    ptr_Text->sent_arr[i].len+=wcslen(green_color);
    end_sent+=wcslen(green_color);

    for (int j = 0; j < wcslen(green_color); j++){
        *(word_index) = green_color[j];
        word_index++;
    }

    wchar_t* word_end = word_index+word_len;

    memmove(word_end + wcslen(default_color), word_end, (end_sent - word_end + 1) * sizeof(wchar_t));
    ptr_Text->sent_arr[i].len+=wcslen(default_color);
    end_sent+=wcslen(default_color);

    for (int j = 0; j < wcslen(default_color); j++){
        *(word_end) = default_color[j];
        word_end++;
    }

}

void remove_color_symbols(text_t* ptr_Text, size_t i){
    wchar_t* green_color = L"\033[0;32m";
    wchar_t* default_color = L"\033[0m";

    wchar_t* green_index = wcsstr(ptr_Text->sent_arr[i].start, green_color);
    wchar_t* default_index = wcsstr(ptr_Text->sent_arr[i].start, default_color);

    wchar_t* end_sent = ptr_Text->sent_arr[i].start+ptr_Text->sent_arr[i].len;

    while (green_index != NULL && default_index != NULL){
        if (green_index != NULL){
            memmove(green_index, green_index + wcslen(green_color), (end_sent - green_index + 1) * sizeof(wchar_t));
            ptr_Text->sent_arr[i].len-=wcslen(green_color);
            end_sent-=wcslen(green_color);

            default_index = wcsstr(ptr_Text->sent_arr[i].start, default_color);
        }
        if (default_index != NULL){
            memmove(default_index, default_index + wcslen(default_color), (end_sent - default_index + 1) * sizeof(wchar_t));
            ptr_Text->sent_arr[i].len-=wcslen(default_color);
            end_sent-=wcslen(default_color);

            green_index = wcsstr(ptr_Text->sent_arr[i].start, green_color);
        }
    }
}

wchar_t* get_second_word(text_t* ptr_Text){
    wchar_t* temp = ptr_Text->sent_arr[0].start;

    if (iswspace(*(temp)) || *(temp) == L','){
        temp = scan_separators(temp);
    }

    temp = scan_graph(temp);
    temp = scan_separators(temp);

    wchar_t* start_word = temp;

    temp = scan_graph(temp);

    wchar_t* end_word = temp;

    wchar_t* word = malloc((end_word-start_word + 1) * sizeof(wchar_t));
    for (size_t i = 0; i < (end_word-start_word); i++){
        word[i] = *(start_word+i);
    }
    word[(end_word-start_word)] = L'\0';

    return word;
}

wchar_t* scan_separators(wchar_t* temp){
    size_t i = 0;
    while (iswspace(*(temp)) || *(temp) == L','){
        temp++;
    }
    return temp;
}

wchar_t* scan_graph(wchar_t* temp){
    size_t i = 0;
    while (!(iswspace(*(temp)) || *(temp) == L',' || *(temp) == L'.')){
        temp++;
    }
    return temp;
}