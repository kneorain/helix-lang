import multiprocessing, threading
from src.token.normalize_tokens import normalize_tokens
from src.token.remove_comments import remove_comment
from src.token.tokenize_line import tokenize_line
from src.classes.cache_store import cache
from src.classes.ast import AST, AST_LIST
from src.globals import CACHE

def something(ast: AST):
    remove_comment(ast)
    ast.line = tokenize_line(ast.line)

def tokenize_file(path: str) -> tuple[AST_LIST, ...]:
    """
    Tokenize a file.

    Args:
        path (str): The path to the file to tokenize

    Returns:
        list[list[str]]: The normalized and tokenized file
    """
    lines:           list[AST] = []
    
    if path in CACHE: return CACHE[path]

    lines = tuple(AST(line, "", index+1, 0) for index, line in enumerate(open(path, "r").readlines()))
    
    frozenset(map(something, lines))
        
     
    CACHE[path] = normalize_tokens(lines, path)
    return CACHE[path]