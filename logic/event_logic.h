#ifndef CALENDAR_APP_LOGIC_EVENT_LOGIC_H
#define CALENDAR_APP_LOGIC_EVENT_LOGIC_H

#include "../core/types.h"
#include "../core/constants.h"
#include "../core/validation.h"
#include "../core/datetime_utils.h"

int expand_events_array(event_data*& events, int& capacity);

int add_event(event_data*& events, int& events_count, int& capacity, const event_data& new_event);

int find_event_index_by_id(const event_data* events, int events_count, int event_id);

int is_event_exists_by_id(const event_data* events, int events_count, int event_id);

int delete_event_by_id(event_data* events, int& events_count, int event_id);

int update_event_by_id(event_data* events, int events_count, int event_id, const event_data& updated_event);

event_data* find_event_by_id(event_data* events, int events_count, int event_id);

const event_data* find_event_by_id_const(const event_data* events, int events_count, int event_id);

void sort_events_by_datetime(event_data* events, int events_count);

void sort_events_by_priority(event_data* events, int events_count);

void sort_events_by_title(event_data* events, int events_count);

void swap_events(event_data& left, event_data& right);

int count_events_by_date(const event_data* events, int events_count, date_data target_date);

int count_events_in_date_range(const event_data* events, int events_count, date_data start_date, date_data end_date);

int get_events_by_date(const event_data* source_events,
                       int source_count,
                       date_data target_date,
                       event_data* result_events,
                       int result_capacity,
                       int& result_count);

int get_events_in_date_range(const event_data* source_events,
                             int source_count,
                             date_data start_date,
                             date_data end_date,
                             event_data* result_events,
                             int result_capacity,
                             int& result_count);

int find_events_by_title(const event_data* source_events,
                         int source_count,
                         const char* title,
                         event_data* result_events,
                         int result_capacity,
                         int& result_count);

int mark_event_as_done(event_data* events, int events_count, int event_id);

int mark_event_as_canceled(event_data* events, int events_count, int event_id);

int get_next_event_id(const event_data* events, int events_count);

#endif