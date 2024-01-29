if __name__ == '__main__':
    from classes.ast import AST

from dataclasses import dataclass
from typing import override
from threading import Thread
from time import time
from src.global_vars import BODY_REQUIRED_KEYWORDS

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

    pass