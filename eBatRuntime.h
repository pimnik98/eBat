#ifndef EBAT_RUNTIME_H
#define EBAT_RUNTIME_H

/////////////////////////
/// Поле конфигурации eBR
#define EBAT_CONFIG_HELLO_LINE      ">"     ///< Строка приглашения для вывода команд (при echo on) пробел ставится автоматический
#define EBAT_CONFIG_CRITICAL_STOP   1       ///< Остановить выполнение скрипта, при наличии ошибок (Рекомендуется оставить 1)
#define EBAT_CONFIG_FILEIO_EXIST    1       ///< Настроен FileIO.Exist (Проверка наличия файла или папки)
#define EBAT_CONFIG_SYSTEM_SET      1       ///< Настроен System.Set (Получение и установка окружения системы)


/////////////////////////


#define EBAT_INVALIDARGC(Line, Cur, Req) \
    if (Cur != Req){                                \
        bat_fatalerror(Line, "Check the number of arguments! Current %d, required %d.", Cur, Req);\
        return 1;                   \
    }\

#define EBAT_INVALIDMINARGC(Line, Cur, Req) \
    if (Cur < Req){                                \
        bat_fatalerror(Line, "Not enough arguments! Current %d, required %d.", Cur, Req);\
        return 2;                   \
    } \

#define eBatCheckModule(Line, Module, ModuleName) \
    if (Module != 1){                                \
        bat_fatalerror(Line, "The module \"%s\" is not built for eBat.", ModuleName);\
        return 3;                   \
    }\

#define eBatCheckMixingData(Line, Cur, Req) \
    if (Cur != Req){                   \
        bat_fatalerror(Line, "Data type mismatch. \"%s\" Received, \"%s\" Required", bat_debug_type(Cur), bat_debug_type(Req)); \
        return 4;                                   \
    }

#define eBatCheckInputValue(Line) \
    bat_fatalerror(Line, "You cannot compare different types of data. Only NUMBERS and VARIABLES are allowed to be compared."); \
    return 5;                                   \

#define eBatCheckVariable(Line, Key, Var) \
    char* Var = bat_runtime_system_get(Key);    \
    if (Var == NULL){                 \
        bat_fatalerror(Line, "The variable \"%s\" was not found.", Key); \
        return 6;                         \
    }

#define eBatCheckGoTo(Line, Key) \
    if (Key == NULL){            \
        bat_fatalerror(Line, "The goto \"%s\" was not found.", Key); \
        return 7;   \
    }

int bat_runtime_system_cls();
void bat_runtime_system_echo(char* text);
void bat_runtime_system_set(char* key, char* val);
char* bat_runtime_system_get(char* key);

int bat_runtime_fileio_exist(char* path);

int bat_strtol(char *string);
void bat_trim(char* string);
void bat_str_debug(char* string);
char* bat_toLower(char* str);
char** explode(const char str[], char delimiter);
int str_cdsp2(const char* a_str, char del);
char* readFile(const char* filename);

#endif //EBAT_RUNTIME_H
