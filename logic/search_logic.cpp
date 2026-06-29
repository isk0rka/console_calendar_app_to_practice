#include "search_logic.h"

#include <cstring>
#include <cctype>


int is_char_equal_ignore_case(char left, char right) {
    unsigned char left_char = static_cast<unsigned char>(left);
    unsigned char right_char = static_cast<unsigned char>(right);

    if (std::tolower(left_char) == std::tolower(right_char)) {
        return 1;
    }

    return 0;
}


int is_string_equal_ignore_case(const char* left, const char* right) {
    if (left == nullptr || right == nullptr) {
        return 0;
    }

    int left_length = static_cast<int>(std::strlen(left));
    int right_length = static_cast<int>(std::strlen(right));

    if (left_length != right_length) {
        return 0;
    }

    for (int i = 0; i < left_length; i++) {
        if (!is_char_equal_ignore_case(left[i], right[i])) {
            return 0;
        }
    }

    return 1;
}


int contains_substring_ignore_case(const char* text, const char* pattern) {
    if (text == nullptr || pattern == nullptr) {
        return 0;
    }

    int text_length = static_cast<int>(std::strlen(text));
    int pattern_length = static_cast<int>(std::strlen(pattern));

    if (pattern_length == 0) {
        return 1;
    }

    if (pattern_length > text_length) {
        return 0;
    }

    for (int i = 0; i <= text_length - pattern_length; i++) {
        int is_match = 1;

        for (int j = 0; j < pattern_length; j++) {
            if (!is_char_equal_ignore_case(text[i + j], pattern[j])) {
                is_match = 0;
                break;
            }
        }

        if (is_match) {
            return 1;
        }
    }

    return 0;
}


int search_events_by_id(const event_data* source_events,
                        int source_count,
                        int event_id,
                        event_data* result_events,
                        int result_capacity,
                        int& result_count) {
    result_count = 0;

    for (int i = 0; i < source_count; i++) {
        if (source_events[i].id == event_id) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_events[result_count] = source_events[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


int search_events_by_exact_title(const event_data* source_events,
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
        if (is_string_equal_ignore_case(source_events[i].title, title)) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_events[result_count] = source_events[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


int search_events_by_title_part(const event_data* source_events,
                                int source_count,
                                const char* title_part,
                                event_data* result_events,
                                int result_capacity,
                                int& result_count) {
    result_count = 0;

    if (title_part == nullptr) {
        return LOGIC_ERROR_EMPTY_TITLE;
    }

    for (int i = 0; i < source_count; i++) {
        if (contains_substring_ignore_case(source_events[i].title, title_part)) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_events[result_count] = source_events[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


int search_events_by_category(const event_data* source_events,
                              int source_count,
                              const char* category,
                              event_data* result_events,
                              int result_capacity,
                              int& result_count) {
    result_count = 0;

    if (category == nullptr) {
        return LOGIC_ERROR_INVALID_CATEGORY;
    }

    for (int i = 0; i < source_count; i++) {
        if (is_string_equal_ignore_case(source_events[i].category, category)) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_events[result_count] = source_events[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


int search_events_by_priority(const event_data* source_events,
                              int source_count,
                              int priority,
                              event_data* result_events,
                              int result_capacity,
                              int& result_count) {
    result_count = 0;

    for (int i = 0; i < source_count; i++) {
        if (source_events[i].priority == priority) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_events[result_count] = source_events[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


int search_events_by_status(const event_data* source_events,
                            int source_count,
                            int status,
                            event_data* result_events,
                            int result_capacity,
                            int& result_count) {
    result_count = 0;

    for (int i = 0; i < source_count; i++) {
        if (source_events[i].status == status) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_events[result_count] = source_events[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


int search_events_by_date(const event_data* source_events,
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


int search_events_by_date_range(const event_data* source_events,
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


int search_reminders_by_id(const reminder_data* source_reminders,
                           int source_count,
                           int reminder_id,
                           reminder_data* result_reminders,
                           int result_capacity,
                           int& result_count) {
    result_count = 0;

    for (int i = 0; i < source_count; i++) {
        if (source_reminders[i].id == reminder_id) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_reminders[result_count] = source_reminders[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


int search_reminders_by_event_id(const reminder_data* source_reminders,
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


int search_reminders_by_message_part(const reminder_data* source_reminders,
                                     int source_count,
                                     const char* message_part,
                                     reminder_data* result_reminders,
                                     int result_capacity,
                                     int& result_count) {
    result_count = 0;

    if (message_part == nullptr) {
        return LOGIC_ERROR_EMPTY_TITLE;
    }

    for (int i = 0; i < source_count; i++) {
        if (contains_substring_ignore_case(source_reminders[i].message, message_part)) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_reminders[result_count] = source_reminders[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}


int search_reminders_by_trigger_status(const reminder_data* source_reminders,
                                       int source_count,
                                       int is_triggered,
                                       reminder_data* result_reminders,
                                       int result_capacity,
                                       int& result_count) {
    result_count = 0;

    for (int i = 0; i < source_count; i++) {
        if (source_reminders[i].is_triggered == is_triggered) {
            if (result_count >= result_capacity) {
                return LOGIC_ERROR_MEMORY_ALLOCATION;
            }

            result_reminders[result_count] = source_reminders[i];
            result_count++;
        }
    }

    return LOGIC_OK;
}