import functools
from src.core.core import (
    Processed_Line,
    Token_List,
    INDENT_CHAR,
    re,
    Optional,
    Iterable,
    PRIMITIVES_MAP,
    file_cache,
    KEYWORDS,
    Thread,
    
)

def multi_split(
    string: str,
    *separators: str,
    discard: Optional[Iterable[str]] = None,
) -> list[str]:
    # split the string by all the separators but keep the separators
    # so like "a + b" would become ["a", "+", "b"], if the separators are [" ", "+"]
    # Escape special regex characters in separators and join them with '|' for regex 'or'
    if not discard:
        discard = []

    regex_pattern = "|".join(
        re.escape(sep) for sep in separators
    )

    # Use re.split with a capturing group to keep separators
    return [
        s
        for s in re.split(f"({regex_pattern})", string)
        if s and s not in discard
    ]


def replace_primitive(
    type: str, operation: int = 0
) -> (
    str
):  # 0: helix ir type | python type, 1: python type, 2: helix ir type
    full_type: list[str] = multi_split(
        type, " ", "[", "]", ",", discard=["", " "]
    )

    # for each type in full_type, replace it with the python type | helix ir type
    if isinstance(full_type, str):
        return (
            PRIMITIVES_MAP[full_type][1]
            if operation == 2
            else (
                PRIMITIVES_MAP[full_type][0]
                if operation == 0
                else f"{PRIMITIVES_MAP[full_type][0]} | {PRIMITIVES_MAP[full_type][1]}"
            )
        )

    for i, t in enumerate(full_type):
        if t in PRIMITIVES_MAP:
            match operation:
                case 0:
                    if (
                        len(full_type) - i
                    ) > 1 and full_type[i + 1] == "[":
                        # get everything after the current type and keep track of the brackets, then process that again
                        # and then set a copy of the full_type to the processed type
                        # so like if the type is "list[int]" then it would become "list[hx_int|int] | hx_list[hx_int|int]"
                        # Process the nested type
                        end_index = i + 2
                        brackets = 1
                        while (
                            end_index < len(full_type)
                            and brackets
                        ):
                            if full_type[end_index] == "[":
                                brackets += 1
                            elif (
                                full_type[end_index] == "]"
                            ):
                                brackets -= 1
                            end_index += 1

                        nested_type = replace_primitive(
                            " ".join(
                                full_type[
                                    i + 2 : end_index - 1
                                ]
                            ),
                            operation,
                        )
                        python_type = f"{PRIMITIVES_MAP[t][0]}[{nested_type}]"
                        helix_type = f"{PRIMITIVES_MAP[t][1]}[{nested_type}]"
                        full_type[i:end_index] = [
                            f"{python_type} | {helix_type}"
                        ]
                    else:
                        full_type[i] = (
                            f"{PRIMITIVES_MAP[t][0]} | {PRIMITIVES_MAP[t][1]}"
                        )
                case 1:
                    full_type[i] = PRIMITIVES_MAP[t][0]
                case 2:
                    full_type[i] = PRIMITIVES_MAP[t][0]
                case 3:
                    # only the base type no generics
                    return PRIMITIVES_MAP[t][0]
                case _:
                    raise ValueError("Invalid operation")
        elif operation == 3:
            return full_type[0]

    return " ".join(full_type)

@file_cache
def find_keyword(internal_name: str) -> str:
    return [
        keyword
        for keyword in KEYWORDS.keys()
        if KEYWORDS[keyword]["internal_name"]
        == internal_name
    ][0]


def ASYNC(func):
    def run_thread(func, args, kwargs):
        func._result = func(*args, **kwargs)
        func._thread_started = False

    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        if not hasattr(func, "_thread_started") or not func._thread_started:
            func._thread = Thread(target=run_thread, args=(func, args, kwargs))
            func._thread_started = True
            func._thread.start()
        return func

    def join(timeout=None):
        if hasattr(func, "_thread"):
            func._thread.join(timeout)
            return getattr(func, "_result", None)
        return None

    setattr(func, "join", join)
    setattr(wrapper, "join", join)
    return wrapper
