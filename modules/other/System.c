#include <stdio.h>
#include "../../eBat.h"
#include "../../eBatRuntime.h"

int bar_runtime_system_exec(int argc, char** argv){
    /// Insert your code to execute the "echo" command
    bat_debug("[RUNTIME] [System] [EXEC] Count: %d\n", argc);
    for (int i = 0; i < argc; i++){
        printf("[%d | %d] '%s'\n", i + 1, argc, argv[i]);
    }
    return 0;
}

/**
 * Вывод текста на экран
 * @module System.Echo
 * @param text - Строка для вывода текст
 */
void bat_runtime_system_echo(char* text, int newline, int endline){
    /// Insert your code to execute the "echo" command
    bat_debug("[RUNTIME] [System] [ECHO] %s\n", text);
    if (text == NULL){
        return;
    }

    printf("%s%s%s", (newline == 1?"< ":""), text, (endline == 1?" \n":" "));
}

/**
 * Установка значения переменной
 * @param key - Ключ
 * @param val - Значение
 */
void bat_runtime_system_set(char* key, char* val){
    /// Insert your code
    bat_debug("[RUNTIME] [System] [SET] '%s' => '%s'\n", key, val);

    bat_toUpper(key);
}

/**
 * Получение значения переменной
 * @param key - Ключ
 */
char* bat_runtime_system_get(char* key){
    /// Insert your code
    bat_debug("[RUNTIME] [System] [GET] '%s'\n", key);
    bat_toUpper(key);
    return NULL;
}


void bat_runtime_system_pause(){
    /// Insert your code
    bat_debug("[RUNTIME] [System] [Pause]\n");
    bat_runtime_system_echo("Please, press button", 1, 1);

    ///getchar(); - Функция которая ожидает ввода любой клавиши
}