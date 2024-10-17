#ifndef __NEO_PROCESS_HH__
#define __NEO_PROCESS_HH__

// similar to python subprocess
/// \brief this allows a user to start a new process, connect to its input/output/error pipes,
///        and obtain its return code. while also allowing the user to send input to the process
///        and capture its output.

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define __NEO_WINDOWS__
#else
#define __NEO_UNIX__
#endif

#include <iostream>
#include <string>
#include <vector>

#ifdef __NEO_WINDOWS__
#include <windows.h>
#else
#include <sys/wait.h>
#include <unistd.h>
#endif

#pragma warning(push)
#pragma warning(disable: _UCRT_DISABLED_WARNINGS)
_UCRT_DISABLE_CLANG_WARNINGS

namespace neo {
inline namespace detail {
    struct process_handle {
#ifdef __NEO_WINDOWS__
        HANDLE hProcess;
        HANDLE hThread;
#else
        pid_t pid;
#endif
    };

    struct pipe_handle {
#ifdef __NEO_WINDOWS__
        HANDLE hRead;
        HANDLE hWrite;
#else
        int fd[2];
#endif
    };

    struct process_info {
        process_handle handle;
        pipe_handle    stdin();
        pipe_handle    stdout;
        pipe_handle    stderr;
    };

    inline pipe_handle create_pipe() {
        pipe_handle pipe;
#ifdef __NEO_WINDOWS__
        SECURITY_ATTRIBUTES saAttr;
        saAttr.nLength              = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle       = TRUE;
        saAttr.lpSecurityDescriptor = nullptr;

        if (!CreatePipe(&pipe.hRead, &pipe.hWrite, &saAttr, 0)) {
            throw std::runtime_error("failed to create pipe");
        }
#else
        if (pipe(fd) == -1) {
            throw std::runtime_error("failed to create pipe");
        }
#endif
        return pipe;
    }

    inline void close_pipe(pipe_handle &pipe) {
#ifdef __NEO_WINDOWS__
        CloseHandle(pipe.hRead);
        CloseHandle(pipe.hWrite);
#else
        close(pipe.fd[0]);
        close(pipe.fd[1]);
#endif
    }

    inline process_handle create_process(const std::string &command) {
        process_handle handle;
#ifdef __NEO_WINDOWS__
        STARTUPINFO         si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        if (!CreateProcess(nullptr,
                           const_cast<char *>(command.c_str()),
                           nullptr,
                           nullptr,
                           TRUE,
                           0,
                           nullptr,
                           nullptr,
                           &si,
                           &pi)) {
            throw std::runtime_error("failed to create process");
        }

        handle.hProcess = pi.hProcess;
        handle.hThread  = pi.hThread;
#else
        pid_t pid = fork();
        if (pid == -1) {
            throw std::runtime_error("failed to create process");
        }

        if (pid == 0) {
            execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);
            exit(127);
        }

        handle.pid = pid;
#endif
        return handle;
    }

    inline void close_process(process_handle &handle) {
#ifdef __NEO_WINDOWS__
        CloseHandle(handle.hProcess);
        CloseHandle(handle.hThread);
#else
        waitpid(handle.pid, nullptr, 0);
#endif
    }

    inline void write_to_pipe(pipe_handle &pipe, const std::string &data) {
#ifdef __NEO_WINDOWS__
        DWORD bytes_written;
        WriteFile(pipe.hWrite, data.c_str(), data.size(), &bytes_written, nullptr);
#else
        write(pipe.fd[1], data.c_str(), data.size());
#endif
    }

    inline std::string read_from_pipe(pipe_handle &pipe) {
        std::string data;
#ifdef __NEO_WINDOWS__
        DWORD bytes_read;
        CHAR  buffer[4096];
        while (true) {
            if (!ReadFile(pipe.hRead, buffer, sizeof(buffer), &bytes_read, nullptr) ||
                bytes_read == 0) {
                break;
            }
            data.append(buffer, bytes_read);
        }
#else
        char    buffer[4096];
        ssize_t bytes_read;
        while (true) {
            bytes_read = read(pipe.fd[0], buffer, sizeof(buffer));
            if (bytes_read <= 0) {
                break;
            }
            data.append(buffer, bytes_read);
        }
#endif
        return data;
    }
}  // namespace detail
class process {
    
};
}  // namespace neo::process

_UCRT_RESTORE_CLANG_WARNINGS
#pragma warning(pop) // _UCRT_DISABLED_WARNINGS
#endif  // __NEO_PROCESS_HH__