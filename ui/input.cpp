#include "input.h"

#include "../core/validation.h"

#include <iostream>
#include <cstring>
#include <limits>
#include <sstream>


void clear_input_buffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void read_line(char* buffer, int buffer_size) {
    if (buffer == nullptr || buffer_size <= 0) {
        return;
    }

    std::cin.getline(buffer, buffer_size);

    if (std::cin.fail()) {
        clear_input_buffer();
        buffer[0] = '\0';
    }
}


int is_empty_input(const char* text) {
    if (text == nullptr) {
        return 1;
    }

    int length = static_cast<int>(std::strlen(text));

    for (int i = 0; i < length; i++) {
        if (text[i] != ' ' && text[i] != '\t' && text[i] != '\n' && text[i] != '\r') {
            return 0;
        }
    }

    return 1;
}


int parse_int_from_text(const char* text, int& value) {
    if (text == nullptr) {
        return 0;
    }

    std::stringstream stream(text);
    int parsed_value;
    char extra_character;

    if (!(stream >> parsed_value)) {
        return 0;
    }

    if (stream >> extra_character) {
        return 0;
    }

    value = parsed_value;

    return 1;
}


int read_int() {
    char buffer[128];
    int value;

    while (1) {
        read_line(buffer, 128);

        if (parse_int_from_text(buffer, value)) {
            return value;
        }

        std::cout << "Ошибка: введите целое число: ";
    }
}


int read_int_in_range(int min_value, int max_value) {
    int value;

    while (1) {
        value = read_int();

        if (value >= min_value && value <= max_value) {
            return value;
        }

        std::cout << "Ошибка: введите число от " << min_value << " до " << max_value << ": ";
    }
}


void read_text_input(char* buffer, int buffer_size) {
    if (buffer == nullptr || buffer_size <= 0) {
        return;
    }

    while (1) {
        read_line(buffer, buffer_size);

        if (!std::cin.fail()) {
            return;
        }

        std::cout << "Ошибка ввода. Повторите: ";
    }
}


void read_text_input_non_empty(char* buffer, int buffer_size) {
    if (buffer == nullptr || buffer_size <= 0) {
        return;
    }

    while (1) {
        read_text_input(buffer, buffer_size);

        if (!is_empty_input(buffer)) {
            return;
        }

        std::cout << "Ошибка: пустой ввод. Повторите: ";
    }
}


date_data read_date_input() {
    date_data date;
    char buffer[128];
    int day;
    int month;
    int year;
    char separator1;
    char separator2;

    while (1) {
        read_line(buffer, 128);

        std::stringstream stream(buffer);

        if ((stream >> day >> separator1 >> month >> separator2 >> year) &&
            separator1 == '.' &&
            separator2 == '.') {
            date.day = day;
            date.month = month;
            date.year = year;

            if (is_valid_date(date)) {
                return date;
            }
        }

        std::cout << "Ошибка: введите дату в формате ДД.ММ.ГГГГ: ";
    }
}


time_data read_time_input() {
    time_data time;
    char buffer[128];
    int hour;
    int minute;
    char separator;

    while (1) {
        read_line(buffer, 128);

        std::stringstream stream(buffer);

        if ((stream >> hour >> separator >> minute) &&
            separator == ':') {
            time.hour = hour;
            time.minute = minute;

            if (is_valid_time(time)) {
                return time;
            }
        }

        std::cout << "Ошибка: введите время в формате ЧЧ:ММ: ";
    }
}


int read_yes_no_input() {
    char buffer[16];

    while (1) {
        read_line(buffer, 16);

        if (std::strcmp(buffer, "y") == 0 ||
            std::strcmp(buffer, "Y") == 0 ||
            std::strcmp(buffer, "yes") == 0 ||
            std::strcmp(buffer, "YES") == 0 ||
            std::strcmp(buffer, "1") == 0 ||
            std::strcmp(buffer, "д") == 0 ||
            std::strcmp(buffer, "Д") == 0) {
            return 1;
        }

        if (std::strcmp(buffer, "n") == 0 ||
            std::strcmp(buffer, "N") == 0 ||
            std::strcmp(buffer, "no") == 0 ||
            std::strcmp(buffer, "NO") == 0 ||
            std::strcmp(buffer, "0") == 0 ||
            std::strcmp(buffer, "н") == 0 ||
            std::strcmp(buffer, "Н") == 0) {
            return 0;
        }

        std::cout << "Ошибка: введите y/n: ";
    }
}