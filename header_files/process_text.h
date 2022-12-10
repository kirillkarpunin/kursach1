#pragma once

void count_words(text_t* ptr_Text);

void delete_repetitive_sents(text_t* ptr_Text);

void delete_sents_more_10_words(text_t* ptr_Text);

void replace_tsya(text_t* ptr_Text);

void sort_text(text_t* ptr_Text);

void highlight_word(text_t* ptr_Text);
void add_color_symbols(text_t* ptr_Text, size_t i, wchar_t* word_index, size_t word_len);