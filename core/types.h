#ifndef CALENDAR_APP_CORE_TYPES_H
#define CALENDAR_APP_CORE_TYPES_H
#include "constants.h"

struct date_data
{
    int year;
    int month;
    int day;
};

struct time_data
{
    int hour;
    int minute;
};

enum event_status
{
    EVENT_STATUS_PLANNED = 1,
    EVENT_STATUS_DONE = 2,
    EVENT_STATUS_CANCELED = 3
};

enum event_priority
{
    EVENT_PRIORITY_LOW = 1,
    EVENT_PRIORITY_MEDIUM = 2,
    EVENT_PRIORITY_HIGH = 3
};

struct event_data
{
    int id;

    char title[EVENT_TITLE_SIZE];
    char description[EVENT_DESCRIPTION_SIZE];

    date_data event_date;
    time_data start_time;
    time_data end_time;

    char category[EVENT_CATEGORY_SIZE];

    int priority;
    int status;
};

struct reminder_data
{
    int id;
    int event_id;

    date_data remind_date;
    time_data remind_time;

    int remind_before_minutes;
    int is_triggered;

    char message[REMINDER_MESSAGE_SIZE];
};

struct calendar_storage
{
    event_data* events;
    int events_count;
    int events_capacity;

    reminder_data* reminders;
    int reminders_count;
    int reminders_capacity;

    int next_event_id;
    int next_reminder_id;
};

struct app_context
{
    calendar_storage storage;
    int is_running;
};

#endif