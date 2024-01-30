from typing import Annotated, Any, Iterable, Self
from weakref import ref
import inspect, os
import re
from src.globals import highlight_code

terminal_width: int = os.get_terminal_size().columns

def panic(__error: ref[Exception], *mark: tuple[Any], file: str = "", line_no: int = 0) -> exit:
    lines_to_print: int = 5
    mark = [str(item) for item in mark]
    
    name: str = __error.__class__.__name__
    message: str = str(__error)

    line_no: int = inspect.currentframe().f_back.f_back.f_lineno if not line_no else line_no
    file: str = inspect.currentframe().f_back.f_code.co_filename if not file else file
    lines: list[str] = open(file, "r").readlines()[((line_no-lines_to_print) if line_no-lines_to_print > 0 else 0):line_no]

    chars    = {
        "dash":     "─",
        "b-left":   "╰",
        "b-right":  "╯",
        "straight": "│",
        "t-left":   "╭",
        "t-right":  "╮",
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
        if current_line_no < 1: current_line_no = 1
        if current_line_no == line_no or current_line_no == 1:
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
    
    print("\n".join(mid_section[:-1])) if line_no != 1 else None
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
    else:
        print(f"{red}{chars['straight']} {chars['dash']*(terminal_width-4)} {chars['straight']}{reset}")
    
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
        if hex_code: return [out.replace(f"\'helix doc {_hex_code.group(1)}.{_hex_code.group(2)}\'", f"{yellow}\'helix doc {_hex_code.group(1)}.{_hex_code.group(2)}\'{reset}") for out in output]
        return output
    print("\n".join(process_message(message)))

    
    len_of_file: int = len(file + ':' + str(line_no))
    len_of_halfs = int(((terminal_width-4)/2 - len_of_file/2))
    
    if (len_of_halfs) < 2:
        import os
        file = '.' + os.sep + os.path.relpath(file)
        len_of_file: int = len(file + ':' + str(line_no))
        len_of_halfs = int(((terminal_width-4)/2 - len_of_file/2))
    
    # check if terminal width is even
    print(f"{red}{chars['b-left']}{chars['dash']*len_of_halfs} {green}{file}{gray}:{green}{line_no}{red} {' ' if terminal_width % 2 != 0 else ''}{chars['dash']*len_of_halfs}{chars['b-right']}{reset}")
    exit(1)