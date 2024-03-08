from core.cache_store import cache
from core.panic import panic
from globals import BODY_REQUIRED_KEYWORDS, find_keyword
from classes.Token import Token, Token_List

def colon_check(all_tokens: tuple[Token, ...]):
    print(all_tokens)