#include <stdio.h>
#include <string.h>
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
void bat_trim(char* string){
    int start = 0, end = strlen(string) - 1;
    while (string[start] == ' ' || string[start] == '\t' || string[start] == '\n' || string[start] == 0xD){
        start++;
    }
    while (string[end] == ' ' || string[end] == '\t' || string[end] == '\n' || string[end] == 0xD){
        end--;
    }
    for (int i = 0; i <= end - start; i++){
        string[i] = string[i + start];
    }
    string[end - start + 1] = '\0';
}

void bat_str_debug(char* string){
    printf("      |--- String debug: '%s'\n", string);
    int len = strlen(string);
    for (int i = 0; i < len; i++){
        printf("        |--- [%d | %d] [0x%x] '%c'\n", i+1, len, string[i], string[i]);
    }
}