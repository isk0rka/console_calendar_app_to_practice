#include "menu.h"

#include "input.h"
#include "output.h"

#include "../core/constants.h"
#include "../core/validation.h"
#include "../core/datetime_utils.h"
#include "../logic/event_logic.h"
#include "../logic/reminder_logic.h"
#include "../logic/search_logic.h"
#include "../logic/calendar_logic.h"
#include "../storage/file_storage.h"

#include <iostream>
#include <cstring>


int compare_dates_local(date_data left, date_data right) {
    if (left.year != right.year) {
        if (left.year < right.year) {
            return -1;
        }

        return 1;
    }

    if (left.month != right.month) {
        if (left.month < right.month) {
            return -1;
        }

        return 1;
    }

    if (left.day != right.day) {
        if (left.day < right.day) {
            return -1;
        }

        return 1;
    }

    return 0;
}


int compare_times_local(time_data left, time_data right) {
    if (left.hour != right.hour) {
        if (left.hour < right.hour) {
            return -1;
        }

        return 1;
    }

    if (left.minute != right.minute) {
        if (left.minute < right.minute) {
            return -1;
        }

        return 1;
    }

    return 0;
}


void remove_event_by_index_local(event_data* events, int& events_count, int index) {
    if (events == nullptr || index < 0 || index >= events_count) {
        return;
    }

    for (int i = index; i < events_count - 1; i++) {
        events[i] = events[i + 1];
    }

    events_count--;
}


void remove_reminder_by_index_local(reminder_data* reminders, int& reminders_count, int index) {
    if (reminders == nullptr || index < 0 || index >= reminders_count) {
        return;
    }

    for (int i = index; i < reminders_count - 1; i++) {
        reminders[i] = reminders[i + 1];
    }

    reminders_count--;
}


void show_main_menu() {
    print_line_separator();
    std::cout << "КАЛЕНДАРЬ С НАПОМИНАНИЯМИ" << std::endl;
    print_line_separator();
    std::cout << "1. Показать события на сегодня" << std::endl;
    std::cout << "2. Показать события на дату" << std::endl;
    std::cout << "3. Показать события на неделю" << std::endl;
    std::cout << "4. Показать календарь месяца" << std::endl;
    std::cout << "5. Создать событие" << std::endl;
    std::cout << "6. Изменить событие" << std::endl;
    std::cout << "7. Удалить событие" << std::endl;
    std::cout << "8. Добавить напоминание" << std::endl;
    std::cout << "9. Показать все напоминания" << std::endl;
    std::cout << "10. Проверить напоминания" << std::endl;
    std::cout << "11. Поиск событий" << std::endl;
    std::cout << "12. Сохранить данные" << std::endl;
    std::cout << "0. Выход" << std::endl;
    print_line_separator();
    std::cout << "Выберите пункт меню: ";
}


void run_main_menu(event_data*& events,
                   int& events_count,
                   int& events_capacity,
                   reminder_data*& reminders,
                   int& reminders_count,
                   int& reminders_capacity) {
    int choice;

    while (1) {
        print_empty_line();
        show_main_menu();
        choice = read_int_in_range(0, 12);
        print_empty_line();

        switch (choice) {
            case 1:
                handle_show_today_events(events, events_count);
                break;

            case 2:
                handle_show_events_by_date(events, events_count);
                break;

            case 3:
                handle_show_events_by_week(events, events_count);
                break;

            case 4:
                handle_show_month_calendar();
                break;

            case 5:
                handle_create_event(events, events_count, events_capacity);
                break;

            case 6:
                handle_edit_event(events, events_count);
                break;

            case 7:
                handle_delete_event(events, events_count, reminders, reminders_count);
                break;

            case 8:
                handle_add_reminder(events, events_count, reminders, reminders_count, reminders_capacity);
                break;

            case 9:
                handle_show_all_reminders(reminders, reminders_count);
                break;

            case 10:
                handle_check_due_reminders(reminders, reminders_count);
                break;

            case 11:
                handle_search_events(events, events_count);
                break;

            case 12:
                handle_save_data(events, events_count, reminders, reminders_count);
                break;

            case 0:
                handle_save_data(events, events_count, reminders, reminders_count);
                std::cout << "Выход из программы." << std::endl;
                return;
        }

        print_empty_line();
        std::cout << "Нажмите Enter для продолжения...";
        char pause_buffer[8];
        read_line(pause_buffer, 8);
    }
}


void handle_show_today_events(const event_data* events, int events_count) {
    date_data today = get_current_date();

    std::cout << "События на сегодня: ";
    print_date(today);
    std::cout << std::endl;

    if (events_count <= 0) {
        std::cout << "События не найдены." << std::endl;
        return;
    }

    event_data* found_events = new event_data[events_count];
    int found_count = 0;

    int status = get_events_for_day(events, events_count, today, found_events, events_count, found_count);

    if (status != LOGIC_OK) {
        delete[] found_events;
        std::cout << "Ошибка при получении событий." << std::endl;
        return;
    }

    print_events_table(found_events, found_count);
    delete[] found_events;
}


void handle_show_events_by_date(const event_data* events, int events_count) {
    std::cout << "Введите дату (ДД.ММ.ГГГГ): ";
    date_data target_date = read_date_input();

    if (events_count <= 0) {
        std::cout << "События не найдены." << std::endl;
        return;
    }

    event_data* found_events = new event_data[events_count];
    int found_count = 0;

    int status = get_events_for_day(events, events_count, target_date, found_events, events_count, found_count);

    if (status != LOGIC_OK) {
        delete[] found_events;
        std::cout << "Ошибка при поиске событий." << std::endl;
        return;
    }

    std::cout << "События на дату ";
    print_date(target_date);
    std::cout << ":" << std::endl;

    print_events_table(found_events, found_count);
    delete[] found_events;
}


void handle_show_events_by_week(const event_data* events, int events_count) {
    std::cout << "Введите дату внутри недели (ДД.ММ.ГГГГ): ";
    date_data target_date = read_date_input();

    date_data week_start;
    date_data week_end;

    get_week_range(target_date, week_start, week_end);

    if (events_count <= 0) {
        print_week_range(week_start, week_end);
        std::cout << "События не найдены." << std::endl;
        return;
    }

    event_data* found_events = new event_data[events_count];
    int found_count = 0;

    int status = get_events_for_week(events, events_count, target_date, found_events, events_count, found_count);

    if (status != LOGIC_OK) {
        delete[] found_events;
        std::cout << "Ошибка при получении событий недели." << std::endl;
        return;
    }

    print_week_range(week_start, week_end);
    print_events_table(found_events, found_count);
    delete[] found_events;
}


void handle_show_month_calendar() {
    int month;
    int year;

    std::cout << "Введите месяц (1-12): ";
    month = read_int_in_range(1, 12);

    std::cout << "Введите год: ";
    year = read_int_in_range(1, 9999);

    print_month_calendar(year, month);
}


void handle_create_event(event_data*& events, int& events_count, int& events_capacity) {
    event_data new_event;

    std::cout << "Введите ID события: ";
    new_event.id = read_int();

    if (find_event_index_by_id(events, events_count, new_event.id) != -1) {
        std::cout << "Событие с таким ID уже существует." << std::endl;
        return;
    }

    std::cout << "Введите название: ";
    read_text_input_non_empty(new_event.title, EVENT_TITLE_SIZE);

    std::cout << "Введите описание: ";
    read_text_input(new_event.description, EVENT_DESCRIPTION_SIZE);

    std::cout << "Введите дату (ДД.ММ.ГГГГ): ";
    new_event.event_date = read_date_input();

    std::cout << "Введите время начала (ЧЧ:ММ): ";
    new_event.start_time = read_time_input();

    std::cout << "Введите время окончания (ЧЧ:ММ): ";
    new_event.end_time = read_time_input();

    if (compare_times_local(new_event.end_time, new_event.start_time) < 0) {
        std::cout << "Ошибка: время окончания раньше времени начала." << std::endl;
        return;
    }

    std::cout << "Введите категорию: ";
    read_text_input_non_empty(new_event.category, EVENT_CATEGORY_SIZE);

    std::cout << "Введите приоритет: ";
    new_event.priority = read_int();

    std::cout << "Введите статус: ";
    new_event.status = read_int();

    int status = add_event(events, events_count, events_capacity, new_event);

    if (status == LOGIC_OK) {
        std::cout << "Событие успешно добавлено." << std::endl;
    } else {
        std::cout << "Ошибка при добавлении события." << std::endl;
    }
}


void handle_edit_event(event_data* events, int events_count) {
    if (events == nullptr || events_count <= 0) {
        std::cout << "Нет событий для редактирования." << std::endl;
        return;
    }

    int event_id;

    std::cout << "Введите ID события для изменения: ";
    event_id = read_int();

    int index = find_event_index_by_id(events, events_count, event_id);

    if (index == -1) {
        std::cout << "Событие не найдено." << std::endl;
        return;
    }

    std::cout << "Введите новое название: ";
    read_text_input_non_empty(events[index].title, EVENT_TITLE_SIZE);

    std::cout << "Введите новое описание: ";
    read_text_input(events[index].description, EVENT_DESCRIPTION_SIZE);

    std::cout << "Введите новую дату (ДД.ММ.ГГГГ): ";
    events[index].event_date = read_date_input();

    std::cout << "Введите новое время начала (ЧЧ:ММ): ";
    events[index].start_time = read_time_input();

    std::cout << "Введите новое время окончания (ЧЧ:ММ): ";
    events[index].end_time = read_time_input();

    if (compare_times_local(events[index].end_time, events[index].start_time) < 0) {
        std::cout << "Ошибка: время окончания раньше времени начала." << std::endl;
        return;
    }

    std::cout << "Введите новую категорию: ";
    read_text_input_non_empty(events[index].category, EVENT_CATEGORY_SIZE);

    std::cout << "Введите новый приоритет: ";
    events[index].priority = read_int();

    std::cout << "Введите новый статус: ";
    events[index].status = read_int();

    std::cout << "Событие успешно изменено." << std::endl;
}


void handle_delete_event(event_data* events, int& events_count, reminder_data* reminders, int& reminders_count) {
    if (events == nullptr || events_count <= 0) {
        std::cout << "Нет событий для удаления." << std::endl;
        return;
    }

    int event_id;

    std::cout << "Введите ID события для удаления: ";
    event_id = read_int();

    int event_index = find_event_index_by_id(events, events_count, event_id);

    if (event_index == -1) {
        std::cout << "Событие не найдено." << std::endl;
        return;
    }

    remove_event_by_index_local(events, events_count, event_index);

    for (int i = 0; i < reminders_count; ) {
        if (reminders[i].event_id == event_id) {
            remove_reminder_by_index_local(reminders, reminders_count, i);
        } else {
            i++;
        }
    }

    std::cout << "Событие и связанные напоминания удалены." << std::endl;
}


void handle_add_reminder(const event_data* events,
                         int events_count,
                         reminder_data*& reminders,
                         int& reminders_count,
                         int& reminders_capacity) {
    if (events == nullptr || events_count <= 0) {
        std::cout << "Сначала создайте хотя бы одно событие." << std::endl;
        return;
    }

    reminder_data new_reminder;

    std::cout << "Введите ID напоминания: ";
    new_reminder.id = read_int();

    std::cout << "Введите ID события: ";
    new_reminder.event_id = read_int();

    int event_index = find_event_index_by_id(events, events_count, new_reminder.event_id);

    if (event_index == -1) {
        std::cout << "Событие с таким ID не найдено." << std::endl;
        return;
    }

    std::cout << "Введите дату напоминания (ДД.ММ.ГГГГ): ";
    new_reminder.remind_date = read_date_input();

    std::cout << "Введите время напоминания (ЧЧ:ММ): ";
    new_reminder.remind_time = read_time_input();

    std::cout << "Введите за сколько минут напомнить: ";
    new_reminder.remind_before_minutes = read_int();

    new_reminder.is_triggered = 0;

    std::cout << "Введите текст напоминания: ";
    read_text_input_non_empty(new_reminder.message, REMINDER_MESSAGE_SIZE);

    int status = add_reminder(reminders, reminders_count, reminders_capacity, new_reminder);

    if (status == LOGIC_OK) {
        std::cout << "Напоминание успешно добавлено." << std::endl;
    } else {
        std::cout << "Ошибка при добавлении напоминания." << std::endl;
    }
}


void handle_show_all_reminders(const reminder_data* reminders, int reminders_count) {
    print_reminders_table(reminders, reminders_count);
}


void handle_check_due_reminders(reminder_data* reminders, int reminders_count) {
    if (reminders == nullptr || reminders_count <= 0) {
        std::cout << "Напоминания отсутствуют." << std::endl;
        return;
    }

    date_data current_date = get_current_date();
    time_data current_time = get_current_time();
    int found_any = 0;

    for (int i = 0; i < reminders_count; i++) {
        if (reminders[i].is_triggered) {
            continue;
        }

        int is_due = 0;

        if (is_same_date(reminders[i].remind_date, current_date)) {
            if (compare_times_local(reminders[i].remind_time, current_time) <= 0) {
                is_due = 1;
            }
        } else if (compare_dates_local(reminders[i].remind_date, current_date) < 0) {
            is_due = 1;
        }

        if (is_due) {
            found_any = 1;
            reminders[i].is_triggered = 1;

            print_line_separator();
            std::cout << "НАПОМИНАНИЕ!" << std::endl;
            std::cout << "ID: " << reminders[i].id << std::endl;
            std::cout << "Событие ID: " << reminders[i].event_id << std::endl;
            std::cout << "Сообщение: " << reminders[i].message << std::endl;
        }
    }

    if (!found_any) {
        std::cout << "Новых напоминаний нет." << std::endl;
    }
}


void handle_search_events(const event_data* events, int events_count) {
    if (events == nullptr || events_count <= 0) {
        std::cout << "События отсутствуют." << std::endl;
        return;
    }

    std::cout << "Поиск событий:" << std::endl;
    std::cout << "1. По ID" << std::endl;
    std::cout << "2. По точному названию" << std::endl;
    std::cout << "3. По части названия" << std::endl;
    std::cout << "4. По категории" << std::endl;
    std::cout << "5. По дате" << std::endl;
    std::cout << "Выберите вариант: ";

    int search_choice = read_int_in_range(1, 5);

    event_data* result_events = new event_data[events_count];
    int result_count = 0;
    int status = LOGIC_OK;

    if (search_choice == 1) {
        int event_id;

        std::cout << "Введите ID: ";
        event_id = read_int();

        status = search_events_by_id(events, events_count, event_id, result_events, events_count, result_count);
    } else if (search_choice == 2) {
        char title[EVENT_TITLE_SIZE];

        std::cout << "Введите точное название: ";
        read_text_input_non_empty(title, EVENT_TITLE_SIZE);

        status = search_events_by_exact_title(events, events_count, title, result_events, events_count, result_count);
    } else if (search_choice == 3) {
        char title_part[EVENT_TITLE_SIZE];

        std::cout << "Введите часть названия: ";
        read_text_input_non_empty(title_part, EVENT_TITLE_SIZE);

        status = search_events_by_title_part(events, events_count, title_part, result_events, events_count, result_count);
    } else if (search_choice == 4) {
        char category[EVENT_CATEGORY_SIZE];

        std::cout << "Введите категорию: ";
        read_text_input_non_empty(category, EVENT_CATEGORY_SIZE);

        status = search_events_by_category(events, events_count, category, result_events, events_count, result_count);
    } else if (search_choice == 5) {
        date_data target_date;

        std::cout << "Введите дату (ДД.ММ.ГГГГ): ";
        target_date = read_date_input();

        status = search_events_by_date(events, events_count, target_date, result_events, events_count, result_count);
    }

    if (status != LOGIC_OK) {
        delete[] result_events;
        std::cout << "Ошибка при поиске событий." << std::endl;
        return;
    }

    print_events_table(result_events, result_count);
    delete[] result_events;
}


void handle_save_data(const event_data* events,
                      int events_count,
                      const reminder_data* reminders,
                      int reminders_count) {
    int status = save_all_data(events, events_count, reminders, reminders_count);

    if (status == LOGIC_OK) {
        std::cout << "Данные успешно сохранены." << std::endl;
    } else {
        std::cout << "Ошибка при сохранении данных." << std::endl;
    }
}