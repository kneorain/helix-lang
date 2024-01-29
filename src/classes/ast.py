class AST:
    def __init__(self, original_line: str, processed_line: str, line_number: int, indent_level: int):
        self.__original_line  = original_line
        self.__processed_line = processed_line
        self.__line_number    = line_number
        self.__indent_level   = indent_level
        
    def __str__(self) -> str:
        return f"AST(\n\toriginal_line\t= {repr(self.__original_line)}, \n\tprocessed_line\t= {self.__processed_line}, \n\tline_number\t= {self.__line_number},\n\tindent_level\t= {self.__indent_level}\n)\n"

    @property
    def original_line(self) -> str:
        return self.__original_line
    
    @property
    def line(self) -> str:
        return self.__processed_line

    @property
    def line_number(self) -> int:
        return self.__line_number
    
    @property
    def indent_level(self) -> int:
        return self.__indent_level

    @original_line.setter
    def original_line(self, value: str) -> None:
        self.__original_line = value
        
    @line.setter
    def line(self, value: str) -> None:
        self.__processed_line = value
        
    @line_number.setter
    def line_number(self, value: int) -> None:
        self.__line_number = value
        
    @indent_level.setter
    def indent_level(self, value: int) -> None:
        self.__indent_level = value
        
    def __hash__(self):
        # Use a tuple of all the relevant attributes for hashing
        return hash((self.__original_line, self.__processed_line, self.__line_number, self.__indent_level))

    def __eq__(self, other):
        # Compare all attributes for equality
        if isinstance(other, AST):
            return (
                self.__original_line == other.__original_line and
                self.__processed_line == other.__processed_line and
                self.__line_number == other.__line_number and
                self.__indent_level == other.__indent_level
            )
        return False
    
    def __repr__(self) -> str:
        return f"AST({repr(self.__original_line)}, {repr(self.__processed_line)}, {self.__line_number}, {self.__indent_level})"
    
    def __iter__(self) -> str:
        return iter(self.__processed_line)
    
    
class AST_LIST(list[AST]):
    def __init__(self, tokens: list[AST], indent_level: int):
        self.line = tokens
        self.indent_level = indent_level
        
    def __str__(self):
        return f"[{self.indent_level}, {[_.line for _ in self.line]}]"
    
    def __iter__(self) -> AST:
        return iter(self.line)