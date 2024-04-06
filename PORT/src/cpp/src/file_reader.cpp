/** ----------------------------------------------------------------------------
 * @link{https://github.com/kneorain/helix-lang}
 * @brief Implementation of the FileReader class for efficient file handling.
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
 * Compiler. It includes the implementation of the FileReader class, which
 * serves as a pivotal component in handling large files efficiently. The
 * primary functionality of this class is to perform memory mapping for rapid
 * file access and ensure thread-safe operations for concurrent data reading.
 * This is particularly important in the context of a compiler where speed and
 * efficiency of file processing directly impact the overall compilation time.
 *
 * The FileReader class is designed to optimize the file reading process,
 * leveraging multithreading to enhance performance. It intelligently divides
 * the file into manageable chunks and enables simultaneous processing by
 * multiple threads. This approach is not only efficient but also scalable,
 * accommodating the varying demands of different file sizes and system
 * capabilities.
 *
 * Usage in Compiler Workflow:
 * - The main thread initiates the process by creating a FileReader object.
 * This object becomes the gateway to the underlying file handling operations.
 * - The total number of chunks in the file is determined by invoking the
 * get_total_chunks() method on the FileReader object.
 * - Based on this chunk division, the program dynamically allocates threads,
 * each responsible for processing a subset of the total chunks.
 * - Each thread, in its lifecycle, calls the get_data_from_chunk() method for
 * each chunk it is assigned, thereby enabling parallel processing of the file
 * data.
 *
 * Important Considerations:
 * - FileReader has been designed with thread safety in mind. However, it is
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
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include <cstring>

// mmap
#include <string>
#include <sys/stat.h>
#if defined __unix__ || __APPLE__
    #include <fcntl.h>
    #include <cerrno>
    #include <cstring>
    #include <unistd.h>
    #include <sys/mman.h>
#elif _WIN32
    #include <windows.h>
    #include <fileapi.h>
#endif

#define MAX_LINE_CHUNKS 0x1e


struct FileInfo {
    uint32_t              total_lines;
    std::vector<uint32_t> line_starts ;
};

template<class iter>
FileInfo count(const iter first, const iter last, const char val) {
    if (std::distance(first, last) < 0) {
        throw std::range_error("Invalid iterator range");
    }
    iter non_const_first = first;

    std::vector<uint32_t> line_starts = {};
    for (; non_const_first != last; ++non_const_first) {
        if (*non_const_first == val) {
            line_starts.push_back(std::distance(first, non_const_first));
        }
    }

    return FileInfo {static_cast<uint32_t>(line_starts.size()), std::move(line_starts)};
}

template<typename ... args>
std::string string_format( const std::string &str, args ... formats ) {
    int size_s = std::snprintf(
        nullptr, 0, str.c_str(), formats ...
    ) + 1;

    if (size_s <= 0) {
        throw std::runtime_error( "Error during formatting." );
    }
    
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    
    std::snprintf(
        buf.get(),
        size,
        str.c_str(),
        formats ...
    );
    
    return std::string(
        buf.get(),
        buf.get() + size - 1
    );
}

namespace file_reader {
    T_FileReader::T_FileReader(const std::string &filename)
        : fileName(filename.c_str())
        , totalLines(0)
        , lineStarts(0)
        
        // os specific
        , size(0)
        , data(nullptr)
    {
        #if defined __unix__ || __APPLE__
                int fd = open(fileName, O_RDONLY);
                if (fd == -1) {
                    std::cerr << "Failed to open file: " << strerror(errno) << std::endl;
                    throw std::runtime_error("Failed to open file");
                }

                struct stat fileStat;
                if (fstat(fd, &fileStat) == -1) {
                    std::cerr << "Failed to get file size: " << strerror(errno) << std::endl;
                    close(fd);
                    throw std::runtime_error("Failed to get file size");
                }

                size = fileStat.st_size;
                data = static_cast<char*>(mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0));
                close(fd);

                if (data == MAP_FAILED) {
                    std::cerr << "Failed to memory map file: " << strerror(errno) << std::endl;
                    throw std::runtime_error("Failed to memory map file");
                }

            #elif _WIN32
                hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hFile == INVALID_HANDLE_VALUE) {
                    std::cerr << "Failed to open file: " << GetLastError() << std::endl;
                    throw std::runtime_error("Failed to open file");
                }

                hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
                if (hMap == NULL) {
                    CloseHandle(hFile);
                    std::cerr << "Failed to create file mapping: " << GetLastError() << std::endl;
                    throw std::runtime_error("Failed to create file mapping");
                }

                size = GetFileSize(hFile, NULL);
                if (size == INVALID_FILE_SIZE) {
                    CloseHandle(hMap);
                    CloseHandle(hFile);
                    std::cerr << "Failed to get file size: " << GetLastError() << std::endl;
                    throw std::runtime_error("Failed to get file size");
                }

                data = static_cast<char*>(MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, size));
                if (data == NULL) {
                    CloseHandle(hMap);
                    CloseHandle(hFile);
                    std::cerr << "Failed to map view of file: " << GetLastError() << std::endl;
                    throw std::runtime_error("Failed to map view of file");
                }
            #endif

            FileInfo info = count(data, data + size, '\n');
            totalLines = info.total_lines;
            lineStarts = std::move(info.line_starts);
    }

    rust::Str T_FileReader::read_line(uint32_t lineIndex) const {
        std::cout << "Reading line: " << lineIndex << std::endl;
        if (
               lineIndex >= totalLines
            || lineIndex < 0
        ) {
            char* msg = new char[100];
            int co = std::snprintf(msg, 256, "FAILED TO READ! LINE INDEX OUT OF BOUNDS! GOT: %d MAX: %d", lineIndex, totalLines);
            if (co < 0) {
                return rust::Str(
                    "FAILED TO READ! FORMAT ERROR!"
                );
            }
            return rust::Str(
                msg
            );
        }
        
        uint32_t start = (lineIndex == 0 ? 0 : lineStarts[lineIndex - 1] + 1);

        if (lineIndex == totalLines - 1) {
            return rust::Str(
                data + start,
                size - start
            );
        }

        if (lineStarts[lineIndex] == start) {
            return rust::Str("");
        }

        return rust::Str(
            data + start,
            lineStarts[lineIndex] - start
        );
    }

    rust::Str T_FileReader::read_lines(uint32_t startLine, uint32_t offset) const {
        if (
               startLine >= totalLines
            || (startLine + offset) >= totalLines
            || offset > MAX_LINE_CHUNKS
            || offset == 0
            || offset < 0
            || startLine < 0
            || startLine > totalLines
        ) {
            char* msg = new char[100];
            int co = std::snprintf(msg, 256, "FAILED TO READ! LINE INDEX OUT OF BOUNDS! GOT: %d MAX: %d", startLine, totalLines);
            if (co < 0) {
                return rust::Str(
                    "FAILED TO READ! FORMAT ERROR!"
                );
            }
            return rust::Str(
                msg
            );
        }

        uint32_t start = (startLine == 0 ? 0 : lineStarts[startLine - 1] + 1);

        return rust::Str(
            data + start,
            lineStarts[startLine + offset] - start
        );
    }

    rust::Str T_FileReader::read_file() const {
        return rust::Str(data, size);
    }


    rust::Str T_FileReader::get_file_name() const {
        return rust::Str(fileName);
    }

    uint32_t T_FileReader::get_total_lines() const {
        return totalLines;
    }

    T_FileReader::~T_FileReader() {
        // deallocate memory
        #if defined __unix__ || __APPLE__ // cleanup
            munmap(data, size);
        #elif _WIN32
            UnmapViewOfFile(data);
            CloseHandle(hMap);
            CloseHandle(hFile);
        #endif
    }

    std::unique_ptr<T_FileReader> init(rust::Str filename) {
        return std::make_unique<T_FileReader>(std::string(filename));
    }
}