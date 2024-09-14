// #include <iostream>
// #include <string>
// #include <sstream>

// class VerbosePrinter {
// public:
//     enum Criticality {
//         INFO,
//         WARNING,
//         ERROR,
//         DEBUG
//     };

//     VerbosePrinter(int verbosityLevel) : verbosityLevel(verbosityLevel) {}

//     template<typename... Args>
//     void print(Criticality level, Args... args) {
//         if (level >= verbosityLevel) {
//             std::ostringstream message;
//             message << formatPrefix(level);
//             (message << ... << args); // Fold expression to append all args
//             message << colors::reset << std::endl;
//             std::cout << message.str();
//         }
//     }

// private:
//     int verbosityLevel;

//     std::string formatPrefix(Criticality level) const {
//         std::ostringstream prefix;

//         switch (level) {
//             case INFO:
//                 prefix << colors::fg16(34) << "[INFO] ";
//                 break;
//             case WARNING:
//                 prefix << colors::fg16(214) << "[WARNING] ";
//                 break;
//             case ERROR:
//                 prefix << colors::fg16(196) << "[ERROR] ";
//                 break;
//             case DEBUG:
//                 prefix << colors::fg16(105) << "[DEBUG] ";
//                 break;
//         }

//         return prefix.str();
//     }
// };
