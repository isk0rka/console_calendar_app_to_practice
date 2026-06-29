#include <cassert>
#include <iostream>
#include <cstring>

#include "../core/types.h"
#include "../core/constants.h"
#include "../logic/reminder_logic.h"


reminder_data make_test_reminder(int id,
                                 int event_id,
                                 int day,
                                 int month,
                                 int year,
                                 int hour,
                                 int minute,
                                 int before_minutes,
                                 int is_triggered,
                                 const char* message) {
    reminder_data reminder;

    reminder.id = id;
    reminder.event_id = event_id;

    reminder.remind_date.day = day;
    reminder.remind_date.month = month;
    reminder.remind_date.year = year;

    reminder.remind_time.hour = hour;
    reminder.remind_time.minute = minute;

    reminder.remind_before_minutes = before_minutes;
    reminder.is_triggered = is_triggered;

    std::strcpy(reminder.message, message);

    return reminder;
}


void test_add_reminder() {
    int capacity = 2;
    int count = 0;
    reminder_data* reminders = new reminder_data[capacity];

    reminder_data reminder = make_test_reminder(1, 10, 28, 6, 2026, 9, 30, 30, 0, "Reminder");

    int status = add_reminder(reminders, count, capacity, reminder);

    assert(status == LOGIC_OK);
    assert(count == 1);
    assert(reminders[0].id == 1);

    delete[] reminders;
}


void test_find_reminder_index_by_id_found() {
    int capacity = 2;
    int count = 0;
    reminder_data* reminders = new reminder_data[capacity];

    add_reminder(reminders, count, capacity, make_test_reminder(1, 10, 28, 6, 2026, 9, 30, 30, 0, "First"));
    add_reminder(reminders, count, capacity, make_test_reminder(2, 11, 29, 6, 2026, 8, 15, 15, 0, "Second"));

    int index = find_reminder_index_by_id(reminders, count, 2);

    assert(index != -1);
    assert(reminders[index].id == 2);

    delete[] reminders;
}


void test_find_reminder_index_by_id_not_found() {
    int capacity = 2;
    int count = 0;
    reminder_data* reminders = new reminder_data[capacity];

    add_reminder(reminders, count, capacity, make_test_reminder(1, 10, 28, 6, 2026, 9, 30, 30, 0, "First"));

    int index = find_reminder_index_by_id(reminders, count, 100);

    assert(index == -1);

    delete[] reminders;
}


void test_add_reminder_resizes_array() {
    int capacity = 1;
    int count = 0;
    reminder_data* reminders = new reminder_data[capacity];

    int status1 = add_reminder(reminders, count, capacity, make_test_reminder(1, 10, 28, 6, 2026, 9, 30, 30, 0, "First"));
    int status2 = add_reminder(reminders, count, capacity, make_test_reminder(2, 11, 29, 6, 2026, 8, 15, 15, 0, "Second"));

    assert(status1 == LOGIC_OK);
    assert(status2 == LOGIC_OK);
    assert(count == 2);
    assert(capacity >= 2);

    delete[] reminders;
}


void test_reminder_data_saved_correctly_after_add() {
    int capacity = 2;
    int count = 0;
    reminder_data* reminders = new reminder_data[capacity];

    reminder_data reminder = make_test_reminder(5, 99, 30, 6, 2026, 7, 45, 10, 0, "Wake up");

    add_reminder(reminders, count, capacity, reminder);

    assert(std::strcmp(reminders[0].message, "Wake up") == 0);
    assert(reminders[0].event_id == 99);
    assert(reminders[0].remind_time.hour == 7);
    assert(reminders[0].remind_date.day == 30);

    delete[] reminders;
}


int main() {
    test_add_reminder();
    test_find_reminder_index_by_id_found();
    test_find_reminder_index_by_id_not_found();
    test_add_reminder_resizes_array();
    test_reminder_data_saved_correctly_after_add();

    std::cout << "test_reminder_logic: all tests passed" << std::endl;
    return 0;
}