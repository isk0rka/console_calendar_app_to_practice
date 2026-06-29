#ifndef CALENDAR_APP_UI_INPUT_H
#define CALENDAR_APP_UI_INPUT_H

#include "../core/types.h"


void clear_input_buffer();

void read_line(char* buffer, int buffer_size);

int is_empty_input(const char* text);

int parse_int_from_text(const char* text, int& value);

int read_int();

int read_int_in_range(int min_value, int max_value);

void read_text_input(char* buffer, int buffer_size);

void read_text_input_non_empty(char* buffer, int buffer_size);

date_data read_date_input();

time_data read_time_input();

int read_yes_no_input();

#endif