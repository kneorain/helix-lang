/*
// void panic_cpp_impl(::rust::Str _error, ::rust::Slice<::rust::Str const> mark, ::rust::Str _file, ::std::int32_t line_no, bool no_lines, bool multi_frame, ::std::int8_t pos, bool follow_marked_order, ::std::uint32_t mark_start, ::rust::Str thread_name, bool no_exit, ::rust::Str lang, ::rust::Str _code) noexcept;

example use:
panic_cpp_impl(
    "Invalid mode. Valid modes are 'r', 'w', 'a', 'rw', 'wr'.",
    {},
    "Z:\\devolopment\\helix\\helix-lang\\PORT\\src\\cpp\\src\\file_io.cpp",
    10,
    false,
    false,
    0,
    false,
    0,
    "main",
    false,
    "cpp",
    "Invalid mode. Valid modes are 'r', 'w', 'a', 'rw', 'wr'."
);


*/
#ifndef PANIC_H
#define PANIC_H

#include <string>
#include <cstring>
#include "rust/cxx.h"

#if defined(_WIN32)
    #include <direct.h>
    #define GETCWD _getcwd
    #define PATH_SEPARATOR "\\"
#else
    #include <unistd.h>
    #define GETCWD getcwd
    #define PATH_SEPARATOR "/"
#endif

#ifndef PATH_MAX
    #define PATH_MAX 260
#endif

inline const char* abs_path(const char* filename) {
    char buffer[PATH_MAX];
    // merge the current working directory with the filename
    // so if the filename is "dhruv\file.txt" and the current working directory is "C:\Users\user\dhruv"
    // the result will be "C:\Users\user\dhruv\file.txt"
    // basically converts a relative path to an absolute path
    auto val = GETCWD(buffer, PATH_MAX) ? std::string{std::string(buffer) + PATH_SEPARATOR + filename} : std::string{filename};
    // convert all backslashes to forward slashes
    for (int i = 0; i < val.size(); i++) {
        if (val.data()[i] == '\\' || val.data()[i] == '/') {
            #if defined(_WIN32)
                val.data()[i] = '\\';
            #else
                val.data()[i] = '/';
            #endif
        }
    }

    char* result = new char[val.size() + 1];
    std::strcpy(result, val.c_str());
    return result;
}

/*
rust definition:
fn panic_cpp_impl(
    _error: &str,
    mark: &[&str],
    _file: &str,
    line_no: i32,
    no_lines: bool,
    multi_frame: bool,
    pos: i8,
    follow_marked_order: bool,
    mark_start: u32,
    thread_name: &str,
    no_exit: bool,
    lang: &str,
    _code: &str,
);
*/
#define panic(E) do { \
    panic_cpp_impl( \
        E, \
        {}, \
        abs_path(__FILE__), \
        __LINE__, \
        false, \
        false, \
        0, \
        false, \
        0, \
        "", \
        false, \
        "cpp", \
        "" \
    ); \
    std::terminate(); \
} while (0)

#endif // PANIC_H