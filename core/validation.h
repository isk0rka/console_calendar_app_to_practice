#ifndef CALENDAR_APP_CORE_VALIDATION_H
#define CALENDAR_APP_CORE_VALIDATION_H

#include "types.h"
#include "constants.h"

int is_leap_year(int year);

int get_days_in_month(int year, int month);

int is_valid_year(int year);

int is_valid_month(int month);

int is_valid_day(int day);

int is_valid_date(date_data date);

int is_valid_hour(int hour);

int is_valid_minute(int minute);

int is_valid_time(time_data time);

int is_valid_time_range(time_data start_time, time_data end_time);

int is_non_empty_string(const char* text);

int is_string_length_valid(const char* text, int max_size);

int is_valid_event_title(const char* title);

int is_valid_event_description(const char* description);

int is_valid_event_category(const char* category);

int is_valid_reminder_message(const char* message);

int is_valid_id(int id);

int is_valid_event_priority(int priority);

int is_valid_event_status(int status);

int is_valid_event_data(const event_data& event);

int is_valid_reminder_data(const reminder_data& reminder);

#endif