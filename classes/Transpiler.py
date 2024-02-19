from typing import Callable

from classes.Scope import Scope
from classes.Token import Processed_Line, Token_List
from core.config import load_config
from functions._unmarked import _unmarked
import globals


INDENT_CHAR = load_config().Formatter["indent_char"]


class Transpiler:
    copied_scope: Scope
    
    root_scope: Scope
    scope_stack: list[Scope] = []
    
    transpiled: list[Processed_Line] = []
    add_to_transpiled_queue: list[tuple[str, Scope]] = []
    
    @classmethod
    def parse_non_keyword(cls, line: Token_List, *_: Scope) -> str:
        return _unmarked(line, cls.scope_stack[-1] if len(cls.scope_stack) >= 1 else cls.root_scope, cls.scope_stack[-2] if len(cls.scope_stack) >= 2 else cls.root_scope, cls.root_scope)
    
    @classmethod
    def get_match_function(cls, child: Scope) -> Callable[..., str]:
        match = Scope.get_match(child, globals.KEYWORDS.keys())

        if match:
            return globals.KEYWORDS[match]["parser"]
        else:
            return cls.parse_non_keyword
    
    @classmethod
    def __transpile(cls, child: Scope | Token_List = None) -> None:
        if isinstance(child, Scope):
            cls.scope_stack.append(child) # push
            [cls.__transpile(child) for child in child.children] # recursive call
            cls.scope_stack.pop() # pop
            cls.__add_from_queue(child) # add any lines that were added to the queue (so at the end of the current scope)
                
        elif isinstance(child, Token_List):
            cls.transpiled.append(cls.get_match_function(child)(child, cls.scope_stack[-1] if len(cls.scope_stack) >= 1 else cls.root_scope, cls.scope_stack[-2] if len(cls.scope_stack) >= 2 else cls.root_scope, cls.root_scope))

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
        cls.scope_stack   = []
        
        #globals.POOL.map(cls.__transpile, root_scope.children, chunksize=10)
        [cls.__transpile(child) for child in root_scope.children]
        cls.__add_from_queue(root_scope)
            
        print(*cls.transpiled, sep="\n")
        return cls.transpiled
