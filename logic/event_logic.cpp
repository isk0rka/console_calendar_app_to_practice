#include "event_logic.h"

#include <cstring>
#include <new>


int expand_events_array(event_data*& events, int& capacity) {
    int old_capacity = capacity;
    int new_capacity = capacity * 2;

    if (new_capacity <= 0) {
        new_capacity = INITIAL_EVENTS_CAPACITY;
    }

    event_data* new_events = new (std::nothrow) event_data[new_capacity];

    if (new_events == nullptr) {
        return LOGIC_ERROR_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < old_capacity; i++) {
        new_events[i] = events[i];
    }

    delete[] events;
    events = new_events;
    capacity = new_capacity;

    return LOGIC_OK;
}


int add_event(event_data*& events, int& events_count, int& capacity, const event_data& new_event) {
    if (!is_valid_event_data(new_event)) {
        return LOGIC_ERROR_INVALID_DATE;
    }

    if (is_event_exists_by_id(events, events_count, new_event.id)) {
        return LOGIC_ERROR_EVENT_ALREADY_EXISTS;
    }

    if (events_count >= capacity) {
        int expand_status = expand_events_array(events, capacity);

        if (expand_status != LOGIC_OK) {
            return expand_status;
        }
    }

    events[events_count] = new_event;
    events_count++;

    sort_events_by_datetime(events, events_count);

    return LOGIC_OK;
}


int find_event_index_by_id(const event_data* events, int events_count, int event_id) {
    for (int i = 0; i < events_count; i++) {
        if (events[i].id == event_id) {
            return i;
        }
    }

    return -1;
}


int is_event_exists_by_id(const event_data* events, int events_count, int event_id) {
    if (find_event_index_by_id(events, events_count, event_id) != -1) {
        return 1;
    }

    return 0;
}


int delete_event_by_id(event_data* events, int& events_count, int event_id) {
    int delete_index = find_event_index_by_id(events, events_count, event_id);

    if (delete_index == -1) {
        return LOGIC_ERROR_EVENT_NOT_FOUND;
    }

    for (int i = delete_index; i < events_count - 1; i++) {
        events[i] = events[i + 1];
    }

    events_count--;

    return LOGIC_OK;
}


int update_event_by_id(event_data* events, int events_count, int event_id, const event_data& updated_event) {
    int update_index = find_event_index_by_id(events, events_count, event_id);

    if (update_index == -1) {
        return LOGIC_ERROR_EVENT_NOT_FOUND;
    }

    if (!is_valid_event_data(updated_event)) {
        return LOGIC_ERROR_INVALID_DATE;
    }

    if (updated_event.id != event_id) {
        if (is_event_exists_by_id(events, events_count, updated_event.id)) {
            return LOGIC_ERROR_EVENT_ALREADY_EXISTS;
        }
    }

    events[update_index] = updated_event;

    sort_events_by_datetime(events, events_count);

    return LOGIC_OK;
}


event_data* find_event_by_id(event_data* events, int events_count, int event_id) {
    int event_index = find_event_index_by_id(events, events_count, event_id);

    if (event_index == -1) {
        return nullptr;
    }

    return &events[event_index];
}


const event_data* find_event_by_id_const(const event_data* events, int events_count, int event_id) {
    int event_index = find_event_index_by_id(events, events_count, event_id);

    if (event_index == -1) {
        return nullptr;
    }

    return &events[event_index];
}


void sort_events_by_datetime(event_data* events, int events_count) {
    for (int i = 0; i < events_count - 1; i++) {
        for (int j = 0; j < events_count - i - 1; j++) {
            int compare_result = compare_datetime(
                events[j].event_date,
                events[j].start_time,
                events[j + 1].event_date,
                events[j + 1].start_time
            );

            if (compare_result > 0) {
                swap_events(events[j], events[j + 1]);
            }
        }
    }
}


void sort_events_by_priority(event_data* events, int events_count) {
    for (int i = 0; i < events_count - 1; i++) {
        for (int j = 0; j < events_count - i - 1; j++) {
            if (events[j].priority < events[j + 1].priority) {
                swap_events(events[j], events[j + 1]);
            }
        }
    }
}


void sort_events_by_title(event_data* events, int events_count) {
    for (int i = 0; i < events_count - 1; i++) {
        for (int j = 0; j < events_count - i - 1; j++) {
            if (std::strcmp(events[j].title, events[j + 1].title) > 0) {
                swap_events(events[j], events[j + 1]);
            }
        }
    }
}


void swap_events(event_data& left, event_data& right) {
    event_data temp = left;
    left = right;
    right = temp;
}


int count_events_by_date(const event_data* events, int events_count, date_data target_date) {
    int count = 0;

    for (int i = 0; i < events_count; i++) {
        if (is_same_date(events[i].event_date, target_date)) {
            count++;
        }
    }

    return count;
}


int count_events_in_date_range(const event_data* events, int events_count, date_data start_date, date_data end_date) {
    int count = 0;

    for (int i = 0; i < events_count; i++) {
        if (is_date_in_range(events[i].event_date, start_date, end_date)) {
            count++;
        }
    }

    return count;
}


int get_events_by_date(const event_data* source_events,
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


int get_events_in_date_range(const event_data* source_events,
                             int source_count,
                             date_data start_date,
                             date_data end_date,
                             event_data* result_events,
                             int result_capacity,
                             int& result_count) {
    result_count = 0;

    for (int i = 0; i < source_count; i++) {
        if (is_date_in_range(source_events[i].event_date, start_date, end_date)) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_events[result_count] = source_events[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


int find_events_by_title(const event_data* source_events,
                         int source_count,
                         const char* title,
                         event_data* result_events,
                         int result_capacity,
                         int& result_count) {
    result_count = 0;

    if (title == nullptr) {
        return LOGIC_ERROR_EMPTY_TITLE;
    }

    for (int i = 0; i < source_count; i++) {
        if (std::strcmp(source_events[i].title, title) == 0) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_events[result_count] = source_events[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


int mark_event_as_done(event_data* events, int events_count, int event_id) {
    event_data* event = find_event_by_id(events, events_count, event_id);

    if (event == nullptr) {
        return LOGIC_ERROR_EVENT_NOT_FOUND;
    }

    event->status = EVENT_STATUS_DONE;
    return LOGIC_OK;
}


int mark_event_as_canceled(event_data* events, int events_count, int event_id) {
    event_data* event = find_event_by_id(events, events_count, event_id);

    if (event == nullptr) {
        return LOGIC_ERROR_EVENT_NOT_FOUND;
    }

    event->status = EVENT_STATUS_CANCELED;
    return LOGIC_OK;
}


int get_next_event_id(const event_data* events, int events_count) {
    int max_id = 0;

    for (int i = 0; i < events_count; i++) {
        if (events[i].id > max_id) {
            max_id = events[i].id;
        }
    }

    return max_id + 1;
}