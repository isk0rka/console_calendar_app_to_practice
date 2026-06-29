#include "file_storage.h"

#include "../core/validation.h"
#include "../logic/event_logic.h"
#include "../logic/reminder_logic.h"

#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <new>


int ensure_data_files_exist() {
    {
        std::ifstream events_file(EVENTS_FILE_NAME);

        if (!events_file.is_open()) {
            std::ofstream create_events_file(EVENTS_FILE_NAME);

            if (!create_events_file.is_open()) {
                return LOGIC_ERROR_FILE_OPEN;
            }
        }
    }

    {
        std::ifstream reminders_file(REMINDERS_FILE_NAME);

        if (!reminders_file.is_open()) {
            std::ofstream create_reminders_file(REMINDERS_FILE_NAME);

            if (!create_reminders_file.is_open()) {
                return LOGIC_ERROR_FILE_OPEN;
            }
        }
    }

    return LOGIC_OK;
}


int save_events_to_file(const char* file_name, const event_data* events, int events_count) {
    if (file_name == nullptr) {
        return LOGIC_ERROR_FILE_OPEN;
    }

    if (events == nullptr && events_count > 0) {
        return LOGIC_ERROR_FILE_WRITE;
    }

    std::ofstream file(file_name);

    if (!file.is_open()) {
        return LOGIC_ERROR_FILE_OPEN;
    }

    for (int i = 0; i < events_count; i++) {
        write_event_to_stream(file, events[i]);
    }

    if (!file.good()) {
        file.close();
        return LOGIC_ERROR_FILE_WRITE;
    }

    file.close();

    return LOGIC_OK;
}


int load_events_from_file(const char* file_name, event_data*& events, int& events_count, int& capacity) {
    if (file_name == nullptr) {
        return LOGIC_ERROR_FILE_OPEN;
    }

    std::ifstream file(file_name);

    if (!file.is_open()) {
        return LOGIC_ERROR_FILE_OPEN;
    }

    if (events != nullptr) {
        delete[] events;
        events = nullptr;
    }

    capacity = INITIAL_EVENTS_CAPACITY;
    events_count = 0;
    events = new (std::nothrow) event_data[capacity];

    if (events == nullptr) {
        file.close();
        return LOGIC_ERROR_MEMORY_ALLOCATION;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        event_data temp_event;

        int parse_status = parse_event_from_line(line.c_str(), temp_event);

        if (parse_status != LOGIC_OK) {
            continue;
        }

        int add_status = add_event(events, events_count, capacity, temp_event);

        if (add_status != LOGIC_OK) {
            file.close();
            return add_status;
        }
    }

    if (!file.eof() && file.fail()) {
        file.close();
        return LOGIC_ERROR_FILE_READ;
    }

    file.close();

    return LOGIC_OK;
}


int save_reminders_to_file(const char* file_name, const reminder_data* reminders, int reminders_count) {
    if (file_name == nullptr) {
        return LOGIC_ERROR_FILE_OPEN;
    }

    if (reminders == nullptr && reminders_count > 0) {
        return LOGIC_ERROR_FILE_WRITE;
    }

    std::ofstream file(file_name);

    if (!file.is_open()) {
        return LOGIC_ERROR_FILE_OPEN;
    }

    for (int i = 0; i < reminders_count; i++) {
        write_reminder_to_stream(file, reminders[i]);
    }

    if (!file.good()) {
        file.close();
        return LOGIC_ERROR_FILE_WRITE;
    }

    file.close();

    return LOGIC_OK;
}


int load_reminders_from_file(const char* file_name, reminder_data*& reminders, int& reminders_count, int& capacity) {
    if (file_name == nullptr) {
        return LOGIC_ERROR_FILE_OPEN;
    }

    std::ifstream file(file_name);

    if (!file.is_open()) {
        return LOGIC_ERROR_FILE_OPEN;
    }

    if (reminders != nullptr) {
        delete[] reminders;
        reminders = nullptr;
    }

    capacity = INITIAL_REMINDERS_CAPACITY;
    reminders_count = 0;
    reminders = new (std::nothrow) reminder_data[capacity];

    if (reminders == nullptr) {
        file.close();
        return LOGIC_ERROR_MEMORY_ALLOCATION;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        reminder_data temp_reminder;

        int parse_status = parse_reminder_from_line(line.c_str(), temp_reminder);

        if (parse_status != LOGIC_OK) {
            continue;
        }

        int add_status = add_reminder(reminders, reminders_count, capacity, temp_reminder);

        if (add_status != LOGIC_OK) {
            file.close();
            return add_status;
        }
    }

    if (!file.eof() && file.fail()) {
        file.close();
        return LOGIC_ERROR_FILE_READ;
    }

    file.close();

    return LOGIC_OK;
}


int save_all_data(const event_data* events,
                  int events_count,
                  const reminder_data* reminders,
                  int reminders_count) {
    int save_events_status = save_events_to_file(EVENTS_FILE_NAME, events, events_count);

    if (save_events_status != LOGIC_OK) {
        return save_events_status;
    }

    int save_reminders_status = save_reminders_to_file(REMINDERS_FILE_NAME, reminders, reminders_count);

    if (save_reminders_status != LOGIC_OK) {
        return save_reminders_status;
    }

    return LOGIC_OK;
}


int load_all_data(event_data*& events,
                  int& events_count,
                  int& events_capacity,
                  reminder_data*& reminders,
                  int& reminders_count,
                  int& reminders_capacity) {
    int ensure_status = ensure_data_files_exist();

    if (ensure_status != LOGIC_OK) {
        return ensure_status;
    }

    int load_events_status = load_events_from_file(EVENTS_FILE_NAME, events, events_count, events_capacity);

    if (load_events_status != LOGIC_OK) {
        return load_events_status;
    }

    int load_reminders_status = load_reminders_from_file(REMINDERS_FILE_NAME, reminders, reminders_count, reminders_capacity);

    if (load_reminders_status != LOGIC_OK) {
        return load_reminders_status;
    }

    return LOGIC_OK;
}


void write_event_to_stream(std::ofstream& file, const event_data& event) {
    file
        << event.id << FIELD_SEPARATOR
        << event.title << FIELD_SEPARATOR
        << event.description << FIELD_SEPARATOR
        << event.event_date.year << FIELD_SEPARATOR
        << event.event_date.month << FIELD_SEPARATOR
        << event.event_date.day << FIELD_SEPARATOR
        << event.start_time.hour << FIELD_SEPARATOR
        << event.start_time.minute << FIELD_SEPARATOR
        << event.end_time.hour << FIELD_SEPARATOR
        << event.end_time.minute << FIELD_SEPARATOR
        << event.category << FIELD_SEPARATOR
        << event.priority << FIELD_SEPARATOR
        << event.status
        << '\n';
}


void write_reminder_to_stream(std::ofstream& file, const reminder_data& reminder) {
    file
        << reminder.id << FIELD_SEPARATOR
        << reminder.event_id << FIELD_SEPARATOR
        << reminder.remind_date.year << FIELD_SEPARATOR
        << reminder.remind_date.month << FIELD_SEPARATOR
        << reminder.remind_date.day << FIELD_SEPARATOR
        << reminder.remind_time.hour << FIELD_SEPARATOR
        << reminder.remind_time.minute << FIELD_SEPARATOR
        << reminder.remind_before_minutes << FIELD_SEPARATOR
        << reminder.is_triggered << FIELD_SEPARATOR
        << reminder.message
        << '\n';
}


int parse_event_from_line(const char* line, event_data& event) {
    if (line == nullptr) {
        return LOGIC_ERROR_FILE_READ;
    }

    try {
        std::stringstream stream(line);
        std::string token;

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        event.id = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        std::strncpy(event.title, token.c_str(), EVENT_TITLE_SIZE - 1);
        event.title[EVENT_TITLE_SIZE - 1] = '\0';

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        std::strncpy(event.description, token.c_str(), EVENT_DESCRIPTION_SIZE - 1);
        event.description[EVENT_DESCRIPTION_SIZE - 1] = '\0';

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        event.event_date.year = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        event.event_date.month = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        event.event_date.day = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        event.start_time.hour = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        event.start_time.minute = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        event.end_time.hour = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        event.end_time.minute = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        std::strncpy(event.category, token.c_str(), EVENT_CATEGORY_SIZE - 1);
        event.category[EVENT_CATEGORY_SIZE - 1] = '\0';

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        event.priority = std::stoi(token);

        if (!std::getline(stream, token)) {
            return LOGIC_ERROR_FILE_READ;
        }
        event.status = std::stoi(token);

        if (!is_valid_event_data(event)) {
            return LOGIC_ERROR_FILE_READ;
        }
    } catch (...) {
        return LOGIC_ERROR_FILE_READ;
    }

    return LOGIC_OK;
}


int parse_reminder_from_line(const char* line, reminder_data& reminder) {
    if (line == nullptr) {
        return LOGIC_ERROR_FILE_READ;
    }

    try {
        std::stringstream stream(line);
        std::string token;

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        reminder.id = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        reminder.event_id = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        reminder.remind_date.year = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        reminder.remind_date.month = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        reminder.remind_date.day = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        reminder.remind_time.hour = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        reminder.remind_time.minute = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        reminder.remind_before_minutes = std::stoi(token);

        if (!std::getline(stream, token, FIELD_SEPARATOR)) {
            return LOGIC_ERROR_FILE_READ;
        }
        reminder.is_triggered = std::stoi(token);

        if (!std::getline(stream, token)) {
            return LOGIC_ERROR_FILE_READ;
        }
        std::strncpy(reminder.message, token.c_str(), REMINDER_MESSAGE_SIZE - 1);
        reminder.message[REMINDER_MESSAGE_SIZE - 1] = '\0';

        if (!is_valid_reminder_data(reminder)) {
            return LOGIC_ERROR_FILE_READ;
        }
    } catch (...) {
        return LOGIC_ERROR_FILE_READ;
    }

    return LOGIC_OK;
}