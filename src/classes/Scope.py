import src.core.core as core
from src.core.imports import (
    Optional,
    Token_List,
    Token,
    cache,
    Any,
)

class Scope:
    name: str | Token_List
    namespace_header: Optional[Token_List]
    namespace_type: str
    separate_file_namespace: bool
    children: list[Token_List]
    indent_level:int
    
    variables: dict[str, str]
    functions: dict[str, dict[str, Any]]
    classes:   dict[str, dict[str, Any]]
    operator_functions: dict[str, dict[str, Any]]
    transpiler_instance: Any
        
    def __init__(self, name: Token_List | str, namespace_type: str, children: list, indent_level: int = 0):
        self .name = name
        self .namespace_header = None
        self .namespace_type = namespace_type
        self .separate_file_namespace = False
        self .children = [] if not children else children
        Scope.internal_name = "Variable Assignment Namespace"
        self .indent_level = indent_level
        
        self.variables = {}
        self.functions = {}
        self.classes = {}
        self.operator_functions = {}
        
        self.transpiler_instance = None
        

    def make_readable(self, indent: str = "") -> str:
        output = f"\n{indent}Scope: {self.name} (Type: {self.namespace_type}) (Indent: {self.indent_level})\n"
        for child in self.children:
            if isinstance(child, Scope):
                output += child.make_readable(indent + "    ")
            else:
                output += f"{indent}    {child}\n"
                
        return output
    
    def __str__(self) -> str:
        print(f"\n{'    '*self.indent_level}Scope: {self.name} (Type: {self.namespace_type}) (Indent: {self.indent_level})")
        
        for child in self.children:
            if isinstance(child, Scope):
                print(child.make_readable('    '*(self.indent_level+1)))
            else:
                print('   ', child, end="\n")
                
        return ""
    
    def __repr__(self) -> str:
        return f"Scope({self.name})"
    
    def __getitem__(self, index: int):
        return self.children[index]
    
    def append_line(self, line: Token_List) -> None:
        self.children.append(line)
        
    def append_child(self, line: Token_List) -> None:
        self.children.append(line)
    
    # Token_List contains:
    #   ast_list.indent_level: int
    #   ast_list.line: list[Token]
    #   ast_list.file: str
    #
    # Token contains:
    #   original_line: str     # The original line from source code
    #   token: str             # A single token from the associated line
    #   line_number: int       # The line number from the source code
    #   indent_level: int      # The indent level of the line
    
    @classmethod
    def get_token(cls, ast: Token | str) -> str:
        if not isinstance(ast, str) and isinstance(ast.token, str):
            return str(ast.token)
        else:
            raise TypeError(f"Expected Token, got {type(ast)}")
    
    @classmethod
    def contains(cls, line: Token_List | tuple[str, ...], keys: tuple):
        line = tuple(map(Scope.get_token, line))
        return any(key in line for key in keys)
    
    @classmethod
    def get_match(cls, line: Token_List, keys: Optional[tuple] = None, depth: int = 0) -> Optional[str]:
        all_keywords = tuple(core.KEYWORDS.keys()) if not keys else keys
        matches = [ast.token for ast in line if ast.token in all_keywords]
        if len(matches) >= depth + 1:
            return matches[depth]
        else:
            return None

    def copy(self) -> 'Scope':
        return Scope(self.name, self.namespace_type, self.children.copy(), self.indent_level)
    
    @classmethod
    def process_scope_from_scope(cls, scope: 'Scope') -> 'Scope':
        temp_scope: Scope | Token_List = Scope(scope.name, scope.namespace_type, [], scope.indent_level)
        new_scope = None
        in_scope = False
        
        for index in range(len(scope.children)):
            if not in_scope and cls.contains(scope.children[index], tuple(tuple(core.NAMESPACED_KEYWORD.keys()))) and temp_scope.indent_level != scope.children[index].indent_level:
                _temp: Optional[str] = cls.get_match(scope.children[index], tuple(tuple(core.NAMESPACED_KEYWORD.keys())))
                
                if _temp is None:
                    raise ValueError(f"Expected a match, got {_temp}")
            
                new_scope = Scope(scope.children[index], core.NAMESPACED_KEYWORD[_temp], [scope.children[index]], scope.children[index].indent_level)
                new_scope.namespace_header = scope.children[index]
                in_scope = True
                continue
            if in_scope:
                if scope.children[index].indent_level == new_scope.indent_level:
                    temp_scope.append_child(new_scope)
                    new_scope = None
                    in_scope = False
                    if cls.contains(scope.children[index], tuple(tuple(core.NAMESPACED_KEYWORD.keys()))):
                        new_scope = Scope(scope.children[index], core.NAMESPACED_KEYWORD[cls.get_match(scope.children[index], tuple(tuple(core.NAMESPACED_KEYWORD.keys())))], [scope.children[index]], scope.children[index].indent_level)
                        new_scope.namespace_header = scope.children[index]
                        in_scope = True
                        continue
                    temp_scope.append_child(scope.children[index])
                else:
                    new_scope.append_line(scope.children[index])
            else:
                temp_scope.append_line(scope.children[index])
        else:
            if new_scope:
                temp_scope.append_child(new_scope)
                
        temp_scope.children = [cls.process_scope_from_scope(child) if isinstance(child, Scope) else child for child in temp_scope.children]
        return temp_scope
    
    @classmethod
    def process_from_lines(cls, lines: tuple[Token_List, ...]) -> 'Scope':
        root_scope = Scope(lines[0].file, "root", [], 0)
        new_scope = None
        in_scope = False

        for index in range(len(lines)):
            if not in_scope and cls.contains(lines[index], tuple(core.NAMESPACED_KEYWORD.keys())):
                new_scope = Scope(lines[index], core.NAMESPACED_KEYWORD[cls.get_match(lines[index], tuple(core.NAMESPACED_KEYWORD.keys()))], [lines[index]], lines[index].indent_level)
                new_scope.namespace_header = lines[index]
                in_scope = True
                continue
            if in_scope:
                if lines[index].indent_level == new_scope.indent_level:
                    root_scope.append_child(new_scope)
                    new_scope = None
                    in_scope = False
                    if cls.contains(lines[index], tuple(core.NAMESPACED_KEYWORD.keys())):
                        new_scope = Scope(lines[index], core.NAMESPACED_KEYWORD[cls.get_match(lines[index], tuple(core.NAMESPACED_KEYWORD.keys()))], [lines[index]], lines[index].indent_level)
                        new_scope.namespace_header = lines[index]
                        in_scope = True
                        continue
                    root_scope.append_child(lines[index])
                else:
                    new_scope.append_line(lines[index])
            else:
                root_scope.append_line(lines[index])
        else:
            if new_scope:
                root_scope.append_child(new_scope)
                
        root_scope.children = [cls.process_scope_from_scope(child) if isinstance(child, cls) else child for child in root_scope.children]
        return root_scope

    @cache
    def get_keyword(self, internal_name: str) -> str:
        return next((keyword for keyword in core.KEYWORDS if core.KEYWORDS[keyword]["internal_name"] == internal_name), None)