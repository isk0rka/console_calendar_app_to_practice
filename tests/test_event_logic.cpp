#include <cassert>
#include <iostream>
#include <cstring>

#include "../core/types.h"
#include "../core/constants.h"
#include "../logic/event_logic.h"


event_data make_test_event(int id,
                           const char* title,
                           int day,
                           int month,
                           int year,
                           int start_hour,
                           int start_minute,
                           int end_hour,
                           int end_minute,
                           const char* category,
                           int priority,
                           int status) {
    event_data event;

    event.id = id;

    event.event_date.day = day;
    event.event_date.month = month;
    event.event_date.year = year;

    event.start_time.hour = start_hour;
    event.start_time.minute = start_minute;

    event.end_time.hour = end_hour;
    event.end_time.minute = end_minute;

    event.priority = priority;
    event.status = status;

    std::strcpy(event.title, title);
    std::strcpy(event.description, "Test description");
    std::strcpy(event.category, category);

    return event;
}


void test_add_event() {
    int capacity = 2;
    int count = 0;
    event_data* events = new event_data[capacity];

    event_data event = make_test_event(1, "Exam", 28, 6, 2026, 10, 0, 11, 0, "study", 1, 1);

    int status = add_event(events, count, capacity, event);

    assert(status == LOGIC_OK);
    assert(count == 1);
    assert(events[0].id == 1);

    delete[] events;
}


void test_find_event_index_by_id_found() {
    int capacity = 2;
    int count = 0;
    event_data* events = new event_data[capacity];

    add_event(events, count, capacity, make_test_event(1, "Exam", 28, 6, 2026, 10, 0, 11, 0, "study", 1, 1));
    add_event(events, count, capacity, make_test_event(2, "Practice", 29, 6, 2026, 12, 0, 13, 0, "study", 2, 1));

    int index = find_event_index_by_id(events, count, 2);

    assert(index != -1);
    assert(events[index].id == 2);

    delete[] events;
}


void test_find_event_index_by_id_not_found() {
    int capacity = 2;
    int count = 0;
    event_data* events = new event_data[capacity];

    add_event(events, count, capacity, make_test_event(1, "Exam", 28, 6, 2026, 10, 0, 11, 0, "study", 1, 1));

    int index = find_event_index_by_id(events, count, 999);

    assert(index == -1);

    delete[] events;
}


void test_add_event_resizes_array() {
    int capacity = 1;
    int count = 0;
    event_data* events = new event_data[capacity];

    int status1 = add_event(events, count, capacity, make_test_event(1, "Exam", 28, 6, 2026, 10, 0, 11, 0, "study", 1, 1));
    int status2 = add_event(events, count, capacity, make_test_event(2, "Practice", 29, 6, 2026, 12, 0, 13, 0, "study", 2, 1));

    assert(status1 == LOGIC_OK);
    assert(status2 == LOGIC_OK);
    assert(count == 2);
    assert(capacity >= 2);

    delete[] events;
}


void test_event_data_saved_correctly_after_add() {
    int capacity = 2;
    int count = 0;
    event_data* events = new event_data[capacity];

    event_data event = make_test_event(5, "Lab", 30, 6, 2026, 8, 30, 10, 0, "college", 3, 1);

    add_event(events, count, capacity, event);

    assert(std::strcmp(events[0].title, "Lab") == 0);
    assert(events[0].event_date.day == 30);
    assert(events[0].start_time.hour == 8);
    assert(events[0].end_time.minute == 0);

    delete[] events;
}


int main() {
    test_add_event();
    test_find_event_index_by_id_found();
    test_find_event_index_by_id_not_found();
    test_add_event_resizes_array();
    test_event_data_saved_correctly_after_add();

    std::cout << "test_event_logic: all tests passed" << std::endl;
    return 0;
}