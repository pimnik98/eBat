#include <stdio.h>
#include "../../eBat.h"
#include "../../eBatRuntime.h"

int bar_runtime_system_exec(int argc, char** argv){
    /// Insert your code to execute the "echo" command
    bat_debug("[RUNTIME] [System] [EXEC] Count: %d\n", argc);
    for (int i = 0; i < argc; i++){
        printf("[%d | %d] '%s'\n", i + 1, argc, argv[i]);
    }
}

/**
 * Вывод текста на экран
 * @module System.Echo
 * @param text - Строка для вывода текст
 */
void bat_runtime_system_echo(char* text){
    /// Insert your code to execute the "echo" command
    bat_debug("[RUNTIME] [System] [ECHO] %s\n", text);
}

/**
 * Установка значения переменной
 * @param key - Ключ
 * @param val - Значение
 */
void bat_runtime_system_set(char* key, char* val){
    /// Insert your code
    bat_debug("[RUNTIME] [System] [SET] '%s' => '%s'\n", key, val);
}

/**
 * Получение значения переменной
 * @param key - Ключ
 */
char* bat_runtime_system_get(char* key){
    /// Insert your code
    bat_debug("[RUNTIME] [System] [GET] '%s'\n", key);
    return NULL;
}