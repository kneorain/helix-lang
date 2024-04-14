#ifndef DEBUG_H
#define DEBUG_H

#define debug_enabled std::getenv("DEBUG") != nullptr
#define dbg(x)                                                                 \
    if (debug_enabled) {                                                       \
        std::cout << yellow << "dbg " << green << __FILE__ << ":" << __LINE__  \
                  << reset  << std::endl;                                      \
        std::cout << "\t"   << yellow << #x << ": " << green << "\"" << x << "\""\
                  << reset  << std::endl;                                      \
    }

#define dbg_all(...)                                                           \
    if (debug_enabled) {                                                       \
        std::cout << red << "dbg " << green << __FILE__ << ":" << __LINE__     \
                  << reset << std::endl;                                       \
        auto argList = {__VA_ARGS__};                                          \
        auto argNames = #__VA_ARGS__;                                          \
        std::istringstream iss(argNames);                                      \
        std::vector<std::string> names(                                        \
            (std::istream_iterator<std::string>(iss)),                         \
             std::istream_iterator<std::string>());                            \
        auto it = argList.begin();                                             \
        for (auto &name : names) {                                             \
        if (name.back() == ',') {                                              \
            name.pop_back();                                                   \
        }                                                                      \
        std::cout << "\t" << yellow << name << ": " << green << "\"" << *it    \
                  << "\"" << reset << std::endl;                               \
        if (it != argList.end())                                               \
            ++it;                                                              \
        }                                                                      \
    }

#endif // DEBUG_H