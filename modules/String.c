#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../eBat.h"
#include "../eBatRuntime.h"
#include <stdlib.h>

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
    bat_debug("      |--- String debug: '%s'\n", string);
    int len = strlen(string);
    for (int i = 0; i < len; i++){
        bat_debug("        |--- [%d | %d] [0x%x] '%c'\n", i+1, len, string[i], string[i]);
    }
}

char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        bat_debug("Error opening file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* file_content = malloc(file_size + 1); // +1 для завершающего нулевого символа
    memset(file_content, 0, (file_size + 1));
    if (file_content == NULL) {
        bat_debug("Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    int read = fread(file_content, 1, file_size, file);
    if (read == 0){
        bat_debug("[READ] Error!\n");
    }
    file_content[file_size] = '\0';
    fclose(file);

    return file_content;
}
int str_cdsp2(const char* a_str, char del){
    int x = 0;
    for(size_t i = 0, len = strlen(a_str); i < len; i++){
        if (a_str[i] == del) {
            x++;
        }
    }
    return x;
}
char** explode(const char str[], char delimiter) {
    int ccc = str_cdsp2(str, delimiter);
    char** result = malloc(strlen(str)*2);
    int y = 0;
    int a = 0;

    for (int b = 0; b <= ccc; b++) {
        result[b] = malloc(strlen(str) * sizeof(char));
    }

    for (int i = 0; i < strlen(str); i++){
        if (str[i] == delimiter){
            result[a][y] = 0;
            a++;
            y = 0;
            continue;
        }
        result[a][y] = str[i];
        y++;
    }

    result[a][y] = 0;
    return result;
}

char* bat_toLower(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}