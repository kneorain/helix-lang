import inspect
import os
import re
from sys import exit
from sys import stdout as sys_stdout
from types import FrameType
from typing import Any, NoReturn, Optional
from weakref import ref

from pygments import highlight  # type: ignore
from pygments.formatters import (  # type: ignore
    Terminal256Formatter,
    TerminalTrueColorFormatter,
)
from pygments.lexer import RegexLexer, bygroups, include  # type: ignore
from pygments.lexers import get_lexer_by_name  # type: ignore
from pygments.token import (  # type: ignore
    Comment,
    Keyword,
    Literal,
    Name,
    Number,
    Operator,
    Punctuation,
    String,
    Whitespace,
)

class HelixSyntaxHighlightingLexer(RegexLexer):
    name = "Helix"
    aliases = ["Helix"]
    filenames = ["*.hlx"]
    base_style = "one-dark"
    background_color = "default"

    tokens = {
        "root": [
            (r"\bfor\b", Keyword),
            include("comments"),
            include("block-comments"),
            include("keywords"),
            include("constants"),
            include("functions"),
            include("types"),
            include("in_line_replace"),
            include("namespaces"),
            include("punctuation"),
            include("strings"),
            include("variables"),
            include("class_reference"),
            (r"\s+", Whitespace),
        ],
        "comments": [(r"~~.*$", Comment.Single)],
        "block-comments": [
            (r"~\*~", Comment.Multiline, "block-comment"),
            (r"~\*", Comment.Multiline, "block-comment"),
        ],
        "block-comment": [
            (r"[^~]+", Comment.Multiline),
            (r"~\*", Comment.Multiline, "#push"),
            (r"\*~", Comment.Multiline, "#pop"),
            (r"~", Comment.Multiline),
        ],
        "constants": [
            (
                r"\b\d[\d_]*(\.?)[\d_]*(?:(E|e)([+-]?)([\d_]+))?(f32|f64|i128|i16|i32|i64|i8|isize|u128|u16|u32|u64|u8|usize)?\b",
                Number,
            ),
            (
                r"\b0x[\da-fA-F_]+(i128|i16|i32|i64|i8|isize|u128|u16|u32|u64|u8|usize)?\b",
                Number,
            ),
            (
                r"\b0o[0-7_]+(i128|i16|i32|i64|i8|isize|u128|u16|u32|u64|u8|usize)?\b",
                Number,
            ),
            (
                r"\b0b[01_]+(i128|i16|i32|i64|i8|isize|u128|u16|u32|u64|u8|usize)?\b",
                Number,
            ),
            (r"\b(true|false)\b", Literal),
        ],
        "types": [
            (r"\b(int|float|double|char|string|bool|byte|short|long)\b", Name.Builtin),
            (r"\b(array|list|tuple|map|set)\b", Name.Class),
            (r"\b(void|opt)\b", Name.Class),
            (
                r"\b(class|struct|enum|union)\s+([A-Z][A-Za-z0-9_]*)(<)([A-Z][A-Za-z0-9_]*)(>)\b",
                bygroups(Keyword, Name.Class, Punctuation, Name.Class, Punctuation),
            ),
            (r"\b([A-Z][A-Za-z0-9_]*)\b", Name.Class),
        ],
        "keywords": [
            (
                r"\b(if|else|else\s+if|while|break|continue|return|switch|case|default|stop)\b",
                Keyword,
            ),
            (r"\b(fn|return|yield|async|for|await|lambda|delegate)\b", Keyword),
            (r"\b(class|struct|new|interface|private|protected|final)\b", Keyword),
            (r"\b(impl|abstract)\b", Keyword),
            (r"\b(try|catch|finally|throw)\b", Keyword),
            (r"\b(let|const|var|final)\b", Keyword),
            (r"\b(public|private|protected)\b", Keyword),
            (r"\b(include|import|using|from)\b", Keyword),
            (r"\b(async|await|thread|yield|yield\s+from)\b", Keyword),
            (r"\b(in|override|static|ref|type|->)\b", Keyword),
            (
                r"(\+|\-|\*|\/|\%|\+\+|\-\-|\+=|\-=|\*=|\/=|\%=|==|!=|>|<|>=|<=|===|!==|&&|\|\||!|&|\||\^|~|<<|>>|\.|::|\?|,|=>|@|\#)",
                Operator,
            ),
        ],
        "functions": [
            (r"\bfn\b", Keyword),
            (r"([A-Za-z_][A-Za-z0-9_]*)\s*(\()", bygroups(Name.Function, Punctuation)),
            (r"\b(self|super)\b", Name.Builtin.Pseudo),
        ],
        "in_line_replace": [
            (
                r"(([a-z_][A-Za-z0-9_]*!)|([A-Z_][A-Za-z0-9_]*!))",
                bygroups(Name.Function, Name.Class),
            ),
        ],
        "namespaces": [
            (
                r"(?<![A-Za-z0-9_])([A-Za-z0-9_]+)(::)",
                bygroups(Name.Namespace, Punctuation),
            ),
        ],
        "punctuation": [
            (r"(\(|\)|\[|\]|\{|\})", Punctuation),
            (r"(\,)", Punctuation),
            (r"(\.\.\.)", Punctuation),
        ],
        "strings": [
            # Double-quoted strings
            (r'"[^"\\]*(?:\\.[^"\\]*)*"', String),
            # Single-quoted strings
            (r"'[^'\\]*(?:\\.[^'\\]*)*'", String.Char),
        ],
        "variables": [
            (r"(?<![A-Za-z0-9_])([A-Za-z0-9_]+)(?![A-Za-z0-9_])", Name.Variable),
        ],
        "class_reference": [
            # self
            (r"\bself\b", Name.Builtin.Pseudo),
            # super
            (r"\bsuper\b", Name.Builtin.Pseudo),
        ],
    }


Helix_lexer = HelixSyntaxHighlightingLexer()
formatter = (
    TerminalTrueColorFormatter(style="one-dark")
    if sys_stdout.isatty()
    else Terminal256Formatter(style="one-dark")
)


def highlight_code(code: str, lang: Optional[str] = None) -> str:
    if not lang:
        return highlight(code, Helix_lexer, formatter)
    if lang == "helix":
        return highlight(code, Helix_lexer, formatter)
    else:
        return highlight(code, get_lexer_by_name(lang), formatter)


try:
    terminal_width: int = os.get_terminal_size().columns
except OSError:
    terminal_width = 80
from threading import Lock

lock = Lock()


def standalone_tokenize_line(line: str, preserve_spaces: bool = False) -> list[str]:
    import re

    back_slash = "\\"
    if preserve_spaces:
        space_group = r"(\s+)"
    else:
        space_group = r"\s+"

    # Pattern for ANSI color escape sequences
    color_escape_pattern = r"(\x1b\[[0-9;]*m)"

    double_character_operators = ['\\=\\=\\=', '\\!\\=\\=', '\\.\\.\\.', '\\=\\=', '\\!\\=', '\\-\\>', '\\<\\-', '\\<\\=', '\\>\\=', '\\&\\&', '\\-\\-', '\\:\\:', '\\|\\|', '\\+\\+', '\\+\\=', '\\-\\=', '\\*\\=', '\\/\\=', '\\&\\=', '\\|\\=', '\\^\\=', '\\%\\=', '\\*\\*', '\\<\\<', '\\>\\>', '\\<\\<\\=', '\\>\\>\\=', '\\=\\>', '\\@\\=', '\\_\\_', '\\?\\?', '\\?\\:', '\\?\\=']
    comment_pattern = r"\~\~.*"
    multi_line_comment_pattern = r"\~\*\~"
    
    pattern = re.compile(
        rf"""
            {color_escape_pattern}                                                                                      | # ANSI color escape sequences
            ({back_slash.join(comment_pattern.split())}[^\n]*)                                                                | # Single line comments (~~)
            ({back_slash.join(multi_line_comment_pattern.split())}[\s\S]*?{back_slash.join(multi_line_comment_pattern.split())})                          | # Multi line comments (~*~ ... ~*~)
            (\b\d+\.\d+\b)                                                                                              | # Decimal numbers
            (\b\w+\b)                                                                                                   | # Words (identifiers, keywords)
            ({'|'.join(double_character_operators)})                                      | # Double character operators
            ([\(\){{}};,])                                                                                              | # Single character delimiters
            {space_group}                                                                                               | # Spaces
            (\S)                                                                                                        | # Catch other characters
        """,
        re.MULTILINE | re.VERBOSE,
    )

    tokens: list[list[str]] = [
        [token for token in match if token] for match in pattern.findall(line)
    ]

    return [
        token
        for group in tokens
        for token in group
        if token
        and not token.startswith(r"\~\~.*")
        and not token.startswith(r"\~\*\~")
        and not token.endswith(r"\~\*\~")
    ]


def s_u(line: str | list) -> str | list[str]:
    # \u001b\[\d+m wiht also match \u001b[91;1m
    if isinstance(line, list):
        return list(re.sub(r"\u001b\[\d+(m|\;\d+m)", "", "".join(line)))
    return re.sub(r"\u001b\[\d+(m|\;\d+m)", "", line)


def s_u2(line: str | list) -> str:
    ansi_escape = re.compile(
        r"""
        \x1b  # ESC
        \[    # literal [
        [0-9;]*  # zero or more numbers or semicolons
        [A-Za-z]  # a letter
        """,
        re.VERBOSE,
    )
    if isinstance(line, list):
        line = "".join(line)
    return ansi_escape.sub("", line)


def __panic__(
    __error: type[BaseException] | BaseException | Exception,
    *_mark: Any | str,
    file: str = "",
    line_no: int = 0,
    no_lines: bool = False,
    multi_frame: bool = False,
    pos: int = 0,
    replacements: Optional[dict[str, str]] = None,
    follow_marked_order: bool = False,
    mark_start: Optional[int] = None,
    thread_name: Optional[str] = None,
    no_exit: bool = False,
    lang: str = "",
    _code: Optional[str] = None,
): # type: ignore
    lock.acquire(blocking=True, timeout=0.2)
    
    use_border: bool = False
    final_output: str = ""
    single_frame: bool = False
    
    
    if thread_name and not multi_frame:
        multi_frame = True
        single_frame = True
    
    _mark = () if len(_mark) == 1 and _mark[0] == None else _mark
    lines_to_print: int = 5
    mark: list[str] = [item.__str__() for item in _mark]

    name: str = __error.__class__.__name__

    if name and name == "str":
        name = "rs::std::panic!"
    
        
    message: str = s_u2(s_u(str(__error)))

    if "\r\0\r\0\r\r\0" in message:
        name = "rs::" + message.split("\r\0\r\0\r\r\0")[0]
        message = "\r\0\r\0\r\r\0".join(message.split("\r\0\r\0\r\r\0")[1:])

    
    if name == "KeyboardInterrupt" and message.strip() == "":
        message = "KeyboardInterrupt was raised."

    # Second loop: process each relevant frame
    class custom_string:
        def __init__(self, *options: str):
            self.options = tuple(options)

        def __str__(self):
            return self

        def __repr__(self):
            return " | ".join(self.options)

        def __eq__(self, other):
            return other in self.options

        def __contains__(self, other):
            return other in self.options

    if replacements:
        for key, value in replacements.items():
            # for token in standalone_tokenize_line(message):
            #    if token == key:
            #        message = message.replace(token, value if token not in ('.', '::') else '->')
            if mark:
                for index, token in enumerate(mark):
                    if token == key:
                        mark[index] = value if token not in (".", "::") else custom_string(".", "::")  # type: ignore

    frame: FrameType | None = inspect.currentframe()
    if frame is not None:
        line_no: int = frame.f_back.f_back.f_lineno if not line_no else line_no  # type: ignore
        file: str = frame.f_back.f_code.co_filename if not file else file  # type: ignore
        try:
            lines: list[str] = open(file, "r").readlines()[
                (
                    (line_no - lines_to_print) if line_no - lines_to_print > 0 else 0
                ) : line_no
            ]
        except Exception:
            lines = [
                f"Panic failed, '{file}' (likely due to an eval statement in the previous stack frame)."
            ]
    else:
        raise ValueError("Panic failed, could not find the right stack frame.")

    lang_dict: dict[str, str] = {
        # file extensions | language
        "py": "python",
        "hlx": "helix",
        "c": "c",
        "cpp": "cpp",
        "c++": "cpp",
        "java": "java",
        "js": "javascript",
        "ts": "typescript",
        "tsx": "typescript",
        "html": "html",
        "css": "css",
        "scss": "scss",
        "sass": "sass",
        "less": "less",
        "json": "json",
        "xml": "xml",
        "yaml": "yaml",
        "yml": "yaml",
        "sh": "bash",
        "bash": "bash",
        "zsh": "bash",
        "fish": "bash",
        "ps1": "powershell",
        "psm1": "powershell",
        "psd1": "powershell",
        "bat": "batch",
        "cmd": "batch",
        "go": "go",
        "rs": "rust",
        "rb": "ruby",
        "rspec": "ruby",
        "rake": "ruby",
        "gemfile": "ruby",
        "gemspec": "ruby",
        "jbuilder": "ruby",
        "ru": "ruby",
        "erb": "ruby",
        "haml": "ruby",
        "slim": "ruby",
        "vue": "vue",
        "php": "php",
        "php4": "php",
        "php5": "php",
        "php7": "php",
        "php8": "php",
        "phps": "php",
        "phtml": "php",
        "ctp": "php",
        "twig": "php",
        "md": "markdown",
        "markdown": "markdown",
        "mdx": "markdown",
        "rmd": "markdown",
        "h": "c",
        "hpp": "cpp",
        "hh": "cpp",
        "h++": "cpp",
        "hxx": "cpp",
        "inl": "cpp",
        "ipp": "cpp",
        "tcc": "cpp",
        "tpp": "cpp",
        "cc": "cpp",
        "cp": "cpp",
        "cxx": "cpp",
        "c++": "cpp",
    }
    
    does_support_colors: bool = sys_stdout.isatty()

    if not lang:
        lines = [(highlight_code(line) if does_support_colors else line) for line in lines[:-1]] + [lines[-1]]
    else:
        lines = [(highlight_code(line, lang_dict[lang]) if does_support_colors else line) for line in lines[:-1]] + [
            lines[-1]
        ]

    
    chars = {
        "dash": "─",
        "b-left": "╰",
        "b-right": "╯",
        "straight": "│",
        "t-left": "╭",
        "t-right": "╮",
    }
    
    if not use_border:
        chars = {
            "dash": " ",
            "b-left": " ",
            "b-right": " ",
            "straight": "",
            "t-left": " ",
            "t-right": " ",
        }

    import sys


    base_color: str = "31" if not thread_name else "34"
    second_color: str = "93" if not thread_name else "96"
    third_color: str = "93" if not thread_name else "94"

    # WARNING: primary_error_color MUST be a bold color
    primary_error_color = f"\u001b[{base_color};1m" if (does_support_colors) else ("")

    # WARNING: secondary_error_color CANNOT be a bold color
    secondary_error_color = f"\u001b[{third_color}m" if (does_support_colors) else ("")

    # WARNING: border_color CANNOT be a bold color
    border_color = f"\u001b[{base_color}m" if (does_support_colors) else ("")

    reset = "\u001b[0m" if (does_support_colors) else ""
    gray = "\u001b[38;5;250m" if (does_support_colors) else ""
    green = f"\u001b[{second_color}m" if (does_support_colors) else ""
    thread_error_color = "\u001b[34;1m" if (does_support_colors) else ""

    len_of_file: int = len(file + ":" + str(line_no))
    len_of_halfs = int(((terminal_width - 4) / 2 - len_of_file / 2))

    if (len_of_halfs) < 2:
        import os
        try:
            file = "." + os.sep + os.path.relpath(file)
        except ValueError:
            file = "~" + file.replace(os.path.expanduser("~"), "")
        len_of_file = len(file + ":" + str(line_no))
        len_of_halfs = int(((terminal_width - 4) / 2 - len_of_file / 2))

    final_line: str = (
        chars["b-left"]
        + f" {file}:{line_no} ".center(terminal_width - 2, chars["dash"])
        + chars["b-right"]
    )
    final_line = f"{border_color}{final_line}{reset}"
    final_line = (
        final_line.split(file)[0]
        + green
        + file
        + reset
        + gray
        + ":"
        + green
        + str(line_no)
        + border_color
        + final_line.split(":")[
            (1 if ":\\" != ":" + final_line.split(":")[1][0] else 2)
        ][len(str(line_no)) :]
        + reset
    )
    
    def calculate_skip_ammout(line: str) -> int:
        output: int = 0
        if line[0] == "│":
            output += 1
        for char in s_u(line[1:]):
            if char == " ":
                output += 1
            elif char.isnumeric():
                output += 1
            elif char == "|":
                output += 1
                break
        return output

    def count_spaces(line: str) -> int:
        # count spaces at the start of the line
        # line = "    │ 102 | a.__set__(1221)                              │"
        # output = 4
        skip_amount: int = calculate_skip_ammout(line)
        output: int = 0
        for index, char in enumerate(s_u(line)):
            if index <= skip_amount:
                continue
            if char == " ":
                output += 1
            else:
                break
        return output + (1 if does_support_colors else 0)

    def mark_all(line: str, mark_line: str, mark_start: Optional[int] = None) -> str:
        
        tokenized_line: list[str] = standalone_tokenize_line(line, preserve_spaces=True)
        skip = 9 if use_border else 8
        if not tokenized_line[skip].isspace():
            tokenized_line = standalone_tokenize_line(
                "".join(tokenized_line[:skip] + [" "] + tokenized_line[skip:]),
                preserve_spaces=True,
            )
            # remove the space that was added
            tokenized_line = tokenized_line[:skip] + tokenized_line[(skip + 1) :]
        color_escape_pattern = re.compile(r"(\x1b|\u001b)\[\d*(;\d+)*m")
        mark_line += " ┴ " if not use_border else "   "
        total_char_so_far: int = 0
        line_end = len(standalone_tokenize_line(line, preserve_spaces=True)[:-(((4 if use_border else 3) if tokenized_line[skip].isspace() else (5 if use_border else 4)))]) if does_support_colors else ((len(standalone_tokenize_line(line, preserve_spaces=True))-1))

        max_skip: int = 0
        max_start_with_start_space: int = skip
        for token in tokenized_line[:skip]:
            if token.isspace():
                max_start_with_start_space += 1
        max_start_with_start_space -= (3 if tokenized_line[skip].isspace() else 4) if does_support_colors else 4
        
        for token in tokenized_line[:skip]:
            max_skip += len(token)
        
        if not does_support_colors:
            mark_line += " " * (len(tokenized_line[5])-1)

    
        if not does_support_colors:
            return (
            "".join(tokenized_line)
            # (len(tokenized_line[skip-10:])-1)) + length of the middle part of the line
            + (mark_line + "^" + (" " * (len(''.join(tokenized_line[6:-1]))-1)))
            + f"{chars['straight']}{reset}"
        )
        
        if follow_marked_order:
            if not mark:
                raise ValueError("mark cannot be empty if follow_marked_order is True")
            mark_index: int = 0
            for index, token in enumerate(tokenized_line):
                token = s_u2(token)
                if color_escape_pattern.match(token):
                    continue
                total_char_so_far += len(token) if index >= skip else 0
                if index < skip:
                    continue
                                
                if mark_start and (total_char_so_far - len(token)) + 1 <= (mark_start):
                    if (mark_index < len(mark) and token == mark[mark_index]) and mark[
                        mark_index
                    ] not in tokenized_line[index + 1 : index + 5]:
                        mark_start -= 1
                        tokenized_line[index] = f"{secondary_error_color}{token}{reset}"
                        mark_line += f"{secondary_error_color}{'~'*len(token)}{reset}"
                        mark_index += 1
                    else:
                        tokenized_line[index] = highlight_code(
                            token, lang_dict[lang] if lang else "helix"
                        ).strip() if does_support_colors else token
                        mark_line += " " * len(token)
                    continue

                if (
                    mark_index < len(mark)
                    and token == mark[mark_index]
                    and index < line_end
                ):
                    tokenized_line[index] = f"{primary_error_color}{token}{reset}"
                    mark_line += f"{secondary_error_color}{'^'*len(token)}{reset}"
                    mark_index += 1
                elif (
                    mark_index < len(mark)
                    and token.isspace()
                    and index < line_end
                    and mark_index > 0
                ):
                    mark_line += f"{secondary_error_color}{'^'*len(token)}{reset}"
                else:
                    tokenized_line[index] = highlight_code(
                        token, lang_dict[lang] if lang else "helix"
                    ).strip() if does_support_colors else token
                    mark_line += " " * len(token)
        else:
            if not mark:
                # just underline the whole line with ~
                for index, token in enumerate(tokenized_line):
                    token = s_u2(token)
                    if color_escape_pattern.match(token):
                        continue
                    total_char_so_far += len(token) if index >= skip else 0
                    if index < skip:
                        continue
                    if index < line_end and index > max_start_with_start_space:
                        tokenized_line[index] = f"{primary_error_color}{token}{reset}"
                        mark_line += f"{secondary_error_color}{'~'*len(token)}{reset}"
                    else:
                        mark_line += " " * len(token)

            else:
                for index, token in enumerate(tokenized_line):
                    token = s_u2(token)
                    if color_escape_pattern.match(token):
                        continue
                    total_char_so_far += len(token) if index >= skip else 0
                    if index < skip:
                        continue

                    if token in mark and index < line_end:
                        tokenized_line[index] = f"{primary_error_color}{token}{reset}"
                        mark_line += f"{secondary_error_color}{'^'*len(token)}{reset}"
                    else:
                        tokenized_line[index] = highlight_code(
                            token, lang_dict[lang] if lang else "helix"
                        ).strip()  if does_support_colors else token
                        mark_line += " " * len(token)
        tokenized_line[-2] = border_color + s_u2(tokenized_line[-2]) + reset
        ## try:
        ##     end_marking = 0
        ##     segment1 = ""
        ##     for index, token in enumerate("".join(tokenized_line)[max_skip:]):
        ##         if token.startswith('\x1b'): break
        ##         segment1 += token
        ##         end_marking += len(token)
        ##     end_marking += len("".join(tokenized_line)[:max_skip])
        ##     segment1 = "".join(tokenized_line)[:max_skip] + highlight_code(segment1).strip()
        ##     segment2 = "".join(tokenized_line)[end_marking:]
        ##     return segment1 + segment2 + mark_line[:-1] + f"{border_color}{chars['straight']}{reset}"
        ## except Exception:
        ##     return "".join(tokenized_line) + mark_line[:-1] + f"{border_color}{chars['straight']}{reset}"
        return (
            "".join(tokenized_line)
            + (mark_line[:-1] if use_border else mark_line.rstrip())
            + f"{border_color}{chars['straight']}{reset}"
        )

    def process_lines(line: str, index: int) -> str:
        # called fro each element in lines
        current_line_no: int = ((line_no - lines_to_print) + 1) + index
        if current_line_no < 1:
            current_line_no = 1
        if current_line_no == line_no or current_line_no == 1:
            line = f"{border_color}{chars['straight']}{primary_error_color} {str(current_line_no).center(len(str(line_no)))} | {reset}{line}".rstrip()
        else:
            line = f"{border_color}{chars['straight']}{gray} {str(current_line_no).center(len(str(line_no)))} | {reset}{line}".rstrip()
        # add spaces to the end of the line until it reaches the terminal width
        # print(repr(line))
        if len(s_u2(line)) > (terminal_width - 1):
            line = ''.join(standalone_tokenize_line(line, preserve_spaces=True)[:terminal_width + (22 if does_support_colors else 15)])
            if len(s_u2(line)+"...") > (terminal_width - 1):
                line = line[:terminal_width]
            line +=  "..." if not s_u2(line).strip().endswith('|') else "  ..."

        line = (
            line
            + (" " * (terminal_width - (len(s_u2(line))) - 1))
            + f"{border_color}{chars['straight']}{reset}"
        )
        return line
    import os
    if not multi_frame:
        top_section: str = (
            f"{border_color}{chars['t-left']}{chars['dash']}{reset} {((('~' * len(str(line_no)))+ ' | ') if not use_border else '')}{primary_error_color}{name} ▼ {(f"{green}at {file}:{line_no}".replace(os.getcwd(), ".").replace(os.path.expanduser("~"), "~")) if not use_border else ''}{border_color}{(chars['dash'] * (terminal_width-2-len(name)-5)) if use_border else ''}{reset}{border_color}{chars['t-right']}{reset}"
        )
    elif multi_frame and pos == 0:
        trace_title: str = (
            (
                f"{primary_error_color} {'Stack Trace'} {border_color}".center(
                    (((terminal_width - 2) + 12) if does_support_colors else terminal_width-2), chars["dash"]
                ) if use_border else f"{primary_error_color}{'Stack Trace'} {border_color}"
            )
            if not thread_name
            else (
                f"{thread_error_color} Stack Trace @ {thread_name} {border_color}".center(
                    (((terminal_width - 2) + 12) if does_support_colors else terminal_width-2), chars["dash"]
                ) if use_border else f"{thread_error_color}Stack Trace @ {thread_name} {border_color}"
            )
        )
        final_output += (
            f"{border_color}{chars['t-left']}{trace_title}{reset}{border_color}{chars['t-right']}{reset}"
        ) + "\n"
        top_section: str = f"{border_color}{chars['straight']} {reset}{((('~' * len(str(line_no)))+ ' | ') if not use_border else '')}{primary_error_color}{name} ▼ {(f"{green}at {file}:{line_no}".replace(os.getcwd(), ".").replace(os.path.expanduser("~"), "~")) if not use_border else ''}{border_color}{(chars['dash'] * (terminal_width-2-len(name)-5)) if use_border else ''} {reset}{border_color}{chars['straight']}{reset}"  # type: ignore
    else:
        if not use_border:
            final_output += (
                f"{border_color}{chars['straight']}{' '*(terminal_width-2)}{chars['straight']}{reset}"
            ) + "\n"
            __temp = (gray + " Propagated from the following " + border_color if pos == 1 else gray + " Propagation Caused by " + border_color)
            __temp2 = ((terminal_width - 4 - (len(name) if len(name) % 2 == 0 else len(name) - 1)) - 2)
            propagation: str = (__temp.center(__temp2 + 8, chars["dash"]) if use_border else f"{green} at {f"{file}:{line_no}".replace(os.getcwd(), ".").replace(os.path.expanduser("~"), "~")}") + reset  # type: ignore
            top_section: str = f"{border_color}{chars['straight']} {reset}{((('~' * len(str(line_no)))+ ' | ') if not use_border else '')}{primary_error_color}{name} ▼{reset}{border_color}{' ' if (len(propagation)+len(name)+5) % 2 != 0 else ''}{propagation} {border_color}{chars['straight']}{reset}"  # type: ignore
        else:
            final_output += (
                f"{border_color}{chars['straight']}{' '*(terminal_width-2)}{chars['straight']}{reset}"
            ) + "\n"
            __temp = ((terminal_width - 1 - (len(name) if len(name) % 2 == 0 else len(name) - 1)) - 8)
            __temp2 = (" Propagated from the following " if pos == 1 else " Caused by ")
            propagation: str = (__temp2.center(__temp, chars["dash"]) if use_border else __temp2.ljust(__temp, chars["dash"])) + reset  # type: ignore
            top_section: str = f"{border_color}{chars['straight']} {reset}{primary_error_color}{name} ▼{gray}{'  ' if (len(propagation)+len(name)+5) % 2 != 0 else '  '} {propagation} {border_color}{chars['straight']}{reset}"  # type: ignore

    final_output += ((top_section) if use_border else (top_section.strip())) + "\n"
    mid_section = [process_lines(line, index) for index, line in enumerate(lines)]

    if not no_lines:
        final_output += ("\n".join(mid_section[:-1]) + "\n") if line_no != 1 else ''
        final_output += (
            mark_all(
                mid_section[-1],
                f"\n{border_color}{chars['straight']} {gray}{'~'*len(str(line_no).center(len(str(line_no+(lines_to_print-1)))))}{reset}",
                mark_start=mark_start,
            ).strip()
        ) + "\n"
        final_output += ((
            f"{border_color}{chars['straight']}{' '*(terminal_width-2)}{chars['straight']}{reset}"
        ) + "\n") if use_border else f"{primary_error_color} ERROR:{reset}" if pos == 2 or single_frame else ''

    # hex codes look like this: <Hex(x...)>
    
    hex_code: str | (re.Match[str] | None) = re.search(
        r"<Hex\((\d+)\.(\w+)\)>", message
    ) if not _code else None
    _hex_code = hex_code

    if hex_code:
        hex_code = f"{hex_code.group(1)}.{hex_code.group(2)}"  # type: ignore
        message = message.replace(f"<Hex({hex_code})>: ", f"")
        hex_code = f"{border_color}{chars['straight']} {chars['dash']*2} {primary_error_color}{hex_code}{border_color} {chars['dash']*(terminal_width-4-len(hex_code)-4)} {chars['straight']}{reset}"
        somewhat_middle = hex_code if not no_lines else ""
    else:
        if _code:
            somewhat_middle = (
                f"{border_color}{chars['straight']} {chars['dash']*2} {primary_error_color}{_code}{border_color} {chars['dash']*(terminal_width-4-len(_code)-4)} {chars['straight']}{reset}"
                if not no_lines
                else ""
            )
        else:
            somewhat_middle = (
                f"{border_color}{chars['straight']} {chars['dash']*(terminal_width-4)} {chars['straight']}{reset}"
                if not no_lines
                else ""
            )

    if (not multi_frame or (multi_frame and pos == 2)) and not no_lines or single_frame:
        final_output += (somewhat_middle + "\n") if use_border else f"{primary_error_color} {hex_code}:{reset}" if hex_code else ''

    def process_message(message: str) -> list[str]:
        # wrap message into lines that fit the terminal width
        # also add | to the start and end of each line
        output: list[str] = []
        import textwrap

        if not does_support_colors:
            message = "WARNING: Line marking unavailable since the terminal does not support colors.\n--- error ---\n" + message
        
        for line in message.split("\n"):
            for line2 in textwrap.wrap(line, terminal_width - 4):
                output.append(
                    f"{border_color}{chars['straight']}{reset} {line2.ljust(terminal_width-4)} {border_color}{chars['straight']}{reset}"
                )
        
        _temp_msg: str = ""
        if hex_code:
            _temp_msg = f"If this is your first time seeing this error, and you are not sure how to fix it, type 'helix doc {_hex_code.group(1)}.{_hex_code.group(2)}'."  # type: ignore
        elif _code:
            _temp_msg = f"If this is your first time seeing this error, and you are not sure how to fix it, type 'helix doc {_code}'."
    
        if _temp_msg:
            output.append(f"{border_color}{chars['straight']}{reset} {' '*(terminal_width-4)} {border_color}{chars['straight']}{reset}")
            
            for line in textwrap.wrap(_temp_msg, terminal_width - 4):
                output.append(
                    f"{border_color}{chars['straight']}{reset} {line.ljust(terminal_width-4)} {border_color}{chars['straight']}{reset}"
                )
            
        
        if hex_code:
            output[-1] = output[-1].replace(f"'helix doc {_hex_code.group(1)}.{_hex_code.group(2)}'", f"{secondary_error_color}'helix doc {_hex_code.group(1)}.{_hex_code.group(2)}'{reset}")
        elif _code:
            output[-1] = output[-1].replace(f"'helix doc {_code}'", f"{secondary_error_color}'helix doc {_code}'{reset}")
        return output

    if not multi_frame or (multi_frame and pos == 2) or single_frame:
        final_output += ("\n".join(process_message(message))) + "\n"

    # check if terminal width is even
    if use_border:
        if not multi_frame or (multi_frame and pos == 2):
            final_output += (final_line) + "\n"
        else:
            if single_frame:
                final_output += (final_line) + "\n"
            else:
                final_output += (
                    f"{border_color}{chars['straight']} {final_line[6:-11]} {chars['straight']}{reset}"
                ) + "\n"
                final_output += ("\n".join(process_message(message)) + "\n") if (pos == 2) else ''
            
    print(final_output + reset, sep="\n", end="", flush=True)
    
    lock.release()
    #if not no_exit:
    #    exit(1) if not multi_frame or (multi_frame and pos == 2) else None