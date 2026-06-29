#ifndef CALENDAR_APP_CORE_DATETIME_UTILS_H
#define CALENDAR_APP_CORE_DATETIME_UTILS_H

#include "types.h"

int compare_dates(date_data left, date_data right);

int compare_times(time_data left, time_data right);

int compare_datetime(date_data left_date,
                     time_data left_time,
                     date_data right_date,
                     time_data right_time);

int time_to_minutes(time_data time);

long long datetime_to_number(date_data date, time_data time);

int is_same_date(date_data left, date_data right);

int is_same_time(time_data left, time_data right);

int is_date_in_range(date_data target, date_data start, date_data end);

date_data get_current_date();

time_data get_current_time();

void get_current_datetime(date_data& current_date, time_data& current_time);

#endif