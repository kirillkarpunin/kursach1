#pragma once

void increase_buffer_text(text_t* ptr_Text);

void increase_buffer_sent(text_t* ptr_Text, size_t index);

void destroy_sent(text_t* ptr_Text, size_t index);