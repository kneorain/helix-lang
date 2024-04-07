#pragma once
/** ----------------------------------------------------------------------------
 * @link{https://github.com/kneorain/helix-lang}
 *
 * @brief This file is part of the Helix Compiler, an open-source compiler
 *        for the Helix programming language.
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
 * Compiler. It includes the implementation of the T_FileReader class, which
 * serves as a pivotal component in handling large files efficiently. The
 * primary functionality of this class is to perform memory mapping for rapid
 * file access and ensure thread-safe operations for concurrent data reading.
 * This is particularly important in the context of a compiler where speed and
 * efficiency of file processing directly impact the overall compilation time.
 *
 * The T_FileReader class is designed to optimize the file reading process,
 * leveraging multithreading to enhance performance. It intelligently divides
 * the file into manageable chunks and enables simultaneous processing by
 * multiple threads. This approach is not only efficient but also scalable,
 * accommodating the varying demands of different file sizes and system
 * capabilities.
 *
 * Usage in Compiler Workflow:
 * - The main thread initiates the process by creating a T_FileReader object.
 * This object becomes the gateway to the underlying file handling operations.
 * - The total number of chunks in the file is determined by invoking the
 * get_total_chunks() method on the T_FileReader object.
 * - Based on this line division, the program dynamically allocates threads,
 * each responsible for processing a subset of the total chunks.
 * - Each thread, in its lifecycle, calls the get_data_from_chunk() method for
 * each line it is assigned, thereby enabling parallel processing of the file
 * data.
 *
 * Important Considerations:
 * - T_FileReader has been designed with thread safety in mind. However, it is
 * crucial that the implementation is carefully managed to avoid race conditions
 * and ensure data integrity.
 * - It is imperative that no two threads access the same line simultaneously.
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
#include "rust/cxx.h"
#include <memory>
#include <cstdint>
#include <vector>

#if defined __unix__ || __APPLE__
    #include <sys/mman.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
#elif _WIN32
    #include <windows.h>
#endif

/**
 * @brief file_stream_cpp namespace provides functionality for reading data
 *        from a file in chunks. also thread safe. (**soon**)
 */
namespace file_reader {
    class T_FileReader {
        public:
            /**
             * @brief this class provides functionality for reading data
             *        from a file in an highly optimized manner for a compiler.
             *
             * constructs a T_FileReader object with the specified filename.
             * does the following magic:
             * - calculates the total number of lines in the file.
             * - calculates the size of the file.
             * - calculates the number of chunks in the file.
             * - stores the start pos of each line in the chunks vector.
             * all done in > 500µs for a 40mb (2M lines - non empty) file.
             * **Tested on my machine**
             *
             * @param filename The name of the file to be read.
             */
             T_FileReader(const std::string &filename);
            ~T_FileReader();

            /**
             * retrieves data from the specified line index.
             *
             * @param chunkIndex The index of the line to retrieve data from.
             * @return The data from the specified line as a rust::Str.
             */
            rust::Str read_line(uint32_t lineIndex) const;
            
            /**
             * retrieves data from the specified line index with an offset.
             *
             * @param startLine The index of the line to start reading from.
             * @param offset The number of lines to read.
             * @return The data from the specified line as a rust::Str.
             */
            rust::Str read_lines(uint32_t startLine, uint32_t offset) const;

            /**
             * retrieves the entire file as a rust::Str.
             *
             * @return The entire file as a rust::Str.
             */
            rust::Str read_file() const;
            
            /**
             * retrieves the total number of chunks in the file.
             *
             * @return The total number of chunks.
             */
            uint32_t get_total_lines() const;

            /**
             * retrieves the name of the file.
             *
             * @return The name of the file.
             */
            rust::Str get_file_name() const;

        private:
            const char    *fileName;
            uint32_t       totalLines;
            mutable std::vector<uint32_t> lineStarts;

            #if defined __unix__ || __APPLE__
                size_t size;
                char  *data;
            #elif _WIN32
                DWORD  size;
                HANDLE hMap;
                HANDLE hFile;
                char  *data;
            #endif
    };

    /**
     * creates a new T_FileReader object with the specified filename.
     * this function is the entry point for creating T_FileReader objects.
     * to use in rust/c code.
     *
     * @param filename The name of the file to be read.
     * @return A unique pointer to the newly created T_FileReader object.
     */
    std::unique_ptr<T_FileReader> init(rust::Str filename);
}