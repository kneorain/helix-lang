from __future__ import annotations
from typing import Optional
from src.core.imports import (
    json,
    subtype,
    Iterable,
    Iterator,
)
from  beartype.door import is_bearable

class Token:
    _: str = "Helix Token"
    
    # ---------------------------- Constructor ------------------------------- #
    def __init__(self,
        original_line: Optional[str],
        processed_line: Optional[str],
        line_number: Optional[int],
        indent_level: Optional[int]
    ):
        self.__original_line:  str             = original_line if original_line is not None else ""
        self.__processed_line: list[str] | str = processed_line if processed_line is not None else ""
        self.__line_number:    int             = line_number if line_number is not None else -1
        self.__indent_level:   int             = indent_level if indent_level is not None else 0

    # ------------------------------- Getters -------------------------------- #

    @property
    def original_line(self) -> str:
        return self.__original_line

    @original_line.setter
    def original_line(self, value: str) -> None:
        self.__original_line = value


    @property
    def line(self) -> list[str] | str:
        return self.__processed_line

    @line.setter
    def line(self, value: list[str]) -> None:
        self.__processed_line = value


    @property
    def token(self) -> str:
        if isinstance(self.__processed_line, list):
            raise ValueError("Token is a list of strings, use the line property to get the list of strings")
        return self.__processed_line

    @token.setter
    def token(self, value: str) -> None:
        self.__processed_line = value


    @property
    def line_number(self) -> int:
        return self.__line_number

    @line_number.setter
    def line_number(self, value: int) -> None:
        self.__line_number = value


    @property
    def indent_level(self) -> int:
        return self.__indent_level

    @indent_level.setter
    def indent_level(self, value: int) -> None:
        self.__indent_level = value


    # ------------------------------- Setters -------------------------------- #
    def set_token(self, value: str) -> 'Token':
        self.__processed_line = value
        return self

    # ---------------------------- Magic Methods ----------------------------- #

    def __hash__(self):
        # Use a tuple of all the relevant attributes for hashing
        return hash((self.__original_line, frozenset(self.__processed_line), self.__line_number, self.__indent_level))

    def __eq__(self, other: object) -> bool:
        # Compare all attributes for equality
        if isinstance(other, Token):
            return (
                self.__original_line == other.__original_line and
                self.__processed_line == other.__processed_line and
                self.__line_number == other.__line_number and
                self.__indent_level == other.__indent_level
            )
        if isinstance(self.__processed_line, str) and isinstance(other, str):
            return self.__processed_line == other
        
        return False

    def __contains__(self, other: Iterable) -> bool:
        if isinstance(self.__processed_line, str):
            return self.__processed_line in other
        return any([_ in other for _ in self.__processed_line])

    def __str__(self) -> str:
        return f"Token(\n\toriginal_line\t= {repr(self.__original_line)}, \n\tprocessed_line\t= {self.__processed_line}, \n\tline_number\t= {self.__line_number},\n\tindent_level\t= {self.__indent_level}\n)\n"

    def __repr__(self) -> str:
        return f"Token({repr(self.__processed_line)})"

    def __iter__(self) -> Iterator[str]:
        return iter(self.__processed_line)
    
    def is_empty(self) -> bool:
        return not self.__processed_line


class Token_List(list[Token]):
    _: str = "Raw Token List; Using Token_List"
    
    def __init__(self, tokens: list[Token], indent_level: int, file: str):
        self.line = tokens
        self.indent_level = indent_level
        self.file = file

    def __str__(self):
        return (f"Token_List("
            f"line = {self.line}, "
            f"indent_level = {self.indent_level}, "
            f"file = {self.file}"
        ")")
    
    def __iter__(self) -> Iterator[Token]:
        return iter(self.line)

    def __hash__(self) -> int:
        return hash((tuple(self.line), self.indent_level))

    def __eq__(self, other) -> bool:
        if isinstance(other, Token_List):
            return self.line == other.line and self.indent_level == other.indent_level
        return False

    def __len__(self) -> int:
        return len(self.line)

    def __repr__(self) -> str:
        return '"' + ' '.join([_.token for _ in self.line]) + '"'

    def __getitem__(self, index: int) -> Token:
        return self.line[index]

    def __setitem__(self, index: int, value: Token) -> None:
        self.line[index] = value

    def remove(self, __value: str) -> None:
        self.line = [token for token in self.line if token.token != __value]

    def index(self, __value: str) -> int:
        return [i for i, token in enumerate(self.line) if token.token == __value][0]

    def find_line_number(self, token: str) -> int:
        for line in self.line:
            if isinstance(token, str) and token in line.token:
                return line.line_number
            elif isinstance(token, Token) and token.token in line.token:
                return line.line_number
        return -1

    def __contains__(self, __key: object | Iterable[Token_List]) -> bool:
        if isinstance(__key, subtype(Iterable[Token_List])): # type: ignore
            return any([token in __key for token in self.line]) # type: ignore
        if isinstance(__key, tuple):
            return any([token in __key for token in self.line])
        return any([token == __key for token in self.line])


    def contains_from(self, __key: object | Iterable[Token_List]) -> str:
        if isinstance(__key, subtype(Iterable[Token_List])): # type: ignore
            return [[token for token in self.line if token in __key]+[False]][0] # type: ignore
        return [[token for token in self.line if token == __key]+[False]][0] # type: ignore
    # TODO: switch isinstance to is_bearable

    def full_line(self) -> str:
        return ' '.join([_.token for _ in self.line])

    def get_all_after(self, token: str) -> list[Token]:
        # get all tokens after the token
        found: int = 0
        for i, line in enumerate(self.line):
            if line.token == token:
                found = i
                break
        return [line for line in self.line[found+1:]]

    def get_all_before(self, token: str) -> list[Token]:
        # get all tokens before the token
        found: int = 0
        for i, line in enumerate(self.line):
            if line.token == token:
                found = i
                break
        return [line for line in self.line[:found]]

    def get_between(self, start: str, end: str) -> list[Token]:
        start_index: int = 0
        end_index: int = 0
        count: int = 0

        for i, line in enumerate(self.line):
            if line.token == start and not count > 0:
                start_index = i
                count += 1
            elif line.token == start and count > 0:
                count += 1
            if line.token == end:
                count -= 1
                if count == 0:
                    end_index = i
                    break

        return [line for line in self.line[start_index+1:end_index]]

    def copy(self) -> 'Token_List':
        return Token_List(self.line.copy(), self.indent_level, self.file)

    def count(self, __value: str) -> int:
        return sum([1 for token in self.line if token.token == __value])

    def split(self, __value: str) -> list['Token_List']:
        output: list['Token_List'] = []
        temp: list[Token] = []
        for token in self.line:
            if token.token == __value:
                output.append(Token_List(temp, self.indent_level, self.file))
                temp = []
            else:
                temp.append(token)
        if temp:
            output.append(Token_List(temp, self.indent_level, self.file))
        return output

    # add support for the splicing so [1:2] works or any other slicing
    def splice(self, start: int = 0, end: Optional[int] = None) -> 'Token_List':
        temp = self.copy()
        temp.line = temp.line[start:end]
        return temp

    def append(self, __value: Token | str) -> None:
        if isinstance(__value, str):
            self.line.append(Token(None, __value, -1, self.indent_level))
        else:
            self.line.append(__value)

    def replace(self, __old: str, __new: str) -> 'Token_List':
        self.line = [token if token.token != __old else token.set_token(__new) for token in self.line]
        return self


class Processed_Line:
    def __init__(self, line: str, non_parsed_line: Token_List):
        self.line = line
        self.non_parsed_line = non_parsed_line

    def __str__(self):
        return self.line

    def __repr__(self):
        return repr(self.line.rstrip())

    def to_code(self) -> str:
        return self.line

    def to_line_number(self) -> str:
        # get the most commen line num in self.non_parsed_line.line not the largest
        from collections import Counter
        if len(self.line.splitlines()) > 1:
            return (str(Counter([str(_.line_number) for _ in self.non_parsed_line.line]).most_common(1)[0][0]) + "\n") * len([_ for _ in self.line.splitlines() if _.strip()])

        return str(Counter([str(_.line_number) for _ in self.non_parsed_line.line]).most_common(1)[0][0])