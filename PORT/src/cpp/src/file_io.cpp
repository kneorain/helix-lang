/* header definition:
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
                const rust::Str &filename,
                const rust::Str &mode     = "r",
                const rust::Str &encoding = "utf-8"
            );

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

            const void write      (const rust::slice<const u8> &data);
            const void writeLine  (const rust::slice<const u8> &data);

            const void append     (const rust::slice<const u8> &data);
            const void appendLine (const rust::slice<const u8> &data);
            const void appendLines(const rust::slice<const u8> &lines);

            const void clear();
            const void flush();
            const void insert(
                const rust::slice<const u8> &data,
                u64 position
            ); const void remove(
                u64 start,
                u64 end
            );

            const bool     isOpen();
            const bool     isError();
            const bool     isEmpty();
            const u64 size();
            const void     close();

        protected:
            char*    filename;
            char*    mode;
            char*    encoding;
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
*/
#include "helix-compiler/src/cpp/include/better_ints.hpp"
#include "helix-compiler/src/cpp/mod.rs.h"
#include "rust/cxx.h"
#include "helix-compiler/src/cpp/include/panic.h"

#include <cstring>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <atomic>

namespace file_io {

/* ---------------------------- FileIO ---------------------------- */
FileIO::~FileIO() {
    if (is_open) {
        close();
    }
}

FileIO::FileIO(const char *filename, const char *mode, const char *encoding) {
    this->is_open  = true;
    this->is_error = false;
    this->is_empty = false;
    this->cursor   = 0;

    this->filename = filename;
    this->mode     = mode;
    this->encoding = encoding;
    

    /*
        r = read
        w = write
        a = append
        rw = read and write (file must exist)
        wr = write and read (file does not have to exist)
        ra = INVALID
        wa = INVALID
        ar = INVALID
        aw = INVALID
    */
    panic("Invalid mode. Valid modes are 'r', 'w', 'a', 'rw', 'wr'.");

    // Check if the mode is valid
    if (
           strcmp(mode, "r")  != NULL
        && strcmp(mode, "w")  != NULL
        && strcmp(mode, "a")  != NULL
        && strcmp(mode, "rw") != NULL
        && strcmp(mode, "wr") != NULL
    ) {
        throw std::invalid_argument("Invalid mode. Valid modes are 'r', 'w', 'a', 'rw', 'wr'.");
    }

    mode_flags.read   = strchr(mode, 'r') != nullptr;
    mode_flags.write  = strchr(mode, 'w') != nullptr;
    mode_flags.append = strchr(mode, 'a') != nullptr;

    
}

const rust::slice<const u8> FileIO::read(i64 size) {
    return rust::slice<const u8>();
}

const rust::slice<const u8> FileIO::readNext(i64 size) {
    return rust::slice<const u8>();
}

const rust::slice<const u8> FileIO::readLine(u64 line_number) {
    return rust::slice<const u8>();
}

const rust::slice<const u8> FileIO::readLines(u64 start, u64 end) {
    return rust::slice<const u8>();
}

const rust::slice<const u8> FileIO::readRange(u64 start, u64 end) {
    return rust::slice<const u8>();
}

const void FileIO::write(const rust::slice<const u8> &data) {
    // Implementation to write data to the file.
}

const void FileIO::writeLine(const rust::slice<const u8> &data) {
    // Implementation to write a line of data to the file.
}

const void FileIO::append(const rust::slice<const u8> &data) {
    // Implementation to append data to the file.
}

const void FileIO::appendLine(const rust::slice<const u8> &data) {
    // Implementation to append a line to the file.
}

const void FileIO::appendLines(const rust::slice<const u8> &lines) {
    // Implementation to append multiple lines to the file.
}

const void FileIO::clear() {
    // Implementation to clear file contents.
}

const void FileIO::flush() {
    // Implementation to flush the file buffers.
}

const void FileIO::insert(const rust::slice<const u8> &data, u64 position) {
    // Implementation to insert data at a specific position in the file.
}

const void FileIO::remove(u64 start, u64 end) {
    // Implementation to remove data from 'start' to 'end'.
}

const bool FileIO::isOpen() {
    // Check if the file is open.
    return false;
}

const bool FileIO::isError() {
    // Check for errors in file operations.
    return false;
}

const bool FileIO::isEmpty() {
    // Check if the file is empty.
    return false;
}

const u64 FileIO::size() {
    // Get the size of the file.
    return 0;
}

const void FileIO::close() {
    // Close the file.
}
 
std::unique_ptr<FileIO> open(
    const rust::Str filename,
    const rust::Str mode = "r",
    const rust::Str encoding = "utf-8"
) {
    return std::make_unique<FileIO>(filename.data(), mode.data(), encoding.data());
}

} // namespace file_io