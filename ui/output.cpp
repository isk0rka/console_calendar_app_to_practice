#include "output.h"

#include "../logic/calendar_logic.h"

#include <iostream>
#include <iomanip>


void print_line_separator() {
    std::cout << "------------------------------------------------------------" << std::endl;
}


void print_empty_line() {
    std::cout << std::endl;
}


void print_date(date_data date) {
    std::cout
        << std::setfill('0')
        << std::setw(2) << date.day << "."
        << std::setw(2) << date.month << "."
        << std::setw(4) << date.year
        << std::setfill(' ');
}


void print_time(time_data time) {
    std::cout
        << std::setfill('0')
        << std::setw(2) << time.hour << ":"
        << std::setw(2) << time.minute
        << std::setfill(' ');
}


void print_event(const event_data& event) {
    print_line_separator();
    std::cout << "ID: " << event.id << std::endl;
    std::cout << "Название: " << event.title << std::endl;
    std::cout << "Описание: " << event.description << std::endl;

    std::cout << "Дата: ";
    print_date(event.event_date);
    std::cout << std::endl;

    std::cout << "Время начала: ";
    print_time(event.start_time);
    std::cout << std::endl;

    std::cout << "Время окончания: ";
    print_time(event.end_time);
    std::cout << std::endl;

    std::cout << "Категория: " << event.category << std::endl;
    std::cout << "Приоритет: " << event.priority << std::endl;
    std::cout << "Статус: " << event.status << std::endl;
}


void print_events_table(const event_data* events, int events_count) {
    if (events == nullptr || events_count <= 0) {
        std::cout << "События не найдены." << std::endl;
        return;
    }

    print_line_separator();
    std::cout
        << std::left
        << std::setw(6)  << "ID"
        << std::setw(16) << "Дата"
        << std::setw(8)  << "Нач."
        << std::setw(8)  << "Кон."
        << std::setw(18) << "Категория"
        << std::setw(12) << "Приор."
        << std::setw(12) << "Статус"
        << "Название"
        << std::endl;

    print_line_separator();

    for (int i = 0; i < events_count; i++) {
        std::cout << std::left << std::setw(6) << events[i].id;

        std::cout << std::setfill('0')
                  << std::setw(2) << events[i].event_date.day << "."
                  << std::setw(2) << events[i].event_date.month << "."
                  << std::setw(4) << events[i].event_date.year
                  << std::setfill(' ');

        std::cout << "   ";

        std::cout << std::setfill('0')
                  << std::setw(2) << events[i].start_time.hour << ":"
                  << std::setw(2) << events[i].start_time.minute
                  << std::setfill(' ');

        std::cout << "  ";

        std::cout << std::setfill('0')
                  << std::setw(2) << events[i].end_time.hour << ":"
                  << std::setw(2) << events[i].end_time.minute
                  << std::setfill(' ');

        std::cout << "  ";

        std::cout
            << std::left
            << std::setw(18) << events[i].category
            << std::setw(12) << events[i].priority
            << std::setw(12) << events[i].status
            << events[i].title
            << std::endl;
    }
}


void print_reminder(const reminder_data& reminder) {
    print_line_separator();
    std::cout << "ID: " << reminder.id << std::endl;
    std::cout << "ID события: " << reminder.event_id << std::endl;

    std::cout << "Дата напоминания: ";
    print_date(reminder.remind_date);
    std::cout << std::endl;

    std::cout << "Время напоминания: ";
    print_time(reminder.remind_time);
    std::cout << std::endl;

    std::cout << "За сколько минут: " << reminder.remind_before_minutes << std::endl;
    std::cout << "Сработало: " << reminder.is_triggered << std::endl;
    std::cout << "Сообщение: " << reminder.message << std::endl;
}


void print_reminders_table(const reminder_data* reminders, int reminders_count) {
    if (reminders == nullptr || reminders_count <= 0) {
        std::cout << "Напоминания не найдены." << std::endl;
        return;
    }

    print_line_separator();
    std::cout
        << std::left
        << std::setw(6)  << "ID"
        << std::setw(10) << "EventID"
        << std::setw(16) << "Дата"
        << std::setw(8)  << "Время"
        << std::setw(12) << "Мин.до"
        << std::setw(12) << "Статус"
        << "Сообщение"
        << std::endl;

    print_line_separator();

    for (int i = 0; i < reminders_count; i++) {
        std::cout << std::left << std::setw(6) << reminders[i].id;
        std::cout << std::setw(10) << reminders[i].event_id;

        std::cout << std::setfill('0')
                  << std::setw(2) << reminders[i].remind_date.day << "."
                  << std::setw(2) << reminders[i].remind_date.month << "."
                  << std::setw(4) << reminders[i].remind_date.year
                  << std::setfill(' ');

        std::cout << "   ";

        std::cout << std::setfill('0')
                  << std::setw(2) << reminders[i].remind_time.hour << ":"
                  << std::setw(2) << reminders[i].remind_time.minute
                  << std::setfill(' ');

        std::cout << "  ";

        std::cout
            << std::left
            << std::setw(12) << reminders[i].remind_before_minutes
            << std::setw(12) << reminders[i].is_triggered
            << reminders[i].message
            << std::endl;
    }
}


const char* get_month_name(int month) {
    switch (month) {
        case 1:
            return "Январь";
        case 2:
            return "Февраль";
        case 3:
            return "Март";
        case 4:
            return "Апрель";
        case 5:
            return "Май";
        case 6:
            return "Июнь";
        case 7:
            return "Июль";
        case 8:
            return "Август";
        case 9:
            return "Сентябрь";
        case 10:
            return "Октябрь";
        case 11:
            return "Ноябрь";
        case 12:
            return "Декабрь";
        default:
            return "Неизвестно";
    }
}


const char* get_weekday_name_short(int weekday) {
    switch (weekday) {
        case 0:
            return "Пн";
        case 1:
            return "Вт";
        case 2:
            return "Ср";
        case 3:
            return "Чт";
        case 4:
            return "Пт";
        case 5:
            return "Сб";
        case 6:
            return "Вс";
        default:
            return "--";
    }
}


void print_month_calendar(int year, int month) {
    int calendar_matrix[6][7];

    build_month_calendar_matrix(year, month, calendar_matrix);

    print_line_separator();
    std::cout << get_month_name(month) << " " << year << std::endl;
    print_line_separator();

    for (int weekday = 0; weekday < 7; weekday++) {
        std::cout << std::setw(4) << get_weekday_name_short(weekday);
    }

    std::cout << std::endl;
    print_line_separator();

    for (int row = 0; row < 6; row++) {
        int has_day = 0;

        for (int column = 0; column < 7; column++) {
            if (calendar_matrix[row][column] != 0) {
                has_day = 1;
                break;
            }
        }

        if (!has_day) {
            continue;
        }

        for (int column = 0; column < 7; column++) {
            if (calendar_matrix[row][column] == 0) {
                std::cout << std::setw(4) << " ";
            } else {
                std::cout << std::setw(4) << calendar_matrix[row][column];
            }
        }

        std::cout << std::endl;
    }
}


void print_week_range(date_data start_date, date_data end_date) {
    std::cout << "Неделя: ";
    print_date(start_date);
    std::cout << " - ";
    print_date(end_date);
    std::cout << std::endl;
}