#pragma once

#define INCREASE_BUFFER_SENT 75

int increase_buffer_text(text_t* ptr_Text);

int increase_buffer_sent(text_t* ptr_Text, size_t index);

void destroy_sent(text_t* ptr_Text, size_t index);

void destroy_text(text_t* ptr_Text);