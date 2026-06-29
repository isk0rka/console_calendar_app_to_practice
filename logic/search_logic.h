#ifndef CALENDAR_APP_LOGIC_SEARCH_LOGIC_H
#define CALENDAR_APP_LOGIC_SEARCH_LOGIC_H

#include "../core/types.h"
#include "../core/constants.h"
#include "../core/datetime_utils.h"


int is_char_equal_ignore_case(char left, char right);

int is_string_equal_ignore_case(const char* left, const char* right);

int contains_substring_ignore_case(const char* text, const char* pattern);

int search_events_by_id(const event_data* source_events,
                        int source_count,
                        int event_id,
                        event_data* result_events,
                        int result_capacity,
                        int& result_count);

int search_events_by_exact_title(const event_data* source_events,
                                 int source_count,
                                 const char* title,
                                 event_data* result_events,
                                 int result_capacity,
                                 int& result_count);

int search_events_by_title_part(const event_data* source_events,
                                int source_count,
                                const char* title_part,
                                event_data* result_events,
                                int result_capacity,
                                int& result_count);

int search_events_by_category(const event_data* source_events,
                              int source_count,
                              const char* category,
                              event_data* result_events,
                              int result_capacity,
                              int& result_count);

int search_events_by_priority(const event_data* source_events,
                              int source_count,
                              int priority,
                              event_data* result_events,
                              int result_capacity,
                              int& result_count);

int search_events_by_status(const event_data* source_events,
                            int source_count,
                            int status,
                            event_data* result_events,
                            int result_capacity,
                            int& result_count);

int search_events_by_date(const event_data* source_events,
                          int source_count,
                          date_data target_date,
                          event_data* result_events,
                          int result_capacity,
                          int& result_count);

int search_events_by_date_range(const event_data* source_events,
                                int source_count,
                                date_data start_date,
                                date_data end_date,
                                event_data* result_events,
                                int result_capacity,
                                int& result_count);

int search_reminders_by_id(const reminder_data* source_reminders,
                           int source_count,
                           int reminder_id,
                           reminder_data* result_reminders,
                           int result_capacity,
                           int& result_count);

int search_reminders_by_event_id(const reminder_data* source_reminders,
                                 int source_count,
                                 int event_id,
                                 reminder_data* result_reminders,
                                 int result_capacity,
                                 int& result_count);

int search_reminders_by_message_part(const reminder_data* source_reminders,
                                     int source_count,
                                     const char* message_part,
                                     reminder_data* result_reminders,
                                     int result_capacity,
                                     int& result_count);

int search_reminders_by_trigger_status(const reminder_data* source_reminders,
                                       int source_count,
                                       int is_triggered,
                                       reminder_data* result_reminders,
                                       int result_capacity,
                                       int& result_count);

#endif