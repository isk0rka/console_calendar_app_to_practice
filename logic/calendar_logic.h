#ifndef CALENDAR_APP_LOGIC_CALENDAR_LOGIC_H
#define CALENDAR_APP_LOGIC_CALENDAR_LOGIC_H

#include "../core/types.h"
#include "../core/constants.h"
#include "../core/validation.h"
#include "../core/datetime_utils.h"


int get_days_in_month_for_calendar(int year, int month);

int get_weekday(date_data date);

int get_weekday_monday_first(date_data date);

void get_week_range(date_data target_date, date_data& week_start, date_data& week_end);

int is_same_month(date_data left, date_data right);

int count_events_for_day(const event_data* events, int events_count, date_data target_date);

int get_events_for_day(const event_data* source_events,
                       int source_count,
                       date_data target_date,
                       event_data* result_events,
                       int result_capacity,
                       int& result_count);

int get_events_for_week(const event_data* source_events,
                        int source_count,
                        date_data target_date,
                        event_data* result_events,
                        int result_capacity,
                        int& result_count);

void build_month_calendar_matrix(int year, int month, int calendar_matrix[6][7]);

int date_to_serial_days(date_data date);

date_data serial_days_to_date(int total_days);

date_data add_days_to_date(date_data date, int days);

int get_month_weeks_count(int year, int month);

#endif // CALENDAR_APP_LOGIC_CALENDAR_LOGIC_H