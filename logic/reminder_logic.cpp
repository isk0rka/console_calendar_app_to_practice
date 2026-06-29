#include "reminder_logic.h"

#include <new>

int expand_reminders_array(reminder_data*& reminders, int& capacity) {
    int old_capacity = capacity;
    int new_capacity = capacity * 2;

    if (new_capacity <= 0) {
        new_capacity = INITIAL_REMINDERS_CAPACITY;
    }

    reminder_data* new_reminders = new (std::nothrow) reminder_data[new_capacity];

    if (new_reminders == nullptr) {
        return LOGIC_ERROR_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < old_capacity; i++) {
        new_reminders[i] = reminders[i];
    }

    delete[] reminders;
    reminders = new_reminders;
    capacity = new_capacity;

    return LOGIC_OK;
}

int add_reminder(reminder_data*& reminders, int& reminders_count, int& capacity, const reminder_data& new_reminder) {
    if (!is_valid_reminder_data(new_reminder)) {
        return LOGIC_ERROR_INVALID_DATE;
    }

    if (is_reminder_exists_by_id(reminders, reminders_count, new_reminder.id)) {
        return LOGIC_ERROR_REMINDER_ALREADY_EXISTS;
    }

    if (reminders_count >= capacity) {
        int expand_status = expand_reminders_array(reminders, capacity);

        if (expand_status != LOGIC_OK) {
            return expand_status;
        }
    }

    reminders[reminders_count] = new_reminder;
    reminders_count++;

    sort_reminders_by_datetime(reminders, reminders_count);

    return LOGIC_OK;
}

int find_reminder_index_by_id(const reminder_data* reminders, int reminders_count, int reminder_id) {
    for (int i = 0; i < reminders_count; i++) {
        if (reminders[i].id == reminder_id) {
            return i;
        }
    }

    return -1;
}

int is_reminder_exists_by_id(const reminder_data* reminders, int reminders_count, int reminder_id) {
    if (find_reminder_index_by_id(reminders, reminders_count, reminder_id) != -1) {
        return 1;
    }

    return 0;
}

int delete_reminder_by_id(reminder_data* reminders, int& reminders_count, int reminder_id) {
    int delete_index = find_reminder_index_by_id(reminders, reminders_count, reminder_id);

    if (delete_index == -1) {
        return LOGIC_ERROR_REMINDER_NOT_FOUND;
    }

    for (int i = delete_index; i < reminders_count - 1; i++) {
        reminders[i] = reminders[i + 1];
    }

    reminders_count--;

    return LOGIC_OK;
}

int update_reminder_by_id(reminder_data* reminders, int reminders_count, int reminder_id, const reminder_data& updated_reminder) {
    int update_index = find_reminder_index_by_id(reminders, reminders_count, reminder_id);

    if (update_index == -1) {
        return LOGIC_ERROR_REMINDER_NOT_FOUND;
    }

    if (!is_valid_reminder_data(updated_reminder)) {
        return LOGIC_ERROR_INVALID_DATE;
    }

    if (updated_reminder.id != reminder_id) {
        if (is_reminder_exists_by_id(reminders, reminders_count, updated_reminder.id)) {
            return LOGIC_ERROR_REMINDER_ALREADY_EXISTS;
        }
    }

    reminders[update_index] = updated_reminder;

    sort_reminders_by_datetime(reminders, reminders_count);

    return LOGIC_OK;
}

reminder_data* find_reminder_by_id(reminder_data* reminders, int reminders_count, int reminder_id) {
    int reminder_index = find_reminder_index_by_id(reminders, reminders_count, reminder_id);

    if (reminder_index == -1) {
        return nullptr;
    }

    return &reminders[reminder_index];
}

const reminder_data* find_reminder_by_id_const(const reminder_data* reminders, int reminders_count, int reminder_id) {
    int reminder_index = find_reminder_index_by_id(reminders, reminders_count, reminder_id);

    if (reminder_index == -1) {
        return nullptr;
    }

    return &reminders[reminder_index];
}

void swap_reminders(reminder_data& left, reminder_data& right) {
    reminder_data temp = left;
    left = right;
    right = temp;
}

void sort_reminders_by_datetime(reminder_data* reminders, int reminders_count) {
    for (int i = 0; i < reminders_count - 1; i++) {
        for (int j = 0; j < reminders_count - i - 1; j++) {
            int compare_result = compare_datetime(
                reminders[j].remind_date,
                reminders[j].remind_time,
                reminders[j + 1].remind_date,
                reminders[j + 1].remind_time
            );

            if (compare_result > 0) {
                swap_reminders(reminders[j], reminders[j + 1]);
            }
        }
    }
}

int count_due_reminders(const reminder_data* reminders,
                        int reminders_count,
                        date_data current_date,
                        time_data current_time) {
    int count = 0;

    for (int i = 0; i < reminders_count; i++) {
        if (reminders[i].is_triggered == DEFAULT_IS_TRIGGERED) {
            continue;
        }

        int compare_result = compare_datetime(
            reminders[i].remind_date,
            reminders[i].remind_time,
            current_date,
            current_time
        );

        if (compare_result <= 0) {
            count++;
        }
    }

    return count;
}

int get_due_reminders(const reminder_data* source_reminders,
                      int source_count,
                      date_data current_date,
                      time_data current_time,
                      reminder_data* result_reminders,
                      int result_capacity,
                      int& result_count) {
    result_count = 0;

    for (int i = 0; i < source_count; i++) {
        if (source_reminders[i].is_triggered == DEFAULT_IS_TRIGGERED) {
            continue;
        }

        int compare_result = compare_datetime(
            source_reminders[i].remind_date,
            source_reminders[i].remind_time,
            current_date,
            current_time
        );

        if (compare_result <= 0) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_reminders[result_count] = source_reminders[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}

int mark_reminder_as_triggered(reminder_data* reminders, int reminders_count, int reminder_id) {
    reminder_data* reminder = find_reminder_by_id(reminders, reminders_count, reminder_id);

    if (reminder == nullptr) {
        return LOGIC_ERROR_REMINDER_NOT_FOUND;
    }

    reminder->is_triggered = DEFAULT_IS_TRIGGERED;

    return LOGIC_OK;
}

int mark_all_due_reminders_as_triggered(reminder_data* reminders,
                                        int reminders_count,
                                        date_data current_date,
                                        time_data current_time) {
    int updated_count = 0;

    for (int i = 0; i < reminders_count; i++) {
        if (reminders[i].is_triggered == DEFAULT_IS_TRIGGERED) {
            continue;
        }

        int compare_result = compare_datetime(
            reminders[i].remind_date,
            reminders[i].remind_time,
            current_date,
            current_time
        );

        if (compare_result <= 0) {
            reminders[i].is_triggered = DEFAULT_IS_TRIGGERED;
            updated_count++;
        }
    }

    return updated_count;
}

int get_reminders_by_event_id(const reminder_data* source_reminders,
                              int source_count,
                              int event_id,
                              reminder_data* result_reminders,
                              int result_capacity,
                              int& result_count) {
    result_count = 0;

    for (int i = 0; i < source_count; i++) {
        if (source_reminders[i].event_id == event_id) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_reminders[result_count] = source_reminders[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}

int delete_reminders_by_event_id(reminder_data* reminders, int& reminders_count, int event_id) {
    int i = 0;

    while (i < reminders_count) {
        if (reminders[i].event_id == event_id) {
            for (int j = i; j < reminders_count - 1; j++) {
                reminders[j] = reminders[j + 1];
            }

            reminders_count--;
        } else {
            i++;
        }
    }

    return LOGIC_OK;
}

int get_next_reminder_id(const reminder_data* reminders, int reminders_count) {
    int max_id = 0;

    for (int i = 0; i < reminders_count; i++) {
        if (reminders[i].id > max_id) {
            max_id = reminders[i].id;
        }
    }

    return max_id + 1;
}

int is_reminder_linked_event_valid(const event_data* events,
                                   int events_count,
                                   const reminder_data& reminder) {
    if (!is_event_exists_by_id(events, events_count, reminder.event_id)) {
        return 0;
    }

    return 1;
}