from typing import Callable
from classes.Scope import Scope
from globals import POOL, KEYWORDS, KEYWORDS
from classes.Token import Token_List
from headder import INDENT_CHAR

class Transpiler:
    root_scope: Scope
    current_scope: Scope
    parent_scope: Scope
    transpiled: list[str] = []
    
    @classmethod
    def parse_non_keyword(cls, line: Token_List, *_: Scope) -> str:
        return f"{INDENT_CHAR*line.indent_level}{line.full_line()}".replace("::", ".")
    
    @classmethod
    def get_match_function(cls, child: Scope) -> Callable[..., str]:
        match = Scope.get_match(child, KEYWORDS.keys())

        if match:
            return KEYWORDS[match]["parser"]
        else:
            return cls.parse_non_keyword
    
    @classmethod
    def __transpile(cls, child: Scope = None) -> None:
        if isinstance(child, Scope):
            if child.indent_level == 0:
                cls.parent_scope = cls.root_scope
            else:
                cls.parent_scope = cls.current_scope
            cls.current_scope = child
            [cls.__transpile(child) for child in child.children]
        elif isinstance(child, list):
            cls.transpiled.append(cls.get_match_function(child)(child, cls.current_scope, cls.parent_scope, cls.root_scope))


    @classmethod
    def transpile(cls, root_scope: Scope):
        cls.root_scope    = root_scope
        cls.current_scope = root_scope
        cls.parent_scope  = root_scope
        
        [cls.__transpile(child) for child in root_scope.children]
        #POOL.map(cls.__transpile, root_scope.children, chunksize=10)
        print(*cls.transpiled, sep="\n")
        return cls.transpiled
        
        
