import functools
from src.token.normalize_tokens import normalize_tokens
from src.token.remove_comments import remove_comment
from src.token.tokenize_line   import tokenize_line
from src.classes.Token import Token, Token_List
import src.core.base as base
<<<<<<< HEAD
=======

>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5


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

        if path in base.CACHE:
            return base.CACHE[path]

        with open(path, "r") as file:
            lines = tuple(Token(line, "", index + 1, 0) for index, line in enumerate(file))

<<<<<<< HEAD
        if base.USE_POOL:
            [base.POOL.append(remove_comment, line) for line in lines]
            base.POOL.execute()

            _tokenize_line = functools.partial(tokenize_line, path=path)
            
            [base.POOL.append(_tokenize_line, line) for line in lines]
            base.POOL.execute()
=======
        if base.USE_POOL and len(lines) > 1000:
            base.POOL.map(remove_comment, lines)  # Batch operation
            base.POOL.map(lambda line: tokenize_line(line, path), lines)
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
        else:
            tuple(map(remove_comment, lines))
            tuple(map(lambda line: tokenize_line(line, path), lines))
            
<<<<<<< HEAD
        base.CACHE[path] = normalize_tokens(lines, path)
        return base.CACHE[path]
=======
        normalized_tokens = normalize_tokens(lines, path)
        base.CACHE[path] = normalized_tokens
        return normalized_tokens
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5

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
        
        
