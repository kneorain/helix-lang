#define _CRT_SECURE_NO_WARNINGS

#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int remove_blank_lines(const char *file_path) {
    FILE *file;
    FILE *temp_file;
    char line[BUFFER_SIZE];

    errno_t err = fopen_s(&file, file_path, "r");
    if (err != 0 || file == NULL) {
        return 1;
    }

    err = tmpnam_s(line, sizeof(line));
    if (err != 0) {
        fclose(file);
        return 1;
    }

    err = fopen_s(&temp_file, line, "w+");
    if (err != 0 || temp_file == NULL) {
        fclose(file);
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        // Check if it's the last line and it's blank, skip writing it
        if (feof(file) && line[0] == '\n') {
            break;
        }
        if (line[0] != '\n') {
            fputs(line, temp_file);
        }
    }

    fclose(file);
    rewind(temp_file);

    err = fopen_s(&file, file_path, "w");
    if (err != 0 || file == NULL) {
        fclose(temp_file);
        return 1;
    }

    while (fgets(line, sizeof(line), temp_file) != NULL) {
        fputs(line, file);
    }

    fclose(file);
    fclose(temp_file);

    remove(line);
    return 0;
}