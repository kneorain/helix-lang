#ifndef COLORS_H
#define COLORS_H

#include <string>

namespace colors {
    inline const constexpr char *reset = "\u001b[0m";

    inline namespace effects {
        inline const constexpr char *bold = "\u001b[1m";
        inline const constexpr char *dim = "\u001b[2m";
        inline const constexpr char *italic = "\u001b[3m";
        inline const constexpr char *underline = "\u001b[4m";
        inline const constexpr char *blink = "\u001b[5m";
        inline const constexpr char *reverse = "\u001b[7m";
        inline const constexpr char *hidden = "\u001b[8m";
    }  // namespace effects

    inline namespace fg8 {
        inline const constexpr char *black = "\u001b[30m";
        inline const constexpr char *red = "\u001b[31m";
        inline const constexpr char *green = "\u001b[32m";
        inline const constexpr char *yellow = "\u001b[33m";
        inline const constexpr char *blue = "\u001b[34m";
        inline const constexpr char *magenta = "\u001b[35m";
        inline const constexpr char *cyan = "\u001b[36m";
        inline const constexpr char *white = "\u001b[37m";
    }  // namespace fg8

    inline namespace bg8 {
        inline const constexpr char *black = "\u001b[40m";
        inline const constexpr char *red = "\u001b[41m";
        inline const constexpr char *green = "\u001b[42m";
        inline const constexpr char *yellow = "\u001b[43m";
        inline const constexpr char *blue = "\u001b[44m";
        inline const constexpr char *magenta = "\u001b[45m";
        inline const constexpr char *cyan = "\u001b[46m";
        inline const constexpr char *white = "\u001b[47m";
    }  // namespace bg8

    inline namespace fg16 {
        inline const constexpr char *red = "\u001b[91m";
        inline const constexpr char *green = "\u001b[92m";
        inline const constexpr char *yellow = "\u001b[93m";
        inline const constexpr char *blue = "\u001b[94m";
        inline const constexpr char *magenta = "\u001b[95m";
        inline const constexpr char *cyan = "\u001b[96m";
        inline const constexpr char *white = "\u001b[97m";
        inline const constexpr char *black = "\u001b[30m";
        inline const constexpr char *gray = "\u001b[90m";
    }  // namespace fg16

    inline namespace bg16 {
        inline const constexpr char *red = "\u001b[101m";
        inline const constexpr char *green = "\u001b[102m";
        inline const constexpr char *yellow = "\u001b[103m";
        inline const constexpr char *blue = "\u001b[104m";
        inline const constexpr char *magenta = "\u001b[105m";
        inline const constexpr char *cyan = "\u001b[106m";
        inline const constexpr char *white = "\u001b[107m";
        inline const constexpr char *black = "\u001b[40m";
        inline const constexpr char *gray = "\u001b[100m";
    }  // namespace bg16

    inline namespace fg256 {
        inline const constexpr char *black = "\x1b[38;5;0m";
        inline const constexpr char *maroon = "\x1b[38;5;1m";
        inline const constexpr char *green = "\x1b[38;5;2m";
        inline const constexpr char *olive = "\x1b[38;5;3m";
        inline const constexpr char *navy = "\x1b[38;5;4m";
        inline const constexpr char *purple = "\x1b[38;5;5m";
        inline const constexpr char *teal = "\x1b[38;5;6m";
        inline const constexpr char *silver = "\x1b[38;5;7m";
        inline const constexpr char *grey = "\x1b[38;5;8m";
        inline const constexpr char *red = "\x1b[38;5;9m";
        inline const constexpr char *lime = "\x1b[38;5;10m";
        inline const constexpr char *yellow = "\x1b[38;5;11m";
        inline const constexpr char *blue = "\x1b[38;5;12m";
        inline const constexpr char *fuchsia = "\x1b[38;5;13m";
        inline const constexpr char *aqua = "\x1b[38;5;14m";
        inline const constexpr char *white = "\x1b[38;5;15m";
        inline const constexpr char *grey0 = "\x1b[38;5;16m";
        inline const constexpr char *grey1 = "\x1b[38;5;232m";
        inline const constexpr char *grey2 = "\x1b[38;5;233m";
        inline const constexpr char *grey3 = "\x1b[38;5;234m";
        inline const constexpr char *grey4 = "\x1b[38;5;235m";
        inline const constexpr char *grey5 = "\x1b[38;5;236m";
        inline const constexpr char *custom(int red, int green, int blue) {
            const int BASE = 0x10;
            const int COLOR = 0x24;
            std::string code = "\x1b[38;5;";
            code += std::to_string(BASE + COLOR * red + 6 * green + blue);
            code += "m";
            const char *cstr = code.c_str();
            return cstr;
        }
    }  // namespace fg256

    inline namespace bg256 {
        inline const constexpr char *black = "\x1b[48;5;0m";
        inline const constexpr char *maroon = "\x1b[48;5;1m";
        inline const constexpr char *green = "\x1b[48;5;2m";
        inline const constexpr char *olive = "\x1b[48;5;3m";
        inline const constexpr char *navy = "\x1b[48;5;4m";
        inline const constexpr char *purple = "\x1b[48;5;5m";
        inline const constexpr char *teal = "\x1b[48;5;6m";
        inline const constexpr char *silver = "\x1b[48;5;7m";
        inline const constexpr char *grey = "\x1b[48;5;8m";
        inline const constexpr char *red = "\x1b[48;5;9m";
        inline const constexpr char *lime = "\x1b[48;5;10m";
        inline const constexpr char *yellow = "\x1b[48;5;11m";
        inline const constexpr char *blue = "\x1b[48;5;12m";
        inline const constexpr char *fuchsia = "\x1b[48;5;13m";
        inline const constexpr char *aqua = "\x1b[48;5;14m";
        inline const constexpr char *white = "\x1b[48;5;15m";
        inline const constexpr char *grey0 = "\x1b[48;5;16m";
        inline const constexpr char *grey1 = "\x1b[48;5;232m";
        inline const constexpr char *grey2 = "\x1b[48;5;233m";
        inline const constexpr char *grey3 = "\x1b[48;5;234m";
        inline const constexpr char *grey4 = "\x1b[48;5;235m";
        inline const constexpr char *grey5 = "\x1b[48;5;236m";
        inline const constexpr char *custom(int red, int green, int blue) {
            const int BASE = 0x10;
            const int COLOR = 0x24;
            std::string code = "\x1b[48;5;";
            code += std::to_string(BASE + COLOR * red + 6 * green + blue);
            code += "m";
            const char *cstr = code.c_str();
            return cstr;
        }
    }  // namespace bg256
}  // namespace colors

#endif  // COLORS_H