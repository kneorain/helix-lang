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

class Namespace:
    def __init__(self, name: str, namespace_type: str, lines: list):
        self.name = name
        self.namespace_type = namespace_type
        self.lines = lines
        self.children = []  # Nested namespaces

    def __str__(self, indent_level=0) -> str:
        indent = '    ' * indent_level
        representation = f"{indent}Namespace: {self.name} (Type: {self.namespace_type})\n"
        
        for line in self.lines:
            # Assuming the line is a list of strings, we join them with a space
            # and replace spaces with an empty string
            cleaned_line = ' '.join(line)
            representation += f"{indent}    {repr(cleaned_line)}\n"

        for child in self.children:
            representation += child.__str__(indent_level + 1)

        return representation

def process(lines: list[list[str]]) -> Namespace:
    """
    Process a list of lines and return a Namespace object.

    Args:
        lines (list[list[str]]): The lines to process

    Returns:
        Namespace: The Namespace object
    """

    def parse_namespace(lines, start_index=0, start_indent_level=0):
        children = []
        namespace_name = None
        namespace_type = None
        current_lines = []
        lines_to_remove = []

        index = start_index
        while index < len(lines):
            line = lines[index]
            current_indent_level = int(line[0].split("<\\t:")[1][:-1])

            if current_indent_level < start_indent_level:
                break

            if current_indent_level == start_indent_level and namespace_name is not None and line[1] in BODY_REQUIRED_KEYWORDS and line[1] not in ("else", "elif", "except", "finally", "catch", "if", "try", "unless"):
                nested_ns, nested_lines_to_remove = parse_namespace(current_lines, 0, start_indent_level + 1)
                ns = Namespace(namespace_name, namespace_type, current_lines)
                ns.children.extend(nested_ns)
                children.append(ns)
                lines_to_remove.extend(nested_lines_to_remove)
                current_lines = []

                namespace_name = line[2]
                namespace_type = BODY_REQUIRED_KEYWORDS[line[1]]
            elif namespace_name is None and line[1] in BODY_REQUIRED_KEYWORDS and line[1] not in ("else", "elif", "except", "finally", "catch", "if", "try", "unless"):
                namespace_name = line[2]
                namespace_type = BODY_REQUIRED_KEYWORDS[line[1]]
            elif namespace_name is not None:
                current_lines.append(line)
                lines_to_remove.append(line)

            index += 1

        if namespace_name is not None:
            nested_ns, nested_lines_to_remove = parse_namespace(current_lines, 0, start_indent_level + 1)
            ns = Namespace(namespace_name, namespace_type, current_lines)
            ns.children.extend(nested_ns)
            children.append(ns)
            lines_to_remove.extend(nested_lines_to_remove)

        return children, lines_to_remove

    root_namespace = Namespace("root", "root", [])
    children, lines_to_remove = parse_namespace(lines, 0, 0)
    root_namespace.children = children

    # Removing processed lines
    remaining_lines = [line for line in lines if line not in lines_to_remove]
    root_namespace.lines = remaining_lines

    return root_namespace



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