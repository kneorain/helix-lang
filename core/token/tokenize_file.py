import functools
from core.token.normalize_tokens import normalize_tokens
from core.token.remove_comments import remove_comment
from core.token.tokenize_line import tokenize_line, standalone_tokenize_line
from classes.Token import Token, Token_List
import globals


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

        if path in globals.CACHE:
            return globals.CACHE[path]

        lines: tuple[Token, ...] = tuple(
            Token(line, "", index + 1, 0)
            for index, line in enumerate(open(path, "r").readlines())
        )

        if globals.USE_POOL:
            [globals.POOL.append(remove_comment, line) for line in lines]
            globals.POOL.execute()

            _tokenize_line = functools.partial(tokenize_line, path=path)
            [globals.POOL.append(_tokenize_line, line) for line in lines]
            globals.POOL.execute()
        else:
            tuple(map(remove_comment, lines))
            tuple(map(lambda _: tokenize_line(_, path), lines))
            
        globals.CACHE[path] = normalize_tokens(lines, path)
        return globals.CACHE[path]

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
        
        
