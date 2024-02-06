import re
from functools import cache
from src.globals import DOUBLE_CHARACTER, COMMENT, BLOCK_COMMENT

@cache
def tokenize_line(code) -> list[str]:
    """
    Tokenize a line of code.
    
    Args:
        code (str): The code to tokenize
    
    Returns:
        list[str]: The tokenized code
    """
    
    pattern: str = rf"""
        ("[^"\\]*(?:\\.[^"\\]*)*")                                                          | # Double quotes strings
        ('[^'\\]*(?:\\.[^'\\]*)*')                                                          | # Single quotes strings
        ({'\\'.join(COMMENT.split())}[^\n]*)                                                | # Single line comments (~~)
        ({'\\'.join(BLOCK_COMMENT.split())}[\s\S]*?{'\\'.join(BLOCK_COMMENT.split())})      | # Multi line comments (~*~ ... ~*~)
        (\b\w+\b)                                                                           | # Words (identifiers, keywords)
        ({'|'.join(DOUBLE_CHARACTER)})                                                      | # Double character operators
        ([\(\){{}};,])                                                                      | # Single character delimiters
        (\S)                                                                                  # Catch other characters
    """
    
    tokens: list[list[str]] = re.findall(pattern, code.line, re.MULTILINE | re.VERBOSE)
    flattened_tokens = [
        token
        for group in tokens
        for token in group
        if token and not token.startswith(COMMENT) and not token.startswith(BLOCK_COMMENT) and not token.endswith(BLOCK_COMMENT)
    ]

    code.line = flattened_tokens
