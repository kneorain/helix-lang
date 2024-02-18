from typing import Callable

from classes.Scope import Scope
from classes.Token import Processed_Line, Token_List
from core.config import load_config
import globals

INDENT_CHAR = load_config().Formatter["indent_char"]


class Transpiler:
    copied_scope: Scope
    root_scope: Scope
    current_scope: Scope
    parent_scope: Scope
    transpiled: list[Processed_Line] = []
    add_to_transpiled_queue: list[tuple[str, Scope]] = []
    
    @classmethod
    def parse_non_keyword(cls, line: Token_List, *_: Scope) -> str:
        return f"{INDENT_CHAR*line.indent_level}{line.full_line()}".replace("::", ".")
    
    @classmethod
    def get_match_function(cls, child: Scope) -> Callable[..., str]:
        match = Scope.get_match(child, globals.KEYWORDS.keys())

        if match:
            return globals.KEYWORDS[match]["parser"]
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
            
            cls.__add_from_queue(child)
                
        elif isinstance(child, list):
            cls.transpiled.append(cls.get_match_function(child)(child, cls.current_scope, cls.parent_scope, cls.root_scope))

    @classmethod
    def append_at_end(cls, line: str, current_scope: Scope):
        cls.add_to_transpiled_queue.append((line, current_scope))
    
    @classmethod
    def __add_from_queue(cls, child: Scope):
        if cls.add_to_transpiled_queue:
            for item in cls.add_to_transpiled_queue:
                if item[1] is child:
                    cls.transpiled.append(item[0])
                    cls.add_to_transpiled_queue.remove(item)

    @classmethod
    def transpile(cls, root_scope: Scope):
        cls.root_scope    = root_scope
        cls.current_scope = root_scope
        cls.parent_scope  = root_scope
        
        #globals.POOL.map(cls.__transpile, root_scope.children, chunksize=10)
        [cls.__transpile(child) for child in root_scope.children]
        cls.__add_from_queue(root_scope)
            
        print(*cls.transpiled, sep="\n")
        return cls.transpiled
