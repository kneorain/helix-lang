from src.token.tokenize_line import tokenize_line
from src.token.remove_comments import remove_comments
from src.token.normalize_tokens import normalize_tokens
from src.global_vars import CACHE

def tokenize_file(path: str) -> list[list[str]]:
    """
    Tokenize a file.

    Args:
        path (str): The path to the file to tokenize

    Returns:
        list[list[str]]: The normalized and tokenized file
    """
    
    lines:           list[str] = []
    tokenized_lines: list[str] = []

    if path in CACHE:
        return CACHE[path]

    with open(path) as file:
        lines = file.readlines()

    [
        tokenized_lines.extend(tokenize_line(line))
        for line in remove_comments("|line_sep<:>line_sep|".join(lines)).split(
            "|line_sep<:>line_sep|"
        )
    ]

    CACHE[path] = [
        token.split("|nested_line_sep<:>nested_line_sep|")
        for token in normalize_tokens(
            "|line_sep<:>line_sep|".join(tokenized_lines)
        ).split("|line_sep<:>line_sep|")
    ]

    return CACHE[path]
