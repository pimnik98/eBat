#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "eBat.h"

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

BAT_T* bat_create_session(){
    BAT_T* bat = calloc(1, sizeof *bat);
    if(!bat) {
        return 0;
    }
    bat->Group = calloc(1, sizeof(size_t));
    if(!bat->Group) {
        free(bat);

        return 0;
    }
    bat->Size = 0;
    bat->Capacity = 1;
    return bat;
}
BAT_GROUP_T* bat_create_group(){
    BAT_GROUP_T* group = calloc(1, sizeof *group);
    if(!group) {
        return 0;
    }
    group->Tokens = calloc(1, sizeof(size_t));
    if(!group->Tokens) {
        free(group);

        return 0;
    }
    group->Size = 0;
    group->Capacity = 1;
    return group;
}
void bat_add_group(BAT_T * bat, size_t element) {
    if(bat->Size >= bat->Capacity) {
        size_t new_cap = bat->Capacity + ((bat->Capacity + 1) / 2);
        void* new_buf = realloc(bat->Group, sizeof(size_t) * new_cap);

        if(!new_buf)
            return;

        bat->Group = new_buf;
        bat->Capacity = new_cap;
    }
    bat->Group[bat->Size++] = element;
}
void bat_add_token(BAT_GROUP_T* bat, size_t element) {
    if(bat->Size >= bat->Capacity) {
        size_t new_cap = bat->Capacity + ((bat->Capacity + 1) / 2);
        void* new_buf = realloc(bat->Tokens, sizeof(size_t) * new_cap);

        if(!new_buf)
            return;

        bat->Tokens = new_buf;
        bat->Capacity = new_cap;
    }
    bat->Tokens[bat->Size++] = element;
}
BAT_TOKEN_T* bat_create_token(BAT_TOKEN_TYPE type, char* value) {
    BAT_TOKEN_T* token = malloc(sizeof(BAT_TOKEN_T));
    if (token == 0){
        return NULL;
    }
    memset(token, 0, sizeof(BAT_TOKEN_T));
    token->type = type;

    token->value = malloc(strlen(value)+1);
    memset(token->value, 0, strlen(value)+1);
    memcpy(token->value, value, strlen(value));

    //bat_fatalerror(0, "Get: '%s'\nIns: '%s'\n",token->value,value);
    return token;
}
char* bat_debug_type(BAT_TOKEN_TYPE Type){
    switch (Type) {
        case BAT_TOKEN_TYPE_ECHO: return "ECHO";
        case BAT_TOKEN_TYPE_IF: return "IF";
        case BAT_TOKEN_TYPE_SET: return "SET";
        case BAT_TOKEN_TYPE_TRUE: return "TRUE";
        case BAT_TOKEN_TYPE_FALSE: return "FALSE";

        case BAT_TOKEN_TYPE_NOT: return "NOT";
        case BAT_TOKEN_TYPE_EXIST: return "EXIST";
        case BAT_TOKEN_TYPE_ISSET: return "ISSET";

        case BAT_TOKEN_TYPE_STRING: return "STRING";
        case BAT_TOKEN_TYPE_NUMBER: return "NUMBER";

        case BAT_TOKEN_TYPE_OPERATOR: return "OPERATOR";
        case BAT_TOKEN_TYPE_EQUAL: return "EQUAL";
        case BAT_TOKEN_TYPE_NOT_EQUAL: return "NOT_EQUAL";
        case BAT_TOKEN_TYPE_GREATER: return "GREATER";
        case BAT_TOKEN_TYPE_LESS: return "LESS";
        case BAT_TOKEN_TYPE_LESS_EQUAL: return "LESS_EQUAL";
        case BAT_TOKEN_TYPE_GREATER_EQUAL: return "GREATER_EQUAL";

        case BAT_TOKEN_TYPE_EXIT: return "EXIT";
        default: return "VARIABLE";
    }
}
// Функция для определения типа лексемы
BAT_TOKEN_TYPE bat_parse_token(char* str) {
    bat_trim(str);
    str = bat_toLower(str);
    bat_str_debug(str);

    if (strcmp(str, "echo") == 0) return BAT_TOKEN_TYPE_ECHO;
    if (strcmp(str, "if") == 0) return BAT_TOKEN_TYPE_IF;
    if (strcmp(str, "set") == 0) return BAT_TOKEN_TYPE_SET;
    if (strcmp(str, "=") == 0) return BAT_TOKEN_TYPE_SET;
    if (strcmp(str, "isset") == 0) return BAT_TOKEN_TYPE_ISSET;
    if (strcmp(str, "debug") == 0) return BAT_TOKEN_TYPE_DEBUG;

    if (strcmp(str, "rem") == 0) return BAT_TOKEN_TYPE_COMMENT;
    if (strcmp(str, "::") == 0)  return BAT_TOKEN_TYPE_COMMENT;

    if (strcmp(str, "on") == 0 || strcmp(str, "true") == 0 || strcmp(str, "enabled") == 0) return BAT_TOKEN_TYPE_TRUE;
    if (strcmp(str, "off") == 0 || strcmp(str, "false") == 0 || strcmp(str, "disabled") == 0) return BAT_TOKEN_TYPE_FALSE;


    if (strcmp(str, "not") == 0) return BAT_TOKEN_TYPE_NOT;
    if (strcmp(str, "exist") == 0) return BAT_TOKEN_TYPE_EXIST;
    if (strcmp(str, "exit") == 0) return BAT_TOKEN_TYPE_EXIT;

    if (strcmp(str, "==") == 0) return BAT_TOKEN_TYPE_EQUAL;
    if (strcmp(str, "!=") == 0) return BAT_TOKEN_TYPE_NOT_EQUAL;
    if (strcmp(str, ">")  == 0) return BAT_TOKEN_TYPE_GREATER;
    if (strcmp(str, "<")  == 0) return BAT_TOKEN_TYPE_LESS;
    if (strcmp(str, "<=") == 0) return BAT_TOKEN_TYPE_LESS_EQUAL;
    if (strcmp(str, ">=") == 0) return BAT_TOKEN_TYPE_GREATER_EQUAL;

    if (isdigit(str[0])) {
        return BAT_TOKEN_TYPE_NUMBER;
    } else {
        return BAT_TOKEN_TYPE_UNKNOWN;
    }
}
BAT_GROUP_T* bat_parse_line(BAT_T* bat, char* Line){
    BAT_GROUP_T* group = bat_create_group();

    int c = str_cdsp2(Line, 0x20);
    char** exp = explode(Line, 0x20);

    int inString = 0;

    char* currentString = NULL;
    for (int u = 0; u <= c; u++){
        bat_debug("    |--- [%u] %s\n", u, exp[u]);
        size_t len = strlen(exp[u]);
        if (exp[u][0] == '"' && !inString && exp[u][len - 1] == '"'){
            currentString = malloc(len * sizeof(char) + 1 );
            memset(currentString, 0, len * sizeof(char) + 1);
            memcpy(currentString, exp[u] + 1 , len - 2);

            currentString[len - 1] = '\0';
            //inString = 0;
            BAT_TOKEN_T* xtok = bat_create_token(BAT_TOKEN_TYPE_STRING, currentString);
            bat_debug("create token string method 1: '%s'\n", currentString);
            bat_add_token(group, (size_t) xtok);
            free(currentString);
        } else if (exp[u][0] == '"' && !inString) {
            inString = 1;
            currentString = malloc(len * sizeof(char));
            memset(currentString, 0, len * sizeof(char));
            strcpy(currentString, exp[u] + 1);
        } else if (inString) {
            if (exp[u][len - 1] == '"') {
                currentString = realloc(currentString, (strlen(currentString) + len) * sizeof(char));
                strcat(currentString, " ");
                strcat(currentString, exp[u]);
                currentString[strlen(currentString) - 1] = '\0';
                inString = 0;
                BAT_TOKEN_T* xtok = bat_create_token(BAT_TOKEN_TYPE_STRING, currentString);

                bat_debug("create token string method 2: '%s'\n", currentString);
                bat_add_token(group, (size_t) xtok);
                free(currentString);
            } else {
                currentString = realloc(currentString, (strlen(currentString) + len + 1) * sizeof(char));
                strcat(currentString, " ");
                strcat(currentString, exp[u]);
            }
        } else {
            if (exp[u][0] == '%' && exp[u][len - 1] == '%'){
                char* temp = malloc(len);
                memset(temp, 0, len);
                memcpy(temp, exp[u] + 1, len - 2);
                bat_debug("create token variable method 1: '%s'\n", currentString);
                BAT_TOKEN_T* xtok = bat_create_token(BAT_TOKEN_TYPE_VARIABLE, temp);
                bat_add_token(group, (size_t) xtok);
            } else {
                BAT_TOKEN_TYPE type = bat_parse_token(exp[u]);
                bat_debug("[AUTO_DETECT TYPE] Type: %s | Str: '%s'\n", bat_debug_type(type), exp[u]);
                if (type != BAT_TOKEN_TYPE_COMMENT){
                    BAT_TOKEN_T* xtok = bat_create_token(type, exp[u]);
                    bat_add_token(group, (size_t) xtok);
                }
            }

        }


    }
    if (inString) {
        currentString = realloc(currentString, (strlen(currentString) + 1) * sizeof(char));
        currentString[strlen(currentString) - 2] = '\0';
        inString = 0;

        bat_debug("create token string method 3: '%s'\n", currentString);
        BAT_TOKEN_T* xtok = bat_create_token(BAT_TOKEN_TYPE_STRING, currentString);
        bat_add_token(group, (size_t) xtok);

        free(currentString);
    }
    for (int u = 0; u <= c; u++){
        free(exp[u]);
    }
    free(exp);

    return group;
}
BAT_T* bat_parse_string(char* String){
    BAT_T* bat = bat_create_session();
    bat_debug("\n========================\n");
    bat_debug("%s", String);
    bat_debug("\n========================\n");

    int cLine = str_cdsp2(String, '\n');
    char** Line = explode(String, '\n');
    for (int uL = 0; uL <= cLine; uL++){
        bat_debug("[LINE %d | %d] %s\n", uL +1, cLine +1, Line[uL]);

        BAT_GROUP_T* group = bat_parse_line(bat, Line[uL]);
        bat_add_group(bat, (size_t) group);
        free(Line[uL]);
    }
    free(Line);
    return bat;
}

int main() {
    char* batFile = readFile("examples/if.bat");

    BAT_T* token = bat_parse_string(batFile);
    token->Debug = 1;
    token->Echo = 1;
    bat_debug("========================\n");

    int ret = bat_runtime_exec(token);
    bat_debug("BAT LEX INFO\n");
    bat_debug("Echo: %d\n", token->Echo);
    bat_debug("Debug: %d\n", token->Debug);
    bat_debug("Error: %d\n", token->ErrorCode);
    bat_debug("Count: %d\n", token->Size);
    bat_debug("\n========================\n");
    bat_debug("RETURN CODE: %d\n",ret);
    return ret;
}
