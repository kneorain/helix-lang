# trunk-ignore-all(isort, mypy, flake8, black, ruff)
# type: ignore
from __future__ import annotations
from abc import ABC
from abc import abstractmethod as hx__abstract_method
from collections.abc import Iterator
from dataclasses import dataclass
from decimal import (Decimal as double, getcontext)
from array import array

from enum import Enum
from functools import wraps
import inspect
from threading import Thread
from types import MappingProxyType as FastMap, NoneType, FunctionType, UnionType, BuiltinFunctionType
from beartype.typing import Any, Callable, Literal, NoReturn, Self
from weakref import ref

from multimethod import DispatchError, multimeta
from multimethod import subtype

from typing import Type, TypeVar, Optional
from src.panic import panic, standalone_tokenize_line as _H_tokenize_line__
from time import sleep
#from include.c_cpp import __import_c__

# make an empty wrapper for hx__multi_method
def hx__multi_method(func: Callable) -> Callable:
    @wraps(func)
    def hx_internal_multi_method_decorator(*args, **kwargs):
        return func(*args, **kwargs)
    return hx_internal_multi_method_decorator




def __import_cpp__(*args, **kwargs):
    raise NotImplementedError("C++ is not supported in Helix (YET)")

def __import_c__(*args, **kwargs):
    raise NotImplementedError("C is not supported in Helix (YET)")

def __import_rs__(*args, **kwargs):
    raise NotImplementedError("Rust is not supported in Helix (YET)")

def __import_py__(*args, **kwargs):
    raise NotImplementedError("Python is not supported in Helix (YET)")

 


getcontext().prec = 128
replace_primitives = {
        "hx_int"    : "int",
        "hx_string" : "str",
        "hx_float"  : "float",
        "hx_map"    : "map",
        "hx_list"   : "list",
        "hx_bool"   : "bool",
        "hx_char"   : "char",
        "hx_void"   : "void",
        "hx_tuple"  : "tuple",
        "hx_array"  : "array",
        "hx_set"    : "set",
    }
__registered_functions__ = {}

#def hx__multi_method(func: Callable) -> Callable:
#    # get the annotations
#    blacklist   = ["return"]
#    annotations = [value for key, value in func.__annotations__.items() if key not in blacklist]
#    # get the name of the function
#    name = func.__name__
#    # get the return type
#    return_type = func.__annotations__.get("return", None)
#
#    # add | along with the replace_primitives if the type is a primitive
#    from typing import Type, get_args, Union, get_origin
#    
#    def get_replaced_type(type_: Type) -> Type:
#        # Check if type_ is a union type
#        if get_origin(type_) is UnionType:
#            # Get the types in the union
#            union_types = get_args(type_)
#            # Process each type in the union
#            return Union[tuple(get_replaced_type(_) for _ in union_types)]
#        else:
#            # Handle non-union types
#            return replace_type(type_)
#
#    def replace_type(type_: Type) -> Type:
#        if get_origin(type_) is UnionType:
#            return get_replaced_type(type_)
#        return  (
#            type_ if type_.__name__ not in replace_primitives else eval(replace_primitives[type_.__name__])
#        )
#
#    # Example usage
#    annotations = [get_replaced_type(_) for _ in annotations]
#    return_type = get_replaced_type(return_type) if return_type else None
#    
#    annotations = [get_replaced_type(_) for _ in annotations]
#    return_type = get_replaced_type(return_type) if return_type else None
#
#    if name not in __registered_functions__:
#        # name: [{types: (func, return_type)}, ...]
#        __registered_functions__[name] = []
#        __registered_functions__[name].append(
#            {
#                "types": tuple(annotations),
#                "func": func,
#                "return_type": return_type,
#            }
#        )
#    else:
#        __registered_functions__[name].append(
#            {
#                "types": tuple(annotations),
#                "func": func,
#                "return_type": return_type,
#            }
#        )
#    
#    
#    @wraps(func)
#    def wrapper(*args, **kwargs):
#        # get the types of the arguments
#
#        for arg in __registered_functions__[name]:
#             if all(isinstance(arg, type_) for arg, type_ in zip(args, arg["types"])):
#                val = arg["func"](*args, **kwargs)
#                if arg["return_type"] and not isinstance(val, arg["return_type"]):
#                    raise TypeError(
#                        f"Method '{name}' expects, '{str(arg['return_type']).replace('|', 'or')}', got something else."
#                    )
#                return val
#        else:
#            raise TypeError(
#                f"Method '{name}' expects, '{str(tuple(arg['types'])).replace('|', 'or')}', got something else."
#            )
#            
#    return wrapper

    

def printf(string: str, *args):
    #panic(
    #    NotImplementedError("printf is not implemented in Helix (YET)"),
    #    file=inspect.stack()[4].filename,
    #    line_no=inspect.stack()[4].lineno,
    #)
    print(string % args)
    
def scanf(string: str, *args):
    #panic(
    #    NotImplementedError("scanf is not implemented in Helix (YET)"),
    #    file=inspect.stack()[4].filename,
    #    line_no=inspect.stack()[4].lineno,
    #)
    return input(string % args)

unknown = Any


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

    def __empty__(self) -> bool:
        return True

    def __void__(self) -> bool:
        return True


DEFAULT_VALUE = void()


#class C_For:
#    def __init__(self, **kwargs):
#        # Initialize loop variables
#        self.loop_vars = kwargs
#        # Extract condition and increment expressions
#        self.condition = "True"
#        self.increment = ""
#        # Evaluate initial conditions
#        [exec(f"{var} = {value}") for var, value in self.loop_vars.items()]
#
#    def __iter__(self):
#        return self
#
#    def __next__(self):
#        if not self.loop_condition_met:
#            raise StopIteration
#        current_values = tuple(self.loop_vars.values())
#        exec(self.increment, None, self.loop_vars)
#        self.loop_condition_met = eval(self.condition, None, self.loop_vars)
#        return current_values if len(current_values) > 1 else current_values[0]
#
#    def set_con(self, condition):
#        self.condition = condition
#        self.loop_condition_met = eval(self.condition, None, self.loop_vars)
#        return self
#
#    def set_inc(self, increment):
#        self.increment = (
#            increment.replace("++", "+= 1")
#            .replace("--", "-= 1")
#            .replace("+*", "*= 1")
#            .replace("-*", "*= -1")
#            .replace("/-", "/ -1")
#            .replace("/*", "*= 1")
#        )
#        return self
class C_For:
    def __init__(self, **kwargs):
        # Initialize loop variables
        self.loop_vars = kwargs
        # Extract condition and increment expressions
        self.condition = "True"
        self.increment = ""
        # Evaluate initial conditions
        [exec(f"{var} = {value}") for var, value in self.loop_vars.items()]
        self.loop_condition_met = eval(self.condition, None, self.loop_vars)

    async def __aiter__(self):
        return self

    async def __anext__(self):
        if not self.loop_condition_met:
            raise StopAsyncIteration
        current_values = tuple(self.loop_vars.values())
        exec(self.increment, None, self.loop_vars)
        self.loop_condition_met = eval(self.condition, None, self.loop_vars)
        await asyncio.sleep(0)  # Yield control to allow other tasks to run
        return current_values if len(current_values) > 1 else current_values[0]

    def set_con(self, condition):
        self.condition = condition
        self.loop_condition_met = eval(self.condition, None, self.loop_vars)
        return self

    def set_inc(self, increment):
        self.increment = (
            increment.replace("++", "+= 1")
            .replace("--", "-= 1")
            .replace("+*", "*= 1")
            .replace("-*", "*= -1")
            .replace("/-", "/ -1")
            .replace("/*", "*= 1")
        )
        return self


from beartype import beartype

def hx__async(func: Callable) -> Callable:
    def run_thread(func, args, kwargs):
        func._result = func(*args, **kwargs)
        func._thread_started = False

    @wraps(func)
    def wrapper(*args, **kwargs):
        if not hasattr(func, "_thread_started") or not func._thread_started:
            func._thread = Thread(target=run_thread, args=(func, args, kwargs))
            func._thread_started = True
            func._thread.start()
        return func

    def join(timeout=None):
        if hasattr(func, "_thread"):
            func._thread.join(timeout)
            return getattr(func, "_result", None)
        return None

    func.join = join
    wrapper.join = join
    return wrapper

class hx_void(void): pass

class hx_bool(metaclass=multimeta):
    __value__: int | void | bool | hx_bool | None = False

    def __set__(self, __o) -> None:
        if isinstance(__o, int):
            if __o != 0 and __o != 1:
                panic(
                    ValueError(f"Expected 0 or 1, got {__o}"),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )
            self.__value__ = bool(__o)
        elif isinstance(__o, hx_bool):
            self.__value__ = __o.__value__
        elif isinstance(__o, subtype(int | void | bool | hx_bool | hx_int | hx_void)):
            self.__value__ = __o
        elif isinstance(__o, NoneType):
            self.__value__ = None
        else:
            try:
                self.__value__ = bool(__o)
            except Exception as e:
                panic(
                    TypeError(
                        f"Expected type {self.__class__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )

    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=inspect.stack()[4].filename,
            line_no=inspect.stack()[4].lineno,
        )

    def __empty__(self) -> bool:
        return self.__value__ == False or self.__value__ == None

    def __init__(self, __o = False):
        self.__set__(__o)

    def __str__(self) -> str:
        return str(self.__value__)

    def __repr__(self) -> str:
        return repr(self.__value__)

    def __get__(self) -> bool:
        return self.__value__


class auto:
    __value__: Any = None
    __generic__: subtype = None
    __type__: type = None
    
    def __init__(self, __o = False, __pre: auto = None):
        if __pre:
            self.__generic__ = __pre.__generic__
            self.__type__    = __pre.__type__
        self.__set__(__o)
        
    def __set__(self, __o) -> None:
        if not self.__generic__ and not self.__type__:
            self.__value__ = __o
            self.__type__ = type(__o)
            self.__generic__ = subtype(type(__o))
        else:
            if self.__generic__ and not isinstance(
                __o, self.__generic__
            ):
                panic(
                    TypeError(
                        f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )
            if self.__type__ and not isinstance(
                __o, self.__type__
            ):
                panic(
                    TypeError(
                        f"Expected type {self.__type__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )
            self.__value__ = __o
        
    def __empty__(self) -> bool:
        return self.__value__ == False or self.__value__ == None
    def __str__(self) -> str:
        return str(self.__value__)

    def __repr__(self) -> str:
        return repr(self.__value__)

    def __get__(self) -> bool:
        return self.__value__


class hx_int(int, metaclass=multimeta):
    __value__: int | bytes | hx_bytes | float | double | void | hx_int | hx_float | hx_double | hx_char | None = 0

    def __set__(self, __o) -> None:
        if isinstance(__o, int):
            self.__value__ = __o
        elif isinstance(__o, hx_int):
            self.__value__ = __o.__value__
        elif isinstance(__o, subtype(int | bytes | hx_bytes | float | double | void | hx_float | hx_double | hx_int | hx_char | hx_void)):
            self.__value__ = (
                __o
                if not isinstance(__o, subtype(float | double | hx_float | hx_double)) else int(__o)
                if not isinstance(__o, subtype(hx_char | str)) else ord(__o.__value__)
                if isinstance(__o, hx_char) else ord(__o) if len(__o) == 1 else panic(
                    TypeError(
                        f"Got a string of length {len(__o)}, expected a char or similar."
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )
            )
        elif isinstance(__o, NoneType):
            self.__value__ = None
        else:
            try:
                self.__value__ = int(__o)
            except Exception as e:
                panic(
                    TypeError(
                        f"Expected type {self.__class__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )

    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=inspect.stack()[4].filename,
            line_no=inspect.stack()[4].lineno,
        )

    def __empty__(self) -> bool:
        return self.__value__ == 0 or self.__value__ == None

    def __init__(self, __o = 0):
        self.__set__(__o)

    def __get__(self) -> int:
        return self.__value__

    def __str__(self) -> str:
        return str(self.__value__)

    def __repr__(self) -> str:
        return repr(self.__value__)

    def __float__(self) -> float:
        return float(self.__value__)

    def __int__(self) -> int:
        return int(self.__value__)

    def __double__(self) -> double:
        return double(self.__value__)

    def __bytes__(self) -> bytes:
        return bytes(self.__value__)

    def __char__(self) -> str:
        return chr(self.__value__)

class hx_string(str, metaclass=multimeta):
    __value__: str | hx_string | hx_char | None = ""

    def __set__(self, __o) -> None:
        if isinstance(__o, str):
            self.__value__ = __o
        elif isinstance(__o, hx_string):
            self.__value__ = __o.__value__
        elif isinstance(__o, hx_char):
            self.__value__ = __o.__value__
        elif isinstance(__o, NoneType):
            self.__value__ = None
        else:
            try:
                self.__value__ = str(__o)
            except Exception as e:
                panic(
                    TypeError(
                        f"Expected type {self.__class__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )

    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=inspect.stack()[4].filename,
            line_no=inspect.stack()[4].lineno,
        )

    def __empty__(self) -> bool:
        return self.__value__ == "" or self.__value__ == None

    def __init__(self, __o = ""):
        self.__set__(__o)

    def __get__(self) -> str:
        return self.__value__

    def __str__(self) -> str:
        return str(self.__value__)

    def __repr__(self) -> str:
        return repr(self.__value__)

    def __bytes__(self) -> bytes:
        return bytes(self.__value__, "utf-8")


class hx_float(float, metaclass=multimeta):
    __value__: float | int | bytes | hx_bytes | double | void | hx_float | hx_double | hx_int | None = 0.0

    def __set__(self, __o) -> None:
        if isinstance(__o, float):
            self.__value__ = __o
        elif isinstance(__o, hx_float):
            self.__value__ = __o.__value__
        elif isinstance(__o, subtype(float | int | bytes | hx_bytes | double | void | hx_float | hx_double | hx_int)):
            self.__value__ = (
                __o
                if not isinstance(__o, subtype(int | bytes | hx_bytes | hx_int)) else float(__o)
            )
        elif isinstance(__o, NoneType):
            self.__value__ = None
        else:
            try:
                self.__value__ = float(__o)
            except Exception as e:
                panic(
                    TypeError(
                        f"Expected type {self.__class__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )

    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=inspect.stack()[4].filename,
            line_no=inspect.stack()[4].lineno,
        )

    def __empty__(self) -> bool:
        return self.__value__ == 0.0 or self.__value__ == None

    def __init__(self, __o = 0.0):
        self.__set__(__o)

    def __get__(self) -> float:
        return self.__value__

    def __str__(self) -> str:
        return str(self.__value__)

    def __repr__(self) -> str:
        return repr(self.__value__)

    def __float__(self) -> float:
        return float(self.__value__)

    def __int__(self) -> int:
        return int(self.__value__)

    def __double__(self) -> double:
        return double(self.__value__)

    def __bytes__(self) -> bytes:
        return bytes(self.__value__)

class hx_double(double, metaclass=multimeta):
    __value__: double | float | int | bytes | hx_bytes | void | hx_double | hx_float | hx_int | None = 0.0

    def __set__(self, __o) -> None:
        if isinstance(__o, double):
            self.__value__ = __o
        elif isinstance(__o, hx_double):
            self.__value__ = __o.__value__
        elif isinstance(__o, subtype(double | float | int | bytes | hx_bytes | void | hx_double | hx_float | hx_int)):
            self.__value__ = (
                __o
                if not isinstance(__o, subtype(float | hx_float | int | bytes | hx_bytes | hx_int)) else double(__o, 64)
            )
        elif isinstance(__o, NoneType):
            self.__value__ = None
        else:
            try:
                self.__value__ = double(__o, 64)
            except Exception as e:
                panic(
                    TypeError(
                        f"Expected type {self.__class__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )

    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=inspect.stack()[4].filename,
            line_no=inspect.stack()[4].lineno,
        )

    def __empty__(self) -> bool:
        return self.__value__ == 0.0 or self.__value__ == None

    def __init__(self, __o = 0.0):
        self.__set__(__o)

    def __get__(self) -> double:
        return self.__value__

    def __str__(self) -> str:
        return str(self.__value__)

    def __repr__(self) -> str:
        return repr(self.__value__)

    def __float__(self) -> float:
        return float(self.__value__)

    def __int__(self) -> int:
        return int(self.__value__)

    def __double__(self) -> double:
        return double(self.__value__)

    def __bytes__(self) -> bytes:
        return bytes(self.__value__)


class hx_char(str, metaclass=multimeta):
    __value__: str | int | bytes | hx_bytes | hx_char | hx_int | None = ""

    def __set__(self, __o) -> None:
        if isinstance(__o, str):
            self.__value__ = __o if len(__o) == 1 else panic(
                TypeError(
                    f"Got a string of length {len(__o)}, expected a char or similar."
                ),
                file=inspect.stack()[4].filename,
                line_no=inspect.stack()[4].lineno,
            )
        elif isinstance(__o, hx_char):
            self.__value__ = __o.__value__
        elif isinstance(__o, subtype(str | int | bytes | hx_bytes | hx_int)):
            self.__value__ = (
                __o
                if not isinstance(__o, subtype(int | bytes | hx_bytes | hx_int)) else chr(__o)
            )
        elif isinstance(__o, NoneType):
            self.__value__ = None
        else:
            try:
                self.__value__ = str(__o) if len(str(__o)) == 1 else panic(
                    TypeError(
                        f"Got a string of length {len(__o)}, expected a char or similar."
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )
            except Exception as e:
                panic(
                    TypeError(
                        f"Expected type {self.__class__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )

    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=inspect.stack()[4].filename,
            line_no=inspect.stack()[4].lineno,
        )

    def __empty__(self) -> bool:
        return self.__value__ == "" or self.__value__ == None

    def __init__(self, __o = ""):
        self.__set__(__o)

    def __get__(self) -> str:
        return self.__value__

    def __str__(self) -> str:
        return str(self.__value__)

    def __repr__(self) -> str:
        return repr(self.__value__)

    def __int__(self) -> int:
        return ord(self.__value__)

    def __char__(self) -> str:
        return self.__value__

    def __bytes__(self) -> bytes:
        return bytes(self.__value__, "utf-8")

class hx_bytes(bytes, metaclass=multimeta):
    __value__: bytes = b""

    def __set__(self, __o) -> None:
        if isinstance(__o, bytes):
            self.__value__ = __o
        elif isinstance(__o, hx_bytes):
            self.__value__ = __o.__value__
        elif isinstance(__o, subtype(bytes)):
            self.__value__ = __o
        elif isinstance(__o, NoneType):
            self.__value__ = None
        else:
            try:
                self.__value__ = bytes(__o, "utf-8")
            except Exception as e:
                panic(
                    TypeError(
                        f"Expected type {self.__class__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )

    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=inspect.stack()[4].filename,
            line_no=inspect.stack()[4].lineno,
        )

    def __empty__(self) -> bool:
        return self.__value__ == b"" or self.__value__ == None

    def __init__(self, __o = b""):
        self.__set__(__o)

    def __get__(self) -> bytes:
        return self.__value__

    def __str__(self) -> str:
        return str(self.__value__)

    def __repr__(self) -> str:
        return repr(self.__value__)

    def __bytes__(self) -> bytes:
        return self.__value__

T = TypeVar("T")

class hx_tuple(tuple, metaclass=multimeta):
    __value__: tuple | hx_tuple | None = ()
    __generic__: subtype = None
    
    def __set__(self, __o) -> None:
        if not self.__generic__:
            if isinstance(__o, tuple):
                self.__value__ = __o
            elif isinstance(__o, hx_tuple):
                self.__value__ = __o.__value__
            elif isinstance(__o, subtype(tuple)):
                self.__value__ = __o
            elif isinstance(__o, NoneType):
                self.__value__ = None
            else:
                try:
                    self.__value__ = tuple(__o)
                except Exception as e:
                    panic(
                        TypeError(
                            f"Expected type {self.__class__}, got {type(__o)}, unable to cast"
                        ),
                        file=inspect.stack()[4].filename,
                        line_no=inspect.stack()[4].lineno,
                    )
        else:
            try:
                self.__value__ = tuple(__o) if not isinstance(__o, hx_tuple) else __o.__value__
                if self.__generic__ and not isinstance(
                    self.__value__, self.__generic__
                ):
                    panic(
                        TypeError(
                            f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"
                        ),
                        file=inspect.stack()[4].filename,
                        line_no=inspect.stack()[4].lineno,
                    )
            except Exception as e:
                panic(
                    TypeError(
                        f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )
        super().__init__(self.__value__)
                
    def __set_generic__(self, __o: str) -> None:
        exec(f"self.__generic__ = {f'subtype(tuple[{__o[1:-1]}]'.replace('hx_tuple', 'tuple')} | void)")
        if self.__value__:
            self.__set__(self.__value__) # recheck the value
            
    def __init__(self, __o = ()):
        self.__set__(__o)
        super().__init__(self.__value__)
    
    def __get__(self) -> tuple:
        return self.__value__
    
    def __str__(self) -> str:
        return str(self.__value__)
    
    def __repr__(self) -> str:
        return repr(self.__value__)
    
    def __empty__(self) -> bool:
        return self.__value__ == () or self.__value__ == None
    
    @property
    def length(self) -> int:
        return len(self.__value__)
    
    @property
    def first(self) -> T:
        return self.__value__[0]
    
    @property
    def last(self) -> T:
        return self.__value__[-1]

# Derived Types
class hx_list(list, metaclass=multimeta):
    __value__: list = None
    __generic__: subtype = None
    __initialized__ = False
    
    def __check_if_initialed(self) -> None:
        if not self.__initialized__:
            panic(
                TypeError(
                    f"Expected type a generic to be set, got none instead."
                ),
                file=inspect.stack()[5].filename,
                line_no=inspect.stack()[5].lineno,
            )
        return
    
    def __type_check__(self, __o: Any) -> None:
        if self.__generic__:
            if not isinstance(__o, self.__generic__):
                panic(
                    TypeError(
                        f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )
                
    def __set_generic__(self, __o: str) -> Self:
        exec(
            f"self.__generic__ = subtype(list{__o} | {((' | '.join(['list[' + _ + ']' for _ in [replace_primitives[_] for _ in replace_primitives if _ in __o]])) + ' | ') if ' | '.join(['list[' + _ + ']' for _ in [replace_primitives[_] for _ in replace_primitives if _ in __o] if _]) else ''} void {'| list' if not __o.endswith(']') else ''})"
        )
        if self.__initialized__:
            panic(
                TypeError(
                    f"Generic type already set, cannot change it."
                ),
                file=inspect.stack()[4].filename,
                line_no=inspect.stack()[4].lineno,
            )
        self.__initialized__ = True
        if self.__value__: self.__type_check__(self.__value__)  # recheck the value
        return self
        
            
    def __init__(self, __o = None):
        self.__value__ = __o if not isinstance(__o, void) else [] if isinstance(__o, NoneType) else None
        
    def __get__(self) -> list:
        self.__check_if_initialed()
        return self.__value__
    
    def __empty__(self) -> bool:
        self.__check_if_initialed()
        return self.__value__ == [] or self.__value__ == None
    
    def __str__(self) -> str:
        self.__check_if_initialed()
        return str(self.__value__)
    
    def __repr__(self) -> str:
        self.__check_if_initialed()
        return repr(self.__value__)
    
    @property
    def length(self) -> int:
        self.__check_if_initialed()
        return len(self.__value__)

class hx_array(array, metaclass=multimeta):
    __value__: list = None
    __generic__: subtype = None
    __initialized__ = False
    
    def __check_if_initialed(self) -> None:
        if not self.__initialized__:
            panic(
                TypeError(
                    f"Expected type a generic to be set, got none instead."
                ),
                file=inspect.stack()[5].filename,
                line_no=inspect.stack()[5].lineno,
            )
        return
    
    def __type_check__(self, __o: Any) -> None:
        if self.__generic__:
            if not isinstance(__o, self.__generic__):
                panic(
                    TypeError(
                        f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )
                
    def __set_generic__(self, __o: str) -> Self:
        exec(
            f"self.__generic__ = subtype(list{__o} | {((' | '.join(['list[' + _ + ']' for _ in [replace_primitives[_] for _ in replace_primitives if _ in __o]])) + ' | ') if ' | '.join(['array[' + _ + ']' for _ in [replace_primitives[_] for _ in replace_primitives if _ in __o] if _]) else ''} void {'| array' if not __o.endswith(']') else ''})"
        )
        if self.__initialized__:
            panic(
                TypeError(
                    f"Generic type already set, cannot change it."
                ),
                file=inspect.stack()[4].filename,
                line_no=inspect.stack()[4].lineno,
            )
        self.__initialized__ = True
        if self.__value__: self.__type_check__(self.__value__)  # recheck the value
        return self
    
    def __init__(self, __o = None):
        self.__value__ = __o if not isinstance(__o, void) else [] if isinstance(__o, NoneType) else None
        
    def __get__(self) -> list:
        self.__check_if_initialed()
        return self.__value__
    
    def __empty__(self) -> bool:
        self.__check_if_initialed()
        return self.__value__ == [] or self.__value__ == None
    
    def __str__(self) -> str:
        self.__check_if_initialed()
        return str(self.__value__)
    
    def __repr__(self) -> str:
        self.__check_if_initialed()
        return repr(self.__value__)
    
    @property
    def length(self) -> int:
        self.__check_if_initialed()
        return len(self.__value__)

class hx_set(set, metaclass=multimeta):
    __value__: list = None
    __generic__: subtype = None
    __initialized__ = False
    
    def __check_if_initialed(self) -> None:
        if not self.__initialized__:
            panic(
                TypeError(
                    f"Expected type a generic to be set, got none instead."
                ),
                file=inspect.stack()[5].filename,
                line_no=inspect.stack()[5].lineno,
            )
        return
    
    def __type_check__(self, __o: Any) -> None:
        if self.__generic__:
            if not isinstance(__o, self.__generic__):
                panic(
                    TypeError(
                        f"Expected type {self.__generic__}, got {type(__o)}, unable to cast"
                    ),
                    file=inspect.stack()[4].filename,
                    line_no=inspect.stack()[4].lineno,
                )
                
    def __set_generic__(self, __o: str) -> Self:
        exec(
            f"self.__generic__ = subtype(set{__o} | {((' | '.join(['set[' + _ + ']' for _ in [replace_primitives[_] for _ in replace_primitives if _ in __o]])) + ' | ') if ' | '.join(['set[' + _ + ']' for _ in [replace_primitives[_] for _ in replace_primitives if _ in __o] if _]) else ''} void {'| set' if not __o.endswith(']') else ''})"
        )
        if self.__initialized__:
            panic(
                TypeError(
                    f"Generic type already set, cannot change it."
                ),
                file=inspect.stack()[4].filename,
                line_no=inspect.stack()[4].lineno,
            )
        self.__initialized__ = True
        if self.__value__: self.__type_check__(self.__value__)  # recheck the value
        return self
    
    def __init__(self, __o = None):
        self.__value__ = __o if not isinstance(__o, void) else set() if isinstance(__o, NoneType) else None
        
    def __get__(self) -> list:
        self.__check_if_initialed()
        return self.__value__
    
    def __empty__(self) -> bool:
        self.__check_if_initialed()
        return self.__value__ == set() or self.__value__ == None
    
    def __str__(self) -> str:
        self.__check_if_initialed()
        return str(self.__value__)
    
    def __repr__(self) -> str:
        self.__check_if_initialed()
        return repr(self.__value__)
    
    @property
    def length(self) -> int:
        self.__check_if_initialed()
        return len(self.__value__)
    
    
    
    
class hx_map(dict, metaclass=multimeta):
    __value__: list = None
    __generic__: subtype = None
    __initialized__ = False


class hx_unknown(metaclass=multimeta):
    __value__: Any = None

    def __set__(self, __o) -> None:
        self.__value__ = __o if not isinstance(__o, void) else None if not isinstance(__o, hx_unknown) else __o.__value__

    def __set_generic__(self, _: str) -> NoReturn:
        panic(
            TypeError(f"Cannot set generic type for {self.__class__}"),
            file=inspect.stack()[4].filename,
            line_no=inspect.stack()[4].lineno,
        )

    def __init__(self, __o):
        self.__set__(__o if not isinstance(__o, void) else None)

    def __get__(self) -> Any:
        return self.__value__

string = hx_string

class std:
    @staticmethod
    def generate(iter: Iterator, func: Callable, filter: Callable = None) -> list:
        return [func(_) for _ in iter if not filter or filter(_)]

    def div_by_0() -> int:
        return 1 / 0


# def __int__(self) -> int: return self.__value__
    # def __add__(self, __value: int) -> int: return self.__value__ + __value
    # def __sub__(self, __value: int) -> int: return self.__value__ - __value
    # def __mul__(self, __value: int) -> int: return self.__value__ * __value
    # def __floordiv__(self, __value: int) -> int: return self.__value__ // __value
    # def __truediv__(self, __value: int) -> float: return self.__value__ / __value
    # def __mod__(self, __value: int) -> int: return self.__value__ % __value
    # def __divmod__(self, __value: int) -> tuple[int, int]: return divmod(self.__value__, __value)
    # def __radd__(self, __value: int) -> int: return __value + self.__value__
    # def __rsub__(self, __value: int) -> int: return __value - self.__value__
    # def __rmul__(self, __value: int) -> int: return __value * self.__value__
    # def __rfloordiv__(self, __value: int) -> int: return __value // self.__value__
    # def __rtruediv__(self, __value: int) -> float: return __value / self.__value__
    # def __rmod__(self, __value: int) -> int: return __value % self.__value__
    # def __rdivmod__(self, __value: int) -> tuple[int, int]: return divmod(__value, self.__value__)
    # def __pow__(self, __value: int, __mod: int) -> int: return self.__value__ ** __value
    # def __rpow__(self, __value: int, __mod: int | None = None) -> Any: return __value ** self.__value__
    # def __and__(self, __value: int) -> int: return self.__value__ & __value
    # def __or__(self, __value: int) -> int: return self.__value__ | __value
    # def __xor__(self, __value: int) -> int: return self.__value__ ^ __value
    # def __lshift__(self, __value: int) -> int: return self.__value__ << __value
    # def __rshift__(self, __value: int) -> int: return self.__value__ >> __value
    # def __rand__(self, __value: int) -> int: return __value & self.__value__
    # def __ror__(self, __value: int) -> int: return __value | self.__value__
    # def __rxor__(self, __value: int) -> int: return __value ^ self.__value__
    # def __rlshift__(self, __value: int) -> int: return __value << self.__value__
    # def __rrshift__(self, __value: int) -> int: return __value >> self.__value__
    # def __neg__(self) -> int: return -self.__value__
    # def __pos__(self) -> int: return +self.__value__
    # def __invert__(self) -> int: return ~self.__value__
    # def __trunc__(self) -> int: return self.__value__
    # def __ceil__(self) -> int: return self.__value__
    # def __floor__(self) -> int: return self.__value__
    # def __round__(self, __ndigits: int) -> int: return round(self.__value__, __ndigits)
    # def __getnewargs__(self) -> tuple[int]: return (self.__value__,)
    # def __eq__(self, __value: object) -> bool: return self.__value__ == __value
    # def __ne__(self, __value: object) -> bool: return self.__value__ != __value
    # def __lt__(self, __value: int) -> bool: return self.__value__ < __value
    # def __le__(self, __value: int) -> bool: return self.__value__ <= __value
    # def __gt__(self, __value: int) -> bool: return self.__value__ > __value
    # def __ge__(self, __value: int) -> bool: return self.__value__ >= __value
    # def __float__(self) -> float: return float(self.__value__)
    # def __int__(self) -> int: return self.__value__
    # def __abs__(self) -> int: return abs(self.__value__)
    # def __hash__(self) -> int: return hash(self.__value__)
    # def __bool__(self) -> bool: return bool(self.__value__)
    # def __index__(self) -> int: return self.__value__


#    def __and__(self, __o: bool) -> bool:
#        return self.__value__ and __o
#
#    def __and__(self, __o: int) -> int:
#        return self.__value__ and __o
#
#    def __or__(self, __o: bool) -> bool:
#        return self.__value__ or __o
#
#    def __or__(self, __o: int) -> int:
#        return self.__value__ or __o
#
#    def __xor__(self, __o: bool) -> bool:
#        return self.__value__ ^ __o
#
#    def __xor__(self, __o: int) -> int:
#        return self.__value__ ^ __o
#
#    def __rand__(self, __o: bool) -> bool:
#        return __o and self.__value__
#
#    def __rand__(self, __o: int) -> int:
#        return __o and self.__value__
#
#    def __ror__(self, __o: bool) -> bool:
#        return __o or self.__value__
#
#    def __ror__(self, __o: int) -> int:
#        return __o or self.__value__
#
#    def __rxor__(self, __o: bool) -> bool:
#        return self.__value__ ^ __o
#
#    def __rxor__(self, __o: int) -> int:
#        return self.__value__ ^ __o
#
#    def __getnewargs__(self) -> tuple[int]:
#        return (self.__value__,)
#
#    def __invert__(self) -> int:
#        return ~self.__value__