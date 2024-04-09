#pragma once

#include "rust/cxx.h"
#include <atomic>
#include <climits>
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
namespace file_io {
    class FileIO {
        public:
            virtual ~FileIO() {}

            static std::shared_ptr<FileIO> open(const rust::Str &filename,
                                                const rust::Str &mode = "r",
                                                const rust::Str &encoding = "utf-8");

            virtual rust::slice<const uint8_t> readLine() = 0;
            virtual rust::slice<const uint8_t> readLines() = 0;
            virtual rust::slice<const uint8_t> read() = 0;

            virtual void write(const rust::slice<const uint8_t> &data) = 0;
            virtual void writeLine(const rust::slice<const uint8_t> &data) = 0;
            virtual void writeLines(const rust::slice<const rust::slice<const uint8_t>> &lines) = 0;

            virtual void append(const rust::slice<const uint8_t> &data) = 0;
            virtual void appendLine(const rust::slice<const uint8_t> &data) = 0;
            virtual void appendLines(const rust::slice<const rust::slice<const uint8_t>> &lines) = 0;

            virtual void close() = 0;

        protected:
            FileIO() = default;
    };

    class FileIO_R : public FileIO {
             FileIO_R(const rust::Str &filename, const rust::Str &encoding);
            ~FileIO_R();

            rust::slice<const uint8_t> readLine();
            rust::slice<const uint8_t> readLines();
            rust::slice<const uint8_t> read();

            std::atomic_bool is_open;
            std::atomic_bool is_error;
            std::atomic_bool is_empty;
    };


    class FileIO_W : public FileIO {
         FileIO_W(const rust::Str &filename, const rust::Str &encoding);
        ~FileIO_W();

        void write(const rust::Str &data);
        void writeLine(const rust::Str &data);
        void writeLines(const rust::slice<const rust::Str> &lines);

        std::atomic_bool is_open;
        std::atomic_bool is_error;
    };

    class FileIO_A : public FileIO {
         FileIO_A(const rust::Str &filename, const rust::Str &encoding);
        ~FileIO_A();

        void append(const rust::Str &data);
        void appendLine(const rust::Str &data);
        void appendLines(const rust::slice<const rust::Str> &lines);

        rust::slice<const uint8_t> readLine();
        rust::slice<const uint8_t> readLines();
        rust::slice<const uint8_t> read();

        std::atomic_bool is_open;
        std::atomic_bool is_error;
        std::atomic_bool is_empty;
    };


    class FileIO_Internal {
        private:
            FileIO **files;
            static FileIO_Internal *instance;

            FileIO_Internal() {
                files = static_cast<FileIO**>(malloc(sizeof(FileIO*) * 0xf36db));
            }

        public:
            ~FileIO_Internal() {
                delete[] files;
            }

            static FileIO_Internal* getInstance() {
                if (!instance) {
                    instance = new FileIO_Internal();
                }
                return instance;
            }
    };

    inline FileIO_Internal* FileIO_Internal::instance = nullptr;
    inline std::shared_ptr<FileIO> FileIO::open(const rust::Str &filename,
                                                const rust::Str &mode,
                                                const rust::Str &encoding
    ) {
        if (mode == "r") {
            return std::make_shared<FileIO_R>(filename, encoding);
        } else if (mode == "w") {
            return std::make_shared<FileIO_W>(filename, encoding);
        }

        throw std::invalid_argument("Unsupported file mode");
    }
    void init();
}