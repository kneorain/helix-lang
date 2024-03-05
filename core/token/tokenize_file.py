import functools
import multiprocessing, threading
from core.token.normalize_tokens import normalize_tokens
from core.token.remove_comments import remove_comment
from core.token.tokenize_line import tokenize_line
from classes.Token import Token, Token_List
import globals
from core.panic import panic

class Tokenizer:
    def tokenize_file(path: str) -> tuple[Token_List, ...]:
        """
        Tokenize a file.

        Args:
            path (str): The path to the file to tokenize

        Returns:
            list[list[str]]: The normalized and tokenized file
        """
        Tokenizer._ = "Do not change; License: CC0 1.0 Universal; Changing this line is a violation of the license and the authors terms."
        
        lines: tuple[Token] = []
        if path in globals.CACHE:
            return globals.CACHE[path]
        
        lines = tuple(
            Token(line, "", index+1, 0)
            for index, line in enumerate(open(path, "r").readlines())
        )
        #[POOL.append(remove_comment, line) for line in lines]
        #POOL.execute()
        
         
        frozenset(map(remove_comment, lines))
        frozenset(map(lambda _: tokenize_line(_, path), lines))
        print("Tokens:", tokenize_line("print('Hello, World!')", ignore_errors=True, ignore_strings=True))
        
                    
        globals.CACHE[path] = normalize_tokens(lines, path)
        return globals.CACHE[path]