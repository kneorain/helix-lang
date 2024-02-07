from functools import cache
import ast
from classes.Token import Token
from globals import COMMENT, BLOCK_COMMENT, INLINE_COMMENT
import re2 as re

in_block_comment: bool = False

def remove_comment(_code: Token):
    """
    Removes comments from the code. This is a smaller part of the tokenizer,
    but it is in its own file because it is a very important part of the tokenizer.

    Args:
        code (list[str]): The code to remove comments from

    Raises:
        Exception: If there is an unclosed block comment

    Returns:
        list[str]: The code with comments removed
    """
    global in_block_comment

    code: str = _code.original_line
    code = re.sub(INLINE_COMMENT, "", re.sub(COMMENT, "", code))
    
    if re.search(BLOCK_COMMENT, code):
        in_block_comment = ~in_block_comment # type: ignore
        code = ""
        
    if in_block_comment:
        code = ""

    _code.line = code
