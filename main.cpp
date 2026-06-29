#include <iostream>

#include "core/types.h"
#include "core/constants.h"
#include "storage/file_storage.h"
#include "ui/menu.h"


int main() {
    event_data* events = nullptr;
    reminder_data* reminders = nullptr;

    int events_count = 0;
    int reminders_count = 0;

    int events_capacity = INITIAL_EVENTS_CAPACITY;
    int reminders_capacity = INITIAL_REMINDERS_CAPACITY;

    events = new event_data[events_capacity];
    reminders = new reminder_data[reminders_capacity];

    if (events == nullptr || reminders == nullptr) {
        std::cout << "Ошибка: не удалось выделить память." << std::endl;

        delete[] events;
        delete[] reminders;
        return 1;
    }

    int load_status = load_all_data(events,
                                    events_count,
                                    events_capacity,
                                    reminders,
                                    reminders_count,
                                    reminders_capacity);

    if (load_status == LOGIC_OK) {
        std::cout << "Данные успешно загружены." << std::endl;
    } else {
        std::cout << "Не удалось загрузить данные. Будет создана пустая рабочая сессия." << std::endl;
    }

    run_main_menu(events,
                  events_count,
                  events_capacity,
                  reminders,
                  reminders_count,
                  reminders_capacity);

    int save_status = save_all_data(events, events_count, reminders, reminders_count);

    if (save_status == LOGIC_OK) {
        std::cout << "Данные успешно сохранены." << std::endl;
    } else {
        std::cout << "Ошибка при сохранении данных." << std::endl;
    }

    delete[] events;
    delete[] reminders;

    events = nullptr;
    reminders = nullptr;

    return 0;
}