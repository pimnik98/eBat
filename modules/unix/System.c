#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../eBat.h"
#include "../../eBatRuntime.h"

typedef struct BAT_SET {
    int State;
    char key[256];
    char val[4096];
} BAT_SET_T;

BAT_SET_T __bat_set_data__[256] = {0};

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
    if (text == NULL){
        return;
    }

    //printf("[RUNTIME] [System] [ECHO] [0x%x] '%s'\n", text[0], text);
    printf("%s%s%s", (newline == 1?"< ":""), text, (endline == 1?" \n":" "));
}


/**
 * Получение значения переменной
 * @param key - Ключ
 */
char* bat_runtime_system_get(char* key){
    /// Insert your code
    //bat_debug("[RUNTIME] [System] [GET] '%s'\n", key);
    //printf("[RUNTIME] [System] [GET] '%s'\n", key);
    for (int i = 0; i < 256; i++){
        if (__bat_set_data__[i].State != 1) continue;
        if (strcmp(__bat_set_data__[i].key, key) == 0){
            int len = strlen(__bat_set_data__[i].val);
            char* temp = malloc(len + 1);
            memset(temp, 0, len + 1);
            memcpy(temp, __bat_set_data__[i].val, len);
            return temp;
        }
    }
    return NULL;
}

/**
 * Установка значения переменной
 * @param key - Ключ
 * @param val - Значение
 */
void bat_runtime_system_set(char* key, char* val){
    /// Insert your code
    //bat_debug("[RUNTIME] [System] [SET] '%s' => '%s'\n", key, val);
    //printf("[RUNTIME] [System] [SET] '%s' => '%s'\n", key, val);

    char* get = bat_runtime_system_get(key);

    int len_key = (key == NULL?0:strlen(key));
    int len_val = (val == NULL?0:strlen(val));

    if (get == NULL){
        if (val == NULL) return;
        for (int i = 0; i < 256; i++){
            if (__bat_set_data__[i].State == 1) continue;
            memset(__bat_set_data__[i].key, 0, 256);
            memset(__bat_set_data__[i].val, 0, 4096);

            memcpy(__bat_set_data__[i].key, key, (len_key > 255?255:len_key));
            memcpy(__bat_set_data__[i].val, val, (len_val > 4096?4096:len_val));

            __bat_set_data__[i].State = 1;
            break;
        }
    } else {
        for (int i = 0; i < 256; i++){
            if (__bat_set_data__[i].State != 1) continue;
            if (strcmp(__bat_set_data__[i].key, key) == 0){
                if (val == NULL) {
                    __bat_set_data__[i].State = 0;
                    break;
                }
                memset(__bat_set_data__[i].val, 0, 4096);
                memcpy(__bat_set_data__[i].val, val, (len_val > 4096?4096:len_val));
                __bat_set_data__[i].State = 1;
                break;
            }
        }
    }
    free(get);
}

void bat_runtime_system_pause(){
    /// Insert your code
    bat_debug("[RUNTIME] [System] [Pause]\n");
    bat_runtime_system_echo("Please, press button", 1, 1);

    getchar();
}