if __name__ == '__main__':
    from namespace_abstraction import NamespaceAbstraction

from dataclasses import dataclass
from typing import override
from threading import Thread
from time import time
from src.global_vars import BODY_REQUIRED_KEYWORDS

class Namespace:
    line_number: int = 0
    start: int = 0
    end: int = 0
    namespace_type: str = ""
    namespace_name: str = ""
    lines: list[list[str or "Namespace"]] = [[]]
    
    def __init__(
        self,
        line_number: int = 0,
        start: int = 0,
        end: int = 0,
        namespace_type: str = "",
        namespace_name: str = "",
        lines: list[list[str or "Namespace"]] = [[]]
    ):
        line_number = line_number
        start = start
        end = end
        namespace_type = namespace_type
        namespace_name = namespace_name
        lines = lines
        
        
"""
lines...

read lines, if namepace then take note of indent level and create a namepace object with the lines that are indented

in the namespace object, read the lines and if there is a namespace then create a namespace object with the lines that are indented

repeat until there are no more namespaces
"""

def process(lines: list[list[str]]) -> Namespace:
    """
    Process a list of lines and return a Namespace object.

    Args:
        lines (list[list[str]]): The lines to process

    Returns:
        Namespace: The Namespace object
    """
    
    # ~~~~~~~~~~~~ Innit Variables ~~~~~~~~~~~~ #
    _current_indent_level: int = 0
    _start_indent_level: int = 0
    _in_namespace: bool = False
    _start: int = 0
    _end: int = 0
    _namespace_type: str = ""
    _namespace_name: str = ""
    _lines: list[list[str or "Namespace"]] = [[]]
    
    # ~~~~~~~~~~~~ Parse top level namespaces ~~~~~~~~~~~~ #
    for index, line in enumerate(lines):
        # ['<\\t:0>', 'include', '"add"', 'from', '"test.c"']
        # look at indent levels, recurse until change has been found or a base keyword is there,
        # if then mark index as start along with indent level, recurse until end of said level so
        # if start at 0 go thru anything over 0 until 0 is found then save index - 1 as end remove
        # from lost and store as namespace object, then parse the lines in there the same way.
        _current_indent_level = int(line[0].split("<\\t:")[1][:-1])
        
        if _in_namespace:
            if _current_indent_level == _start_indent_level:
                _in_namespace = False
                _end = index - 1
                continue
            else:
                _lines.append(line)

        if line[1] in BODY_REQUIRED_KEYWORDS.keys():
            _in_namespace = True
            _lines.append(line)
            _start = index
            _start_indent_level = _current_indent_level
            _namespace_type = BODY_REQUIRED_KEYWORDS[line[1]]
    

    

"""

start_indent: int = 0
start: int = 0
end: int = 0
in_namespace: bool = False
lines_in_namespace: list[list[str]] = [[]]
remove: list[str] = []

for index, line in enumerate(lines):
    if in_namespace:
        if int(line[0].split(":")[1].split(">")[0]) > start_indent:
            lines_in_namespace.append(line)
            continue
        else:
            in_namespace = False
            end = index - 1
            lines_in_namespace.pop(0)
            namespace = Namespace(start=start, end=end, lines=lines_in_namespace)
            lines[start:end] = [namespace] # type: ignore
            lines_in_namespace = [[]]
            continue
    if line[1] in BODY_REQUIRED_KEYWORDS:
        start = index
        in_namespace = True
        start_indent = int(line[0].split(":")[1].split(">")[0])
        lines_in_namespace = [[]]
        lines_in_namespace.append(line)
        continue


"""