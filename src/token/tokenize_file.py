from src.token.tokenize_line import tokenize_line
from src.token.remove_comments import remove_comment
from src.token.normalize_tokens import normalize_tokens
from src.global_vars import CACHE, LINE_BREAK, SUB_LINE_BREAK
import re
from difflib import SequenceMatcher
def APPROXIMATE_LINE(LINE_1: str, LINE_2: str) -> int:
    """
    \n Compares two strings and returns the similarity percentage.
    \n Input: compare - The string to compare.
    \n        compare_to - The string to compare to.
    \n Output: The similarity percentage. (0.0 - 1.0)
    """

    return SequenceMatcher(None, LINE_1, LINE_2).ratio()

def find_line_number(line: str, file: str) -> int:
    """
    \n Finds the line number of a line in a file.
    \n Input: line - The line to find.
    \n        file - The file to find the line in.
    \n Output: The line number of the line.
    """

    lines = open(file, "r").readlines()
    similar_lines = []
    similarity: float = 0.0
    for i in range(len(lines)):
        similarity = APPROXIMATE_LINE(line, lines[i])
        if similarity >= 0.7:
            similar_lines.append({"line": lines[i], "similarity": similarity})
    if similar_lines:
        similar_lines.sort(key=lambda x: x["similarity"], reverse=True)
        return similar_lines[0]["line"]
    else:
        return -1


from src.classes.ast import AST, AST_LIST

def tokenize_file(path: str) -> list[list[str]]:
    """
    Tokenize a file.

    Args:
        path (str): The path to the file to tokenize

    Returns:
        list[list[str]]: The normalized and tokenized file
    """
    
    lines:           list[AST] = []
    tokenized_lines: list[AST_LIST] = []

    if path in CACHE:
        return CACHE[path]

    with open(path) as file:
        lines = tuple(AST(line, "", index+1, 0) for index, line in enumerate(file.readlines()))

    
    for index, ast in enumerate(lines):
        temp_arr = []
        remove_comment(ast)
        ast.line = tokenize_line(ast.line)
        
    tokenized_lines = normalize_tokens(lines, path)
    
    for AST_line in tokenized_lines:
        for token in AST_line:
            print(token)
    
    print(*tokenized_lines, sep='\n')
    exit()
    

    CACHE[path];

    return CACHE[path]
