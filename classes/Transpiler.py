from typing import Callable

from classes.Scope import Scope
from classes.Token import Processed_Line, Token_List
from core.config import load_config
from functions._unmarked import _unmarked
import globals
from core.better_print import color_print


INDENT_CHAR = load_config().Formatter["indent_char"]


class Transpiler:
    def __init__(self) -> None:
        self.copied_scope: Scope
        
        self.root_scope: Scope
        self.scope_stack: list[Scope] = []
        
        self.transpiled: list[Processed_Line] = []
        self.add_to_transpiled_queue: list[tuple[str, Scope]] = []
    
    def parse_non_keyword(self, line: Token_List, *_: Scope) -> str:
        return _unmarked(line, self.scope_stack[-1] if len(self.scope_stack) >= 1 else self.root_scope, self.scope_stack[-2] if len(self.scope_stack) >= 2 else self.root_scope, self.root_scope, self.ignore_main)
    
    def get_match_function(self, child: Scope) -> Callable[..., str]:
        match = Scope.get_match(child, globals.KEYWORDS.keys())

        if match:
            return globals.KEYWORDS[match]["parser"]
        else:
            return self.parse_non_keyword
    
    def __transpile(self, child: Scope | Token_List = None) -> None:
        if isinstance(child, Scope):
            self.scope_stack.append(child) # push
            [self.__transpile(child) for child in child.children] # recursive call
            self.scope_stack.pop() # pop
            self.__add_from_queue(child) # add any lines that were added to the queue (so at the end of the current scope)
                
        elif isinstance(child, Token_List):
            self.transpiled.append(self.get_match_function(child)(child, self.scope_stack[-1] if len(self.scope_stack) >= 1 else self.root_scope, self.scope_stack[-2] if len(self.scope_stack) >= 2 else self.root_scope, self.root_scope))

    def append_at_end(self, line: str, current_scope: Scope):
        self.add_to_transpiled_queue.append((line, current_scope))
    
    def __add_from_queue(self, child: Scope):
        if self.add_to_transpiled_queue:
            for item in self.add_to_transpiled_queue:
                if item[1] is child:
                    self.transpiled.append(item[0])
                    self.add_to_transpiled_queue.remove(item)

    def reset(self):
        self.copied_scope = None
        self.root_scope = None
        self.scope_stack = []
        self.transpiled = []
        self.add_to_transpiled_queue = []

    def transpile(self, root_scope: Scope, ignore_main: bool = False):
        if self.transpiled:
            color_print("WARNING: Transpiler state was not reset before transpiling. This may cause unexpected behavior. Reset the state with Transpiler.reset() before transpiling.", border=True, style="rgb(255, 155, 50)", word_wrap=True)
        
        self.root_scope    = root_scope
        self.scope_stack   = []
        self.ignore_main   = ignore_main
        
        #globals.POOL.map(self.__transpile, root_scope.children, chunksize=10)
        [self.__transpile(child) for child in root_scope.children]
        self.__add_from_queue(root_scope)
            
        return self.transpiled