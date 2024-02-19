import ast
from functools import cache

from core.config import load_config

re = __import__(load_config().Transpiler["regex_module"])
from classes.Token import Token
from globals import BLOCK_COMMENT, COMMENT, INLINE_COMMENT

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
    
    code = re.sub(r"override\s+.*\:", "", code)
    code = re.sub(r"impl\s+.*:", "", code)
    
    if re.search(BLOCK_COMMENT, code):
        in_block_comment = ~in_block_comment # type: ignore
        code = ""
        
    if in_block_comment:
        code = ""

    _code.line = code
