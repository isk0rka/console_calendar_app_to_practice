#include "validation.h"

#include <cstring>

int is_leap_year(int year)
{
    if (year % 400 == 0){
        return 1;
    }

    if (year % 100 == 0){
        return 0;
    }

    if (year % 4 == 0){
        return 1;
    }

    return 0;
}

int get_days_in_month(int year, int month)
{
    if (month == 1 || month == 3 || month == 5 || month == 7 ||
        month == 8 || month == 10 || month == 12){
        return 31;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11){
        return 30;
    }

    if (month == 2){
        if (is_leap_year(year)){
            return 29;
        }

        return 28;
    }

    return 0;
}

int is_valid_year(int year)
{
    if (year < MIN_YEAR || year > MAX_YEAR){
        return 0;
    }

    return 1;
}

int is_valid_month(int month)
{
    if (month < MIN_MONTH || month > MAX_MONTH){
        return 0;
    }

    return 1;
}

int is_valid_day(int day)
{
    if (day < MIN_DAY || day > MAX_DAY){
        return 0;
    }

    return 1;
}

int is_valid_date(date_data date)
{
    if (!is_valid_year(date.year)){
        return 0;
    }

    if (!is_valid_month(date.month)){
        return 0;
    }

    if (!is_valid_day(date.day)){
        return 0;
    }

    if (date.day > get_days_in_month(date.year, date.month)){
        return 0;
    }

    return 1;
}

int is_valid_hour(int hour)
{
    if (hour < MIN_HOUR || hour > MAX_HOUR){
        return 0;
    }

    return 1;
}

int is_valid_minute(int minute)
{
    if (minute < MIN_MINUTE || minute > MAX_MINUTE){
        return 0;
    }

    return 1;
}

int is_valid_time(time_data time)
{
    if (!is_valid_hour(time.hour)){
        return 0;
    }

    if (!is_valid_minute(time.minute)){
        return 0;
    }

    return 1;
}

int is_valid_time_range(time_data start_time, time_data end_time)
{
    if (!is_valid_time(start_time) || !is_valid_time(end_time)){
        return 0;
    }

    if (end_time.hour < start_time.hour){
        return 0;
    }

    if (end_time.hour == start_time.hour && end_time.minute < start_time.minute){
        return 0;
    }

    return 1;
}

int is_non_empty_string(const char* text)
{
    if (text == nullptr){
        return 0;
    }

    if (text[0] == '\0'){
        return 0;
    }

    return 1;
}

int is_string_length_valid(const char* text, int max_size)
{
    if (text == nullptr){
        return 0;
    }

    if (static_cast<int>(std::strlen(text)) >= max_size){
        return 0;
    }

    return 1;
}

int is_valid_event_title(const char* title)
{
    if (!is_non_empty_string(title)){
        return 0;
    }

    if (!is_string_length_valid(title, EVENT_TITLE_SIZE)){
        return 0;
    }

    return 1;
}

int is_valid_event_description(const char* description)
{
    if (description == nullptr){
        return 0;
    }

    if (!is_string_length_valid(description, EVENT_DESCRIPTION_SIZE)){
        return 0;
    }

    return 1;
}

int is_valid_event_category(const char* category)
{
    if (!is_non_empty_string(category)){
        return 0;
    }

    if (!is_string_length_valid(category, EVENT_CATEGORY_SIZE)){
        return 0;
    }

    return 1;
}

int is_valid_reminder_message(const char* message)
{
    if (!is_non_empty_string(message)){
        return 0;
    }

    if (!is_string_length_valid(message, REMINDER_MESSAGE_SIZE)){
        return 0;
    }

    return 1;
}

int is_valid_id(int id)
{
    if (id <= 0){
        return 0;
    }

    return 1;
}

int is_valid_event_priority(int priority)
{
    if (priority != EVENT_PRIORITY_LOW &&
        priority != EVENT_PRIORITY_MEDIUM &&
        priority != EVENT_PRIORITY_HIGH){
        return 0;
    }

    return 1;
}

int is_valid_event_status(int status)
{
    if (status != EVENT_STATUS_PLANNED &&
        status != EVENT_STATUS_DONE &&
        status != EVENT_STATUS_CANCELED){
        return 0;
    }

    return 1;
}

int is_valid_event_data(const event_data& event)
{
    if (!is_valid_id(event.id)){
        return 0;
    }

    if (!is_valid_event_title(event.title)){
        return 0;
    }

    if (!is_valid_event_description(event.description)){
        return 0;
    }

    if (!is_valid_date(event.event_date)){
        return 0;
    }

    if (!is_valid_time(event.start_time)){
        return 0;
    }

    if (!is_valid_time(event.end_time)){
        return 0;
    }

    if (!is_valid_time_range(event.start_time, event.end_time)){
        return 0;
    }

    if (!is_valid_event_category(event.category)){
        return 0;
    }

    if (!is_valid_event_priority(event.priority)){
        return 0;
    }

    if (!is_valid_event_status(event.status)){
        return 0;
    }

    return 1;
}

int is_valid_reminder_data(const reminder_data& reminder)
{
    if (!is_valid_id(reminder.id)){
        return 0;
    }

    if (!is_valid_id(reminder.event_id)){
        return 0;
    }

    if (!is_valid_date(reminder.remind_date)){
        return 0;
    }

    if (!is_valid_time(reminder.remind_time)){
        return 0;
    }

    if (reminder.remind_before_minutes < 0){
        return 0;
    }

    if (reminder.is_triggered != DEFAULT_IS_NOT_TRIGGERED &&
        reminder.is_triggered != DEFAULT_IS_TRIGGERED){
        return 0;
    }

    if (!is_valid_reminder_message(reminder.message)){
        return 0;
    }

    return 1;
}