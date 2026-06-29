#ifndef CALENDAR_APP_UI_OUTPUT_H
#define CALENDAR_APP_UI_OUTPUT_H

#include "../core/types.h"


void print_line_separator();

void print_empty_line();

void print_date(date_data date);

void print_time(time_data time);

void print_event(const event_data& event);

void print_events_table(const event_data* events, int events_count);

void print_reminder(const reminder_data& reminder);

void print_reminders_table(const reminder_data* reminders, int reminders_count);

const char* get_month_name(int month);

const char* get_weekday_name_short(int weekday);

void print_month_calendar(int year, int month);

void print_week_range(date_data start_date, date_data end_date);

#endif