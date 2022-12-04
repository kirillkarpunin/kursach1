#include "../header_files/structs.h"
#include "../header_files/increase_buffer.h"

void get_text(text_t* ptr_Text){
    while (ptr_Text->len <= 5) {

        wchar_t c = 0;

        do {
            c = getwchar();

            if (ptr_Text->sent_arr[ptr_Text->len - 1].len >= ptr_Text->sent_arr[ptr_Text->len -1].capacity - 1) {
                increase_buffer_sent(ptr_Text);
            }

            *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = c;
            ptr_Text->sent_arr[ptr_Text->len - 1].len += 1;

        } while (c != L'.');

        *(ptr_Text->sent_arr[ptr_Text->len - 1].start + ptr_Text->sent_arr[ptr_Text->len - 1].len) = '\0';
        ptr_Text->len += 1;
        increase_buffer_text(ptr_Text);
    }
}