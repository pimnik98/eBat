#ifndef EBAT_H
#define EBAT_H

#include <stdarg.h>
#define bat_fatalerror(Line, M, ...) \
    printf("\033[31;1mError on line %d: " M "\033[0m\n", Line, ##__VA_ARGS__)



typedef enum {
    BEC_OK = 0,     /// Все норм
    BEC_MEMORY = 1, /// Недостаточно памяти
} BAT_ERROR_CODE;

typedef enum {
    BAT_TOKEN_TYPE_ECHO,            ///< Выводит текст
    BAT_TOKEN_TYPE_IF,              ///< Условия IF
    BAT_TOKEN_TYPE_SET,             ///< Установка данных переменных
    BAT_TOKEN_TYPE_TRUE,            ///< Флаг Правды
    BAT_TOKEN_TYPE_FALSE,           ///< Флаг лжы
    BAT_TOKEN_TYPE_EXIT,            ///< Выход

    BAT_TOKEN_TYPE_NOT,             ///< Условия для IF | Условие не равно
    BAT_TOKEN_TYPE_EXIST,           ///< Условия для IF | Существует файл или папка
    BAT_TOKEN_TYPE_ISSET,           ///< Условия для IF | Существует ли переменная
    // Операторы сравнения
    BAT_TOKEN_TYPE_EQUAL,           ///< Оператор сравнения ==
    BAT_TOKEN_TYPE_NOT_EQUAL,       ///< Оператор сравнения !=
    BAT_TOKEN_TYPE_GREATER,         ///< Оператор сравнения >
    BAT_TOKEN_TYPE_LESS,            ///< Оператор сравнения <
    BAT_TOKEN_TYPE_LESS_EQUAL,      ///< Оператор сравнения <=
    BAT_TOKEN_TYPE_GREATER_EQUAL,   ///< Оператор сравнения >=

    BAT_TOKEN_TYPE_STRING,          ///< Тип данных строка
    BAT_TOKEN_TYPE_NUMBER,          ///< Тип данных число
    BAT_TOKEN_TYPE_OPERATOR,        ///< Тип данных оператор
    BAT_TOKEN_TYPE_VARIABLE,        ///< Тип данных переменная
    BAT_TOKEN_TYPE_UNKNOWN          ///< Тип данных неизвестно
} BAT_TOKEN_TYPE;


typedef struct BAT_TOKEN {
    BAT_TOKEN_TYPE type;
    char* value;
} BAT_TOKEN_T;

typedef struct BAT_GROUP {
    int Size;
    int Capacity;
    size_t* Tokens;
} BAT_GROUP_T;

typedef struct BAT {
    int Echo;
    int ErrorCode;
    int Size;
    int Capacity;
    size_t* Group;
} BAT_T;

char* bat_toLower(char* str);
BAT_T* bat_create_session();
void bat_add_token(BAT_GROUP_T* bat, size_t element);
BAT_TOKEN_T* bat_create_token(BAT_TOKEN_TYPE type, char* value);
char* bat_debug_type(BAT_TOKEN_TYPE Type);
BAT_TOKEN_TYPE bat_parse_token(char* str);
BAT_GROUP_T* bat_parse_line(BAT_T* bat, char* Line);
BAT_T* bat_parse_string(char* String);

#endif //EBAT_H
