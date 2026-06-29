#include "calendar_logic.h"


int get_days_in_month_for_calendar(int year, int month) {
    return get_days_in_month(year, month);
}


int get_weekday(date_data date) {
    static int month_codes[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

    int year = date.year;
    int month = date.month;
    int day = date.day;

    year -= (month < 3);

    return (year + year / 4 - year / 100 + year / 400 + month_codes[month - 1] + day) % 7;
}


int get_weekday_monday_first(date_data date) {
    int weekday = get_weekday(date);

    if (weekday == 0) {
        return 6;
    }

    return weekday - 1;
}


void get_week_range(date_data target_date, date_data& week_start, date_data& week_end) {
    int weekday = get_weekday_monday_first(target_date);

    week_start = add_days_to_date(target_date, -weekday);
    week_end = add_days_to_date(week_start, 6);
}


int is_same_month(date_data left, date_data right) {
    if (left.year == right.year && left.month == right.month) {
        return 1;
    }

    return 0;
}


int count_events_for_day(const event_data* events, int events_count, date_data target_date) {
    int count = 0;

    for (int i = 0; i < events_count; i++) {
        if (is_same_date(events[i].event_date, target_date)) {
            count++;
        }
    }

    return count;
}


int get_events_for_day(const event_data* source_events,
                       int source_count,
                       date_data target_date,
                       event_data* result_events,
                       int result_capacity,
                       int& result_count) {
    result_count = 0;

    for (int i = 0; i < source_count; i++) {
        if (is_same_date(source_events[i].event_date, target_date)) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_events[result_count] = source_events[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


int get_events_for_week(const event_data* source_events,
                        int source_count,
                        date_data target_date,
                        event_data* result_events,
                        int result_capacity,
                        int& result_count) {
    result_count = 0;

    date_data week_start;
    date_data week_end;

    get_week_range(target_date, week_start, week_end);

    for (int i = 0; i < source_count; i++) {
        if (is_date_in_range(source_events[i].event_date, week_start, week_end)) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_events[result_count] = source_events[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


void build_month_calendar_matrix(int year, int month, int calendar_matrix[6][7]) {
    for (int row = 0; row < 6; row++) {
        for (int column = 0; column < 7; column++) {
            calendar_matrix[row][column] = 0;
        }
    }

    date_data first_day_date;
    first_day_date.year = year;
    first_day_date.month = month;
    first_day_date.day = 1;

    int first_weekday = get_weekday_monday_first(first_day_date);
    int days_in_month = get_days_in_month_for_calendar(year, month);

    int current_day = 1;
    int row = 0;
    int column = first_weekday;

    while (current_day <= days_in_month) {
        calendar_matrix[row][column] = current_day;

        current_day++;
        column++;

        if (column == 7) {
            column = 0;
            row++;
        }
    }
}


int date_to_serial_days(date_data date) {
    int total_days = 0;

    for (int year = 1; year < date.year; year++) {
        if (is_leap_year(year)) {
            total_days += 366;
        } else {
            total_days += 365;
        }
    }

    for (int month = 1; month < date.month; month++) {
        total_days += get_days_in_month(date.year, month);
    }

    total_days += date.day - 1;

    return total_days;
}


date_data serial_days_to_date(int total_days) {
    date_data result_date;
    result_date.year = 1;
    result_date.month = 1;
    result_date.day = 1;

    while (1) {
        int days_in_year;

        if (is_leap_year(result_date.year)) {
            days_in_year = 366;
        } else {
            days_in_year = 365;
        }

        if (total_days >= days_in_year) {
            total_days -= days_in_year;
            result_date.year++;
        } else {
            break;
        }
    }

    while (1) {
        int days_in_month = get_days_in_month(result_date.year, result_date.month);

        if (total_days >= days_in_month) {
            total_days -= days_in_month;
            result_date.month++;
        } else {
            break;
        }
    }

    result_date.day = total_days + 1;

    return result_date;
}


date_data add_days_to_date(date_data date, int days) {
    int serial_days = date_to_serial_days(date);
    serial_days += days;

    if (serial_days < 0) {
        serial_days = 0;
    }

    return serial_days_to_date(serial_days);
}


int get_month_weeks_count(int year, int month) {
    int calendar_matrix[6][7];

    build_month_calendar_matrix(year, month, calendar_matrix);

    int weeks_count = 0;

    for (int row = 0; row < 6; row++) {
        int has_day = 0;

        for (int column = 0; column < 7; column++) {
            if (calendar_matrix[row][column] != 0) {
                has_day = 1;
                break;
            }
        }

        if (has_day) {
            weeks_count++;
        }
    }

    return weeks_count;
}