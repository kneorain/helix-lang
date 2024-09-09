#ifndef __WIN32_CWD_INC__
#define __WIN32_CWD_INC__

const char *cwd_env = std::getenv("PWD");
if (cwd_env != nullptr) {
    return {cwd_env};
}

// fallback to using sys calls
std::array<char, PATH_MAX> buffer{};

DWORD length = GetCurrentDirectory(static_cast<DWORD>(buffer.size()), buffer.data());
if (length == 0) {
    throw std::runtime_error("failed to get cwd, set the envrionment variable 'PWD': " +
                            std::to_string(GetLastError()));
}

#endif  // __WIN32_CWD_INC__