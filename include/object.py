from typing import Annotated, Any, Iterable, Self
from weakref import ref
import inspect, os, re

terminal_width: int = os.get_terminal_size().columns


def compare_with_type(__value: object, __type: type) -> bool:
    if __type in __primitive__:
        return type(__value) in __primitive__[__type]
    return type(__value) is __type

char = Annotated[str, "char"]

class object(object):
    __additional_types__: list[type] = []
    __value__: object = None
    
    def __check_type(self, __value: object) -> bool:
        if type(__value) in self.__additional_types__:
            return True
        if type(__value) is type(self.__value__):
            return True
        return False
    
def panic(__error: ref[Exception], *mark: tuple[Any]) -> exit:
    lines_to_print: int = 50
    mark = [str(item) for item in mark]
    
    name: str = __error.__class__.__name__
    message: str = str(__error)

    line_no: int = inspect.currentframe().f_back.f_back.f_lineno
    file: str = inspect.currentframe().f_back.f_code.co_filename
    lines: list[str] = open(file, "r").readlines()[((line_no-lines_to_print) if line_no-lines_to_print > 0 else 0):line_no]

    chars    = {
        "dash": "─",
        "b-left": "╰",
        "b-right": "╯",
        "straight": "│",
        "t-left": "╭",
        "t-right": "╮",
    }

    import sys
    does_support_colors: bool =  sys.stdout.isatty()
    if does_support_colors:
        red      = "\u001b[31m"
        bold_red = "\u001b[31;1m"
        reset    = "\u001b[0m"
        gray     = "\u001b[90m"
        yellow   = "\u001b[33m"
        green    = "\u001b[32m"
    else:
        red, bold_red, reset, gray, yellow, green = "", "", "", "", "", ""
    
    def calculate_skip_ammout (line: str) -> int:
        output: int = 0
        if line[0] == '│':
            output += 1
        for char in s_u(line[1:]):
            if char == ' ':
                output += 1
            elif char.isnumeric():
                output += 1
            elif char == '|':
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
            if index <= skip_amount: continue
            if char == ' ':
                output += 1
            else: break
        return output + (1 if does_support_colors else 0)
    
    def line_without_spaces(line: str) -> str:
        # line = "    │ 102 | a.__set__(1221)                              │"
        # output = "a.__set__(1221)"
        skip_amount: int = calculate_skip_ammout(line)
        spaces: int = count_spaces(line)
        output: str = line[(spaces+skip_amount):]
        return output
    
    
    def mark_all(line: str, mark_line: int) -> list[str]:
        # mark_line = "│ ~~~~~"
        # line = "│ 102 | a.__set__(1221)                                 │"
        # output = ["│ 102 | a.__set__(1221)                              │",
        #           "│ ~~~~~           ^^^^                               │"]
        output: list[str] = []
        output_line = []
        line = line.rstrip()
        
        mark_line += ' ' * ((len(s_u(line)) - len(s_u(mark_line))))
        mark_line = list(mark_line)
        marked: bool = False
        
        skip_amount: int = calculate_skip_ammout(line)

        if mark:
            for item in mark:
                len_of_item: int = len(item)
                for index in range(len(line)):
                    if index <= skip_amount: continue
                    if line[index:index+len_of_item] == str(item):
                        #mark_line[(index-2):(index+len_of_item)] = f"{red}^{reset}" * len_of_item
                        mark_line = mark_line[:index-2] + [f"{bold_red}^{reset}"] * len_of_item + mark_line[(index-2)+len_of_item:]
                        marked = True
            line = list(line)
            for item in mark:
                len_of_item = len(item)
                for index in range(len(line)):
                    if index <= skip_amount: continue
                    if "".join(line[index:index+len_of_item]) == item:
                        line[index:index+len_of_item] = [f"{bold_red}{item}{reset}"]
                        break
            output_line = "".join(line)
        
        if not marked:
            output_line = line
            mark_line = list("".join(mark_line[:-2]).rstrip() + ' ')
            mark_line += ['  '] +  [' ']*count_spaces(output_line) + [f"{red}~{reset}"]*(len(line_without_spaces(lines[-1])) - (1 if does_support_colors else 2))
            if len(mark_line) > terminal_width:
                mark_line = mark_line[:terminal_width-3] + [' '] + [f"{red}{chars['straight']}{reset}"]
            else:
                mark_line += [' ']*((len(s_u(line)) - len(s_u(mark_line)))-1) + [f"{red}{chars['straight']}{reset}"]
            mark_line = "".join(mark_line)
            
        output.append(output_line)
        output.append("".join(mark_line) + (f"\b {red}{chars['straight']}{reset}" if marked else ""))
        
        return "\n".join(output)
    
    def s_u(line: str|list) -> str:
        # \u001b\[\d+m wiht also match \u001b[91;1m
        if isinstance(line, list):
            return list(re.sub(r"\u001b\[\d+(m|\;\d+m)", "", "".join(line)))
        return re.sub(r"\u001b\[\d+(m|\;\d+m)", "", line)
    
    def process_lines(line: str, index: int) -> str:
        # called fro each element in lines
        current_line_no: int = ((line_no-lines_to_print) + 1) + index
        if current_line_no == line_no:
            line = f"{red}{chars['straight']}{bold_red} {str(current_line_no).center(len(str(line_no)))} | {reset}{line}".rstrip()
        else:
            line = f"{red}{chars['straight']}{gray} {str(current_line_no).center(len(str(line_no)))} | {reset}{line}".rstrip()
        # add spaces to the end of the line until it reaches the terminal width
        if len(s_u(line)) > (terminal_width-1):
            line = line[:terminal_width+(9 if does_support_colors else -5)] + "..."

        line = line + (" " * (terminal_width - (len(s_u(line))+1))) + f"{red}{chars['straight']}{reset}"
        return line
    
    top_section: list[str] = f"{red}{chars['t-left']}{chars['dash']}{reset} {bold_red}{name} {red}{chars['dash'] * (terminal_width-2-len(name)-3)}{reset}{red}{chars['t-right']}{reset}"
    
    print(top_section)
    
    mid_section = [process_lines(line, index) for index, line in enumerate(lines)]
    
    print("\n".join(mid_section[:-1]))
    print(mark_all(mid_section[-1], f"{red}│ {gray}{'~'*len(str(line_no).center(len(str(line_no+(lines_to_print-1)))))}{reset}"))
    print(f"{red}{chars['straight']}{' '*(terminal_width-2)}{chars['straight']}{reset}")
    
    # hex codes look like this: <Hex(x...)>
    hex_code = re.search(r"<Hex\((\d+)\.(\w+)\)>", message)
    _hex_code = hex_code
    if hex_code:
        hex_code = f"{hex_code.group(1)}.{hex_code.group(2)}"
        message = message.replace(f"<Hex({hex_code})>: ", f"")
        hex_code = f"{red}{chars['straight']} {chars['dash']*2} {bold_red}{hex_code}{red} {chars['dash']*(terminal_width-4-len(hex_code)-4)} {chars['straight']}{reset}"
        print(hex_code)
    
    def process_message(message: str) -> list[str]:
        # wrap message into lines that fit the terminal width
        # also add | to the start and end of each line
        output: list[str] = []
        import textwrap
        if hex_code:
            message += f"\nIf this is your first time seeing this error, and you are not sure how to fix it, type \'helix doc {_hex_code.group(1)}.{_hex_code.group(2)}\'."
        for line in message.split("\n"):
            for line2 in textwrap.wrap(line, terminal_width-4):
                output.append(f"{red}{chars['straight']}{reset} {line2.ljust(terminal_width-4)} {red}{chars['straight']}{reset}")
        return [out.replace(f"\'helix doc {_hex_code.group(1)}.{_hex_code.group(2)}\'", f"{yellow}\'helix doc {_hex_code.group(1)}.{_hex_code.group(2)}\'{reset}") for out in output]
    print("\n".join(process_message(message)))

    
    len_of_file: int = len(file + ':' + str(line_no))
    len_of_halfs = int(((terminal_width-4)/2 - len_of_file/2))
    
    if (len_of_halfs) < 2:
        import os
        file = '.' + os.sep + os.path.relpath(file)
        len_of_file: int = len(file + ':' + str(line_no))
        len_of_halfs = int(((terminal_width-4)/2 - len_of_file/2))
    
    # check if terminal width is even
    print(f"{red}{chars['b-left']}{chars['dash']*len_of_halfs} {green}{file}{gray}:{green}{line_no}{red} {'' if terminal_width % 2 != 0 else ' '}{chars['dash']*len_of_halfs}{chars['b-right']}{reset}")
    exit(1)
    
    
class string(object):
    __value__: Any = None # type: ignore

    def __check_type(self, __value: Any) -> bool:
        if compare_with_type(__value, str):
            return True
        if type(__value) is type(self.__value__):
            return True
        return False

    def __add__(self, other: Any) -> str:
        if self.__check_type(other):
            return self.__value__ + other
        try:
            return self.__value__ + str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' + '{type(other).__name__}'")
        
    def __radd__(self, other: Any) -> str:
        if self.__check_type(other):
            return other + self.__value__
        try:
            return str(other) + self.__value__
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(other).__name__}'+d '{type(self).__name__}'")
    
    def __iadd__(self, other: Any) -> str:
        if self.__check_type(other):
            self.__value__ += other
            return self.__value__
        try:
            self.__value__ += str(other)
            return self.__value__
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' + '{type(other).__name__}'")
        
    def __mul__(self, other: int) -> str:
        if compare_with_type(other, int):
            return self.__value__ * other
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' * '{type(other).__name__}'")
    
    def __rmul__(self, other: int) -> str:
        if compare_with_type(other, int):
            return other * self.__value__
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(other).__name__}' * '{type(self).__name__}'")
    
    def __imul__(self, other: int) -> str:
        if compare_with_type(other, int):
            self.__value__ *= other
            return self.__value__
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' * '{type(other).__name__}'")
    
    def __getitem__(self, index: int) -> str:
        if compare_with_type(index, int):
            return self.__value__[index]
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}'[{type(index).__name__}]")
    
    def __setitem__(self, index: int, value: Any) -> str:
        _: list[char] = list(self.__value__)
        
        if compare_with_type(index, int) and compare_with_type(value, str):
            _[index] = value
            self.__value__ = "".join(_)
            
            del _
            return self.__value__
        
        del _
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}'[{type(index).__name__}]")
    
    def __delitem__(self, index: int) -> str:
        _: list[char] = list(self.__value__)
        
        if compare_with_type(index, int):
            del _[index]
            self.__value__ = "".join(_)
            
            del _
            return self.__value__
        
        del _
        raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}'[{type(index).__name__}]")
    
    def __iter__(self) -> Iterable[str]:
        return iter(list(self.__value__))
    
    def __contains__(self, value: Any) -> bool:
        if not compare_with_type(value, str):
            raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' in '{type(value).__name__}'")
        
        return value in self.__value__
     
    def __len__(self) -> int:
        return len(self.__value__)
    
    def __eq__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ == other
        try:
            return self.__value__ == str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' == '{type(other).__name__}'")
        
    def __ne__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ != other
        try:
            return self.__value__ != str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' != '{type(other).__name__}'")
        
    def __lt__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ < other
        try:
            return self.__value__ < str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' < '{type(other).__name__}'")
        
    def __gt__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ > other
        try:
            return self.__value__ > str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' > '{type(other).__name__}'")
        
    def __le__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ <= other
        try:
            return self.__value__ <= str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' <= '{type(other).__name__}'")
        
    def __ge__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ >= other
        try:
            return self.__value__ >= str(other)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' >= '{type(other).__name__}'")
        
    def __bool__(self) -> bool:
        return bool(self.__value__)
    
    def __str__(self) -> str:
        return str(self.__value__)
    
    def __repr__(self) -> str:
        return f"<String({self.__value__})>"
    
    def __cast__(self, __type: type) -> Any:
        if compare_with_type(self.__value__, __type): return self.__value__
        try: return __type(self.__value__)
        except: raise TypeError(f"<String(02.E4)>: cannot cast type '{type(self).__name__}' to '{__type.__name__}'")
        
    def __init__(self, value: Any) -> None:
        if not compare_with_type(value, str):
            # try to cast value to string
            try: value = str(value)
            except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}'")

        self.__value__ = value
        del value
        
    def __copy__(self) -> Self:
        return type(self)(self.__value__)
    
    def __deepcopy__(self) -> Self:
        return type(self)(self.__value__)
    
    def __hash__(self) -> int:
        return hash(self.__value__)
    
    def __format__(self, format_spec: Any) -> str:
        return self.__value__.__format__(format_spec)
    
    def __new__(cls, value: Any) -> Self:
        # try to cast value to string
        try: value = str(value)
        except: raise TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}'")
        
        # create new instance
        self = super().__new__(cls)
        self.__init__(value)
        
        del value

        return self
    
    def __del__(self) -> None:
        del self.__value__
    
    def __call__(self, value: Any) -> Self:
        return type(self)(value)
    
    def __set__(self, value: Any) -> None:
        if not compare_with_type(value, str):
            # try to cast value to string
            panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}', cannot auto cast to '{type(self).__name__}'"), value, "__set__")
        self.__value__ = value

class i8(object):
    __value__: Any = None # type: ignore
    __max__: int = 127
    __min__: int = -128

    def __check_range__(self, other: int | None = None) -> int:
        if other:
            if other > self.__max__ or other < self.__min__:
                panic(ValueError(f"<Hex(02.E3)>: value '{other}' is out of range"), "self")
            
        if self.__value__ > self.__max__ or self.__value__ < self.__min__:
            panic(ValueError(f"<Hex(02.E3)>: value '{self.__value__}' is out of range"), "self")

        if other: return other
        return self.__value__
        
    def __check_type(self, __value: Any) -> bool:
        if compare_with_type(__value, int):
            return True
        if type(__value) is type(self.__value__):
            return True
        return False

    def __add__(self, other: Any) -> int:
        if self.__check_type(other):
            return self.__check_range__(self.__value__ + other)
        try:
            return self.__check_range__(self.__value__ + int(other))
        except: panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' + '{type(other).__name__}'"))
        
    def __radd__(self, other: Any) -> int:
        if self.__check_type(other):
            return self.__check_range__(other + self.__value__)
        try:
            return self.__check_range__(int(other) + self.__value__)
        except: panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(other).__name__}' + '{type(self).__name__}'"))
    
    def __iadd__(self, other: Any) -> int:
        if self.__check_type(other):
            self.__value__ += other
            return self.__check_range__()
        try:
            self.__value__ += int(other)
            return self.__check_range__()
        except: panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' + '{type(other).__name__}'"))
        
    def __mul__(self, other: int) -> int:
        if compare_with_type(other, int):
            return self.__check_range__(self.__value__ * other)
        panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' * '{type(other).__name__}'"))
    
    def __rmul__(self, other: int) -> int:
        if compare_with_type(other, int):
            return self.__check_range__(other * self.__value__)
        panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(other).__name__}' * '{type(self).__name__}'"))
    
    def __imul__(self, other: int) -> int:
        if compare_with_type(other, int):
            self.__value__ *= other
            return self.__check_range__()
        panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' * '{type(other).__name__}'"))
    
    def __getitem__(self, index: int) -> int:
        panic(AttributeError(f"<Hex(04.E2)>: cannot get item from '{type(self).__name__}'"))
    
    def __setitem__(self, index: int, value: Any) -> int:
        panic(AttributeError(f"<Hex(04.E2)>: cannot set item to '{type(self).__name__}'"))

    def __delitem__(self, index: int) -> int:
        panic(AttributeError(f"<Hex(04.E2)>: cannot delete item from '{type(self).__name__}'"))
    
    def __iter__(self) -> Iterable[int]:
        panic(AttributeError(f"<Hex(04.E2)>: cannot iterate '{type(self).__name__}'"))
    
    def __contains__(self, value: Any) -> bool:
        panic(AttributeError(f"<Hex(04.E2)>: cannot check if '{type(self).__name__}' contains '{type(value).__name__}'"))
    
    def __len__(self) -> int:
        panic(AttributeError(f"<Hex(04.E2)>: cannot get length of '{type(self).__name__}'"))
    
    def __eq__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ == other
        try:
            return self.__value__ == int(other)
        except: panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' == '{type(other).__name__}'"))
        
    def __ne__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ != other
        try:
            return self.__value__ != int(other)
        except: panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' != '{type(other).__name__}'"))
        
    def __lt__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ < other
        try:
            return self.__value__ < int(other)
        except: panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' < '{type(other).__name__}'"))
        
    def __gt__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ > other
        try:
            return self.__value__ > int(other)
        except: panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' > '{type(other).__name__}'"))
        
    def __le__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ <= other
        try:
            return self.__value__ <= int(other)
        except: panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' <= '{type(other).__name__}'"))
        
    def __ge__(self, other: Any) -> bool:
        if self.__check_type(other):
            return self.__value__ >= other
        try:
            return self.__value__ >= int(other)
        except: panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(self).__name__}' >= '{type(other).__name__}'"))
        
    def __bool__(self) -> bool:
        return bool(self.__value__)
    
    def __str__(self) -> str:
        return str(self.__value__)
    
    def __repr__(self) -> str:
        return f"i8({self.__value__})"
    
    def __cast__(self, __type: type) -> Any:
        if compare_with_type(self.__value__, __type): return self.__value__
        try: return __type(self.__value__)
        except: panic(TypeError(f"<i8(02.E4)>: cannot cast type '{type(self).__name__}' to '{__type.__name__}'"))
    
    def __init__(self, value: Any) -> None:
        if not compare_with_type(value, int):
            # try to cast value to int
            try: value = int(value)
            except: panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}'"))

        self.__value__ = value
        self.__check_range__()
        del value
        
    def __copy__(self) -> Self:
        return type(self)(self.__value__)
    
    def __deepcopy__(self) -> Self:
        return type(self)(self.__value__)
    
    def __hash__(self) -> int:
        return hash(self.__value__)
    
    def __format__(self, format_spec: Any) -> str:
        return self.__value__.__format__(format_spec)
    
    def __new__(cls, value: Any) -> Self:
        # try to cast value to int
        try: value = int(value)
        except: panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}'"))
        
        # create new instance
        self = super().__new__(cls)
        self.__init__(value)
        
        del value

        return self
    
    def __del__(self) -> None:
        del self.__value__
        
    def __call__(self, value: Any) -> Self:
        panic(AttributeError(f"<Hex(04.E2)>: cannot call '{type(self).__name__}'"))

    def __set__(self, value: Any) -> None:
        if not compare_with_type(value, int):
            # try to cast value to int
            panic(TypeError(f"<Hex(02.E1)>: type mismatch for '{type(value).__name__}', cannot auto cast to '{type(self).__name__}'"))
        
        self.__value__ = value
        self.__check_range__()
    
__primitive__: dict[type, tuple[type, ...]] = {
    int: (int, float),
    str: (str, string),
}
    
a = string("Hello, World! is not TRUEEEEEEEEEEEEEEEEEE!")

a.__add__(i8(1221))

# a: string = "Hello, World!"

print(a)
    