import src.core.base as base
from src.core.imports import (
    Processed_Line,
    Token_List,
    Token,
    map,
    Scope,
    panic,
    _class,
    INDENT_CHAR,
    Optional
)

replace_function_name: map[str, str] = map({
    "=="  : "__eq__",
    "//"  : "__floordiv__",
    ">="  : "__ge__",
    "<="  : "__le__",
    "<<"  : "__lshift__",
    "!="  : "__ne__",
    "**"  : "__pow__",
    "//"  : "__rfloordiv__",
    ">>"  : "__rshift__",
    "**"  : "__rpow__",
    "%"   : "__rmod__",
    "%"   : "__mod__",
    "*"   : "__rmul__",
    "&"   : "__and__",
    "*"   : "__mul__",
    "+"   : "__radd__",
    "+"   : "__add__",
    "-"   : "__neg__",
    "|"   : "__ror__",
    "~"   : "__invert__",
    "+"   : "__pos__",
    ">"   : "__gt__",
    "&"   : "__rand__",
    "<"   : "__lt__",
    "-"   : "__rsub__",
    "/"   : "__rtruediv__",
    "|"   : "__or__",
    "^"   : "__rxor__",
    "-"   : "__sub__",
    "/"   : "__truediv__",
    "^"   : "__xor__",
    "@"   : "__matmul__",
})

def extract_variables(ast_line: Token_List, root_scope: Scope) -> dict[Optional[str], (
        Optional[list[str]] | Optional[str] | dict[str, dict[str, str]]
    )]:
    allowed_untyped = (
        "self",
        "cls",
        "super"
    )
    variables: dict[str, dict[str, str]] = {}
    line = ast_line.line[2:] # remove the fn keyword and the function name
    in_param = False
    in_generic: bool = False
    generic: str = ""
    generic_count: int = 0

    if line[0].token == "(" and line[1].token == ")":
        if line[2].token == "->":
            # no parameters, just a return type
            if line[3].token == ":" or line[3].token == "<\\r1>":
                panic(SyntaxError(f"<Hex(02.E3)>: Expected a return type after the {root_scope.get_keyword('FUNCTION')} keyword"), "->", file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword('FUNCTION')))
            return {"return_type": line[3].token, "params": {}}
        else:
            # no parameters, no return type
            if line[2].token != ":" and line[2].token != "<\\r1>":
                panic(SyntaxError(f"<Hex(02.E3)>: Expected a colon after the parameters"), ":", file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword('FUNCTION')))
            return {"return_type": None, "params": {}}
    elif line[0].token == "(":
        in_param = True
        line = line[1:]
    else:
        panic(SyntaxError(f"<Hex(02.E3)>: Expected an open parenthesis after the {root_scope.get_keyword('FUNCTION')} keyword"), "(", file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword('FUNCTION')))
    
    if in_param:
        while line:
            if line[0].token == ")":
                if line[1].token == "->":
                    # no parameters, just a return type
                    if line[2].token == ":" or line[2].token == "<\\r1>":
                        panic(SyntaxError(f"<Hex(02.E3)>: Expected a return type after the {root_scope.get_keyword('FUNCTION')} keyword"), "->", file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword('FUNCTION')))
                    return {"return_type": line[2].token, "params": variables}
                else:
                    # no parameters, no return type
                    if line[1].token != ":" and line[1].token != "<\\r1>":
                        panic(SyntaxError(f"<Hex(02.E3)>: Expected a colon after the parameters"), ":", file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword('FUNCTION')))
                    return {"return_type": None, "params": variables}
            if line[0].token == "<":
                generic_count += 1
                in_generic = True if generic_count > 0 else False
                if not in_generic:
                    in_generic = False
                    variables[tuple(variables.keys())[-1]] = {"type": variables[tuple(variables.keys())[-1]]["type"] + generic}
                    line = line[1:]
                    continue
                generic += "[" + " "
                line = line[1:]
            elif line[0].token == ">":
                generic_count -= 1
                in_generic = True if generic_count > 0 else False
                generic += " " + "]"
                if not in_generic:
                    in_generic = False
                    variables[tuple(variables.keys())[-1]] = {"type": variables[tuple(variables.keys())[-1]]["type"] + generic}
                    line = line[1:]
                    continue
                line = line[1:]
            elif in_generic:
                generic += line[0].token
                line = line[1:]
            elif line[0].token == ",":
                line = line[1:]
            else:
                if line[1].token == ":":
                    variables[line[0].token] = {"type": line[2].token}
                    line = line[3:]
                else:
                    if line[0].token == "=":
                        panic(SyntaxError(f"<Hex(02.E3)>: Default values are not allowed in function parameters"), line[0].token, file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword('FUNCTION')))
                    if line[0].token == "<":
                        in_generic = True
                        generic = ""
                        continue
                    if line[0].token in allowed_untyped:
                        variables[line[0].token] = {"type": "Any"}
                        line = line[1:]
                        continue
                    panic(SyntaxError(f"<Hex(02.E3)>: Expected a colon and a type after the variable name"), line[0].token, file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword('FUNCTION')))
                    
    return variables # type: ignore

class ExtractFuncParameters:
    allowed_untyped = ("self", "cls", "super")

    def __init__(self, ast_line: Token_List, root_scope: Scope):
        self.generic:       str     = ""
        self.in_param:      bool    = False
        self.generic_count: int     = 0
        self.in_generic:    bool    = False
        self.root_scope:    Scope   = root_scope
        self.ast_line:      Token_List      = ast_line
        self.return_type:   Optional[str]   = None
        self.line:          list[Token]     = ast_line.line[2:]
        self.variables:     dict[str, dict[str, str]]           = {}
        self.params:        Optional[dict[str, dict[str, str]]] = None

    def parse(self) -> dict[Optional[str], Optional[list[str]] | Optional[str] | dict[str, dict[str, str]]]:
        ...
    
    def handle_no_parameters(self) -> dict[Optional[str], dict[str, dict[str, str]]]:
        ...
    
    def handle_closing_parenthesis(self) -> dict[Optional[str], dict[str, dict[str, str]]]:
        ...
    def process_parameter(self, in_generic: bool):
        ...



def process_modifiers(ast_list: Token_List, root_scope: Scope) -> list[str]:
    allowed_modifiers = (
        root_scope.get_keyword('ASYNC'),
        root_scope.get_keyword('PRIVATE'),
        root_scope.get_keyword("PROTECTED"),
        root_scope.get_keyword("FINAL"),
        root_scope.get_keyword('UNSAFE'),
        root_scope.get_keyword('STATIC') # TODO: add virtual
    )

    modifiers = []
    index = 0
    
    if ast_list.line[0].token != root_scope.get_keyword('FUNCTION'):
        line = ast_list.line.copy()
        while line:
            index += 1
            if line[0].token in allowed_modifiers:
                modifiers.append(line[0].token)
                line = line[1:]
            else:
                if line[0].token != root_scope.get_keyword('FUNCTION'):
                    return modifiers
                else:
                    break
        ast_list.line = ast_list.line[index-1:]
        return modifiers
    else:
        return modifiers


def contains(line: Token_List, compare: tuple):
    # check if any of the tokens in compare are in line and
    return any([_ in line for _ in compare])

# static async fn factorial(n: int) -> int {
def _function(ast_list: Token_List, current_scope: Scope, parent_scope: Scope, root_scope: Scope) -> Processed_Line:
    decorators = []
    if ast_list.line[0].token == "#":
        for _ in range(ast_list.count("#")):
            decorator = ast_list.get_between("[", "]")
            ast_list.line = ast_list.line[len(decorator)+3:]
            decorators.append('@' + ' '.join([__.token for __ in decorator]))
            
    modifiers = process_modifiers(ast_list, root_scope)
        
    not_allowed_classes = (
        parent_scope.get_keyword("CLASS"),
        parent_scope.get_keyword("INTERFACE"),
        parent_scope.get_keyword("STRUCT"),
        parent_scope.get_keyword("UNION"),
        parent_scope.get_keyword("ENUM"),
        parent_scope.get_keyword("ABSTRACT"),
        parent_scope.get_keyword("UNSAFE"),
    )
    
    if ast_list.line[0].token != root_scope.get_keyword('FUNCTION'):
        if ast_list.splice(len(modifiers))[0] in not_allowed_classes:
            return _class(ast_list.splice(len(modifiers)), current_scope, parent_scope, root_scope, modifiers)
    
        panic(SyntaxError(f"<Hex(02.E3)>: Expected the {root_scope.get_keyword('FUNCTION')} keyword"), ast_list[1].token, file=ast_list.file, line_no=ast_list[0].line_number)
    
    variables = extract_variables(ast_list, root_scope)
    name = ast_list.line[1].token
    
    if name in replace_function_name:
        if not any([i in not_allowed_classes for i in parent_scope.name]):
            panic(SyntaxError(f"<Hex(02.E3)>: Cannot overload a unary operator outside a class"), name, file=ast_list.file, line_no=ast_list.find_line_number(name))
        name = replace_function_name[name]
    
    output = f"def {name}(" if name not in parent_scope.functions else f"def _("
    
    if not variables["params"]:
        output += ")"
    else:
        if not isinstance(variables["params"], dict):
            raise ValueError("The variable type is not a dictionary")
        
        for k, v in variables["params"].items():
            if v["type"] == "void":
                panic(SyntaxError(f"<Hex(02.E3)>: The type void is not allowed for variables"), file=ast_list.file, line_no=ast_list.find_line_number(k))
            output += f"{k}: {base.replace_primitive(v['type'], 0)}, "
            current_scope.variables[k] = v["type"]
        
        output = output[:-2] + ")"
    
    if ast_list.line[-1].token == "<\\r1>" and ast_list.indent_level == 0:
        panic(SyntaxError(f"<Hex(02.E3)>: Cannot have a blank function in the global scope"), file=ast_list.file, line_no=ast_list.find_line_number(name))
    
    if variables["return_type"]:
        output += f" -> {variables['return_type']}:" if ast_list.line[-1].token != "<\\r1>" else f" -> {variables['return_type']}\n{INDENT_CHAR*(ast_list.indent_level+1)}pass"
    else:
        output += ":" if ast_list.line[-1].token != "<\\r1>" else f":\n{INDENT_CHAR*(ast_list.indent_level+1)}pass"
    
    output = f"\n{INDENT_CHAR*ast_list.indent_level}{output}"
    
    #if not any([i in not_allowed_classes for i in parent_scope.name]):
    #    if not root_scope.get_keyword('ASYNC') in modifiers and not root_scope.get_keyword('UNSAFE') in modifiers:
    #        if name in parent_scope.functions:
    #            output = (f"\n{INDENT_CHAR*ast_list.indent_level}@{name}.register" + output)
    #        else:
    #            output = (f"\n{INDENT_CHAR*ast_list.indent_level}@hx__multi_method" + output)
    # if the type of parent_sope is an abstract class
    
    if any([i == root_scope.get_keyword("ABSTRACT") for i in parent_scope.name]):
        output = f"\n{INDENT_CHAR*ast_list.indent_level}@hx__abstract_method" + output
    # if the type of parent_sope is an interface
    if any([i == root_scope.get_keyword("INTERFACE") for i in parent_scope.name]):
        output = f"\n{INDENT_CHAR*ast_list.indent_level}@hx__abstract_method" + output

    static:  bool = False
    async_:  bool = False
    private: bool = False
    unsafe:  bool = False
    
    if root_scope.get_keyword('STATIC') in modifiers:
        if not any([i in not_allowed_classes for i in parent_scope.name]):
            panic(SyntaxError(f"<Hex(02.E3)>: The {root_scope.get_keyword('STATIC')} modifier cannot be used outside a class"), root_scope.get_keyword("STATIC"), file=ast_list.file, line_no=ast_list[0].line_number)
        
        output = f"\n{INDENT_CHAR*ast_list.indent_level}@staticmethod{output}"
        static = True
    
    if root_scope.get_keyword('ASYNC') in modifiers:
        output = f"\n{INDENT_CHAR*ast_list.indent_level}@hx__async{output}"
        async_ = True

    if root_scope.get_keyword('PRIVATE') in modifiers:
        private = True

    # if root_scope.get_keyword("PROTECTED") in modifiers:
    #     output = output.replace("def ", "def _")
        
    if root_scope.get_keyword("FINAL") in modifiers:
        output = f"{INDENT_CHAR*ast_list.indent_level}@final{output}"
        
    if root_scope.get_keyword('UNSAFE') in modifiers:
        unsafe = True

    if private and static:
        panic(SyntaxError(f"<Hex(02.E3)>: The {root_scope.get_keyword('PRIVATE')} and {root_scope.get_keyword('STATIC')} modifiers cannot be used together"), file=ast_list.file, line_no=ast_list.find_line_number(root_scope.get_keyword('STATIC')))
        
    if async_ and unsafe:
        panic(SyntaxError(f"<Hex(02.E3)>: The {root_scope.get_keyword('ASYNC')} and {root_scope.get_keyword('UNSAFE')} modifiers cannot be used together"), file=ast_list.file, line_no=ast_list.find_line_number(root_scope.get_keyword('STATIC')))
        
    parent_scope.functions[name] = {"type": variables["return_type"], "params": variables["params"], root_scope.get_keyword('STATIC'): static, root_scope.get_keyword('ASYNC'): async_, root_scope.get_keyword('PRIVATE'): private, root_scope.get_keyword('UNSAFE'): unsafe}
        
    if "unknown" in output:
        output = output.replace("unknown", "Any")
    
    #print(output)
    if decorators:
        for _, decorator in enumerate(reversed(decorators)):
            output = f"{INDENT_CHAR*ast_list.indent_level}{decorator}\n{INDENT_CHAR*ast_list.indent_level}{output.strip()}"

    return Processed_Line((f'\n{INDENT_CHAR*ast_list.indent_level}@overload_with_type_check\n' if not async_ else '\n') + output, ast_list)