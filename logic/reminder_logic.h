#ifndef CALENDAR_APP_LOGIC_REMINDER_LOGIC_H
#define CALENDAR_APP_LOGIC_REMINDER_LOGIC_H

#include "../core/types.h"
#include "../core/constants.h"
#include "../core/validation.h"
#include "../core/datetime_utils.h"
#include "event_logic.h"


int expand_reminders_array(reminder_data*& reminders, int& capacity);

int add_reminder(reminder_data*& reminders, int& reminders_count, int& capacity, const reminder_data& new_reminder);

int find_reminder_index_by_id(const reminder_data* reminders, int reminders_count, int reminder_id);

int is_reminder_exists_by_id(const reminder_data* reminders, int reminders_count, int reminder_id);

int delete_reminder_by_id(reminder_data* reminders, int& reminders_count, int reminder_id);

int update_reminder_by_id(reminder_data* reminders, int reminders_count, int reminder_id, const reminder_data& updated_reminder);

reminder_data* find_reminder_by_id(reminder_data* reminders, int reminders_count, int reminder_id);

const reminder_data* find_reminder_by_id_const(const reminder_data* reminders, int reminders_count, int reminder_id);

void swap_reminders(reminder_data& left, reminder_data& right);

void sort_reminders_by_datetime(reminder_data* reminders, int reminders_count);

int count_due_reminders(const reminder_data* reminders,
                        int reminders_count,
                        date_data current_date,
                        time_data current_time);

int get_due_reminders(const reminder_data* source_reminders,
                      int source_count,
                      date_data current_date,
                      time_data current_time,
                      reminder_data* result_reminders,
                      int result_capacity,
                      int& result_count);

int mark_reminder_as_triggered(reminder_data* reminders, int reminders_count, int reminder_id);

int mark_all_due_reminders_as_triggered(reminder_data* reminders,
                                        int reminders_count,
                                        date_data current_date,
                                        time_data current_time);

int get_reminders_by_event_id(const reminder_data* source_reminders,
                              int source_count,
                              int event_id,
                              reminder_data* result_reminders,
                              int result_capacity,
                              int& result_count);

int delete_reminders_by_event_id(reminder_data* reminders, int& reminders_count, int event_id);

int get_next_reminder_id(const reminder_data* reminders, int reminders_count);

int is_reminder_linked_event_valid(const event_data* events,
                                   int events_count,
                                   const reminder_data& reminder);

#endif