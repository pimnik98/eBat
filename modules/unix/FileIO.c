#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../../eBat.h"
#include "../../eBatRuntime.h"

int sys_unix_file_exist(char* filename){
    // Проверка на существование файла
    if (access(filename, F_OK) != -1) {
        return 1;
    } else {
        return 0;
    }
}

int sys_unix_dir_exist(char* path){
    struct stat sb;

    // Проверка на существование папки
    if (stat(path, &sb) != -1 && S_ISDIR(sb.st_mode)) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Проверка наличии файла или папки
 * @module FileIO.Exits
 * @param path Путь к файлу
 * @return 1 - Если файл найден или 0 - если нет
 */
int bat_runtime_fileio_exist(char* path){
    /// Insert your code
    bat_debug("[RUNTIME] [FileIO] [Exits] %s\n", path);
    int file = sys_unix_file_exist(path);
    int dir = sys_unix_dir_exist(path);
    bat_debug("file: %d || dir: %d\n", file, dir);
    return (file == 1 || dir == 1);
}

int bat_runtime_fileio_write(const char *filename, const char *text, int mode) {
    FILE *file;
    char *mode_str;

    // Выбор режима записи в файл (дозапись или перезапись)
    if (mode == 1) {
        mode_str = "a"; // Append (дозапись)
    } else {
        mode_str = "w"; // Write (перезапись)
    }

    // Открытие файла в выбранном режиме
    file = fopen(filename, mode_str);

    // Проверка на ошибки открытия файла
    if (file == NULL) {
        bat_debug("Error open file: %s\n", filename);
        return 1; // Возвращение кода ошибки
    }

    // Запись текста в файл
    fprintf(file, "%s", text);

    // Закрытие файла
    fclose(file);

    return 0; // Возвращение кода успеха
}