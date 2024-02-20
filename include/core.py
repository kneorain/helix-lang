from abc import ABC
from abc import abstractmethod as hx__abstract_method
from dataclasses import dataclass
from enum import Enum
from threading import Thread
from types import MappingProxyType as FastMap
from typing import Any, NoReturn

from multimethod import multimeta
from multimethod import multimethod as hx__multi_method
from multimethod import subtype

from core.panic import panic
from include.__c_cpp_import__ import __c_cpp_import__
    
def printf(string: str, *args):
    panic(
        NotImplementedError("printf is not implemented in Helix (YET)"),
        file=__file__,
    )
    print(string % args)
    
unknown = Any
replace_primitives = FastMap({
    "hx_int"    : "int",
    "hx_string" : "string",
    "hx_float"  : "float",
    "hx_map"    : "map",
    "hx_list"   : "list",
    "hx_bool"   : "bool",
    "hx_char"   : "char",
    "hx_void"   : "void",
    "hx_tuple"  : "tuple",
    "hx_array"  : "array",
    "hx_set"    : "set"
})

class void:
    def __init__(self, *args, **kwargs):
        pass
    def __set__(self, value: Any) -> None:
        pass
    def __set_generic__(self, value: Any) -> None:
        pass
    def __get__(self) -> None:
        pass
    def __get_generic__(self) -> None:
        pass
    def __new__(self, *args, **kwargs):
        return self
    def __call__(self, *args, **kwargs):
        pass
    def __del__(self):
        pass

DEFAULT_VALUE = void()

class C_For:
    def __init__(self, **kwargs):
        # Initialize loop variables
        self.loop_vars = kwargs
        # Extract condition and increment expressions
        self.condition = 'True'
        self.increment = ''
        # Evaluate initial conditions
        [exec(f"{var} = {value}") for var, value in self.loop_vars.items()]

    def __iter__(self):
        return self

    def __next__(self):
        if not self.loop_condition_met:
            raise StopIteration
        current_values = tuple(self.loop_vars.values())
        exec(self.increment, None, self.loop_vars)
        self.loop_condition_met = eval(self.condition, None, self.loop_vars)
        return current_values if len(current_values) > 1 else current_values[0]
    
    def set_con(self, condition):
        self.condition = condition
        self.loop_condition_met = eval(self.condition, None, self.loop_vars)
        return self
    
    def set_inc(self, increment):
        self.increment = increment.replace('++', '+= 1').replace('--', '-= 1').replace('+*', '*= 1').replace('-*', '*= -1').replace('/-', '/ -1').replace('/*', '*= 1')
        return self
    
def hx__async(func):
    def wrapper(*args, **kwargs):
        Thread(target=func, args=args, kwargs=kwargs, daemon=True).start()
    return wrapper

class hx_void:
    def __init__(self, *args, **kwargs):
        pass
    def __set__(self, value: Any) -> None:
        pass
    def __set_generic__(self, value: Any) -> None:
        pass
    def __get__(self) -> None:
        pass
    def __get_generic__(self) -> None:
        pass
    def __new__(self, *args, **kwargs):
        return self
    def __call__(self, *args, **kwargs):
        pass
    def __del__(self):
        pass

class hx_int(int, metaclass=multimeta):
    __value__: int = 0
    
    def __set__(self, __o: int) -> None:
        if isinstance(__o, subtype(self.__class__ | void | int | float | bytes)):
            self.__value__ = __o
        else:
            try:
                self.__value__ = int(__o)
            except Exception as e:
                panic(
                    TypeError(f"Expected type {self.__class__}, got {type(__o)}, unable to cast"),
                    file=__file__,
                )
                
    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=__file__,
        )
    
    def __init__(self, __o: int):
        self.__set__(__o if not isinstance(__o, void) else 0)
        
    def __get__(self) -> int:
        return self.__value__
    
    def __int__(self) -> int:
        return self.__value__
    
class hx_string(str, metaclass=multimeta):
    __value__: str = ""
    
    def __set__(self, __o: str) -> None:
        if isinstance(__o, self.__class__):
            self.__value__ = __o
        else:
            try:
                self.__value__ = str(__o)
            except Exception as e:
                panic(
                    TypeError(f"Expected type {self.__class__}, got {type(__o)}, unable to cast"),
                    file=__file__,
                )
                
    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=__file__,
        )
    
    def __init__(self, __o: str):
        self.__set__(__o if not isinstance(__o, void) else "")
        super().__new__(self.__value__)
        
    def __get__(self) -> str:
        return self.__value__
    
class hx_float(float, metaclass=multimeta):
    __value__: float = 0.0
    
    def __set__(self, __o: float | void) -> None:
        if isinstance(__o, self.__class__):
            self.__value__ = __o
        else:
            try:
                self.__value__ = float(__o)
            except Exception as e:
                panic(
                    TypeError(f"Expected type {self.__class__}, got {type(__o)}, unable to cast"),
                    file=__file__,
                )
                
    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=__file__,
        )
    
    def __init__(self, __o: float | void):
        self.__set__(__o if not isinstance(__o, void) else 0.0)
        super().__new__(self.__value__)
        
    def __get__(self) -> float:
        return self.__value__


class hx_map[T](dict, metaclass=multimeta):
    __value__: dict = {}
    __generic__: subtype = None
    
    def __set__(self, __o: dict | void) -> None:
        if isinstance(__o, self.__class__ if not self.__generic__ else self.__generic__):
            self.__value__ = __o
        else:
            try:
                self.__value__ = dict(__o)
                if self.__generic__ and not isinstance(self.__value__, self.__generic__):
                    panic(
                        TypeError(f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"),
                        file=__file__,
                    )
            except Exception as e:
                panic(
                    TypeError(f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"),
                    file=__file__,
                )
                
    def __set_generic__(self, __o: str) -> None:
        exec(f"self.__generic__ = {f'subtype(dict[{__o[1:-1]}]'.replace('hx_map', 'dict')} | void)")
        if self.__value__: self.__set__(self.__value__) # recheck the value

    def __init__(self, __o: dict | void):
        self.__set__(__o if not isinstance(__o, void) else {})
        super().__init__(self.__value__)
        
    def __get__(self) -> dict:
        return self.__value__

class hx_list[T](list, metaclass=multimeta):
    __value__: list = []
    __generic__: subtype = None
    
    def __set__(self, __o: list | void) -> None:
        if isinstance(__o, self.__class__ if not self.__generic__ else self.__generic__):
            self.__value__ = __o
        else:
            try:
                self.__value__ = list(__o)
                if self.__generic__ and not isinstance(self.__value__, self.__generic__):
                    panic(
                        TypeError(f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"),
                        file=__file__,
                    )
            except Exception as e:
                panic(
                    TypeError(f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"),
                    file=__file__,
                )
                
    def __set_generic__(self, __o: str) -> None:
        exec(f"self.__generic__ = {f'subtype(list[{__o[1:-1]}]'.replace('hx_list', 'list')} | void)")
        if self.__value__: self.__set__(self.__value__) # recheck the value

    def __init__(self, __o: list | void):
        self.__set__(__o if not isinstance(__o, void) else [])
        super().__init__(self.__value__)
        
    def __get__(self) -> list:
        return self.__value__


class hx_bool(metaclass=multimeta):
    __value__: bool = False
    
    def __set__(self, __o: bool | void) -> None:
        if isinstance(__o, self.__class__):
            self.__value__ = __o
        else:
            try:
                self.__value__ = bool(__o)
            except Exception as e:
                panic(
                    TypeError(f"Expected type {self.__class__}, got {type(__o)}, unable to cast"),
                    file=__file__,
                )
                
    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=__file__,
        )
    
    def __init__(self, __o: bool | void):
        self.__set__(__o if not isinstance(__o, void) else False)
    def __get__(self) -> bool:
        return self.__value__
    def __and__(self, __o: bool) -> bool:
        return self.__value__ and __o
    def __and__(self, __o: int) -> int:
        return self.__value__ and __o
    def __or__(self, __o: bool) -> bool:
        return self.__value__ or __o
    def __or__(self, __o: int) -> int:
        return self.__value__ or __o
    def __xor__(self, __o: bool) -> bool:
        return self.__value__ ^ __o
    def __xor__(self, __o: int) -> int:
        return self.__value__ ^ __o
    def __rand__(self, __o: bool) -> bool:
        return __o and self.__value__
    def __rand__(self, __o: int) -> int:
        return __o and self.__value__
    def __ror__(self, __o: bool) -> bool:
        return __o or self.__value__
    def __ror__(self, __o: int) -> int:
        return __o or self.__value__
    def __rxor__(self, __o: bool) -> bool:
        return self.__value__ ^ __o
    def __rxor__(self, __o: int) -> int:
        return self.__value__ ^ __o
    def __getnewargs__(self) -> tuple[int]:
        return (self.__value__,)
    def __invert__(self) -> int:
        return ~self.__value__
    
class hx_char(str, metaclass=multimeta):
    __value__: str = ""
    
    def __set__(self, __o: str) -> None:
        if isinstance(__o, self.__class__):
            self.__value__ = __o
        else:
            try:
                self.__value__ = str(__o)
            except Exception as e:
                panic(
                    TypeError(f"Expected type {self.__class__}, got {type(__o)}, unable to cast"),
                    file=__file__,
                )
                
    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=__file__,
        )
    
    def __init__(self, __o: str):
        self.__set__(__o if not isinstance(__o, void) else "")
        super().__new__(self.__value__)
        
    def __get__(self) -> str:
        return self.__value__
    
class hx_tuple[T](tuple, metaclass=multimeta):
    __value__: tuple = ()
    __generic__: subtype = None
    
    def __set__(self, __o: tuple | void) -> None:
        if isinstance(__o, self.__class__ if not self.__generic__ else self.__generic__):
            self.__value__ = __o
        else:
            try:
                self.__value__ = tuple(__o)
                if self.__generic__ and not isinstance(self.__value__, self.__generic__):
                    panic(
                        TypeError(f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"),
                        file=__file__,
                    )
            except Exception as e:
                panic(
                    TypeError(f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"),
                    file=__file__,
                )
                
    def __set_generic__(self, __o: str) -> None:
        exec(f"self.__generic__ = {f'subtype(tuple[{__o[1:-1]}]'.replace('hx_tuple', 'tuple')} | void)")
        if self.__value__: self.__set__(self.__value__) # recheck the value

    def __init__(self, __o: tuple | void):
        self.__set__(__o if not isinstance(__o, void) else ())
        super().__new__(self.__value__)
        
    def __get__(self) -> tuple:
        return self.__value__
    
class hx_array[T](list, metaclass=multimeta):
    __value__: list = []
    __generic__: subtype = None
    
    def __set__(self, __o: list | void) -> None:
        if isinstance(__o, self.__class__ if not self.__generic__ else self.__generic__):
            self.__value__ = __o
        else:
            try:
                self.__value__ = list(__o)
                if self.__generic__ and not isinstance(self.__value__, self.__generic__):
                    panic(
                        TypeError(f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"),
                        file=__file__,
                    )
            except Exception as e:
                panic(
                    TypeError(f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"),
                    file=__file__,
                )
                
    def __set_generic__(self, __o: str) -> None:
        exec(f"self.__generic__ = {f'subtype(list[{__o[1:-1]}]'.replace('hx_array', 'list')} | void)")
        if self.__value__: self.__set__(self.__value__) # recheck the value

    def __init__(self, __o: list | void):
        self.__set__(__o if not isinstance(__o, void) else [])
        super().__init__(self.__value__)
        
    def __get__(self) -> list:
        return self.__value__
    
class hx_set[T](set, metaclass=multimeta):
    __value__: set = set()
    __generic__: subtype = None
    
    def __set__(self, __o: set | void) -> None:
        if isinstance(__o, self.__class__ if not self.__generic__ else self.__generic__):
            self.__value__ = __o
        else:
            try:
                self.__value__ = set(__o)
                if self.__generic__ and not isinstance(self.__value__, self.__generic__):
                    panic(
                        TypeError(f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"),
                        file=__file__,
                    )
            except Exception as e:
                panic(
                    TypeError(f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"),
                    file=__file__,
                )
                
    def __set_generic__(self, __o: str) -> None:
        exec(f"self.__generic__ = {f'subtype(set[{__o[1:-1]}]'.replace('hx_set', 'set')} | void)")
        if self.__value__: self.__set__(self.__value__) # recheck the value

    def __init__(self, __o: set | void):
        self.__set__(__o if not isinstance(__o, void) else set())
        super().__init__(self.__value__)
        
    def __get__(self) -> set:
        return self.__value__
    
class hx_unknown(metaclass=multimeta):
    __value__: Any = None
    
    def __set__(self, __o: Any | void) -> None:
        if isinstance(__o, self.__class__):
            self.__value__ = __o
        else:
            try:
                self.__value__ = __o
            except Exception as e:
                panic(
                    TypeError(f"Expected type {self.__class__}, got {type(__o)}, unable to cast"),
                    file=__file__,
                )
                
    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=__file__,
        )
    
    def __init__(self, __o: Any | void):
        self.__set__(__o if not isinstance(__o, void) else None)
    def __get__(self) -> Any:
        return self.__value__