from functools import cache
from src.global_vars import COMMENT, BLOCK_COMMENT

@cache
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

    code:             list[str] = _code.split("|line_sep<:>line_sep|") # type: ignore
    in_block_comment: bool      = False
    in_line_comment:  bool      = False

    for index, line in enumerate(code):
        if line.strip().startswith(BLOCK_COMMENT):
            in_block_comment = ~in_block_comment # type: ignore
            code[index] = ""
            continue

        if line.strip().startswith(COMMENT):
            in_line_comment = ~in_line_comment # type: ignore
            continue

        if in_block_comment or in_line_comment:
            code[index] = ""

    if in_block_comment:
        raise Exception("Unclosed block comment")

    return "|line_sep<:>line_sep|".join([line for line in code if line])
