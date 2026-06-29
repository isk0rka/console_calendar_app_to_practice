#include "datetime_utils.h"

#include <ctime>

int compare_dates(date_data left, date_data right){
    if (left.year < right.year){
        return -1;
    }

    if (left.year > right.year){
        return 1;
    }

    if (left.month < right.month){
        return -1;
    }

    if (left.month > right.month){
        return 1;
    }

    if (left.day < right.day){
        return -1;
    }

    if (left.day > right.day){
        return 1;
    }

    return 0;
}

int compare_times(time_data left, time_data right){
    if (left.hour < right.hour){
        return -1;
    }

    if (left.hour > right.hour){
        return 1;
    }

    if (left.minute < right.minute){
        return -1;
    }

    if (left.minute > right.minute){
        return 1;
    }

    return 0;
}

int compare_datetime(date_data left_date,
                     time_data left_time,
                     date_data right_date,
                     time_data right_time){
    int date_compare_result = compare_dates(left_date, right_date);

    if (date_compare_result != 0){
        return date_compare_result;
    }

    return compare_times(left_time, right_time);
}

int time_to_minutes(time_data time){
    return time.hour * 60 + time.minute;
}

long long datetime_to_number(date_data date, time_data time){
    long long result = 0;

    result += static_cast<long long>(date.year) * 100000000LL;
    result += static_cast<long long>(date.month) * 1000000LL;
    result += static_cast<long long>(date.day) * 10000LL;
    result += static_cast<long long>(time.hour) * 100LL;
    result += static_cast<long long>(time.minute);

    return result;
}

int is_same_date(date_data left, date_data right){
    if (compare_dates(left, right) == 0){
        return 1;
    }

    return 0;
}

int is_same_time(time_data left, time_data right)
{
    if (compare_times(left, right) == 0)
    {
        return 1;
    }

    return 0;
}

int is_date_in_range(date_data target, date_data start, date_data end)
{
    if (compare_dates(target, start) < 0){
        return 0;
    }

    if (compare_dates(target, end) > 0){
        return 0;
    }

    return 1;
}

date_data get_current_date(){
    date_data current_date;

    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);

    current_date.year = local_time->tm_year + 1900;
    current_date.month = local_time->tm_mon + 1;
    current_date.day = local_time->tm_mday;

    return current_date;
}

time_data get_current_time(){
    time_data current_time;

    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);

    current_time.hour = local_time->tm_hour;
    current_time.minute = local_time->tm_min;

    return current_time;
}

void get_current_datetime(date_data& current_date, time_data& current_time){
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);

    current_date.year = local_time->tm_year + 1900;
    current_date.month = local_time->tm_mon + 1;
    current_date.day = local_time->tm_mday;

    current_time.hour = local_time->tm_hour;
    current_time.minute = local_time->tm_min;
}