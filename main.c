#include <locale.h>

#include "header_files/structs.h"
#include "header_files/text_io.h"
#include "header_files/memory_interaction.h"
#include "header_files/preprocess_text.h"
#include "header_files/menu.h"

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int err = 0;

    text_t* ptr_Text = create_struct_text();

    err = get_text(ptr_Text);
    if (err){
        destroy_text(ptr_Text);
        return 0;
    }

    if (ptr_Text->len == 0){
        err_print(err);
        destroy_text(ptr_Text);
        return 0;
    }

    count_words(ptr_Text);
    delete_repetitive_sents(ptr_Text);

    err = menu(ptr_Text);
    if (err){
        destroy_text(ptr_Text);
        return 0;
    }

    destroy_text(ptr_Text);

    return 0;
}
