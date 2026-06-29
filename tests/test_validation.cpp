#include <cassert>
#include <iostream>

#include "../core/types.h"
#include "../core/validation.h"


void test_is_valid_date_with_correct_date() {
    date_data date;
    date.day = 28;
    date.month = 6;
    date.year = 2026;

    assert(is_valid_date(date) == 1);
}


void test_is_valid_date_with_wrong_day() {
    date_data date;
    date.day = 32;
    date.month = 1;
    date.year = 2026;

    assert(is_valid_date(date) == 0);
}


void test_is_valid_date_with_wrong_month() {
    date_data date;
    date.day = 10;
    date.month = 13;
    date.year = 2026;

    assert(is_valid_date(date) == 0);
}


void test_is_valid_time_with_correct_time() {
    time_data time;
    time.hour = 14;
    time.minute = 30;

    assert(is_valid_time(time) == 1);
}


void test_is_valid_time_with_wrong_hour() {
    time_data time;
    time.hour = 25;
    time.minute = 10;

    assert(is_valid_time(time) == 0);
}


void test_is_valid_time_with_wrong_minute() {
    time_data time;
    time.hour = 12;
    time.minute = 75;

    assert(is_valid_time(time) == 0);
}


void test_is_valid_event_data_with_correct_event() {
    event_data event;

    event.id = 1;

    event.event_date.day = 28;
    event.event_date.month = 6;
    event.event_date.year = 2026;

    event.start_time.hour = 10;
    event.start_time.minute = 0;

    event.end_time.hour = 11;
    event.end_time.minute = 30;

    event.priority = 1;
    event.status = 1;

    std::strcpy(event.title, "Exam");
    std::strcpy(event.description, "Math exam");
    std::strcpy(event.category, "study");

    assert(is_valid_event_data(event) == 1);
}


void test_is_valid_event_data_with_empty_title() {
    event_data event;

    event.id = 1;

    event.event_date.day = 28;
    event.event_date.month = 6;
    event.event_date.year = 2026;

    event.start_time.hour = 10;
    event.start_time.minute = 0;

    event.end_time.hour = 11;
    event.end_time.minute = 30;

    event.priority = 1;
    event.status = 1;

    std::strcpy(event.title, "");
    std::strcpy(event.description, "Math exam");
    std::strcpy(event.category, "study");

    assert(is_valid_event_data(event) == 0);
}


void test_is_valid_reminder_data_with_correct_reminder() {
    reminder_data reminder;

    reminder.id = 1;
    reminder.event_id = 10;

    reminder.remind_date.day = 28;
    reminder.remind_date.month = 6;
    reminder.remind_date.year = 2026;

    reminder.remind_time.hour = 9;
    reminder.remind_time.minute = 30;

    reminder.remind_before_minutes = 30;
    reminder.is_triggered = 0;

    std::strcpy(reminder.message, "Reminder");

    assert(is_valid_reminder_data(reminder) == 1);
}


void test_is_valid_reminder_data_with_empty_message() {
    reminder_data reminder;

    reminder.id = 1;
    reminder.event_id = 10;

    reminder.remind_date.day = 28;
    reminder.remind_date.month = 6;
    reminder.remind_date.year = 2026;

    reminder.remind_time.hour = 9;
    reminder.remind_time.minute = 30;

    reminder.remind_before_minutes = 30;
    reminder.is_triggered = 0;

    std::strcpy(reminder.message, "");

    assert(is_valid_reminder_data(reminder) == 0);
}


int main() {
    test_is_valid_date_with_correct_date();
    test_is_valid_date_with_wrong_day();
    test_is_valid_date_with_wrong_month();

    test_is_valid_time_with_correct_time();
    test_is_valid_time_with_wrong_hour();
    test_is_valid_time_with_wrong_minute();

    test_is_valid_event_data_with_correct_event();
    test_is_valid_event_data_with_empty_title();

    test_is_valid_reminder_data_with_correct_reminder();
    test_is_valid_reminder_data_with_empty_message();

    std::cout << "test_validation: all tests passed" << std::endl;
    return 0;
}