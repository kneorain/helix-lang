from functools import cache

import re ##### Keep

from globals import BLOCK_COMMENT, COMMENT, DOUBLE_CHARACTER, EARLY_REPLACEMENTS


@cache
def tokenize_line(code) -> list[str]:
    """
    Tokenize a line of code.
    
    Args:
        code (str): The code to tokenize
    
    Returns:
        list[str]: The tokenized code
    """
    
    back_slash = "\\"
    
    pattern: str = rf"""
        ("[^"\\]*(?:\\.[^"\\]*)*")                                                          | # Double quotes strings
        ('[^'\\]*(?:\\.[^'\\]*)*')                                                          | # Single quotes strings
        ({back_slash.join(COMMENT.split())}[^\n]*)                                                      | # Single line comments (~~)
        ({back_slash.join(BLOCK_COMMENT.split())}[\s\S]*?{back_slash.join(BLOCK_COMMENT.split())})      | # Multi line comments (~*~ ... ~*~)
        (\b\d+\.\d+\b)                                                                      | # Decimal numbers
        (\b\w+\b)                                                                           | # Words (identifiers, keywords)
        ({'|'.join(DOUBLE_CHARACTER)})                                                      | # Double character operators
        ([\(\){{}};,])                                                                      | # Single character delimiters
        (\S)                                                                                | # Catch other characters
    """
    
    tokens: list[list[str]] = re.findall(pattern, code.line, re.MULTILINE | re.VERBOSE)
    flattened_tokens = [
        token
        for group in tokens
        for token in group
        if token and not token.startswith(COMMENT) and not token.startswith(BLOCK_COMMENT) and not token.endswith(BLOCK_COMMENT)
    ]
    
    code.line = [EARLY_REPLACEMENTS[token] if token in EARLY_REPLACEMENTS else token for token in flattened_tokens] if flattened_tokens else []
