#ifndef CALENDAR_APP_STORAGE_FILE_STORAGE_H
#define CALENDAR_APP_STORAGE_FILE_STORAGE_H

#include "../core/types.h"
#include "../core/constants.h"

#include <fstream>


int ensure_data_files_exist();

int save_events_to_file(const char* file_name, const event_data* events, int events_count);

int load_events_from_file(const char* file_name, event_data*& events, int& events_count, int& capacity);

int save_reminders_to_file(const char* file_name, const reminder_data* reminders, int reminders_count);

int load_reminders_from_file(const char* file_name, reminder_data*& reminders, int& reminders_count, int& capacity);

int save_all_data(const event_data* events,
                  int events_count,
                  const reminder_data* reminders,
                  int reminders_count);

int load_all_data(event_data*& events,
                  int& events_count,
                  int& events_capacity,
                  reminder_data*& reminders,
                  int& reminders_count,
                  int& reminders_capacity);

void write_event_to_stream(std::ofstream& file, const event_data& event);

void write_reminder_to_stream(std::ofstream& file, const reminder_data& reminder);

int parse_event_from_line(const char* line, event_data& event);

int parse_reminder_from_line(const char* line, reminder_data& reminder);

#endif