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
#include <sstream>
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


struct FileInfo {
    uint32_t              total_lines;
    std::vector<uint32_t> line_starts ;
};

template<class init>
FileInfo count(const init first, const init last, const char val) {
    std::_Adl_verify_range(first, last);
    auto usize_first      = std::_Get_unwrapped(first);
    const auto usize_last = std::_Get_unwrapped(last);

    std::vector<uint32_t> line_starts = {};
    for (; usize_first != usize_last; ++usize_first) {
        if (*usize_first == val) {
            line_starts.push_back(std::distance(first, usize_first));
        }
    }

    return FileInfo {static_cast<uint32_t>(line_starts.size()), std::move(line_starts)};
}

namespace file_reader {
    T_FileReader::T_FileReader(const std::string &filename)
        : fileName(filename.c_str()
    ) {
        #ifdef __unix__ // tell kernel the access pattern.
            posix_fadvise(fd, 0, 0, 1);  // FDADVICE_SEQUENTIAL
        #endif

        #ifdef __unix__ // memory map the file to unix
            stat sb;
            size = sb.st_size;
            fstat(
                fileno(fd),
                &sb
            );
            *data = (char*) mmap(
                NULL,
                size,
                PROT_READ,
                MAP_PRIVATE,
                fileno(fd),
                0
            );
        #elif _WIN32 // memory map the file to windows
            hFile = CreateFileA(
                fileName,
                0x80000000L, // GENERIC_READ
                0x00000001L,     // FILE_SHARE_READ
                NULL,   // default security
                0x3,   // OPEN_EXISTING
                0x80,   // FILE_ATTRIBUTE_NORMAL
                NULL           // no template
            );
            hMap  = CreateFileMapping(
                hFile,
                NULL,
                PAGE_READONLY,
                0,
                0,
                NULL
            );
            size  = GetFileSize(
                hFile,
                NULL
            );
            data = (char*) MapViewOfFile(
                hMap,
                FILE_MAP_READ,
                0,
                0,
                size
            );
        #endif /* count the number of lines in the file */
        FileInfo info = count(data, data + size, '\n');
        totalLines = info.total_lines; // store the total number of lines
        lineStarts = info.line_starts; // store the line starts
    }

    rust::Str T_FileReader::read_line(uint32_t lineIndex) const {
        if (lineIndex >= totalLines) {
            return rust::Str(
                "FAILED TO READ! LINE INDEX OUT OF BOUNDS! GOT: "
                + std::to_string(lineIndex)
                + " MAX: "
                + std::to_string(totalLines)
            );
        }
        
        uint32_t start = (lineIndex == 0 ? 0 : lineStarts[lineIndex - 1] + 1);

        return rust::Str(
            data + start,
            lineStarts[lineIndex] - start
        );
    }

    rust::Str T_FileReader::read_lines(uint32_t startLine, uint32_t offset) const {
        if (startLine >= totalLines || (startLine + offset) >= totalLines) {
            return rust::Str(
                "FAILED TO READ! LINE INDEX OUT OF BOUNDS! GOT: "
                + std::to_string(startLine)
                + " MAX: "
                + std::to_string(totalLines)
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
        #ifdef __unix__ // cleanup
            munmap(data, size);
        #elif _WIN32
            UnmapViewOfFile(data);
            CloseHandle(hMap);
            CloseHandle(hFile);
        #endif
        // deallocate memory
        delete[] data;
        
    }

    std::unique_ptr<T_FileReader> init(rust::Str filename) {
        return std::make_unique<T_FileReader>(std::string(filename));
    }

}