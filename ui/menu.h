#ifndef CALENDAR_APP_UI_MENU_H
#define CALENDAR_APP_UI_MENU_H

#include "../core/types.h"


void run_main_menu(event_data*& events,
                   int& events_count,
                   int& events_capacity,
                   reminder_data*& reminders,
                   int& reminders_count,
                   int& reminders_capacity);

void show_main_menu();

void handle_show_today_events(const event_data* events, int events_count);

void handle_show_events_by_date(const event_data* events, int events_count);

void handle_show_events_by_week(const event_data* events, int events_count);

void handle_create_event(event_data*& events, int& events_count, int& events_capacity);

void handle_edit_event(event_data* events, int events_count);

void handle_delete_event(event_data* events, int& events_count, reminder_data* reminders, int& reminders_count);

void handle_add_reminder(const event_data* events,
                         int events_count,
                         reminder_data*& reminders,
                         int& reminders_count,
                         int& reminders_capacity);

void handle_show_all_reminders(const reminder_data* reminders, int reminders_count);

void handle_check_due_reminders(reminder_data* reminders, int reminders_count);

void handle_search_events(const event_data* events, int events_count);

void handle_show_month_calendar();

void handle_save_data(const event_data* events,
                      int events_count,
                      const reminder_data* reminders,
                      int reminders_count);

#endif