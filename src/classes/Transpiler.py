import src.core.base as base
<<<<<<< HEAD
from src.functions._unmarked import _unmarked
from src.core.imports import (
    Callable,
    Optional,
=======
from src.core.imports import (
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
    Scope,
    Processed_Line,
    Token_List,
    color_print,
<<<<<<< HEAD
    INDENT_CHAR,
)


class Transpiler:
    def __init__(self) -> None:
        self.copied_scope: Optional[Scope]
        
        self.root_scope:   Optional[Scope]
        self.scope_stack:  list[Scope] = []
        
        self.transpiled:   list[Processed_Line] = []
        self.add_to_transpiled_queue: list[tuple[Processed_Line, Scope]] = []
    
    def parse_non_keyword(self, line: Token_List, *_: Scope) -> str:
        return _unmarked(line, self.scope_stack[-1] if len(self.scope_stack) >= 1 else self.root_scope, self.scope_stack[-2] if len(self.scope_stack) >= 2 else self.root_scope, self.root_scope, self.ignore_main)
=======
    Callable, Optional
)

class Transpiler:
    def __init__(self) -> None:
        self.copied_scope: Optional[Scope] = None
        self.root_scope: Optional[Scope] = None
        self.scope_stack: list[Scope] = []
        self.transpiled: list[Processed_Line] = []
        self.add_to_transpiled_queue: list[tuple[Processed_Line, Scope]] = []
        self.ignore_main: bool = False
    
    def parse_non_keyword(self, line: Token_List, *_: Optional[Scope]) -> Processed_Line:
        #if not self.scope_stack:
        #    raise ValueError("scope_stack is empty. Internal reference error. This should never happen.")
        
        current_scope = self.scope_stack[-1] if self.scope_stack else self.root_scope
        parent_scope  = self.scope_stack[-2] if len(self.scope_stack) > 1 else self.root_scope
        root_scope    = self.root_scope
        
        if current_scope is None:
            raise ValueError("current_scope is None. Internal reference error. This should never happen.")
        if parent_scope is None:
            raise ValueError("parent_scope is None. Internal reference error. This should never happen.")
        if root_scope is None:
            raise ValueError("root_scope is None. Internal reference error. This should never happen.")
        
        return base._unmarked(line, current_scope, parent_scope, root_scope, self.ignore_main)
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
    
    def get_match_function(self, child: Token_List) -> Callable[[Token_List, Optional[Scope], Optional[Scope], Scope], Processed_Line]:
        match = Scope.get_match(child, tuple(base.KEYWORDS.keys()))

        if match:
<<<<<<< HEAD
            return base.KEYWORDS[match]["parser"]
        else:
            return self.parse_non_keyword
    
    def __transpile(self, child: Scope | Token_List = None) -> None:
        if isinstance(child, Scope):
            self.scope_stack.append(child) # push
            
            #with ThreadPoolExecutor() as executor:
            #    # Submit all transpile tasks to the executor
            #    futures = [executor.submit(self.__transpile, child) for child in child.children]
            #
            #    # Gather the results
            #    [future.result() for future in futures]

            [self.__transpile(child) for child in child.children] # recursive call
            
            self.scope_stack.pop() # pop
            self.__add_from_queue(child) # add any lines that were added to the queue (so at the end of the current scope)
=======
            return base.KEYWORDS[match]["parser"] # type: ignore
        else:
            return self.parse_non_keyword
    
    def __transpile(self, child: Scope | Token_List) -> None:
        if isinstance(child, Scope):
            self.scope_stack.append(child)  # push
            for child_scope in child.children:
                self.__transpile(child_scope)  # recursive call
            self.scope_stack.pop()  # pop
            self.__add_from_queue(child)  # add any lines that were added to the queue
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
                
        elif isinstance(child, Token_List):
            if self.root_scope is None:
                raise ValueError("root_scope is None. Internal reference error. This should never happen.")
<<<<<<< HEAD
            self.transpiled.append(self.get_match_function(child)(child, self.scope_stack[-1] if len(self.scope_stack) >= 1 else self.root_scope, self.scope_stack[-2] if len(self.scope_stack) >= 2 else self.root_scope, self.root_scope))

    def append_at_end(self, line: Processed_Line, current_scope: Scope):
        self.add_to_transpiled_queue.append((line, current_scope))
    
    def __add_from_queue(self, child: Scope):
=======
            matched_func = self.get_match_function(child)
            self.transpiled.append(matched_func(child, self.scope_stack[-1] if self.scope_stack else self.root_scope, self.scope_stack[-2] if len(self.scope_stack) > 1 else self.root_scope, self.root_scope))

    def append_at_end(self, line: Processed_Line, current_scope: Scope) -> None:
        self.add_to_transpiled_queue.append((line, current_scope))
    
    def __add_from_queue(self, child: Scope) -> None:
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
        if self.add_to_transpiled_queue:
            self.transpiled.extend([item[0] for item in self.add_to_transpiled_queue if item[1] is child])
            self.add_to_transpiled_queue = [item for item in self.add_to_transpiled_queue if item[1] is not child]

<<<<<<< HEAD
    def reset(self):
        self.copied_scope = None
        self.root_scope   = None
        self.scope_stack  = []
        self.transpiled   = []
        self.add_to_transpiled_queue = []

    def transpile(self, root_scope: Scope, ignore_main: bool = False):
        if self.transpiled:
            color_print("WARNING: Transpiler state was not reset before transpiling. This may cause unexpected behavior. Reset the state with Transpiler.reset() before transpiling.", border=True, style="rgb(255, 155, 50)", word_wrap=True)
        
        self.root_scope    = root_scope
        self.scope_stack   = []
        self.ignore_main   = ignore_main
        self.root_scope.transpiler_instance = self
        
        [self.__transpile(child) for child in root_scope.children]
            
        self.__add_from_queue(root_scope)
            
        return self.transpiled
=======
    def reset(self) -> None:
        self.copied_scope = None
        self.root_scope = None
        self.scope_stack = []
        self.transpiled = []
        self.add_to_transpiled_queue = []

    def transpile(self, root_scope: Scope, ignore_main: bool = False) -> list[Processed_Line]:
        if self.transpiled:
            color_print("WARNING: Transpiler state was not reset before transpiling. This may cause unexpected behavior. Reset the state with Transpiler.reset() before transpiling.", border=True, style="rgb(255, 155, 50)", word_wrap=True)
        
        self.root_scope = root_scope
        self.ignore_main = ignore_main
        self.root_scope.transpiler_instance = self
        
        for child in root_scope.children:
            self.__transpile(child)
            
        self.__add_from_queue(root_scope)
            
        return self.transpiled
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
