/** ----------------------------------------------------------------------------
 * @link{https://github.com/kneorain/helix-lang}
 * @brief Header file for the FileIO class, offering comprehensive file
 * manipulation capabilities.
 *
 * This header is part of the Helix Compiler's frontend, leveraging advanced
 * file I/O operations crucial for handling source code efficiently in the
 * compilation process. The module provides functionalities such as reading,
 * writing, appending, and managing files with high efficiency and reliability,
 * ensuring robust file operations.
 *
 * @author Dhruvan Kartik
 * @date 2024
 *
 * This work is licensed under the Creative Commons Attribution 4.0
 * International License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by/4.0/ or send a letter to
 * Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
 * @see http://creativecommons.org/licenses/by/4.0/
 *
 * You are free to:
 * - Share — copy and redistribute the material in any medium or format
 * - Adapt — remix, transform, and build upon the material
 * for any purpose, even commercially, under the following terms:
 * - Attribution — You must give appropriate credit, provide a link to
 *   the license, and indicate if changes were made. You may do so in
 *   any reasonable manner, but not in any way that suggests the licensor
 *   endorses you or your use.
 *
 * This is a human-readable summary of (and not a substitute for) the license.
 * For the full license text, see the LICENSE file in the root directory of
 * this source code repository or visit the URL above.
 *
 * -----------------------------------------------------------------------------
 *
 * @file file_io.hpp
 * Description: Implements the FileIO and FileManager classes, providing
 * methods for reading, writing, appending, and managing files with high
 * performance and reliability. The classes support file handling operations
 * using memory-safe constructs and exception handling to ensure robustness,
 * particularly useful in a compiler setting for handling large files.
 *
 * Classes Defined:
 * - FileIO: Facilitates opening files and performing read, write, and append
 * operations.
 * - file: Manages memory for file data, ensuring efficient space usage.
 * - FileManager: Manages a pool of file objects for optimized file access.
 *
 * Usage in Compiler Workflow:
 * - FileIO objects manage file interactions throughout the compilation process,
 * ensuring thread-safe and efficient file access.
 * - FileManager maintains a static instance for global file management,
 * optimizing memory usage and operational speed by reusing file objects where
 * possible.
 *
 * Important Considerations:
 * - Proper error handling and resource management are crucial, especially in
 * multithreaded environments to prevent data corruption and memory leaks.
 * - The architecture should allow for scalability and flexibility to adapt to
 * various file sizes and system capabilities without degradation in
 * performance.
 *
 * @since   v0.1.3-stable
 * @version v0.1.4-stable
 * -------------------------------------------------------------------------- */
#pragma once

#include "better_ints.hpp"
#include "rust/cxx.h"
#include <memory>

namespace file_io {
    typedef struct {
        bool read;
        bool write;
        bool append;
    } FileMode;

    struct file {
        char* data;
        u64   size;
        u64   capacity;

        file(const char* init_data) {
            size = strlen(init_data);
            capacity = size + 0xf36dbf;
            data = (char*)std::malloc(capacity + 1);
            if (data == nullptr) {
                throw std::bad_alloc();
            }
            std::memcpy(data, init_data, size);
            data[size] = '\0';
        }

        ~file() {
            std::free(data);
        }
    };

    class FileIO {
        public:
            ~FileIO();
             FileIO(
                const char *filename,
                const char *mode,
                const char *encoding
            );

            /* ---------------------------- READ ---------------------------- */
            const rust::slice<const u8> read     (i64 size);
            const rust::slice<const u8> readNext (i64 size);
            const rust::slice<const u8> readLine (u64 line_number);
            const rust::slice<const u8> readLines(
                u64 start,
                u64 end
            ); const rust::slice<const u8> readRange(
                u64 start,
                u64 end
            );

            /* ---------------------------- WRITE --------------------------- */
            const void write      (const rust::slice<const u8> &data);
            const void writeLine  (const rust::slice<const u8> &data);

            /* ---------------------------- APPEND -------------------------- */
            const void append     (const rust::slice<const u8> &data);
            const void appendLine (const rust::slice<const u8> &data);
            const void appendLines(const rust::slice<const u8> &lines);

            /* ---------------------------- UTILS --------------------------- */
            const void clear();
            const void flush();
            const void insert(
                const rust::slice<const u8> &data,
                u64 position
            ); const void remove(
                u64 start,
                u64 end
            );

            /* ---------------------------- META ---------------------------- */
            const bool     isOpen();
            const bool     isError();
            const bool     isEmpty();
            const u64 size();
            const void     close();

        protected:
            const char*    filename;
            const char*    mode;
            const char*    encoding;
            bool     is_open;
            bool     is_error;
            bool     is_empty;
            u64 cursor;

        private:
            FileMode mode_flags;
    };

    class FileManager {
        public:
            ~FileManager() {
                for (size_t i = 0; i < 0xf36db; ++i) {
                    delete files[i];
                }
                std::free(files);
            }

            static FileManager* getInstance() {
                if (!instance) {
                    instance = new FileManager();
                }
                return instance;
            }

            void loadFile(const char* data, int discernment) {
                if (discernment < 0 || discernment >= 0xf36db) {
                    throw std::out_of_range("Index out of range");
                }
                delete files[discernment];
                files[discernment] = new file(data);
            }

            file* getFile(int discernment) {
                if (discernment < 0 || discernment >= 0xf36db) {
                    throw std::out_of_range("Index out of range");
                }
                return files[discernment];
            }

        private:
            file** files;
            static FileManager* instance;

            FileManager() {
                files = (file**)std::malloc(sizeof(file*) * 0xf36db);
                if (files == NULL) {
                    throw std::bad_alloc();
                }
                for (size_t i = 0; i < 0xf36db; ++i) {
                    files[i] = nullptr;
                }
            }
    };

    inline FileManager* FileManager::instance = nullptr;
    std::unique_ptr<FileIO> open(
        const rust::Str filename,
        const rust::Str mode,
        const rust::Str encoding
    );
}