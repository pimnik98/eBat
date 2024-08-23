#include <stdio.h>
#include <ctype.h>
#include "../eBat.h"
#include "../eBatRuntime.h"

int bat_strtol(char *string) {
    int number = 0;
    int sign = 1;
    int i = 0;

    // Пропускаем пробелы в начале строки
    while (string[i] == ' ' && string[i] != '\0') {
        i++;
    }

    // Обработка знака
    if (string[i] == '-' || string[i] == '+') {
        sign = (string[i] == '-' ? -1 : 1);
        i++;
    }

    // Извлечение цифр
    while (isdigit(string[i]) && string[i] != '\0') {
        number = number * 10 + (string[i] - '0');
        i++;
    }

    return number * sign;
}