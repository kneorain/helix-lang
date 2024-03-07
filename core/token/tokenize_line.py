import re  # #### Keep
from functools import cache
from core.panic import panic

import globals
from classes.Token import Token

COMPILED_RE: re.Pattern = None

def compiled_re(ignore_strings: bool = False) -> re.Pattern:
    global COMPILED_RE
    back_slash = "\\"
    if not COMPILED_RE and not ignore_strings:
        COMPILED_RE = re.compile(rf"""
            ([fbur]*"[^"\\]*(?:\\.[^"\\]*)*")                                                                          | # Double quotes strings, including f, b, r, u strings
            ([fbur]*'[^'\\]*(?:\\.[^'\\]*)*')                                                                          | # Single quotes strings, including f, b, r, u strings
            ({back_slash.join(globals.COMMENT.split())}[^\n]*)                                                         | # Single line comments (~~)
            ({back_slash.join(globals.BLOCK_COMMENT.split())}[\s\S]*?{back_slash.join(globals.BLOCK_COMMENT.split())}) | # Multi line comments (~*~ ... ~*~)
            (\b\d+\.\d+\b)                                                                                             | # Decimal numbers
            (\b\w+\b)                                                                                                  | # Words (identifiers, keywords)
            ({'|'.join(globals.FAT_CHARACTER)})                                                                        | # Double character operators
            ([\(\){{}};,])                                                                                             | # Single character delimiters
            (\S)                                                                                                       | # Catch other characters
        """, re.MULTILINE | re.VERBOSE)
    if ignore_strings:
        return re.compile(rf"""
            ({back_slash.join(globals.COMMENT.split())}[^\n]*)                                                         | # Single line comments (~~)
            ({back_slash.join(globals.BLOCK_COMMENT.split())}[\s\S]*?{back_slash.join(globals.BLOCK_COMMENT.split())}) | # Multi line comments (~*~ ... ~*~)
            (\b\d+\.\d+\b)                                                                                             | # Decimal numbers
            (\b\w+\b)                                                                                                  | # Words (identifiers, keywords)
            ({'|'.join(globals.FAT_CHARACTER)})                                                                        | # Double character operators
            ([\(\){{}};,])                                                                                             | # Single character delimiters
            (\S)                                                                                                       | # Catch other characters
        """, re.MULTILINE | re.VERBOSE)
    else: return COMPILED_RE

@cache
def tokenize_line(code: Token | str, path: str = None, ignore_errors: bool = False, ignore_strings: bool = False) -> list[str]:
    """
    Tokenize a line of code.
    
    Args:
        code (str): The code to tokenize
    
    Returns:
        list[str]: The tokenized code
    """
    if isinstance(code, str):
        code = Token(None, code, 0, 0)
    
    tokens: list[list[str]] = [
        [
            token
            for token in match
            if token
        ]
        for match in compiled_re(ignore_strings).findall(code.token)
    ]
    flattened_tokens = [
        token
        for group in tokens
        for token in group
        if token and not token.startswith(globals.COMMENT) and not token.startswith(globals.BLOCK_COMMENT) and not token.endswith(globals.BLOCK_COMMENT)
    ]
    [
        panic(
            SyntaxError(f"Reserved keyword '{token}' used."),
            token,
            file=path,
            line_no=code.line_number
        )
        for token in flattened_tokens
        if token.strip() in globals.RESERVED_KEYWORDS and not ignore_errors
    ]
    
    code.line = [
        globals.EARLY_REPLACEMENTS[token]
        if (
            token in globals.EARLY_REPLACEMENTS
        ) else (
            token
        ) for token in flattened_tokens
    ] if flattened_tokens else []
    
    if ignore_errors:
        return code.line

def standalone_tokenize_line(line: str | Token) -> list[str]:
    import re
    if isinstance(line, Token):
        line = line.token
    
    back_slash = "\\"
    pattern = re.compile(rf"""
        ({back_slash.join(globals.COMMENT.split())}[^\n]*)                                                         | # Single line comments (~~)
        ({back_slash.join(globals.BLOCK_COMMENT.split())}[\s\S]*?{back_slash.join(globals.BLOCK_COMMENT.split())}) | # Multi line comments (~*~ ... ~*~)
        (\b\d+\.\d+\b)                                                                                             | # Decimal numbers
        (\b\w+\b)                                                                                                  | # Words (identifiers, keywords)
        ({'|'.join(globals.FAT_CHARACTER)})                                                                        | # Double character operators
        ([\(\){{}};,])                                                                                             | # Single character delimiters
        (\S)                                                                                                       | # Catch other characters
    """, re.MULTILINE | re.VERBOSE)
    
    tokens: list[list[str]] = [
        [
            token
            for token in match
            if token
        ]
        for match in pattern.findall(line)
    ]
    
    return [
        token
        for group in tokens
        for token in group
        if token and not token.startswith(globals.COMMENT) and not token.startswith(globals.BLOCK_COMMENT) and not token.endswith(globals.BLOCK_COMMENT)
    ]