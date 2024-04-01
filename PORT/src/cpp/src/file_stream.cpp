/** ----------------------------------------------------------------------------
 * @link{https://github.com/kneorain/helix-lang}
 * @brief Implementation of the FileStream_CPP class for efficient file handling.
 *
 * This file is part of the Helix Compiler, an open-source compiler
 * for the Helix programming language.
 *
 * @author Kneorain
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
 * @author Dhruvan Kartik
 *
 * -----------------------------------------------------------------------------
 *
 * @file file_stream.cpp
 * Description: This file forms an integral part of the frontend for the Helix
 * Compiler. It includes the implementation of the FileStream_CPP class, which
 * serves as a pivotal component in handling large files efficiently. The
 * primary functionality of this class is to perform memory mapping for rapid
 * file access and ensure thread-safe operations for concurrent data reading.
 * This is particularly important in the context of a compiler where speed and
 * efficiency of file processing directly impact the overall compilation time.
 *
 * The FileStream_CPP class is designed to optimize the file reading process,
 * leveraging multithreading to enhance performance. It intelligently divides
 * the file into manageable chunks and enables simultaneous processing by
 * multiple threads. This approach is not only efficient but also scalable,
 * accommodating the varying demands of different file sizes and system
 * capabilities.
 *
 * Usage in Compiler Workflow:
 * - The main thread initiates the process by creating a FileStream_CPP object.
 * This object becomes the gateway to the underlying file handling operations.
 * - The total number of chunks in the file is determined by invoking the
 * get_total_chunks() method on the FileStream_CPP object.
 * - Based on this chunk division, the program dynamically allocates threads,
 * each responsible for processing a subset of the total chunks.
 * - Each thread, in its lifecycle, calls the get_data_from_chunk() method for
 * each chunk it is assigned, thereby enabling parallel processing of the file
 * data.
 *
 * Important Considerations:
 * - FileStream_CPP has been designed with thread safety in mind. However, it is
 * crucial that the implementation is carefully managed to avoid race conditions
 * and ensure data integrity.
 * - It is imperative that no two threads access the same chunk simultaneously.
 * Proper synchronization mechanisms or access control should be in place to
 * enforce this rule.
 * - The design and implementation should be robust to handle any exceptions or
 * edge cases that might arise during file operations, ensuring stability and
 * reliability of the compiler.
 *
 * The development of this file and its functionality has been guided by the
 * overarching goal to enhance the performance and reliability of the Helix
 * Compiler. Through effective file management and parallel processing
 * capabilities, it contributes significantly to the compiler's efficiency,
 * especially when dealing with large source files.
 *
 * @since   v0.0.1-stable
 * @version v0.1.2-stable
 * -------------------------------------------------------------------------- */

#include "helix-compiler/src/cpp/mod.rs.h"
#include "rust/cxx.h"
// headers
#include <cstdint>
#include <memory>
#include <algorithm>
#include <cstring>
// mmap
#include <string>
#include <sys/stat.h>

#ifdef __unix__
    #include <fcntl.h>
    #include <sys/mman.h>
#elif _WIN32
    #include <windows.h>
    #include <fileapi.h>
#endif

#define MAX_LINE_CHUNKS 0x1e

static inline size_t rls(char* data, int startLine, int endLine) {
    if (startLine > endLine || startLine < 1) return 0;

    const char* cursor = data;
    size_t size = 0;
    int currentLine = 1;

    // skip lines until it reaches the startLine
    while (*cursor && currentLine < startLine) {
        if (*cursor++ == '\n') {
            currentLine++;
        }
    }

    // count bytes in the specified line range
    while (*cursor && currentLine <= endLine) {
        size += (*cursor != '\n');
        currentLine += (*cursor++ == '\n');
    }

    return size;
}

// function to read a specific line from a file
static inline std::string rl(char*& data, int line) {
    if (--line < 0) return ""; // adjust for 0-based indexing

    const char* line_start = nullptr;
    const char* cursor = data;

    for (; *cursor; ++cursor) {
        if (line_start == nullptr) line_start = cursor; // set start at the beginning or after a newline

        if (*cursor == '\n') {
            if (line-- == 0) {
                // found the desired line
                return std::string(line_start, cursor - line_start);
            }
            line_start = nullptr; // reset start for next line
        }
    }

    // handle the case where the last line doesn't end with a newline
    return (line == 0) ? std::string(line_start, cursor - line_start) : std::string();
}

static std::_Iter_diff_t<char *> tl(char const *fname) {
    #ifdef __unix__ // tell kernel the access pattern.
        posix_fadvise(fd, 0, 0, 1);  // FDADVICE_SEQUENTIAL
    #endif

    // memory map the file
    #ifdef __unix__
        struct stat sb;
        size_t size = sb.st_size;
        fstat(
            fileno(fd),
            &sb
        );
        char* data = (char*) mmap(
            NULL,
            size,
            PROT_READ,
            MAP_PRIVATE,
            fileno(fd),
            0
        );
    #elif _WIN32
        HANDLE hFile = CreateFileA(
            fname,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );
        HANDLE hMap  = CreateFileMapping(
            hFile,
            NULL,
            PAGE_READONLY,
            0,
            0,
            NULL
        );
        DWORD  size  = GetFileSize(
            hFile,
            NULL
        );
        char*  data  = (char*) MapViewOfFile(
            hMap,
            FILE_MAP_READ,
            0,
            0,
            size
        );
    #endif

    // get the total number of lines
    auto total_lines = std::count(
        data,
        data + size,
        '\n'
    );

    // calculate the number of chunks
    auto chunks = total_lines / MAX_LINE_CHUNKS;

    if (total_lines % MAX_LINE_CHUNKS != 0) {
        chunks += 1;
    }

    // store the following {int, int, int, ...} where each int is the start pos
    // of a line, and the index is the line number

    #ifdef __unix__ // cleanup
        munmap(data, size);
    #elif _WIN32
        UnmapViewOfFile(data);
        CloseHandle    (hMap);
        CloseHandle    (hFile);
    #endif

    return total_lines;
}

namespace file_stream_cpp {
    FileStream_CPP::FileStream_CPP(const std::string &filename):
        fileName(filename.c_str()) {
    }

    /*
    4kb of data as a rust::Str ~ 2us
    reading 4kb of data from a file ~ 8.0us
    */

    rust::Str FileStream_CPP::get_data_from_chunk(uint32_t chunkIndex) const {
        return rust::Str("Total Lines = " + std::to_string(tl(fileName)));
    }

    FileStream_CPP::~FileStream_CPP() {
        //fileStream.close();
    }

    uint32_t FileStream_CPP::get_total_chunks() const {
        return 1;
    }

    std::unique_ptr<FileStream_CPP> new_file_stream(rust::Str filename) {
        return std::make_unique<FileStream_CPP>(std::string(filename));
    }
}