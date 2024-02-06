from src.classes.namespace import Scope
from src.globals import POOL, KEYWORDS, KEYWORDS

class Transpiler:
    root_scope: Scope
    current_scope: Scope
    parent_scope: Scope
    transpiled: list[str] = []
    
    @classmethod
    def parse_non_keyword(cls, child: Scope, *_):
        pass
    
    @classmethod
    def get_match_function(cls, child: Scope):
        match = Scope.get_match(child, KEYWORDS.keys())
        
        if match:
            return KEYWORDS[match]["parser"]
        else:
            return cls.parse_non_keyword
    
    @classmethod
    def __transpile(cls):
        for child in cls.current_scope.children:
            if isinstance(child, Scope):
                cls.parent_scope = cls.current_scope
                cls.current_scope = child
                cls.__transpile()
            elif isinstance(child, list):
                cls.transpiled.append(cls.get_match_function(child)(child, cls.current_scope, cls.parent_scope, cls.root_scope))
            
    
    @classmethod
    def transpile(cls, root_scope: Scope):
        cls.root_scope = root_scope
        cls.current_scope = root_scope
        cls.parent_scope = root_scope
        
        cls.__transpile()
        exit()
        return cls.transpiled
        