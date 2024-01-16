from functools import cache
from src.global_vars import BODY_REQUIRED_KEYWORDS

@cache
def normalize_tokens(_lines: str) -> str:
    """
    This function normalizes the tokens. This is a smaller part of the tokenizer,
    but it is in its own file because it is a very important part of the tokenizer.
    Some of the things this function does is:
        - Reads the indent level of each line
        - Normalizes the indent level of each line
        - Normalizes the formatting of the code (e.g. `if (a) {` -> `if (a):`)

    Args:
        lines (str): The code to normalize
                     - LINES MUST BE SEPARATED BY `|line_sep<:>line_sep|`
                     This is because this allows for the function to be cached

    Returns:
        str: The normalized code separated by `|line_sep<:>line_sep|`, and
             `|nested_line_sep<:>nested_line_sep|`
    """

    lines:        list[str]       = _lines.split("|line_sep<:>line_sep|")
    stack:        list[str]       = []
    current_line: list[str]       = []
    final_lines:  list[list[str]] = []
    firs_inst:    bool            = True
    in_for_loop:  bool            = False
    indent_level: int             = 0

    for index, token in enumerate(lines):
        if token in BODY_REQUIRED_KEYWORDS.keys():
            stack.append(token)
            indent_level += 1
            firs_inst = True
        elif token == "{":
            if not firs_inst:
                indent_level += 1
            if len(stack) == indent_level:
                lines[index] = ":"
                lines.insert(index + 1, "<\\n>")
                firs_inst = False
            if lines[index + 2] == "}":
                lines[index + 2] = "}"
                lines.insert(index + 3, "<\\r>")
        elif token == "}":
            if len(stack) == indent_level:
                lines[index] = "<\\n>"
                indent_level -= 1
                stack.pop()
            else:
                indent_level -= 1
        if token == "<\\r>":
            lines[index - 5] = "<\\r1>"
        if token == ";":
            lines[index] = "<\\n>"
        if lines[index] == "<\\n>":
            lines.insert(index + 1, f"<\\t:{indent_level}>")
        if token == "..." and not lines[index + 1] == "<\\n>":
            lines.insert(index + 1, "<\\n>")
        if token == "<\\r>":
            for i in range(index, -1, -1):
                if lines[i] == "<\\r1>":
                    break
                else:
                    lines[i] = ""
        if token == ";":
            lines[index] = "<\\n>"

    for index, token in enumerate(lines):
        if token == "for":
            in_for_loop = True
        if in_for_loop:
            if token == "<\\n>":
                lines[index] = ";"
                if lines[index + 1].startswith("<\\t:"):
                    lines[index + 1] = ""
            elif token == ":":
                in_for_loop = False

    for token in [token for token in lines if token]:
        if token == "<\\n>":
            final_lines.append(current_line)
            current_line = []
        else:
            current_line.append(token)
    else:
        if current_line:
            final_lines.append(current_line)

    for index, i in enumerate(final_lines):
        if len(i) == 1 and i[0].startswith("<\\t:"):
            final_lines[index] = []

    final_lines = [line for line in final_lines if line]
    final_lines[0].insert(0, "<\\t:0>")

    return "|line_sep<:>line_sep|".join(
        ["|nested_line_sep<:>nested_line_sep|".join(line) for line in final_lines]
    )
