DISABLED: bool = False

from src.core.imports import (
    dump, load,
    wraps,
    Callable, Tuple, Union,
    lru_cache,
    os,
)

CACHE_DIR: str = os.path.join(os.path.dirname(os.path.dirname(__file__)), "cache")
local_cache: dict[str, any] = {}

if not os.path.isdir(CACHE_DIR):
    os.mkdir(CACHE_DIR)

def async_cache(path: str, args: tuple, result: any) -> None:
    global local_cache
    
    local_cache[args] = result
    with open(path, "wb") as file:
        dump(local_cache, file)

def get_cache(path: str, args: tuple) -> Union[any, None]:
    global local_cache
    
    if os.path.isfile(path):
        with open(path, "rb") as file:
            try:
                local_cache = load(file)
            except EOFError:
                return None
            return local_cache[args] if args in local_cache else None
    
    return None

def cache(func: Callable) -> Callable:
    return lru_cache(maxsize=None)(func)

def file_cache(func: Callable) -> Callable:
    @wraps(func)
    def wrapper(*args: Tuple[any, ...], **kwargs: dict[str, any]) -> any:
        if DISABLED: return func(*args, **kwargs)
        
        global local_cache
        
        cache_file_path: str = os.path.join(CACHE_DIR, f"{func.__name__}.cache")

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