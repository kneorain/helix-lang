from functools import lru_cache
import re
from src.global_vars import COMMENT, BLOCK_COMMENT, LINE_BREAK, INLINE_COMMENT

@lru_cache
def remove_comments(_code: str) -> str:
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

    code:             list[str] = _code.split(LINE_BREAK) # type: ignore
    in_block_comment: bool      = False
    
    for index, line in enumerate(code):
        code[index] = re.sub(INLINE_COMMENT, "", re.sub(COMMENT, "", line))
        
        if re.search(BLOCK_COMMENT, line):
            in_block_comment = ~in_block_comment # type: ignore
            code[index] = ""
            continue

        if in_block_comment:
            code[index] = ""

    if in_block_comment:
        raise Exception("Unclosed block comment")

    return LINE_BREAK.join([line for line in code if line])
