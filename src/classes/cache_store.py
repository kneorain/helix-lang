DISABLED: bool = False


from   os        import (path as os_path, mkdir)
from   pickle     import dump, load
from   threading import Thread
from   functools  import wraps
from   typing     import Callable, Tuple, Union

CACHE_DIR: str = os_path.join(os_path.dirname(os_path.dirname(__file__)), "cache")
local_cache: dict[str, any] = {}

if not os_path.isdir(CACHE_DIR):
    mkdir(CACHE_DIR)

def async_cache(path: str, args: tuple, result: any) -> None:
    global local_cache
    
    local_cache[args] = result
    with open(path, "wb") as file:
        dump(local_cache, file)

def get_cache(path: str, args: tuple) -> Union[any, None]:
    global local_cache
    
    if os_path.isfile(path):
        with open(path, "rb") as file:
            try:
                local_cache = load(file)
            except EOFError:
                return None
            return local_cache[args] if args in local_cache else None
    
    return None

from functools import lru_cache
def cache(func: Callable) -> Callable:
    return lru_cache(maxsize=None)(func)
    def dummy(*args: Tuple[any, ...], **kwargs: dict[str, any]) -> any:
        return func(*args, **kwargs)
    
    
    @wraps(func)
    def wrapper(*args: Tuple[any, ...], **kwargs: dict[str, any]) -> any:
        if DISABLED: return func(*args, **kwargs)
        
        global local_cache
        
        cache_file_path: str = os_path.join(CACHE_DIR, f"{func.__name__}.cache")

        if args in local_cache:
            return local_cache[args]
        else:
            result = get_cache(cache_file_path, args)
            if result:
                return result
        
        result: any = func(*args, **kwargs)
        async_cache(cache_file_path, args, result)
        
        return result
    return wrapper
    
if __name__ == "__main__":
    from time import process_time_ns
    
    
    @cache
    def fib(n: int) -> int:
        if n <= 1:
            return n
        else:
            return fib(n-1) + fib(n-2)
    
    start = process_time_ns()
    print(fib(100))
    end = process_time_ns()
    
    print("Time:", (end - start) / 1000000000, "seconds", "or about", (end - start), "nanoseconds")