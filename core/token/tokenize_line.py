from functools import cache

import re ##### Keep
from classes.Token import Token

import globals

@cache
def tokenize_line(code: Token | str) -> list[str]:
    """
    Tokenize a line of code.
    
    Args:
        code (str): The code to tokenize
    
    Returns:
        list[str]: The tokenized code
    """
    if isinstance(code, str):
        code = Token(None, code, 0, 0)
    
    back_slash = "\\"
    
    pattern: str = rf"""
        ([fbur]*"[^"\\]*(?:\\.[^"\\]*)*")                                                          | # Double quotes strings, including f, b, r, u strings
        ([fbur]*'[^'\\]*(?:\\.[^'\\]*)*')                                                          | # Single quotes strings, including f, b, r, u strings
        ({back_slash.join(globals.COMMENT.split())}[^\n]*)                                                      | # Single line comments (~~)
        ({back_slash.join(globals.BLOCK_COMMENT.split())}[\s\S]*?{back_slash.join(globals.BLOCK_COMMENT.split())})      | # Multi line comments (~*~ ... ~*~)
        (\b\d+\.\d+\b)                                                                      | # Decimal numbers
        (\b\w+\b)                                                                           | # Words (identifiers, keywords)
        ({'|'.join(globals.DOUBLE_CHARACTER)})                                                      | # Double character operators
        ([\(\){{}};,])                                                                      | # Single character delimiters
        (\S)                                                                                | # Catch other characters
    """
    
    tokens: list[list[str]] = re.findall(pattern, code.line, re.MULTILINE | re.VERBOSE)
    flattened_tokens = [
        token
        for group in tokens
        for token in group
        if token and not token.startswith(globals.COMMENT) and not token.startswith(globals.BLOCK_COMMENT) and not token.endswith(globals.BLOCK_COMMENT)
    ]
    
    code.line = [globals.EARLY_REPLACEMENTS[token] if token in globals.EARLY_REPLACEMENTS else token for token in flattened_tokens] if flattened_tokens else []
