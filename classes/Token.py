import json
from typing import Iterator


class Token:
    # ---------------------------- Constructor ------------------------------- #
    def __init__(self, original_line: str, processed_line: str, line_number: int, indent_level: int):
        self.__original_line:  str             = original_line
        self.__processed_line: list[str] | str = processed_line
        self.__line_number:    int             = line_number
        self.__indent_level:   int             = indent_level
        
    # ------------------------------- Getters -------------------------------- #

    @property
    def original_line(self) -> str:
        return self.__original_line
    
    @property
    def line(self) -> str:
        return self.__processed_line
    
    @property
    def token(self) -> str:
        return self.__processed_line

    @property
    def line_number(self) -> int:
        return self.__line_number
    
    @property
    def indent_level(self) -> int:
        return self.__indent_level

    # ------------------------------- Setters -------------------------------- #

    @original_line.setter
    def original_line(self, value: str) -> None:
        self.__original_line = value
                
    @line.setter
    def line(self, value: list[str]) -> None:
        self.__processed_line = value
        
    @token.setter
    def token(self, value: str) -> None:
        self.__processed_line = value
        
    @line_number.setter
    def line_number(self, value: int) -> None:
        self.__line_number = value
        
    @indent_level.setter
    def indent_level(self, value: int) -> None:
        self.__indent_level = value
        
    # ---------------------------- Magic Methods ----------------------------- #

    def __hash__(self):
        # Use a tuple of all the relevant attributes for hashing
        return hash((self.__original_line, frozenset(self.__processed_line), self.__line_number, self.__indent_level))

    def __eq__(self, other):
        # Compare all attributes for equality
        if isinstance(other, Token):
            return (
                self.__original_line == other.__original_line and
                self.__processed_line == other.__processed_line and
                self.__line_number == other.__line_number and
                self.__indent_level == other.__indent_level
            )
        return False
    
    def __str__(self) -> str:
        return f"Token(\n\toriginal_line\t= {repr(self.__original_line)}, \n\tprocessed_line\t= {self.__processed_line}, \n\tline_number\t= {self.__line_number},\n\tindent_level\t= {self.__indent_level}\n)\n"

    def __repr__(self) -> str:
        return f"Token({repr(self.__processed_line)})"
    
    def __iter__(self) -> str:
        return iter(self.__processed_line)
    
    
class Token_List(list[Token]):
    def __init__(self, tokens: list[Token], indent_level: int, file: str):
        self.line = tokens
        self.indent_level = indent_level
        self.file = file
        
    def __str__(self):
        return json.dumps({"line_indent_level": self.indent_level, "joined_line": [_.token for _ in self.line]})
    #f"\"Token_List\": {{\"line_indent_level\": {self.indent_level}, \"joined_line\": \"{(' '.join([_.token for _ in self.line])).replace('\"', '\\\"').replace('\'', '\\\'')}\"}}"
    
    def __iter__(self) -> Iterator[Token]:
        return iter(self.line)
    
    def __hash__(self) -> int:
        return hash((frozenset(self.line), self.indent_level))
    
    def __eq__(self, other) -> bool:
        if isinstance(other, Token_List):
            return self.line == other.line and self.indent_level == other.indent_level
        return False
    
    def __repr__(self) -> str:
        return '"' + ' '.join([_.token for _ in self.line]) + '"'
    
    
    def __getitem__(self, index: int) -> Token:
        return self.line[index]
    
    def __setitem__(self, index: int, value: Token) -> None:
        self.line[index] = value
        
    def remove(self, __value: str) -> None:
        self.line = [token for token in self.line if token.token != __value]
    
    def find_line_number(self, token: str) -> int:
        for line in self.line:
            if token in line.token:
                return line.line_number
        return -1