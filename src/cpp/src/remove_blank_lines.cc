/**
 * FIXME: add macos support.
 *
 * @file remove_blank_lines.cpp
 * @brief Implementation of a function to remove blank lines from a file in C++
 * using the secure functions provided by Visual C++.
 *
 * This source file includes the implementation of the `remove_blank_lines`
 * function, which is designed to read a file, remove all blank lines, and write
 * the modified content back to the same file. This function uses secure
 * functions like `fopen_s` and `tmpnam_s` to enhance security by reducing the
 * risk of buffer overflows and other common vulnerabilities associated with
 * standard C functions.
 *
 * The key steps in the function include:
 * - Opening the source file for reading.
 * - Creating a temporary file to store the content without blank lines.
 * - Reading from the source file and writing to the temporary file, skipping
 * blank lines.
 * - Rewriting the source file with the modified content from the temporary
 * file.
 * - Cleaning up by closing files and removing the temporary file.
 *
 * The function uses `BUFFER_SIZE` as the buffer for reading lines, which is set
 * to 1024 bytes. This buffer size can be adjusted as needed based on expected
 * file line lengths. The function returns `0` on success and `1` on any error,
 * ensuring easy integration into larger systems where error handling is
 * crucial.
 *
 * The implementation provides a practical example of file manipulation and
 * error handling in C++ while adhering to safer programming practices
 * recommended for Visual C++ applications.
 *
 * @author Dhruvan Kartik
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 * @doc generated by ChatGPT
 * This work is licensed under the Creative Commons Attribution 4.0
 * International License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by/4.0/ or send a letter to Creative
 * Commons, PO Box 1866, Mountain View, CA 94042, USA.
 * @see http://creativecommons.org/licenses/by/4.0/
 */
#define _CRT_SECURE_NO_WARNINGS

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
