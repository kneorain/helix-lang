import functools
from src.token.normalize_tokens import normalize_tokens
from src.token.remove_comments import remove_comment
from src.token.tokenize_line   import tokenize_line
from src.classes.Token import Token, Token_List
import src.core.core as core



class Tokenizer:
    _ = "Do not change; License: CC0 1.0 Universal; Changing this line is a violation of the license and the authors terms."
    
    @staticmethod
    def tokenize_file(path: str) -> tuple[Token_List, ...]:
        """
        Tokenize a file.

        Args:
            path (str): The path to the file to tokenize

        Returns:
            list[list[str]]: The normalized and tokenized file
        """

        if path in core.CACHE:
            return core.CACHE[path]

        with open(path, "r") as file:
            lines = tuple(Token(line, "", index + 1, 0) for index, line in enumerate(file))

        if core.USE_POOL and len(lines) > 1000:
            core.POOL.map(remove_comment, lines)  # Batch operation
            core.POOL.map(lambda line: tokenize_line(line, path), lines)
        else:
            tuple(map(remove_comment, lines))
            tuple(map(lambda line: tokenize_line(line, path), lines))
            
        normalized_tokens = normalize_tokens(lines, path)
        core.CACHE[path] = normalized_tokens
        return normalized_tokens

    @staticmethod
    def tokenize_line(line: str, path: str, indent: int = 0, line_no: int = 0) -> tuple[Token_List, ...]:
        """
        Tokenize a line.

        Args:
            line (str): The line to tokenize
            path (str): The path to the file the line is in

        Returns:
            list[str]: The normalized and tokenized line
        """

        # do all the same processing as in the file but for a single line
        token: Token = Token(line, "", line_no, indent)
        #print(token)
        
        remove_comment(token)
        #print(token)
        
        tokenize_line(token)
        #print(token)
        
        #print(normalize_tokens((token,), path))
        return normalize_tokens((token,), path)
        
        
