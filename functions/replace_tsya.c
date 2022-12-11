#include "../header_files/structs.h"
#include "../header_files/memory_interaction.h"

#include <string.h>
#include <wctype.h>

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
                    if ((iswspace(*(index1+4)) || *(index1+4) == L',' || *(index1+4) == L'.')){ // 4 - len of ться

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
                        start = index1+4;
                    }


                } else {
                    if ((iswspace(*(index2+3)) || *(index2+3) == L',' || *(index2+3) == L'.')) { // 3 - len of тся
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
                    } else {
                        start = index2 + 3;
                    }

                }
            }
        }
    }
}
