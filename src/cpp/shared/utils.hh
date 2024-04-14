#ifndef HELIX_LANG_SHARED_UTILS_hh
#define HELIX_LANG_SHARED_UTILS_hh

#include "helix-compiler/src/cpp/shared/panic.hh"
#include <cstring>
#include <memory>
#include <string>
#include <stdexcept>

namespace utils {
    template <typename T>
    inline T* copy(T* data, size_t size) {
        T* new_data = new T[size];
        std::memcpy(new_data, data, size);
        return new_data;
    }

    template <typename T>
    inline T* copy(T* data, size_t size, size_t new_size) {
        T* new_data = new T[new_size];
        std::memcpy(new_data, data, size);
        return new_data;
    }

    template <typename T>
    inline T* copy(T* data, size_t size, size_t new_size, T fill) {
        T* new_data = new T[new_size];
        std::memcpy(new_data, data, size);
        for (size_t i = size; i < new_size; i++) {
            new_data[i] = fill;
        }
        return new_data;
    }

    template<typename ... Args>
    inline std::string string_format( const std::string& format, Args ... args ) {
        int size_s = std::snprintf(
            nullptr,
            0,
            format.c_str(),
            args ...
        ) + 1;

        if( size_s <= 0 ) {
            panic(std::runtime_error("string formatting failed"
                                           "during formatting."));
        }

        auto size = static_cast<size_t>(size_s);
        std::unique_ptr<char[]> buf(new char[size]);
        
        std::snprintf(
            buf.get(),
            size,
            format.c_str(),
            args ...
        );

        return std::string(
            buf.get(),
            buf.get() + size - 1
        );
    }

    inline void safe_strcpy(char* dest, const char* src) {
        size_t size = strlen(src);
        
        #ifdef _MSC_VER
            strncpy_s(dest, size, src, size);
        #else
            if (dest_size > src.size()) {
                std::strcpy(dest, src.c_str());
            } else {
                std::cerr << "Destination buffer is too small" << std::endl;
            }
        #endif
    }
}

#endif //HELIX_LANG_SHARED_UTILS_hh