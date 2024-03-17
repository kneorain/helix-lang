import ast
from functools import cache

from src.config import CONFIG

re = __import__(CONFIG.Transpiler.regex_module)
from src.classes.Token import Token
import src.core.base as base

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
    code = re.sub(base.INLINE_COMMENT, "", re.sub(base.COMMENT, "", code))
    
    code = re.sub(r"override\s+.*\:", "", code)
    code = re.sub(r"impl\s+.*:", "", code)
    
    if re.search(base.BLOCK_COMMENT, code):
        in_block_comment = ~in_block_comment # type: ignore
        code = ""
        
    if in_block_comment:
        code = ""

    _code.line = code
